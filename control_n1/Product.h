#pragma once
#include <string>
using namespace std;

namespace cproduct {
	class Product
	{
	public:

		string getName();
		void setName(string);

		string getManufacturer();
		void setManufacturer(string);

		double getPrice();
		void setPrice(int);

		int getShelfLife();
		void setShelfLife(int);

		int getQuantity();
		void setQuantity(int);


	private:
		string name;
		string manufacturer;
		double price;
		int shelfLife;
		int quantity;

	};
}
