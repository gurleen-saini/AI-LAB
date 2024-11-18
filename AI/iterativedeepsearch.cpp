#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <vector>
using namespace std;
bool dfs(map<int, vector<int>> m, int start, int ele, int depth)
{
  bool flag = false;
  vector<int> result;
  set<int> visited;
  stack<pair<int, int>> s;
  s.push({start, 0});

  while (!s.empty())
  {
    int vertex = s.top().first;
    int current_depth = s.top().second;
    s.pop();

    if (visited.find(vertex) == visited.end())
    {
      visited.insert(vertex);
      if (current_depth <= depth)
      {
        result.push_back(vertex);
      }
      else
      {
        continue;
      }

      for (auto it = m[vertex].rbegin(); it != m[vertex].rend(); ++it)
      {
        if (visited.find(*it) == visited.end())
        {
          s.push({*it, current_depth + 1});
        }
      }
    }
  }

  for (int i = 0; i < result.size(); i++)
  {
    if (result[i] == ele)
      flag = true;
    cout << result[i] << " ";
  }
  cout << endl;
  return flag;
}

int main()
{
  int ele;
  int n;
  map<int, vector<int>> m;
  cout << "Enter number of nodes = ";
  cin >> n;
  for (int i = 0; i < n - 1; i++)
  {
    int n1, n2;
    cin >> n1 >> n2;
    m[n1].push_back(n2);
    m[n2].push_back(n1);
  }
  cout << "Enter element to search = ";
  cin >> ele;
  int depth = 4;
  for (int i = 1; i <= depth; i++)
  {
    bool check = false;
    check = dfs(m, 1, ele, i);
    if (check)
      cout << "Element is present upto " << i << " level" << endl;
    else
      cout << "Element is not present upto " << i << " level" << endl;
  }
}