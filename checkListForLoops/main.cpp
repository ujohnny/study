#include "list.hpp"
#include <iostream>

int main() {
	List list;
	list.add();
	list.add();
	list.add();
	list.add();
	list.add();
	std::cout << "size " << list.getSize() << std::endl;
	list.makeLoop(2, 3);
	if (list.hasLoop())
		std::cout << "ok";
}
