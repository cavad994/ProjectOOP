#pragma once
#include<iostream>
#include<windows.h>
#include<time.h>
#include<vector>
#include<iomanip>
#include<conio.h>
#include<map>
#include<exception>
#include<fstream>
#include<sstream>
#include"Design.h"
#include"Exception.h"
#include"LoginOrRegister.h"
#include"Order.h"
#include"Dish.h"
class Ingredient {
	string name;
	double price;
	int kcal;
public:
	Ingredient() = default;
	Ingredient(const string name, double price, int kcal) {
		try
		{
			SetName(name);
			SetPrice(price);
			SetKcal(kcal);
		}
		catch (const char* ex)
		{
			cout << ex;
		}
	}

#pragma region Getter
	string GetName()const { return this->name; }
	double GetPrice()const { return this->price; }
	int GetKcal()const { return this->kcal; }
#pragma endregion

#pragma region Setter
	void SetName(const string name) {
		if (name.empty())
			throw("Enter name of ingredient!\n");
		this->name = name;
	}
	void SetPrice(double price) {
		this->price = price;
	}
	void SetKcal(int kcal) {
		if (kcal <= 0)
			throw("Add something!");
		this->kcal = kcal;
	}
#pragma endregion
	void ShowIngr(Ingredient ingr) {
		cout << "\t\t\t\t\t Name : " << this->GetName() << "\n" << endl;
		cout << "\t\t\t\t\t Kcal : " << this->GetKcal() << "\n" << endl;
		cout << "\t\t\t\t\t Price : " << this->GetPrice() << "\n" << endl;
	}
};

struct Operator {
	bool operator() (const Ingredient& lhs, const Ingredient& rhs) const
	{
		return lhs.GetName() < rhs.GetName();
	}
};
