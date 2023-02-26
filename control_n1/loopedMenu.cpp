#include "loopedMenu.h"
#include "funcForValue.h"
#include <iostream>

using namespace std;
using namespace menu;
using namespace func;

funcForValue func;

void loopedMenu::printInputWays() {
    cout << "Пожалуйста выберете, как вы бы хотели заполнить данные ?" << endl;
    cout << "Используйте пункты меню для навигации в программе, нажмите :" << endl;
    cout << "1 - если хотите взять данные из файла" << endl;
    cout << "2 - если хотите ввести данные в консоли" << endl;
    cout << "3 - если хотите вернуться" << endl;
}

void loopedMenu::launchMenu() {

    printInputWays();
    int variant = 0;
    do
    {
        variant = func.getInteger();

        if (variant > exitp) {
            puts("Ошибка ввода. Попробуйте ещё раз!");
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
            puts("Вы вышли из программы !");
            break;
        }

    } while (variant != exitProgramm);
}
