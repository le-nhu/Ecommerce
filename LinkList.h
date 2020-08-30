#pragma once
#include "Inventory.h"
#include "Customer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>

class LinkList
{
	friend class Inventory;
	friend class Customer;
public:
	LinkList();
	LinkList(int num, string name, double cost, int qty);
	LinkList operator+( const LinkList &add);
	~LinkList();
	int build();
	void print();
	int addproduct(int data);
	int findPosition(int data);
	bool search(int data);
	void remove(int data);
	int updateQTY(int data);
	int updateCost(int data);
	void updateCVS(fstream & inFile);
	string showCart();	//display the item in cart
	void appendCart(int productNum, int userQuantity, string name, double itemPrice);
	int searchQTY(LinkList* inventory, LinkList* customer, int productNum, int userQuantity, int &shopCount);
	void finalCart();
	int updateQTY(LinkList* inventory, LinkList* customer,int data);
	Inventory* head;
	void invoice(Customer user);
	
};

