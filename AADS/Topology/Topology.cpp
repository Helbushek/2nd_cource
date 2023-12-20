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
	while (!hasLoop && matrix.lines() != 0 && matrix.columns() != 0) {
		deletion.clear();
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

		hasLoop = true;
		for (int i = static_cast<int>(deletion.size())-1; i >=0 ; --i) {
			deleteColumn(matrix, deletion[i]);
			deleteLine(matrix, deletion[i]);
			hasLoop = false;
		}
	}
	return solve;
}

bool topologySortList(List<Graph>& graph) {
	List<Graph> temp;
	while (graph.getSize() > 0) {
		bool ifFoundOne = false;
		List<Graph>::_iterator iter = graph.begin();
		while (iter != nullptr) { // Проход для выбора нулевых узлов
			if ((*iter).st == 0) {
				List<Graph>::_iterator tempIt = temp.end();
				iter.move(tempIt);

				if (!ifFoundOne)
					ifFoundOne = true;
			}
		}
		iter = temp.begin();
		while (iter != nullptr) { // Проход для уменьшения счётчика у тех, на которые вели нулевые узлы
			List<List<Graph>::_iterator>::_iterator tempIter = (*iter++).trailer.begin();
			while (tempIter != (*iter).trailer.end()) {
				--(*(*tempIter++)).st;
			}
		}
	// Повторять, пока не конатся нулевые элементы, можно завести флаг ... !!! Для проверки цикла 
		if (!ifFoundOne) {
			assert("loop in graph in TopologySortList");
			temp += graph;
			temp.swap(graph);
			return false;
		}
	}
	// Восстановление ссылок в trailer и значений st
	List<Graph>::_iterator iter = temp.begin(); // С новым перемещением ссылки восстанавливать не нужно 
	while (iter != temp.end()) {
		List<List<Graph>::_iterator>::_iterator innerIter = (*iter++).trailer.begin();
		while (innerIter != (*iter++).trailer.end()) {
			++(*(*innerIter)).st;
		}
	}

	temp.swap(graph); // graph должен оказаться пустым, если все решения совпадают
	return true;
}