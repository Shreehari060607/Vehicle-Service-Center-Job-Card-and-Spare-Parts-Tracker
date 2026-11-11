# Vehicle Service Center Job Card and Spare Parts Tracker

## 1. Project Information

### 1.1 Project Title

Vehicle Service Center Job Card and Spare Parts Tracker

### 1.2 Engineering Domain

Automotive

### 1.3 Team Details

| Field | Details | 
| ----- | ----- | 
| Student name | Shreehari Fating | 
| Roll number | 612509074 | 
| Division / batch | Division 1 / Batch 1 | 
| Repository name | Vehicle-Service-Center-Job-Card-and-Spare-Parts-Tracker | 
| GitHub repository link | https://github.com/Shreehari060607/Vehicle-Service-Center-Job-Card-and-Spare-Parts-Tracker.git | 

### 1.4 Individual Project Declaration

I confirm that this project is my individual work. I understand the design, source code, unit tests, Makefile and documentation included in this repository, and I am prepared to explain or modify any part during evaluation.

Student acknowledgement: Shreehari Fating

## 2. Engineering Scenario

### 2.1 Scenario Description

Small and medium vehicle service centers handle many vehicles every day. When a vehicle arrives, the service advisor records the owner's details, the vehicle registration number, and the customer's complaint. A mechanic then carries out the work and uses spare parts such as oil filters, brake pads, and spark plugs from the workshop's stock. After the work is done, the service advisor prepares the bill using labour charges and the cost of the parts used.

In many workshops, this is still done on paper job cards and notebooks.
The information that must be managed includes:

* Job details (job ID, vehicle registration number, owner, complaint, service type)

* Job status (open, in progress, completed, billed)

* Spare parts stock (part ID, name, quantity, unit price, reorder level)

* Parts consumed by each job

* Labour charges and the final bill

**Problems with the current method:**

* Job cards are lost or damaged, and old records are hard to find.

* Parts used on a job are not always deducted from stock, so the stock count is wrong.

* Low-stock parts are noticed only after they run out.

* Manual bill calculation leads to arithmetic mistakes and missed charges.

* There is no quick way to see which jobs are still pending.

### 2.2 Problem Statement

In small vehicle service centers, service advisors and parts keepers currently face difficulty in keeping track of job cards, spare parts usage, and stock levels. The current paper-based method results in lost records, incorrect stock counts, delayed reordering of parts, and billing errors. The proposed software will provide job card creation, job status tracking, spare parts stock management, automatic bill calculation, and low-stock reporting so that users can handle vehicle service jobs accurately, keep correct stock records, and generate bills quickly.

### 2.3 Proposed Solution

The proposed solution is a modular command-line application written in C. It will:

* Create and store job cards for incoming vehicles.

* Maintain a stock record of spare parts and allow users to add, update, and search parts.

* Record the parts used on a job and automatically reduce stock.

* Reject a part request when stock is insufficient.

* Move each job through a structured status workflow ($\text{Open} \rightarrow \text{In Progress} \rightarrow \text{Completed} \rightarrow \text{Billed}$).

* Calculate the final bill from the labour charge for the service type, total parts cost, GST, and any applied discount.

* Generate reports: the bill for a job, the list of jobs by status, and the list of parts below their reorder level.

Job and parts data are stored in text files so records remain available after exiting the program. All inputs will be validated, and errors will be reported cleanly without crashing the program.

### 2.4 Target Users

| User Type | Responsibility | How the User Will Use the Application | 
| ----- | ----- | ----- | 
| Service Advisor | Receives vehicles and prepares bills | Creates job cards, searches jobs, generates final bills | 
| Mechanic | Carries out service work | Records parts used on a job and updates job status | 
| Parts Keeper | Manages spare parts store | Adds or updates parts, checks stock and low-stock reports | 
| Workshop Manager | Oversees the workshop | Views pending jobs and low-stock reports | 

## 3. Project Scope

### 3.1 In-Scope Features

1. Create, store, and search job cards (vehicle registration number, owner, complaint, service type).

2. Add, update, and search spare parts in the stock record.

3. Record spare parts used on a job and automatically deduct them from stock.

4. Track job status through the workflow: $\text{Open} \rightarrow \text{In Progress} \rightarrow \text{Completed} \rightarrow \text{Billed}$.

5. Calculate final bill (labour charge, parts cost, GST, and discount).

6. Generate reports: job bill, jobs filtered by status, and low-stock parts.

