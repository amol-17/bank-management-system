#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <ctime>

using namespace std;

class bank
{
    char c_name[50];
    long long bal;
    long long mob;
    char add[50];
    long long acno;
    char status;
    char actype;
    int pass;
    char time[50];

public:
    void set()
    {
        cout << "\n\n\t\tNOTE:\t * For Saving AccountInitial Amount Must Be Greater Than 500 .\n\t\t\t * For Current Account Initial Amount Must Be Greater Than 10000 ";
        cout << "\n\n\t\t\tEnter the Name of the Account holder : ";
        cin.ignore();
        cin.getline(c_name, 50);
        cout << "\n\t\t\tEnter The Initial amount : ";
        cin >> bal;
        cout << "\n\t\t\tEnter Your Mobile Number : ";
        cin >> mob;
        cout << "\n\t\t\tEnter Your Address: ";
        cin.ignore();
        cin.getline(add, 50);
        cout << "\n\t\t\tEnter Type of the Account (C/S) : ";
        cin >> actype;
    }

    void show()
    {

        cout << "\n\t\t\tAccount Holder Name : ";
        cout << c_name << endl;
        cout << "\t\t\tBalance amount : ";
        cout << bal << endl;
        cout << "\t\t\tMobile Number : ";
        cout << mob << endl;
        cout << "\t\t\tAddress : ";
        cout << add << endl;
        cout << "\t\t\tAccount No. : ";
        cout << acno << endl;
        cout << "\t\t\tAccount Status : ";
        cout << status << endl;
        cout << "\t\t\tType of Account : ";
        cout << actype << endl;
    }
    void setacno(int n)
    {
        acno = n;
    }
    void setstatus(char ch)
    {
        status = ch;
    }
    void setfirstpass(int n)
    {
        pass = n;
    }
    void setdeposit(int x)
    {
        bal += x;
    }
    void setwithdraw(int n)
    {
        if (actype == 's' || actype == 'S')
        {

            if ((bal - n) < 500)
            {
                cout << "Sorry, Left Amount Must Be Greater Than 500" << endl;
            }
            else
            {
                bal -= n;
            }
        }
        else
        {
            if ((bal - n) < 1000)
            {
                cout << "Sorry, Left Amount Must Be Greater Than 1000" << endl;
            }
            else
            {
                bal -= n;
            }
        }
    }
    void balupdate()
    {

        if (actype == 'c' || actype == 'C' || actype == 's' || actype == 'S')
        {

            if (actype == 'c' || actype == 'C')
            {
                if (bal <= 10000)
                {
                    cout << "\n\t\t\t\tInitial amount Must be Greater than 10000" << endl;
                    exit(0);
                }
            }
            else 
            {
                if (bal <= 500)
                {
                    cout << "\n\t\t\t\tInitial amount Must be Greater than 500" << endl;
                    exit(0);
                }
            }
        }
        else
        {
            cout << "\n\t\t\t\tInvalid Account Type(choice only 'C' or 'S') .." << endl;
            cout << "\n\t\t\t\t||retry||";
            exit(0);
        }
    }
    int getcheckpass()
    {
        return pass;
    }
    void setpass(int n)
    {
        pass = n;
    }
    void create();
    void display();
    void transfer();
};

void bank::create()
{

    fstream f;
    bank b1;
    f.open("records", ios::app);
    b1.set();
    f.seekg(0, ios::end);
    int p = f.tellg();
    int num = p / sizeof(b1);
    b1.setacno(num + 1);
    b1.setstatus('Y');
    b1.setfirstpass(num + 100);

    b1.balupdate();
    cout << "\n\n\t\t\t * " << b1.acno << " Is Your Account Number And ";
    cout << "\n\t\t\t * " << b1.pass << " Is Your Genreted Pin \n\t\t\tNever Share Your Pin With Anyone\n\t\t\tYou Can Modify It Later";

    f.write((char *)&b1, sizeof(b1));
    f.close();
    cout << "\n\n\t\t\tAccount Created.." << endl;
}

