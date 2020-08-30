#include "Customer.h"
#include "LinkList.h"
#include <iostream>


Customer::Customer()
{
	string first, last, address, city, state;         //will take in and store user's personal information  
	int zip;
	//The following asks for customer's information, reads it in, and stores it 
	cin.ignore();

	cout << "Please enter your first name." << endl;
	getline(cin, first);

	cout << "Enter your last name." << endl;
	getline(cin, last);

	cout << "Enter your address." << endl;
	getline(cin, address);

	cout << "Enter your city." << endl;
	getline(cin, city);

	cout << "Enter your state." << endl;
	getline(cin, state);

	cout << "Enter your zip code." << endl;
	cin >> zip;


	firstName = first;
	lastName = last;
	Address = address;
	City = city;
	State = state;
	zipcode = zip;

}

Customer::Customer(string first, string last, string add, string city, string state, int zip) {
	firstName = first;
	lastName = last;
	Address = add;
	City = city;
	State = state;
	zipcode = zip;
}

Customer::~Customer()
{
}
