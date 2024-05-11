#include <pthread.h>
#include <stdio.h>

typedef struct {
    int a;
    int b;
}myarg_t;

void *mythread(void *arg){
    myarg_t  *args = (myarg_t *) arg;
    printf("%d %d\n",args->a,args->b);
    return NULL;
}

int main(){
    pthread_t p;
    myarg_t args = {10,20};

    int rc = pthread_create(&p,NULL,mythread,&args);
    if(rc!=0){
        perror("thread creation failed");
    }
    sleep(1); //handle races
    exit(0);
}
