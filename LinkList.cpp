#include "LinkList.h"
using namespace std;


LinkList::LinkList()
{
	this->head = nullptr;
}

LinkList::LinkList(int num, string name, double cost, int qty) {
	Inventory* newNode = new Inventory;			//Create a new node to add to the front of the list

	newNode->itemNumber = num;					//Store the data inside the new node
	newNode->itemName = name;
	newNode->itemCost = cost;
	newNode->itemQty = qty;
	newNode->next = head;						//Set the new node next equal to the orginal head

	head = newNode;								//Set the orginal head to point to the new node.
}

LinkList LinkList:: operator+ (const LinkList &add) {
	Inventory* Head = add.head;			//Create a temporary node to keep track of the orginal head node
	Inventory* current = NULL;				//Create a temporary node to use to transverse through the linked list
	Inventory* newNode = add.head;	    //Create a new node to add to the end of the list

	if (!head) {									//Check to see if linked list is empty
		head = newNode;								//If it is append the new node onto the empty list
	}
	else {
		current = Head;								//Set the current node to the head node

		while (current->next) {						//Traverse the linked list until you reach the end
			current = current->next;
		}
		current->next = newNode;					//At the end set the current to point to the new node.
	}
	this->head = Head;								//Return the new linked list to the calling function
	return add;
}

LinkList::~LinkList()
{
	this->head = nullptr;
}

//build inventory
int LinkList::build() {
	fstream inFile;
	int Linecount = 0;					//count how many lines(products) are in inventory file
	string line;						//to get all the lines in file
	inFile.open("ProductData.csv", ios::in | ios::out);

	//count how many products are in inventory file
	while (getline(inFile, line)) {
		Linecount++;
	}
	
	inFile.close();
	inFile.open("ProductData.csv", ios::in | ios::out);

	int num,name, qty;									//takes the number, name, and quantity from the cvs file and store it into the product structure
	double price;										//takes the cost of items from cvs file and store it into the product structure
	string Name;
	Inventory* Head = new Inventory;
	Inventory* current = NULL;

	inFile.seekg(0L, ios::beg);
	inFile >> num;
	inFile.seekg(8L, ios::cur);
	inFile >> name;
	inFile.seekg(1L, ios::cur);
	inFile >> price;
	inFile.seekg(1L, ios::cur);
	inFile >> qty;


	Name = to_string(name);

	Head->next = NULL;
	Head->itemNumber = num;						//holds the item number
	Head->itemName = Name;						//holds the item name
	Head->itemCost = price;					    //holds the item cost
	Head->itemQty = qty;						//holds the item cost

	for (int i = 1; i <= Linecount - 1; i++) {
		Inventory* newNode = new Inventory;
		//read and store each line to a variable
		inFile.seekg(2L, ios::cur);
		inFile >> num;
		inFile.seekg(8L, ios::cur);
		inFile >> name;
		inFile.seekg(1L, ios::cur);
		inFile >> price;
		inFile.seekg(1L, ios::cur);
		inFile >> qty;
		Name = to_string(name);

		//create link list
		if (i == 1) {
			//store first product as head of link list
			Head->next = newNode;
			newNode->itemNumber = num;
			newNode->itemName = Name;
			newNode->itemCost = price;
			newNode->itemQty = qty;
			current = newNode;
		}
		else {
			//continue to make link list
			current->next = newNode;
			newNode->itemNumber = num;
			newNode->itemName = Name;
			newNode->itemCost = price;
			newNode->itemQty = qty;
			current = newNode;
		}
	}
   // current->next = NULL;
	this->head = Head;

	return Linecount;
}

//print inventory
void LinkList::print() {
	//Create a temporary node to keep track of the orginal head node
	Inventory* head = this->head;
	
	//traverse through the list and print out everything in inventory
	cout << "Item Number " << setw(13) << "Item name" << setw(18) << "Unit Cost" << setw(10) << "Qty" << setw(15) << endl;
	cout << "--------------------------------------------------------------" << endl;
	while (head) {
		cout << setw(16) << left << fixed << setprecision(0) << head->itemNumber;
		cout << "Product " << setw(9) << left << head->itemName << "  ";
		cout << fixed << setprecision(2) << setw(13) << left << head->itemCost << "  ";
		cout << left << head->itemQty << endl;
		head = head->next;
	}
}

