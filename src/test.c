#include "test.h"

#include <stdio.h>

extern test_t test_dummy;
extern test_t test_linked_list;

test_t * tests_glob[] = {&test_dummy, &test_linked_list};
int tests_glob_size = sizeof(tests_glob) / sizeof(tests_glob[0]);

int run_test(test_t * test)
{
        int rc = TEST_SKIP;
        if(!test->active)
        {
                printf("[test] skip: %s\n", test->name);
                return TEST_SKIP;
        }
        printf("[test] run %s\n", test->name);
        rc = test->test_base();
        if(rc == TEST_PASS)
                printf("[test] pass %s\n", test->name);
        else
                printf("[test] fail %s\n", test->name);
        fflush(stdout);
        return rc;
}

int run_tests()
{
        int i=0;
        setvbuf(stdout, NULL, _IONBF, 0);
        for(; i < tests_glob_size; i++)
        {
                test_t * test = tests_glob[i];
                run_test(test);
        }
        return 0;
}
