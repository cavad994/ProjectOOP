#pragma once
#include "Source.cpp"
#include<iostream>
#include<windows.h>
#include<time.h>
#include<vector>
#include<iomanip>
#include<conio.h>
#include"exception.h"
#include"Header.h"
#include"Restaurant.h"
using namespace std;

class User
{
	string username;
	string password;
public:
	User() {}
	User(const string username, const string password) {
		try
		{
			SetUsername(username);
			SetPassword(password);
		}
		catch (const char* ex)
		{
			cout << ex;
		}
	}
#pragma region Getter
	string GetUsername() { return this->username; }
	string GetPassword() { return this->password; }
#pragma endregion

#pragma region Setter
	void SetUsername(string username) throw() {
		if (username.size() <= 0)
			throw ("Please, enter your username !");
		this->username = username;
	}

	void SetPassword(string password) throw() {
		int upper = 0;
		int num = 0;
		if (password.size() <= 0)
			throw ("Please, enter your password correctly!");
		for (int i = 0; i < password.size(); i++)
		{
			if (password[i] >= 65 && password[i] <= 90)
				upper++;
			if (password[i] >= 48 && password[i] <= 57)
				num++;
		}
		if (upper >= 1 && num >= 3)
			this->password = password;
		else
			throw("Password is not true !\n Please, use minimum 1 upper case and 3 numbers! ");
	}
#pragma endregion
};

class Admin : public User {
public:
	Admin() {}
	Admin(string username, string password) {
		try
		{
			SetUsername(username);
			SetPassword(password);
		}
		catch (const char* ex)
		{
			cout << ex;
		}
	}
};

class Client : public User {
public:
	Order ClientOrder;
	Client(string username, string password)
	{
		try
		{
			SetUsername(username);
			SetPassword(password);
		}
		catch (const char* ex)
		{
			cout << ex;
		}
		
		
	}

	void AddOrder(Dish dish) {
		ClientOrder.AddOrder(dish);
	}
	void ClearOrder() {
		
	}
};

void Password(string username,string password) {
	char p = 0;

	system("cls");

	while (true)
	{
		system("cls");
		cout << setw(50) << right << "Username : " << username;
		cout << setw(50) << right << "Password : ";
		for (int i = 0; i < password.length(); i++)
		{
			cout << "*";
		}
		p = _getch();
		if (password.length() != 0)
			password.pop_back();
		else if (int(p) == 13)
			break;
		else
			password.push_back(p);
	}
}

//////////////////////dotted password!////////////////////

