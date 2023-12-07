#include <iostream>
#include "Topology.h"
#include "BoolMatrix.h"

int main() {
	BoolMatrix temp(5, 5, false);
	std::vector<int> tempVector = topologySortMatrix(temp);
	for (int iter : tempVector) {
		std::cout << iter << ' ';
	}
	return 0;
}