#pragma once
#include<iostream>
#include<conio.h>
#include<fstream>
#include<iomanip>
using namespace std;

class mall
{
	int pno;
	char name[30];
	float price, dis;
	int quantity;

public:
	void getdata()
	{
		char ch;
		system("color e4");

		cout << "\n\tEnter the details of the product...";
		cout << "\n\tProduct No: ";
		cin >> pno;
		cin.get(ch);
		cout << "\n\tProduct Name: ";
		cin >> name;
		cout << "\n\tProduct Price: ";
		cin >> price;
		cout << "\n\tProduct Discount(%): ";
		cin >> dis;
		cout << "\n\tProduct Quantity: ";
		cin >> quantity;

	}

	void showdata()
	{
		cout << setw(4) << pno << setw(20) << name << setw(8) << price << setw(10) << dis << "%" << setw(10) << quantity << "\n\t";
	}

	int retpno()
	{
		return pno;
	}

	float retprice()
	{
		return price;
	}

	char* retname()
	{
		return name;
	}

	int retdis()
	{
		return dis;
	}

	int retquantity() 
	{
		return quantity;
	}

	void setquantity(int p) 
	{
		quantity = p;
	}
};
