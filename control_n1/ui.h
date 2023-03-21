#pragma once
#include "Product.h"
using namespace cproduct;

namespace UI {
	class ui 
	{
	public:
		int getInt();
		int getMenuVar(int, int);
		int getSize();
		double getDouble();
		int readConsole(Product**);
		void outConsole(Product**, int);
	};
}

