/**
 * tests/test_exceptions.cpp
 */

#include <iostream>
#include "lucca.hpp"
#include "gtest/gtest.h"

namespace lucca {
    namespace tests {
        namespace test_smoke {
            TEST(TestExceptions, ExceptionsTest) {
                EXPECT_STREQ(lucca::exceptions::xUnknown().what(), "Some kind of unknown astrodynamics exception was thrown");
            }
        }
    }
}

int main(int nArgs, char** vArgs) {
    ::testing::InitGoogleTest(&nArgs, vArgs);
    return RUN_ALL_TESTS();
}
