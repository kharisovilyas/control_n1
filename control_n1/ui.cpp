#include "ui.h"
#include "Product.h"
#include <iostream>
#include "fileReader.h"

using namespace UI;
using namespace std;
using namespace cproduct;
using namespace reader;

template<typename T>
T getInput() {
	T userInput = 0;
	cout << "����: ";
	cin >> userInput;
	if (cin.fail()) {
		cout << "����������� ����. ���������� ��� ���" << endl;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "����: ";
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
			cout << "��� ������ ������ ����!" << endl;
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
			cout << "������ ��������������� ������! ���������� ��� ���" << endl;
		}
	}
	return in;
}

int getIntField() {
	ui ui;
	bool inputCorrect = false;
	int in = 0;
	while (!inputCorrect) {
		in = ui.getInt();
		if (in >= 1) {
			inputCorrect = true;
		}
		else {
			cout << "������ ��������������� �����! ���������� ��� ���" << endl;
		}
	}
	return in;
}

int getDoubleField() {
	ui ui;
	bool inputCorrect = false;
	double in = 0;
	while (!inputCorrect) {
		in = ui.getDouble();
		if (in >= 1) {
			inputCorrect = true;
		}
		else {
			cout << "������ ��������������� �����! ���������� ��� ���" << endl;
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
	cout << "-----..........-----..........-----..........-----" << endl;
	cout << "������� �������� ������" << endl;
	cout << "����: ";
	cin >> name;
	(*products)[i].setName(name);
	cout << "������� ������������� ������" << endl;
	cout << "����: ";
	cin >> manufacturer;
	(*products)[i].setManufacturer(manufacturer);
	cout << "������� ���� ������" << endl;
	price = getDoubleField();
	(*products)[i].setPrice(price);
	cout << "������� ���� �������� ������" << endl;
	shelfLife = getIntField();
	(*products)[i].setShelfLife(shelfLife);
	cout << "������� ���������� ������� ��������� ��������" << endl;
	quantity = getIntField();
	(*products)[i].setQuantity(quantity);
}

bool getBool() {
	return getInput<bool>();
}

void printInformOut() {
	cout << "��� ������������ ������ �������� ������ � ����" << endl;
	cout << "����������� ������ ���� ��� ��������� � ���������, ������� :" << endl;
	cout << "[1] - ��������" << endl;
	cout << "[0] - �� ���������� � ���������� ���������� ���������" << endl;
}

void outInitialDataInFile(Product** products, int size) {
	printInformOut();
	bool variant = getBool();
	if (variant == 0) return;
	fileReader fr;
	fr.fillFile(products, size);
}

int ui::readConsole(Product** products) {
	ui mUI;
	int size = 0;
	cout << "-----..........-----..........-----..........-----" << endl;
	cout << "������� ���������� �������" << endl;
	size = mUI.getSize();
	cout << "-----..........-----..........-----..........-----" << endl;
	*products = new Product[size];
	for (int i = 0; i < size; i++) {
		cout << "�� ������� ����� �" << i+1 << endl;
		filling(products, i);
		cout << "-----..........-----..........-----..........-----" << endl;
	}
	cout << "���� ��� ������� ��������! " << endl;
	outInitialDataInFile(products, size);
	return size;
}

void printProduct(Product** products, int i) {
	cout << "-----..........-----..........-----..........-----" << endl;
	cout << "������������ ������: " << (*products)[i].getName() << endl;
	cout << "�������������: " << (*products)[i].getManufacturer() << endl;
	cout << "���� ������: " << (*products)[i].getPrice() << endl;
	cout << "���� ��������: " << (*products)[i].getShelfLife() << endl;
	cout << "���������� ������: " << (*products)[i].getQuantity() << endl;
}

void ui::outConsole(Product** products, int size) {
	if (size != 0 ) {
		cout << "��������� ������:" << endl;
		for (int i = 0; i < size; i++) {
			printProduct(products, i);
		}
	}
	else {
		cout << "���������� ������ ������ �����" << endl <<endl;
		throw runtime_error("error");
	}
}