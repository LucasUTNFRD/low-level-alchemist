//
// Created by lucas on 5/6/24.
//

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
    int fd = open("abecedario1", O_CREAT| O_WRONLY | O_TRUNC,0777);
    char letra = 'A';
    char letrah = 'b';
    pid_t pid1 = fork();
    signal(SIGUSR1, signal_handler);
    if(pid1==0){

    }else{
        pid_t pid2 = fork();
        

    }

}
