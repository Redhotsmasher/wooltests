#include <stdio.h>
#include <unistd.h>
#include "wool.h"
#include "wool-common.h"
#include "wool-queue.h"

VOID_TASK_1(smalltest, int, i) {
    printf("Hi!\n");
}

int main(int argc, char** argv) {
    argc = wool_init(argc, argv);
    /*for(int i = 0; i < n_workers; i++) {
        workers[i]->pr.more_work = 0;
        printf("[wt:%i]: work_lock\n", i);
        //wool_lock(&(workers[i]->pu.work_lock));
        }*/
    //SPAWN(smalltest, 0);
    sleep(5);
    printf("[wt]: slept\n");
    Task t;
    Task* tp = &t;
    printf("[wt]: pushing %x\n", tp);
    Task* ret = push_task(workers[0], tp);
    printf("[wt]: pushed, ret = %x\n", ret);
    #if 0
    printf("Zero is true!");
    #endif
    assert(workers[0]->pr.pr_top == ret);
    pop_task(workers[0], ret);
    /*for(int i = 0; i < n_workers; i++) {
        //wool_unlock(&(workers[i]->pu.work_lock));
        }*/
    //printf("tp = %x, tp2 = %x\n", tp, tp2);
    //printf("t = %x, t2 = %x\n", *tp, *tp2);
    //assert(tp == tp2);
    //SYNC(smalltest);
    wool_fini();
    return 0;
}
