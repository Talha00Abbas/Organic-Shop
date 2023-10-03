#include <fstream>
#include <limits>
#include<iostream>
#include<string>
#include<cstdlib>
#include <cstring>
#include<stdio.h>
#include "Amount.h"
#include "Mall.h"

#define MAX_FEEDBACK_LEN 120 // Maximum length of your feedback can't be more than 120

using namespace std;
void BrowseCatalog();
void customer();
void FeedBack();
void AddToCart();

#pragma region Management Fuctions


fstream f;
mall m;
float cost = 0;
int cash = 1000;

void menu()
{
    cout << "\n\t";
    system("color e4");
    cout << setw(4) << "P No" << setw(20) << "Product Name" << setw(8) << "Price" << setw(10) << "Discount" << setw(10) << "Quantity";
    cout << "\n\t--------------------------------------------\n\t";
}

void enter()
{
    system("cls");
    system("color e4");

    f.open("mall.txt", ios::out | ios::app);
    m.getdata();
    f.write((char*)&m, sizeof(mall));
    f.close();

    cout << "\n\n\tProduct has been created...!!! ";

}

void display()
{
    system("color e4");
    cout << "\n\n\t\tDISPLAYING ALL RECORDS !!!\n\n";

    f.open("mall.txt", ios::in);
    menu();

    while (f.peek() != EOF)
    {
        f.read((char*)&m, sizeof(mall));
        m.showdata();
    }
    f.close();

}

void search()
{
    int no, flag = 0;
    system("cls");
    system("color e4");

    cout << "\n\n\tEnter the Product No. of the Product to be searched: ";
    cin >> no;

    f.open("mall.txt", ios::in);
    menu();

    while (f.read((char*)&m, sizeof(mall)))
    {
        if (m.retpno() == no)
        {
            m.showdata();
            flag = 1;
        }
    }
    f.close();

    if (flag == 0)
        cout << "\n\n\tRecord does not exist...!!!";

}

void update()
{
    int no, found = 0;
    system("cls");
    system("color e4");

    cout << "\n\n\tTo Update...Enter The Product No: ";
    cin >> no;

    f.open("mall.txt", ios::in | ios::out);
    menu();

    while (f.read((char*)&m, sizeof(mall)) && found == 0)
    {
        if (m.retpno() == no)
        {
            m.showdata();
            m.getdata();

            int pos = -1 * sizeof(m);
            f.seekp(pos, ios::cur);
            f.write((char*)&m, sizeof(mall));

            cout << "\n\n\t Record has been Updated...!!!";
            found = 1;
        }
    }
    f.close();

    if (found == 0)
        cout << "\n\n\tRecord Not Found ";

}

void erase()
{
    int no;
    system("cls");
    system("color e4");

    cout << "\n\n\n\tTo Delete...Enter The product No: ";
    cin >> no;

    f.open("mall.txt", ios::in | ios::out);
    fstream ft;
    ft.open("temp.txt", ios::out);
    f.seekg(0, ios::beg);

    while (f.read((char*)&m, sizeof(mall)))
    {
        if (m.retpno() != no)
        {
            ft.write((char*)&m, sizeof(mall));
        }
    }
    ft.close();
    f.close();

    remove("mall.txt");
    rename("temp.txt", "mall.txt");
    cout << "\n\n\tRecord  has been Deleted...!!!";
    display();

}

