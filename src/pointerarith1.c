#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
//#include "wool.h"
#include <pthread.h>

struct ints {
    int int1;
    int int2;
};

struct ints ints;

int val[2];

void *structwrite() {
    ints.int2 = 1;
}

int main(int argc, char** argv) {
    //argc = wool_init(argc, argv);
    ints.int1 = 0;
    ints.int2 = 0;
    long lint = (long)ints.int1;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_t thread1;
    printf("Size: %lu, &ints: %p, &ints.int2: %p\n", sizeof(struct ints), &ints, &ints.int2);
    pthread_create(&thread1, &attr, &structwrite, NULL);
    if(lint == 0) {
        printf("Zero, lint: %lx\n", lint);
    } else {
        printf("Nonzero, lint: %lx\n", lint);
    }
    pthread_attr_destroy(&attr);
    //SYNC(pointerwrite);
    //wool_fini();
    return 0;
}
