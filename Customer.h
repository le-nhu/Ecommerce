#pragma once
#include "LinkList.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;


class Customer
{
public:
	Customer();
	Customer(string first, string last, string add, string city, string state, int zip);
	~Customer();
	void setfirst(string fname) {
		firstName = fname;
	}
	void setlast(string lname) {
		lastName = lname;
	}
	void setadd(string add) {
		Address = add;
	}
	void setcity(string city) {
		City = city;
	}
	void setstate(string state) {
		State = state;
	}
	void setzip(int zip) {
		zipcode = zip;
	}
	string getfirst() const {
		return firstName;
	}
	string getlast() const {
		return lastName;
	}
	string getadd() const {
		return Address;
	}
	string getcity() const {
		return City;
	}
	string getstate() const {
		return State;
	}
	int getzip() const {
		return zipcode;
	}

private:
	string firstName;
	string lastName;
	string Address;
	string City;
	string State;
	int zipcode;
};

