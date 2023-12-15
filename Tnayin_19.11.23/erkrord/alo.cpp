#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int main() {
    pid_t child_pid = fork();

    if (child_pid == -1) {

        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (child_pid == 0) {

        sleep(2);
        printf("killing root-er.\n");


        if (kill(getppid(), SIGKILL) == 0) {
            printf("No mo parrent\n");
        } else {
            printf("He alive(parent)\n");
        }
    } else {

        printf("Expecto Patronum.\n");
        sleep(5);

        printf("Sleep choke.\n");
    }

    return 0;
}
