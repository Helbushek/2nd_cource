#include "Topology.h"

struct graph {

};



std::vector<int> topologySortMatrix(BoolMatrix& matrix) {
	std::vector<int> solve;
	while (matrix.lines() != 0 && matrix.columns() != 0) {
		for (int i = 0; i < matrix.columns(); i++) {
			int count =0;
			for (int j = 0; j < matrix.lines(); j++) {
				if (matrix[j][i] != 0)
					++count;
			}
			if (count == 0) {
				solve.push_back(i + 1);
				deleteLine
			}
		}
	}
}

void topologySortList(std::list<graph> graph) {

}