#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "wool.h"

VOID_TASK_2(arraytest, int, id, int*, arr) {
    arr[id]++;
}

int main(int argc, char** argv) {
    argc = wool_init(argc, argv);
    int arr[2];
    for(int i = 0; i < 2; i++) {
        arr[i] = 0;
        SPAWN(arraytest, i, &arr);
        SYNC(arraytest);
    }
    wool_fini();
    for(int i = 0; i < 2; i++) {
        assert(arr[i] == 1);
    }
    return 0;
}
