#include "ui.h"
#include "Product.h"
#include <iostream>

using namespace UI;
using namespace std;
using namespace cproduct;

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
			cout << "������ ������������� ������! ���������� ��� ���" << endl;
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
	cout << "������� �������� ��������" << endl;
	cout << "����:";
	cin >> name;
	(*products)[i].setName(name);
	cout << "������� ������������� ��������" << endl;
	cout << "����: ";
	cin >> manufacturer;
	(*products)[i].setManufacturer(manufacturer);
	cout << "������� ���� ��������" << endl;
	price = mUI.getDouble();
	(*products)[i].setPrice(price);
	cout << "������� ���� �������� ��������" << endl;
	shelfLife = mUI.getInt();
	(*products)[i].setShelfLife(shelfLife);
	cout << "������� ���������� ���������" << endl;
	quantity = mUI.getInt();
}


int ui::readConsole(Product** products, bool* dataExist) {
	ui mUI;
	int size = 0;
	cout << "������� ���������� ���������" << endl;
	cout << "����: ";
	size = mUI.getSize();
	*products = new Product[size];
	for (int i = 0; i < size; i++) {
		cout << "------------" << endl;
		cout << "�� ������� ����� �" << i << endl;
		filling(products, i);
		cout << endl << "------------" << endl;
	}
	*dataExist = true;
	return size;
}