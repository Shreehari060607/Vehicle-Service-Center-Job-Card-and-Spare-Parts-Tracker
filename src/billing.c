#include <stdio.h>
#include "billing.h"

float Billing_GetLabourCharge(ServiceType_t serviceType) {
    switch (serviceType) {
        case SERVICE_PERIODIC: return LABOUR_PERIODIC;
        case SERVICE_REPAIR:   return LABOUR_REPAIR;
        case SERVICE_ACCIDENT: return LABOUR_ACCIDENT;
        default:               return 0.0f;
    }
}

Status_t Billing_Calculate(uint32_t jobId, float discountPercentage, Bill_t *outBill) {
    if (jobId == 0 || !outBill) return ERR_INVALID_INPUT;
    if (discountPercentage < 0.0f || discountPercentage > 50.0f) {
        return ERR_INVALID_DISCOUNT;
    }

    JobCard_t job;
    Status_t status = JobCard_FindById(jobId, &job);
    if (status != STATUS_SUCCESS) return status;

    outBill->jobId = jobId;
    outBill->labourCharge = Billing_GetLabourCharge(job.serviceType);

    float partsCost = 0.0f;
    for (uint32_t i = 0; i < job.usedPartCount; i++) {
        partsCost += (job.usedParts[i].unitPrice * (float)job.usedParts[i].quantity);
    }
    outBill->partsTotal = partsCost;
    outBill->subtotal = outBill->labourCharge + outBill->partsTotal;
    outBill->gstAmount = outBill->subtotal * (GST_RATE_PERCENT / 100.0f);
    
    float totalBeforeDiscount = outBill->subtotal + outBill->gstAmount;
    outBill->discountAmount = totalBeforeDiscount * (discountPercentage / 100.0f);
    outBill->grandTotal = totalBeforeDiscount - outBill->discountAmount;

    return STATUS_SUCCESS;
}
