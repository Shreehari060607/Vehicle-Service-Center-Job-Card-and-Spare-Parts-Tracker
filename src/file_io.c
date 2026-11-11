#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_io.h"
#include "utils.h"

Status_t FileIO_LoadParts(const char *filename, SparePart_t *parts, uint32_t *count) {
    if (!filename || !parts || !count) return ERR_INVALID_INPUT;

    FILE *fp = fopen(filename, "r");
    if (!fp) return ERR_FILE_OPEN_FAILED;

    char line[256];
    uint32_t loaded = 0;

    while (fgets(line, sizeof(line), fp) && loaded < MAX_PARTS) {
        Utils_TrimNewline(line);
        if (strlen(line) == 0 || line[0] == '#') continue;

        SparePart_t p;
        if (sscanf(line, "%u,%49[^,],%u,%f,%u", 
                   &p.partId, p.name, &p.quantity, &p.unitPrice, &p.reorderLevel) == 5) {
            parts[loaded++] = p;
        }
    }

    fclose(fp);
    *count = loaded;
    return STATUS_SUCCESS;
}

Status_t FileIO_SaveParts(const char *filename, const SparePart_t *parts, uint32_t count) {
    if (!filename || !parts) return ERR_INVALID_INPUT;

    FILE *fp = fopen(filename, "w");
    if (!fp) return ERR_FILE_WRITE_FAILED;

    for (uint32_t i = 0; i < count; i++) {
        fprintf(fp, "%u,%s,%u,%.2f,%u\n",
                parts[i].partId, parts[i].name, parts[i].quantity,
                parts[i].unitPrice, parts[i].reorderLevel);
    }

    fclose(fp);
    return STATUS_SUCCESS;
}

Status_t FileIO_LoadJobs(const char *filename, JobCard_t *jobs, uint32_t *count) {
    if (!filename || !jobs || !count) return ERR_INVALID_INPUT;

    FILE *fp = fopen(filename, "r");
    if (!fp) return ERR_FILE_OPEN_FAILED;

    char line[512];
    uint32_t loaded = 0;

    while (fgets(line, sizeof(line), fp) && loaded < MAX_JOBS) {
        Utils_TrimNewline(line);
        if (strlen(line) == 0 || line[0] == '#') continue;

        JobCard_t j;
        int st, stat;
        if (sscanf(line, "%u,%15[^,],%49[^,],%99[^,],%d,%d",
                   &j.jobId, j.vehicleReg, j.ownerName, j.complaint, &st, &stat) == 6) {
            j.serviceType = (ServiceType_t)st;
            j.status = (JobStatus_t)stat;
            j.usedPartCount = 0;
            jobs[loaded++] = j;
        }
    }

    fclose(fp);
    *count = loaded;
    return STATUS_SUCCESS;
}

Status_t FileIO_SaveJobs(const char *filename, const JobCard_t *jobs, uint32_t count) {
    if (!filename || !jobs) return ERR_INVALID_INPUT;

    FILE *fp = fopen(filename, "w");
    if (!fp) return ERR_FILE_WRITE_FAILED;

    for (uint32_t i = 0; i < count; i++) {
        fprintf(fp, "%u,%s,%s,%s,%d,%d\n",
                jobs[i].jobId, jobs[i].vehicleReg, jobs[i].ownerName,
                jobs[i].complaint, (int)jobs[i].serviceType, (int)jobs[i].status);
    }

    fclose(fp);
    return STATUS_SUCCESS;
}

Status_t FileIO_ExportBill(const char *filename, const JobCard_t *job, const Bill_t *bill) {
    if (!filename || !job || !bill) return ERR_INVALID_INPUT;

    FILE *fp = fopen(filename, "w");
    if (!fp) return ERR_FILE_WRITE_FAILED;

    fprintf(fp, "========================================================\n");
    fprintf(fp, "             VEHICLE SERVICE CENTER INVOICE             \n");
    fprintf(fp, "========================================================\n");
    fprintf(fp, "Job ID: %u\n", job->jobId);
    fprintf(fp, "Vehicle Reg: %s\n", job->vehicleReg);
    fprintf(fp, "Owner Name: %s\n", job->ownerName);
    fprintf(fp, "Service Type: %s\n", Utils_ServiceTypeToString(job->serviceType));
    fprintf(fp, "--------------------------------------------------------\n");
    fprintf(fp, "Labour Charge:        INR %10.2f\n", bill->labourCharge);
    fprintf(fp, "Parts Subtotal:       INR %10.2f\n", bill->partsTotal);
    fprintf(fp, "Subtotal:             INR %10.2f\n", bill->subtotal);
    fprintf(fp, "GST (18%%):            INR %10.2f\n", bill->gstAmount);
    fprintf(fp, "Discount:            -INR %10.2f\n", bill->discountAmount);
    fprintf(fp, "--------------------------------------------------------\n");
    fprintf(fp, "GRAND TOTAL:          INR %10.2f\n", bill->grandTotal);
    fprintf(fp, "========================================================\n");

    fclose(fp);
    return STATUS_SUCCESS;
}
