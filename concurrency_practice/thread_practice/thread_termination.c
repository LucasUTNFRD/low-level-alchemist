#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define Pthread_create(thread, attr, start_routine, arg) \
    if (pthread_create(thread, attr, start_routine, arg) != 0) { \
        perror("pthread_create"); \
        exit(EXIT_FAILURE); \
    }

#define Pthread_join(thread, value_ptr) \
    if (pthread_join(thread, value_ptr) != 0) { \
        perror("pthread_join"); \
        exit(EXIT_FAILURE); \
    }

#define Malloc(size) ({ \
    void *ptr = malloc(size); \
    if (ptr == NULL) { \
        fprintf(stderr, "Error: Memory allocation failed\n"); \
        exit(EXIT_FAILURE); \
    } \
    ptr; \
})


typedef struct { int a;int b; } myarg_t;
typedef struct { int x;int y; } myret_t;

void *mythread(void *args){
    myret_t *rvals= Malloc(sizeof(myret_t));
    rvals->x =1;
    rvals->y = 2;
    return (void *) rvals;
}

int main(){
    pthread_t p;
    myret_t *rvals;
    myarg_t args = {10,20};
    Pthread_create(&p,NULL, mythread,&args);
    Pthread_join(p,(void **) &rvals);
    printf("returned %d %d\n", rvals->x,rvals->y);
    free(rvals);
    return 0;
}

