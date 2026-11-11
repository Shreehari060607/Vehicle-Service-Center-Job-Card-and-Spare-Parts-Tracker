#include <stdio.h>
#include <string.h>
#include "job_card.h"
#include "spare_parts.h"
#include "utils.h"

static JobCard_t s_jobs[MAX_JOBS];
static uint32_t s_jobCount = 0;

void JobCard_Init(void) {
    memset(s_jobs, 0, sizeof(s_jobs));
    s_jobCount = 0;
}

Status_t JobCard_Create(const JobCard_t *job) {
    if (!job || job->jobId == 0) return ERR_INVALID_INPUT;
    if (!Utils_ValidateVehReg(job->vehicleReg)) return ERR_INVALID_INPUT;
    if (s_jobCount >= MAX_JOBS) return ERR_STORAGE_FULL;

    // Check duplicate Job ID
    for (uint32_t i = 0; i < s_jobCount; i++) {
        if (s_jobs[i].jobId == job->jobId) {
            return ERR_DUPLICATE_ID;
        }
    }

    s_jobs[s_jobCount] = *job;
    s_jobs[s_jobCount].status = STATUS_OPEN;
    s_jobs[s_jobCount].usedPartCount = 0;
    s_jobCount++;

    return STATUS_SUCCESS;
}

Status_t JobCard_FindById(uint32_t jobId, JobCard_t *outJob) {
    if (jobId == 0 || !outJob) return ERR_INVALID_INPUT;

    for (uint32_t i = 0; i < s_jobCount; i++) {
        if (s_jobs[i].jobId == jobId) {
            *outJob = s_jobs[i];
            return STATUS_SUCCESS;
        }
    }
    return ERR_JOB_NOT_FOUND;
}

Status_t JobCard_UpdateStatus(uint32_t jobId, JobStatus_t newStatus) {
    if (jobId == 0) return ERR_INVALID_INPUT;

    for (uint32_t i = 0; i < s_jobCount; i++) {
        if (s_jobs[i].jobId == jobId) {
            // Workflow rule: Open (0) -> In Progress (1) -> Completed (2) -> Billed (3)
            if ((int)newStatus != (int)s_jobs[i].status + 1) {
                return ERR_INVALID_STATUS_TRANSITION;
            }
            s_jobs[i].status = newStatus;
            return STATUS_SUCCESS;
        }
    }
    return ERR_JOB_NOT_FOUND;
}

Status_t JobCard_AddPartUsage(uint32_t jobId, uint32_t partId, uint32_t qty) {
    if (jobId == 0 || partId == 0 || qty == 0) return ERR_INVALID_INPUT;

    SparePart_t stockPart;
    Status_t status = SpareParts_FindById(partId, &stockPart);
    if (status != STATUS_SUCCESS) return status;

    status = SpareParts_DeductStock(partId, qty);
    if (status != STATUS_SUCCESS) return status;

    for (uint32_t i = 0; i < s_jobCount; i++) {
        if (s_jobs[i].jobId == jobId) {
            if (s_jobs[i].usedPartCount >= MAX_PARTS_PER_JOB) {
                return ERR_MAX_PARTS_EXCEEDED;
            }

            uint32_t idx = s_jobs[i].usedPartCount;
            s_jobs[i].usedParts[idx].partId = partId;
            s_jobs[i].usedParts[idx].quantity = qty;
            s_jobs[i].usedParts[idx].unitPrice = stockPart.unitPrice;
            s_jobs[i].usedPartCount++;

            return STATUS_SUCCESS;
        }
    }
    return ERR_JOB_NOT_FOUND;
}

Status_t JobCard_GetByStatus(JobStatus_t status, JobCard_t *outList, uint32_t *outCount) {
    if (!outList || !outCount) return ERR_INVALID_INPUT;

    uint32_t count = 0;
    for (uint32_t i = 0; i < s_jobCount; i++) {
        if (s_jobs[i].status == status) {
            outList[count++] = s_jobs[i];
        }
    }
    *outCount = count;
    return STATUS_SUCCESS;
}

uint32_t JobCard_GetCount(void) {
    return s_jobCount;
}

const JobCard_t* JobCard_GetAll(void) {
    return s_jobs;
}
