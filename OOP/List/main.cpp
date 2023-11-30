
#include "List.h"

int main() {
	List<int> temp(3, 1);
	//temp.set();
	std::cout << std::endl;
	temp.print();
	std::cout << std::endl;
	temp.push(1);
	temp.print();
	return(0);
}