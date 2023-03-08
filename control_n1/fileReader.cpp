#include <iostream>
#include "fileReader.h"
#include "ui.h"
#include "product.h"
#include <string>
#include <stdlib.h>
#include <fstream>
#include <cstring>


using namespace std;
using namespace reader;
using namespace UI;
using namespace cproduct;

static const string mInput = "input";

void printInform(string way) {
	int howInput = 0;
	if (way == mInput) {
		cout << "�������� ��������! ��� ������ �� ����� ������ ������ ���� �������� �� ����� ������ ����� ; � ��� �������� !" << endl << endl;
		cout << "�������� ��������! ��� ������ ������ ����������� ������ ��������� ���������� �������!" << endl << endl;
		cout << "���� ������ �������� �����, ��������� ������ �� ������, ��������� ���������� � �������� ��������� �������� ����" << endl << endl;
		cout << "������� �������� ����� ��� ���� � ����: ";
	}
}

// ��������� ������ �� ���������, ��������� ������ ';' � �������� �����������
void filling(Product** products, const char* str_ptr, size_t i) {
	int iter = 0;
	char* str_copy = new char[strlen(str_ptr) + 1];
	strcpy_s(str_copy, strlen(str_ptr) + 1, str_ptr);
	char* context = nullptr;
	char* token = strtok_s(str_copy, "; ", &context);
	while (token != nullptr) {
		switch (iter) {
		case 0:
			(*products)[i].setName(token);
			break;
		case 1:
			(*products)[i].setManufacturer(token);
			break;
		case 2:
			(*products)[i].setPrice(stod(token));
			break;
		case 3:
			(*products)[i].setShelfLife(atoi(token));
			break;
		case 4:
			(*products)[i].setQuantity(atoi(token));
			break;
		default:
			cout << "� �������� ������ ��� �� �� ���!" << endl;
		}
		token = strtok_s(nullptr, "; ", &context);
		iter++;
	}
	delete[] str_copy;
}


void implFile(Product** products, int* size, bool* dataExist) {
	string name = "";
	int i = 0;
	string data = "";
	cin >> name;
	ifstream input;
	input.open(name);
	if (input.is_open()) {
		while (getline(input, data)) {
			*size = atoi(data.c_str());
			break;
		}
		*dataExist = true;
	}else{
		*dataExist = false;
		cout << endl << "������ ������ ����� ��� ��������� ������!" << endl << endl;
	}
	if (*size <= 0){
		*dataExist = false;
		cout << endl << "� ����� ������� ������������� ����������" << endl << endl;
	}
	if (*dataExist) {
		*products = new Product[*size];
	}
	if (input.is_open() && *dataExist) {
		*dataExist = false;
		while (getline(input, data)) {
			*dataExist = true;
			filling(products, data.c_str(), i);
			i++;
		}
	}
	input.close();
}

int fileReader::readFile(Product** products, bool* dataExist) {
	int size = 0;
	printInform(mInput);
	implFile(products, &size, dataExist);
	return size;

}



void fileReader::fillFile(Product** products) {
	
}