//add item to link list
int LinkList::addproduct( int data) {
	int  qty;								//info for the new product
	double price;
	string name;
	Inventory* Head = this->head;			//Create a temporary node to keep track of the orginal head node
	Inventory* current = NULL;				//Create a temporary node to use to transverse through the linked list
	Inventory* newNode = new Inventory;	    //Create a new node to add to the end of the list

	cin.ignore();

	//Set the Node Data
	newNode->itemNumber = data;
	cout << "Enter the name for this item.\n";
	getline(cin, name);
	newNode->itemName = name;
	cout << "Enter the price for this item.\n";
	cin >> price;
	cout << "Enter the quantity amount for this item.\n";
	cin >> qty;
	newNode->itemQty = qty;
	newNode->itemCost = price;
	newNode->next = NULL;

	if (!head) {									//Check to see if linked list is empty
		head = newNode;								//If it is append the new node onto the empty list
	}
	else {
		current = Head;								//Set the current node to the head node

		while (current->next) {						//Traverse the linked list until you reach the end
			current = current->next;
		}
		current->next = newNode;					//At the end set the current to point to the new node.
	}
	this->head = Head;								//Return the new linked list to the calling function

	return 1;
}

//find where the product position is in link list
int LinkList::findPosition(int data) {
	Inventory* current = head;		//Create a temporary node to keep track of the current node
	int count = 0;				    //counts the position
	int prod;						//for customer to call cart

	while (current != NULL) {					   //Loop through the list until we find the end
		if (current->itemNumber == data) {   //if the data is found return the product number
			//if the item exist, display the item's name and cost
			return count;
		}
		count++;
		current = current->next;   //Set the current node to the next node
	}

	//if product is not found, have user reenter number
	cout << "Error: Item does not exist. Please enter a new product number." << endl;
	cin >> prod;

	if (prod == 0) {
		return prod;
	}

	//recall function with new item number
	return  findPosition(prod);
}

//search to see if item exist
bool LinkList::search(int data) {
	Inventory* current = head;	//Create a temporary node to keep track of the current node
	while (current != NULL) {          //Loop through the list until we find the end
		if (current->itemNumber == data) {   //if the data is found return the product number
			//if the item exist, display the item's name and cost
			cout << "Item name Product " << current->itemName <<
				" cost $" << fixed << setprecision(2) << current->itemCost << endl;
			return true;
		}
		current = current->next;   //Set the current node to the next node
	}
	return false;
}

//get rid of item from link list
void LinkList::remove(int data) {
	Inventory* currentNode = head;				//Create a temporary node to use to transverse through the linked list
	Inventory* previousNode = head;			//Create a temporary node to keep track of the previous node
	int count = 0;

	if (data == 0) {							    //if removing node in position 0, delete the head and set the head to next
		head = currentNode->next;
		delete currentNode;
	}
	else {
		//skip all nodes whos position is not equal to the one that will be removed 
		while (currentNode != nullptr && count != data) {
			previousNode = currentNode;
			currentNode = currentNode->next;
			count++;
		}
		//delete the node when position is found
		if (count == data) {
			previousNode->next = currentNode->next;
			delete currentNode;
		}
	}
}

//update quantity of item for admin
int LinkList::updateQTY(int data) {
	Inventory* currentNode = head;				//Create a temporary node to use to transverse through the linked list
	Inventory* Head = head;					//Create a temporary node to keep track of the orginal head node
	currentNode = Head;
	int newQuantity;									//new quantity for the item

	while (currentNode != NULL) {
		if (currentNode->itemNumber == data) {
			cout << "Enter the new quantity for product " << data << ".\n";
			cin >> newQuantity;
			currentNode->itemQty = newQuantity;
			head = Head;									//Return the new linked list to the calling function
			return 0;
		}
		currentNode = currentNode->next;
	}

	//if item entered was not found, ask admin to enter the product number again
	cout << "Error: Invalid product number entered. Reenter the product number you wish to update.\n";
	cin >> data;

	return updateQTY(data);

}

