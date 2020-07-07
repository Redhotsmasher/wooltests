#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "wool.h"

VOID_TASK_2(arraytest, int, id, int*, arr) {
    //printf("arr from %i: %x\n", id, arr);
    arr[id]++;
}

int main(int argc, char** argv) {
    argc = wool_init(argc, argv);
    int arr[8];
    //int* arr = malloc(8*sizeof(int));
    //printf("arr: %x\n", &arr);
    for(int i = 0; i < 8; i++) {
        arr[i] = 0;
        SPAWN(arraytest, i, &arr);
        SYNC(arraytest);
    }
    for(int i = 0; i < 8; i++) {
        //printf("arr[%i]: %i\n", i, arr[i]);
    }
    /*for(int i = 7; i >= 0; i--) {
        SYNC(arraytest);
        }*/
    for(int i = 0; i < 8; i++) {
        //printf("arr[%i]: %i\n", i, arr[i]);
        assert(arr[i] == 1);
    }
#ifdef NDEBUG
    //printf("NDEBUG!\n");
#endif
    //printf("Success!\n");
    wool_fini();
    //free(arr);
    return 0;
}
