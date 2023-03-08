#pragma once
#include "Product.h"
using namespace cproduct;
namespace reader {
	class fileReader {
	public:
		int readFile(Product**, bool*);
		void fillFile(Product**);
	};
}
