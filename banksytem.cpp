#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>
#include <conio.h>
#include <iomanip>
#include <time.h>
using namespace std;
class account
{
private:
    int id;
    string names, phone, passwrd;
    float balance;

public:
    void menu();
    void createAccount();
    void viewAccount();
    void viewALLAccounts();
    void updateAccount();
    void deposit();
    void withdraw();
    void deleteAccount();
    void deleteAllAccounts();
};

void account::menu()
{
menu:
    cout << "********************************************************* \n";
    cout << "************     BASIC BANK SYSTEM     ****************** \n";
    cout << "************ 1. Menu                   ****************** \n";
    cout << "************ 2. Create account         ****************** \n";
    cout << "************ 3. View account           ****************** \n";
    cout << "************ 4. View All accounts      ****************** \n";
    cout << "************ 5. Update account         ****************** \n";
    cout << "************ 6. Deposit on account     ****************** \n";
    cout << "************ 7. Withdraw account       ****************** \n";
    cout << "************ 8. Delete account         ****************** \n";
    cout << "************ 9. Delete all accounts    ****************** \n";
    cout << "************ 10. Exit                   ****************** \n";
    cout << "********************************************************* \n";

    int choice = 1;

    cout << "\n Your choice:\n";
    cin >> choice;

    switch (choice)
    {
    case 1:
        menu();
        break;
    case 2:
        createAccount();
        break;
    case 3:
        viewAccount();
        break;
    case 4:
        viewALLAccounts();
        break;
    case 5:
        updateAccount();
        break;
    case 6:
        deposit();
        break;
    case 7:
        withdraw();
        break;
    case 8:
        deleteAccount();
    case 9:
        deleteAllAccounts();
        break;
    case 10:
        exit(0);
    default:
        cout << "Invalid input!\n";
    }
    if (choice != 8)
        goto menu;
}
void account::createAccount()
{
    fstream file;
    file.open("AccountRecords.txt", ios::in | ios::app | ios::out);
    if (!file)
    {
        cout << "No contents in the file\n";
        file.close();
    }
    else
    {
        cout << "Enter your names";
        // getline(cin,names);
        cin >> names;
        cout << "Enter password";
        cin >> passwrd;

        cout << "Enter phone number";
        cin >> phone;

        srand(time(0));
        id = rand() % 100;
        balance = 0.00;

        file << std::setw(10) << id << std::setw(10) << names << std::setw(10) << passwrd << std::setw(10) << phone << std::setw(10) << balance << endl;
        file.close();
        cout << "Your Id is: " << id;
    }
}
void account::viewALLAccounts()
{
    int id;
    string passwrd;
    cout << "Enter id\n";
    cin >> id;
    cout << "Enter password\n";
    cin >> passwrd;
    if (id == 1 && passwrd == "admin")
    {
        ifstream file("AccountRecords.txt");
        if (!file)
            cout << "File is empty!";
        else
        {
            cout << "Oder of records: Id  |  names  |  phone  | baalance\n";
            file >> id >> names >> passwrd >> phone >> balance;
            while (!file.eof())
            {
                cout << id << "  " << names << "    " << passwrd << "  " << phone << "   " << balance << endl;
                file >> id >> names >> passwrd >> phone >> balance;
            }
        }
    }
    else
    {
        cout << "You are not allowed to do this operation";
    }
}
void account::viewAccount()
{
    string userpasswrd;
    int userid;
    cout << "Enter your Id\n";
    cin >> userid;
    cout << "Enter password\n";
    cin >> userpasswrd;
    ifstream file("AccountRecords.txt");
    if (!file)
        cout << "Error in opening file";
    else
    {
        file >> id >> names >> passwrd >> phone >> balance;
        int flag = 0;
        while (!file.eof())
        {
            if (userid == id && userpasswrd == passwrd)
            {
                cout << "Your account details: id | names | password | phone | balance: \n";
                cout << id << "   " << names << "   " << passwrd << "   " << phone << "   " << balance << endl;

                flag++;
                break;
            }
            file >> id >> names >> passwrd >> phone >> balance;
        }
        if (flag == 0)
            cout << "Invalid cridentials";
    }
}
void account::updateAccount()
{
    fstream file1, filetemp;
    file1.open("AccountRecords.txt", ios::in);
    if (!file1)
        cout << "Error opening file\n";
    else
    {
        string userpasswrd;
        int userid;
        cout << "Enter your Id\n";
        cin >> userid;
        cout << "Enter password\n";
        cin >> userpasswrd;

        filetemp.open("temporary.txt", ios::out);
        int flag = 0;
        file1 >> id >> names >> passwrd >> phone >> balance;
        while (!file1.eof())
        {
            if (id == userid && passwrd == userpasswrd)
            {
                cout << "Current credentials \"names | password | phone \"\n";
                cout << names << "  " << passwrd << "   " << phone << endl;

                string nnames, npasswrd, nphone;

                cout << "Enter new name";
                cin >> nnames;
                cout << "Enter new password";
                cin >> npasswrd;

                cout << "Enter new  phone number";
                cin >> nphone;
                names = nnames;
                phone = nphone;
                passwrd = npasswrd;
                id = id * 1;
                balance = balance * 1;
                flag++;
                filetemp << std::setw(10) << id << std::setw(10) << names << std::setw(10) << passwrd << std::setw(10) << phone << std::setw(10) << balance << endl;
            }
            else
            {
                filetemp << std::setw(10) << id << std::setw(10) << names << std::setw(10) << passwrd << std::setw(10) << phone << std::setw(10) << balance << endl;
            }

            file1 >> id >> names >> passwrd >> phone >> balance;
        }
        file1.close();
        filetemp.close();
        if (flag == 0)
        {
            cout << "Invalid cridentials";
            remove("temporary.txt");
        }
        else
        {
            cout << "successfully updated the record!\n";
            cout << (rename("AccountRecords.txt", "readme.txt") == -1);
            cout << (rename("temporary.txt", "AccountRecords.txt") != -1);
        }
    }
}
void account::deposit()
{
    fstream file, tempfile;
    file.open("AccountRecords.txt", ios::in);
    if (!file)
        cout << "Error opening file";
    else
    {
        float userid;
        string userpasswrd;
        cout << "Enter id\n";
        cin >> userid;
        cout << "Enter password\n";
        cin >> userpasswrd;
        int flag = 0;

        tempfile.open("temp.txt", ios::out);

        file >> id >> names >> passwrd >> phone >> balance;
        while (!file.eof())
        {
            if (id == userid && passwrd == userpasswrd)
            {
                promt:
                float nbal = 0;            
                cout << "Enter new amount!\n";
                cin >> nbal;
                if(nbal<=0){
                    cout<<"Please put valid amount!\n";
                    goto promt;
                }
                balance += nbal;
                flag++;
                cout<<"New Balance: "<<balance<<endl;
            }
            tempfile << std::setw(10) << id << std::setw(10) << names << setw(10) << passwrd << setw(10) << phone << setw(10) << balance << endl;
            file >> id >> names >> passwrd >> phone >> balance;
        }
        file.close();
        tempfile.close();
        if (flag == 0)
        {
            cout << "Invalid credentials";
            remove("temp.txt");
        }
        else
        {
            remove("AccountRecords.txt");
            rename("temp.txt", "AccountRecords.txt");
        }
    }
}
void account::withdraw()
{
    fstream file, tempfile;
    file.open("AccountRecords.txt", ios::in);
    if (!file)
        cout << "Error opening file";
    else
    {
        float userid;
        string userpasswrd;
        cout << "Enter id\n";
        cin >> userid;
        cout << "Enter password\n";
        cin >> userpasswrd;
        int flag = 0;

        tempfile.open("temp.txt", ios::out);

        file >> id >> names >> passwrd >> phone >> balance;
        while (!file.eof())
        {
            if (id == userid && passwrd == userpasswrd)
            {
                float nbal = 0;
                prompt:
                cout << "Enter new amount!\n";
                cin >> nbal;
                if(nbal<=0){
                    cout<<"Please enter valid amount!( >0)\n";
                    goto prompt;
                }else if(nbal>balance){
                    cout<<"You do not have enough Money on you account. Balance :"<<balance<<endl;
                    goto prompt;
                }
                balance += nbal;
                flag++;
                cout<<"New Balance: "<<balance<<endl;
            }
            tempfile << std::setw(10) << id << std::setw(10) << names << setw(10) << passwrd << setw(10) << phone << setw(10) << balance << endl;
            file >> id >> names >> passwrd >> phone >> balance;
        }
        file.close();
        tempfile.close();
        if (flag == 0)
        {
            cout << "Invalid credentials";
            remove("temp.txt");
        }
        else
        {
            remove("AccountRecords.txt");
            rename("temp.txt", "AccountRecords.txt");
        }
    }
}
void account::deleteAccount()
{
    fstream file, tempfile;
    file.open("AccountRecords.txt", ios::in);
    if (!file)
        cout << "Unable to open file";
    else
    {
        char confirm = 'n';

        int userid, flag = 0;
        cout << "Enter the id of account you want to delete:\n";
        cin >> userid;
        tempfile.open("temp.txt", ios::out);
        file >> id >> names >> passwrd >> phone >> balance;
        while (!file.eof())
        {
            if (id == userid)
            {
                cout << "Are you sure you want to delete this record? y/n \n";
                cin >> confirm;
                if (confirm == 'y')
                    flag++;
                else
                {
                    cout << "Action cancel\n";
                    flag = 0;
                    break;
                }
            }
            else
            {
                tempfile << setw(10) << id << setw(10) << names << setw(10) << passwrd << setw(10) << phone << setw(10) << balance << endl;
            }
            file >> id >> names >> passwrd >> phone >> balance;
        }
        file.close();
        tempfile.close();
        if (flag == 0)
        {
            cout << "Delete operation failed/canceled";
            remove("temp.txt");
        }
        else
        {
            remove("AccountRecords.txt");
            rename("temp.txt", "AccountRecords.txt");
        }
    }
}
void account::deleteAllAccounts()
{
    fstream file, tempfile;
    file.open("AccountRecords.txt", ios::out);
    if (!file)
        cout << "Unable to open file";
    else
    {
        int userid;
        string userpasswrd;
        cout << "Enter id\n";
        cin >> userid;
        cout << "Enter password \n";
        cin >> userpasswrd;
        if (userid == 1 && userpasswrd == "admin")
        {
            char confirm = 'n';
            cout << "Are you sure you wantto delete all records? y/n";
            cin >> confirm;
            if (confirm == 'y')
            {
                file << "";
            }
        }else{
            cout<<"UnAuthorized!\n";
        }

        file.close();
        // cout<< "Lets see!\n";
    }
}
int main()
{
    account account;
    account.menu();
    return 0;
}
