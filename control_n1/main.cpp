#include <iostream>
#include "fileReader.h"
#include "Product.h"
#include "ui.h"
#include "sorting.h"

using namespace UI;
using namespace reader;
using namespace sorted;

enum { exitp = 0, rfile = 1, rconsole = 2, unitTest = 3 };
enum { task1 = 1, task2 = 2, task3 = 3, returnp = 4};

void printInputWays() {
    cout << "ѕожалуйста выберете, как вы бы хотели заполнить данные или вы хотите запустить модульные тесты ?" << endl;
    cout << "»спользуйте пункты меню дл€ навигации в программе, нажмите :" << endl;
    cout << "1 - если хотите вз€ть данные из файла" << endl;
    cout << "2 - если хотите ввести данные в консоли" << endl;
    cout << "3 - если хотите запустить модульные тесты" << endl;
    cout << "0 - если хотите выйти! досвидани€!" << endl << endl;
}

void printAction() {
    cout << "ѕожалуйста выберете, что вы хотите сделать с данными ?" << endl;
    cout << "»спользуйте пункты меню дл€ навигации в программе, нажмите :" << endl;
    cout << "1 - если хотите ввести наименование и получить список товаров по нему" << endl;
    cout << "2 - если хотите получить список товаров дл€ заданного наименовани€, цена которых не превышает указанной" << endl;
    cout << "3 - если хотите получить список товаров, срок хранени€ которых больше заданного" << endl;
    cout << "4 - если хотите вернутьс€ и ввести данные заново" << endl;
}


void selectImplTask(int variant, Product** products, int* size) {
    sorting sort;
    switch (variant)
    {
    case task1:
        sort.sortByName(products, *size);
        break;
    case task2:
        sort.sortByNamePrice(products, *size);
        break;
    case task3:
        sort.sortByShelfLife(products, *size);
        break;
    case returnp:
        cout << "¬ы вышли !" << endl;
        break;
    }
}

void selectInput(int variant, Product** products, bool* dataExist, int* size) {
    ui mUI;
    fileReader mReader;
    switch (variant)
    {
    case rfile:
        *size = mReader.readFile(products, dataExist);
        break;
    case rconsole:
        *size = mUI.readConsole(products, dataExist);
        break;
    case exitp:
        puts("¬ы вышли из программы !");
        break;
    }
}

void launchMenu() {
    ui mUI;
    int variant = 0;
    int boardMenu = unitTest;
    int sizeArr = 0;
    bool dataExists = false;
    Product* products = nullptr;
    do
    {
        dataExists = false;
        printInputWays();
        variant = mUI.getMenuVar(exitp, unitTest);
        selectInput(variant, &products, &dataExists, &sizeArr);
        boardMenu = returnp;
        if (variant == 0) break;
        if (dataExists) {
            do {
                printAction();
                variant = mUI.getMenuVar(task1, boardMenu);
                selectImplTask(variant, &products, &sizeArr);
            } while (variant != returnp);
        }
        delete[]products;
        products = nullptr;

    } while (variant != exitp);
}


int main() {
	setlocale(LC_CTYPE, "Russian");
	launchMenu();
	system("pause");
}
