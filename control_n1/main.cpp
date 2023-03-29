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
    cout << "����� ���������� � ���������� ���������� ����������� ������ �1" << endl;
    cout << "������������ ������ ��������: ������� ����� ���������, 424 ������, 21 �������" << endl << endl;
    cout << "��� ����� ���� ������� ?" << endl;
    cout << "����������� ������ � 1. ������������.������ � �������� �� ���������� � �++" << endl 
         << "������ ����������� ������ ������������� ��� ������������ ������������� ����� � �������� ���������� ������� � �������������� �����"<<endl
         <<"���������������� �++.���������� ����������� ����� ��� ��������� ���������� �������.������ � ������ ����������� � ������� ������� Set, Get,Show."<<endl
         <<"��� ���������� ����������� ������ ������ ������������ ���������� � ��������� ���������� STL ��� ����������� ��������� ���������." << endl;
    cout << "�����: ������������, �������������, ����, ���� ��������, ����������."<<endl
         << "������� ������ ��������.����������� ����������� ��������� :" <<endl
         <<"� ������ ������� ��� ��������� ������������,"<<endl
         <<"� ������ ������� ��� ��������� ������������, ���� ������� �� ��������� ���������,"<<endl
         <<"� ������ �������, ���� �������� ������� ������ ���������." << endl;
}

void printInputWays() {

    cout << "-----..........-----..........-----..........-----" << endl;
    cout << "���������� ��������, ��� �� �� ������ ��������� ������ ��� �� ������ ��������� ��������� ����� ?" << endl;
    cout << "����������� ������ ���� ��� ��������� � ���������, ������� :" << endl;
    cout << "[1] - ���� ������ ����� ������ �� �����" << endl;
    cout << "[2] - ���� ������ ������ ������ � �������" << endl;
    cout << "[3] - ���� ������ ��������� ��������� �����" << endl;
    cout << "[0] - ���� ������ �����! �� ��������!" << endl << endl;
}

void printAction() {
    cout << "-----..........-----..........-----..........-----" << endl;
    cout << "���������� ��������, ��� �� ������ ������� � ������� ?" << endl;
    cout << "����������� ������ ���� ��� ��������� � ���������, ������� :" << endl;
    cout << "[1] - ���� ������ ������ ������������ � �������� ������ ������� �� ����" << endl;
    cout << "[2] - ���� ������ �������� ������ ������� ��� ��������� ������������, ���� ������� �� ��������� ���������" << endl;
    cout << "[3] - ���� ������ �������� ������ �������, ���� �������� ������� ������ ���������" << endl;
    cout << "[4] - ���� ������ ��������� � ������ ������ ������" << endl;
}

void printOutputWays() {
    cout << "-----..........-----..........-----..........-----" << endl;
    cout << "���������� ��������, ��� �� ������ �������� ������ ?" << endl;
    cout << "����������� ������ ���� ��� ��������� � ���������, ������� :" << endl;
    cout << "[1] - ���� ������ ������� ������ � ����" << endl;
    cout << "[2] - ���� ������ ������� ������ � �������" << endl;
    cout << "[3] - ���� ������ ��������� � �������� ����� ������ ��� ��������� ������ �����" << endl;
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
        cout << "�� ����� !" << endl;
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
        cout << "�� ����� !" << endl;
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
        cout<<"�� ����� !"<<endl;
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
