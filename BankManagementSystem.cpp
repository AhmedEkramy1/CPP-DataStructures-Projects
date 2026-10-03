#include <iostream>
#include <vector>
#include <string>

using namespace std;

class BankAccount {
private:
    int accountNumber;
    string accountHolder;
    double balance;

public:
    BankAccount(int accNum, string holder, double initialBalance) {
        accountNumber = accNum;
        accountHolder = holder;
        balance = initialBalance;
    }

    int getAccountNumber() const { return accountNumber; }
    string getAccountHolder() const { return accountHolder; }
    double getBalance() const { return balance; }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Successfully deposited $" << amount << "\n";
        } else {
            cout << "Invalid deposit amount!\n";
        }
    }

    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Successfully withdrew $" << amount << "\n";
            return true;
        } else {
            cout << "Insufficient balance or invalid amount!\n";
            return false;
        }
    }

    void displayAccountInfo() const {
        cout << "Account Number: " << accountNumber 
             << " | Holder: " << accountHolder 
             << " | Balance: $" << balance << "\n";
    }
};

class BankManagementSystem {
private:
    vector<BankAccount> accounts;

public:
    void createAccount(int accNum, string holder, double initialBalance) {
        for (const auto& acc : accounts) {
            if (acc.getAccountNumber() == accNum) {
                cout << "Error: Account number already exists!\n";
                return;
            }
        }
        accounts.push_back(BankAccount(accNum, holder, initialBalance));
        cout << "Account created successfully for " << holder << "!\n";
    }

    void displayAllAccounts() const {
        if (accounts.empty()) {
            cout << "No accounts found in the system.\n";
            return;
        }
        cout << "\n--- All Bank Accounts ---\n";
        for (const auto& acc : accounts) {
            acc.displayAccountInfo();
        }
    }

    BankAccount* findAccount(int accNum) {
        for (auto& acc : accounts) {
            if (acc.getAccountNumber() == accNum) {
                return &acc;
            }
        }
        return nullptr;
    }
};

int main() {
    BankManagementSystem bank;
    int choice;

    do {
        cout << "\n===============================\n";
        cout << "    BANK MANAGEMENT SYSTEM     \n";
        cout << "===============================\n";
        cout << "1. Create New Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Display All Accounts\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int accNum;
                string name;
                double balance;
                cout << "Enter Account Number: ";
                cin >> accNum;
                cout << "Enter Account Holder Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Initial Balance: ";
                cin >> balance;
                bank.createAccount(accNum, name, balance);
                break;
            }
            case 2: {
                int accNum;
                double amount;
                cout << "Enter Account Number: ";
                cin >> accNum;
                BankAccount* acc = bank.findAccount(accNum);
                if (acc) {
                    cout << "Enter Deposit Amount: ";
                    cin >> amount;
                    acc->deposit(amount);
                } else {
                    cout << "Account not found!\n";
                }
                break;
            }
            case 3: {
                int accNum;
                double amount;
                cout << "Enter Account Number: ";
                cin >> accNum;
                BankAccount* acc = bank.findAccount(accNum);
                if (acc) {
                    cout << "Enter Withdrawal Amount: ";
                    cin >> amount;
                    acc->withdraw(amount);
                } else {
                    cout << "Account not found!\n";
                }
                break;
            }
            case 4:
                bank.displayAllAccounts();
                break;
            case 5:
                cout << "Exiting system. Thank you!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
