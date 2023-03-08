#include "ui.h"
#include "Product.h"
#include <iostream>

using namespace UI;
using namespace std;
using namespace cproduct;

template<typename T>
T getInput() {
	T userInput = 0;
	cout << "Ввод: ";
	cin >> userInput;
	if (cin.fail()) {
		cout << "Некоректный ввод. Попробуйте еще раз" << endl;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Ввод: ";
			cin >> userInput;
		}
	}
	cin.ignore(INT_MAX, '\n');
	return userInput;
}


int ui::getMenuVar(int lower, int upper) {
	bool inputCorrect = false;
	int in = 0;
	while (!inputCorrect) {
		in = getInt();
		if (in >= lower && in <= upper) {
			inputCorrect = true;
		}
		else {
			cout << "Нет такого пункта меню!" << endl;
		}
	}
	return in;
}

int ui::getSize() {
	bool inputCorrect = false;
	int in = 0;
	while (!inputCorrect) {
		in = getInt();
		if (in >= 1) {
			inputCorrect = true;
		}
		else {
			cout << "Введен отрицательный размер! Попробуйте еще раз" << endl;
		}
	}
	return in;
}

int ui::getInt() {
	return getInput<int>();
}


double ui::getDouble() {
	return getInput<double>();
}

void filling(Product** products, int i) {
	ui mUI;
	string name;
	string manufacturer;
	double price = 0;
	int shelfLife = 0;
	int quantity = 0;
	cout << "Введите название продукта" << endl;
	cout << "Ввод:";
	cin >> name;
	(*products)[i].setName(name);
	cout << "Введите производителя продукта" << endl;
	cout << "Ввод: ";
	cin >> manufacturer;
	(*products)[i].setManufacturer(manufacturer);
	cout << "Введите цену продукта" << endl;
	price = mUI.getDouble();
	(*products)[i].setPrice(price);
	cout << "Введите срок годности продукта" << endl;
	shelfLife = mUI.getInt();
	(*products)[i].setShelfLife(shelfLife);
	cout << "Введите количество продуктов" << endl;
	quantity = mUI.getInt();
}


int ui::readConsole(Product** products, bool* dataExist) {
	ui mUI;
	int size = 0;
	cout << "Введите количество продуктов" << endl;
	cout << "Ввод: ";
	size = mUI.getSize();
	*products = new Product[size];
	for (int i = 0; i < size; i++) {
		cout << "------------" << endl;
		cout << "Вы вводите товар №" << i << endl;
		filling(products, i);
		cout << endl << "------------" << endl;
	}
	*dataExist = true;
	return size;
}