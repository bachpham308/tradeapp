// TradeApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdio>
#include <io.h>
#include <fcntl.h>

using namespace std;


/*поставщик*/
class Supplier {
private:
	Supplier() {

	}
	Supplier(const Supplier& copy) {

	}
public:
	string name;
	string address;

	Supplier(string name, string address) {
		this->name = name;
		this->address = address;
	}
};


/*склад*/
class Store {
protected:
	Store() {

	}
	Store(const Store& copy) {

	}
public:
	string name;
	string address;

	Store(string name, string address) {
		this->name = name;
		this->address = address;
	}
};

/*оптовый склад*/
class Warehouse : public Store {
public:
	Warehouse(string name, string address) : Store(name, address) {}
};

/*розничный магазин*/
class Shop : public Store {
public:
	Shop(string name, string address) : Store(name, address) {}
};

/*клиенты*/
class Client {
private:
	Client() {

	}
	Client(const Client& copy) {

	}
protected:
	string name;
	string address;

	Client(string name, string address) {
		this->name = name;
		this->address = address;
	}

public:
	string getName() {
		return name;
	}
};

/*оптовый клиент*/
class StoreClient : public Client {
public:
	StoreClient(string name, string address) : Client(name, address) {}
};

/*розничный клиент*/
class ShopClient : public Client {
public:
	ShopClient(string name, string address) : Client(name, address) {}
};

/*товар*/
class Product {
private:
	Product() {

	}
	Product(const Product& copy) {

	}
protected: 
	Supplier* supplier;
	string name;
	int placeAmt;
	float price;

	Product(Supplier* supplier, string name, int placeAmt, float price) {
		this->supplier = supplier;
		this->name = name;
		this->placeAmt = placeAmt;
		this->price = price;
	}

public: 
	string getName() {
		return name;
	}

	int getPlaceAmt() {
		return placeAmt;
	}

	float getPrice() {
		return price;
	}

	Supplier* getSupplier() {
		return supplier;
	}
};

/*типы товаров*/
class Food : public Product {
public:
	Food(Supplier* supplier, string name, int placeAmt, float price) : Product(supplier, name, placeAmt, price) {}
};

class Drink : public Product {
public:
	Drink(Supplier* supplier, string name, int placeAmt, float price) : Product(supplier, name, placeAmt, price) {}
};

class Furniture : public Product {
public:
	Furniture(Supplier* supplier, string name, int placeAmt, float price) : Product(supplier, name, placeAmt, price) {}
};

class Electronic : public Product {
public:
	Electronic(Supplier* supplier, string name, int placeAmt, float price) : Product(supplier, name, placeAmt, price) {}
};

/*партия товаров*/
class ProductsPart {
private:
	vector<Product*>* products;
	Client* client;

	ProductsPart(const ProductsPart& copy) {

	}
public:
	ProductsPart(Client* client) {
		this->client = client;
		products = new vector<Product*>();
	}

	void add(Product* product) {
		products->push_back(product);
	}

	void add(vector<Product*>* products) {
		this->products = products;
	}

	Product* getProduct(string name) {
		vector<Product*>::iterator it = find_if(products->begin(), products->end(), [&](Product* const& p) { return p->getName() == name; });
		return *it;
	}

	Client* getClient() {
		return client;
	}

	float getSumPrice() {
		float sum = 0;
		for_each(products->begin(), products->end(), [&](Product* const& p) {
			sum += p->getPrice();
		});
		return sum;
	}

	int getSumPlaceAmt() {
		int sum = 0;
		for_each(products->begin(), products->end(), [&](Product* const& p) {
			sum += p->getPlaceAmt();
		});
		return sum;
	}
};

/*грузовик для рассылки по клиентам*/
class Truck {
private:
	int capacity;
	Client* client;
	ProductsPart* productsPart;

	Truck(const Truck& copy) {

	}
public:
	Truck(int capacity) {
		this->capacity = capacity;
	}

	void setProductsPart(ProductsPart* productPart) {
		this->productsPart = productPart;
	}

	void setClient(Client* client) {
		this->client = client;
	}
};


class Trade {
private:
	vector<Truck*>* trucks;
	vector<Supplier*>* suppliers;
	vector<Product*>* products;
	vector<ProductsPart*>* productsParts;
	vector<Store*>* stores;
	vector<Client*>* clients;

public:
	Trade() {
		trucks = new vector<Truck*>();
		suppliers = new vector<Supplier*>();
		products = new vector<Product*>();
		productsParts = new vector<ProductsPart*>();
		stores = new vector<Store*>();
		clients = new vector<Client*>();
	}

	vector<Supplier*>* getSuppliers() {
		return suppliers;
	}

	vector<ProductsPart*>* getProductsParts() {
		return productsParts;
	}

	void add(Truck* truck) {
		trucks->push_back(truck);
	}

	void add(Supplier* supplier) {
		suppliers->push_back(supplier);
	}

	void add(Product* product) {
		products->push_back(product);
	}

	void add(Store* store) {
		stores->push_back(store);
	}

	void add(Client* client) {
		clients->push_back(client);
	}

	void createProductsParts() {
		ProductsPart* productsPart1 = new ProductsPart(clients->at(0));
		productsPart1->add(products->at(0));
		productsPart1->add(products->at(1));

		ProductsPart* productsPart2 = new ProductsPart(clients->at(1));
		productsPart2->add(products->at(2));

		ProductsPart* productsPart3 = new ProductsPart(clients->at(1));
		productsPart3->add(products->at(3));

		productsParts->push_back(productsPart1);
		productsParts->push_back(productsPart2);
		productsParts->push_back(productsPart3);
	}

