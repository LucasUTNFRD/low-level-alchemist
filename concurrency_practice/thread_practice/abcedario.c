// #include <bits/pthreadtypes.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t lock_1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock_2 = PTHREAD_MUTEX_INITIALIZER;

#define Pthread_create(thread, attr, start_routine, arg)                       \
  if (pthread_create(thread, attr, start_routine, arg) != 0) {                 \
    perror("pthread_create");                                                  \
  }

#define Pthread_join(thread, value_ptr)                                        \
  if (pthread_join(thread, value_ptr) != 0) {                                  \
    perror("pthread_join");                                                    \
  }

typedef struct {
  int fd;
  char caracter;
} datosHilo;

void *handler_minusulas(void *args) {
  datosHilo *datos = (datosHilo *)args;
  while (datos->caracter <= 'z') {
    pthread_mutex_lock(&lock_1);
    write(datos->fd, &(datos->caracter), 1);
    pthread_mutex_unlock(&lock_2);
    datos->caracter += 2;
  }
}

void *handler_mayusculas(void *args) {
  datosHilo *datos = (datosHilo *)args;
  while (datos->caracter <= 'Z') {
    pthread_mutex_lock(&lock_2);
    write(datos->fd, &(datos->caracter), 1);
    pthread_mutex_unlock(&lock_1);
    datos->caracter += 2;
  }
}

int main(void) {
  pthread_mutex_lock(&lock_2);
  int fd = open("hola", O_TRUNC | O_WRONLY | O_CREAT, 0777);
  datosHilo datos_hilo1 = {fd, 'a'};
  datosHilo datos_hilo2 = {fd, 'B'};
  pthread_t p1;
  pthread_t p2;
  Pthread_create(&p1, NULL, (void *)handler_minusulas, &datos_hilo1);
  Pthread_create(&p2, NULL, (void *)handler_mayusculas, &datos_hilo2);
  Pthread_join(p1, NULL);
  Pthread_join(p2, NULL);
  close(fd);

  return 0;
}