//update cost of item
int LinkList::updateCost(int data) {
	Inventory* currentNode = head;				//Create a temporary node to use to transverse through the linked list
	Inventory* Head = head;					//Create a temporary node to keep track of the orginal head node
	currentNode = Head;
	double newCost;									//new quantity for the item

	while (currentNode != NULL) {
		if (currentNode->itemNumber == data) {
			cout << "Enter the new cost for product " << data << ".\n";
			cin >> newCost;
			currentNode->itemCost = newCost;
			head = Head;									//Return the new linked list to the calling function
			return 0;
		}
		currentNode = currentNode->next;
	}

	//if item entered was not found, ask admin to enter the product number again
	cout << "Error: Invalid product number entered. Reenter the product number you wish to update.\n";
	cin >> data;

	return updateQTY(data);
}

//display current shopping cart
string LinkList::showCart() {
	Inventory* current = head;		//Create a temporary node to keep track of the current node
	double Subtotal = 0;						//calculate the subtotal from the current shopping cart
	string cart;								//takes in a new item number or redisplay the showCart function

	//format to display what's in the current shopping cart
	cout << "Your current shopping cart:" << endl;
	cout << "Item Number " << setw(17) << "Item name" << setw(15) << "Qty" << setw(22) << "Unit Cost" << setw(20) << "Total" << endl;
	cout << "--------------------------------------------------------------------------------------------------" << endl;

	while (current != NULL) {			//Loop through the list until we find the end

		cout << setw(20) << left << fixed << setprecision(0) << current->itemNumber;
		cout << "Product ";
		cout << setw(13) << left << current->itemName;
		cout << setw(17) << left << current->itemQty;
		cout << fixed << setprecision(2) << setw(23) << left << current->itemCost;
		cout << setw(20) << left << current->itemQty * current->itemCost << endl;
		Subtotal += (current->itemQty * current->itemCost);
		current = current->next;		//Set the current node to the next node
	}

	cout << "--------------------------------------------------------------------------------------------------" << endl;
	cout << right << setw(81) << "Total: $" << Subtotal << endl;

	//get user's desired product to proceed on shopping
	cout << "To add another item, please enter the product number or 0 if done." << endl;
	cin >> cart;

	//if user reenters cart then redisplay the showCart function
	if (cart == "cart" || cart == "Cart" || cart == "CART") {
		return showCart();
	}
	//if not, return the new desired product
	return cart;
}

//display everything in cart
void LinkList::finalCart() {
	Inventory* current = head;		//Create a temporary node to keep track of the current node
	double Subtotal = 0;						//calculate the subtotal from the current shopping cart

	//format to display what's in the current shopping cart
	cout << "Your current shopping cart:" << endl;
	cout << "Item Number " << setw(17) << "Item name" << setw(15) << "Qty" << setw(22) << "Unit Cost" << setw(20) << "Total" << endl;
	cout << "--------------------------------------------------------------------------------------------------" << endl;

	while (current != NULL) {			//Loop through the list until we find the end

		cout << setw(20) << left << fixed << setprecision(0) << current->itemNumber;
		cout << "Product ";
		cout << setw(13) << left << current->itemName;
		cout << setw(17) << left << current->itemQty;
		cout << fixed << setprecision(2) << setw(23) << left << current->itemCost;
		cout << setw(20) << left << current->itemQty * current->itemCost << endl;
		Subtotal += (current->itemQty * current->itemCost);
		current = current->next;		//Set the current node to the next node
	}

	cout << "--------------------------------------------------------------------------------------------------" << endl;
	cout << right << setw(81) << "Total: $" << Subtotal << endl;
}

