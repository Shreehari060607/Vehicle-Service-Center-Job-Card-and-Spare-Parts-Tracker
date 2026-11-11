# Vehicle Service Center Job Card and Spare Parts Tracker — Detailed Design Document

## 5. High-Level Architecture

### 5.1 Architecture Description

The software uses a layered modular architecture designed to separate concerns across user interaction, core business logic, file storage, and data validation:

1. **Presentation Layer (`src/main.c`)**: Manages high-level control flow, presents interactive menus, and captures user inputs.
2. **Business Logic Layer (`src/job_card.c`, `src/spare_parts.c`, `src/billing.c`)**: Implements primary domain rules including state transition validation ($\text{Open} \rightarrow \text{In Progress} \rightarrow \text{Completed} \rightarrow \text{Billed}$), inventory deduction, low-stock threshold evaluation, and billing calculations ($\text{Labour} + \text{Parts} + \text{GST} - \text{Discount}$).
3. **Data Management & Utility Layer (`src/file_io.c`, `src/utils.c`)**: Handles persistent file read/write operations, menu option parsing, input cleaning, and pattern verification (such as Indian vehicle registration format checks).

### 5.2 Architecture Diagram

```
                     +-----------------------------------+
                     |         User Interface            |
                     |             (main.c)              |
                     +-----------------------------------+
                                       |
                   +-------------------+-------------------+
                   |                   |                   |
                   v                   v                   v
        +--------------------+ +-------------------+ +-------------------+
        |  Job Card Module   | | Spare Parts Module| |   Billing Module  |
        |    (job_card.c)    | |  (spare_parts.c)  | |    (billing.c)    |
        +--------------------+ +-------------------+ +-------------------+
                   |                   |                   |
                   +-------------------+-------------------+
                                       |
                   +-------------------+-------------------+
                   |                                       |
                   v                                       v
        +--------------------+                   +-------------------+
        |   File I/O Module  |                   |   Utility Module  |
        |     (file_io.c)    |                   |     (utils.c)     |
        +--------------------+                   +-------------------+
                   |
                   v
        +--------------------+
        |  Data Files (.txt) |
        +--------------------+
```

### 5.3 High-Level Workflow

1. **Initialization**: Program starts $\rightarrow$ `file_io` loads existing job cards and spare parts from text files into memory structures $\rightarrow$ initializes system state.
2. **Main Menu Loop**: User chooses an operation (Create Job, Update Parts, Consume Parts, Advance Status, Calculate Bill, View Reports).
3. **Validation & Processing**: Input is checked by `utils` $\rightarrow$ domain module updates data structures $\rightarrow$ file state is synced back to disk.
4. **Termination**: User selects exit $\rightarrow$ final state saved $\rightarrow$ program closes gracefully.

---

## 6. Module Design

### 6.1 Module Summary

| Module Name | Source File | Header File | Responsibility |
|---|---|---|---|
| Main Application | `src/main.c` | N/A | Controls top-level menu flow and high-level user interaction. |
| Job Card | `src/job_card.c` | `include/job_card.h` | Manages job card creation, retrieval, search, and status workflow state machine. |
| Spare Parts | `src/spare_parts.c` | `include/spare_parts.h` | Manages inventory items, additions, stock level updates, and reorder alerts. |
| Billing | `src/billing.c` | `include/billing.h` | Computes labour charges, parts total, GST, and net payable amounts. |
| File I/O | `src/file_io.c` | `include/file_io.h` | Handles reading from and writing job card and inventory data to plain text files. |
| Utilities | `src/utils.c` | `include/utils.h` | Provides input parsing, validation rules, and helper functions. |

---

### 6.2 Detailed Module Description

