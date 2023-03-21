#include <iostream>
#include <cassert>
#include <fstream>
#include <sstream>
#include "test.h"
#include "fileReader.h"
#include "sorting.h"

using namespace testUnit;
using namespace sorted;
using namespace reader;
using namespace std;

const string testParsing = "parsing";
const string testFileRead = "read";


template<typename T, typename U>

void printInvalid(T received, U expected, string message) {
    cout << message;
    cout << "Ожидалось: " << expected << endl << "Было получено: " << received << endl;
}


void printCorrect(void (*function)(), string message) {
    stringstream buffer{};
    streambuf* old_cout_buf = cout.rdbuf(buffer.rdbuf());
    (*function)();
    cout.rdbuf(old_cout_buf);
    string output = buffer.str();
    if (output.empty()) {
        cout << endl << message << endl << endl;
    }
    else {
        cout << output;
    }
}

void checkingData(Product* products, int iter,
                    string name, string manufacturer, double price, int sh, int q) {
    string message = {};
    if (products[iter].getName() != name)
        printInvalid(products[0].getName(), name, message);
    if (products[iter].getManufacturer() != manufacturer)
        printInvalid(products[0].getManufacturer(), manufacturer, message);
    if (products[iter].getPrice() != price)
        printInvalid(products[0].getPrice(), price, message);
    if (products[iter].getShelfLife() != sh)
        printInvalid(products[0].getShelfLife(), sh, message);
    if (products[iter].getQuantity() != q)
        printInvalid(products[0].getQuantity(), q, message);
}

string chekingOutput(Product** products, const char* str, int i) {
    fileReader mReader;
    stringstream buffer{};
    streambuf* old_cout_buf = cout.rdbuf(buffer.rdbuf());
    mReader.filling(products, str, i);
    cout.rdbuf(old_cout_buf);
    return buffer.str();
}

void creatingTestFiles() {
    ofstream out("test1.txt");
    out << "milk;Nestle;3.5;10;100" << endl;
    out << "bread;Dobryanka;3;7;50" << endl;
    out.close();

    ofstream out2("test2.txt");
    out2 << "" << endl;
    out2 << "" << endl;
    out2.close();

    ofstream out3("test3.txt");
    out3 << "milk;Nestle;3.5;10;100;Extra" << endl;
    out3.close();

    ofstream out4("test4.txt");
    out4 << "peach;Google;9.2;11;111;Extra;Extra2" << endl;
    out4 << "bread;Dobryanka;-2;7;50" << endl;
    out4 << "" << endl;
    out4.close();

    ofstream out5("test5.txt");
    out5 << "peach;Google;009.2;11;111;" << endl;
    out5 << "bread;Dobryanka;02;7;50" << endl;
    out5 << "breadik;Dobr;002;7;50" << endl;
    out5 << "milk;Nestle;3.5;10;-100;Extra" << endl;
    out5 << "" << endl;
    out5.close();

}

void testImplFile() {
    int size = 0;
    string myOutput = {};
    string message = {};
    fileReader reader;
    Product* products = nullptr;
    string outputInputError = "Ввод товара на 1 строке не был произведен! Исправьте файл и введите данные заново\nВвод товара на 2 строке не был произведен! Исправьте файл и введите данные заново\n";
    string outputDataError = "Слишком много данных в одной строке! Данные будут проигнорированы\n";
    string outputNegativePrice = "Отрицательная или нулевая цена товара! Исправьте данные в файле! В 2 строке\n";
    string outputNegativeQuantity = "Отрицательное или нулевое количество товара! Исправьте данные в файле! В 4 строке\n";
    string outputInputError3 = "Ввод товара на 3 строке не был произведен! Исправьте файл и введите данные заново\n";
    string outputInputError5 = "Ввод товара на 5 строке не был произведен! Исправьте файл и введите данные заново\n";

    // Тест с корректными данными
    stringstream buffer{};
    streambuf* old_cout_buf = cout.rdbuf(buffer.rdbuf());
    reader.implFile(&products, &size, "test1.txt");
    cout.rdbuf(old_cout_buf);
    string output = buffer.str();
    if(size != 2) printInvalid(size, 2, message);
    checkingData(products, 0, "milk", "Nestle", 3.5, 10, 100);
    checkingData(products, 1, "bread", "Dobryanka", 3, 7, 50);

    // Тест с 0 количеством товаров
    products = nullptr;
    size = 0;
    buffer = {};
    old_cout_buf = cout.rdbuf(buffer.rdbuf()); 
    reader.implFile(&products, &size, "test2.txt");
    cout.rdbuf(old_cout_buf);
    output = buffer.str();

    if (size != 0) printInvalid(size, 0, message);
    if (output != outputInputError) printInvalid(output, outputInputError, message);

    // Тест с некорректным форматом данных
    products = nullptr;
    size = 0;
    buffer = {};
    old_cout_buf = cout.rdbuf(buffer.rdbuf());
    reader.implFile(&products, &size, "test3.txt");
    cout.rdbuf(old_cout_buf);
    output = buffer.str();

    if(output != outputDataError) printInvalid(output, outputDataError, message);
    if(size != 1) printInvalid(size, 1, message);

    // Тест с отрицательной ценой и с некорректным форматом данных
    products = nullptr;
    size = 0;
    buffer = {};
    old_cout_buf = cout.rdbuf(buffer.rdbuf());
    reader.implFile(&products, &size, "test4.txt");
    cout.rdbuf(old_cout_buf);
    output = buffer.str();

    if(output != outputDataError + outputDataError + outputNegativePrice + outputInputError3) 
        printInvalid(output, outputDataError + outputDataError + outputNegativePrice + outputInputError3, message);
    if(size != 2) printInvalid(size, 2, message);

    // Тест с отрицательным количеством и пустыми строчками
    products = nullptr;
    size = 0;
    buffer = {};
    old_cout_buf = cout.rdbuf(buffer.rdbuf());
    reader.implFile(&products, &size, "test5.txt");
    cout.rdbuf(old_cout_buf);
    output = buffer.str();
    if(output != outputNegativeQuantity + outputDataError + outputInputError5) 
        printInvalid(output, outputNegativeQuantity + outputDataError + outputInputError5, message);
    if(size != 4) printInvalid(size, 4, message);
}


