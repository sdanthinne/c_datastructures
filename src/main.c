#include <stdio.h>
#include "test.h"


int main(int argc, char *argv[])
{
        (void) argc;
        (void) argv;
        printf("Running tests\n\r");
        return run_tests();
}
