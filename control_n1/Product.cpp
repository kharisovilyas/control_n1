#include "Product.h"
using namespace cproduct;

string Product::getName() {
	return Product::name;
}
void Product::setName(string mName) {
	Product::name = mName;
}


string Product::getManufacturer() {
	return Product::manufacturer;
}
void Product::setManufacturer(string mManufacturer) {
	Product::manufacturer = mManufacturer;
}


double Product::getPrice() {
	return Product::price;
}
void Product::setPrice(int mPrice) {
	Product::price = mPrice;
}


int Product::getShelfLife() {
	return Product::shelfLife;
}
void Product::setShelfLife(int mShelfLife) {
	Product::shelfLife = mShelfLife;
}


int Product::getQuantity() {
	return Product::quantity;
}

void Product::setQuantity(int mQuantity) {
	Product::quantity = mQuantity;
}