void testParsingTXT() {
    fileReader fr;
    string output = {};
    string myOutput = {};
    string message = {};
    const char* str1 = "Milk;Manufacturer;1.99;7;10";
    const char* str2 = "Bread;Manufacturer;0.99;7;10";
    const char* str3 = "Sugar;Manufacturer;2.49;30;5";
    const char* str4 = "Juice;Manufacturer;-1.5;1;5";
    const char* str5 = "Salt;Manufacturer;-0.49;0;-2";
    string outputNegativePrice4 = "Отрицательная или нулевая цена товара! Исправьте данные в файле! В 4 строке\n";
    string outputNegativePrice5 = "Отрицательная или нулевая цена товара! Исправьте данные в файле! В 5 строке\n";
    string outputNegativeSH5 = "Отрицательный или нулевой срок годности товара! Исправьте данные в файле! В 5 строке\n";
    string outputNegativeQuantity5 = "Отрицательное или нулевое количество товара! Исправьте данные в файле! В 5 строке\n";

    Product* products = new Product[5];

    fr.filling(&products, str1, 0);
    checkingData(products, 0, "Milk", "Manufacturer", 1.99, 7, 10);

    fr.filling(&products, str2, 1);
    checkingData(products, 1, "Bread",  "Manufacturer", 0.99, 7, 10);

    fr.filling(&products, str3, 2);
    checkingData(products, 2, "Sugar", "Manufacturer", 2.49, 30, 5);

    // Тесты на обработку некорректных данных
    //TODO: надо сделать проверку на вывод

    myOutput = outputNegativePrice4;
    output = chekingOutput(&products, str4, 3);
    if (output != myOutput) printInvalid(output, myOutput, message);
    checkingData(products, 3, "Juice", "Manufacturer", - 1.5, 1, 5);

    myOutput = outputNegativePrice5 + outputNegativeSH5 + outputNegativeQuantity5;
    output = chekingOutput(&products, str5, 4);
    if (output != myOutput) printInvalid(output, myOutput, message);
    checkingData(products, 4, "Salt", "Manufacturer", -0.49, 0, -2);

    delete[] products;
    products = nullptr;
}

void fillingForTest(Product** products, int iter, double price, int sh, int q){
    (*products)[iter].setName("test name");
    (*products)[iter].setManufacturer("test manufacturer");
    (*products)[iter].setPrice(price);
    (*products)[iter].setShelfLife(sh);
    (*products)[iter].setQuantity(q);
}

void deleteProductData(Product** products) {
    delete[] *products;
    *products = nullptr;

}

void testRemoveNegative() {
    fileReader fr;
    Product* products = new Product[3];
    string message{};
    int size = 3;
    fillingForTest(&products, 0, 9.2, 11, 111);
    fillingForTest(&products, 1, 1, 11, 1411);
    fillingForTest(&products, 2, 4, 141, 111);
    //тест на 1 продукт с <= 0 полем
    fr.removeNegative(&products, &size);
    if (size != 3) printInvalid(size, 3, message);
    deleteProductData(&products);

    size = 3;
    products = new Product[3];
    fillingForTest(&products, 0, -9.2, 011, 0111);
    fillingForTest(&products, 1, 0, 0, 0);
    fillingForTest(&products, 2, 4, 141, 111);
    //тест на 1 продукт с > 0 полями
    fr.removeNegative(&products, &size);
    if (size != 1) printInvalid(size, 1, message);
    deleteProductData(&products);

    size = 3;
    products = new Product[3];
    fillingForTest(&products, 0, -9.2, -11, -111);
    fillingForTest(&products, 1, -91, -11, -071411);
    fillingForTest(&products, 2, -8.4, -1041, -111);
    //тест на все продукты с <= 0 полями
    fr.removeNegative(&products, &size);
    if (size != 0) printInvalid(size, 0, message);
    deleteProductData(&products);

}