	void assignTrucks() {
		trucks->at(0)->setClient(clients->at(0));
		trucks->at(0)->setProductsPart(productsParts->at(0));

		trucks->at(1)->setClient(clients->at(1));
		trucks->at(1)->setProductsPart(productsParts->at(1));

		trucks->at(2)->setClient(clients->at(1));
		trucks->at(2)->setProductsPart(productsParts->at(2));
	}

	~Trade() {
		for_each(trucks->begin(), trucks->end(), [&](Truck* const& p) {
			delete p;
		});
		for_each(suppliers->begin(), suppliers->end(), [&](Supplier* const& p) {
			delete p;
		});
		for_each(products->begin(), products->end(), [&](Product* const& p) {
			delete p;
		});
		for_each(productsParts->begin(), productsParts->end(), [&](ProductsPart* const& p) {
			delete p;
		});
		for_each(stores->begin(), stores->end(), [&](Store* const& p) {
			delete p;
		});
		for_each(clients->begin(), clients->end(), [&](Client* const& p) {
			delete p;
		});

		delete trucks;
		delete suppliers;
		delete products;
		delete productsParts;
		delete stores;
		delete clients;
	}
};

void createTrucks(Trade* trade) {
	Truck* truck = new Truck(8);
	trade->add(truck);
	wcout << L"Добавлен грузовик вместимостью 8\n";

	Truck* truck2 = new Truck(10);
	trade->add(truck2);
	wcout << L"Добавлен грузовик вместимостью 10\n";

	Truck* truck3 = new Truck(15);
	trade->add(truck3);
	wcout << L"Добавлен грузовик вместимостью 15\n";

	Truck* truck4 = new Truck(15);
	trade->add(truck4);
	wcout << L"Добавлен грузовик вместимостью 15\n";
}

void createSuppliers(Trade* trade) {
	Supplier* supplier = new Supplier("поставщик 1", "адрес 1");
	trade->add(supplier);
	wcout << L"Добавлен поставщик 1\n";

	Supplier* supplier2 = new Supplier("поставщик 2", "адрес 2");
	trade->add(supplier2);
	wcout << L"Добавлен поставщик 2\n";
}

void createStores(Trade* trade) {
	Warehouse* warehouse = new Warehouse("Оптовый клиент 1", "адрес 1");
	trade->add(warehouse);
	wcout << L"Добавлен Оптовый клиент 1\n";

	Shop* shop = new Shop("Розничный клиент 2", "адрес 2");
	trade->add(shop);
	wcout << L"Добавлен розничный клиент 2\n";
}

void createProducts(Trade* trade) {
	Food* food = new Food(trade->getSuppliers()->at(0), "Еда", 5, 5);
	trade->add(food);
	wcout << L"Добавлен товар еда для поставщика 1\n";

	Drink* drink = new Drink(trade->getSuppliers()->at(0), "Напиток", 7, 5);
	trade->add(drink);
	wcout << L"Добавлен товар напиток для поставщика 1\n";

	Furniture* furniture = new Furniture(trade->getSuppliers()->at(1), "Мебель", 10, 50);
	trade->add(furniture);
	wcout << L"Добавлен товар мебель для поставщика 2\n";

	Electronic* electronic = new Electronic(trade->getSuppliers()->at(1), "Электроника", 10, 100);
	trade->add(electronic);
	wcout << L"Добавлен товар электроника для поставщика 2\n";
}

void createClients(Trade* trade) {
	StoreClient* client = new StoreClient("Добавлен склад 1", "адрес 1");
	trade->add(client);
	wcout << L"Добавлен склад 1\n";

	ShopClient* client2 = new ShopClient("Добавлен розничный 2", "адрес 2");
	trade->add(client2);
	wcout << L"Добавлен розничный 2\n";
}

void createPP(Trade* trade) {
	trade->createProductsParts();
	wcout << L"Добавлена партия товара для клиента розничного магазина: еда, напиток, стоимость = " + to_wstring(trade->getProductsParts()->at(0)->getSumPrice()) + L"\n";
	wcout << L"Добавлена партия товара для клиента оптового магазина: мебель, стоимость = " + to_wstring(trade->getProductsParts()->at(1)->getSumPrice()) + L"\n";
	wcout << L"Добавлена партия товара для клиента оптового магазина: электроника, стоимость = " + to_wstring(trade->getProductsParts()->at(2)->getSumPrice()) + L"\n";
}

void assign(Trade* trade) {
	trade->assignTrucks();
	wcout << L"Отгрузка грузовика 1 для клиента розничного магазина: еда, напиток\n";
	wcout << L"Отгрузка грузовика 2 для клиента оптового магазина: мебель\n";
	wcout << L"Отгрузка грузовика 3 для клиента оптового магазина: электроника\n";
}

int wmain(int argc, wchar_t* argv[])
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stderr), _O_U16TEXT);

	Trade* trade = new Trade();

	createTrucks(trade);
	createSuppliers(trade);
	createStores(trade);
	createProducts(trade);
	createClients(trade);

	com_label:
	wcout << L"\n******************\nОтгрузка - 1\n" << L"Инициализировать заново - 2\n";
	int com;
	wcin >> com;
	if (com == 1) {
		createPP(trade);
		assign(trade);
		goto com_label;
	}
	else {
		delete trade;
		trade = new Trade();

		createTrucks(trade);
		createSuppliers(trade);
		createStores(trade);
		createProducts(trade);
		createClients(trade);
		goto com_label;
	}
}