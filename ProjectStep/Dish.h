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
#include"Order.h"
#include"LoginOrRegister.h"
#include"Ingredient.h"

using namespace std;

class Dish {
	string name;
	map<Ingredient, int, Operator> ingredients;
	double price = 0;
	int kcal = 0;
public:

	Dish() {}
	Dish(const string name) {
		SetName(name);
	}

#pragma region Getter
	string GetName()const { return this->name; }

	map<Ingredient, int, Operator> GetIngredients() { return this->ingredients; }

	double GetPrice()const { return this->price; }

	int GetKcal()const { return this->kcal; }

#pragma endregion
#pragma region Setter
	void SetName(const string name) {
		if (name.empty())
			throw("Enter name of dish!");
		this->name = name;
	}

#pragma endregion

	void addIngrToDish(Ingredient& ingr, int count = 1) {
		bool b = false;
		for (auto item : ingredients) {
			if (item.first.GetName() == ingr.GetName())
			{
				ingredients[item.first] += count; b = true;
			}
		}
		if (!b)
			ingredients.insert({ ingr, count });
		this->price += (ingr.GetPrice() * 1.5) * count;
		this->kcal += ingr.GetKcal() * count;
	}

	void deleteFromDish(Ingredient& ingredient) throw() {
		for (auto ingr : ingredients) {
			if (ingr.first.GetName() == ingredient.GetName()) {
				this->price -= (ingredient.GetPrice() * ingr.second) * 1.5;
				this->ingredients.erase(ingredient);
			}
		}
		throw notFoundException("No any ingredient");
	}

	Ingredient GetIngrByIndex(int a) {
		int i = 0;
		for (auto ingr : ingredients) {
			if (i = a)
				return ingr.first;
			i++;
		}
		throw notFoundException("Ingredient is not found");
	}

	void ShowDishInfo() {
		cout << setw(70) << right << "Meal : " << GetName() << endl;
		for (auto ingr : ingredients)
		{
			cout << setw(40) << left << ingr.first.GetName() << right << ingr.second << endl;
		}
		cout << setw(40) << right << "Kcal : " << this->GetKcal() << " kcal" << endl;
		cout << setw(40) << right << "Price : " << this->GetPrice() << " AZN" << endl;
	}

	void ShowIngr() {
		int i = 0;
		for (auto ingr : ingredients) {
			cout << ++i << setw(30) << left << ingr.first.GetName() << right << ingr.second << endl;
		}
	}
};
