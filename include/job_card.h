#ifndef JOB_CARD_H
#define JOB_CARD_H

#include "common.h"

typedef struct {
    uint32_t partId;
    uint32_t quantity;
    float unitPrice;
} UsedPart_t;

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

/* Job Card Public API */
void JobCard_Init(void);
Status_t JobCard_Create(const JobCard_t *job);
Status_t JobCard_FindById(uint32_t jobId, JobCard_t *outJob);
Status_t JobCard_UpdateStatus(uint32_t jobId, JobStatus_t newStatus);
Status_t JobCard_AddPartUsage(uint32_t jobId, uint32_t partId, uint32_t qty);
Status_t JobCard_GetByStatus(JobStatus_t status, JobCard_t *outList, uint32_t *outCount);
uint32_t JobCard_GetCount(void);
const JobCard_t* JobCard_GetAll(void);

#endif /* JOB_CARD_H */
