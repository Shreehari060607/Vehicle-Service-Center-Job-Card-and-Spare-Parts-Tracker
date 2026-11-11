#ifndef BILLING_H
#define BILLING_H

#include "common.h"
#include "job_card.h"

typedef struct {
    uint32_t jobId;
    float labourCharge;
    float partsTotal;
    float subtotal;
    float gstAmount;
    float discountAmount;
    float grandTotal;
} Bill_t;

/* Billing Public API */
Status_t Billing_Calculate(uint32_t jobId, float discountPercentage, Bill_t *outBill);
float Billing_GetLabourCharge(ServiceType_t serviceType);

#endif /* BILLING_H */
