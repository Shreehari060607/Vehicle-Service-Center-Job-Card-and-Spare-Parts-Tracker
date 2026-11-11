#include <gtest/gtest.h>
extern "C" {
    #include "billing.h"
    #include "job_card.h"
    #include "spare_parts.h"
}

class BillingTest : public ::testing::Test {
protected:
    void SetUp() override {
        SpareParts_Init();
        JobCard_Init();
    }
};

// UT-10: Positive - Bill calculation accuracy
TEST_F(BillingTest, CalculateBillAccuracy) {
    JobCard_t job = {1001, "MH12AB1234", "Rahul", "Periodic service", SERVICE_PERIODIC, STATUS_COMPLETED, {}, 0};
    JobCard_Create(&job);

    Bill_t bill;
    // Periodic labour = 500.0, 0 parts, GST 18% = 90.0, Total = 590.0
    EXPECT_EQ(Billing_Calculate(1001, 0.0f, &bill), STATUS_SUCCESS);
    EXPECT_FLOAT_EQ(bill.labourCharge, 500.0f);
    EXPECT_FLOAT_EQ(bill.gstAmount, 90.0f);
    EXPECT_FLOAT_EQ(bill.grandTotal, 590.0f);
}

// UT-11: Boundary - Reject out-of-range discount
TEST_F(BillingTest, RejectInvalidDiscount) {
    JobCard_t job = {1001, "MH12AB1234", "Rahul", "Periodic service", SERVICE_PERIODIC, STATUS_COMPLETED, {}, 0};
    JobCard_Create(&job);

    Bill_t bill;
    EXPECT_EQ(Billing_Calculate(1001, 60.0f, &bill), ERR_INVALID_DISCOUNT);
}
