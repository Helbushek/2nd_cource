#pragma once
#include <iostream>
#include <ios>
#include <vector>
#include "/Users/Александр/2nd_cource/OOP/BoolMatrix/BoolMatrix.h"
#include "List.h"

struct Trailer;

struct Graph {
	List<List<Graph>::_iterator> trailer;
	int st=0;
	int key=0;
};

struct arc
{
	int left;
	int right;

	int max() const {
		int max = left;
		if (right > left) max = right;
		return max;
	}

	int min() const {
		int min = left;
		if (right < left) min = right;
		return min;
	}

};

inline std::istream& operator>>(std::istream& is, arc& arc) {
	is >> arc.left >> arc.right;
	return is;
}

inline std::ostream& operator<<(std::ostream& os, const Graph& graph) {
	
	os << graph.key << " " << graph.st << " |: ";
	for (auto iter = graph.trailer.begin(); iter != graph.trailer.end(); ++iter) {
		os << (*(*iter)).key << ' ';
	}
	os << std::endl;
	return os;
}

std::vector<int> topologySortMatrix(BoolMatrix matrix);

List<Graph>& topologySortList(List<Graph>& graph);