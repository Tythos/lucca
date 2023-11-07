/**
 * tests/test_anomaly.cpp
 */

#include <cmath>
#include <iostream>
#include "lucca.hpp"
#include "gtest/gtest.h"

namespace lucca {
    namespace tests {
        namespace test_smoke {
            TEST(TestAnomaly, Example3P1) {
                EXPECT_TRUE(true); // placeholder
            }

            TEST(TestAnomaly, Example3P2) {
                float tht_rad = lucca::anomaly::mean2true(3.6029, 0.37255);
                float tht_deg = tht_rad * 180 / M_PI;
                ASSERT_NEAR(tht_deg, 193.2, 1e-1);
            }

            TEST(TestAnomaly, Example3P2_inv) {
                float M_rad = lucca::anomaly::true2mean(193.2 * M_PI / 180.0, 0.37255);
                ASSERT_NEAR(M_rad, 3.6029, 1e-1);
            }
        }
    }
}

int main(int nArgs, char** vArgs) {
    ::testing::InitGoogleTest(&nArgs, vArgs);
    return RUN_ALL_TESTS();
}
