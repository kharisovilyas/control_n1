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

void outGretting() {
    cout << "Добро пожаловать в програмную реализацию Контрольной работы №1" << endl;
    cout << "Лабораторную работу выполнил: Харисов Ильяс Ренатович, 424 группа, 21 вариант" << endl << endl;
    cout << "Что нужно было сделать ?" << endl;
    cout << "Контрольная работа № 1. Инкапсуляция.Классы и средства их построения в С++" << endl 
         << "Первая контрольная работа предназначена для приобретения практического опыта в создании простейших классов с использованием языка"<<endl
         <<"программирования С++.Необходимо разработать класс для указанной предметной области.Доступ к данным реализовать с помощью методов Set, Get,Show."<<endl
         <<"При выполнении контрольной работы нельзя использовать контейнеры и алгоритмы библиотеки STL или аналогичных сторонних библиотек." << endl;
    cout << "Товар: наименование, производитель, цена, срок хранения, количество."<<endl
         << "Создать массив объектов.Реализовать возможность получения :" <<endl
         <<"– списка товаров для заданного наименования,"<<endl
         <<"– списка товаров для заданного наименования, цена которых не превышает указанной,"<<endl
         <<"– списка товаров, срок хранения которых больше заданного." << endl;
}

void printInputWays() {

    cout << "-----..........-----..........-----..........-----" << endl;
    cout << "Пожалуйста выберете, как вы бы хотели заполнить данные или вы хотите запустить модульные тесты ?" << endl;
    cout << "Используйте пункты меню для навигации в программе, нажмите :" << endl;
    cout << "[1] - если хотите взять данные из файла" << endl;
    cout << "[2] - если хотите ввести данные в консоли" << endl;
    cout << "[3] - если хотите запустить модульные тесты" << endl;
    cout << "[0] - если хотите выйти! до свидания!" << endl << endl;
}

void printAction() {
    cout << "-----..........-----..........-----..........-----" << endl;
    cout << "Пожалуйста выберете, что вы хотите сделать с данными ?" << endl;
    cout << "Используйте пункты меню для навигации в программе, нажмите :" << endl;
    cout << "[1] - если хотите ввести наименование и получить список товаров по нему" << endl;
    cout << "[2] - если хотите получить список товаров для заданного наименования, цена которых не превышает указанной" << endl;
    cout << "[3] - если хотите получить список товаров, срок хранения которых больше заданного" << endl;
    cout << "[4] - если хотите вернуться и ввести данные заново" << endl;
}

void printOutputWays() {
    cout << "-----..........-----..........-----..........-----" << endl;
    cout << "Пожалуйста выберете, как вы хотите получить список ?" << endl;
    cout << "Используйте пункты меню для навигации в программе, нажмите :" << endl;
    cout << "[1] - если хотите вывести данные в файл" << endl;
    cout << "[2] - если хотите вывести данные в консоль" << endl;
    cout << "[3] - если хотите вернуться и получить новый список или заполнить данные снова" << endl;
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
        cout << "Вы вышли !" << endl;
        break;
    }
}

void selectInput(int variant, Product** products, int* size) {
    ui mUI;
    fileReader mReader;
    test mTest;
    switch (variant)
    {
    case exitp:
        cout << "Вы вышли !" << endl;
        break;
    case rfile:
        *size = mReader.readFile(products, {});
        break;
    case rconsole:
        *size = mUI.readConsole(products);
        break;
    case unitTest: 
        mTest.startTest();
    }
}

void selectOutput(int variant, Product** sortList, int size) {
    ui mUI;
    fileReader mReader;
    switch (variant)
    {
    case fileOutput:
        mReader.fillFile(sortList, size);
        break;
    case coutput:
        mUI.outConsole(sortList, size);
        break;

    case outreturn:
        cout<<"Вы вышли !"<<endl;
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
            cout << e.what() << endl;
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
                cout << e.what() << endl;
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
                    cout << e.what() << endl;
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
    outGretting();
	launchMenu();
	system("pause");
}
