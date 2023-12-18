#include <assert.h>
#include "Topology.h"

BoolMatrix deleteColumn(BoolMatrix& matrix, int index){
	assert(index >= 0 && index < matrix.columns());
	BoolMatrix temp(matrix.lines(), matrix.columns() - 1, 0);
	for (int i = 0; i < matrix.lines(); i++) {
		for (int j = 0; j < index; j++) {
			temp[i][j] = matrix[i][j];
		}
		for (int j=index; j<matrix.columns()-1; ++j) { 
				temp[i][j] = matrix[i][j+1];
		}
	}
	matrix.swap(temp);
	return matrix;
}

BoolMatrix deleteLine(BoolMatrix& matrix, int index) {
	assert(index >= 0 && index < matrix.lines());
	BoolMatrix temp(matrix.lines()-1, matrix.columns(), 0);
	for (int i = 0; i < index; i++) {
		temp[i] = matrix[i];
	}
	for (int i = index; i < matrix.lines()-1; ++i) {
			temp[i] = matrix[i+1];
	}
	matrix.swap(temp);
	return matrix;
}

std::vector<int> topologySortMatrix(BoolMatrix& matrix) {
	std::vector<int> solve;
	std::vector<int> deletion;
	while (matrix.lines() != 0 && matrix.columns() != 0) {
		deletion.clear();
		bool flag = 0;
		for (int i = 0; i < matrix.columns(); i++) {
			int count=0;
			for (int j = 0; j < matrix.lines(); j++) {
				if (matrix[j][i] != 0)
					++count;
			}
			if (count == 0) {
				solve.push_back(i + 1);
				deletion.push_back(i);
			}
		}

		for (int i = deletion.size()-1; i >=0 ; --i) {
			deleteColumn(matrix, deletion[i]);
			deleteLine(matrix, deletion[i]);
			flag = 1;
		}

		if (flag == 0) {
			assert(!"Graph has loop");
			break;
		}
	}
	return solve;
}

void topologySortList(List<graph> graph) {

}