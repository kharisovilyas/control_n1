#include <iostream>
#include "fileReader.h"
#include "Product.h"
#include "ui.h"
#include "sorting.h"
#include "test.h"

using namespace UI;
using namespace reader;
using namespace sorted;
using namespace testUnit;

enum { task1 = 1, task2 = 2, task3 = 3, returnp = 4 };
enum { exitp = 0, rfile = 1, rconsole = 2, unitTest = 3 };
enum { fileOutput = 1, coutput = 2, outreturn = 3};

void printInputWays() {

    cout << "-----..........-----..........-----..........-----" << endl;
    cout << "ѕожалуйста выберете, как вы бы хотели заполнить данные или вы хотите запустить модульные тесты ?" << endl;
    cout << "»спользуйте пункты меню дл€ навигации в программе, нажмите :" << endl;
    cout << "[1] - если хотите вз€ть данные из файла" << endl;
    cout << "[2] - если хотите ввести данные в консоли" << endl;
    cout << "[3] - если хотите запустить модульные тесты" << endl;
    cout << "[0] - если хотите выйти! досвидани€!" << endl << endl;
}

void printAction() {
    cout << "-----..........-----..........-----..........-----" << endl;
    cout << "ѕожалуйста выберете, что вы хотите сделать с данными ?" << endl;
    cout << "»спользуйте пункты меню дл€ навигации в программе, нажмите :" << endl;
    cout << "[1] - если хотите ввести наименование и получить список товаров по нему" << endl;
    cout << "[2] - если хотите получить список товаров дл€ заданного наименовани€, цена которых не превышает указанной" << endl;
    cout << "[3] - если хотите получить список товаров, срок хранени€ которых больше заданного" << endl;
    cout << "[4] - если хотите вернутьс€ и ввести данные заново" << endl;
}

void printOutputWays() {
    cout << "-----..........-----..........-----..........-----" << endl;
    cout << "ѕожалуйста выберете, как вы хотите получить список ?" << endl;
    cout << "»спользуйте пункты меню дл€ навигации в программе, нажмите :" << endl;
    cout << "[1] - если хотите вывести данные в файл" << endl;
    cout << "[2] - если хотите вывести данные в консоль" << endl;
    cout << "[3] - если хотите вернутьс€ и получить новый список или заполнить данные снова" << endl;
}

void selectImplTask(int variant, Product** products, Product** sortList, int* size, int* sizeSort) {
    sorting sort;
    switch (variant)
    {
    case task1:
        *sizeSort = sort.sortByName(products, sortList, *size, {}, false);
        break;
    case task2:
        *sizeSort = sort.sortByNamePrice(products, sortList, *size, {}, 0, false);
        break;
    case task3:
        *sizeSort = sort.sortByShelfLife(products, sortList, *size, 0, false);
        break;
    case returnp:
        cout << "¬ы вышли !" << endl;
        break;
    }
}

void selectInput(int variant, Product** products, int* size) {
    ui mUI;
    fileReader mReader;
    test mTest;
    switch (variant)
    {
    case rfile:
        *size = mReader.readFile(products, {});
        break;
    case rconsole:
        *size = mUI.readConsole(products);
        break;
    case unitTest: 
        mTest.startTest();
    case exitp:
        cout<<"¬ы вышли !"<<endl;
        break;
    }
}

void selectOutput(int variant, Product** sortList, int size) {
    ui mUI;
    fileReader mReader;
    test mTest;
    switch (variant)
    {
    case fileOutput:
        mReader.fillFile(sortList, size);
        break;
    case coutput:
        mUI.outConsole(sortList, size);
        break;

    case outreturn:
        cout<<"¬ы вышли !"<<endl;
        break;
    }
}

void launchMenu() {
    ui mUI;
    int variant = 0;
    int boardMenu = unitTest;
    int sizeSort = 0;
    int size = 0;
    Product* products = nullptr;
    Product* sortList = nullptr;
    do
    {
        printInputWays();
        variant = mUI.getMenuVar(exitp, unitTest);
        try {
            selectInput(variant, &products, &size);
        }
        catch (const exception& e) {
            continue;
        }
        if (variant == exitp) break;
        if (variant == unitTest) continue;
        do {
            printAction();
            boardMenu = returnp;
            variant = mUI.getMenuVar(task1, boardMenu);
            try {
                selectImplTask(variant, &products, &sortList, &size, &sizeSort);
            }
            catch (const exception& e) {
                continue;
            }
            if (variant == returnp) break;
            do {
                printOutputWays();
                boardMenu = returnp;
                variant = mUI.getMenuVar(fileOutput, boardMenu);
                if (variant == outreturn) break;
                try {
                    selectOutput(variant, &sortList, sizeSort);
                }
                catch (const exception& e) {
                    continue;
                }
            } while (variant != returnp);
        } while (variant != returnp);
        delete[]products;
        products = nullptr;
    } while (variant != exitp);
}


int main() {
	setlocale(LC_CTYPE, "Russian");
	launchMenu();
	system("pause");
}
