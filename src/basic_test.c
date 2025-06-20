#include "test.h"

#include <stdio.h>

static int test_function(void)
{
        return TEST_PASS;
}

REGISTER_TEST(dummy, test_function, true)
