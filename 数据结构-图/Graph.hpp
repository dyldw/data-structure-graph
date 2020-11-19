#ifndef MY_GRAPH
#define MY_GRAPH
#include <vector>
#include <queue>
#include <array>
#include <iostream>
namespace GRAPH
{
	// todo graph类的默认构造函数没有测试
	// todo graph类的两种最短路径算法没有实现
	// todo graph类的最小生成树没有实现

	template <typename VertexType,typename EdgeType>
	class Graph
	{
	private:
		std::vector<VertexType> _vertexs;
		std::vector<EdgeType*> _edges;
		std::vector<bool> _visited;//小心std::vector<bool>。
		size_t _numEdge;

	public:
		enum { infinity = 1000000 };
		Graph(size_t size)
		{ 
			_numEdge = 0;
			for (size_t i = 0; i < size; i++)
			{
				_edges.push_back(new EdgeType[size]);
				for (size_t j = 0; j < size; j++)
				{
					_edges[i][j] = 0;
				}
				//下面这句是临时用的
				_vertexs.push_back(static_cast<VertexType>(i + 1));
			}
			_visited.resize(_vertexs.size(), false);
		}
		Graph()
		{
			//建立结点数组
			setVertexs();
			//建立边矩阵
			setEdges();

			_visited.resize(_vertexs.size(), false);
		}
		Graph(Graph const&) = delete;
		~Graph()
		{
			for (auto& edge : _edges)
			{
				delete[] edge;
				edge = nullptr;
			}
		}
		int const howManyEdges() { return _numEdge; }
		int const howManyVertex() { return _vertexs.size(); }
		void resetEdges();
		void showEdgesMatrix();
		void showVertexsArray();
		void DFS(VertexType const);
		void BFS(VertexType const);
		void topSort() {
			std::vector<VertexType> tops;
			topSortHelper(tops);
			for (auto const& vertex : tops)
			{
				std::cout << vertex << " ";
			}
			std::cout << std::endl;
		}
		bool topSortHelper(std::vector<VertexType>&);
		void addEdge(VertexType const& v1, VertexType const& v2, EdgeType const& weight = 1);
		void addDirectedEdge(VertexType const& v1, VertexType const& v2, EdgeType const& weight = 1);
		//hasloop()函数一般用于有向图
		bool hasLoop();
	private:
		void initialVisited();
		size_t getIndex(VertexType const& ver)const
		{
			for (size_t i = 0; i < _vertexs.size(); i++)
			{
				if (ver == _vertexs[i])return i;
			}
			return infinity;
		}
		void _addDirectedEdge(size_t row, size_t col, EdgeType weight = 1)
		{
			_edges[row][col] = weight; _numEdge++;
		}
		void _addEdge(size_t row, size_t col, EdgeType weight = 1)
		{
			_edges[row][col] = weight;
			_edges[col][row] = weight;
			_numEdge++;
		}
		void bfsHelper(size_t);
		void dfsHelper(size_t);
		void setVertexs();
		void setEdges();
	};