int main()
{
    int i, n, x, y;
    char ch;
    bank b1;
    cout << "\n\n\t\t\t\t\t======================\n";
    cout << "\t\t\t\tWelcome to NEERAV-MAALYA BANK";
    cout << "\n\t\t\t\t\t======================\n\n";
    cout << "\t\t\t\t\t    ::MAIN MENU::\n";
    cout << "\n\t\t\t\t1. NEW USER";
    cout << "\n\t\t\t\t2. EXISTING USER";
    cout << "\n\t\t\t\t0. EXIT";
    cout << "\n\n\t\t\t\tSelect Your Option (1,2 ,or 0): ";
    cin >> i;
    if (i == 1)
    {
        cout << "\n\t\t\t\tCREATING A ACCOUNT...";
        b1.create();
    }
    else if (i == 2)
    {

        fstream f;
        bank b1;
        int acno, pass1, newpass, c_newpass;
        int r, vpin;
        f.open("records", ios::in | ios::out);
        f.seekg(0, ios::end);
        int p = f.tellg();
        int num = p / sizeof(b1);
        if (num <= 0)
        {
            cout << "There Are 0 Accounts" << endl;
            cout << "Thanks For Coming To The NEERAV-MAALYA Bank" << endl;
        }
        else
        {
            system("CLS");
            cout << "\n\t\t\t1.Modify Pin";
            cout << "\n\t\t\t2.Login";
            cout << "\n\t\t\tSelect Your Option (1 or 2) : ";
            cin >> y;
            if (y == 1)
            {
                cout << "\n\t\t\t\tEnter Your Account No : ";
                cin >> acno;

                if (acno > num || acno == 0 || num == 0)
                {
                    cout << "\ninvalid account number" << endl;
                }
                else
                {

                    int pos = (acno - 1) * sizeof(b1);
                    f.seekg(pos);
                    f.read((char *)&b1, sizeof(b1));
                    cout << "\n\t\t\t\tEnter Your Old Pin : ";
                    cin >> pass1;
                    if (pass1 == b1.getcheckpass())
                    {
                        cout << "\n\t\t\tEnter Your New Pin : ";
                        cin >> newpass;
                        cout << "\n\t\t\tConfirm Your New Pin : ";
                        cin >> c_newpass;
                        if (c_newpass == newpass)
                        {
                            b1.setpass(newpass);
                            int pos1 = (acno - 1) * sizeof(b1);
                            f.seekp(pos1);
                            f.write((char *)&b1, sizeof(b1));
                            cout << "\n\n\t\t\tPIN UPDATED...\n\n";
                            f.close();
                        }
                        else
                        {
                            cout << "\n\t\t\tConfirmation Pin Not Match...\n\t\t\t!!RETRY!!\n\n";
                        }
                    }
                    else
                    {
                        cout << "\n\t\t\t\t!!Invalid Pin!!";
                        cout << "\n\t\t\t\t!!RETRY!!";
                    }
                }
            }
            if (y == 2)
            {

                cout << "\n\t\t\t\tEnter Your Account No : ";
                cin >> acno;

                if (acno > num || acno == 0 || num == 0)
                {
                    cout << "\ninvalid account number" << endl;
                }
                else
                {
                    int pos = (acno - 1) * sizeof(b1);
                    f.seekg(pos);
                    f.read((char *)&b1, sizeof(b1));
                    cout << "\n\t\t\t\tEnter Your 3 Digit Pin Code : ";
                    cin >> pass1;
                    if (pass1 == b1.getcheckpass())
                    {
                        do
                        {
                            system("CLS");
                            cout << "\n\n\t\t\t\t======================\n";
                            cout << "\t\t\t\t NEERAV-MAALYA Bank";
                            cout << "\n\t\t\t\t======================\n";
                            cout << "\t\t\t\t    ::MENU::\n";
                            cout << "\n\t\t\t\t1. DISPLAY ACCOUNT";
                            cout << "\n\t\t\t\t2. WITHDRAW AMOUNT";
                            cout << "\n\t\t\t\t3. DEPOSIT AMOUNT";
                            cout << "\n\t\t\t\t4. CLOSE AN ACCOUNT";
                            cout << "\n\t\t\t\t5. ACTIVATE ACCOUNT";
                            cout << "\n\t\t\t\t6. MONEY TRANSFER";
                            cout << "\n\n\t\t\t\tSelect Your Option (1-6): ";
                            cin >> n;

                            if (n == 1)
                                b1.show();
                            else if (n == 2)
                            {
                                cout << "\n\t\t\t\thow much amount do you wanted to withdraw : ";
                                cin >> x;
                                cout << "\n\t\t\tEnter PIN For Verification : ";
                                cin >> vpin;
                                if (vpin == b1.getcheckpass())
                                {
                                    b1.setwithdraw(x);
                                    int pos1 = (acno - 1) * sizeof(b1);
                                    f.seekp(pos1);
                                    f.write((char *)&b1, sizeof(b1));
                                    cout << "Amount Withdrawed..." << endl;
                                }
                                else
                                {
                                    cout << "\n\t\t\tInvalid PIN\n\t\t\t!!RETRY!!";
                                }
                            }
                            else if (n == 3)
                            {

                                cout << "\n\t\t\t\thow much amount do you wanted to deposit : ";
                                cin >> x;

                                b1.setdeposit(x);
                                int pos1 = (acno - 1) * sizeof(b1);
                                f.seekp(pos1);
                                f.write((char *)&b1, sizeof(b1));
                                cout << "Amount Deposited..." << endl;
                            }
                            else if (n == 4)
                            {
                                b1.setstatus('N');
                                int pos1 = (acno - 1) * sizeof(b1);
                                f.seekp(pos1);
                                f.write((char *)&b1, sizeof(b1));
                                cout << "\n\nAccount Deactivated .." << endl;
                            }

                            else if (n == 5)
                            {
                                b1.setstatus('Y');
                                int pos1 = (acno - 1) * sizeof(b1);
                                f.seekp(pos1);
                                f.write((char *)&b1, sizeof(b1));
                                cout << "\n\nAccount Activated .." << endl;
                            }

                            else if (n == 6)
                            {

                                cout << "\n\t\t\t\tEnter Receiver's Account No. : ";
                                cin >> r;
                                if (r > num || r == 0)
                                {
                                    cout << "\n\t\t\tReceiver's Account Does't Exist";
                                    cout << "\n\t\t\t\t!!RETRY!!";
                                    exit(0);
                                }
                                else
                                {

                                    int pos2 = (acno - 1) * sizeof(b1);
                                    f.seekg(pos2);
                                    f.read((char *)&b1, sizeof(b1));

                                    cout << "\n\t\t\t\tHow Much Amount Do You Wants To Transfer : ";
                                    cin >> x;
                                    cout << "\n\t\t\tEnter PIN For Verification : ";
                                    cin >> vpin;
                                    if (vpin == b1.getcheckpass())
                                    {
                                        b1.setwithdraw(x);
                                        int pos3 = (acno - 1) * sizeof(b1);
                                        f.seekp(pos3);
                                        f.write((char *)&b1, sizeof(b1));

                                        int pos4 = (r - 1) * sizeof(b1);
                                        f.seekg(pos4);
                                        f.read((char *)&b1, sizeof(b1));
                                        b1.setdeposit(x);
                                        int pos5 = (r - 1) * sizeof(b1);
                                        f.seekp(pos5);
                                        f.write((char *)&b1, sizeof(b1));

                                        cout << "\n\t\t\tRs." << x << " has been transfered to " << r;
                                        cout << "\n\t\t\tTRANSACTION SUCCESSFUL..." << endl;

                                        f.seekg(pos2);
                                        f.read((char *)&b1, sizeof(b1));
                                    }
                                    else
                                    {
                                        cout << "\n\t\t\tInvalid PIN\n\t\t\t!!RETRY!!";
                                    }
                                }
                            }
                            else
                            {
                                cout << "invalid choice";
                                exit(1);
                            }
                            cout << "do you want to continue(Y/N)...?\n";
                            fflush(stdin);
                            cin >> ch;
                        } while (ch != 'n' || ch != 'N');
                    }
                    else
                    {
                        cout << "\n\t\t\t\t!!Invalid Pin!!";
                        cout << "\n\t\t\t\t!!RETRY!!";
                    }
                }
            }
        }
        f.close();
    }
    else
    {
        cout << "\n\t\t\tNEERAV-MAALYA BANK THANK YOU";
        cout << "\n\t\t\tFOR VISITING";
        exit(0);
    }
}