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
#include"Dish.h"
#include"Ingredient.h"
using namespace std;
class Order {
	string ClientUsername;
	vector<Dish> order;
public:
	Order() {}

#pragma region Getter
	string GetClientUsername() { return this->ClientUsername; }
	vector<Dish> GetOrder() { return this->order; }
	int GetDishCount() { return this->order.size(); }
#pragma endregion

#pragma region Setter
	void SetClientName(string username) throw () {
		if (username.size() > 0)
			this->ClientUsername = username;
		else
			throw("Enter client name");
	}
#pragma endregion

	void AddOrder(Dish dish, int count = 1) {
		for (int i = 0; i < count; i++)
		{
			order.push_back(dish);
		}
	}

	void DeleteOrder() {
		order.clear();
	}

	void AddIngredient(Ingredient ingr, int index, int count = 1) {
		if (index >= 0 && index < order.size())
			order[index].addIngrToDish(ingr, count);
	}

	void ShowOrder() const {
		double cost = 0;
		for (int i = 0; i < order.size(); i++)
		{
			cout << setw(40) << right << i + 1 << ". " << order[i].GetName() << "\t - " << order[i].GetPrice() << endl;
			cost += order[i].GetPrice();
		}
		cout << setw(40) << right << "\nTotal price : " << cost;
	}

	double GetTotalPrice() {
		double cost = 0;
		for (int i = 0; i < order.size(); i++)
		{
			cost += order[i].GetPrice();
		}
		return cost;
	}
};