7. Validate all user input and file data without crashing.

8. Save and load job and parts data using persistent files.

### 3.2 Out-of-Scope Features

1. Graphical user interface (command-line interface only).

2. Multi-user login, passwords, or role-based access control.

3. Online payment, invoice printing, or SMS/email notifications.

4. Appointment booking and mechanic scheduling.

5. Database integration or networking.

6. Automatic purchase orders to suppliers (only low-stock report is produced).

### 3.3 Assumptions

1. Single-user execution on one computer at a time.

2. Each job card belongs to exactly one vehicle; each visit generates a new job card.

3. Job IDs and part IDs are unique integers assigned by system or user.

4. Labour charges are fixed per service type (`Periodic`, `Repair`, `Accident`) and stored as constants.

5. GST is a fixed percentage rate ($18\%$) stored as a constant.

6. All prices are in Indian Rupees (INR) and stock quantities are whole numbers.

7. Vehicle registration numbers follow standard Indian format (e.g., `MH12AB1234`).

### 3.4 Constraints

1. Command-line interface only.

2. Data stored in plain text files; no external database engine.

3. Maximum job cards fixed at 100; maximum spare parts fixed at 100.

4. Maximum distinct spare parts per single job card fixed at 10.

5. Fixed maximum lengths for text fields (e.g., Owner Name max 50 chars).

6. Built using standard C, GoogleTest (gTest), Make, and Git.

## 4. Requirements

### 4.1 Functional Requirements

| ID | Functional Requirement | Priority | Verification Method | 
| ----- | ----- | ----- | ----- | 
| FR-01 | Create new job card containing job ID, registration number, owner, complaint, and service type. | High | Demonstration / Test | 
| FR-02 | Validate vehicle registration number format before accepting a job card. | High | Test | 
| FR-03 | Reject a job card or spare part whose ID already exists. | High | Test | 
| FR-04 | Search for a job card using its unique job ID. | High | Demonstration / Test | 
| FR-05 | Add a new spare part with ID, name, quantity, unit price, and reorder level. | High | Demonstration / Test | 
| FR-06 | Search for a spare part using its part ID. | Medium | Demonstration / Test | 
| FR-07 | Increase stock quantity of an existing spare part when new stock arrives. | Medium | Demonstration / Test | 
| FR-08 | Record spare part used on a job and deduct stock accordingly. | High | Demonstration / Test | 
| FR-09 | Reject part request when requested quantity exceeds available stock. | High | Test | 
| FR-10 | Enforce workflow status transitions: $\text{Open} \rightarrow \text{In Progress} \rightarrow \text{Completed} \rightarrow \text{Billed}$. | High | Test | 
| FR-11 | Calculate bill as $(\text{Labour} + \text{Parts}) + \text{GST} - \text{Discount}$. | High | Test | 
| FR-12 | Display all jobs filtered by selected status. | Medium | Demonstration / Test | 
| FR-13 | Generate report for spare parts at or below reorder level. | Medium | Demonstration / Test | 
| FR-14 | Save job and spare part records to text files when updated or on application exit. | High | Demonstration | 
| FR-15 | Load existing records from files when application starts. | High | Demonstration | 
| FR-16 | Display error message and remain running upon invalid menu input or invalid data. | High | Negative testing | 
| FR-17 | Display complete details of selected job, including parts used and bill state. | Low | Demonstration | 

### 4.2 Non-Functional Requirements

| ID | Non-Functional Requirement | Verification Method | 
| ----- | ----- | ----- | 
| NFR-01 | Source code compiles cleanly with flags `-Wall -Wextra -Wpedantic`. | Build output | 
| NFR-02 | Uses a modular multi-file structure with `main.c` limited to menu control flow. | Code review | 
| NFR-03 | Gracefully handles invalid user input and file read/write errors without crashing. | Negative testing | 
| NFR-04 | Key business logic functions tested via GoogleTest (gTest) with $\ge 10$ test cases. | Unit-test output | 
| NFR-05 | Automates tasks using Makefile targets `all`, `run`, `test`, and `clean`. | Build demonstration | 
| NFR-06 | Maintained in GitHub repository with clear, descriptive commit messages. | Repository review | 
| NFR-07 | Uses named constants instead of hardcoded magic numbers. | Code review | 
| NFR-08 | Checks every file handling and function return status code. | Code review | 
| NFR-09 | Provides standalone instructions enabling any user to build, run, and test. | Documentation review | 

## 5. High-Level Architecture

