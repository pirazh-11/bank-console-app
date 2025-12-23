#pragma once
#include <string>

class Account {
private:
    int    id;
    std::string name;
    double balance;

public:
    Account(int id, const std::string& name, double initial = 0.0);

    int         getId()    const;
    std::string getName()  const;
    double      getBalance() const;

    void deposit(double amount);
    bool withdraw(double amount);  
};