#### Module: Job Card
* **Source file**: `src/job_card.c`
* **Header file**: `include/job_card.h`
* **Purpose**: Manages job card operations and ensures proper status workflow transition.
* **Responsibilities**:
  * Create new job cards with validated vehicle registration numbers.
  * Search job cards by ID or filter by status.
  * Transition status along sequence: $\text{Open} \rightarrow \text{In Progress} \rightarrow \text{Completed} \rightarrow \text{Billed}$.
  * Attach consumed spare parts to job records.
* **Public functions**:
  * `void JobCard_Init(void);`
  * `Status_t JobCard_Create(const JobCard_t *job);`
  * `Status_t JobCard_FindById(uint32_t jobId, JobCard_t *outJob);`
  * `Status_t JobCard_UpdateStatus(uint32_t jobId, JobStatus_t newStatus);`
  * `Status_t JobCard_AddPartUsage(uint32_t jobId, uint32_t partId, uint32_t qty);`
  * `Status_t JobCard_GetByStatus(JobStatus_t status, JobCard_t *outList, uint32_t *outCount);`
  * `uint32_t JobCard_GetCount(void);`
  * `const JobCard_t* JobCard_GetAll(void);`
* **Data used or owned**: Array of `JobCard_t` structures (`MAX_JOBS` capacity) and active job count.
* **Dependencies**: `spare_parts.h`, `utils.h`
* **Possible errors**: `ERR_JOB_NOT_FOUND`, `ERR_DUPLICATE_ID`, `ERR_INVALID_STATUS_TRANSITION`, `ERR_MAX_PARTS_EXCEEDED`

---

#### Module: Spare Parts
* **Source file**: `src/spare_parts.c`
* **Header file**: `include/spare_parts.h`
* **Purpose**: Controls spare parts stock, additions, inventory deductions, and low-stock checks.
* **Responsibilities**:
  * Maintain spare parts records (ID, name, stock, unit price, reorder level).
  * Validate and deduct stock upon job usage.
  * Replenish inventory when new stock is received.
  * Identify parts requiring reorder.
* **Public functions**:
  * `void SpareParts_Init(void);`
  * `Status_t SpareParts_Add(const SparePart_t *part);`
  * `Status_t SpareParts_FindById(uint32_t partId, SparePart_t *outPart);`
  * `Status_t SpareParts_DeductStock(uint32_t partId, uint32_t qty);`
  * `Status_t SpareParts_AddStock(uint32_t partId, uint32_t qty);`
  * `Status_t SpareParts_GetLowStock(SparePart_t *outList, uint32_t *outCount);`
  * `uint32_t SpareParts_GetCount(void);`
  * `const SparePart_t* SpareParts_GetAll(void);`
* **Data used or owned**: Array of `SparePart_t` structures (`MAX_PARTS` capacity) and active parts count.
* **Dependencies**: `utils.h`
* **Possible errors**: `ERR_PART_NOT_FOUND`, `ERR_DUPLICATE_ID`, `ERR_INSUFFICIENT_STOCK`

---

#### Module: Billing
* **Source file**: `src/billing.c`
* **Header file**: `include/billing.h`
* **Purpose**: Calculates final billing breakdowns for completed jobs.
* **Responsibilities**:
  * Retrieve labour charge based on predefined service type constants.
  * Compute total parts cost for attached parts.
  * Calculate GST ($18\%$) and apply optional discounts to compute net total.
* **Public functions**:
  * `Status_t Billing_Calculate(uint32_t jobId, float discountPercentage, Bill_t *outBill);`
  * `float Billing_GetLabourCharge(ServiceType_t serviceType);`
* **Data used or owned**: Reads job and part details via `job_card` and `spare_parts` modules.
* **Dependencies**: `job_card.h`, `spare_parts.h`
* **Possible errors**: `ERR_JOB_NOT_FOUND`, `ERR_INVALID_DISCOUNT`

---

#### Module: File I/O
* **Source file**: `src/file_io.c`
* **Header file**: `include/file_io.h`
* **Purpose**: Handles persistence of system records to plain text storage.
* **Responsibilities**:
  * Load job records and spare part records from files during startup.
  * Save job and spare part records whenever data changes or system exits.
  * Export structured bill invoices to disk.
