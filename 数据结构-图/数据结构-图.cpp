#include <iostream>
#include "Graph.hpp"
using namespace std;
void solve();
int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		solve();
	}
	return 0;
}
void solve()
{
	size_t n, e;//, s;
	cin >> n >> e; //>> s;
	GRAPH::Graph<size_t, size_t> graph(n);

	for (size_t i = 0, row, col; i < e; i++)
	{
		cin >> row >> col;
		graph.addDirectedEdge(row, col);
	}
	//graph.DFS(s);
	//cout << endl;
	//graph.BFS(s);
	graph.topSort();
}