#pragma once
#include <iostream>
#include <string>
#include <limits>
#include "Bank.h"
using namespace std;

class ConsoleUI
{
    private:
        Bank& bank;

        void clearInputBuffer() {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        int inputInt(const std::string& prompt) {
            int value;
            while (true) {
                cout << prompt;
                cin >> value;

                if (cin.fail()) {
                    cout << "Ошибка! Введите целое число.\n";
                    clearInputBuffer();
                }
                else {
                    clearInputBuffer();
                    return value;
                }
            }
        }

        double inputDouble(const string& prompt) {
            double value;
            while (true) {
                cout << prompt;
                cin >> value;

                if (cin.fail() || value < 0) {
                    cout << "Ошибка! Введите положительное число.\n";
                    clearInputBuffer();
                }
                else {
                    clearInputBuffer();
                    return value;
                }
            }
        }

        string inputString(const string& prompt) {
            string value;
            cout << prompt;
            getline(cin, value);
            return value;
        }

    public:
        ConsoleUI(Bank& b) : bank(b) {}

        void showMainMenu() {
            while (true) {
                cout << "\n=== БАНКОВСКОЕ ПРИЛОЖЕНИЕ ===\n";
                cout << "1) Создать новый аккаунт\n";
                cout << "2) Просмотреть баланс\n";
                cout << "3) Пополнить баланс\n";
                cout << "4) Снять деньги\n";
                cout << "5) Перевести деньги\n";
                cout << "6) Показать все аккаунты\n";
                cout << "0) Выход\n";
                cout << "Выберите действие: ";

                int choice;
                cin >> choice;
                clearInputBuffer();

                switch (choice) {
                case 1: createAccount(); break;
                case 2: showBalance(); break;
                case 3: depositMoney(); break;
                case 4: withdrawMoney(); break;
                case 5: transferMoney(); break;
                case 6: showAllAccounts(); break;
                case 0:
                    cout << "Сохранение данных...\n";
                    cout << "Выход из программы.\n";
                    return;
                default:
                    cout << "Неверный выбор! Попробуйте снова.\n";
                }
            }
        }

        void createAccount() {
            cout << "\n=== СОЗДАНИЕ АККАУНТА ===\n";

            string name = inputString("Введите имя: ");
            double initialBalance = inputDouble("Введите начальный баланс: ");

            Account newAccount = bank.createAccount(name, initialBalance);
            cout << "Аккаунт успешно создан!\n";
            cout << "ID вашего аккаунта: " << newAccount.getId() << "\n";
            cout << "Запомните этот ID для доступа к аккаунту!\n";
        }

        void showBalance() {
            cout << "\n=== ПРОСМОТР БАЛАНСА ===\n";

            int id = inputInt("Введите ID аккаунта: ");
            Account* account = bank.findAccount(id);

            if (account) {
                cout << "Владелец: " << account->getName() << "\n";
                cout << "Баланс: " << account->getBalance() << " руб.\n";
            }
            else {
                cout << "Аккаунт с ID " << id << " не найден!\n";
            }
        }

        void depositMoney() {
            cout << "\n=== ПОПОЛНЕНИЕ БАЛАНСА ===\n";

            int id = inputInt("Введите ID аккаунта: ");
            Account* account = bank.findAccount(id);

            if (account) {
                cout << "Текущий баланс: " << account->getBalance() << " руб.\n";
                double amount = inputDouble("Введите сумму для пополнения: ");

                if (account->deposit(amount)) {
                    cout << "Успешно! Новый баланс: " << account->getBalance() << " руб.\n";
                }
                else {
                    cout << "Ошибка при пополнении!\n";
                }
            }
            else {
                cout << "Аккаунт с ID " << id << " не найден!\n";
            }
        }

        void withdrawMoney() {
            cout << "\n=== СНЯТИЕ ДЕНЕГ ===\n";

            int id = inputInt("Введите ID аккаунта: ");
            Account* account = bank.findAccount(id);

            if (account) {
                cout << "Текущий баланс: " << account->getBalance() << " руб.\n";
                double amount = inputDouble("Введите сумму для снятия: ");

                if (account->withdraw(amount)) {
                    cout << "Успешно! Снято: " << amount << " руб.\n";
                    cout << "Новый баланс: " << account->getBalance() << " руб.\n";
                }
                else {
                    cout << "Ошибка! Недостаточно средств или неверная сумма.\n";
                }
            }
            else {
                cout << "Аккаунт с ID " << id << " не найден!\n";
            }
        }

        void transferMoney() {
            cout << "\n=== ПЕРЕВОД ДЕНЕГ ===\n";

            int fromId = inputInt("Введите ID вашего аккаунта: ");
            int toId = inputInt("Введите ID аккаунта получателя: ");

            if (fromId == toId) {
                cout << "Ошибка! Нельзя перевести деньги самому себе.\n";
                return;
            }

            Account* fromAccount = bank.findAccount(fromId);
            Account* toAccount = bank.findAccount(toId);

            if (!fromAccount) {
                cout << "Аккаунт отправителя не найден!\n";
                return;
            }

            if (!toAccount) {
                std::cout << "Аккаунт получателя не найден!\n";
                return;
            }

            cout << "Отправитель: " << fromAccount->getName() << "\n";
            cout << "Текущий баланс: " << fromAccount->getBalance() << " руб.\n";
            cout << "Получатель: " << toAccount->getName() << "\n\n";

            double amount = inputDouble("Введите сумму для перевода: ");

            if (bank.transferMoney(fromId, toId, amount)) {
                cout << "Перевод успешно выполнен!\n";
                cout << "Новый баланс отправителя: " << fromAccount->getBalance() << " руб.\n";
            }
            else {
                cout << "Ошибка перевода! Проверьте баланс и повторите попытку.\n";
            }
        }

        void showAllAccounts() {
            cout << "\n=== ВСЕ АККАУНТЫ В СИСТЕМЕ ===\n";
            cout << "Функция показа всех аккаунтов временно недоступна.\n";
            cout << "Разработчик Bank еще не реализовал метод getAllAccounts().\n";
        };
};