* **Public functions**:
  * `Status_t FileIO_LoadJobs(const char *filename, JobCard_t *jobs, uint32_t *count);`
  * `Status_t FileIO_SaveJobs(const char *filename, const JobCard_t *jobs, uint32_t count);`
  * `Status_t FileIO_LoadParts(const char *filename, SparePart_t *parts, uint32_t *count);`
  * `Status_t FileIO_SaveParts(const char *filename, const SparePart_t *parts, uint32_t count);`
  * `Status_t FileIO_ExportBill(const char *filename, const JobCard_t *job, const Bill_t *bill);`
* **Data used or owned**: File streams (`FILE*`) and string file paths.
* **Dependencies**: `job_card.h`, `spare_parts.h`
* **Possible errors**: `ERR_FILE_OPEN_FAILED`, `ERR_FILE_READ_FAILED`, `ERR_FILE_WRITE_FAILED`

---

#### Module: Utilities
* **Source file**: `src/utils.c`
* **Header file**: `include/utils.h`
* **Purpose**: Provides string parsing, input validation, and verification utilities.
* **Responsibilities**:
  * Trim trailing newlines and whitespace from input strings.
  * Validate Indian vehicle registration number format (e.g., `MH12AB1234`).
  * Validate integer and floating-point numeric inputs.
  * Map enums to human-readable text labels.
* **Public functions**:
  * `bool Utils_ValidateVehReg(const char *regNum);`
  * `void Utils_TrimNewline(char *str);`
  * `bool Utils_ParseUInt(const char *str, uint32_t *outVal);`
  * `bool Utils_ParseFloat(const char *str, float *outVal);`
  * `const char* Utils_StatusToString(JobStatus_t status);`
  * `const char* Utils_ServiceTypeToString(ServiceType_t type);`
  * `const char* Utils_ErrorToString(Status_t err);`
* **Data used or owned**: Temporary buffer memory.
* **Dependencies**: None
* **Possible errors**: Returns boolean flags (`true`/`false`) or text strings.

---

## 7. Data Design

### 7.1 Structure Definitions

#### Structure: `UsedPart_t`
* **Purpose**: Represents a part used in a specific job card.
* **Definition**:
```c
typedef struct {
    uint32_t partId;
    uint32_t quantity;
    float unitPrice;
} UsedPart_t;
```
* **Member details**:
| Member | C Type | Valid Range or Size | Description |
|---|---|---|---|
| `partId` | `uint32_t` | 100 to 999 | Unique identifier of used spare part. |
| `quantity` | `uint32_t` | 1 to 100 | Quantity consumed for job. |
| `unitPrice` | `float` | 0.0 to 100000.0 | Unit price in INR. |

---

#### Structure: `JobCard_t`
* **Purpose**: Holds details, state, and usage records for a single vehicle service job.
* **Definition**:
```c
typedef struct {
    uint32_t jobId;
    char vehicleReg[MAX_REG_LEN];
    char ownerName[MAX_NAME_LEN];
    char complaint[MAX_DESC_LEN];
    ServiceType_t serviceType;
    JobStatus_t status;
    UsedPart_t usedParts[MAX_PARTS_PER_JOB];
    uint32_t usedPartCount;
} JobCard_t;
```
* **Member details**:
| Member | C Type | Valid Range or Size | Description |
|---|---|---|---|
| `jobId` | `uint32_t` | 1000 to 9999 | Unique identifier for job card. |
| `vehicleReg` | `char[16]` | Indian reg format | Vehicle registration plate text. |
| `ownerName` | `char[50]` | 1 to 49 chars | Owner full name. |
| `complaint` | `char[100]` | 1 to 99 chars | Customer complaint summary. |
| `serviceType` | `ServiceType_t` | 0 to 2 | Service type enumeration. |
| `status` | `JobStatus_t` | 0 to 3 | Workflow status enumeration. |
| `usedParts` | `UsedPart_t[10]` | Max 10 items | Array of parts used. |
| `usedPartCount` | `uint32_t` | 0 to 10 | Count of used parts. |

