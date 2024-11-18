#include <iostream>
#include <vector>
#include <queue>
using namespace std;
void bfs(vector<vector<int>> &adj, int start, int width)
{
  queue<vector<int>> q;
  q.push({start});
  vector<int> beam_order;
  vector<int> visited(adj.size(), 0);
  visited[start] = 1;
  beam_order.push_back(start);

  while (!q.empty())
  {
    int level_size = q.size();
    int ct = 0;
    vector<vector<int>> next_level;
    for (int i = 0; i < level_size; i++)
    {
      vector<int> path = q.front();
      int node = path.back();
      q.pop();
      for (int j = 0; j < adj[node].size(); j++)
      {
        if (adj[node][j] && !visited[j])
        {
          vector<int> new_path = path;
          new_path.push_back(j);
          next_level.push_back(new_path);
          visited[j] = 1;
          ct++;
          if (ct == 2)
            break;
        }
      }
      if (ct == 2)
        break;
    }
    int next_level_size = min((int)next_level.size(), width);
    for (int i = 0; i < next_level_size; i++)
    {
      q.push(next_level[i]);
      beam_order.push_back(next_level[i].back());
    }
  }
  cout << "Beam Search Order with width " << width << ": ";
  for (int node : beam_order)
  {
    cout << node << " ";
  }
  cout << endl;
}
int main()
{
  int n;
  cout << "Enter the number of nodes: ";
  cin >> n;
  vector<vector<int>> adj(n, vector<int>(n));
  cout << "Enter the adjacency matrix:" << endl;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      cin >> adj[i][j];
    }
  }
  int start;
  cout << "Enter the starting node: ";
  cin >> start;
  for (int width = 1; width <= 3; width++)
  {
    cout << "Beam Search with Width = " << width << endl;
    bfs(adj, start, width);
    cout << endl;
  }
  return 0;
}
