#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "wool.h"

TASK_1(int, fib, int, i) {
    if(i <= 1) {
        return i;
    } else {
        SPAWN(fib, i-1);
        SPAWN(fib, i-2);
        int fib2 = SYNC(fib);
        int fib1 = SYNC(fib);
        return fib1+fib2;
    }
}

int main(int argc, char** argv) {
    argc = wool_init(argc, argv);
    SPAWN(fib, 2);
    int res = SYNC(fib);
    wool_fini();
    assert(res == 1);
    return 0;
}
