#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<climits>
using namespace std;
class Graph {
private:
	vector<vector<int>> adjMatrix;
public:
	int V;
	Graph(int vertices) :V(vertices) {
		adjMatrix.resize(V, vector<int>(V, 0));
	}
	~Graph() {

	}
	void addEdge(int u, int v) {
		adjMatrix[u][v] = 1;
		adjMatrix[v][u] = 1;
	}
	void addWeightEdge(int u, int v, int weight) {
		adjMatrix[u][v] = weight;
		adjMatrix[v][u] = weight;
	}
	void DFS1(int v, vector<bool>& visited) {
		visited[v] = true;
		cout << v << " ";
		for (int i = 0; i < V; i++) {
			if (adjMatrix[v][i] == 1 && !visited[i]) {
				DFS1(i, visited);
			}
		}
	}
	void DFS2(int start) {
		vector<bool> visited(V, false);
		stack<int> s;
		s.push(start);
		visited[start] = true;
		while (!s.empty()) {
			int v = s.top();
			s.pop();
			cout << v << " ";
			for (int i = 0; i < V; i++) {
				if (adjMatrix[v][i] == 1 && !visited[i]) {
					visited[i] = true;
					s.push(i);
				}
			}
		}
		cout << endl;
	}
	void BFS(int start) {
		vector<bool> visited(V, false);
		queue<int> q;
		q.push(start);
		visited[start] = true;
		while (!q.empty()) {
			int v = q.front();
			q.pop();
			cout << v << " ";
			for (int i = 0; i < V; i++) {
				if (adjMatrix[v][i] == 1 && !visited[i]) {
					visited[i] = true;
					q.push(i);
				}
			}
		}
		cout << endl;
	}
	bool isConnected() {
		vector<bool> visited(V, false);
		DFS1(0,visited);
		for (bool v: visited) {
			if (!v)return false;

		}
		return true;

	}
	void printAdjMatrix() {
		for (int i = 0; i < V; i++) {
			for (int j = 0; j < V; j++) {
				cout << adjMatrix[i][j] << " ";
			}
			cout << endl;
		}
	}
};
int main() {
	Graph g(5);
	g.addEdge(0, 1);
	g.addEdge(0, 4);
	g.addEdge(1, 2);
	g.addEdge(1, 3);
	g.addEdge(1, 4);
	g.addEdge(2, 3);
	g.addEdge(3, 4);
	g.printAdjMatrix();
	vector<bool> visited(g.V, false); 
	g.DFS1(0, visited);
	cout << endl;
	g.DFS2(0);
	g.BFS(0);
	cout << "Is the graph connected? " << (g.isConnected() ? "Yes" : "No") << endl;
}