---

#### Structure: `SparePart_t`
* **Purpose**: Represents inventory stock information for a spare part item.
* **Definition**:
```c
typedef struct {
    uint32_t partId;
    char name[MAX_NAME_LEN];
    uint32_t quantity;
    float unitPrice;
    uint32_t reorderLevel;
} SparePart_t;
```
* **Member details**:
| Member | C Type | Valid Range or Size | Description |
|---|---|---|---|
| `partId` | `uint32_t` | 100 to 999 | Unique spare part ID. |
| `name` | `char[50]` | 1 to 49 chars | Descriptive part name. |
| `quantity` | `uint32_t` | 0 to 1000 | Stock quantity on hand. |
| `unitPrice` | `float` | 0.0 to 50000.0 | Unit price in INR. |
| `reorderLevel` | `uint32_t` | 1 to 100 | Minimum stock alert limit. |

---

#### Structure: `Bill_t`
* **Purpose**: Stores complete billing breakdown details for a job card.
* **Definition**:
```c
typedef struct {
    uint32_t jobId;
    float labourCharge;
    float partsTotal;
    float subtotal;
    float gstAmount;
    float discountAmount;
    float grandTotal;
} Bill_t;
```
* **Member details**:
| Member | C Type | Valid Range or Size | Description |
|---|---|---|---|
| `jobId` | `uint32_t` | 1000 to 9999 | ID of billed job card. |
| `labourCharge` | `float` | $\ge 0.0$ | Fixed charge based on service type. |
| `partsTotal` | `float` | $\ge 0.0$ | Sum total of consumed parts. |
| `subtotal` | `float` | $\ge 0.0$ | Sum of labour and parts costs. |
| `gstAmount` | `float` | $\ge 0.0$ | Tax amount calculated at $18\%$. |
| `discountAmount` | `float` | $\ge 0.0$ | Discount value applied. |
| `grandTotal` | `float` | $\ge 0.0$ | Net amount payable. |

---

### 7.2 Enumeration Definitions

#### Enumeration: `JobStatus_t`
```c
typedef enum {
    STATUS_OPEN = 0,
    STATUS_IN_PROGRESS,
    STATUS_COMPLETED,
    STATUS_BILLED
} JobStatus_t;
```
| Enumeration Constant | Meaning |
|---|---|
| `STATUS_OPEN` | Job card created; work not started. |
| `STATUS_IN_PROGRESS` | Service work in progress. |
| `STATUS_COMPLETED` | Service work completed; ready for billing. |
| `STATUS_BILLED` | Bill calculated and job closed. |

---

#### Enumeration: `ServiceType_t`
```c
typedef enum {
    SERVICE_PERIODIC = 0,
    SERVICE_REPAIR,
    SERVICE_ACCIDENT
} ServiceType_t;
```
| Enumeration Constant | Meaning |
|---|---|
| `SERVICE_PERIODIC` | Routine maintenance service. |
| `SERVICE_REPAIR` | Specific component repair or replacement. |
| `SERVICE_ACCIDENT` | Major overhaul or accident repair. |

---

### 7.3 Constants

| Constant Name | Value | Purpose |
|---|---|---|
| `MAX_JOBS` | `100` | Maximum job cards in memory |
| `MAX_PARTS` | `100` | Maximum spare parts in memory |
| `MAX_PARTS_PER_JOB` | `10` | Maximum unique parts allowed per job card |
| `GST_RATE_PERCENT` | `18.0f` | Standard GST tax rate percentage |
| `LABOUR_PERIODIC` | `500.0f` | Base labour rate for periodic service |
| `LABOUR_REPAIR` | `1000.0f` | Base labour rate for repairs |
| `LABOUR_ACCIDENT` | `2500.0f` | Base labour rate for accident repairs |

