#include "loopedMenu.h"
#include "funcForValue.h"
#include <iostream>

using namespace std;
using namespace menu;
using namespace func;

funcForValue func;

void loopedMenu::printInputWays() {
    cout << "���������� ��������, ��� �� �� ������ ��������� ������ ?" << endl;
    cout << "����������� ������ ���� ��� ��������� � ���������, ������� :" << endl;
    cout << "1 - ���� ������ ����� ������ �� �����" << endl;
    cout << "2 - ���� ������ ������ ������ � �������" << endl;
    cout << "3 - ���� ������ ���������" << endl;
}

void loopedMenu::launchMenu() {

    printInputWays();
    int variant = 0;
    do
    {
        variant = func.getInteger();

        if (variant > exitp) {
            puts("������ �����. ���������� ��� ���!");
        }
        switch (variant)
        {
        case task1:
            informMenu();
            break;
        case task2:
            informMenu(task2);
            break;
        case task3:
            informMenu(task3);
            break;
        case exitProgramm:
            puts("�� ����� �� ��������� !");
            break;
        }

    } while (variant != exitProgramm);
}
