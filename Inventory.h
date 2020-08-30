#pragma once
#include "LinkList.h"
#include <string>
using namespace std;

class Inventory
{
public:
	Inventory();
	Inventory(int num, string name, double cost, int qty);
	~Inventory();
	Inventory* next= NULL;
	void setQty(int qty);
	void setCost(double cost);
	int getItemNumber() const {
		return itemNumber;
	}
	string getName() const {
		return itemName;
	}
	double getCost() const {
		return itemCost;
	}
	int getQty() const {
		return itemQty;
	}
	friend class LinkList;
	
	
private:
	int itemNumber;
	string itemName;
	double itemCost;
	int itemQty;
};

