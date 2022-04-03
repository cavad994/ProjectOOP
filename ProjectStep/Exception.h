#pragma once
#include<iostream>
#include<exception>
using namespace std;
class BaseException : public exception
{
public:
	virtual char const* what()const override {
		return "Base exception error!\n";
	}
};

class notFoundException : public BaseException {
public:
	string message;
	notFoundException(string message) {
		this->message = message;
	}
	char const* what()const override {
		cout << message << endl;
		return "Item is not found\n";
	}
};