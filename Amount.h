#pragma once
#include<fstream>
#include<iostream>
#include<string>
#include<cstdlib>
#include <cstring>
#include<stdio.h>

using namespace std;

class file {
public:
    file() {
        ofstream fout;
        fout.open("talha.txt");
        fout << "talha";
        fout.close();
    }
};
class earn {
public:
    double profit;
    void show()
    {
        ifstream x("$$$.txt");
        if (!x)
            cout << "PROFIT = 0 ";
        else {
            x >> profit;
            cout << "\nTOTAL STARTING PROFIT:  " << profit << endl;
            x.close();
        }

    }

};
class product :public virtual earn {
public:
    int quan;
    char name[20];
    char id[20];
    double percost;
    double persell;
    double cost;
    double sell;
    void cal()
    {
        cost = percost * quan;
        sell = persell * quan;
        profit = profit + (sell - cost) * 365;
    }
    void file();
    void get();

};
void product::get()
{
    int s;
    cout << "\nnumber of products produced?\n";
    cin >> s;
    for (int i = 0; i < s; i++)
    {
        cout << "\ninput product name: \n";
        cin >> name;
        cout << "\ninput product id: \n";
        cin >> id;
        cout << "\ninput cost price of product: \n";
        cin >> percost;
        cout << "\ninput selling price of product: \n";
        cin >> persell;
        cout << "\ntotal product quantity: \n";
        cin >> quan;
        cal();
        file();
    }

}
void product::file()
{
    char file[20];
    strcpy_s(file, id);
    strcat_s(file, ".txt");
    ofstream f(file);
    f << "\nproduct name: " << name << "\nproduct id: " << id << "\ncost price of product: " << percost << "\nselling price of product: " << persell << "\nquantity: " << quan << "\n total cost: " << cost << "\nsell: " << sell;
    f.close();
}

class staff :public virtual earn {
protected:
    double salary;
    char post[12];
    char empid[10];
    int postquan;
    void cal()
    {
        profit = (profit - salary * postquan) * 12;
    }
    void getstaff();
    void file();
};
void staff::getstaff()
{
    cout << "\ninput salary: \n";
    cin >> salary;
    cout << "\ninput number of employees: \n";
    cin >> postquan;
    for (int i = 0; i < postquan; i++)
    {
        cout << "input employee name\n";
        cin >> post;
        cout << "\ninput employee ID\n";
        cin >> empid;
        cal();
        file();
    }
}
void staff::file()
{
    char file[20];
    strcpy_s(file, empid);
    strcat_s(file, ".txt");
    ofstream f(file);
    f << "\nnumber of working employees: " << postquan << "\nemployee salary: " << salary << "\nemployee name :" << post << "\nemployee id: " << empid;
    f.close();
}

class amount :public staff, public product
{

public:
    void add();
    void update_item();
    void update_emp();

};
void amount::add()
{
    int ch;
    char name[20];
    while (1)
    {
        cout << "1.)Input for employee\n2.)Exit\n";
        cout << "Enter choice\n";
        cin >> ch;
        /*if (ch == 1) {
            get();
            ofstream x("$$$.txt");
            x << profit;
            x.close();
        }*/
        if (ch == 1) {
            getstaff();
            ofstream x("$$$.txt");
            x << profit;
            x.close();
        }
        else if (ch == 2)
            break;
        else
            cout << "Invaid Option. Please re-enter\n";
    }
}


void amount::update_item()
{
    char id[20];
    char pid[20];
    char c;
    cout << "\nINPUT product ID to modify\n";
    cin >> id;
    char file[20];
    char file2[20];
    strcpy_s(file, id);
    strcat_s(file, ".txt");
    fstream fout(file, ios::in | ios::out);
    if (!fout)
    {
        cout << "file couldn't be opened. product ID not found. \n";
    }
    else {
        cout << "file found! \n";
        cout << "\nupdate product name: \n";
        cin >> name;
        cout << "\nupdate percost of product: \n";
        cin >> percost;
        cout << "\nupdate persell of product: \n";
        cin >> persell;
        cout << "\nupdate total product quantity: \n";
        cin >> quan;
        cost = percost * quan;
        sell = persell * quan;
        profit = profit + (sell - cost) * 365;
        fout << "\nproduct name: " << name << "\nproduct id: " << id << "\npercost ofproduct: " << percost << "\npersell of product: " << persell << "\nquantity: " << quan << "\n total cost: " << cost << "\nsell: " << sell;
        fout.close();
    }
}
void amount::update_emp()
{
    char id[20];
    char c;
    cout << "\nINPUT employee ID to modify: ";
    cin >> id;
    char file[20];
    strcpy_s(file, id);
    strcat_s(file, ".txt");
    fstream fout(file, ios::in | ios::out);
    if (!fout)
    {
        cout << "file couldn't be opened. product ID not found. \n";
    }
    cout << "modify employee name: \n";
    cin >> post;
    fout << "\nnumber of working employees: " << postquan << "\nemployee salary: " << salary << "\nemployee name :" << post << "\nemployee id: " << empid;
    fout.close();
}