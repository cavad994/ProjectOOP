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
#include"Ingredient.h"
#include"Dish.h"
using namespace std;


class Menu {
	vector<Dish> dishes;
	vector<Dish> drinks;
public:
	Menu() {}

#pragma region Getter

	vector<Dish> GetDishes() { return this->dishes; }

	vector<Dish> GetDrinks() { return this->drinks; }

#pragma endregion

#pragma region DishDetails
	void addDish(Dish dish) {
		dishes.push_back(dish);
	}

	void deleteDish(Dish dish) {
		for (int i = 0; i < dishes.size(); i++)
		{
			if (dishes[i].GetName() == dish.GetName()) {
				dishes.erase(dishes.begin() + i);
				return;
			}
		}
		cout << dish.GetName();
		throw notFoundException(" not found");
	}

	void ShowDishes() {
		cout << setw(50) << right << "DISHES" << endl;
		if (dishes.size() > 0) {
			cout << dishes.size() << endl;
			for (int i = 0; i < dishes.size(); i++)
			{
				cout << "\t\t\t\t\t" << i + 1 << ". " << setw(40) << left << dishes[i].GetName() << right << dishes[i].GetPrice() << " AZN\n";
			}
		}
		else
			cout << "\t\t\t\t\t\t" << "No any dishes\n";
	}
#pragma endregion

#pragma region DrinkDetails
	void addDrink(Dish drink) {
		drinks.push_back(drink);
	}

	void deleteDrink(Dish drink) {
		for (int i = 0; i < drinks.size(); i++)
		{
			if (drinks[i].GetName() == drink.GetName()) {
				drinks.erase(drinks.begin() + i);
				return;
			}
		}
	}

	void ShowDrinks() {
		if (drinks.size() > 0) {
			cout << setw(50) << right << "DRINKS" << endl;
			for (int i = 0; i < drinks.size(); i++)
			{
				cout << "\t\t\t\t\t" << i + 1 << ". " << setw(40) << left << drinks[i].GetName() << right << drinks[i].GetPrice() << " AZN\n";
			}
			return;
		}
		else
			cout << "\t\t\t\t\t\t" << "No any drinks\n";
	}
#pragma endregion

	void ShowMenuForAdmin() {
		try
		{
			ShowDishes();
			ShowDrinks();
		}
		catch (const char* ex)
		{
			cout << ex << endl;
		}
	}

};

#pragma region Restaurant

class Restaurant
{
public:
	map <Ingredient, int, Operator> stock;
	Menu menu;
	double budget = 100000;
	vector<Client> clients;
	vector<Ingredient> ingredients;
	User* a = new Admin("Cavad", "Cavad994");
#pragma region File

