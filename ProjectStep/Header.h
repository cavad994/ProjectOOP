#pragma once
#include "Source.cpp"
#include<iostream>
#include<windows.h>
#include<time.h>
#include<vector>
#include<iomanip>
#include"exception.h"
#include<conio.h>
#include<map>
#include<sstream>
#include<fstream>
#include"Restaurant.h"

double StringToDouble(string str) {
	double total = 0;
	double num = 0;
	bool test = false;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '.')
			test = true;
		if (!test)
			total = total * 10 + (str[i] - 48);
		else {
			num = num * 10 + (str[i] - 48);
		}
	}
	total = total + (num / 10);
	return total;
}

#pragma region Reading
void ReadFileStock(map <Ingredient, int>& stock) {
	ifstream file("stock.txt");

	if (file.is_open()) {
		while (!file.eof())
		{
			string name;
			string count;
			string kcal;
			string price;
			file >> name >> count >> kcal >> price;
			Ingredient ingr(name, StringToDouble(price), StringToDouble(kcal));
			stock.insert({ ingr,int(StringToDouble(count)) });
		}
	}
	file.close();
	system("pause");
}
void ReadFileOrders() {
	ifstream file("orders.txt");
	if (file.is_open()) {

		while (!file.eof())
		{
			string name, price, kcal, time;
			file >> name >> price >> kcal >> time;

			cout << setw(10) << left << name;
			cout << setw(10) << left << price;
			cout << setw(10) << left << kcal;
			cout << setw(10) << left << time;
		}
	}
	file.close();
	system("pause");
}
#pragma endregion

#pragma region Uptading
void UpdateStock(map <Ingredient, int>& stock) {
	ofstream file("stock.txt", ios::out);

	file << setw(10) << "Name";
	file << setw(10) << "Count";
	file << setw(10) << "Kcal";
	file << setw(10) << "Price";
	file << endl;

	for (auto ingr : stock)
	{
		if (file.is_open()) {
			file << setw(10) << ingr.first.GetName();
			file << setw(10) << ingr.second;
			file << setw(10) << ingr.first.GetKcal();
			file << setw(10) << ingr.first.GetPrice() << endl;
		}
	}
	file.close();
}

#pragma endregion

#pragma region Users
void ReadUsers(vector<Client>& clients) {
	ifstream file("users.txt");

	if (file.is_open()) {
		while (!file.eof())
		{
			string name;
			string password;
			file >> name >> password;
			Client c(name, password);
			clients.push_back(c);
		}
	}
	file.close();
}
#pragma endregion

























