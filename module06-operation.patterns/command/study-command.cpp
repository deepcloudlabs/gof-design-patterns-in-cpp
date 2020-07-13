#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class Account {
    string iban;
    int balance;
    int overdraft_amount = -500;
public:
    Account(const string &iban, int balance, int overdraftLimit) : iban(iban), balance(balance),
                                                                   overdraft_amount(overdraftLimit) {}

    const string &getIban() const {
        return iban;
    }

    int getBalance() const {
        return balance;
    }

    int getOverdraftAmount() const {
        return overdraft_amount;
    }

    void deposit(int amount) {
        balance += amount;
        cout << "deposited " << amount << ", balance now " << balance << endl;
    }

    void withdraw(int amount) {
        if (balance - amount >= overdraft_amount) {
            balance -= amount;
            cout << "withdrew " << amount << ", balance now " << balance << endl;
        }
    }
};


struct Command {
    virtual ~Command() = default;

    virtual void call() const = 0;

    virtual void undo() const = 0;

};

class WithdrawCommand : public Command {
    Account &account;
    int amount;
public:
    WithdrawCommand(Account &account, const int amount) : account(account), amount(amount) {}

    void call() const override {
        account.withdraw(amount);
    }

    void undo() const override {
        account.deposit(amount);
    }

};

class DepositCommand : public Command {
    Account &account;
    int amount;
public:
    DepositCommand(Account &account, const int amount) : account(account), amount(amount) {}

    void call() const override {
        account.deposit(amount);
    }

    void undo() const override {
        account.withdraw(amount);
    }

};

class CompositeAccountCommand : public Command {
    vector<Command *> commands;
public:
    CompositeAccountCommand(const initializer_list<Command *> &items) : commands(items) {}

    void call() const override {
        for (auto &cmd : commands)
            cmd->call();
    }

    void undo() const override {
        for (auto &cmd : commands)
            cmd->undo();
    }
};

int main() {
    Account account("tr1", 1'000, -500);

    CompositeAccountCommand commands{
            new DepositCommand{account, 150},
            new WithdrawCommand{account, 700}
    };

    cout << account.getBalance() << endl;

    commands.call();

    cout << account.getBalance() << endl;

    commands.undo();

    cout << account.getBalance() << endl;

    return 0;
}
