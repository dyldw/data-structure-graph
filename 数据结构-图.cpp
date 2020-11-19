#include <iostream>
#include "Graph.hpp"
#include <string>
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
	size_t n, e;
	cin >> n >> e;
	/*char s;
	cin >> s;*/
	GRAPH::Graph<char, double> graph(n);

	for (size_t i = 0; i < e; i++)
	{
		char row, col;
		cin >> row >> col;
		graph.addDirectedEdge(row, col);
	}
	//graph.addDirectedEdge("hello", "world");
	//graph.DFS(s);
	//cout << endl;
	//graph.BFS(s);
	//graph.topSort();
	if (graph.hasCycle())
	{
		cout << "YES" << endl;
	}
	else
	{
		graph.topSort();
		cout << "NO" << endl;
	}
}