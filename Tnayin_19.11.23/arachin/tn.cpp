#include <iostream>
#include <csignal>
#include <unistd.h>
using namespace std;

int custom_signal_count = 0;

void custom_interrupt_handler(int signum)
{
    cout << "Total Custom Signals received: " << custom_signal_count << endl;
    exit(0);
}

void custom_signal1_handler(int signum)
{
    cout << "Received Custom Signal 1, ignoring..." << endl;
}

void custom_signal2_handler(int signum)
{
    custom_signal_count++;
}

int main()
{
    signal(SIGINT, custom_interrupt_handler);
    signal(SIGUSR1, custom_signal1_handler);
    signal(SIGUSR2, custom_signal2_handler);

    while (true)
    {
        cout << "Alive and well!" << endl;
        sleep(5);
    }

    return 0;
}
