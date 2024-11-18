#include <iostream>
#include <stack>
#include <queue>
#include <vector>
using namespace std;

typedef pair<int, int> PII;

void DepthFirstSearch(vector<vector<int>> &graph, int startNode)
{
    int numNodes = graph.size();
    vector<bool> visited(numNodes, false);

    cout << "DFS: ";
    stack<int> stackNodes;
    stackNodes.push(startNode);

    while (!stackNodes.empty())
    {
        int currentNode = stackNodes.top();
        stackNodes.pop();

        if (!visited[currentNode])
        {
            cout << currentNode << " ";
            visited[currentNode] = true;
            for (int i = 0; i < numNodes; i++)
            {
                if (graph[currentNode][i] != 0 && !visited[i])
                {
                    stackNodes.push(i);
                }
            }
        }
    }
    cout << endl;
}

void BreadthFirstSearch(vector<vector<int>> &graph, int startNode)
{
    int numNodes = graph.size();
    vector<bool> visited(numNodes, false);

    cout << "BFS: ";
    queue<int> queueNodes;
    queueNodes.push(startNode);

    while (!queueNodes.empty())
    {
        int currentNode = queueNodes.front();
        queueNodes.pop();

        if (!visited[currentNode])
        {
            cout << currentNode << " ";
            visited[currentNode] = true;
            for (int i = 0; i < numNodes; i++)
            {
                if (graph[currentNode][i] != 0 && !visited[i])
                {
                    queueNodes.push(i);
                }
            }
        }
    }
    cout << endl;
}

void IterativeDeepeningDFS(vector<vector<int>> &graph, int currentNode, int depth, vector<int> &visited)
{
    if (depth < 0)
        return;

    visited[currentNode] = 1;
    cout << currentNode << " ";

    for (int i = 0; i < graph.size(); i++)
    {
        if (graph[currentNode][i] && !visited[i])
        {
            IterativeDeepeningDFS(graph, i, depth - 1, visited);
        }
    }
}

void DepthLimitIDS(vector<vector<int>> &graph, int startNode)
{
    int maxDepth = 5;
    for (int i = 0; i < maxDepth; i++)
    {
        vector<int> visited(graph.size(), 0);
        cout << "Depth " << i << ": ";
        IterativeDeepeningDFS(graph, startNode, i, visited);
        cout << endl;
    }
}

void BeamSearch(vector<vector<int>> &graph, int startNode, int beamWidth)
{
    priority_queue<PII, vector<PII>, greater<PII>> priorityQueue;
    vector<bool> visited(graph.size(), false);
    priorityQueue.push({0, startNode});

    visited[startNode] = true;

    cout << "Beam Search: ";
    while (!priorityQueue.empty())
    {
        vector<PII> currentNodes;

        for (int i = 0; i < beamWidth && !priorityQueue.empty(); i++)
        {
            currentNodes.push_back(priorityQueue.top());
            priorityQueue.pop();
        }

        for (auto &p : currentNodes)
        {
            int currentNode = p.second;
            cout << currentNode << " ";

            for (int i = 0; i < graph.size(); i++)
            {
                if (graph[currentNode][i] != 0 && !visited[i])
                {
                    priorityQueue.push({graph[currentNode][i], i});
                    visited[i] = true;
                }
            }
        }
    }
    cout << endl;
}

void BestFirstSearch(const vector<vector<int>> &graph, int startNode)
{
    int numNodes = graph.size();
    vector<bool> visited(numNodes, false);
    priority_queue<PII, vector<PII>, greater<PII>> priorityQueue;

    priorityQueue.push({0, startNode});
    visited[startNode] = true;

    cout << "BestFS: ";
    while (!priorityQueue.empty())
    {
        int currentNode = priorityQueue.top().second;
        priorityQueue.pop();

        cout << currentNode << " ";

        for (int i = 0; i < numNodes; i++)
        {
            if (graph[currentNode][i] != 0 && !visited[i])
            {
                visited[i] = true;
                priorityQueue.push({graph[currentNode][i], i});
            }
        }
    }
    cout << endl;
}

void AStarSearch(vector<vector<int>> &graph, int startNode, vector<int> &heuristics)
{
    priority_queue<PII, vector<PII>, greater<PII>> priorityQueue;
    int numNodes = graph.size();
    vector<bool> visited(numNodes, false);

    priorityQueue.push({heuristics[startNode], startNode});
    visited[startNode] = true;

    cout << "A* Search: ";
    while (!priorityQueue.empty())
    {
        int currentNode = priorityQueue.top().second;
        priorityQueue.pop();
        cout << currentNode << " ";

        for (int i = 0; i < numNodes; i++)
        {
            if (graph[currentNode][i] != 0 && !visited[i])
            {
                int edgeCost = graph[currentNode][i];
                int totalCost = edgeCost + heuristics[i];
                priorityQueue.push({totalCost, i});
                visited[i] = true;
            }
        }
    }
    cout << endl;
}

int main()
{
    int numNodes = 10, startNode = 0;
    vector<vector<int>> graph = {
        {0, 6, 3, 1, 0, 0, 0, 0, 0, 0},
        {6, 0, 2, 6, 3, 4, 0, 0, 0, 0},
        {3, 2, 0, 0, 4, 5, 0, 0, 0, 0},
        {1, 6, 0, 0, 7, 8, 9, 0, 0, 0},
        {0, 3, 4, 7, 0, 6, 9, 9, 0, 0},
        {0, 4, 5, 8, 6, 0, 8, 9, 0, 0},
        {0, 0, 0, 9, 9, 8, 0, 11, 12, 14},
        {0, 0, 0, 0, 9, 9, 11, 0, 14, 15},
        {0, 0, 0, 0, 0, 0, 12, 14, 0, 0},
        {0, 0, 0, 0, 0, 0, 14, 15, 0, 0}};

    vector<int> heuristics = {15, 13, 13, 12, 10, 9, 7, 6, 5, 0};

    cout << "DFS:\n";
    DepthFirstSearch(graph, startNode);

    cout << "\nBFS:\n";
    BreadthFirstSearch(graph, startNode);

    cout << "\nIDS:\n";
    DepthLimitIDS(graph, startNode);

    cout << "\nBeam Search (Width=2):\n";
    BeamSearch(graph, startNode, 2);

    cout << "\nBestFS:\n";
    BestFirstSearch(graph, startNode);

    cout << "\nA* algorithm:\n";
    AStarSearch(graph, startNode, heuristics);
}

