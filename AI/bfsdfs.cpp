#include <iostream>
#include <list>
#include <queue>
#include <stack>
using namespace std;

class Graph
{
  int numVertices;
  list<int> *adjList;

public:
  Graph(int numVertices);
  void addEdge(int vertex, int neighbor);
  void BFS(int startVertex);
  void DFS(int startVertex);
};

Graph::Graph(int numVertices)
{
  this->numVertices = numVertices;
  adjList = new list<int>[numVertices];
}

void Graph::addEdge(int vertex, int neighbor)
{
  adjList[vertex].push_back(neighbor);
}

void Graph::BFS(int startVertex)
{
  bool *visited = new bool[numVertices];
  for (int i = 0; i < numVertices; i++)
  {
    visited[i] = false;
  }

  queue<int> queue;
  visited[startVertex] = true;
  queue.push(startVertex);

  while (!queue.empty())
  {
    startVertex = queue.front();
    cout << startVertex << " ";
    queue.pop();

    for (auto adjacentVertex : adjList[startVertex])
    {
      if (!visited[adjacentVertex])
      {
        visited[adjacentVertex] = true;
        queue.push(adjacentVertex);
      }
    }
  }

  delete[] visited;
}

void Graph::DFS(int startVertex)
{
  bool *visited = new bool[numVertices];
  for (int i = 0; i < numVertices; i++)
  {
    visited[i] = false;
  }

  stack<int> stack;
  visited[startVertex] = true;
  stack.push(startVertex);

  while (!stack.empty())
  {
    startVertex = stack.top();
    cout << startVertex << " ";
    stack.pop();

    for (auto adjacentVertex : adjList[startVertex])
    {
      if (!visited[adjacentVertex])
      {
        visited[adjacentVertex] = true;
        stack.push(adjacentVertex);
      }
    }
  }

  delete[] visited;
}

int main()
{
  int numEdges, fromVertex, toVertex, searchChoice, startVertex;

  cout << "Enter number of edges: ";
  cin >> numEdges;

  Graph graph(numEdges + 2);

  cout << "Enter the edges:\n";
  for (int i = 0; i < numEdges; i++)
  {
    cin >> fromVertex >> toVertex;
    graph.addEdge(fromVertex, toVertex);
  }

  cout << "Through which way do you want to search the path?\n (1) BFS \n (2) DFS" << endl;
  cin >> searchChoice;

  switch (searchChoice)
  {
  case 1:
  {
    cout << "Enter starting vertex for BFS: ";
    cin >> startVertex;
    graph.BFS(startVertex);
    cout << endl;
    break;
  }
  case 2:
  {
    cout << "Enter starting vertex for DFS: ";
    cin >> startVertex;
    graph.DFS(startVertex);
    cout << endl;
    break;
  }
  default:
  {
    cout << "Invalid choice" << endl;
  }
  }

  return 0;
}
