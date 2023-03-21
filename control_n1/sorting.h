#pragma once
namespace sorted {
	class sorting {
	public:
		int sortByName(Product**, Product**, int, string, bool);
		int sortByNamePrice(Product**, Product**, int, string, double, bool);
		int sortByShelfLife(Product**, Product**, int, int, bool);
	};
}