#include <gtest/gtest.h>
extern "C" {
    #include "spare_parts.h"
}

class SparePartsTest : public ::testing::Test {
protected:
    void SetUp() override {
        SpareParts_Init();
    }
};

// UT-04: Positive - Add spare part
TEST_F(SparePartsTest, AddPartSuccess) {
    SparePart_t p = {101, "Oil Filter", 20, 350.0f, 5};
    EXPECT_EQ(SpareParts_Add(&p), STATUS_SUCCESS);
    EXPECT_EQ(SpareParts_GetCount(), 1u);
}

// UT-05: Negative - Reject duplicate part ID
TEST_F(SparePartsTest, RejectDuplicatePartId) {
    SparePart_t p1 = {101, "Oil Filter", 20, 350.0f, 5};
    SparePart_t p2 = {101, "Air Filter", 10, 450.0f, 3};
    EXPECT_EQ(SpareParts_Add(&p1), STATUS_SUCCESS);
    EXPECT_EQ(SpareParts_Add(&p2), ERR_DUPLICATE_ID);
}

// UT-06: Boundary/Negative - Stock deduction failure on insufficient stock
TEST_F(SparePartsTest, InsufficientStockDeduction) {
    SparePart_t p = {101, "Oil Filter", 5, 350.0f, 2};
    SpareParts_Add(&p);
    EXPECT_EQ(SpareParts_DeductStock(101, 10), ERR_INSUFFICIENT_STOCK);
}

// UT-07: Positive - Low stock report filtering
TEST_F(SparePartsTest, LowStockReport) {
    SparePart_t p1 = {101, "Oil Filter", 2, 350.0f, 5}; // Low stock (2 <= 5)
    SparePart_t p2 = {102, "Brake Pads", 15, 1200.0f, 4}; // Normal stock
    SpareParts_Add(&p1);
    SpareParts_Add(&p2);

    SparePart_t lowList[MAX_PARTS];
    uint32_t count = 0;
    EXPECT_EQ(SpareParts_GetLowStock(lowList, &count), STATUS_SUCCESS);
    EXPECT_EQ(count, 1u);
    EXPECT_EQ(lowList[0].partId, 101u);
}
