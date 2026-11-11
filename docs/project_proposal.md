# Vehicle Service Center Job Card and Spare Parts Tracker — Project Proposal

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

Student acknowledgement: Shreehari Fating

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

Problems with the current method:
- Job cards are lost or damaged, and old records are hard to find.
- Parts used on a job are not always deducted from stock, so the stock count is wrong.
- Low-stock parts are noticed only after they run out.
- Manual bill calculation leads to arithmetic mistakes and missed charges.
- There is no quick way to see which jobs are still pending.

### 2.2 Problem Statement
In small vehicle service centers, service advisors and parts keepers currently face difficulty in keeping track of job cards, spare parts usage, and stock levels. The current paper-based method results in lost records, incorrect stock counts, delayed reordering of parts, and billing errors. The proposed software will provide job card creation, job status tracking, spare parts stock management, automatic bill calculation, and low-stock reporting so that users can handle vehicle service jobs accurately, keep correct stock records, and generate bills quickly.

### 2.3 Proposed Solution
The proposed solution is a modular command-line application written in C.
It will:
- Create and store job cards for incoming vehicles.
- Maintain a stock record of spare parts and let the user add, update, and search parts.
- Record the parts used on a job and automatically reduce the stock.
- Reject a part request when the stock is insufficient.
- Move each job through a status workflow ($\text{Open} \rightarrow \text{In Progress} \rightarrow \text{Completed} \rightarrow \text{Billed}$).
- Calculate the final bill from the labour charge for the service type, the total parts cost, GST, and any discount.
- Generate reports: the bill for a job, the list of jobs by status, and the list of parts below their reorder level.

Job and parts data will be stored in files so that records remain available after the program is closed. All inputs will be validated, and errors will be reported without crashing the program.

### 2.4 Target Users
| User Type | Responsibility | How the User Will Use the Application |
|---|---|---|
| Service Advisor | Receives vehicles and prepares bills | Creates job cards, searches jobs, generates the final bill |
| Mechanic | Carries out the service work | Records parts used on a job and updates the job status |
| Parts Keeper | Manages the spare parts store | Adds or updates parts, checks stock and the low-stock report |
| Workshop Manager | Oversees the workshop | Views pending jobs and the low-stock report |

---

## 3. Project Scope

### 3.1 In-Scope Features
1. Create, store, and search job cards (vehicle registration number, owner, complaint, service type).
2. Add, update, and search spare parts in the stock record.
3. Record spare parts used on a job and automatically deduct them from stock.
4. Track the job status through the workflow: $\text{Open} \rightarrow \text{In Progress} \rightarrow \text{Completed} \rightarrow \text{Billed}$.
5. Calculate the final bill (labour charge, parts cost, GST, and discount).
6. Generate reports: job bill, jobs filtered by status, and low-stock parts.
7. Validate all user input and file data without crashing.
8. Save and load job and parts data using persistent plain text files.

### 3.2 Out-of-Scope Features
1. Graphical user interface (command-line interface only).
2. Multi-user login, passwords, or role-based access control.
3. Online payment, invoice printing, or SMS/email notifications.
4. Appointment booking and mechanic scheduling.
5. Database integration or networking.
6. Automatic purchase orders to suppliers (only a low-stock report is produced).

### 3.3 Assumptions
1. The application is used by one person at a time on one computer.
2. Each job card belongs to exactly one vehicle, and each vehicle visit creates a new job card.
3. Job IDs and part IDs are unique integers assigned by the user or the system.
4. Labour charges are fixed per service type (`Periodic`, `Repair`, `Accident`) and stored as constants.
5. GST is a fixed percentage ($18\%$) stored as a constant.
6. All prices are in Indian Rupees (INR) and quantities are whole numbers.
7. Vehicle registration numbers follow a standard Indian format (for example, `MH12AB1234`).

### 3.4 Constraints
1. The application uses a command-line interface only.
2. Data is stored in plain text files; no external database engine is used.
3. The maximum number of job cards is fixed (100) and the maximum number of spare parts is fixed (100).
4. A single job can use a limited number of different parts (maximum 10).
5. String fields have fixed maximum lengths (for example, owner name max 50 characters).
6. The project must be completed individually within the course duration, using only C, gTest, Make, and Git as taught in the course.

---

## 4. Requirements

### 4.1 Functional Requirements