### 5.1 Architecture Description

The project employs a 3-tier layered modular architecture:

1. **Presentation Layer (`main.c`)**: Directs application menu flow, processes user interactions, and presents output formatting.

2. **Business Logic Layer (`job_card.c`, `spare_parts.c`, `billing.c`)**: Implements workflow verification, stock allocation validation, and billing arithmetic.

3. **Data & Utility Layer (`file_io.c`, `utils.c`)**: Manages file storage routines, input parsing, and validation rules.

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

## 6. Module Design

### 6.1 Module Summary

| Module Name | Source File | Header File | Responsibility | 
| ----- | ----- | ----- | ----- | 
| Main Application | `src/main.c` | N/A | Controls top-level interaction menus and high-level flow. | 
| Job Card | `src/job_card.c` | `include/job_card.h` | Manages job card entities, lookup, and state flow. | 
| Spare Parts | `src/spare_parts.c` | `include/spare_parts.h` | Manages part records, stock levels, and low-stock queries. | 
| Billing | `src/billing.c` | `include/billing.h` | Computes labour rates, parts subtotal, tax, and final total. | 
| File I/O | `src/file_io.c` | `include/file_io.h` | Reads and writes persistent plain text records. | 
| Utilities | `src/utils.c` | `include/utils.h` | Performs string sanitation, formatting checks, and type parsing. | 

## 7. Data Design & C Concepts Used

### 7.1 C Concepts Used

| Concept | Location / Implementation | Description & Usage | 
| ----- | ----- | ----- | 
| **Structures & Nested Structs** | `job_card.h`, `spare_parts.h`, `billing.h` | `JobCard_t`, `SparePart_t`, `Bill_t`, and nested `UsedPart_t` to encapsulate domain entities. | 
| **Enumerations** | `job_card.h`, `billing.h` | `JobStatus_t` (Open, In Progress, Completed, Billed) and `ServiceType_t` for strong state typing. | 
| **Multi-File Modular Design** | `src/` & `include/` | Clean separation of concerns with header guards (`#ifndef ...`) across 6 distinct modules. | 
| **File I/O Operations** | `src/file_io.c` | Defensive file handling (`fopen`, `fgets`, `fprintf`, `fclose`) checking return status on all calls. | 
| **String & Memory Handling** | `src/utils.c`, `src/job_card.c` | Bounds-checked string handling (`strncpy`), trimming newline characters, and format verification. | 
| **Defensive Pointers** | All function prototypes | Strict NULL-pointer checks and output return parameters for error-safe execution. | 
| **Static Functions** | `src/utils.c`, `src/file_io.c` | Local private helper functions scoped using the `static` keyword. | 

### 7.2 Core Data Structures

