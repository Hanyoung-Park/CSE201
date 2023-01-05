/*
* Assignment 3
*/
//Factory Pattern
#include <iostream>
#include <string>
using namespace std;

//Pizza class
class Pizza {
protected:
	string type;
	string dough; //Added
	string sauce;  //Added
	string toppings;	//Added: A list of toppings
	string orderID;	//order ID

public:
	Pizza() { cout << "Pizza Default Constructor" << endl; };		//Default Constructor
	Pizza(string t, string oID); //Constructor	
	virtual ~Pizza();  //Destructor
	void prepare();
	void bake();
	//void cut();
	virtual void cut(); //Virtual destructor
	void box();
	string getType();
	string getOrderID();
};

Pizza::Pizza(string t, string oID) : type(t), orderID(oID)
{
	cout << "Pizza constructor" << endl;
}
void Pizza::prepare() {
	cout << "Prepare all ingredients" << endl;
}
void Pizza::bake() {
	cout << "Bake for 25 minutes at 350" << endl;
}
void Pizza::cut() {
	cout << "Cutting the pizza into diagonal slices" << endl;
}
void Pizza::box() {
	cout << "Place pizza in official PizzaStore box" << endl;
}
string Pizza::getType() {
	return type;
}
string Pizza::getOrderID() {
	return orderID;
}
Pizza::~Pizza() { cout << "Pizza Destructor" << endl; }

//class PaPaStyleCheesePizza //Added
class PaPaStyleCheesePizza : public Pizza {
public:
	PaPaStyleCheesePizza(string oID);
	~PaPaStyleCheesePizza();
};

//constructor
PaPaStyleCheesePizza::PaPaStyleCheesePizza(string oID) {
	type = "PAPA Style Sauce and Cheese Pizza";
	dough = "Thin Crust Dough";
	sauce = "Marinara Sauce";
	toppings = toppings + " Grated Reggiano Cheese";
	this->orderID = oID;
}

//Destructor
PaPaStyleCheesePizza::~PaPaStyleCheesePizza() { cout << "PaPaStyleCheesePizza Destructor" << endl; }

//class PapaStylePepperoniPizza
class PaPaStylePepperoniPizza : public Pizza {
public:
	PaPaStylePepperoniPizza(string oID);
	~PaPaStylePepperoniPizza();
};

//constructor
PaPaStylePepperoniPizza::PaPaStylePepperoniPizza(string oID) {
	type = "PAPA Style Sauce and Pepernoni Pizza";
	dough = "Thin Crust Dough";
	sauce = "Marinara Sauce";
	toppings = toppings + " Grated Reggiano Cheese";
	this->orderID = oID;
}
//destructor
PaPaStylePepperoniPizza::~PaPaStylePepperoniPizza() { cout << "PapaStylePepperoniPizza Destructor" << endl; }

//class DominoStyleCheesePizza
class DominoStyleCheesePizza : public Pizza {
public:
	DominoStyleCheesePizza(string oID);
	~DominoStyleCheesePizza();
	void cut(); //override
};

DominoStyleCheesePizza::DominoStyleCheesePizza(string oID) {
	type = "Domino Style Deep Dish Cheese Pizza";
	dough = "Extra Thick Crust Dough";
	sauce = "Plum Tomata Sauce";
	toppings = toppings + "Shredded Mozzarella Cheesse";
	this->orderID = oID;
}

DominoStyleCheesePizza::~DominoStyleCheesePizza()
{
	cout << "DominoStyleCheesePizza Destructor" << endl;
}

void DominoStyleCheesePizza::cut() {
	cout << "Cutting the pizza into square slices" << endl;
}

//class DominoStylePepperoniPizza
class DominoStylePepperoniPizza : public Pizza {
public:
	DominoStylePepperoniPizza(string oID);
	~DominoStylePepperoniPizza();
	void cut(); //override
};

DominoStylePepperoniPizza::DominoStylePepperoniPizza(string oID) {
	type = "Domino Style Deep Dish Pepperoni Pizza";
	dough = "Extra Thick Crust Dough";
	sauce = "Plum Tomata Sauce";
	toppings = toppings + "Shredded Mozzarella Cheesse";
	this->orderID = oID;
}

