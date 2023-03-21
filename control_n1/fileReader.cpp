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
		cout << "Обратите внимание! Что данные об одном товаре должны быть записаны на одной строке через ; и без пробелов !" << endl;
		cout << "Если данные записаны иначе, программа укажет на ошибку, прекратит выполнение и попросит исправить исходный файл" << endl;
		cout << "-----..........-----..........-----..........-----" << endl;
		cout << "Загрузить из: ";
	}
	if (way == mOutput) {
		cout << "Введите название файла в который вы хотите сохранить результат" << endl;
	}
}

// Разбиваем строку на подстроки, используя символ ';' в качестве разделителя
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
				cout << "Отрицательная или нулевая цена товара! Исправьте данные в файле! В " << i + 1 << " строке" << endl;
			}
			(*products)[i].setPrice(strtod(token, nullptr));
			break;
		case 3:
			if (atoi(token) <= 0) {
				cout << "Отрицательный или нулевой срок годности товара! Исправьте данные в файле! В " << i + 1 << " строке"<<endl;
			}
			(*products)[i].setShelfLife(atoi(token));
			break;
		case 4:
			if (atoi(token) <= 0) {
				cout << "Отрицательное или нулевое количество товара! Исправьте данные в файле! В " << i + 1 << " строке"<<endl;
			}
			(*products)[i].setQuantity(atoi(token));
			break;
		default:
			cout << "Слишком много данных в одной строке! Данные будут проигнорированы" << endl;
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
		cout << endl << "Файла с таким именем не существует!" << endl << endl;
		throw runtime_error("error");
	}

	input.open(name);
	if (input.is_open()) {
		*products = new Product[*size];
		while (getline(input, data)) {
			if (data.empty()) {
				cout << "Ввод товара на " << i+1 << " строке не был произведен! Исправьте файл и введите данные заново" << endl;
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
		cout << endl << "Ошибка чтения файла или выделения памяти!" << endl << endl;
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
	// обнуляем плохие элементы
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
		cout << "Сохранить в:";
		getline(cin, filePath);

		if (ifstream(filePath)) {
			cout << "Файл уже существует." << endl;
			cout << "[0] - Перезаписать существующий файл." << endl;
			cout << "[1] - Повторить ввод." << endl;
			int tryAnotherFile = mUI.getMenuVar(0, 1);
			if (tryAnotherFile) {
				continue;
			}
		}

		ofstream myFile(filePath, ofstream::app);

		error_code ec{};

		if (!myFile) {
			cout << "Запись запрещена. Повторите ввод." << endl;
			myFile.close();
			continue;
		}

		myFile.close();
		myFile.open(filePath, ofstream::trunc);
		myFile << "Наименование\tПроизводитель\tЦена\t\tСрок годности (в днях)\tКоличество\n";
		for (int i = 0; i < size; i++) {
			myFile << (*products)[i].getName() << "\t\t|\t" << (*products)[i].getManufacturer() << "\t\t|\t" << (*products)[i].getPrice()
				<< "\t\t|\t" << (*products)[i].getShelfLife() << "\t\t|\t" << (*products)[i].getQuantity() << endl;
		}
		myFile.close();
		cout << "Запись завершена." << endl;
		isDataSaved = true;
	} while (!isDataSaved);
}
