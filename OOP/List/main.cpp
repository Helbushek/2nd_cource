
#include "List.h"

int main() {
	List<int> temp(5, 1);
	for (int i = 0; i < 5; i++) {
		temp[i] = 5-i;
	}
	
	std::cout << temp <<std::endl;
	
	return(0);
}