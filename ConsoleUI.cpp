#include "ConsoleUI.h"
#pragma once
#include <string>
#include "Bank.h"

class ConsoleUI
{
private:
    Bank& bank;

    void clearInputBuffer();
    int inputInt(const std::string& prompt);
    double inputDouble(const std::string& prompt);
    std::string inputString(const std::string& prompt);

public:
    ConsoleUI(Bank& b);

    void showMainMenu();
    void createAccount();
    void showBalance();
    void depositMoney();
    void withdrawMoney();
    void transferMoney();
    void showAllAccounts();
};

