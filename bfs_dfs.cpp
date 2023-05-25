#include <iostream>
#include <stack>
#include <vector>
#include <omp.h>

using namespace std;

// Function to perform parallel DFS
void dfs_parallel(vector<vector<int>>& graph, vector<bool>& visited, int start_node) {
    stack<int> s;
    s.push(start_node);

    while (!s.empty()) {
        int current_node = s.top();
        s.pop();

        if (!visited[current_node]) {
            #pragma omp critical
            {
                if (!visited[current_node]) {
                    visited[current_node] = true;
                    cout << "Node " << current_node << " visited" << endl;
                }
            }

            #pragma omp parallel for
            for (size_t i = 0; i < graph[current_node].size(); ++i) {
                int neighbor_id = graph[current_node][i];
                s.push(neighbor_id);
            }
        }
    }
}

int main() {
    // Create the graph
    vector<vector<int>> graph(10);
    graph[0] = {1, 2};
    graph[1] = {0, 2, 3};
    graph[2] = {0, 1, 4};
    graph[3] = {1};
    graph[4] = {2};

    // Create a vector to track visited nodes
    vector<bool> visited(graph.size(), false);

    // Perform parallel DFS
    dfs_parallel(graph, visited, 0);

    return 0;
}

//////

#include <iostream>
#include <queue>
#include <vector>
#include <omp.h>

using namespace std;

// Function to perform parallel BFS
void bfs_parallel(vector<vector<int>>& graph, vector<bool>& visited, int start_node) {
    queue<int> q;
    visited[start_node] = true;
    q.push(start_node);

    while (!q.empty()) {
        int current_node = q.front();
        q.pop();

        #pragma omp parallel for
        for (size_t i = 0; i < graph[current_node].size(); ++i) {
            int neighbor_id = graph[current_node][i];
            if (!visited[neighbor_id]) {
                #pragma omp critical
                {
                    if (!visited[neighbor_id]) {
                        visited[neighbor_id] = true;
                        q.push(neighbor_id);
                    }
                }
            }
        }
    }
}

int main() {
    // Create the graph
    vector<vector<int>> graph(10);
    graph[0] = {1, 2};
    graph[1] = {0, 2, 3};
    graph[2] = {0, 1, 4};
    graph[3] = {1};
    graph[4] = {2};

    // Create a vector to track visited nodes
    vector<bool> visited(graph.size(), false);

    // Perform parallel BFS
    bfs_parallel(graph, visited, 0);

    // Output the visited nodes
    for (size_t i = 0; i < visited.size(); ++i) {
        if (visited[i]) {
            cout << "Node " << i << " visited" << endl;
        }
    }

    return 0;
}