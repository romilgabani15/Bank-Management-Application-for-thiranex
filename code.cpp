#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class BankAccount {
private:
    int accNo;
    char name[50];
    float balance;

public:
    void createAccount() {
        cout << "\nEnter Account Number: ";
        cin >> accNo;

        cin.ignore();

        cout << "Enter Customer Name: ";
        cin.getline(name, 50);

        cout << "Enter Initial Balance: ";
        cin >> balance;
    }

    void displayAccount() {
        cout << "\nAccount Number : " << accNo;
        cout << "\nCustomer Name  : " << name;
        cout << "\nBalance        : " << balance << endl;
    }

    int getAccNo() {
        return accNo;
    }

    float getBalance() {
        return balance;
    }

    void deposit(float amount) {
        balance += amount;
    }

    void withdraw(float amount) {
        if (amount <= balance) {
            balance -= amount;
            cout << "\nWithdrawal Successful!\n";
        } else {
            cout << "\nInsufficient Balance!\n";
        }
    }
};

// Create Account
void createNewAccount() {
    BankAccount acc;

    ofstream file("bank.dat", ios::binary | ios::app);

    acc.createAccount();

    file.write((char*)&acc, sizeof(acc));

    file.close();

    cout << "\nAccount Created Successfully!\n";
}

// Display All Accounts
void displayAllAccounts() {
    BankAccount acc;

    ifstream file("bank.dat", ios::binary);

    cout << "\n========== Account Records ==========\n";

    while (file.read((char*)&acc, sizeof(acc))) {
        acc.displayAccount();
        cout << "-----------------------------------\n";
    }

    file.close();
}

// Deposit Money
void depositMoney() {
    BankAccount acc;
    int number;
    float amount;
    bool found = false;

    fstream file("bank.dat", ios::binary | ios::in | ios::out);

    cout << "\nEnter Account Number: ";
    cin >> number;

    while (file.read((char*)&acc, sizeof(acc))) {
        if (acc.getAccNo() == number) {
            cout << "Enter Amount to Deposit: ";
            cin >> amount;

            acc.deposit(amount);

            int pos = (-1) * sizeof(acc);
            file.seekp(pos, ios::cur);

            file.write((char*)&acc, sizeof(acc));

            cout << "\nAmount Deposited Successfully!\n";

            found = true;
            break;
        }
    }

    if (!found)
        cout << "\nAccount Not Found!\n";

    file.close();
}

// Withdraw Money
void withdrawMoney() {
    BankAccount acc;
    int number;
    float amount;
    bool found = false;

    fstream file("bank.dat", ios::binary | ios::in | ios::out);

    cout << "\nEnter Account Number: ";
    cin >> number;

    while (file.read((char*)&acc, sizeof(acc))) {
        if (acc.getAccNo() == number) {
            cout << "Enter Amount to Withdraw: ";
            cin >> amount;

            acc.withdraw(amount);

            int pos = (-1) * sizeof(acc);
            file.seekp(pos, ios::cur);

            file.write((char*)&acc, sizeof(acc));

            found = true;
            break;
        }
    }

    if (!found)
        cout << "\nAccount Not Found!\n";

    file.close();
}

// Balance Check
void checkBalance() {
    BankAccount acc;
    int number;
    bool found = false;

    ifstream file("bank.dat", ios::binary);

    cout << "\nEnter Account Number: ";
    cin >> number;

    while (file.read((char*)&acc, sizeof(acc))) {
        if (acc.getAccNo() == number) {
            cout << "\nCurrent Balance: " << acc.getBalance() << endl;
            found = true;
            break;
        }
    }

    if (!found)
        cout << "\nAccount Not Found!\n";

    file.close();
}

int main() {
    int choice;

    do {
        cout << "\n========== BANK MANAGEMENT SYSTEM ==========\n";
        cout << "1. Create Account\n";
        cout << "2. Display All Accounts\n";
        cout << "3. Deposit Money\n";
        cout << "4. Withdraw Money\n";
        cout << "5. Check Balance\n";
        cout << "6. Exit\n";
        cout << "Enter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                createNewAccount();
                break;

            case 2:
                displayAllAccounts();
                break;

            case 3:
                depositMoney();
                break;

            case 4:
                withdrawMoney();
                break;

            case 5:
                checkBalance();
                break;

            case 6:
                cout << "\nThank You for Using Bank Management System!\n";
                break;

            default:
                cout << "\nInvalid Choice! Try Again.\n";
        }

    } while (choice != 6);

    return 0;
}
