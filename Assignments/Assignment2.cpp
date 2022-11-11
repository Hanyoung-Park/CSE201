#include <iostream>
#include <string>
using namespace std;

class Pizza {
    private:
        string type;
        string orderID;
    public:
        Pizza(string t, string oID);
        ~Pizza();
        void prepare();
        void bake();
        void cut();
        void box();
        string getType();
        string getOrderID();
};

Pizza::Pizza(string t, string oID) {
    type = t;
    orderID = oID;
    cout << "Pizza constructor" << endl;
}
Pizza::~Pizza() {
    cout << "Pizza Destructor" << endl;
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

class DeliveryProcessing {
    private:
        int maxNumOrder;
        Pizza** deliveryQueue; //Array of Pizza pointers
        int front, rear;
    public:
        DeliveryProcessing(int maxOrder);
        ~DeliveryProcessing();
        int addOrder(Pizza* newOrder);
        int deliverOrder();
};

DeliveryProcessing::DeliveryProcessing(int maxOrder) {
    front=0;
    rear=0;
    maxNumOrder = maxOrder;
    deliveryQueue = new Pizza*[maxNumOrder];
}
DeliveryProcessing::~DeliveryProcessing() {
    delete[] deliveryQueue;
}
int DeliveryProcessing::addOrder(Pizza* newOrder) {
    if(rear == maxNumOrder) {
        cout << "Queue is full" << endl;
        delete newOrder;
        return 0;
    }
    deliveryQueue[rear] = newOrder;
    cout << "[" << newOrder->getType() << "] is ordered by [" << newOrder->getOrderID() << "]" << endl;
    
    rear++;
    return 1;
};

int DeliveryProcessing::deliverOrder() {
    if(front==rear) {
        cout << "Queue is empty" << endl;
        return 0;
    }
    cout << "[" << deliveryQueue[front]->getType() << "] is delivered to [" << deliveryQueue[front]->getOrderID() << "]" << endl;
    delete deliveryQueue[front];
    
    for(int i=0;i<rear-1;i++) {
        deliveryQueue[i] = deliveryQueue[i+1];
    }
    rear--;
    return 1;
}

class PizzaStore {
private:
    int numOfDeliveryCar;
    DeliveryProcessing* myDeliveryProcessing;
    static int OrderCnt;
public:
    PizzaStore();
    PizzaStore(int n);
    ~PizzaStore();
    Pizza* orderPizza(string type, string orderID);
    Pizza* createPizza(string type, string orderID);
    DeliveryProcessing* getDeliveryProcessingHandler();
    int getTotalOrderCnt();
};

int PizzaStore::OrderCnt = 0;

PizzaStore::PizzaStore() {
    numOfDeliveryCar = 10;
    myDeliveryProcessing = new DeliveryProcessing(numOfDeliveryCar);
    cout << "PizzaStore Constructor" << endl;
}

PizzaStore::PizzaStore(int n) {
    numOfDeliveryCar = n;
    myDeliveryProcessing = new DeliveryProcessing(numOfDeliveryCar);
    cout << "PizzaStore Constructor" << endl;
}

PizzaStore::~PizzaStore() {
    cout << "PizzaStore Destructor" << endl;
}

Pizza* PizzaStore::orderPizza(string type, string orderID) {
    Pizza* pizza = createPizza(type, orderID);
    OrderCnt++;
    cout << "Total orders so far : " << getTotalOrderCnt() << endl;
    pizza->prepare();
    pizza->bake();
    pizza->cut();
    pizza->box();
    return pizza;
}
Pizza* PizzaStore::createPizza(string type, string orderID) {
    Pizza* ptr;
    ptr = new Pizza(type, orderID);
    return ptr;
}
DeliveryProcessing* PizzaStore::getDeliveryProcessingHandler() {
    return myDeliveryProcessing;
}
int PizzaStore::getTotalOrderCnt() {
    return OrderCnt;
}

int main() {
    PizzaStore* newStore = new PizzaStore(5);
    
    Pizza* t_pizza; //Temporary pointer to the pizza
    t_pizza = newStore->orderPizza("cheese", "tom");
    newStore->getDeliveryProcessingHandler()->addOrder(t_pizza);
    
    t_pizza = newStore->orderPizza("cheese", "nick");
    newStore->getDeliveryProcessingHandler()->addOrder(t_pizza);
    
    t_pizza = newStore->orderPizza("cheese", "jack");
    newStore->getDeliveryProcessingHandler()->addOrder(t_pizza);
    
    t_pizza = newStore->orderPizza("pepperoni", "jenny");
    newStore->getDeliveryProcessingHandler()->addOrder(t_pizza);
    
    t_pizza = newStore->orderPizza("pepperoni", "kate");
    newStore->getDeliveryProcessingHandler()->addOrder(t_pizza);
    
    t_pizza = newStore->orderPizza("pepperoni", "nana");
    newStore->getDeliveryProcessingHandler()->addOrder(t_pizza);
    
    newStore->getDeliveryProcessingHandler()->deliverOrder();
    newStore->getDeliveryProcessingHandler()->deliverOrder();
    newStore->getDeliveryProcessingHandler()->deliverOrder();
    newStore->getDeliveryProcessingHandler()->deliverOrder();
    newStore->getDeliveryProcessingHandler()->deliverOrder();
    newStore->getDeliveryProcessingHandler()->deliverOrder();
    newStore->getDeliveryProcessingHandler()->deliverOrder();
    newStore->getDeliveryProcessingHandler()->deliverOrder();
    delete newStore;
    return 0;
}
