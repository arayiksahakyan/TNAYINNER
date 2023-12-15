#include <iostream>
#include <csignal>
#include <unistd.h>
#include <sys/ucontext.h>

using namespace std;

void custom_signal_handler(int signum, siginfo_t *info, void *context) {

    cout << "ID of the sender: " << info->si_pid << endl;

    ucontext_t *custom_context = (ucontext_t *)context;
    cout << "EIP: " << custom_context->uc_mcontext.gregs[REG_EIP] << endl;
    cout << "EAX: " << custom_context->uc_mcontext.gregs[REG_EAX] << endl;
    cout << "EBX: " << custom_context->uc_mcontext.gregs[REG_EBX] << endl;
}

int main() {
    struct sigaction custom_action;
    custom_action.sa_sigaction = custom_signal_handler;
    custom_action.sa_flags = SA_SIGINFO;

    if (sigaction(SIGUSR1, &custom_action, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    cout << "My Process ID: " << getpid() << endl;
    cout << "Waiting for signals..." << endl;

    while (true) {
        sleep(10);
    }

    return 0;
}
