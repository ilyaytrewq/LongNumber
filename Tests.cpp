#include "LongNumber.hpp"
#include "gtest/gtest.h"


TEST(MATH, TEST1){
    LongMath::LongNumber a{"0,0354628376451547623546797645"};
    LongMath::LongNumber b{"-4352143512435124,9187346519783459"};
    EXPECT_EQ("-4352143512435124.8832718143331911376453202355", (a+b).toString());
}

TEST(MATH, TEST2){
    LongMath::LongNumber a = 99999999.9999999499997_ln;
    LongMath::LongNumber b = 100000000000.0000000500003_ln;
    EXPECT_EQ("100100000000.0", (a+b).toString());
}