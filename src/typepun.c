#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
//#include "wool.h"
#include <pthread.h>

int val[2];

void *pointerwrite() {
    //int* v2 = ((int*)val)+1;
    int* v2 = val+1;
    *v2 = 1;
}

int main(int argc, char** argv) {
    //argc = wool_init(argc, argv);
    long *v = &val[0];
    *v = 0;
    //printf("main::val: %p\n", val);
    //SPAWN(pointerwrite, &val);
    pthread_t thread1;
    pthread_create(&thread1, NULL, &pointerwrite, NULL);
    if(*v == 0) {
        printf("Zero.\n");
    } else {
        printf("v: %lx\n", *v);
    }
    pthread_join(thread1, NULL);
    //SYNC(pointerwrite);
    //wool_fini();
    return 0;
}
