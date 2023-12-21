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
	bool hasLoop = false;
	
	int deleted = 0;
	while (!hasLoop && matrix.lines() != 0 && matrix.columns() != 0) {
		deletion.clear();
		for (int i = 0; i < matrix.columns(); i++) {
			int count=0;
			for (int j = 0; j < matrix.lines(); j++) {
				if (matrix[j][i])
					++count;
			}
			if (count == 0) {
				deletion.push_back(i);
				int temp = i + 1;
				if (!solve.empty() && temp > solve.back())
					temp += deleted;
				solve.push_back(temp);
				
			}
		}

		hasLoop = true;
		for (int i = static_cast<int>(deletion.size())-1; i >=0 ; --i) {
			deleteColumn(matrix, deletion[i]);
			deleteLine(matrix, deletion[i]);
			++deleted;
			hasLoop = false;
		}
	}
	return solve;
}

std::vector<int> topologySortMatrix_(BoolMatrix matrix) {
	std::vector<int> solve;
	BoolVector disjunctions = matrix.disjunction();
	BoolVector deleted(matrix.lines(), false);
	
	while (disjunctions != BoolVector(matrix.lines(), false)) {
		BoolVector tempDeleted(matrix.lines(), false);
		disjunctions = matrix.disjunction(); // nullified columns
		tempDeleted |= ~disjunctions;
		for (int i = 0; i < tempDeleted.sizeOf(); ++i) {
			if (tempDeleted[i] == true && tempDeleted[i]!=deleted[i]) {
				solve.push_back(i + 1);
				matrix[i].setAll(false);
			}
		}
		deleted |= tempDeleted;
		if (tempDeleted == BoolVector(tempDeleted.sizeOf(), false)) {
			return solve;
		}
	}
	return solve;
}

bool topologySortList(List<Graph>& graph) {
	List<Graph> temp;
	bool hasLoop = false;

	while (graph.getSize() > 0 && !hasLoop) {
		for (List<Graph>::_iterator graphIter = graph.begin(); graphIter != graph.end(); ++graphIter) {
			if ((*graphIter).st == 0) {
				List<Graph>::_iterator temp_(temp.end()), tempMove(graphIter++);
				tempMove.move(temp_);
				
				graph.resize();
				temp.resize();	
			}
			std::cout << graph;
		}
		

		for (List<Graph>::_iterator tempIter = temp.begin(); tempIter != temp.end(); ++tempIter) {
			for (List<List<Graph>::_iterator>::_iterator trailerIter = (*tempIter).trailer.begin(); trailerIter != (*tempIter).trailer.end(); ++trailerIter) {
				(*(*trailerIter)).st--;
			}
		}



	}
	temp.swap(graph);
	return true;
}