# Vehicle Service Center Job Card and Spare Parts Tracker

## 1. Project Information

### 1.1 Project Title
Vehicle Service Center Job Card and Spare Parts Tracker

### 1.2 Engineering Domain
Automotive

### 1.3 Team Details
| Field | Details |
|---|---|
| Student name | Shreehari Fating |
| Roll number | 612509074 |
| Division / batch | Division 1 / Batch 1 |
| Repository name | Vehicle-Service-Center-Job-Card-and-Spare-Parts-Tracker |
| GitHub repository link | https://github.com/Shreehari060607/Vehicle-Service-Center-Job-Card-and-Spare-Parts-Tracker.git |

### 1.4 Individual Project Declaration
I confirm that this project is my individual work. I understand the design, source code, unit tests, Makefile and documentation included in this repository, and I am prepared to explain or modify any part during evaluation.

**Student acknowledgement:** Shreehari Fating

---

## 2. Engineering Scenario

### 2.1 Scenario Description
Small and medium vehicle service centers handle many vehicles every day. When a vehicle arrives, the service advisor records the owner's details, the vehicle registration number, and the customer's complaint. A mechanic then carries out the work and uses spare parts such as oil filters, brake pads, and spark plugs from the workshop's stock. After the work is done, the service advisor prepares the bill using labour charges and the cost of the parts used.

In many workshops, this is still done on paper job cards and notebooks.
The information that must be managed includes:
- Job details (job ID, vehicle registration number, owner, complaint, service type)
- Job status (open, in progress, completed, billed)
- Spare parts stock (part ID, name, quantity, unit price, reorder level)
- Parts consumed by each job
- Labour charges and the final bill

**Problems with the current method:**
- Job cards are lost or damaged, and old records are hard to find.
- Parts used on a job are not always deducted from stock, leading to incorrect stock counts.
- Low-stock parts are noticed only after they run out.
- Manual bill calculation leads to arithmetic mistakes and missed charges.
- There is no quick way to see which jobs are still pending.

### 2.2 Problem Statement
In small vehicle service centers, service advisors and parts keepers currently face difficulty in keeping track of job cards, spare parts usage, and stock levels. The current paper-based method results in lost records, incorrect stock counts, delayed reordering of parts, and billing errors. The proposed software will provide job card creation, job status tracking, spare parts stock management, automatic bill calculation, and low-stock reporting so that users can handle vehicle service jobs accurately, keep correct stock records, and generate bills quickly.

### 2.3 Proposed Solution
The proposed solution is a modular command-line application written in C. It will:
- Create and store job cards for incoming vehicles.
- Maintain a stock record of spare parts and allow users to add, update, and search parts.
- Record the parts used on a job and automatically reduce stock.
- Reject a part request when stock is insufficient.
- Move each job through a structured status workflow (`Open` $\rightarrow$ `In Progress` $\rightarrow$ `Completed` $\rightarrow$ `Billed`).
- Calculate the final bill from the labour charge for the service type, total parts cost, GST, and any applied discount.
- Generate reports: the bill for a job, the list of jobs by status, and the list of parts below their reorder level.

Job and parts data are stored in persistent text files so records remain available after exiting the program. All inputs are validated to handle errors without crashing.

### 2.4 Target Users
| User Type | Responsibility | How the User Will Use the Application |
|---|---|---|
| Service Advisor | Receives vehicles and prepares bills | Creates job cards, searches jobs, generates the final bill |
| Mechanic | Carries out the service work | Records parts used on a job and updates the job status |
| Parts Keeper | Manages the spare parts store | Adds or updates parts, checks stock and low-stock reports |
| Workshop Manager | Oversees the workshop | Views pending jobs and low-stock reports |

---

## 3. Project Scope

