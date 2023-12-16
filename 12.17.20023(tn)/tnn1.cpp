#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <semaphore.h>

class Counter {
public:
    int value = 0;
};

std::mutex counterMutex;

void incrementWithMutex(Counter* counter) {
    for (int i = 0; i < 10000; ++i) {
        counterMutex.lock();
        counter->value++;
        counterMutex.unlock();
    }
}

int main() {
    Counter* myCounter = new Counter();
    myCounter->value = 2;

    std::thread threads[20];

    auto startMutex = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 20; ++i) {
        threads[i] = std::thread(incrementWithMutex, myCounter);
    }

    for (int i = 0; i < 20; ++i) {
        threads[i].join();
    }
    auto endMutex = std::chrono::high_resolution_clock::now();

    std::cout << "Mutex Time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(endMutex - startMutex).count()
              << "ms" << std::endl;

    std::cout << myCounter->value << std::endl;
    delete myCounter;

    return 0;
}