| ID | Functional Requirement | Priority | Verification Method |
|---|---|---|---|
| FR-01 | The system shall create a new job card containing the job ID, vehicle registration number, owner name, complaint, and service type. | High | Demonstration / Test |
| FR-02 | The system shall validate the vehicle registration number format before accepting a job card. | High | Test |
| FR-03 | The system shall reject a job card or spare part whose ID already exists. | High | Test |
| FR-04 | The system shall search for a job card using its job ID. | High | Demonstration / Test |
| FR-05 | The system shall add a new spare part with its ID, name, quantity, unit price, and reorder level. | High | Demonstration / Test |
| FR-06 | The system shall search for a spare part using its part ID. | Medium | Demonstration / Test |
| FR-07 | The system shall increase the stock quantity of an existing spare part when new stock is received. | Medium | Demonstration / Test |
| FR-08 | The system shall record a spare part used on a job and reduce its stock by the quantity used. | High | Demonstration / Test |
| FR-09 | The system shall reject a part usage request when the available stock is less than the quantity requested. | High | Test |
| FR-10 | The system shall allow the job status to change only in the order $\text{Open} \rightarrow \text{In Progress} \rightarrow \text{Completed} \rightarrow \text{Billed}$. | High | Test |
| FR-11 | The system shall calculate the final bill as labour charge plus parts cost, plus GST, minus any applicable discount. | High | Test |
| FR-12 | The system shall display all jobs that have a selected status. | Medium | Demonstration / Test |
| FR-13 | The system shall generate a report of spare parts whose stock is at or below the reorder level. | Medium | Demonstration / Test |
| FR-14 | The system shall save all job and spare part records to files when data is changed or the application exits. | High | Demonstration |
| FR-15 | The system shall load existing records from files when the application starts. | High | Demonstration |
| FR-16 | The system shall display an error message and continue running when the user enters invalid input or an unsupported menu choice. | High | Negative testing |
| FR-17 | The system shall display the complete details of a selected job, including parts used and bill status. | Low | Demonstration |

### 4.2 Non-Functional Requirements

| ID | Non-Functional Requirement | Verification Method |
|---|---|---|
| NFR-01 | The source code shall compile without warnings using `-Wall -Wextra -Wpedantic`. | Build output |
| NFR-02 | The project shall use a modular multi-file structure with `main.c` limited to high-level control. | Code review |
| NFR-03 | The application shall handle invalid input and file errors without crashing. | Negative testing |
| NFR-04 | Important functions shall be tested using gTest, with at least 10 tests covering positive, negative, and boundary cases. | Unit-test output |
| NFR-05 | The project shall build using a Makefile that supports `all`, `run`, `test`, and `clean`. | Build demonstration |
| NFR-06 | The project shall be maintained in a GitHub repository with multiple meaningful commits. | Repository review |
| NFR-07 | The code shall use named constants instead of unexplained numeric values. | Code review |
| NFR-08 | Every file operation and function return status shall be checked. | Code review |
| NFR-09 | The README shall allow another developer to build, run, and test the project without extra instructions. | Repository review |

### 4.3 Requirement Traceability Matrix

| Requirement ID | Module | Function or Feature | Test ID |
|---|---|---|---|
| FR-01 | `job_card` | `JobCard_Create` | UT-08 |
| FR-02 | `utils` | `Utils_ValidateVehReg` | UT-01, UT-02 |
| FR-03 | `job_card` / `spare_parts` | `JobCard_Create` / `SpareParts_Add` | UT-05 |
| FR-04 | `job_card` | `JobCard_FindById` | UT-08 |
| FR-05 | `spare_parts` | `SpareParts_Add` | UT-04 |
| FR-06 | `spare_parts` | `SpareParts_FindById` | UT-04 |
| FR-07 | `spare_parts` | `SpareParts_AddStock` | UT-04 |
| FR-08 | `job_card` / `spare_parts` | `JobCard_AddPartUsage` / `SpareParts_DeductStock` | UT-06 |
| FR-09 | `spare_parts` | `SpareParts_DeductStock` | UT-06 |
| FR-10 | `job_card` | `JobCard_UpdateStatus` | UT-09 |
| FR-11 | `billing` | `Billing_Calculate` | UT-10, UT-11 |
| FR-12 | `job_card` | `JobCard_GetByStatus` | UT-09 |
| FR-13 | `spare_parts` | `SpareParts_GetLowStock` | UT-07 |
| FR-14 | `file_io` | `FileIO_SaveJobs` / `FileIO_SaveParts` | Manual / Demo |
| FR-15 | `file_io` | `FileIO_LoadJobs` / `FileIO_LoadParts` | Manual / Demo |
| FR-16 | `utils` / `main` | `Utils_ParseUInt` / CLI menu validation | UT-03 |
| FR-17 | `job_card` | CLI display details option | Manual / Demo |