DominoStylePepperoniPizza::~DominoStylePepperoniPizza() { cout << "DominoStylePepperoniPizza Destructor" << endl; }

void DominoStylePepperoniPizza::cut() {
	cout << "Cutting the pizza into square slices" << endl;
}


//class Delivery processing
class DeliveryProcessing {
private:
	int maxNumOrder;
	Pizza** deliveryQueue; //Array of Pizza pointers
	int front, rear;
	//static int OrderCnt;
public:
	DeliveryProcessing(int maxOrder);
	~DeliveryProcessing();
	int addOrder(Pizza* newOrder);
	int deliverOrder();
    Pizza** getDeliveryQueue() {return deliveryQueue;}
    int getLength() {return rear-front;}
	//int getTotalOrderCnt();//Return the total number of orders so far	
};

//Constructor
DeliveryProcessing::DeliveryProcessing(int maxOrder) {
	//cout << "Order Processing class is created: Max Order Number [" << maxOrder << "]" << endl;
	maxNumOrder = maxOrder;
	front = rear = 0;
	deliveryQueue = new Pizza * [maxOrder];
}

//Destructor
DeliveryProcessing::~DeliveryProcessing() {
	cout << "DeliveryProcessing Destructor" << endl;
	//Deallocate the memory
	for (int i = 0; i < this->maxNumOrder; i++) {
		delete deliveryQueue[i];
	}
	delete[] deliveryQueue;
	//cout << "Destructur called : [" << "OrderProcessing" << "]" << endl;
}

//Implementation: https://www.geeksforgeeks.org/array-implementation-of-queue-simple/
//Add an order (Return 0: fail, Return 1: success)
int DeliveryProcessing::addOrder(Pizza* newOrder) {
	if (maxNumOrder == rear) {
		cout << "Queue is full" << endl;
		//cout << "Total orders so far : " << getTotalOrderCnt() << endl;
		delete newOrder; //Newly added
		return 0;
	}
	else {
		//OrderCnt++;		//Increase an order count
		deliveryQueue[rear] = newOrder;
		rear++;
		cout << "[" << newOrder->getType() << "] is ordered by [" << newOrder->getOrderID() << "]" << endl;

		//cout << "Total orders so far : " << getTotalOrderCnt() << endl;
		return 1;
	}
}

//Remove an order (delete an item from the front of the queue) (Return 0: fail, Return 1: success)
int DeliveryProcessing::deliverOrder() {
	if (front == rear) {
		cout << "Queue is empty" << endl;
		//cout << "Total orders so far : " << getTotalOrderCnt() << endl;
		return 0;
	}
	else {
		//if queue is not empty
		cout << "[" << deliveryQueue[front]->getType() << "] is delivered to [" << deliveryQueue[front]->getOrderID() << "] " << endl;

		//Deallocate memory of the delivered pizza
		delete deliveryQueue[front];

		for (int i = 0; i < rear - 1; i++) {
			deliveryQueue[i] = deliveryQueue[i + 1];
		}
		//decrement rear
		rear--;
		return 1;
	}
}


//class PizzaStore

//Assignment 3
class PizzaStore {
protected:
    int numOfDeliveryCar;
    DeliveryProcessing* myDeliveryProcessing;
    static int OrderCnt;
public:
    PizzaStore();
    PizzaStore(int n);
    virtual ~PizzaStore();
    Pizza* orderPizza(string type, string orderID);
    virtual Pizza* createPizza(string type, string orderID) = 0;
    DeliveryProcessing* getDeliveryProcessingHandler();
    int getTotalOrderCnt();
    string operator[](int index); //Implement this
};

//Initialize static member
int PizzaStore::OrderCnt = 0;
int PizzaStore::getTotalOrderCnt() { return OrderCnt; }


PizzaStore::PizzaStore() : numOfDeliveryCar(10) {
	cout << "PizzaStore constructor" << endl;
	myDeliveryProcessing = new DeliveryProcessing(numOfDeliveryCar);
}
PizzaStore::PizzaStore(int n) {
	cout << "PizzaStore constructor" << endl;
	myDeliveryProcessing = new DeliveryProcessing(n);
}

