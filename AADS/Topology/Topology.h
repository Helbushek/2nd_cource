#pragma once
#include <list>
#include <vector>
#include "BoolMatrix.h"

struct graph {
	std::list<graph*> trailer;
	int st;
	int key;
};

BoolMatrix deleteColumn(BoolMatrix& matrix, int index);

BoolMatrix deleteLine(BoolMatrix& matrix, int index);

std::vector<int> topologySortMatrix(BoolMatrix& matrix);

void topologySortList(std::list<graph> graph);