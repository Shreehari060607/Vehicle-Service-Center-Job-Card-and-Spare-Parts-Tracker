#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "job_card.h"
#include "spare_parts.h"
#include "billing.h"
#include "file_io.h"
#include "utils.h"

static void PrintMenu(void) {
    printf("\n==================================================\n");
    printf("   Vehicle Service Center & Spare Parts System    \n");
    printf("==================================================\n");
    printf("1. Create New Job Card\n");
    printf("2. View Job Card Details\n");
    printf("3. Advance Job Status\n");
    printf("4. Add Spare Part to Inventory\n");
    printf("5. Record Part Usage on Job\n");
    printf("6. Generate Job Bill\n");
    printf("7. Display Low-Stock Parts Report\n");
    printf("8. Save Data\n");
    printf("0. Save and Exit\n");
    printf("--------------------------------------------------\n");
    printf("Enter choice: ");
}

int main(void) {
    SpareParts_Init();
    JobCard_Init();

    // Load initial data files if present
    SparePart_t initialParts[MAX_PARTS];
    uint32_t partCount = 0;
    if (FileIO_LoadParts("data/parts.txt", initialParts, &partCount) == STATUS_SUCCESS) {
        for (uint32_t i = 0; i < partCount; i++) {
            SpareParts_Add(&initialParts[i]);
        }
    }

    JobCard_t initialJobs[MAX_JOBS];
    uint32_t jobCount = 0;
    if (FileIO_LoadJobs("data/jobs.txt", initialJobs, &jobCount) == STATUS_SUCCESS) {
        for (uint32_t i = 0; i < jobCount; i++) {
            JobCard_Create(&initialJobs[i]);
        }
    }

    int choice = -1;
    char buffer[128];

    while (choice != 0) {
        PrintMenu();
        if (!fgets(buffer, sizeof(buffer), stdin)) break;
        if (sscanf(buffer, "%d", &choice) != 1) {
            printf("[ERROR] Invalid choice. Please enter a number.\n");
            continue;
        }

        switch (choice) {
            case 1: {
                JobCard_t job;
                printf("Enter Job ID: ");
                fgets(buffer, sizeof(buffer), stdin);
                Utils_ParseUInt(buffer, &job.jobId);

                printf("Enter Vehicle Reg (e.g., MH12AB1234): ");
                fgets(buffer, sizeof(buffer), stdin);
                Utils_TrimNewline(buffer);
                strncpy(job.vehicleReg, buffer, MAX_REG_LEN);

                printf("Enter Owner Name: ");
                fgets(buffer, sizeof(buffer), stdin);
                Utils_TrimNewline(buffer);
                strncpy(job.ownerName, buffer, MAX_NAME_LEN);

                printf("Enter Complaint: ");
                fgets(buffer, sizeof(buffer), stdin);
                Utils_TrimNewline(buffer);
                strncpy(job.complaint, buffer, MAX_DESC_LEN);

                printf("Select Service Type (0: Periodic, 1: Repair, 2: Accident): ");
                fgets(buffer, sizeof(buffer), stdin);
                int st = 0;
                sscanf(buffer, "%d", &st);
                job.serviceType = (ServiceType_t)st;

                Status_t res = JobCard_Create(&job);
                if (res == STATUS_SUCCESS) {
                    printf("[SUCCESS] Job card created successfully.\n");
                } else {
                    printf("[ERROR] %s\n", Utils_ErrorToString(res));
                }
                break;
            }
            case 2: {
                uint32_t jid = 0;
                printf("Enter Job ID: ");
                fgets(buffer, sizeof(buffer), stdin);
                Utils_ParseUInt(buffer, &jid);

                JobCard_t job;
                Status_t res = JobCard_FindById(jid, &job);
                if (res == STATUS_SUCCESS) {
                    printf("\nJob ID: %u | Reg: %s | Owner: %s\n", job.jobId, job.vehicleReg, job.ownerName);
                    printf("Status: %s | Service: %s\n", Utils_StatusToString(job.status), Utils_ServiceTypeToString(job.serviceType));
                    printf("Complaint: %s\n", job.complaint);
                } else {
                    printf("[ERROR] %s\n", Utils_ErrorToString(res));
                }
                break;
            }
            case 3: {
                uint32_t jid = 0;
                int nstat = 0;
                printf("Enter Job ID: ");
                fgets(buffer, sizeof(buffer), stdin);
                Utils_ParseUInt(buffer, &jid);
                printf("Enter New Status (1: In Progress, 2: Completed, 3: Billed): ");
                fgets(buffer, sizeof(buffer), stdin);
                sscanf(buffer, "%d", &nstat);

                Status_t res = JobCard_UpdateStatus(jid, (JobStatus_t)nstat);
                if (res == STATUS_SUCCESS) {
                    printf("[SUCCESS] Job status updated successfully.\n");
                } else {
                    printf("[ERROR] %s\n", Utils_ErrorToString(res));
                }
                break;
            }
            case 4: {
                SparePart_t p;
                printf("Enter Part ID: ");
                fgets(buffer, sizeof(buffer), stdin);
                Utils_ParseUInt(buffer, &p.partId);

                printf("Enter Part Name: ");
                fgets(buffer, sizeof(buffer), stdin);
                Utils_TrimNewline(buffer);
                strncpy(p.name, buffer, MAX_NAME_LEN);

                printf("Enter Quantity: ");
                fgets(buffer, sizeof(buffer), stdin);
                Utils_ParseUInt(buffer, &p.quantity);

                printf("Enter Unit Price (INR): ");
                fgets(buffer, sizeof(buffer), stdin);
                Utils_ParseFloat(buffer, &p.unitPrice);

                printf("Enter Reorder Level: ");
                fgets(buffer, sizeof(buffer), stdin);
                Utils_ParseUInt(buffer, &p.reorderLevel);

                Status_t res = SpareParts_Add(&p);
                if (res == STATUS_SUCCESS) {
                    printf("[SUCCESS] Spare part added to stock.\n");
                } else {
                    printf("[ERROR] %s\n", Utils_ErrorToString(res));
                }
                break;
            }
            case 5: {
                uint32_t jid = 0, pid = 0, qty = 0;
                printf("Enter Job ID: ");
                fgets(buffer, sizeof(buffer), stdin);
                Utils_ParseUInt(buffer, &jid);

                printf("Enter Part ID: ");
                fgets(buffer, sizeof(buffer), stdin);
                Utils_ParseUInt(buffer, &pid);

                printf("Enter Quantity: ");
                fgets(buffer, sizeof(buffer), stdin);
                Utils_ParseUInt(buffer, &qty);

                Status_t res = JobCard_AddPartUsage(jid, pid, qty);
                if (res == STATUS_SUCCESS) {
                    printf("[SUCCESS] Part usage recorded and stock deducted.\n");
                } else {
                    printf("[ERROR] %s\n", Utils_ErrorToString(res));
                }
                break;
            }
            case 6: {
                uint32_t jid = 0;
                float disc = 0.0f;
                printf("Enter Job ID: ");
                fgets(buffer, sizeof(buffer), stdin);
                Utils_ParseUInt(buffer, &jid);

                printf("Enter Discount (%%): ");
                fgets(buffer, sizeof(buffer), stdin);
                Utils_ParseFloat(buffer, &disc);

                Bill_t bill;
                Status_t res = Billing_Calculate(jid, disc, &bill);
                if (res == STATUS_SUCCESS) {
                    printf("\n--- Bill Summary ---\n");
                    printf("Labour Charge : INR %.2f\n", bill.labourCharge);
                    printf("Parts Total   : INR %.2f\n", bill.partsTotal);
                    printf("GST (18%%)     : INR %.2f\n", bill.gstAmount);
                    printf("Discount      : INR %.2f\n", bill.discountAmount);
                    printf("GRAND TOTAL   : INR %.2f\n", bill.grandTotal);
                } else {
                    printf("[ERROR] %s\n", Utils_ErrorToString(res));
                }
                break;
            }
            case 7: {
                SparePart_t lowList[MAX_PARTS];
                uint32_t lowCount = 0;
                SpareParts_GetLowStock(lowList, &lowCount);

                printf("\n--- Low Stock Alert Report (%u items) ---\n", lowCount);
                for (uint32_t i = 0; i < lowCount; i++) {
                    printf("ID: %u | Name: %s | Qty: %u | Reorder Level: %u\n",
                           lowList[i].partId, lowList[i].name, lowList[i].quantity, lowList[i].reorderLevel);
                }
                break;
            }
            case 8:
            case 0: {
                FileIO_SaveParts("data/parts.txt", SpareParts_GetAll(), SpareParts_GetCount());
                FileIO_SaveJobs("data/jobs.txt", JobCard_GetAll(), JobCard_GetCount());
                printf("[INFO] System data saved cleanly.\n");
                break;
            }
            default:
                printf("[ERROR] Invalid choice selected.\n");
                break;
        }
    }

    return 0;
}