PizzaStore::~PizzaStore() { cout << "PizzaStore Destructor" << endl; }

DeliveryProcessing* PizzaStore::getDeliveryProcessingHandler()
{
	return myDeliveryProcessing;
}

Pizza* PizzaStore::orderPizza(string type, string orderID) {
	Pizza* pizza;
	pizza = createPizza(type, orderID);
	OrderCnt++;		//Increase an order count
	cout << "Total orders so far : " << getTotalOrderCnt() << endl;
	pizza->prepare();
	pizza->bake();
	pizza->cut();
	pizza->box();

	return pizza;
}

string PizzaStore::operator[] (int index) {
    if(index>=myDeliveryProcessing->getLength()) {
        return "";
    }
    return myDeliveryProcessing->getDeliveryQueue()[index]->getType();
}

class PaPaPizzaStore : public PizzaStore {
public:
	PaPaPizzaStore();
	~PaPaPizzaStore();
	Pizza* createPizza(string item, string orderID);
};

PaPaPizzaStore::PaPaPizzaStore() {
	cout << "PaPaPizzaStore constructor" << endl;
}

PaPaPizzaStore::~PaPaPizzaStore()
{
	cout << "PaPaPizzaStore Destructor" << endl;
}

Pizza* PaPaPizzaStore::createPizza(string item, string orderID) {
	if (item == "cheese") {
		return new PaPaStyleCheesePizza(orderID);
	}
	else if (item == "pepperoni") {
		return new PaPaStylePepperoniPizza(orderID);
	}
}

//class DominoPizzaStore
class DominoPizzaStore : public PizzaStore {
public:
	DominoPizzaStore();
	~DominoPizzaStore();
	Pizza* createPizza(string item, string orderID);
};

DominoPizzaStore::DominoPizzaStore() {
	cout << "DominoPizzaStore constructor" << endl;
}
DominoPizzaStore::~DominoPizzaStore()
{
	cout << "DominoPizzaStore Destructor" << endl;
}


Pizza* DominoPizzaStore::createPizza(string item, string orderID) {
	if (item == "cheese") {
		return new DominoStyleCheesePizza(orderID);
	}
	else if (item == "pepperoni") {
		return new DominoStylePepperoniPizza(orderID);
	}
}


int main() {
    PizzaStore* papaStore = new PaPaPizzaStore();
    PizzaStore* dominoStore = new DominoPizzaStore();
    Pizza* pizza_papa_1 = papaStore->orderPizza("cheese", "tom");
    cout << pizza_papa_1->getType() << endl;
    papaStore->getDeliveryProcessingHandler()->addOrder(pizza_papa_1);
    cout << "PaPaStore[0]: " << (*papaStore)[0] << " PaPaStore[1]: " << (*papaStore)[1] << endl;
    Pizza* pizza_papa_2 = papaStore->orderPizza("pepperoni", "nick");
    cout << pizza_papa_2->getType() << endl;
    papaStore->getDeliveryProcessingHandler()->addOrder(pizza_papa_2);
    cout << "PaPaStore[0]: " << (*papaStore)[0] << " PaPaStore[1]: " << (*papaStore)[1] << endl;
    Pizza* pizza_domino_1 = dominoStore->orderPizza("cheese", "jenny");
    cout << pizza_domino_1->getType() << endl;
    Pizza* pizza_domino_2 = dominoStore->orderPizza("pepperoni", "kate");
    cout << pizza_domino_2->getType() << endl;
    dominoStore->getDeliveryProcessingHandler()->addOrder(pizza_domino_1);
    dominoStore->getDeliveryProcessingHandler()->addOrder(pizza_domino_2);
    cout << "DominoStore[0]: " << (*dominoStore)[0] << " DominoStore[1]: " << (*dominoStore)[1] << endl;
    papaStore->getDeliveryProcessingHandler()->deliverOrder();
    dominoStore->getDeliveryProcessingHandler()->deliverOrder();
    cout << "PaPaStore[0]: " << (*papaStore)[0] << " PaPaStore[1]: " << (*papaStore)[1] << endl;
    cout << "DominoStore[0]: " << (*dominoStore)[0] << " DominoStore[1]: " << (*dominoStore)[1] << endl;
    return 0;
}