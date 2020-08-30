//Nhu Le, this program will allow for a admin/customer experience in an ecommerce site.
//to access admin, the username and password must be entered; afterwards changes can be made to inventory.
//customers may shop for whats in stock and recieve an invoice for their purchase.
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include "Admin.h"
#include "Customer.h"
#include "Inventory.h"
#include "LinkList.h"
using namespace std;

int search(LinkList* inventory, LinkList* customer, int productNum);

int main() {
	fstream inFile;						//takes in the cvs file that holds all the inventory data
	int customerLast;					//ask customer to check and make any final changes to their cart
	int shopCount = 0;					//counts how many different item is added into the shopping  cart
	int modeChoice, adminChoice;		//admin of customer option
	int itemPosition;					//position of the item in the cart
	int size;
	string line;						//to get all the lines in file
	string cart;						//getting customer input
	int productNum = 0, userQuantity;	//product customer is entering to get and the quantity
	string adm = "admin";
	string userAttempt, passAttempt;
	inFile.open("ProductData.csv", ios::in | ios::out);

	//create an admin and set a username and password
	Admin adminInfo;
	adminInfo.Username(adm);
	adminInfo.Password(adm);

	//test for file validity
	if (inFile.fail()) {
		cout << "File failed to open" << endl;
		return 0;
	}


	LinkList *invent = new LinkList;			//to point to the inventory and dynamically allocate object
	size = invent->build();							//build inventory link list
	
	do {
		cout << "Choose an option\n";
		cout << "1. Admin" << endl << "2. Customer" << endl << "3. Exit" << endl;
		cin >> modeChoice;

		if (modeChoice == 1) {
			cout << "Enter Admin username and password. This is case sensitive. \n";
			cout << "Username: \n";
			cin >> userAttempt;
			cout << "Password: \n";
			cin >> passAttempt;


			if (adminInfo.validate(userAttempt, passAttempt) == true) {
				do { //allow admin to edit more than once 
					cout << "Enter 1-4 for the option you would like to do\n";
					cout << "1. Add a new product" << endl << "2. Delete a product" << endl << "3. Update a product quantity"
						<< endl << "4. Update a product cost" << endl << "5. Exit" << endl;
					cin >> adminChoice;

					switch (adminChoice) {
					case 1: {
						int data;			//get the new product name that will be added

						cout << "This is the current product inventory." << endl;    //display inventory 
						invent->print();

						cout << "Enter the product number you wish to add\n";
						cin >> data;

						while (data != 0) {										    //allow admin to edit more than once
							size+=invent->addproduct(data);		//add new product to the end of the list
							invent->print();
							cout << "To add another product enter the new product number or enter 0 to end and go back to main." << endl;
							cin >> data;
						}
					}
							break;

					case 2:
						int prodDelete;				//the product to be deleted from inventory

						cout << "This is the current product inventory." << endl;    //display inventory 
						invent->print();

						cout << "Enter the product number you wish to delete\n";
						cin >> prodDelete;

						while (prodDelete != 0) {							//allow admin to edit more than once
							itemPosition = invent->findPosition(prodDelete); //search for the position of the item in the list inventory
							invent->remove(itemPosition);					  // delete the product from list
							cout << "This is the current product inventory." << endl;
							invent->print();
							cout << "To delete another product enter the product number or enter 0 to end and go back to main." << endl;
							cin >> prodDelete;
						}

						break;

					case 3:
						int updateProduct;					//the product that admin will update quantity
						cout << "This is the current product inventory." << endl;    //display inventory 
						invent->print();

						cout << "Enter the product number you wish to update its quantity\n";
						cin >> updateProduct;

						while (updateProduct != 0) {						  //allow admin to edit more than once
							invent->updateQTY(updateProduct);				 // update the product quantity
							cout << "This is the current product inventory." << endl;
							invent->print();
							cout << "To update another product enter the product number or enter 0 to end and go back to main." << endl;
							cin >> updateProduct;
						}

						break;

					case 4:
						int upProduct;					//the product that admin will update quantity
						cout << "This is the current product inventory." << endl;    //display inventory 
						invent->print();

						cout << "Enter the product number you wish to update its cost\n";
						cin >> upProduct;

						while (upProduct != 0) {						  //allow admin to edit more than once
							invent->updateCost(upProduct);					  // update the product quantity
							cout << "This is the current product inventory." << endl;
							invent->print();
							cout << "To update another product enter the product number or enter 0 to end and go back to main." << endl;
							cin >> upProduct;
						}

						break;
					case 5:
						//will end loop and exit
						adminChoice = 0;
						break;

					default:
						cout << "Invalid option.\n";
						break;
					}
				} while (adminChoice != 0);
			}
			break;
		}
		else if(modeChoice==2) {
			LinkList *customer = new LinkList;  //to point to the shopping cart and dynamically allocate object
			Customer user;
			
			//display inventory to customer
			cout << "Enter the word \"cart\" anytime when asked for product number to view your shopping cart." << endl;

			//get user's desired product
			cout << "Please enter the product number for the item you would like." << endl;
			cin >> cart;

			//if user enters the word cart, display their current shopping cart
			if (cart == "cart" || cart == "Cart" || cart == "CART") {
				productNum = stoi(customer->showCart());	//change the cart string to an int
			}
			else {
				productNum = stoi(cart); //change cart string to int 
			}

			/*while customer enters a valid product number, search for the item and get
			  the cost, quantity, and store the items to invoice file. */
			while (productNum != 0) {
				//search to see if product exists
				productNum = search(invent, customer, productNum);

				//for items that exist, get user quantity and calculate total cost for all items purchased
				cout << "Enter quantity amount." << endl;
				cin >> userQuantity;

				if (userQuantity <= 0) {
					cout << "Invalid quantity amount. Enter amount greater than 0." << endl;
					cin >> userQuantity;
				}

				shopCount += customer->searchQTY(invent, customer, productNum, userQuantity, shopCount);

				//set limit to cart up to however many different item type is sold in the inventory, when limit is reached, go to invoice
				if (shopCount > size) {
					cout << "Cart is full, no more products can be entered" << endl;
					break;
				}

				cout << endl << "To add another item, please enter the product number or 0 if done. " << endl;
				cin >> cart;

				//if user enters the word cart, display their current shopping cart
				if (cart == "cart" || cart == "Cart" || cart == "CART") {
					productNum = stoi(customer->showCart());	//change the cart string to an int
				}
				else {
					productNum = stoi(cart); //change cart string to int 
				}

			}

			customer->finalCart();
			cout << "Pick any changes you'd like to make or proceed to checkout.\n";
			do {
				cout << "1.Delete a product." << endl << "2.Update quantity.\n" << "3.Checkout\n";
				cin >> customerLast;

				switch (customerLast) {
				case 1: {
					int prodD;				//the product to be deleted from cart

					cout << "Enter the product number you wish to delete\n";
					cin >> prodD;

					while (prodD != 0) {							//allow admin to edit more than once
						itemPosition = customer->findPosition(prodD); //search for the position of the item in the list inventory
						customer->remove(itemPosition);					  // delete the product from list
						cout << "This is your current cart." << endl;
						customer->finalCart();
						cout << "To delete another product enter the product number or enter 0 to end and go back to options." << endl;
						cin >> prodD;
					}
					break;
				}
				case 2: {
					int upProduct;					//the product that  will update quantity

					cout << "Enter the product number you wish to update its quantity\n";
					cin >> upProduct;

					while (upProduct != 0) {						  //allowt o edit more than once
						customer->updateQTY(invent, customer, upProduct);					  // update the product quantity
						cout << "This is the current product inventory." << endl;
						customer->finalCart();
						cout << "To update another product enter the product number or enter 0 to end and go back to main." << endl;
						cin >> upProduct;
					}
					break;
				}
				case 3: {
					//create invoice and end customer shopping
					customer->invoice(user);
					//delete object from memory and set to null
					delete customer;
					customer = nullptr;
					break;
				}
				default: {
					cout << "Invalid option.\n";
					break;
				}
				}
			} while (customerLast != 3);
			//exit loop and edit inventory file
			modeChoice = 0;
			break;
		}	
		else if (modeChoice == 3) {
		 //exit loop and edit inventory file
		 modeChoice = 0;
		 break;
		}

		else {
		cout << "Invalid option\n";
		}
	}
	while (modeChoice != 0);

	//transfer the quantity in stock after customer purchase to the csv inventory file, update
	invent->updateCVS(inFile);

	//delete the object from memory
	delete invent;

	//make object a nullptr
	invent = nullptr;

	return 0;
}

//search to validate if the item the customer wants is in the inventory
int search(LinkList* inventory, LinkList* customer, int productNum) {
	string cart;						//for customer to call cart
	bool a;

	a = inventory->search(productNum);

	if (a == true) {
		return productNum;
	}

	//if product is not found, have user reenter number
	cout << "Error: Item does not exist. Please enter a new product number." << endl;
	cin >> cart;
	if (cart == "cart" || cart == "Cart" || cart == "CART") {
		productNum = stoi(customer->showCart());	//change the cart string to an int
	}
	else {
		productNum = stoi(cart); //change cart string to int 
	}
	//recall function with new item number
	return  search(inventory, customer, productNum);
}

