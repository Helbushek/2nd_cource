
#include "List.h"

int main() {
	List<int> temp(3, 1);
	//temp.set();
	std::cout << std::endl;
	for (auto iter : temp) {
		std::cout << iter << ' ';
	}
	return(0);
}