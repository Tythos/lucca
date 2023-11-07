/**
 * tests/test_stumpff.cpp
 */

#include <iostream>
#include "lucca.hpp"
#include "gtest/gtest.h"

namespace lucca {
    namespace tests {
        namespace test_stumpff {
            TEST(TestStumpff, SineTests) {
                EXPECT_NEAR(lucca::stumpff::sine(-1.0), 0.175201, 1e-3);
                EXPECT_NEAR(lucca::stumpff::sine(0.0), 0.166667, 1e-3);
                EXPECT_NEAR(lucca::stumpff::sine(1.0), 0.158529, 1e-3);
            }

            TEST(TestStumpff, CosineTests) {
                EXPECT_NEAR(lucca::stumpff::cosine(-1.0), 0.543081, 1e-3);
                EXPECT_NEAR(lucca::stumpff::cosine(0.0), 0.5, 1e-3);
                EXPECT_NEAR(lucca::stumpff::cosine(1.0), 0.459698, 1e-3);
            }
        }
    }
}

int main(int nArgs, char** vArgs) {
    ::testing::InitGoogleTest(&nArgs, vArgs);
    return RUN_ALL_TESTS();
}
