#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void signal_handler(int signum) {
    // Empty signal handler
}


int main(){
  int fd = open("abecedario", O_CREAT| O_WRONLY | O_TRUNC,0777);
  char letra = 'A';
  char letrah = 'b';
  pid_t pid = fork();
  signal(SIGUSR1, signal_handler);
  if (pid > 0){
    while (letra <= 'Z'){
      write(fd, &letra, 1);
      letra+=2;
      kill(pid, SIGUSR1);
      pause();
    }
  } else {
    while (letrah <= 'z'){
      pause();
      write(fd, &letrah,1);
      letrah+=2;
      kill(getppid(), SIGUSR1);
    }
  }
  close(fd);
  return 0;
}
