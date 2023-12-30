#include <assert.h>
#include "Topology.h"

std::vector<int> topologySortMatrix(BoolMatrix matrix) {
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

List<Graph>& topologySortList(List<Graph>& graph) {
	List<Graph> temp;
	bool hasLoop = false;

	while (graph.getSize() > 0 && !hasLoop) {
		int addedNodes = 0;
		for (List<Graph>::_iterator graphIter = graph.begin(); graphIter != graph.end();) {
			if ((*graphIter).st == 0) {
				List<Graph>::_iterator temp_(temp.end()), tempMove(graphIter++);
				tempMove.move(temp_);
				graph.resize();
				temp.resize();
				++addedNodes;
			}
			else graphIter++;
		}
		if (addedNodes == 0) {
			hasLoop = true;
			continue;
		}
		List<Graph>::iterator tempIter = temp.begin();
		for (int j = 0; j < temp.getSize() - addedNodes; ++j, ++tempIter);
		for (; tempIter != temp.end(); ++tempIter) {
			for (auto trailerIter = (*tempIter).trailer.begin(); trailerIter != (*tempIter).trailer.end(); ++trailerIter) {
				--(*(*trailerIter)).st;
			}
		}

	}
	if (hasLoop) {
		graph.clear();
		return graph;
	}
	temp.swap(graph);
	graph.resize();
	for (List<Graph>::_iterator iter = graph.begin(); iter != graph.end(); ++iter) {
		for (List<List<Graph>::_iterator>::_iterator innerIter = (*iter).trailer.begin(); innerIter != (*iter).trailer.end(); ++innerIter) {
			++(*(*innerIter)).st;
		}
	}
	return graph;
}