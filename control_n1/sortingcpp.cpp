#include <iostream>
#include "ui.h"
#include "product.h"
#include "sorting.h"
#include <string>
#include <cstring>


using namespace std;
using namespace UI;
using namespace cproduct;
using namespace sorted;


static string byName = "inputName";
static string byPrice = "inputPrice";
static string byShelfLife = "inputSL";

void printInputInfo(string way) {
	if (way == byName) {
		cout << "������� ������������, ����� �������� ������ ������� � ���" << endl;
	}
	if (way == byPrice) {
		cout << "������� ����, ����� �������� ������ �������, ���� ������� �� ��������� ���������" << endl;
	}
	if (way == byShelfLife) {
		cout << "������� ���� �������� ������, ����� �������� ������� �������, ���� �������� ������� ������ ���������" << endl;
	}
	cout << "����: ";
}

void printProduct(Product** products, int i) {
	cout << "������������ ������: " << (*products)[i].getName() << endl;
	cout << "�������������: " << (*products)[i].getManufacturer() << endl;
	cout << "���� ������: " << (*products)[i].getPrice() << endl;
	cout << "���� ��������: " << (*products)[i].getShelfLife() << endl;
	cout << "���������� ������: " << (*products)[i].getQuantity() << endl;
	cout << "--------------------" << endl;
}

void sorting::sortByName(Product** products, int size) {
	string nameSearch = "";
	printInputInfo(byName);
	cin >> nameSearch;
	for (int i = 0; i < size; i++) {
		if ((*products)[i].getName() == nameSearch) {
			printProduct(products, i);
		}
	}
}

void sorting::sortByNamePrice(Product** products, int size) {
	ui mUI;
	string nameSearch = "";
	double priceSearch = 0;
	printInputInfo(byName);
	cin >> nameSearch;
	printInputInfo(byPrice);
	priceSearch = mUI.getDouble();
	for (int i = 0; i < size; i++) {
		if ((*products)[i].getName() == nameSearch && (*products)[i].getPrice() <= priceSearch) {
			printProduct(products, i);
		}
	}
}

void sorting::sortByShelfLife(Product** products, int size) {
	ui mUI;
	int sl = 0;
	printInputInfo(byShelfLife);
	sl = mUI.getInt();
	for (int i = 0; i < size; i++) {
		if ((*products)[i].getShelfLife() > sl) {
			printProduct(products, i);
		}
	}
}