---

## 8. Function Design

### 8.1 Function: `JobCard_Create`
* **Module**: Job Card Module
* **Prototype**: `Status_t JobCard_Create(const JobCard_t *job);`
* **Purpose**: Validates and adds a new job card record to system memory.
* **Parameters**:
| Parameter | C Type | Direction | Description | Valid Values |
|---|---|---|---|---|
| `job` | `const JobCard_t*` | Input | Pointer to input job card struct | Non-null pointer with valid fields |
* **Return type**: `Status_t`
* **Return values**: `STATUS_SUCCESS`, `ERR_INVALID_INPUT`, `ERR_DUPLICATE_ID`, `ERR_STORAGE_FULL`
* **Preconditions**: `job` pointer is valid and non-null.
* **Postconditions**: Total job count incremented by 1; new record stored.
* **Errors handled**: Checks duplicate IDs, validates vehicle registration format, checks array capacity bounds.

---

### 8.2 Function: `JobCard_UpdateStatus`
* **Module**: Job Card Module
* **Prototype**: `Status_t JobCard_UpdateStatus(uint32_t jobId, JobStatus_t newStatus);`
* **Purpose**: Enforces sequential workflow transitions for job card status updates.
* **Parameters**:
| Parameter | C Type | Direction | Description | Valid Values |
|---|---|---|---|---|
| `jobId` | `uint32_t` | Input | Target job ID | Existing job ID (1000 to 9999) |
| `newStatus` | `JobStatus_t` | Input | Target status | `STATUS_OPEN` to `STATUS_BILLED` |
* **Return type**: `Status_t`
* **Return values**: `STATUS_SUCCESS`, `ERR_JOB_NOT_FOUND`, `ERR_INVALID_STATUS_TRANSITION`
* **Preconditions**: Target job card exists in system memory.
* **Postconditions**: Job card status updated to `newStatus`.
* **Errors handled**: Rejects out-of-sequence transitions (e.g., Open directly to Billed).

---

### 8.3 Function: `SpareParts_DeductStock`
* **Module**: Spare Parts Module
* **Prototype**: `Status_t SpareParts_DeductStock(uint32_t partId, uint32_t qty);`
* **Purpose**: Reduces stock quantity for a spare part after verifying available quantity.
* **Parameters**:
| Parameter | C Type | Direction | Description | Valid Values |
|---|---|---|---|---|
| `partId` | `uint32_t` | Input | ID of spare part | Existing part ID (100 to 999) |
| `qty` | `uint32_t` | Input | Quantity to deduct | 1 to available stock |
* **Return type**: `Status_t`
* **Return values**: `STATUS_SUCCESS`, `ERR_PART_NOT_FOUND`, `ERR_INSUFFICIENT_STOCK`
* **Preconditions**: Spare part exists in inventory.
* **Postconditions**: Stock quantity reduced by `qty`.
* **Errors handled**: Prevents negative stock levels.

---

### 8.4 Function: `Billing_Calculate`
* **Module**: Billing Module
* **Prototype**: `Status_t Billing_Calculate(uint32_t jobId, float discountPercentage, Bill_t *outBill);`
* **Purpose**: Computes full bill breakdown including labour, parts total, GST, and discount.
* **Parameters**:
| Parameter | C Type | Direction | Description | Valid Values |
|---|---|---|---|---|
| `jobId` | `uint32_t` | Input | Target job card ID | Valid completed job ID |
| `discountPercentage` | `float` | Input | Percentage discount | 0.0f to 50.0f |
| `outBill` | `Bill_t*` | Output | Pointer to write calculated bill | Non-null output pointer |
* **Return type**: `Status_t`
* **Return values**: `STATUS_SUCCESS`, `ERR_JOB_NOT_FOUND`, `ERR_INVALID_DISCOUNT`
* **Preconditions**: Target job card exists and is completed.
* **Postconditions**: `outBill` populated with breakdown details.
* **Errors handled**: Rejects discount percentages outside valid range ($0\text{--}50\%$).

