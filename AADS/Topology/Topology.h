#pragma once
#include <list>
#include <vector>
#include "BoolMatrix.h"

struct graph;

std::vector<int> topologySortMatrix(BoolMatrix& matrix);

void topologySortList(std::list<graph> graph);