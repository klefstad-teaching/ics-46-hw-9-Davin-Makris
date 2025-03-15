#include "dijkstras.h"

using namespace std;

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous){
	int n = G.numVertices;
	vector<int> distance(n, INF);
	vector<bool> visited(n, false);
	previous.assign(n, -1);
	priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
	pq.push(Edge(-1, source, 0));
	while (!pq.empty()){
		Edge current = pq.top();
		pq.pop();

		int u = current.dst;
		visited[u] = true;
		int uWeight = current.weight;
		for (const auto& edge: G[u]){
			int v = edge.dst;
			int vWeight = edge.weight;
			if (!visited[v] && uWeight + vWeight < distance[v]){
				distance[v] = uWeight + vWeight;
				previous[v] = u;
				pq.push(Edge(u, v, distance[v]));
			}
		}
	}
	return distance;
}
vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination){
	vector<int> path;
	if (destination >= int(distances.size()) || distances[destination] == INF)
		return path;
	for (int cur = destination; cur != -1; cur = previous[cur])
		path.push_back(cur);
	reverse(path.begin(), path.end());
	return path;
}
void print_path(const vector<int>& v, int total){
	for (size_t i = 0; i < v.size(); ++i){
		if (v[i] == INF) {
		    cout << "0 ";
		} else {
		    cout << v[i] << " ";
		}
	}
	cout << endl << "Total cost is " << total << endl;
}