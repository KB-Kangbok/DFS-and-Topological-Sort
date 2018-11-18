#include "graph.h"
#include <iostream>

int main() {
	graph<std::string> G("clothing.txt");

	std::list<std::string> L;
	G.topoSort(L, "watch");
}
