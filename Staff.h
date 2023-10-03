#pragma once
#include<fstream>
#include<iostream>
#include<string>
#include<cstdlib>
#include <cstring>
#include<stdio.h>
#include "Amount.h"

using namespace std;

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