#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "wool.h"

int ctl;
int v[] = {0, 0, 0, 0, 0};
int* vp;

void* thread1func() {
    while(ctl == 0) {};
    vp = &v[1];
    v[0] = 1;
}

void* thread2func() {
    while(ctl == 0) {};
    *vp = 1;
}

void* thread3func() {
    while(ctl == 0) {};
    vp = &v[3];
    v[4] = 1;
}

int main(int argc, char** argv) {
    ctl = 1;
    vp = &v[2];
    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;
    pthread_create(&thread1, NULL, thread1func, NULL);
    pthread_create(&thread2, NULL, thread2func, NULL);
    pthread_create(&thread3, NULL, thread3func, NULL);
    ctl = 0;
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    assert(v[0]+v[1]+v[2]+v[3]+v[4] == 3);
    return 0;
}