	template<typename VertexType, typename EdgeType>
	inline void Graph<VertexType, EdgeType>::resetEdges()
	{
		setEdges();
	}
	template<typename VertexType, typename EdgeType>
	void Graph<VertexType, EdgeType>::showEdgesMatrix()
	{
		for (size_t i = 0; i < _vertexs.size(); i++)
		{
			for (size_t j = 0; j < _vertexs.size(); j++)
			{
				std::cout << _edges[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}
	template<typename VertexType, typename EdgeType>
	void Graph<VertexType, EdgeType>::showVertexsArray()
	{
		for (size_t i = 0; i < _vertexs.size(); i++)
		{
			std::cout << _vertexs[i] << " ";
		}
		std::cout << std::endl;
	}
	template<typename VertexType, typename EdgeType>
	void Graph<VertexType, EdgeType>::DFS(VertexType const s)
	{
		//for (auto& state : _visited) { state = false; }
		//vector<bool>比较特殊，按位储存做了优化所以上句有BUG
		//for (bool& state : _visited) { state = false; }
		//显式也不可以
		initialVisited();
		dfsHelper(getIndex(s));
		for (size_t i = 0; i < _vertexs.size(); i++)
		{
			if (!_visited[i])
			{
				dfsHelper(i);
			}
		}
	}
	template<typename VertexType, typename EdgeType>
	void Graph<VertexType, EdgeType>::BFS(VertexType const s)
	{
		initialVisited();
		bfsHelper(getIndex(s));
		for (size_t i = 0; i < _visited.size(); i++)
		{
			if (_visited[i] == false)
			{
				bfsHelper(i);
			}
		}
	}
	template<typename VertexType, typename EdgeType>
	bool Graph<VertexType, EdgeType>::topSortHelper(std::vector<VertexType>& tops)
	{
		std::vector<size_t> inDegree;
		inDegree.resize(_vertexs.size(), 0);
		initialVisited();
		for (size_t i = 0; i < _vertexs.size(); i++)
		{
			for (size_t j = 0; j < _vertexs.size(); j++)
			{
				if (_edges[i][j])
				{
					inDegree[j]++;
				}
			}
		}

		std::queue<size_t> que;
		for (size_t i = 0; i < inDegree.size(); i++)
		{
			if (inDegree[i] == 0)
			{
				que.push(i);
				_visited[i] = true;
			}
		}
		while (!que.empty())
		{
			tops.push_back(_vertexs[que.front()]);
			for (size_t i = 0; i < inDegree.size(); i++)
			{
				if (_visited[i] == false && _edges[que.front()][i])
				{
					inDegree[i]--;
					if (inDegree[i] == 0)
					{
						que.push(i);
						_visited[i] = true;
					}
				}
			}
			que.pop();
		}

		for (size_t i = 0; i < _visited.size(); i++)
		{
			if (_visited[i] == false)
			{
				return true;
			}
		}
		return false;
	}
	template<typename VertexType, typename EdgeType>
	inline void Graph<VertexType, EdgeType>::addEdge(VertexType const& v1, VertexType const& v2,EdgeType const& weight)
	{
		size_t row = getIndex(v1);
		size_t col = getIndex(v2);
		_addEdge(row, col, weight);
	}
	template<typename VertexType, typename EdgeType>
	inline void Graph<VertexType, EdgeType>::addDirectedEdge(VertexType const& v1, VertexType const& v2, EdgeType const& weight)
	{
		size_t row = getIndex(v1);
		size_t col = getIndex(v2);
		_addDirectedEdge(row, col, weight);
	}
	template<typename VertexType, typename EdgeType>
	inline bool Graph<VertexType, EdgeType>::hasLoop()
	{
		std::vector<VertexType> tops;
		return topSortHelper(tops);
	}
	template<typename VertexType, typename EdgeType>
	inline void Graph<VertexType, EdgeType>::initialVisited()
	{
		for (size_t i = 0; i < _visited.size(); i++)
		{
			_visited[i] = false;
		}
	}
	template<typename VertexType, typename EdgeType>
	void Graph<VertexType, EdgeType>::bfsHelper(size_t s)
	{
		//queue<size_t> que
		//此BUG: ‘标记符’语法错误 改符合模式为否，不明原因
		std::queue<size_t> que;
		que.push(s);
		_visited[s] = true;
		while (!que.empty())
		{
			std::cout << _vertexs[que.front()] << " ";
			for (size_t i = 0; i < _vertexs.size(); i++)
			{
				if (_visited[i] == false && _edges[que.front()][i])
				{
					que.push(i);
					_visited[i] = true;
				}
			}
			que.pop();
		}
	}
	template<typename VertexType, typename EdgeType>
	void Graph<VertexType, EdgeType>::dfsHelper(size_t s)
	{
		std::cout << _vertexs[s] << " ";
		_visited[s] = true;
		for (size_t i = 0; i < _vertexs.size(); i++)
		{
			if (_visited[i] == false && _edges[s][i])
			{
				dfsHelper(i);
			}
		}
	}
	template<typename VertexType, typename EdgeType>
	inline void Graph<VertexType, EdgeType>::setVertexs()
	{
		//建立结点数组
		VertexType tmp;
		while (std::cin >> tmp)
		{
			_vertexs.push_back(tmp);
		}
	}
	template<typename VertexType, typename EdgeType>
	void Graph<VertexType, EdgeType>::setEdges()
	{
		_numEdge = 0;
		//建立边矩阵
		for (int i = 0; i < _vertexs.size(); i++)
		{
			EdgeType* tmp = new EdgeType[_vertexs.size()];
			_edges.push_back(tmp);
			for (size_t j = 0; j < _vertexs.size(); j++)
			{
				EdgeType tmp;
				std::cin >> tmp;
				if (tmp >= infinity)
				{
					_edges[i][j] = infinity;
				}
				else
				{
					_edges[i][j] = tmp;
					_numEdge++;
				}
			}
		}
	}
}
#endif