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

std::istream& operator>>(std::istream& is, arc arc) {
	is >> arc.left >> arc.right;
	return is;
}


List<graph> listFromArcs(std::vector<arc> arcs) {
	int nodes = 0;
	for (int i = 0; i < arcs.size(); i++) {
		if (nodes < arcs[i].max())
			nodes = arcs[i].max();
	}
	List<graph> Graph(nodes);
	for (int i = 0; i < nodes; ++i) {
		Graph[i].key = i + 1;
	}
	for (int i = 0; i < arcs.size(); ++i) {
		int right = arcs[i].right;
		int left = arcs[i].left;

		List<graph>::Iterator<graph> iteratorLeft, iteratorRight; // take 2 iters
		iteratorLeft = iteratorRight = Graph.begin(); // they look at begin of list
		for (int j = 0; j < right-1; ++j, ++iteratorRight); // right goes to right node of arc
		for (int j = 0; j < left - 1; ++j, ++iteratorLeft); // left goes to left node of arc
		iteratorLeft.getNode()->get().trailer.pushBack(iteratorRight.getNode()); // left iter calls node ptr, that calls its key which is graph structure, where we call for trailer link, which we can use to push back link to node that right iterator points to
		++iteratorRight.getNode()->get().st;
	}

	return Graph;
}

int main() {
	int size;
	std::cin >> size;
	std::vector<arc> arcs(size);
	for (int i = 0; i < size; ++i) {
		std::cin >> arcs[i];
	}

	List<graph> graph = listFromArcs(arcs);
	topologySortList(graph);

	return 0;
}