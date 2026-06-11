#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class BankAccount {
public:
    int accNo;
    string name;
    float balance;
};

void createAccount() {
    BankAccount acc;

    cout << "\nEnter Account Number: ";
    cin >> acc.accNo;

    cout << "Enter Customer Name: ";
    cin.ignore();
    getline(cin, acc.name);

    cout << "Enter Initial Balance: ";
    cin >> acc.balance;

    ofstream file("accounts.txt", ios::app);

    file << acc.accNo << endl;
    file << acc.name << endl;
    file << acc.balance << endl;

    file.close();

    cout << "\nAccount Created Successfully!\n";
}

void viewAccounts() {
    BankAccount acc;
    ifstream file("accounts.txt");

    cout << "\n===== ACCOUNT DETAILS =====\n";

    while (file >> acc.accNo) {
        file.ignore();
        getline(file, acc.name);
        file >> acc.balance;

        cout << "\nAccount No : " << acc.accNo;
        cout << "\nName       : " << acc.name;
        cout << "\nBalance    : Rs." << acc.balance;
        cout << "\n---------------------------";
    }

    file.close();
}

void searchAccount() {
    int searchNo;
    bool found = false;

    BankAccount acc;
    ifstream file("accounts.txt");

    cout << "\nEnter Account Number: ";
    cin >> searchNo;

    while (file >> acc.accNo) {
        file.ignore();
        getline(file, acc.name);
        file >> acc.balance;

        if (acc.accNo == searchNo) {
            cout << "\nAccount Found!";
            cout << "\nName    : " << acc.name;
            cout << "\nBalance : Rs." << acc.balance;
            found = true;
            break;
        }
    }

    if (!found)
        cout << "\nAccount Not Found!";

    file.close();
}

void depositMoney() {
    int searchNo;
    float amount;
    bool found = false;

    cout << "\nEnter Account Number: ";
    cin >> searchNo;

    cout << "Enter Amount to Deposit: ";
    cin >> amount;

    BankAccount acc;

    ifstream file("accounts.txt");
    ofstream temp("temp.txt");

    while (file >> acc.accNo) {
        file.ignore();
        getline(file, acc.name);
        file >> acc.balance;

        if (acc.accNo == searchNo) {
            acc.balance += amount;
            found = true;
        }

        temp << acc.accNo << endl;
        temp << acc.name << endl;
        temp << acc.balance << endl;
    }

    file.close();
    temp.close();

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (found)
        cout << "\nAmount Deposited Successfully!";
    else
        cout << "\nAccount Not Found!";
}

void withdrawMoney() {
    int searchNo;
    float amount;
    bool found = false;

    cout << "\nEnter Account Number: ";
    cin >> searchNo;

    cout << "Enter Amount to Withdraw: ";
    cin >> amount;

    BankAccount acc;

    ifstream file("accounts.txt");
    ofstream temp("temp.txt");

    while (file >> acc.accNo) {
        file.ignore();
        getline(file, acc.name);
        file >> acc.balance;

        if (acc.accNo == searchNo) {
            if (amount <= acc.balance) {
                acc.balance -= amount;
                cout << "\nWithdrawal Successful!";
            } else {
                cout << "\nInsufficient Balance!";
            }
            found = true;
        }

        temp << acc.accNo << endl;
        temp << acc.name << endl;
        temp << acc.balance << endl;
    }

    file.close();
    temp.close();

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (!found)
        cout << "\nAccount Not Found!";
}

int main() {
    int choice;

    do {
        cout << "\n\n===== BANK MANAGEMENT SYSTEM =====";
        cout << "\n1. Create Account";
        cout << "\n2. View All Accounts";
        cout << "\n3. Search Account";
        cout << "\n4. Deposit Money";
        cout << "\n5. Withdraw Money";
        cout << "\n6. Exit";
        cout << "\nEnter Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                createAccount();
                break;

            case 2:
                viewAccounts();
                break;

            case 3:
                searchAccount();
                break;

            case 4:
                depositMoney();
                break;

            case 5:
                withdrawMoney();
                break;

            case 6:
                cout << "\nThank You!";
                break;

            default:
                cout << "\nInvalid Choice!";
        }

    } while (choice != 6);

    return 0;
}