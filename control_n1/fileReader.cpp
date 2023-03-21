#include <iostream>
#include <filesystem>
#include "fileReader.h"
#include "ui.h"
#include "product.h"
#include <string>
#include <fstream>
#include <cstring>


using namespace std;
using namespace reader;
using namespace UI;
using namespace cproduct;

static const string mInput = "input";
static const string mOutput = "output";

void printInform(string way) {
	if (way == mInput) {
		cout << "-----..........-----..........-----..........-----" << endl;
		cout << "�������� ��������! ��� ������ �� ����� ������ ������ ���� �������� �� ����� ������ ����� ; � ��� �������� !" << endl;
		cout << "���� ������ �������� �����, ��������� ������ �� ������, ��������� ���������� � �������� ��������� �������� ����" << endl;
		cout << "-----..........-----..........-----..........-----" << endl;
		cout << "��������� ��: ";
	}
	if (way == mOutput) {
		cout << "������� �������� ����� � ������� �� ������ ��������� ���������" << endl;
	}
}

// ��������� ������ �� ���������, ��������� ������ ';' � �������� �����������
void fileReader::filling(Product** products, const char* str_ptr, int i) {
	int iter = 0;
	char* str_copy = new char[strlen(str_ptr) + 1];
	strcpy_s(str_copy, strlen(str_ptr) + 1, str_ptr);
	char* context = nullptr;
	char* token = strtok_s(str_copy, ";", &context);
	while (token != nullptr) {
		switch (iter) {
		case 0:
			(*products)[i].setName(token);
			break;
		case 1:
			(*products)[i].setManufacturer(token);
			break;
		case 2:
			if (strtod(token, nullptr) <= 0) {
				cout << "������������� ��� ������� ���� ������! ��������� ������ � �����! � " << i + 1 << " ������" << endl;
			}
			(*products)[i].setPrice(strtod(token, nullptr));
			break;
		case 3:
			if (atoi(token) <= 0) {
				cout << "������������� ��� ������� ���� �������� ������! ��������� ������ � �����! � " << i + 1 << " ������"<<endl;
			}
			(*products)[i].setShelfLife(atoi(token));
			break;
		case 4:
			if (atoi(token) <= 0) {
				cout << "������������� ��� ������� ���������� ������! ��������� ������ � �����! � " << i + 1 << " ������"<<endl;
			}
			(*products)[i].setQuantity(atoi(token));
			break;
		default:
			cout << "������� ����� ������ � ����� ������! ������ ����� ���������������" << endl;
		}
		token = strtok_s(nullptr, ";", &context);
		iter++;
	}
	delete[] str_copy;
}


void fileReader::implFile(Product** products, int* size, string name) {
	int i = 0;
	string data{};
	ifstream input;
	input.open(name);
	if (input.is_open()) {
		while (getline(input, data)) {
			*size += 1;
		}
		input.close();
	}else{
		cout << endl << "����� � ����� ������ �� ����������!" << endl << endl;
		throw runtime_error("error");
	}

	input.open(name);
	if (input.is_open()) {
		*products = new Product[*size];
		while (getline(input, data)) {
			if (data.empty()) {
				cout << "���� ������ �� " << i+1 << " ������ �� ��� ����������! ��������� ���� � ������� ������ ������" << endl;
				*size -= 1;
			}
			else {
				filling(products, data.c_str(), i);
			}
			i++;
		}
		input.close();
	}
	else {
		cout << endl << "������ ������ ����� ��� ��������� ������!" << endl << endl;
		throw runtime_error("An error occurred");
	}
}

void fileReader::removeNegative(Product** products, int* size) {
	int newSize = 0;
	for (int i = 0; i < *size; i++) {
		if (!(*products)[i].isNegavive()) {
			(*products)[newSize++] = (*products)[i];
		}
	}
	// �������� ������ ��������
	for (int i = newSize; i < *size; i++) {
		(*products)[i] = Product();
	}
	*size = newSize;

}

int fileReader::readFile(Product** products, string name) {
	int size = 0;
	printInform(mInput);
	cin >> name;
	implFile(products, &size, name);
	removeNegative(products, &size);
	return size;
}


void fileReader::fillFile(Product** products, int size) {
	printInform(mOutput);
	string filePath = "";
	bool isDataSaved = false;
	ui mUI;
	do {
		cout << "��������� �:";
		getline(cin, filePath);

		if (ifstream(filePath)) {
			cout << "���� ��� ����������." << endl;
			cout << "[0] - ������������ ������������ ����." << endl;
			cout << "[1] - ��������� ����." << endl;
			int tryAnotherFile = mUI.getMenuVar(0, 1);
			if (tryAnotherFile) {
				continue;
			}
		}

		ofstream myFile(filePath, ofstream::app);

		error_code ec{};

		if (!myFile) {
			cout << "������ ���������. ��������� ����." << endl;
			myFile.close();
			continue;
		}

		myFile.close();
		myFile.open(filePath, ofstream::trunc);
		myFile << "������������\t�������������\t����\t\t���� �������� (� ����)\t����������\n";
		for (int i = 0; i < size; i++) {
			myFile << (*products)[i].getName() << "\t\t|\t" << (*products)[i].getManufacturer() << "\t\t|\t" << (*products)[i].getPrice()
				<< "\t\t|\t" << (*products)[i].getShelfLife() << "\t\t|\t" << (*products)[i].getQuantity() << endl;
		}
		myFile.close();
		cout << "������ ���������." << endl;
		isDataSaved = true;
	} while (!isDataSaved);
}
