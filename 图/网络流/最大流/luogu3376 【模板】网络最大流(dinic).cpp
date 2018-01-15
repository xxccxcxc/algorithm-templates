#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int N = 10050, M = 100050, INF = 0x3f3f3f3f;

struct Graph {
	struct Edge {
		int to, w, nxt;
		Edge() {}
		Edge(int _to, int _w, int _nxt): to(_to), w(_w), nxt(_nxt) {}
	} e[M<<1];
	int etop, head[N];
	
	Graph() { etop = 0; memset(head, -1, sizeof(head)); }
	void Add1(int u, int v, int f) { e[etop] = Edge(v, f, head[u]); head[u] = etop++; }
};

struct Network {
	Graph G;
	int s, t;
	int dis[N];
	
	void Add(int u, int v, int w) {
		G.Add1(u, v, w);
		G.Add1(v, u, 0);
	}
	
	bool Bfs() {
		memset(dis, 0, sizeof(dis)); dis[s] = 1;
		queue<int> q; q.push(s);
		while (!q.empty() && !dis[t]) {
			int u = q.front(); q.pop();
			for (int i = G.head[u]; ~i; i = G.e[i].nxt) {
				int v = G.e[i].to;
				if (G.e[i].w && !dis[v]) {
					dis[v] = dis[u] + 1;
					q.push(v);
				}
			}
		}
		return dis[t];
	}
	
	int Dfs(int u, int curFlow) {
		if (u == t) return curFlow;
		if (dis[u] >= dis[t]) return 0;
		for (int i = G.head[u]; ~i; i = G.e[i].nxt) {
			int v = G.e[i].to, flow;
			if (G.e[i].w && dis[v] == dis[u] + 1 && (flow = Dfs(v, min(curFlow, G.e[i].w)))) {
				G.e[i].w -= flow;
				G.e[i^1].w += flow;
				return flow;
			}
		}
		dis[u] = -1;
		return 0;
	}
	
	int Dinic(int _s, int _t) {
		s = _s; t = _t;
		int maxFlow = 0, flow;
		while (Bfs())
			while (flow = Dfs(s, INF))
				maxFlow += flow;
		return maxFlow;
	}
} net;

int main() {
	ios::sync_with_stdio(false);
	int n, m, s, t; cin >> n >> m >> s >> t;
	for (int u, v, w; m--; net.Add(u, v, w))
		cin >> u >> v >> w;
	cout << net.Dinic(s, t) << endl;
	return 0;
}

