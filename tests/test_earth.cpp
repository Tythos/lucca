/**
 * tests/test_earth.cpp
 */

#include <iostream>
#include "lucca.hpp"
#include "gtest/gtest.h"

namespace lucca {
    namespace tests {
        namespace test_earth {
            TEST(TestAnomaly, ConstsTest) {
                EXPECT_NEAR(lucca::earth::radius_m, 6.3781e6, 1e3);
            }
        }
    }
}

int main(int nArgs, char** vArgs) {
    ::testing::InitGoogleTest(&nArgs, vArgs);
    return RUN_ALL_TESTS();
}
