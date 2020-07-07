#include <stdio.h>
#include "wool.h"

VOID_TASK_1(smalltest, int, i) {
    printf("Hi!\n");
}

int main(int argc, char** argv) {
    argc = wool_init(argc, argv);
    SPAWN(smalltest, 0);
    SYNC(smalltest);
    wool_fini();
    return 0;
}
