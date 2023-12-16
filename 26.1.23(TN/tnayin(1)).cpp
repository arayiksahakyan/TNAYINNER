 #include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int custom_pipe_fd[2];

    pid_t child_pid1, child_pid2;
    child_pid1 = fork();

    if (child_pid1 < 0) {
        std::cerr << "Error creating first child process." << std::endl;
        return 1;
    } else if (child_pid1 == 0) {
        pid_t ownPID = getpid();
        close(custom_pipe_fd[0]);
        write(custom_pipe_fd[1], &ownPID, sizeof(ownPID));
        close(custom_pipe_fd[1]);
        return 0;
    } else {
        child_pid2 = fork();

        if (child_pid2 < 0) {
            std::cerr << "Error creating second child process." << std::endl;
            return 1;
        } else if (child_pid2 == 0) {
            pid_t ownPID = getpid();
            close(custom_pipe_fd[0]);
            write(custom_pipe_fd[1], &ownPID, sizeof(ownPID));
            close(custom_pipe_fd[1]);
            return 0;
        } else {
            close(custom_pipe_fd[1]);

            pid_t pid_from_child1, pid_from_child2;

            read(custom_pipe_fd[0], &pid_from_child1, sizeof(pid_from_child1));
            read(custom_pipe_fd[0], &pid_from_child2, sizeof(pid_from_child2));

            std::cout << "Parent Process ID: " << getpid() << std::endl;
            std::cout << "First Child's PID: " << pid_from_child1 << std::endl;
            std::cout << "Second Child's PID: " << pid_from_child2 << std::endl;

            close(custom_pipe_fd[0]);
            wait(NULL);
            wait(NULL);
        }
    }

    return 0;
}