//update the product csv file
void LinkList::updateCVS(fstream & inFile) {
	Inventory* current = head;		//Create a temporary node to keep track of the current node
	inFile.close();
	inFile.open("ProductData.csv", ios::out | ios::trunc);


	while (current != NULL) {			//Loop through entire list
		if (current->itemQty == 0) {
			//do not add items with 0 quantity back into inventory, go to next product
			current = current->next;
		}
		else {
			//store everything from inventory to the csv file
			inFile << current->itemNumber << ",";
			inFile << "Product ";
			inFile << current->itemName << ",";
			inFile << fixed << setprecision(2) << current->itemCost << ",";
			inFile << current->itemQty << endl;
			current = current->next;
		}
	}
}

//add item to cart
void LinkList::appendCart( int productNum, int userQuantity, string name, double itemPrice) {
	Inventory* Head = head;				//Create a temporary node to keep track of the orginal head node
	Inventory* current = NULL;					//Create a temporary node to use to transverse through the linked list
	Inventory* newNode = new Inventory;	    //Create a new node to add to the end of the list

	//Set the Node Data
	newNode->itemNumber = productNum;
	newNode->itemName = name;
	newNode->itemCost = itemPrice;
	newNode->itemQty = userQuantity;
	newNode->next = NULL;


	current = Head;								//Set the current node to the head node

	while (current->next) {						//Traverse the linked list until you reach the end
		current = current->next;
	}
	current->next = newNode;				//At the end set the current to point to the new node.

	head = Head;							//Return the new linked list to the calling function

}

//search to see if item wanted is in stock
int LinkList::searchQTY(LinkList* inventory, LinkList* customer, int productNum, int userQuantity, int &shopCount) {
	Inventory* current = inventory->head;		//Create a temporary node to keep track of the current node
	double itemPrice;						//price of the product item
	string name;								//name of product

	while (current != NULL) {					   //Loop through the list until we find the end
		if (current->itemNumber == productNum) {   //if the data is found return its position
			if (current->itemQty >= userQuantity) {
				//Create a temporary node to keep track of the current cart to test if the product is already in cart
				Inventory* test = customer->head;
				Inventory* shopHead = new Inventory;
				Inventory* cartCurrent = NULL;
				shopHead->next = NULL;

				//compare the user's shopping cart to see if item has already been added to their cart 
				while (test != NULL) {
					if (test->itemNumber == productNum) {
						//if item already exist in cart, simply add to the previous quantity
						test->itemQty += userQuantity;
						current->itemQty -= userQuantity;
						return 0;
					}
					test = test->next;
				}

				//create head of shopping cart
				if (shopCount == 0) {
					shopHead->itemQty = userQuantity;
					shopHead->itemNumber = current->itemNumber;
					shopHead->itemName = current->itemName;
					shopHead->itemCost = current->itemCost;

					//update product inventory
					current->itemQty -= userQuantity;
					customer->head = shopHead;
					return 1;
				}

				//add item to shopping cart
				itemPrice = current->itemCost;
				name = current->itemName;


				customer->appendCart(productNum, userQuantity, name, itemPrice);
				current->itemQty -= userQuantity;				//update product inventory
				return 1;

			}
			//ask to reenter desired quality as initial desired is more than what's in stock, recheck if new quantity desire is available
			else if ((current->itemQty > 0) && (current->itemQty < userQuantity)) {
				cout << "Not enough quantity in stock, please reenter quantity." << endl;
				cin >> userQuantity;

				//call the searchQty function again with the new desired quantity
				return searchQTY(inventory, customer, productNum, userQuantity, shopCount);
			}
			//quantity of product availanble is 0
			else {
				cout << "This product is out of stock" << endl;
				return 0;
			}
		}
		current = current->next;   //Set the current node to the next node
	}

	return 0;
}