```
typedef enum {
    STATUS_OPEN = 0,
    STATUS_IN_PROGRESS,
    STATUS_COMPLETED,
    STATUS_BILLED
} JobStatus_t;

typedef enum {
    SERVICE_PERIODIC = 0,
    SERVICE_REPAIR,
    SERVICE_ACCIDENT
} ServiceType_t;

typedef struct {
    uint32_t partId;
    uint32_t quantity;
    float unitPrice;
} UsedPart_t;

typedef struct {
    uint32_t jobId;
    char vehicleReg[16];
    char ownerName[50];
    char complaint[100];
    ServiceType_t serviceType;
    JobStatus_t status;
    UsedPart_t usedParts[10];
    uint32_t usedPartCount;
} JobCard_t;

typedef struct {
    uint32_t partId;
    char name[50];
    uint32_t quantity;
    float unitPrice;
    uint32_t reorderLevel;
} SparePart_t;

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

### 7.3 System Constants

| Constant Name | Value | Purpose | 
| ----- | ----- | ----- | 
| `MAX_JOBS` | `100` | Maximum job cards capacity in memory | 
| `MAX_PARTS` | `100` | Maximum distinct spare parts in inventory | 
| `MAX_PARTS_PER_JOB` | `10` | Maximum unique parts allowed per job card | 
| `GST_RATE_PERCENT` | `18.0f` | Standard GST tax rate applied to bill | 
| `LABOUR_PERIODIC` | `500.0f` | Base labour rate for periodic service | 
| `LABOUR_REPAIR` | `1000.0f` | Base labour rate for repairs | 
| `LABOUR_ACCIDENT` | `2500.0f` | Base labour rate for accident repairs | 

## 8. Coding Standards

* **Naming Conventions**:

  * Source & Header files: `lowercase_with_underscores.c`

  * Functions: `PascalCase_CamelCase` (e.g., `JobCard_Create`, `Utils_ValidateVehReg`)

  * Types/Structs/Enums: `PascalCase_t` (e.g., `JobCard_t`, `Status_t`)

  * Constants & Enum Values: `UPPER_SNAKE_CASE` (e.g., `MAX_JOBS`, `STATUS_OPEN`)

* **Formatting**: Indentation of 4 spaces (no tabs). Each brace on its own line. Standard width within \~100 characters.

* **Compiler Warning Flags**: Strict zero-warning compilation under `-Wall -Wextra -Wpedantic -std=c11`.

* **Prohibited Practices**: No global variables, no `gets()` or unsafe `scanf()`, no unvalidated string buffer copies, no unchecked file pointers.

## 9. Error-Handling Strategy & Status Catalogue

All core functions return a strongly-typed status indicator (`Status_t`) and never call exit directly.

| Status Code | Meaning | System & User Handling | 
| ----- | ----- | ----- | 
| `STATUS_SUCCESS` | Operation completed without error. | Execution proceeds; success confirmation shown. | 
| `ERR_INVALID_INPUT` | Input string/number failed formatting or range validation. | Prompt rejected; user asked to re-enter value. | 
| `ERR_DUPLICATE_ID` | Attempted to create a Job ID or Part ID that already exists. | Operation cancelled; duplicate warning shown. | 
| `ERR_JOB_NOT_FOUND` | Requested Job ID does not exist in records. | Action aborted with explicit error message. | 
| `ERR_PART_NOT_FOUND` | Requested Part ID does not exist in inventory. | Action aborted with explicit error message. | 
| `ERR_INSUFFICIENT_STOCK` | Stock quantity is lower than requested usage quantity. | Stock deduction blocked; current stock count shown. | 
| `ERR_INVALID_STATUS_TRANSITION` | Out-of-order workflow status update attempted. | State change blocked; valid sequence enforced. | 
| `ERR_STORAGE_FULL` | Record capacity (100 jobs or 100 parts) reached. | Rejects addition; alerts user capacity reached. | 
| `ERR_FILE_OPEN_FAILED` | Data file could not be created or opened. | Warns user and defaults to clean empty session. | 

## 10. Repository Structure

```
Vehicle-Service-Center-Job-Card-and-Spare-Parts-Tracker/
├── include/
│   ├── billing.h
│   ├── file_io.h
│   ├── job_card.h
│   ├── spare_parts.h
│   └── utils.h
├── src/
│   ├── billing.c
│   ├── file_io.c
│   ├── job_card.c
│   ├── main.c
│   ├── spare_parts.c
│   └── utils.c
├── tests/
│   └── test_main.cpp
├── data/
│   ├── sample_jobs.txt
│   ├── sample_parts.txt
│   ├── jobs.txt
│   └── parts.txt
├── docs/
│   └── project_proposal.md
├── Makefile
├── README.md
├── LICENSE
└── .gitignore

```

## 11. Prerequisites & Quick Start

### Toolchain Prerequisites

* **C Compiler**: GCC supporting C11 (`-std=c11`)

* **C++ Compiler**: G++ supporting C++17 (`-std=c++17` for Google Test runner)

* **Build Tool**: GNU Make

* **Unit Testing Framework**: Google Test (`libgtest-dev`)

#### Installation Commands

**Linux (Ubuntu / Debian):**

```
sudo apt update
sudo apt install build-essential libgtest-dev cmake

```

**Windows (MSYS2 UCRT64):**
Install [MSYS2](https://www.msys2.org/), open **MSYS2 UCRT64 Terminal**, and run:

```
pacman -Syu
pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain mingw-w64-ucrt-x86_64-gtest

```

### Quick Start Commands

```
# 1. Clone repository
git clone https://github.com/Shreehari060607/Vehicle-Service-Center-Job-Card-and-Spare-Parts-Tracker.git
cd Vehicle-Service-Center-Job-Card-and-Spare-Parts-Tracker

# 2. Build project
make all

# 3. Run application
make run

# 4. Run unit tests
make test