	double StringConverter(string str) {
		double total = 0;
		double num = 0;
		bool test = false;
		for (int i = 0; i < str.length(); i++)
		{
			if (str[i] == '.') {
				test = true;
				continue;
			}
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
	void ReadFileStock() {
		ifstream file("stock.txt");

		if (file.is_open()) {
			while (!file.eof())
			{
				string name;
				string count;
				string kcal;
				string price;
				file >> name >> count >> kcal >> price;
				if (name == "Name")
					continue;
				if (name == "")
					break;
				Ingredient ingr(name, StringConverter(price), StringConverter(kcal));
				stock.insert({ ingr,StringConverter(count) });
			}
		}
		file.close();
	}
	void ReadFileOrders() {
		ifstream file("orders.txt");
		if (file.is_open()) {
			std::cout << std::left << setw(10) << "Name";
			std::cout << std::left << setw(10) << "Price";
			std::cout << std::left << setw(10) << "Date";
			std::cout << std::right << setw(15) << "Time\n";

			while (!file.eof())
			{
				string name, price, month, day, year, time;
				file >> name >> price >> month >> day >> year >> time;

				cout << setw(10) << left << name;
				cout << setw(10) << left << price;
				cout << setw(5) << left << month;
				cout << setw(2) << left << day;
				cout << setw(5) << left << year;
				cout << setw(15) << right << time << endl;
			}
		}
		file.close();
	}
	void ReadFileBudget() {
		ifstream file("budget.txt");
		if (file.is_open()) {
			while (!file.eof()) {
				string cash;
				file >> cash;
				this->budget = StringConverter(cash);
			}
		}
		file.close();
	}
#pragma endregion

#pragma region Updating
	void UpdateStock() {
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
	void UpdateBudget() {
		ofstream file("budget.txt", ios::out);
		file << setw(20) << this->budget;
		file.close();
	}
	void UpdateClient() {
		ofstream file("users.txt", ios::out);
		file << setw(15) << "Username";
		file << setw(15) << "Password";
		file << endl;
		for (int i = 0; i < clients.size(); i++)
		{
			if (file.is_open()) {
				file << setw(15) << clients[i].GetUsername();
				file << setw(15) << clients[i].GetPassword() << endl;
			}
		}
		file.close();
	}
	void UpdateOrder(Client client) {
		ofstream file("orders.txt", ios::app);
		file << setw(15) << client.GetUsername();
		file << setw(10) << client.GetOrder().GetTotalPrice();
		file << setw(20) << __DATE__;
		file << setw(10) << __TIME__ << "\n";

		file.close();
	}
#pragma endregion

#pragma region Users
	void ReadUsers() {
		ifstream file("users.txt");

		if (file.is_open()) {
			while (!file.eof())
			{
				string name;
				string password;
				file >> name >> password;
				if (name == "Username")
					continue;
				if (name == "")
					break;
				Client client(name, password);
				clients.push_back(client);
			}
		}
		file.close();
	}
#pragma endregion


#pragma endregion
	void AddToStock(Ingredient ingr, int count) {
		for (auto i : stock)
		{
			if (i.first.GetName() == ingr.GetName()) {
				stock[i.first] += count;
				return;
			}
		}
		stock.insert({ ingr,count });
	}
	void ShowStock() {
		cout << setw(40) << right << "Name" << setw(20) << right << "Count" << endl;
		for (auto ingr : stock)
		{
			cout << setw(40) << right << ingr.first.GetName() << setw(20) << right << ingr.second << endl;
		}
	}

	void AddMenu() {

		Dish kabab("Kabab");
		Dish dolma("3 baci dolmasi");
		Dish plov("Plov");

		Dish ayran("Ayran (Atena)");
		Dish limonad("Duses (Natakhtari)");
		Dish almasiresi("Alma siresi (Bizim Tarla)");

		for (int i = 0; i < ingredients.size(); i++)
		{
			if (ingredients[i].GetName() == "pomidor") {
				dolma.addIngrToDish(ingredients[i]);
				kabab.addIngrToDish(ingredients[i]);
			}
			if (ingredients[i].GetName() == "xiyar") {
				dolma.addIngrToDish(ingredients[i]);
				kabab.addIngrToDish(ingredients[i]);
			}
			if (ingredients[i].GetName() == "maleti") {
				kabab.addIngrToDish(ingredients[i]);
				dolma.addIngrToDish(ingredients[i]);
			}
			if (ingredients[i].GetName() == "qoyuneti") {
				dolma.addIngrToDish(ingredients[i]);
				kabab.addIngrToDish(ingredients[i]);
			}
			if (ingredients[i].GetName() == "su") {
				ayran.addIngrToDish(ingredients[i]);
				almasiresi.addIngrToDish(ingredients[i]);
			}
			if (ingredients[i].GetName() == "qatiq") {
				ayran.addIngrToDish(ingredients[i]);
			}
			if (ingredients[i].GetName() == "duz") {
				ayran.addIngrToDish(ingredients[i]);
				kabab.addIngrToDish(ingredients[i]);
				limonad.addIngrToDish(ingredients[i]);
				almasiresi.addIngrToDish(ingredients[i]);
				dolma.addIngrToDish(ingredients[i]);
			}
			if (ingredients[i].GetName() == "badimcan") {
				dolma.addIngrToDish(ingredients[i]);
				plov.addIngrToDish(ingredients[i]);
			}
			if (ingredients[i].GetName() == "biber") {
				dolma.addIngrToDish(ingredients[i]);
				kabab.addIngrToDish(ingredients[i]);
			}
			if (ingredients[i].GetName() == "duyu") {
				plov.addIngrToDish(ingredients[i]);
			}
			if (ingredients[i].GetName() == "kismis") {
				plov.addIngrToDish(ingredients[i]);
			}
			if (ingredients[i].GetName() == "sabalid") {
				plov.addIngrToDish(ingredients[i]);
			}
			if (ingredients[i].GetName() == "zeferan") {
				plov.addIngrToDish(ingredients[i]);
			}
			if (ingredients[i].GetName() == "duses") {
				limonad.addIngrToDish(ingredients[i]);
			}
			if (ingredients[i].GetName() == "sheker") {
				limonad.addIngrToDish(ingredients[i]);
				almasiresi.addIngrToDish(ingredients[i]);
			}
		}
		menu.addDish(kabab);
		menu.addDish(dolma);
		menu.addDish(plov);
		menu.addDrink(ayran);
		menu.addDrink(almasiresi);
		menu.addDrink(limonad);
	}

	///////////////////////////////////////////////////////////////////////////

	void FirstSteps() {
		ReadFileStock();
		ReadFileBudget();
		ReadUsers();
		IlkBosluq();
		cout << setw(70) << right << "Restorana xos gelmisiniz !" << endl << endl << endl << endl;
		cout << setw(68) << right << "  Enter any key \n\n\n\n\n";
		system("pause");
		system("cls");
	start:
		system("cls");
		Loading();
		cout << "\t\t\t\t\t" << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "\t\t\t\t\t||" << "\t1 - Daxil ol" << setw(13) << right << " || " << endl;
		cout << "\t\t\t\t\t||" << "\t2 - Qeydiyyatdan kec  ||" << endl;
		cout << "\t\t\t\t\t" << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
		int ch1 = 0;
		cout << "\t\t\t\t\t" << "Your choice : ";
		ch1 = _getch();
		system("cls");
		if (ch1 == '1') {
			int tries = 0;
		login:
			Loading();
			cout << "Username of admin : Cavad\n";
			cout << "Password of admin : Cavad994\n";
			string username, password;
			cout << "\t\t\t\t\tUsername : "; cin >> username;
			cout << "\t\t\t\t\tPassword : ";
			Password(username, password);
			tries++;
			if (username == a->GetUsername() && password == a->GetPassword()) {
				AdminSide();
				goto start;
			}
			for (size_t i = 0; i < clients.size(); i++)
			{
				if (username == clients[i].GetUsername() && password == clients[i].GetPassword()) {
					ClientSide(clients[i]);
					goto start;
				}
			}
			if (tries < 3) {
				cout << "\n\t\t\t\t\tAccount doesn't exist\n\n\n";
				system("pause");
				goto login;
			}
			else {
				Tries();
				tries = 0;
				goto login;
			}
		}
		//////////////////////// I will continue tomorrow from here. I will write client and admin sides. Adding dishes and etc; line 790

		else if (ch1 == '2') {
			Loading();
			bool b = true;
		registerside:
			system("cls");
			string username;
			string password;
			IlkBosluq();
			cout << "\t\t\t\t\tTo cancel registeration, enter only '0'\n\n";
			cout << "\t\t\t\t\tUsername : "; cin >> username;
			if (username == "0")
				goto start;
			if (username == "Cavad") {
				cout << "\n\t\t\t\t\t You can't use admin's username!\n\n";
				system("pause");
				goto registerside;
			}
			for (int i = 0; i < clients.size(); i++)
			{
				if (username == clients[i].GetUsername()) {
					cout << "\n\n\t\t\t\tChange your username. This username is used !\n\n";
					system("pause");
					b = false;
					goto registerside;
				}
			}
			cout << "\t\t\t\t\tPassword : ";
			Password(username, password);
			if (TestPassword(password) == true) {
				Client newClient(username, password);
				clients.push_back(newClient);
				UpdateClient();
				cout << "\n\n\t\t\t\t\tUser succesfully added!\n";
				Sleep(3000);
				goto start;
			}
			else {
				cout << "Password is not true !";
				system("pause");
				goto registerside;
			}
		}
		else
			goto start;
	}
#pragma region admin
	void AdminSide() {
	adminside:
		Loading();
		int ch = 0;
		cout << "\t\t\t\t\t\t\t\t\t\t" << "0 - Log out" << endl << endl;
		cout << "\t\t\t\t\t" << "HELLO Mr." << a->GetUsername() << endl;
		cout << "\t\t\t\t\t" << "1 - Stock" << endl;
		cout << "\t\t\t\t\t" << "2 - Dishes" << endl;
		cout << "\t\t\t\t\t" << "3 - Orders" << endl << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t BUDGET : " << budget << endl;
		cout << "\t\t\t\t\t" << "How can i help you boss? Choose : ";
		ch = _getch();
		system("cls");
		if (ch == '1') {
			Loading();
		stck:
			system("cls");
			IlkBosluq();
			int index = 1;
			int ch1;
			cout << "\t\t";
			for (auto item : stock)
			{
				cout << index++ << ". " << setw(30) << left << item.first.GetName() << right << item.second;
				if (index % 2 == 0)
					cout << "\t || \t";
				else
					cout << endl << "\t\t";
			}
			cout << "\n\t\t\t\t\t" << index << " - ADD INGREDIENT" << endl;
			cout << "\t\t\t\t\t" << "0 - BACK" << endl;
			cout << "\n\t\t\t\t\t" << "Your choice : "; cin >> ch1;
			int userChoice;
			if (ch1 == index) {
			addIngr:
				int i = 1;
				system("cls");
				IlkBosluq();
				cout << "\t\t\t\t";
				for (auto item : ingredients)
				{
					cout << i++ << ". " << setw(10) << left << item.GetName();
					if (i % 2 == 0)
						cout << "\t || \t";
					else
						cout << endl << "\t\t\t\t";
				}
				cout << "\t\t\t\t\t" << "0 - BACK\n";
				cout << endl;
				cout << "\t\t\t\t\t" << "Choose ingredient: "; cin >> userChoice;
				if (userChoice == 0) {
					goto stck;
				}
				else if (userChoice > 0 && userChoice <= ingredients.size()) {
					int count;
					cout << "\t\t\t\t\tHow many/much? :"; cin >> count;
					if (count > 0) {
						AddToStock(ingredients[userChoice - 1], count);
						budget -= (ingredients[userChoice - 1].GetPrice() * count);
						UpdateStock();
						UpdateBudget();
						cout << "\t\t\t\t\t Ingredient succesfully added !\n";
						Sleep(3000);
						goto addIngr;
					}
					else
						goto addIngr;
				}
				else {
					cout << "Choose correctly !\n";
					goto addIngr;
				}
			}

			else if (ch1 == 0) {
				system("cls");
				goto adminside;
			}
			else
				goto stck;
			///////////////////////////////////ingredients adding
			/////////////////////dish adding
		}

		else if (ch == '2') {
			int userChoice;
		menuSection:
			system("cls");
			Loading();
			cout << "\t\t\t\t\t" << "1 - Juices or drinks\n";
			cout << "\t\t\t\t\t" << "2 - Dishes\n";
			cout << "\t\t\t\t\t" << "0 - BACK\n";
			cout << "\n\t\t\t\t\t" << "Choice : ";
			userChoice = _getch();
			int userItem;
			Loading();
			if (userChoice == '1') {
				menu.ShowDrinks();
				cout << endl << endl;
				cout << "\t\t\t\t\t" << menu.GetDrinks().size() + 1 << ". ADD DRINK\n";
				cout << "\t\t\t\t\t" << "0. BACK\n\n";
				cout << "\t\t\t\t\t" << "If you want, you can see info about drinks by index.\n ";
				cout << "\t\t\t\t\t" << "Choose : "; cin >> userItem;
				if (userItem == 0)
					goto menuSection;
				else if (userItem == menu.GetDrinks().size() + 1) {
					string newDrink;
					Loading();
					cout << "\t\t\t\t\tEnter name of drink : "; cin >> newDrink;
					for (int i = 0; i < menu.GetDrinks().size(); i++)
					{
						if (newDrink == menu.GetDrinks()[i].GetName()) {
							cout << "This drink is already exist !";
							return;
						}
					}
					Dish newD(newDrink);
					while (true)
					{
						int index = 1;
						int ch1;
						system("cls");
						for (int i = 0; i < ingredients.size(); i++)
						{
							cout << "\t\t\t\t\t" << index++ << ". " << setw(20) << left << ingredients[i].GetName() << right << endl;
						}
						cout << "\t\t\t\t\t" << "0 - BACK\n";
						cout << "\t\t\t\t\t" << "Choose : "; cin >> ch1;
						if (ch1 > 0 && ch1 <= ingredients.size()) {
							newD.addIngrToDish(ingredients[ch1 - 1]);
							cout << "\n\t\t\t\t\tIngredient added !\n";
							system("pause");
						}
						else
							break;
					}
					if (!newD.GetIngredients().empty())
						menu.addDrink(newD);
					goto menuSection;
				}

				else if (userItem > 0 && userItem <= menu.GetDrinks().size()) {
					char sechim;
					Loading();
					cout << "\n\t\t\t\t\t" << menu.GetDrinks()[userItem - 1].GetName() << endl;
					cout << "\t\t\tIngredients : ";
					for (auto item : menu.GetDrinks()[userItem - 1].GetIngredients()) {
						cout << item.first.GetName() << ", ";
					}
					cout << "\n\t\t\t\t\t" << menu.GetDrinks()[userItem - 1].GetKcal() << endl;
					cout << "\t\t\t\t\t" << menu.GetDrinks()[userItem - 1].GetPrice() << endl;
					cout << "\n\t\t\t\t\t" << "If you want to delete drink, then please enter '0' ";
					sechim = _getch();
					if (sechim == '0')
						menu.deleteDrink(menu.GetDrinks()[userItem - 1]);
					goto menuSection;
				}
			}
			if (userChoice == '2') {
				menu.ShowDishes();
				cout << endl << endl;
				cout << "\t\t\t\t\t" << menu.GetDishes().size() + 1 << ". ADD DISH\n";
				cout << "\t\t\t\t\t" << "0" << ". BACK\n";
				cout << "\t\t\t\t\t" << "If you want, you can see info about dishes by index.\n ";
				cout << "\t\t\t\t\t" << "Choose : "; cin >> userItem;
				if (userItem == 0)
					goto menuSection;
				else if (userItem == menu.GetDishes().size() + 1) {
					string newDish;
					Loading();
					cout << "\t\t\t\t\tEnter name of dish : "; cin >> newDish;
					for (int i = 0; i < menu.GetDishes().size(); i++)
					{
						if (newDish == menu.GetDishes()[i].GetName()) {
							cout << "This dish is already exist !";
							return;
						}
					}
					Dish newD(newDish);
					while (true)
					{
						int index = 1;
						int ch1;
						system("cls");
						for (int i = 0; i < ingredients.size(); i++)
						{
							cout << "\t\t\t\t\t" << index++ << ". " << setw(20) << left << ingredients[i].GetName() << right << endl;
						}
						cout << "\t\t\t\t\t" << "0 - BACK\n";
						cout << "\t\t\t\t\t" << "Choose : "; cin >> ch1;
						if (ch1 > 0 && ch1 <= ingredients.size()) {
							newD.addIngrToDish(ingredients[ch1 - 1]);
							cout << "\n\t\t\t\t\tIngredient added !\n";
							system("pause");
						}
						else
							break;
					}
					if (!newD.GetIngredients().empty())
						menu.addDish(newD);
					goto menuSection;
				}

				else if (userItem > 0 && userItem <= menu.GetDishes().size()) {
					char sechim;
					Loading();
					cout << "\n\t\t\t\t\t" << menu.GetDishes()[userItem - 1].GetName() << endl;
					cout << "\t\t\tIngredients : ";
					for (auto item : menu.GetDishes()[userItem - 1].GetIngredients()) {
						cout << item.first.GetName() << ", ";
					}
					cout << "\n\t\t\t\t\t" << menu.GetDishes()[userItem - 1].GetKcal() << endl;
					cout << "\t\t\t\t\t" << menu.GetDishes()[userItem - 1].GetPrice() << endl;
					cout << "\n\t\t\t\t\t" << "If you want to delete dish, then please enter '0' ";
					sechim = _getch();
					if (sechim == '0')
						menu.deleteDish(menu.GetDishes()[userItem - 1]);
					goto menuSection;
				}
			}
			else
				goto adminside;
		}
		////////////////////////////////////
		////////////boshluqda error var. Seher ona baxacam. Loading hemcinin. main de, ickileri elave etmek. 
		else if (ch == '3') {
			ReadFileOrders();
			system("pause");
			goto adminside;
		}
		else if (ch == '0')
			FirstSteps();
		else {
			goto adminside;
		}
		//////////////////////////////////////
		//////////////admin hissesi demek olar hazirdir. Test etmek qalib. Full test, daha sonra client side a baslamaq.
	}

#pragma endregion
#pragma region client
	void ClientSide(Client& client) {
		Loading();
		cout << "\t\t\t\t\t\t Welcome Mr." << client.GetUsername() << endl;
		Sleep(2000);
	menu:
		system("cls");
		cout << "\t\t\t\t\t\t\t\t\t\t\t 0 - LOG OUT";
		IlkBosluq();
		int ChooseFromMenu;
		cout << "\t\t\t\t\t1 - Foods\n\t\t\t\t\t2 - drinks\n";
		cout << "\t\t\t\t\t. (dot)" << " - BASKET\n";
		cout << "\t\t\t\t\t0 - BACK";
		cout << "\n\t\t\tChoose : ";
		ChooseFromMenu = _getch();
		if (ChooseFromMenu == '0') {
			Loading();
			FirstSteps();
		}
		else if (ChooseFromMenu == '1') {
			Loading();
			menu.ShowDishes();
			cout << "\t\t\t\t\t0 - BACK\n";
			int ChoosingDish = 0;
			cout << "\t\t\tChoose an dish : "; cin >> ChoosingDish;
			if (ChoosingDish > 0 && ChoosingDish < menu.GetDishes().size() + 1) {
				system("cls");
				int ch1 = 0;
				cout << "\t\t\t\t\t" << menu.GetDishes()[ChoosingDish - 1].GetName() << "\t - " << menu.GetDishes()[ChoosingDish - 1].GetPrice() << " AZN\n";
				menu.GetDishes()[ChoosingDish - 1].ShowIngr();
				cout << "\t\t\t\t\t 1 - GET\n\t\t\t\t\t0 - BACK\n\t\t\t\t\t  CHOISE : ";
				ch1 = _getch();
				if (ch1 == '1') {
					client.AddOrder(menu.GetDishes()[ChoosingDish - 1]);
					system("cls");
					IlkBosluq();
					cout << "\n\n\t\t\t\t\tOrder added!\n";
				}
				goto menu;
			}
		}
		else if (ChooseFromMenu == '2') {
			Loading();
			menu.ShowDrinks();
			cout << "\t\t\t\t\t0 - BACK\n";
			int ChoosingDrink = 0;
			cout << "\t\t\tChoose an drink : "; cin >> ChoosingDrink;
			if (ChoosingDrink > 0 && ChoosingDrink < menu.GetDrinks().size() + 1) {
				system("cls");
				int ch1 = 0;
				cout << "\t\t\t\t\t" << menu.GetDrinks()[ChoosingDrink - 1].GetName() << "\t - " << menu.GetDrinks()[ChoosingDrink - 1].GetPrice() << " AZN\n";
				menu.GetDrinks()[ChoosingDrink - 1].GetIngredients();
				cout << "\t\t\t\t\t 1 - GET\n\t\t\t\t\t0 - BACK\n\t\t\t\t\t  CHOISE : ";
				ch1 = _getch();
				if (ch1 == '1') {
					client.AddOrder(menu.GetDrinks()[ChoosingDrink - 1]);
					system("cls");
					IlkBosluq();
					cout << "\n\n\t\t\t\t\tOrder added!\n";
				}
				goto menu;
			}

		}
		else if (ChooseFromMenu == '.') {
			int ch1;
			Loading();
			client.GetOrder().ShowOrder();
			cout << "\t\t\t\t\t. (dot)" << " - BUY\n" << "9 - CLEAR BASKET\n0 - BACK\n";
			cout << "\t\t\t\t\tCHOISE : ";
			ch1 = _getch();
			if (ch1 == '.') {
				map<Ingredient, int, Operator> basket;
				for (int i = 0; i < client.GetOrder().GetOrder().size(); i++)
				{
					for (auto item : client.GetOrder().GetOrder()[i].GetIngredients())
					{
						for (auto itemInBasket : basket) {
							if (item.first.GetName() == itemInBasket.first.GetName()) {
								basket[itemInBasket.first] += item.second;
								break;
							}
						}
						basket.insert({ item.first,item.second });
					}
				}
				for (auto item : basket) {
					for (auto item1 : stock) {
						if (item.first.GetName() == item1.first.GetName()) {
							if (item.second > item1.second) {
								cout << "\nSorry, we dont have any " << item.first.GetName() << " in stock!\n";
								system("pause");
								goto menu;
							}
						}
					}
				}
				for (auto item : basket) {
					for (auto ingr : stock) {
						if (item.first.GetName() == ingr.first.GetName()) {
							stock[item.first] -= item.second;
							UpdateStock();
						}
					}
				}
				this->budget += client.GetOrder().GetTotalPrice();
				UpdateBudget();
				UpdateOrder(client);
				for (auto i : basket)
				{
					cout << i.first.GetName() << endl;
				}
				cout << "\n\t\t\t\t\tYour dishes are cooking...\n";
				Sleep(3000);
			}

			else if (ch1 == '9') {
				client.ClearOrder();
				system("cls");
				cout << "\n\t\t\t\t\tBasket deleted succesfully!\n";
			}
			goto menu;

		}
		/////////////////////////////////////buradan davam edecem. icki secmek olmur. Test etmek

		system("pause");
	}

};



int main() {
	//start();
	Ingredient cucumber("xiyar", 0.20, 50);
	Ingredient tomato("pomidor", 0.30, 70);
	Ingredient malEti("maleti", 1.20, 200);
	Ingredient qoyunEti("qoyuneti", 1, 200);
	Ingredient ketchup("ketchup", 0.30, 30);
	Ingredient water("su", 0.50, 100);
	Ingredient qatiq("qatiq", 0.40, 70);
	Ingredient salt("duz", 0.1, 30);
	Ingredient egg("yumurta", 35, 150);
	Ingredient istiot("istiot", 0.3, 20);
	Ingredient kolbasa("kolbasa", 0.10, 100);
	Ingredient badimcan("badimcan", 0.40, 150);
	Ingredient gobelek("gobelek", 0.20, 25);
	Ingredient zeferan("zeferan", 0.30, 20);
	Ingredient kelem("kelem", 6, 75);
	Ingredient sugar("sheker", 0.30, 200);
	Ingredient sausage("sausage", 0.25, 150);
	Ingredient yerkoku("yerkoku", 0.25, 70);
	Ingredient sogan("sogan", 0.25, 60);
	Ingredient yag("yag", 0.05, 10);
	Restaurant r;
	r.ingredients.push_back(cucumber);
	r.ingredients.push_back(tomato);
	r.ingredients.push_back(malEti);
	r.ingredients.push_back(qoyunEti);
	r.ingredients.push_back(ketchup);
	r.ingredients.push_back(water);
	r.ingredients.push_back(qatiq);
	r.ingredients.push_back(salt);
	r.ingredients.push_back(egg);
	r.ingredients.push_back(istiot);
	r.ingredients.push_back(kolbasa);
	r.ingredients.push_back(badimcan);
	r.ingredients.push_back(gobelek);
	r.ingredients.push_back(zeferan);
	r.ingredients.push_back(kelem);
	r.ingredients.push_back(sugar);
	r.ingredients.push_back(sausage);
	r.ingredients.push_back(yerkoku);
	r.ingredients.push_back(sogan);
	r.ingredients.push_back(yag);
	while (true)
	{
		try
		{
			r.AddMenu();
			r.FirstSteps();
		}
		catch (const char* ex)
		{
			cout << ex;
			Sleep(2000);
			system("cls");
		}
	}
};

