#include "dijkstras.h"

int main() {
    Graph G;
    file_to_graph("src/small.txt", G);
	std::vector<int> previous;
	std::vector<int> distances = dijkstra_shortest_path(G, 0, previous);

	std::vector<int> path = extract_shortest_path(distances, previous, 3);
	print_path(path, distances[3]);
}