```

### Makefile Targets

| Target | Command | Action | 
| ----- | ----- | ----- | 
| `all` | `make all` | Compiles source files and links main executable into `build/`. | 
| `run` | `make run` | Builds executable (if needed) and starts the CLI application. | 
| `test` | `make test` | Builds and executes Google Test unit testing suite. | 
| `clean` | `make clean` | Removes compiled binaries, object files, and build artifacts. | 

## 12. Sample Input, Persistence & Output

### Raw Data Persistence Formats

`data/parts.txt` (Part ID, Name, Stock Quantity, Unit Price, Reorder Level):

```
101,Oil Filter,25,350.00,5
102,Brake Pads,12,1200.00,4
103,Spark Plug,40,150.00,10
104,Engine Oil 4L,8,2100.00,3

```

`data/jobs.txt` (Job ID, Vehicle Reg, Owner Name, Complaint, Service Type, Status):

```
1001,MH12AB1234,Rahul Sharma,Engine oil change and periodic maintenance,0,0
1002,MH14CD5678,Priya Patel,Brake noise during hard braking,1,1

```

### Sample Interactive Session

```
=== Vehicle Service Center Tracker ===
1. Create Job Card
2. Search / Display Job Card
3. Update Job Status
4. Manage Spare Parts Stock
5. Record Parts Used on Job
6. Calculate Job Bill
7. View Low Stock Report
8. Save Data
0. Save and Exit
Enter Choice: 1

=== Create Job Card ===
Enter Job ID (1000-9999): 1001
Enter Vehicle Registration (e.g., MH12AB1234): MH12PQ5678
Enter Owner Name: Rajesh Sharma
Enter Complaint: Engine oil replacement and brake inspection
Select Service Type (0: Periodic, 1: Repair, 2: Accident): 0
Job Card 1001 created successfully!

Enter Choice: 6
Enter Job ID to Bill: 1001

==================================================
              VEHICLE SERVICE BILL                
==================================================
Job ID          : 1001
Vehicle Reg     : MH12PQ5678
Owner Name      : Rajesh Sharma
Service Type    : Periodic Service
--------------------------------------------------
Labour Charge   : INR  500.00
Parts Cost      : INR  1200.00
--------------------------------------------------
Subtotal        : INR  1700.00
GST (18%)       : INR   306.00
Discount (0%)   : INR     0.00
--------------------------------------------------
GRAND TOTAL     : INR  2006.00
==================================================

```

## 13. Unit Testing Summary

Google Test is utilized to execute unit tests covering business logic functions across positive, negative, and boundary scenarios.

| Test ID | Module | Scenario / Function | Category | Expected Result | 
| ----- | ----- | ----- | ----- | ----- | 
| UT-01 | `job_card` | `JobCard_Create` with valid data | Positive | Returns `STATUS_SUCCESS` | 
| UT-02 | `job_card` | `JobCard_Create` with invalid vehicle reg | Negative | Returns `ERR_INVALID_INPUT` | 
| UT-03 | `job_card` | `JobCard_Create` up to maximum limit | Boundary | Returns `ERR_STORAGE_FULL` at 101 | 
| UT-04 | `job_card` | `JobCard_UpdateStatus` valid sequence | Positive | Status moves Open $\rightarrow$ In Progress | 
| UT-05 | `job_card` | `JobCard_UpdateStatus` illegal skip transition | Negative | Returns `ERR_INVALID_STATUS_TRANSITION` | 
| UT-06 | `spare_parts` | `SpareParts_DeductStock` sufficient quantity | Positive | Stock count decreases accurately | 
| UT-07 | `spare_parts` | `SpareParts_DeductStock` exceeding stock | Negative | Returns `ERR_INSUFFICIENT_STOCK` | 
| UT-08 | `billing` | `Billing_Calculate` standard bill calculation | Positive | Grand total calculated correctly | 
| UT-09 | `billing` | `Billing_Calculate` invalid discount percentage | Negative | Returns `ERR_INVALID_DISCOUNT` | 
| UT-10 | `utils` | `Utils_ValidateVehReg` format checks | Boundary | Validates `"MH12AB1234"` vs invalid strings | 

## 14. Known Limitations & Future Enhancements

### Known Limitations

1. Maximum capacity is fixed at 100 job cards and 100 spare parts in memory.

2. Command-line interface only; no graphical user interface.

3. Plain text file storage lacks atomic transactional writes.

4. Single-user execution without network access or role-based access control.

### Future Enhancements

1. Dynamic memory allocation (`malloc`/`free`) to support unlimited records.

2. Development of a GUI front-end or Web interface using modern frameworks.

3. PDF receipt generation and SMS/Email notification integration.

4. Database integration (SQLite/PostgreSQL) for persistent data integrity.
