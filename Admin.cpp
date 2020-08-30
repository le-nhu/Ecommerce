#include "Admin.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
using namespace std;

//set the pass and username as admin by default
Admin::Admin() {
	string a = "admin";
	user = a;
	pass = a;
}


Admin::~Admin()
{
}

//set username
string Admin::Username(string username) {
	user = username;
	return user;
}

//set password
string Admin::Password(string password) {
	pass = password;
	return pass;
}


//see if what is enter matches password and username
bool Admin::validate(string userAttempt, string passAttempt) {
	string u, p;

	//if it matches return true
	if ((userAttempt == user) && (passAttempt == pass)) {
		return true;
	}
	else {
		//if what was enter is wrong have user reenter
		cout << "Wrong username/password was entered. Please try again.\n";
		cout << "Username: \n";
		cin >> u;
		cout << "Password: \n";
		cin >> p;
		return validate(u, p);
	}

	return false;
}

