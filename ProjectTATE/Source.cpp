#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
using namespace std;

class Transaction {
protected:
    double amount;
    string description;
public:
    Transaction(double amt, const string& des) {
        amount = amt;
        description = des;
    }
    virtual void display() {
        cout << setw(15) << amount << setw(20) << description << endl;
    }
};
class Income : public Transaction {
public:
    Income(double amt, const string& des) : Transaction(amt, des) {}
    void display() {
        cout << setw(15) << "������" << setw(20);
        Transaction::display();
    }
};
class Expenditure : public Transaction {
public:
    Expenditure(double amt, const string& des) : Transaction(amt, des) {}
    void display() {
        cout << setw(15) << "������" << setw(20);
        Transaction::display();
    }
};
class Investment {
protected:
    double amount;
    int duration;
public:
    Investment(double amt, int dur) {
        amount = amt;
        duration = dur;
    }
    virtual void display() {
        cout << setw(15) << amount << setw(15) << duration;
    }
    virtual double maturityAmount() {
        return amount;
    }
};
class SIP : public Investment {
private:
    double monthly;
public:
    SIP(double amt, int dur, double monAmt) : Investment(amt, dur) {
        monthly = monAmt;
    }
    void display() {
        cout << setw(15) << "���� SIP";
        Investment::display();
        cout << setw(20) << "������� ����������: " << monthly << endl;
    }

    double maturityAmount() {
        double final = amount * pow(1 + (0.096 / 12), duration * 12);
        return final + (monthly * 12 * duration);
    }
};
class FD : public Investment {
public:
    FD(double amt, int dur) : Investment(amt, dur) {}
    void display() {
        cout << setw(15) << "�������� �������";
        Investment::display();
        cout << endl;
    }
    double maturityAmount() {
        return amount * pow((1 + 0.071), duration);
    }
};
class FinanceManager {
public:
    Transaction* transactions[100];
    Investment* investments[50];
    int tcount;
    int icount;
    FinanceManager() {
        tcount = 0;
        icount = 0;
    }
    void addTransaction(Transaction* t) {
        transactions[tcount++] = t;
    }
    void addInvestment(Investment* i) {
        investments[icount++] = i;
    }
    void displayRecord(double balance) {
        cout << "-----------------------------------\n";
        cout << "|        ����� �������           |\n";
        cout << "-----------------------------------\n";
        cout << "\n||--������--: " << balance << "||" << endl;

        cout << "\n--�����������--: \n";
        cout << setw(15) << "����" << setw(20) << "��������" << endl;
        for (int i = 0; i < tcount; i++) {
            transactions[i]->display();
        }

        cout << "\n--����������--\n";
        cout << setw(15) << "����" << setw(15) << "���������������" << setw(20) << "���";
        cout << endl;
        for (int i = 0; i < icount; i++) {
            investments[i]->display();
        }
    }
};
class User {
public:
    FinanceManager manager;
    double balance;
    User(double initialBalance) {
        balance = initialBalance;
    }
    void operations() {
        int choice = -1;
        while (choice != 0) {
            cout << "\n--�����--\n";
            cout << "1. ����� �� ������\n";
            cout << "2. ����� �� ������\n";
            cout << "3. ������� ����������\n";
            cout << "4. ���������� �� ���������\n";
            cout << "5. ���������� �� ������������\n";
            cout << "0. �����\n";
            cout << "�������� �����: ";
            cin >> choice;
            switch (choice) {
            case 1: {
                double amt;
                string desc;
                cout << "�������� ����: ";
                cin >> amt;
                cout << "�������� ��������: ";
                cin.ignore();
                getline(cin, desc);
                manager.addTransaction(new Income(amt, desc));
                balance += amt;
                break;
            }
            case 2: {
                double amt;
                string desc;
                cout << "�������� ����: ";
                cin >> amt;
                if (balance - amt < 1000) {
                    cout << "������: �������� �� ���� �� ���� ��� 1000.\n";
                    continue;
                }
                cin.ignore();
                cout << "�������� ��������: ";
                getline(cin, desc);
                manager.addTransaction(new Expenditure(amt, desc));
                balance -= amt;
                break;
            }
            case 3: {
                makeInvestment();
                break;
            }
            case 4: {
                manager.displayRecord(balance);
                break;
            }
            case 5: {
                cout << "--���� �� �������--||\n";
                for (int i = 0; i < manager.icount; i++) {
                    Investment* inv = manager.investments[i];
                    cout << "\n���������� " << i + 1 << " : " << inv->maturityAmount() << " ��\n";
                    cout << "���������� (���, ����, ���������������):\n";
                    inv->display();
                }
                break;
            }
            case 0:
                break;
            default:
                cout << "\n���� ������ �����:(";
                break;
            }
        }
    }
    void makeInvestment() {
        int sub = -1;
        while (sub != 0) {
            cout << "\n��� ����������:\n";
            cout << "1. SIP\n";
            cout << "2. �������� �������\n";
            cout << "0. �����\n";
            cout << "�������� �����: ";
            cin >> sub;
            switch (sub) {
            case 1: {
                double amt, monthly;
                int dur;
                cout << "�������� ����: ";
                cin >> amt;
                if (balance - amt < 1000) {
                    cout << "������: ��������� ������: 1000\n";
                    return;
                }
                cout << "�������� ��������������� (� ������): ";
                cin >> dur;
                cout << "�������� ������� ����������: ";
                cin >> monthly;
                manager.addInvestment(new SIP(amt, dur, monthly));
                balance -= amt;
                break;
            }
            case 2: {
                double amt;
                int dur;
                cout << "�������� ����: ";
                cin >> amt;
                if (balance - amt < 1000) {
                    cout << "������: ��������� ������: 1000\n";
                    return;
                }
                cout << "�������� ��������������� (� ������): ";
                cin >> dur;
                manager.addInvestment(new FD(amt, dur));
                balance -= amt;
                break;
            }
            case 0:
                break;
            default:
                cout << "��������� �����.\n";
                break;
            }
        }
    }
};
int main() {
    cout << "---����� ����� � ��������� �� ���������� �� �������!---\n";
    User user(2000); // ��������� �� ���������� � ������� ������ 2000 ��.
    user.operations();
    return 0;
}
