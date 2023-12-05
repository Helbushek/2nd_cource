
#include "List.h"

int main() {
	const List<int> temp(5, 1);
	for (Iterator<const int> iter = temp.begin(); iter != temp.end(); iter++) {
		std::cout << *iter;
	}
	
	std::cout << temp <<std::endl;
	
	return(0);
}