#include <gtest/gtest.h>

#include "../lib.h"

TEST(test_version, simple_test)
{
    int vers = version();
    ASSERT_TRUE( vers > 0);
}
