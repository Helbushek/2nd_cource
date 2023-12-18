#pragma once
#include <vector>
#include "BoolMatrix.h"
#include "List.h"


struct graph {
	List<List<graph>::Node*> trailer;
	int st=0;
	int key=0;
};

BoolMatrix deleteColumn(BoolMatrix& matrix, int index);

BoolMatrix deleteLine(BoolMatrix& matrix, int index);

std::vector<int> topologySortMatrix(BoolMatrix& matrix);

void topologySortList(List<graph> graph);