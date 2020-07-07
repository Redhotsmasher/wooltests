#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "wool.h"

TASK_1(int, recurse, int, i) {
    if(i > 0) {
        SPAWN(recurse, i-1);
        return SYNC(recurse)+1;
    } else {
        return 0;
    }
}

int main(int argc, char** argv) {
    argc = wool_init(argc, argv);
    SPAWN(recurse, 2);
    int sum = SYNC(recurse);
    wool_fini();
    assert(sum == 2);
    return 0;
}
