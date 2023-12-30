#include <iostream>
#include "Topology.h"

List<Graph> listFromArcs(std::vector<arc> arcs) {
	int nodes = 0;
	for (int i = 0; i < arcs.size(); i++) {
		if (nodes < arcs[i].max())
			nodes = arcs[i].max();
	}
	List<Graph> graph(nodes, Graph());
	for (int i = 0; i < nodes; ++i) {
		graph[i].key = i + 1;
	}
	for (int i = 0; i < arcs.size(); ++i) {
		int right = arcs[i].right;
		int left = arcs[i].left;

		List<Graph>::iterator iteratorLeft, iteratorRight; // take 2 iters
		iteratorLeft = iteratorRight = graph.begin(); // they look at begin of list
		for (int j = 0; j < right-1; ++j, ++iteratorRight); // right goes to right node of arc
		for (int j = 0; j < left - 1; ++j, ++iteratorLeft); // left goes to left node of arc
		(*iteratorLeft).trailer.pushBack(iteratorRight); // left iter calls node ptr, that calls its key which is graph structure, where we call for trailer link, which we can use to push back link to node that right iterator points to
		(*iteratorRight).st++;
	}

	return graph;
}

BoolMatrix boolMatrixFromVector(std::vector<std::vector<bool>> matrix, int size) {
	BoolMatrix temp(size, size, false);
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j <size ; ++j)
			temp[i][j] = matrix[i][j];
	}
	return temp;
}

List<Graph> listFromMatrix(std::vector<std::vector<bool>> matrix, int size) {
	BoolMatrix temp = boolMatrixFromVector(matrix, size);

	List<Graph> graph(size, Graph());
	for (int i = 0; i < size; ++i) {
		graph[i].key = i + 1;
		graph[i].st = 0;
		graph[i].trailer = List<List<Graph>::_iterator>();
		graph[i].trailer.clear();
	}

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (temp[i][j]) {
				List<Graph>::_iterator tempIter = graph.begin();
				for (int k = 0; k < j; ++k, ++tempIter);
				graph[i].trailer.pushBack(tempIter);
				++(*tempIter).st;
			}
		}
	}
	return graph;
}

int main() {
	std::vector<std::vector<bool>> matrix{
	{0, 0, 0, 0,},
	{0, 0, 0, 0,},
	{0, 0, 0, 0,},
	{1, 1, 1, 0,}
	};

	std::vector<std::vector<bool>> matrix2{
	{0, 0, 0, 1,},
	{0, 0, 1, 0,},
	{1, 0, 0, 0,},
	{0, 0, 1, 0,}
	};

	std::vector<std::vector<bool>> matrix3{
	{0, 0, 0, 0,},
	{1, 0, 1, 0,},
	{0, 0, 0, 0,},
	{0, 0, 1, 0,}
	};

	BoolMatrix tempMatrix = boolMatrixFromVector(matrix, matrix.size());
	std::vector<int> solve = topologySortMatrix(tempMatrix);
	for (auto iter : solve) {
		std::cout << iter << ' ';
	}
	std::cout << '\n';


	std::cout << "MATRIX" << std::endl;
	List<Graph> tempList = listFromMatrix(matrix2, matrix.size());
	std::cout << "key    st  |: trailer" << std::endl;
	std::cout << ' ' << tempList;
	tempList = topologySortList(tempList);
	std::cout << tempList << std::endl;

	return 0;
}