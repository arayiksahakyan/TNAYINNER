#include <iostream>
#include <csignal>
#include <cstdlib>
#include <unistd.h>
using namespace std;

int main(int argument_count, char *argument_values[])
{
    if (argument_count != 3)
    {
        cerr << argument_values[0] << "PID" << endl;
        return 1;
    }
    int chosen_signal = atoi(argument_values[1]);
    pid_t target_pid = atoi(argument_values[2]);

    if (kill(target_pid, chosen_signal) == -1)
    {
        perror("Error!!");
        return 1;
    }
    
    return 0;
}
