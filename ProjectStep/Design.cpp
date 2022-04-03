#include<iostream>
#include<Windows.h>
#include"Design.h"
using namespace std;
void IlkBosluq() {
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
}

void Loading() {
	system("cls");
	IlkBosluq();
	cout << "\t\t\t\t\t\t\t" << "LOADING.";
	Sleep(200);
	system("cls");
	IlkBosluq();
	cout << "\t\t\t\t\t\t\t" << "LOADING..";
	Sleep(200);
	system("cls");
	IlkBosluq();
	cout << "\t\t\t\t\t\t\t" << "LOADING...";
	Sleep(200);
	system("cls");
	IlkBosluq();
}

void Tries() {
	IlkBosluq();
	int time = 60;
	for (int i = 0; i < 60; i++)
	{
		system("cls");
		IlkBosluq();
		cout << "\t\t\t\t\t" << time--;
		Sleep(1000);
	}
}