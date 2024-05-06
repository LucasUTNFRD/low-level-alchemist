//
// Created by lucas on 5/5/24.
//

//create one thread and print the proces and thread ids of the new thread and the intial thread.
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

void printids(const char *s) {
    pid_t pid;
    pthread_t tid;

    pid = getpid();
    tid = pthread_self();
    printf("%s pid %lu tid %lu (0x%lx)\n", s, (unsigned long) pid,(unsigned long) tid, (unsigned long) tid);

}

void *thr_fn(void *arg){
    printids("new thread: ");
    return((void *)0);
}
pthread_t ntid;
int main(void){
    int err;
    err = pthread_create(&ntid,NULL, thr_fn,NULL);
    if(err!=0){
        perror("cant create thread");
    }
    printids("main thread: ");
    sleep(1);
    // if it doesnt sleep, the main thread might exit, thereby temrinating the entire process before
    //the new thread get chance to run.
    exit(0);
}