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
		void setPrice(double);

		int getShelfLife();
		void setShelfLife(int);

		int getQuantity();
		void setQuantity(int);

		bool isNegavive() const {
			return (price <= 0.0 || quantity <= 0 || shelfLife <= 0);
		}


	private:
		string name{};
		string manufacturer{};
		double price{};
		int shelfLife{};
		int quantity{};

	};
}
