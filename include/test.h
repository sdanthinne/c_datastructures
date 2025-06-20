#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef struct test_s {
        char * name;
        int (*test_base)(void);
        bool active;
} test_t;

#define REGISTER_TEST(n, f, a) \
        test_t test_ ## n __attribute__((used,section("__registered_tests"))) = { \
                .name = #n, \
                .test_base = f, \
                .active = a, \
        };

enum test_rc {
        TEST_SKIP,
        TEST_PASS,
        TEST_FAIL
};

extern test_t * registered_tests_start;
extern test_t * registered_tests_end;

int run_tests(void);
