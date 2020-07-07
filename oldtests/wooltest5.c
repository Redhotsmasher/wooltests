#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "wool.h"

int res = 0;
int res2 = 0;

VOID_TASK_1(helloworld, int, i) {
    //printf("Hello world!");
    res = i;
}

VOID_TASK_1(hello2, int, dummy) {
    //printf("Hello world!");
    res2++;
}

int main(int argc, char** argv) {
    argc = wool_init(argc, argv);
    SPAWN(helloworld, 1);
    SPAWN(hello2, 1);
    
    SYNC(hello2);
    SYNC(helloworld);
    wool_fini();
    assert(res == 1);
    assert(res2 == 1);
    return 0;
}