### 3.1 In-Scope Features
1. Create, store, and search job cards (vehicle registration number, owner, complaint, service type).
2. Add, update, and search spare parts in the stock record.
3. Record spare parts used on a job and automatically deduct them from stock.
4. Track job status through the workflow: `Open` $\rightarrow$ `In Progress` $\rightarrow$ `Completed` $\rightarrow$ `Billed`.
5. Calculate final bill (labour charge, parts cost, GST, and discount).
6. Generate reports: job bill, jobs filtered by status, and low-stock parts.
7. Validate all user input and file data without crashing.
8. Save and load job and parts data using files.

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
5. GST is a fixed percentage rate (18%) stored as a constant.
6. All prices are in Indian Rupees (INR) and stock quantities are whole numbers.
7. Vehicle registration numbers follow standard Indian format (e.g., `MH12AB1234`).

### 3.4 Constraints
1. Command-line interface only.
2. Data stored in plain text files; no external database engine.
3. Maximum job cards fixed at 100; maximum spare parts fixed at 100.
4. Maximum distinct spare parts per single job card fixed at 10.
5. Fixed maximum lengths for text fields (e.g., Owner Name max 50 chars).
6. Built using standard C, GoogleTest (gTest), Make, and Git.

---

## 4. Requirements

### 4.1 Functional Requirements
| ID | Functional Requirement | Priority | Verification Method |
|---|---|---|---|
| FR-01 | Create new job card containing job ID, registration number, owner, complaint, and service type. | High | Demonstration / Test |
| FR-02 | Validate vehicle registration number format before accepting a job card. | High | Test |
| FR-03 | Reject a job card or spare part whose ID already exists. | High | Test |
| FR-04 | Search for a job card using its unique job ID. | High | Demonstration / Test |
| FR-05 | Add a new spare part with ID, name, quantity, unit price, and reorder level. | High | Demonstration / Test |
| FR-06 | Search for a spare part using its part ID. | Medium | Demonstration / Test |
| FR-07 | Increase stock quantity of an existing spare part when new stock arrives. | Medium | Demonstration / Test |
| FR-08 | Record spare part used on a job and deduct stock accordingly. | High | Demonstration / Test |
| FR-09 | Reject part request when requested quantity exceeds available stock. | High | Test |
| FR-10 | Enforce workflow status transitions: Open $\rightarrow$ In Progress $\rightarrow$ Completed $\rightarrow$ Billed. | High | Test |
| FR-11 | Calculate bill as (Labour + Parts) + GST - Discount. | High | Test |
| FR-12 | Display all jobs filtered by selected status. | Medium | Demonstration / Test |
| FR-13 | Generate report for spare parts at or below reorder level. | Medium | Demonstration / Test |
| FR-14 | Save job and spare part records to text files when updated or on application exit. | High | Demonstration |
| FR-15 | Load existing records from files when application starts. | High | Demonstration |
| FR-16 | Display error message and remain running upon invalid menu input or invalid data. | High | Negative testing |
| FR-17 | Display complete details of selected job, including parts used and bill state. | Low | Demonstration |

### 4.2 Non-Functional Requirements
| ID | Non-Functional Requirement | Verification Method |
|---|---|---|
| NFR-01 | Source code compiles cleanly with flags `-Wall -Wextra -Wpedantic`. | Build output |
| NFR-02 | Uses a modular multi-file structure with `main.c` limited to menu control flow. | Code review |
| NFR-03 | Gracefully handles invalid user input and file read/write errors without crashing. | Negative testing |
| NFR-04 | Key business logic functions tested via GoogleTest (gTest) with $\ge 10$ test cases. | Unit-test output |
| NFR-05 | Automates tasks using Makefile targets `all`, `run`, `test`, and `clean`. | Build demonstration |
| NFR-06 | Maintained in GitHub repository with clear, descriptive commit messages. | Repository review |
| NFR-07 | Uses named constants instead of hardcoded magic numbers. | Code review |
| NFR-08 | Checks every file handling and function return status code. | Code review |
| NFR-09 | Provides standalone instructions enabling any user to build, run, and test. | Documentation review |

