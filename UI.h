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
                    cout << "Îøèáêà! Ââåäèòå öåëîå ÷èñëî.\n";
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
                    cout << "Îøèáêà! Ââåäèòå ïîëîæèòåëüíîå ÷èñëî.\n";
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
                cout << "\n=== ÁÀÍÊÎÂÑÊÎÅ ÏÐÈËÎÆÅÍÈÅ ===\n";
                cout << "1) Ñîçäàòü íîâûé àêêàóíò\n";
                cout << "2) Ïðîñìîòðåòü áàëàíñ\n";
                cout << "3) Ïîïîëíèòü áàëàíñ\n";
                cout << "4) Ñíÿòü äåíüãè\n";
                cout << "5) Ïåðåâåñòè äåíüãè\n";
                cout << "6) Ïîêàçàòü âñå àêêàóíòû\n";
                cout << "0) Âûõîä\n";
                cout << "Âûáåðèòå äåéñòâèå: ";

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
                    cout << "Ñîõðàíåíèå äàííûõ...\n";
                    cout << "Âûõîä èç ïðîãðàììû.\n";
                    return;
                default:
                    cout << "Íåâåðíûé âûáîð! Ïîïðîáóéòå ñíîâà.\n";
                }
            }
        }

        void createAccount() {
            cout << "\n=== ÑÎÇÄÀÍÈÅ ÀÊÊÀÓÍÒÀ ===\n";

            string name = inputString("Ââåäèòå èìÿ: ");
            double initialBalance = inputDouble("Ââåäèòå íà÷àëüíûé áàëàíñ: ");

            Account newAccount = bank.createAccount(name, initialBalance);
            cout << "Àêêàóíò óñïåøíî ñîçäàí!\n";
            cout << "ID âàøåãî àêêàóíòà: " << newAccount.getId() << "\n";
            cout << "Çàïîìíèòå ýòîò ID äëÿ äîñòóïà ê àêêàóíòó!\n";
        }

        void showBalance() {
            cout << "\n=== ÏÐÎÑÌÎÒÐ ÁÀËÀÍÑÀ ===\n";

            int id = inputInt("Ââåäèòå ID àêêàóíòà: ");
            Account* account = bank.findAccount(id);

            if (account) {
                cout << "Âëàäåëåö: " << account->getName() << "\n";
                cout << "Áàëàíñ: " << account->getBalance() << " ðóá.\n";
            }
            else {
                cout << "Àêêàóíò ñ ID " << id << " íå íàéäåí!\n";
            }
        }

        void depositMoney() {
            cout << "\n=== ÏÎÏÎËÍÅÍÈÅ ÁÀËÀÍÑÀ ===\n";

            int id = inputInt("Ââåäèòå ID àêêàóíòà: ");
            Account* account = bank.findAccount(id);

            if (account) {
                cout << "Òåêóùèé áàëàíñ: " << account->getBalance() << " ðóá.\n";
                double amount = inputDouble("Ââåäèòå ñóììó äëÿ ïîïîëíåíèÿ: ");

                if (account->deposit(amount)) {
                    cout << "Óñïåøíî! Íîâûé áàëàíñ: " << account->getBalance() << " ðóá.\n";
                }
                else {
                    cout << "Îøèáêà ïðè ïîïîëíåíèè!\n";
                }
            }
            else {
                cout << "Àêêàóíò ñ ID " << id << " íå íàéäåí!\n";
            }
        }

        void withdrawMoney() {
            cout << "\n=== ÑÍßÒÈÅ ÄÅÍÅÃ ===\n";

            int id = inputInt("Ââåäèòå ID àêêàóíòà: ");
            Account* account = bank.findAccount(id);

            if (account) {
                cout << "Òåêóùèé áàëàíñ: " << account->getBalance() << " ðóá.\n";
                double amount = inputDouble("Ââåäèòå ñóììó äëÿ ñíÿòèÿ: ");

                if (account->withdraw(amount)) {
                    cout << "Óñïåøíî! Ñíÿòî: " << amount << " ðóá.\n";
                    cout << "Íîâûé áàëàíñ: " << account->getBalance() << " ðóá.\n";
                }
                else {
                    cout << "Îøèáêà! Íåäîñòàòî÷íî ñðåäñòâ èëè íåâåðíàÿ ñóììà.\n";
                }
            }
            else {
                cout << "Àêêàóíò ñ ID " << id << " íå íàéäåí!\n";
            }
        }

        void transferMoney() {
            cout << "\n=== ÏÅÐÅÂÎÄ ÄÅÍÅÃ ===\n";

            int fromId = inputInt("Ââåäèòå ID âàøåãî àêêàóíòà: ");
            int toId = inputInt("Ââåäèòå ID àêêàóíòà ïîëó÷àòåëÿ: ");

            if (fromId == toId) {
                cout << "Îøèáêà! Íåëüçÿ ïåðåâåñòè äåíüãè ñàìîìó ñåáå.\n";
                return;
            }

            Account* fromAccount = bank.findAccount(fromId);
            Account* toAccount = bank.findAccount(toId);

            if (!fromAccount) {
                cout << "Àêêàóíò îòïðàâèòåëÿ íå íàéäåí!\n";
                return;
            }

            if (!toAccount) {
                std::cout << "Àêêàóíò ïîëó÷àòåëÿ íå íàéäåí!\n";
                return;
            }

            cout << "Îòïðàâèòåëü: " << fromAccount->getName() << "\n";
            cout << "Òåêóùèé áàëàíñ: " << fromAccount->getBalance() << " ðóá.\n";
            cout << "Ïîëó÷àòåëü: " << toAccount->getName() << "\n\n";

            double amount = inputDouble("Ââåäèòå ñóììó äëÿ ïåðåâîäà: ");

            if (bank.transferMoney(fromId, toId, amount)) {
                cout << "Ïåðåâîä óñïåøíî âûïîëíåí!\n";
                cout << "Íîâûé áàëàíñ îòïðàâèòåëÿ: " << fromAccount->getBalance() << " ðóá.\n";
            }
            else {
                cout << "Îøèáêà ïåðåâîäà! Ïðîâåðüòå áàëàíñ è ïîâòîðèòå ïîïûòêó.\n";
            }
        }

        void showAllAccounts() {
            cout << "\n=== ÂÑÅ ÀÊÊÀÓÍÒÛ Â ÑÈÑÒÅÌÅ ===\n";
            cout << "Ôóíêöèÿ ïîêàçà âñåõ àêêàóíòîâ âðåìåííî íåäîñòóïíà.\n";
            cout << "Ðàçðàáîò÷èê Bank åùå íå ðåàëèçîâàë ìåòîä getAllAccounts().\n";
        };
};