//user update qty in cart
int LinkList::updateQTY(LinkList* inventory, LinkList* customer, int data) {
	Inventory* currentNode = customer->head;				//Create a temporary node to use to transverse through shopping cart
	Inventory* Head = customer->head;					//Create a temporary node to keep track of the orginal head node
	currentNode = Head;
	int newQuantity;									//new quantity for the item

	while (currentNode != NULL) {
		if (currentNode->itemNumber == data) {
			//if item is found in cart, get new qty
			cout << "Enter the new quantity for product number " << data << ".\n";
			cin >> newQuantity;

			Inventory* current = inventory->head;				//Create a temporary node to use to transverse through inventory
			Inventory* HEAD = inventory->head;					//Create a temporary node to keep track of the orginal head node
			current = HEAD;
			while (current != NULL) {
				//find item qty in inventory
				if (current->itemNumber == data) {
					//add back all the qty to inventory which will later be deleted
					current->itemQty += currentNode->itemQty;
					//if new qty is available, proceed
					if ((current->itemQty) >= newQuantity) {
						//set shopping cart to new qty and delete the qty from inventory
						currentNode->itemQty = newQuantity;
						current->itemQty -= newQuantity;
						//Return the new linked list to the calling function
						inventory->head = HEAD;
						customer->head = Head;									
						return 0;
						
					}
					else {
						cout << "Not enough quantity available, please reenter quantity desired.\n";
						return updateQTY(inventory, customer, data);
					}
				}
				current = current->next;
			}

		}
		currentNode = currentNode->next;
	}

	//if item entered was not found, ask admin to enter the product number again
	cout << "Error: Invalid product number entered. Reenter the product number you wish to update.\n";
	cin >> data;

	return updateQTY(inventory, customer, data);

}

//create user invoice
void LinkList::invoice(Customer user) {
	//get user info
	string lastName = user.getlast();
	string firstName = user.getfirst();
	string Address = user.getadd();
	string City = user.getcity();
	string State = user.getstate();
	int zipcode = user.getzip();

	string i = "_Invoice.txt";
	string file = lastName + i;
	fstream invoiceFile(file);				//create an invoice file after customer is finished shopping
	invoiceFile.open(file, ios::out);

	Inventory* currentInvoice = head;	//Create a temporary node to keep track of the current node
	Inventory* current = head;			//Create a temporary node to keep track of the current node
	double subtotal = 0;							//calculate the subtotal of everthing in the cart


	invoiceFile << "Customer Name: " << firstName << " " << lastName << endl;
	invoiceFile << "Customer Address: " << Address << endl;
	invoiceFile.seekg(18L, ios::cur);
	invoiceFile << City << ", ";
	invoiceFile << State << " ";
	invoiceFile << zipcode << endl << endl;

	//Format invoice file and display heading for purchases
	invoiceFile << "Item Number " << setw(17) << "Item name" << setw(15) << "Qty" << setw(22) << "Unit Cost" << setw(20) << "Total" << endl;
	invoiceFile << "--------------------------------------------------------------------------------------------------" << endl;

	//send everything from the shopping cart to be in the invoice file

	while (currentInvoice != NULL) {			//Loop through the list until we find the end
		invoiceFile << setw(20) << left << fixed << setprecision(0) << currentInvoice->itemNumber;
		invoiceFile << "Product ";
		invoiceFile << setw(13) << left << currentInvoice->itemName;
		invoiceFile << setw(17) << left << currentInvoice->itemQty;
		invoiceFile << fixed << setprecision(2) << setw(23) << left << currentInvoice->itemCost;
		invoiceFile << setw(20) << left << currentInvoice->itemQty * currentInvoice->itemCost << endl;
		subtotal += (currentInvoice->itemQty * currentInvoice->itemCost);
		currentInvoice = currentInvoice->next;		//Set the current node to the next node
	}
	invoiceFile << "--------------------------------------------------------------------------------------------------" << endl;
	invoiceFile << right << setw(81) << "Total: $" << subtotal;                  //Display subtotal for every item purchased

	invoiceFile.close();

	//Display everything found in invoice directly for user to see
	cout << "Customer Name: " << firstName << " " << lastName << endl;
	cout << "Customer Address: " << Address << endl;
	cout << setw(22) << City << ", " << State << " " << zipcode << endl << endl;

	finalCart();
}