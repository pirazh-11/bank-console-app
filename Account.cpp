#include "Account.h"

Account::Account(int id, const std::string& name, double initial)
    : id(id), name(name), balance(initial) {
}

int Account::getId() const { return id; }

std::string Account::getName()  const { return name; }

double Account::getBalance() const { return balance; }

void Account::deposit(double amount) {
    if (amount > 0) balance += amount;
}

bool Account::withdraw(double amount) {
    if (amount > 0 && amount <= balance) {
        balance -= amount;
        return true;
    }
    return false;
}