---

## 9. Input-Validation Plan

| Input Field | Source | Validation Rule | Invalid Example | Expected Error Behaviour |
|---|---|---|---|---|
| Vehicle Reg Number | User / File | Standard Indian format: 2 letters, 2 digits, optional 2 letters, 4 digits | `"MH1234"` or `"1234MH"` | Returns `ERR_INVALID_INPUT`; asks user to re-enter |
| Job ID / Part ID | User / File | Positive unsigned integer; must be unique | `-100` or duplicate ID | Returns `ERR_DUPLICATE_ID` or `ERR_INVALID_INPUT` |
| Quantity / Price | User / File | Non-negative numeric values | `"-5"` or `"abc"` | Returns `ERR_INVALID_INPUT` |
| Workflow Status | User | Sequential transition ($\text{Open} \rightarrow \text{In Progress} \rightarrow \text{Completed} \rightarrow \text{Billed}$) | Open directly to Billed | Returns `ERR_INVALID_STATUS_TRANSITION` |
| Discount Percentage | User | Floating point value between $0.0\%$ and $50.0\%$ | `65.0` or `-10.0` | Returns `ERR_INVALID_DISCOUNT` |

### Common Validation Strategy
All menu inputs are read using safe buffer-bounded string inputs (`fgets`), stripped of trailing newlines, and parsed using strict validation utilities (`Utils_ParseUInt`, `Utils_ParseFloat`, `Utils_ValidateVehReg`). No unvalidated direct console scans (`scanf`) are used.

---

## 10. File-Handling Design

### 10.1 File Summary

| File | Purpose | Format | Created By | Read By | Updated By |
|---|---|---|---|---|---|
| `data/jobs.txt` | Persistent job card records | Text (CSV) | System | System | System |
| `data/parts.txt` | Persistent spare parts inventory | Text (CSV) | System | System | System |
| `data/invoice_*.txt` | Exported bill summary | Text | System | User | System |

### 10.2 Record Format

`data/parts.txt` record schema:
`PartID,Name,Quantity,UnitPrice,ReorderLevel`

`data/jobs.txt` record schema:
`JobID,VehicleReg,OwnerName,Complaint,ServiceType,Status`

### 10.3 File Operations

| Operation | Function or Module | C Library Function | Failure Handling |
|---|---|---|---|
| Open/Create | `file_io.c` | `fopen` | Checks NULL pointer; returns `ERR_FILE_OPEN_FAILED`. |
| Read | `file_io.c` | `fgets`, `sscanf` | Skips corrupt/empty lines; returns `ERR_FILE_READ_FAILED` if unreadable. |
| Write | `file_io.c` | `fprintf` | Returns `ERR_FILE_WRITE_FAILED` if write fails. |
| Close | `file_io.c` | `fclose` | Ensures file resource closed safely. |

---

## 11. Error-Handling Strategy

### 11.1 Status Representation

System operations return a strongly-typed `Status_t` enumeration representing outcome status cleanly without calling abrupt exit routines:

```c
typedef enum {
    STATUS_SUCCESS = 0,
    ERR_INVALID_INPUT,
    ERR_DUPLICATE_ID,
    ERR_JOB_NOT_FOUND,
    ERR_PART_NOT_FOUND,
    ERR_INSUFFICIENT_STOCK,
    ERR_INVALID_STATUS_TRANSITION,
    ERR_STORAGE_FULL,
    ERR_MAX_PARTS_EXCEEDED,
    ERR_INVALID_DISCOUNT,
    ERR_FILE_OPEN_FAILED,
    ERR_FILE_READ_FAILED,
    ERR_FILE_WRITE_FAILED
} Status_t;
```