void testSortByName() {
    int result = 0;
    int size = 5;
    sorting sort;
    Product* products = new Product[5];
    Product* sortList = new Product[5];
    string message = {};
    products[0].setName("Milk");
    products[0].setManufacturer("Looped Menu Milk Fabrik");
    products[0].setPrice(1.35);
    products[0].setShelfLife(1000);
    products[0].setQuantity(1024);

    products[1].setName("milk");
    products[1].setManufacturer("Google Milk Fabrik");
    products[1].setPrice(8.996);
    products[1].setShelfLife(10);
    products[1].setQuantity(1);

    products[2].setName("LIPSIHA");
    products[2].setManufacturer("instasamka");
    products[2].setPrice(1.345);
    products[2].setShelfLife(10);
    products[2].setQuantity(14);

    products[3].setName("Milk");
    products[3].setManufacturer("Fabrik Milkis");
    products[3].setPrice(1.35);
    products[3].setShelfLife(1000);
    products[3].setQuantity(1024);

    products[4].setName("Milk");
    products[4].setManufacturer("Dora goblin fabtik");
    products[4].setPrice(1.35);
    products[4].setShelfLife(1000);
    products[4].setQuantity(1024);


    result = sort.sortByName(&products, &sortList, size, "Milk", true);

    if (result != 3) printInvalid(result, 3, message);
    deleteProductData(&products);


}

void testSortByNamePrice() {
    int result = 0;
    int size = 5;
    sorting sort;
    Product* products = new Product[5];
    Product* sortList = new Product[5];
    string message = {};
    products[0].setName("Bread");
    products[0].setManufacturer("Looped Menu Milk Fabrik");
    products[0].setPrice(1.99);
    products[0].setShelfLife(1000);
    products[0].setQuantity(1024);

    products[1].setName("milk");
    products[1].setManufacturer("Google Milk Fabrik");
    products[1].setPrice(8.996);
    products[1].setShelfLife(10);
    products[1].setQuantity(1);

    products[2].setName("Bread");
    products[2].setManufacturer("instasamka");
    products[2].setPrice(1.345);
    products[2].setShelfLife(10);
    products[2].setQuantity(14);

    products[3].setName("Milk");
    products[3].setManufacturer("Fabrik Milkis");
    products[3].setPrice(1.25);
    products[3].setShelfLife(1000);
    products[3].setQuantity(1024);

    products[4].setName("Bread");
    products[4].setManufacturer("Dora goblin fabtik");
    products[4].setPrice(1.36);
    products[4].setShelfLife(1000);
    products[4].setQuantity(1024);

    result = sort.sortByNamePrice(&products, &sortList, size, "Bread", 1.35, true);

    if (result != 1) printInvalid(result, 1, message);
    deleteProductData(&products);

}

void testSortBySH() {
    int result = 0;
    int size = 5;
    sorting sort;
    Product* products = new Product[5];
    Product* sortList = new Product[5];
    string message = {};
    products[0].setName("Milk");
    products[0].setManufacturer("Looped Menu Milk Fabrik");
    products[0].setPrice(1.35);
    products[0].setShelfLife(1004);
    products[0].setQuantity(1024);

    products[1].setName("milk");
    products[1].setManufacturer("Google Milk Fabrik");
    products[1].setPrice(8.996);
    products[1].setShelfLife(10);
    products[1].setQuantity(1);

    products[2].setName("LIPSI HA");
    products[2].setManufacturer("instasamka");
    products[2].setPrice(1.345);
    products[2].setShelfLife(10);
    products[2].setQuantity(14);

    products[3].setName("Milk");
    products[3].setManufacturer("Fabrik Milkis");
    products[3].setPrice(1.35);
    products[3].setShelfLife(999);
    products[3].setQuantity(1024);

    products[4].setName("Milk");
    products[4].setManufacturer("Dora goblin fabtik");
    products[4].setPrice(1.35);
    products[4].setShelfLife(1009);
    products[4].setQuantity(1024);

    result = sort.sortByShelfLife(&products, &sortList, size, 1000, true);

    if (result != 2) printInvalid(result, 2, message);
    deleteProductData(&products);

}

void test::startTest() {
    creatingTestFiles();
    printCorrect(&testImplFile, "Тесты на чтения файла пройдены");
    printCorrect(&testParsingTXT, "Тесты на заполнения данных пройдены");
    printCorrect(&testRemoveNegative, "Тесты на удаление товаров с отрицательными полями (цена, срок годности, количество) пройдены");
    printCorrect(&testSortByName, "Тесты на выборку по имени пройдены");
    printCorrect(&testSortByNamePrice, "Тесты на выборку по имени и цене пройдены");
    printCorrect(&testSortBySH, "Тесты на выборку по сроку годности пройдены");
}