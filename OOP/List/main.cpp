
#include "List.h"

int main() {
	int maxValue = 200;
	List<int> temp(maxValue, 1);
	
	for (int i = maxValue-1; i >= 0; --i) {
		temp[maxValue-1 - i] = i + 1;
	}
	std::cout << temp << std::endl;
	
	temp.sort();

	std::cout << temp << std::endl;


	return(0);
}