### 11.2 Error Recovery Strategy
When invalid input or file operation errors occur, the system converts the status code into a human-readable text string using `Utils_ErrorToString()`, presents it to the user, and safely returns execution back to the main interactive menu loop without crashing.

---

## 12. Coding Standards Plan

### 12.1 Naming Conventions

* **Source/Header files**: `lowercase_with_underscores.c` (e.g., `job_card.c`, `job_card.h`)
* **Functions**: `PascalCase_CamelCase` (e.g., `JobCard_Create`, `SpareParts_DeductStock`)
* **Local variables & members**: `camelCase` (e.g., `jobId`, `partCount`)
* **Structures & Enums**: `PascalCase_t` (e.g., `JobCard_t`, `Status_t`)
* **Constants & Enum values**: `UPPER_SNAKE_CASE` (e.g., `MAX_JOBS`, `STATUS_OPEN`)

### 12.2 Formatting Rules

* **Indentation**: 4 spaces, no tabs.
* **Brace Style**: All open and close braces on their own separate lines.
* **Compiler Warning Flags**: `-Wall -Wextra -Wpedantic -std=c11` (C) and `-std=c++17` (C++ tests).
* **Line Length Limit**: Maximum 100 characters per line.

---

## 13. Application Flow

### 13.1 Main Application Flow

```
   [ Application Start ]
             |
             v
 [ Load Parts & Jobs Files ]
             |
             v
   +---> [ Display Menu ]
   |         |
   |         v
   |   [ Get User Choice ]
   |         |
   |         +---> (Choice 1-7) ---> [ Execute Operation & Validate ] --+
   |         |                                                           |
   |         +---> (Choice 8)   ---> [ Save State to Disk ] ------------+
   |         |                                                           |
   +---------+---> (Choice 0)   ---> [ Save State & Exit Program ]
```

---

## 14. Unit-Test Plan

### 14.1 Test Cases

| Test ID | Module | Function | Category | Scenario / Input | Expected Result | Requirement ID |
|---|---|---|---|---|---|---|
| UT-01 | `utils` | `Utils_ValidateVehReg` | Positive | `"MH12AB1234"` | Returns `true` | FR-02 |
| UT-02 | `utils` | `Utils_ValidateVehReg` | Negative | `"INVALID"` | Returns `false` | FR-02 |
| UT-03 | `utils` | `Utils_ParseUInt` | Boundary | `"100"` vs `"-5"` | Returns `true` for 100; `false` for negative | FR-16 |
| UT-04 | `spare_parts` | `SpareParts_Add` | Positive | Valid part struct | Returns `STATUS_SUCCESS` | FR-05 |
| UT-05 | `spare_parts` | `SpareParts_Add` | Negative | Duplicate part ID | Returns `ERR_DUPLICATE_ID` | FR-03 |
| UT-06 | `spare_parts` | `SpareParts_DeductStock` | Boundary/Negative | Deduct 10 from stock 5 | Returns `ERR_INSUFFICIENT_STOCK` | FR-09 |
| UT-07 | `spare_parts` | `SpareParts_GetLowStock` | Positive | Query parts $\le$ reorder limit | Low stock list populated accurately | FR-13 |
| UT-08 | `job_card` | `JobCard_Create` | Positive | Valid job card struct | Returns `STATUS_SUCCESS` | FR-01 |
| UT-09 | `job_card` | `JobCard_UpdateStatus` | Negative | Open directly to Billed | Returns `ERR_INVALID_STATUS_TRANSITION` | FR-10 |
| UT-10 | `billing` | `Billing_Calculate` | Positive | Standard completed job | Calculates labour, tax, total accurately | FR-11 |
| UT-11 | `billing` | `Billing_Calculate` | Boundary | Discount = $60.0\%$ | Returns `ERR_INVALID_DISCOUNT` | FR-11 |

### 14.2 Test Command
```bash
make test
```