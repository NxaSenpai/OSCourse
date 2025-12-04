#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    pid = fork();     // Create a child process

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    else if (pid == 0) {
        // Child process
        printf("Child process running ls...\n");

        // Replace child program with "ls"
        execlp("ls", "ls", "-l", NULL);

        // If exec fails:
        perror("exec failed");
        exit(1);
    }
    else {
        // Parent process
        printf("Parent waiting for child...\n");
        wait(NULL);
        printf("Child finished.\n");
    }

    return 0;
}
