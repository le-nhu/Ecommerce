#pragma once
#include <iostream>
#include <string>
using namespace std;


class Admin
{
public:
	Admin();
	~Admin();
	string Username(string username);
	string Password(string password);
	bool validate(string userAttempt, string passAttempt);

private:
	string user;
	string pass;

};

