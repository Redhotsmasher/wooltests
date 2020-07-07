#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "wool.h"

int res = 0;

VOID_TASK_1(helloworld, int, i) {
    //printf("Hello world!");
    res = i;
}

int main(int argc, char** argv) {
    argc = wool_init(argc, argv);
    SPAWN(helloworld, 1);
    SYNC(helloworld);
    wool_fini();
    assert(res == 1);
    return 0;
}
