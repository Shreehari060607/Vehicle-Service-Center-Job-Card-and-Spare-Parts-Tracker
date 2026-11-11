#include <gtest/gtest.h>
extern "C" {
    #include "utils.h"
}

// UT-01: Positive - Valid Indian vehicle registration format
TEST(UtilsTest, ValidVehicleReg) {
    EXPECT_TRUE(Utils_ValidateVehReg("MH12AB1234"));
    EXPECT_TRUE(Utils_ValidateVehReg("DL01C1234"));
}

// UT-02: Negative - Invalid vehicle registration format
TEST(UtilsTest, InvalidVehicleReg) {
    EXPECT_FALSE(Utils_ValidateVehReg("INVALID"));
    EXPECT_FALSE(Utils_ValidateVehReg("1234MH"));
    EXPECT_FALSE(Utils_ValidateVehReg(NULL));
}

// UT-03: Boundary - Integer parsing bounds check
TEST(UtilsTest, ParseUIntBounds) {
    uint32_t val = 0;
    EXPECT_TRUE(Utils_ParseUInt("100", &val));
    EXPECT_EQ(val, 100u);
    EXPECT_FALSE(Utils_ParseUInt("-5", &val));
    EXPECT_FALSE(Utils_ParseUInt("abc", &val));
}
