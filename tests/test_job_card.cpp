#include <gtest/gtest.h>
extern "C" {
    #include "job_card.h"
    #include "spare_parts.h"
}

class JobCardTest : public ::testing::Test {
protected:
    void SetUp() override {
        SpareParts_Init();
        JobCard_Init();
    }
};

// UT-08: Positive - Create job card
TEST_F(JobCardTest, CreateJobSuccess) {
    JobCard_t job = {1001, "MH12AB1234", "Rahul Sharma", "Oil change", SERVICE_PERIODIC, STATUS_OPEN, {}, 0};
    EXPECT_EQ(JobCard_Create(&job), STATUS_SUCCESS);
}

// UT-09: Positive/Negative - Workflow state machine transitions
TEST_F(JobCardTest, StatusWorkflowEnforcement) {
    JobCard_t job = {1001, "MH12AB1234", "Rahul Sharma", "Oil change", SERVICE_PERIODIC, STATUS_OPEN, {}, 0};
    JobCard_Create(&job);

    // Valid: Open -> In Progress
    EXPECT_EQ(JobCard_UpdateStatus(1001, STATUS_IN_PROGRESS), STATUS_SUCCESS);

    // Invalid: Attempting to skip directly from In Progress to Billed
    EXPECT_EQ(JobCard_UpdateStatus(1001, STATUS_BILLED), ERR_INVALID_STATUS_TRANSITION);
}