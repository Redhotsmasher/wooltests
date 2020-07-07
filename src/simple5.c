#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "wool.h"

int res = 0;
int res2 = 0;
int res3 = 0;
int res4 = 0;
int res5 = 0;

VOID_TASK_1(helloworld, int, i) {
    res = i;
}

VOID_TASK_1(hello2, int, dummy) {
    res2++;
}

VOID_TASK_1(hello3, int, i) {
    res3 = i;
}

VOID_TASK_1(hello4, int, dummy) {
    res4++;
}

VOID_TASK_1(hello5, int, i) {
    res5 += i;
}

int main(int argc, char** argv) {
    argc = wool_init(argc, argv);
    SPAWN(helloworld, 1);
    SPAWN(hello2, 1);
    SPAWN(hello3, 1);
    SPAWN(hello4, 1);
    SPAWN(hello5, 1);
    
    SYNC(hello5);
    SYNC(hello4);
    SYNC(hello3);
    SYNC(hello2);
    SYNC(helloworld);
    wool_fini();
    assert(res == 1);
    assert(res2 == 1);
    assert(res3 == 1);
    assert(res4 == 1);
    assert(res5 == 1);
    return 0;
}
