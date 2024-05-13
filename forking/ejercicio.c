#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

static volatile char caracter = 'a';

void handler(int sig) {
  for (size_t i = 0; i < 5; i++) {
    printf("%c\n", caracter);
    caracter++;
  }
}

int main(int argc, char *argv[]) {
  pid_t pid;

  signal(SIGUSR1, handler);

  for (size_t i = 0; i < 5; i++) {
    pid = fork();
    if (pid == 0) {
      // printf("soy el hijo: %d\n",getpid());
      signal(SIGUSR1, handler);
    }
  }
  sleep(1);
  for (size_t i = 0; i < 5; i++) {
    kill(getpid(), SIGUSR1);
    wait(NULL);
  }

  return 0;
}
