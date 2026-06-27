#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

pid_t vim_pid;

void sigint_handler(int sig) {
    printf("\nYou are pressed CTRL+C! Goodbye!\n");
    if (vim_pid > 0) {
        kill(vim_pid, SIGTERM);   // tat vim
    }
    exit(0);
}

int main() {
    // a. In dong chu chao mung
    printf("Welcome to IT007, I am CT230024!\n");

    // Cai dat handler bat CTRL+C
    signal(SIGINT, sigint_handler);

    // b. Mo tep abcd.txt bang vim
    vim_pid = fork();
    if (vim_pid == 0) {
        execlp("vim", "vim", "abcd.txt", NULL);
        perror("execlp loi");
        exit(1);
    } else if (vim_pid > 0) {
        waitpid(vim_pid, NULL, 0);  // cho vim ket thuc binh thuong (vd: go :q)
        printf("Vim da dong.\n");
    } else {
        perror("fork loi");
        exit(1);
    }

    return 0;
}
