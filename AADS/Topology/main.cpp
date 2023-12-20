#include "Topology.h"

struct arc 
{
	int left;
	int right;

	int max() const{
		int max = left;
		if (right > left) max = right;
		return max;
	}

	int min() const{
		int min = left;
		if (right < left) min = right;
		return min;
	}

};

std::istream& operator>>(std::istream& is, arc &arc) {
	is >> arc.left >> arc.right;
	return is;
}


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
		++iteratorRight.getNode()->get().st;
	}

	return graph;
}

List<Graph> listFromMatrix(std::vector<bool> matrix, int size) {
	BoolMatrix temp(size, size, false);
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; j++)
			temp[i][j] = matrix[i + (size)*j];
	}

	List<Graph> graph(size, Graph());
	for (int i = 0; i < size; ++i) {
		graph[i].key = i + 1;
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
	std::vector<bool> matrix{ 0, 1, 1,
							0, 0, 1,
							0, 0, 0, };

	List<Graph> graph = listFromMatrix(matrix, sqrt(matrix.size()));
	topologySortList(graph);

	return 0;
}