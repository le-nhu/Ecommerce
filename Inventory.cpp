#include "Inventory.h"
#include <iomanip>
#include <iostream>
using namespace std;



Inventory::Inventory()
{
}

Inventory::Inventory(int num, string name, double cost, int qty) {
	itemNumber = num;
	itemName = name;
	itemCost = cost;
	itemQty = qty;
}

Inventory::~Inventory()
{
}

void Inventory::setQty(int qty) {
	itemQty = qty;
}

void Inventory::setCost(double cost) {
	itemCost = cost;
}