---

## 5. High-Level Architecture

### 5.1 Architecture Description
The project employs a 3-tier layered modular architecture:
1. **Presentation Layer (`main.c`)**: Directs application menu flow, processes user interactions, and presents output formatting.
2. **Business Logic Layer (`job_card.c`, `spare_parts.c`, `billing.c`)**: Implements workflow verification, stock allocation validation, and billing arithmetic.
3. **Data & Utility Layer (`file_io.c`, `utils.c`)**: Manages file storage routines, input parsing, and regex-style validation.

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

---

## 6. Module Design

### 6.1 Module Summary
| Module Name | Source File | Header File | Responsibility |
|---|---|---|---|
| Main Application | `main.c` | N/A | Controls top-level interaction menus and flow. |
| Job Card | `job_card.c` | `job_card.h` | Manages job card entities, lookup, and state flow. |
| Spare Parts | `spare_parts.c` | `spare_parts.h` | Manages part records, stock levels, and low-stock queries. |
| Billing | `billing.c` | `billing.h` | Computes labour rates, parts subtotal, tax, and final total. |
| File I/O | `file_io.c` | `file_io.h` | Reads and writes state persistent plain text records. |
| Utilities | `utils.c` | `utils.h` | Performs string sanitation, formatting checks, and type parsing. |

---

## 7. Data Design

### 7.1 Data Structures & Enums

```c
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

### 7.2 System Constants
| Constant Name | Value | Purpose |
|---|---|---|
| `MAX_JOBS` | `100` | Maximum job cards in system |
| `MAX_PARTS` | `100` | Maximum distinct spare parts in inventory |
| `MAX_PARTS_PER_JOB` | `10` | Maximum unique parts allowed per job card |
| `GST_RATE_PERCENT` | `18.0f` | Standard GST tax rate applied to bill |
| `LABOUR_PERIODIC` | `500.0f` | Base labour rate for periodic service |
| `LABOUR_REPAIR` | `1000.0f` | Base labour rate for repairs |
| `LABOUR_ACCIDENT` | `2500.0f` | Base labour rate for accident repairs |

---

## 8. Repository Structure

```text
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
│   ├── jobs.txt
│   └── parts.txt
├── docs/
│   └── project_proposal.md
├── Makefile
├── README.md
└── .gitignore
```

---

## 9. Build, Run, and Test Instructions

### Prerequisites
- **Compiler**: GCC / G++ (supporting C11 / C++14 or higher)
- **Build Tool**: GNU Make
- **Testing Framework**: GoogleTest (gTest)

### Execution Commands

1. **Build the Application**
   ```bash
   make all
   ```

2. **Run the Application**
   ```bash
   make run
   ```

3. **Build and Run Unit Tests**
   ```bash
   make test
   ```

4. **Clean Build Files**
   ```bash
   make clean
   ```

---

## 10. Sample Usage & Execution

### Sample Input (Adding Job Card)
```text
=== Job Card Creation ===
Enter Job ID: 1001
Enter Vehicle Registration (e.g., MH12AB1234): MH12PQ5678
Enter Owner Name: Rajesh Sharma
Enter Complaint: Engine oil replacement and brake inspection
Select Service Type (0: Periodic, 1: Repair, 2: Accident): 0
```

### Sample Output (Bill Generation)
```text
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
Discount        : INR     0.00
--------------------------------------------------
GRAND TOTAL     : INR  2006.00
==================================================
```

---

## 11. Known Limitations & Future Enhancements

### Known Limitations
1. Maximum capacity capped at 100 jobs and 100 spare parts in memory.
2. Command-line interface only; no graphical user interaction.
3. Multi-user concurrent access is not supported.

### Future Enhancements
1. Dynamic memory allocation to support unlimited job cards and parts records.
2. Development of a GUI front-end or Web UI.
3. PDF receipt generation and email/SMS notification integration.
