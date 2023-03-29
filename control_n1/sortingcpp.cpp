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
		cout << "-----..........-----..........-----..........-----" << endl;
		cout << "Введите наименование, чтобы получить список товаров с ним" << endl;
		cout << "Ввод: ";
	}
	if (way == byPrice) {
		cout << "-----..........-----..........-----..........-----" << endl;
		cout << "Введите цену, чтобы получить список товаров, цена которых не превышает указанной" << endl;
	}
	if (way == byShelfLife) {
		cout << "-----..........-----..........-----..........-----" << endl;
		cout << "Введите срок хранения товара, чтобы получить спискок товаров, срок хранения которых больше заданного" << endl;
	}
}


int sorting::sortByName(Product** products, Product** sortList, int size, string nameSearch, bool isTest) {
	int i = 0;
	int iter = 0;
	*sortList = new Product[size];
	if(!isTest){
		printInputInfo(byName);
		cin >> nameSearch;
	}
	for (; i < size; i++) {
		if ((*products)[i].getName() == nameSearch) {
			(*sortList)[iter] = (*products)[i];
			iter++;
		}
	}
	return iter;
}

int sorting::sortByNamePrice(Product** products, Product** sortList, int size, string nameSearch, double priceSearch, bool isTest) {
	ui mUI;
	int i = 0;
	int iter = 0;
	*sortList = new Product[size];
	if(!isTest){
		printInputInfo(byName);
		cin >> nameSearch;
		printInputInfo(byPrice);
		priceSearch = mUI.getDoubleField();
	}
	for (; i < size; i++) {
		if ((*products)[i].getName() == nameSearch && (*products)[i].getPrice() <= priceSearch) {
			(*sortList)[iter] = (*products)[i];
			iter++;
		}
	}
	return iter;
}

int sorting::sortByShelfLife(Product** products, Product** sortList, int size, int sh, bool isTest) {
	ui mUI;
	*sortList = new Product[size];
	int i = 0;
	int iter = 0;
	if(!isTest){
		printInputInfo(byShelfLife);
		sh = mUI.getIntField();
	}
	for ( ; i < size; i++) {
		if ((*products)[i].getShelfLife() > sh) {
			(*sortList)[iter] = (*products)[i];
			iter++;
		}
	}
	return iter;
}
