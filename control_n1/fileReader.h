#pragma once
#include "Product.h"
using namespace cproduct;
namespace reader {
	class fileReader {
	public:
		int readFile(Product**, string);
		void fillFile(Product**, int);
		void implFile(Product**, int*, string);
		void filling(Product**, const char*, int );
		void removeNegative(Product**, int*);
	};
}
