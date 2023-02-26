#include <iostream>
#include "loopedMenu.h"
#include "fileReader.h"
#include "Product.h"

using namespace menu;

int main() {
	loopedMenu menu;
	setlocale(LC_CTYPE, "Russian");
	menu.launchMenu();
	system("pause");
}
