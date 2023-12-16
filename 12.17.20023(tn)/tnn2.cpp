#include <iostream>
#include <thread>
#include <mutex>

class BankAccount {
public:
    BankAccount(int initial_balance) : balance(initial_balance) {}

    void processTransaction(int debit_amount, int credit_amount) {
        std::lock_guard<std::mutex> lock(mtx);
        balance -= debit_amount;
        balance += credit_amount;
    }

    int checkBalance() const {
        return balance;
    }

private:
    int balance;
    mutable std::mutex mtx;
};

void performTransaction(BankAccount& account, int debit_amount, int credit_amount) {
    account.processTransaction(debit_amount, credit_amount);
}

int main() {
    BankAccount userAccount(2000);

    const int debit_amount = 300;
    const int credit_amount = 400;
    const int num_threads = 10;
    std::thread threads[num_threads];

    for (int i = 0; i < num_threads; ++i) {
        threads[i] = std::thread(performTransaction, std::ref(userAccount), debit_amount, credit_amount);
    }

    for (int i = 0; i < num_threads; ++i) {
        threads[i].join();
    }

    std::cout << "Final Balance: " << userAccount.checkBalance() << std::endl;

    return 0;
}
