#pragma once
#include <iostream>
#include <vector>
#include "BoolMatrix.h"
#include "List.h"

struct Trailer;

struct Graph {
	List<List<Graph>::_iterator> trailer;
	int st=0;
	int key=0;
};

inline std::ostream& operator<<(std::ostream& os, const Graph& graph) {
	os << graph.key << ' ' << graph.st << " |: ";
	for (auto iter = graph.trailer.begin(); iter != graph.trailer.end(); ++iter) {
		os << (*(*iter)).key << ' ';
	}
	return os;
}

BoolMatrix deleteColumn(BoolMatrix& matrix, int index);

BoolMatrix deleteLine(BoolMatrix& matrix, int index);

std::vector<int> topologySortMatrix(BoolMatrix& matrix);

std::vector<int> topologySortMatrix_(BoolMatrix matrix);

bool topologySortList(List<Graph>& graph);