void place_order()
{
    int  order[30], quan[30], i = 0, quant[30], totalquant[30];
    float amt, damt, total = 0;
    char ch = 'Y';
   

    system("cls");
    system("color e4");
    display();

    cout << "\n\n\t============================";
    cout << "\n\t      PLACE YOUR ORDER";
    cout << "\n\t============================\n";

    do
    {
        cout << "\n\n\tEnter The Product No: ";
        cin >> order[i];
        cout << "\tQuantity: ";
        cin >> quan[i];
        totalquant[i] = m.retquantity();
        quant[i] = totalquant[i];
        
        i++;
        
        cout << "\n\tDo you want to order another product ?(y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');

    cout << "\n\n\tThank You...!!!";


    system("cls");
    system("color 70");

    cout << "\n\n\t\t************************BILL************************\n\n\t\t";
    cout << setw(4) << "P No" << setw(20) << "Product Name" << setw(10) << "Quantity" << setw(8) << "Price" << setw(8) << "Amount" << setw(10) << "Discount" << endl;
    cout << "\t\t------------------------------------------------------------\n\t\t";

    for (int x = 0; x <= i; x++)
    {
        f.open("mall.txt", ios::in);
        f.read((char*)&m, sizeof(mall));

        while (f)
        {
            if (m.retpno() != order[x])
            {
                amt = 0;
                damt = 0;
                
            }
            else
            {
                amt = m.retprice() * quan[x];
                damt = amt - (amt * m.retdis() / 100);
                
                cout << setw(4) << order[x] << setw(20) << m.retname() << setw(10) << quan[x] << setw(8) << m.retprice() << setw(8) << amt << setw(10) << damt << "\n\t\t";
                total += damt;
                totalquant[x] -= quan[x];
               
            }



            f.read((char*)&m, sizeof(mall));
        }
        f.close();
    }
    cost = total;
    cout << "\n\t\t--------------------------------------------------------------";
    cout << "\n\t\tThank You For The Purchase...Go To Checkout Please...............TOTAL = " << "Rs." << total;
    cout << "\n\t\t--------------------------------------------------------------";

}

int Checkout(int payment)
{
    if (payment < cost)
    {
        cout << "\n\n\t\tYou don't have enough money. SORRY!!!" << endl;
        cout << "Your balance is " << payment << endl;
        return 0;
    }
    else
    {



        cout << "\n\n\t\tYour Total Is " << cost << " Rs. How would you like to Pay?" << endl;
        cout << "\n\n\t\t1. Cash" << endl;
        cout << "\n\n\t\t2. Credit Card" << endl;
        cout << "\n\n\t\t3. Easypaisa" << endl;
        int opt = 0;
        cin >> opt;

        if (opt == 1)
        {
            payment -= cost + 30;
        }
        else
        {
            payment -= cost;
        }
        
        return payment;
    }
    
}   


#pragma endregion


void admin()
{
    while (1)
    {
        cout << "\n\t\t\t==============================\n";
        cout << "\n\t\t\t     WELCOME TO THE SHOP  \n";
        cout << "\n\t\t\t==============================\n\n";
        cout << "\n\t\t\t* * * * * * * * * * * * * * * *\n";
        cout << "\n\n\t\t\t1. Add Employee\n\n\t\t\t2. Add Product\n\n\t\t\t3. Show profit\n\n\t\t\t4. Search Product Details\n\n\t\t\t5. Search Employee Details\n\n\t\t\t6. Modify Product Details\n\n\t\t\t7. Modify Employee Details\n\n\t\t\t8. Check Feedback\n\n\t\t\t9. Delete Product\n\n\t\t\t10. Exit\n";
        cout << "\n\n\t\t\tSelect your choice\n";
        int u;
        cin >> u;
        if (u == 1)
        {
            amount a;
            /*a.show();*/
            a.add();
        }
        else if (u == 2)
        {
            enter();
        }
        else if (u == 3)
        {
            amount d;
            d.show();
        }
        else if (u == 4)
        {
            search();
        }
        else if (u == 5)
        {
            char eid[20];
            char d;
            cout << "\nINPUT employee ID to search\n";
            cin >> eid;
            char file[20];
            strcpy_s(file, eid);
            strcat_s(file, ".txt");
            ifstream y(file);
            if (!y)
            {
                cout << "file couldn't be opened. employee ID not found. \n";
            }
            while (y)
            {
                y.get(d);
                cout << d;
            }

            y.close();
        }
        else if (u == 6)
        {
            /*amount u;
            u.update_item();*/
            update();
        }
        else if (u == 7)
        {
            amount v;
            v.update_emp();
        }
        else if (u == 8)
        {

            cout << "\n\t\t\t==============================\n";
            cout << "\n\t\t\t     Current Feedback  \n";
            cout << "\n\t\t\t==============================\n\n";

            char c;
            //Check Feedback
            ifstream x("Feedback.txt");
            if (!x)
            {
                cout << "file couldn't be opened. product ID not found. \n";
            }
            while (x)
            {
                x.get(c);
                cout << c;
            }

            cout << "\n\t\t\t==============================\n\n";
            cout << "\n\t\t\t==============================\n\n";

        }
        else if (u == 9)
        {
            erase();
        }
        else if (u == 10)
        {
            break;
        }
        else cout << "Invalid option. Please select one of the available options\n";
    }

}

#pragma region Login/Register Area
string usn;
int tm;
void valid(string str)
{
    string dir, user;
    ifstream file;
    dir = str + ".txt";
    file.open(dir.c_str());
    if (!file.is_open() && file.fail())
    {
        //file.close();
        return;
    }
    else
    {
        tm++;
        if (tm == 3)
        {
            cout << "\nThis username already exists\nPlease try Again.";
            //file.close();
            return;
        }
        cout << "\nThis username already exists!\nCreate a username:";
        cin >> usn;
        //file.close();
        valid(usn);
    }
}

void LoginAndRegister() 
{
    int choice, i, exit = 0;
    string ans, psd, name, fname, bio, usern, pw, line, nusn;
    ofstream fileo;
    ifstream filei;
    cout << "----------------------------------------------Welcome to our system!------------------------------------------------------\n";
    while (exit == 0)
    {
        cout << "\nChoose one option:\n1. SignIn/LogIn(press 1 to select this)\n2. SignUp/Register(press 2 to select this)\n\npress any key and enter to exit\n";
        cin >> choice;
        if (choice == 1)
        {
            cout << "Enter your username:";
            cin >> usn;
            cout << "\nEnter your password:";
            cin >> psd;
            fname = usn + ".txt";
            filei.open(fname.c_str());
            if (!filei.is_open() && filei.fail())
            {
                cout << "\nYou are not registered, please register before logging in.\n";
                filei.close();
                continue;
            }
            getline(filei, usern);
            getline(filei, line);
            getline(filei, pw);
            if (usn == usern && psd == pw)
            {
                cout << "\nYou are successfully logged in:)\n\n";
                cout << "User-name:" << usern << endl;
                cout << "Name:" << line << endl << endl;
                getline(filei, line);
                filei.close();  
                exit = 1;
            }
            else {
                cout << "\nWrong username or password!\nPlease try Again.\n";
            }
            cout << endl;
        }
        else if (choice == 2)
        {
            cout << "\nEnter your name:";
            cin.ignore();
            getline(cin, name);
            cout << "\nCreate a username:";
            cin >> usn;
            tm = 0;
            valid(usn);
            if (tm >= 3)
            {
                continue;
            }
            cout << "\nCreate a password:";
            cin >> psd;
            fname = usn + ".txt";
            //cout<<fname;
            fileo.open(fname.c_str());
            fileo << usn << endl << name << endl << psd << endl;
            cout << "\nYou are successfully registered:)";
            cout << "\nAdd to your bio and press enter when you are done:";
            cin.ignore();
            getline(cin, bio);
            fileo << bio << endl;
            cout << "\nYour bio is saved as: " << bio;
            fileo.close();
        }
        else
        {
            exit = 1;
        }
    }
    
}

#pragma endregion


int main() {
    system("color e4");
    int ch = 0;
    int startCheck = 0;
    char  username[20];
    char password[20];
    char pwd[20];
    while (1) {
        cout << "\n \t\t\t=========================\n";
        cout << "\n\t\t\tWELCOME TO MY SHOP  \n";
        cout << "\n \t\t\t=========================\n\n";
        cout << "\n \t\t\t* * * * * * * * * * * * ";
        cout << "\n\t\t\t  1. ENTER SYSTEM";
        cout << "\n\t\t\t  2. EXIT";
        cout << "\n\t\t\t* * * * * * * * * * * *\n";
        cout << "\n\t\t\t Enter Your choice: ";
        cin >> startCheck;
        
        switch (startCheck)
        {
        case 1:
            int authCheck;
            cout << endl << "Are you an Admin or a Customer \n\nPress 1 for Admin \nPress 2 for Customer " << endl;
            cin >> authCheck;
            if (authCheck == 1)
            {
                cout << "Enter UserName " << endl;
                cin >> username;

                if (username[0] == 'a' && username[1] == 'd' && username[2] == 'm' && username[3] == 'i' && username[4] == 'n')
                {
                    ch = 1;
                }
            }

            if (authCheck == 2)
            {
                ch = 2;
                LoginAndRegister();
            }
            break;
        case 2:
            exit(0);
            break;
        default:
            cout << "Error Error Error Error " << endl;
            break;
        }

        

        // For Admin or Customer Check

        switch (ch) {
        case 1:
            admin();
            break;
        case 2:
            customer();
            break;
        case 3:
            exit(0);
            break;
        default:
            cout << "CH is " << ch << endl;
            cout << "UnAuthorized Access\n";
            break;
        }
    }
    return 0;
}


#pragma region Customer Workspace

void customer()
{

    while (1)
    {
        cout << "\n\t\t\t==============================\n";
        cout << "\n\t\t\t     WELCOME TO THE SHOP  \n";
        cout << "\n\t\t\t==============================\n\n";
        cout << "\n\t\t\t* * * * * * * * * * * * * * * *\n";
        cout << "\n\t\t\t1. Browse Catalog\n\n\t\t\t2. Add to Cart\n\n\t\t\t3. Checkout & Payment\n\n\t\t\t4. FeedBack\n\n\t\t\t5. Exit\n";
        cout << "\n\n\t\t\tSelect your choice  : ";
        int u;
        cin >> u;
        if (u == 1)
        {
            //Browse Catalog
            display();
        }
        else if (u == 2)
        {
            // Add to Cart
            place_order();
        }
        else if (u == 3)
        {
            // Checkout
            Checkout(cash);
        }
        else if (u == 4)
        {
            FeedBack();
            break;
        }
        else if (u == 5)
        {
            break;
        }
        else cout << "Invalid option. Please select one of the available options\n";
    }

}



void BrowseCatalog()
{
    int browse = 0;
    int lineCheck = 0;


    cout << "\n\n\t\t\tWhich Section do you want to Browse" << endl;
    while (browse != 5)
    {
        cout << "\n\n\t\t\t1- Perishible Goods\n\n\t\t\t2- Non-Perishible Goods\n\n\t\t\t3- Personal Hygeine\n\n\t\t\t4- Household Items\n\n\t\t\t5- Exit" << endl;
        cin >> browse;

        switch (browse)
        {
        case 1:
        {

            for (int i = 10; i < 18; i++)
            {
                string tempstr = to_string(i);
                char const* id = tempstr.c_str();
                char c;
                char file[20];
                strcpy_s(file, id);
                strcat_s(file, ".txt");
                fstream x(file);
                if (!x)
                {
                    cout << "file couldn't be opened. product ID not found. \n";
                }
                while (lineCheck < 5)
                {
                    if (lineCheck != 3)
                    {
                        x.get(c);
                        cout << c;
                    }
                    if (c == '\n') 
                    {
                        lineCheck += 1;
                    }
                }
                lineCheck = 0;

                x.close();
                cout << "\n-------------------------------------------------------\n";
            }

            cout << "\n\n\t\t\tWould You Like to browse more\n" << endl;
            break;
        }
        case 2:
        {

            for (int i = 20; i < 24; i++)
            {
                string tempstr = to_string(i);
                char const* id = tempstr.c_str();
                char c;
                char file[20];
                strcpy_s(file, id);
                strcat_s(file, ".txt");
                ifstream x(file);
                if (!x)
                {
                    cout << "file couldn't be opened. product ID not found. \n";
                }
                while (lineCheck < 5)
                {
                    if (lineCheck != 3)
                    {
                        x.get(c);
                        cout << c;
                    }
                    if (c == '\n')
                    {
                        lineCheck += 1;
                    }
                }
                lineCheck = 0;
                x.close();
                cout << "\n-------------------------------------------------------\n";
            }

            cout << "\n\n\t\t\tWould You Like to browse more\n" << endl;
            break;
        }
        case 3:
        {

            for (int i = 30; i < 32; i++)
            {
                string tempstr = to_string(i);
                char const* id = tempstr.c_str();
                char c;
                char file[20];
                strcpy_s(file, id);
                strcat_s(file, ".txt");
                ifstream x(file);
                if (!x)
                {
                    cout << "file couldn't be opened. product ID not found. \n";
                }
                while (lineCheck < 5)
                {
                    if (lineCheck != 3)
                    {
                        x.get(c);
                        cout << c;
                    }
                    if (c == '\n')
                    {
                        lineCheck += 1;
                    }
                }
                lineCheck = 0;
                x.close();
                cout << "\n-------------------------------------------------------\n";
            }

            cout << "\n\n\t\t\tWould You Like to browse more\n" << endl;
            break;
        }
        case 4:
        {

            for (int i = 40; i < 42; i++)
            {
                string tempstr = to_string(i);
                char const* id = tempstr.c_str();
                char c;
                char file[20];
                strcpy_s(file, id);
                strcat_s(file, ".txt");
                ifstream x(file);
                if (!x)
                {
                    cout << "file couldn't be opened. product ID not found. \n";
                }
                while (lineCheck < 5)
                {
                    if (lineCheck != 3)
                    {
                        x.get(c);
                        cout << c;
                    }
                    if (c == '\n')
                    {
                        lineCheck += 1;
                    }
                }
                lineCheck = 0;
                x.close();
                cout << "\n-------------------------------------------------------\n";
            }

            cout << "\n\n\t\t\tWould You Like to browse more\n" << endl;
            break;
        }

        case 5:
            break;
        default:
            cout << "Enter A valid Input" << endl;
            break;
        }
    }
}


void FeedBack() 
{

    char name[20];
    char feedback[MAX_FEEDBACK_LEN];

    cout << "\nEnter Your Name: \n";
    cin >> name;

    cout << "\nEnter Your Complaint: \n";
    cin >> feedback;

    //File Feedback
    char file[20];
    ofstream f("Feedback.txt", ios::app);
    f << "\nCustomer Name: " << name<<"\nFeedBack : "<<feedback<<"\n";
    f.close();

}


void AddToCart() 
{
#pragma region All the Catalog

    int lineCheck = 0;

    for (int i = 10; i < 18; i++)
    {
        string tempstr = to_string(i);
        char const* id = tempstr.c_str();
        char c;
        char file[20];
        strcpy_s(file, id);
        strcat_s(file, ".txt");
        fstream x(file);
        if (!x)
        {
            cout << "file couldn't be opened. product ID not found. \n";
        }
        while (lineCheck < 5)
        {
            if (lineCheck != 3)
            {
                x.get(c);
                cout << c;
            }
            if (c == '\n')
            {
                lineCheck += 1;
            }
        }
        lineCheck = 0;

        x.close();
        cout << "\n-------------------------------------------------------\n";
    }

    for (int i = 20; i < 24; i++)
    {
        string tempstr = to_string(i);
        char const* id = tempstr.c_str();
        char c;
        char file[20];
        strcpy_s(file, id);
        strcat_s(file, ".txt");
        ifstream x(file);
        if (!x)
        {
            cout << "file couldn't be opened. product ID not found. \n";
        }
        while (lineCheck < 5)
        {
            if (lineCheck != 3)
            {
                x.get(c);
                cout << c;
            }
            if (c == '\n')
            {
                lineCheck += 1;
            }
        }
        lineCheck = 0;
        x.close();
        cout << "\n-------------------------------------------------------\n";
    }
    

    for (int i = 30; i < 32; i++)
    {
        string tempstr = to_string(i);
        char const* id = tempstr.c_str();
        char c;
        char file[20];
        strcpy_s(file, id);
        strcat_s(file, ".txt");
        ifstream x(file);
        if (!x)
        {
            cout << "file couldn't be opened. product ID not found. \n";
        }
        while (lineCheck < 5)
        {
            if (lineCheck != 3)
            {
                x.get(c);
                cout << c;
            }
            if (c == '\n')
            {
                lineCheck += 1;
            }
        }
        lineCheck = 0;
        x.close();
        cout << "\n-------------------------------------------------------\n";
    }

    for (int i = 40; i < 42; i++)
    {
        string tempstr = to_string(i);
        char const* id = tempstr.c_str();
        char c;
        char file[20];
        strcpy_s(file, id);
        strcat_s(file, ".txt");
        ifstream x(file);
        if (!x)
        {
            cout << "file couldn't be opened. product ID not found. \n";
        }
        while (lineCheck < 5)
        {
            if (lineCheck != 3)
            {
                x.get(c);
                cout << c;
            }
            if (c == '\n')
            {
                lineCheck += 1;
            }
        }
        lineCheck = 0;
        x.close();
        cout << "\n-------------------------------------------------------\n";
    }

     



}


#pragma endregion


#pragma endregion

