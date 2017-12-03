#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <utility>
#include <queue>
using namespace std;
const int N = 5050, M = 50050, INF = 0x3f3f3f3f;

struct Graph {
	struct Edge {
		int to, f, c, nxt;
		Edge(int _to=0, int _f=0, int _c=0, int _nxt=0): to(_to), f(_f), c(_c), nxt(_nxt) {}
	} e[M<<1];
	int head[N], top;
	
	Graph() { memset(head, -1, sizeof(head)); }
	void add1(int u, int v, int f, int c) { e[top] = Edge(v, f, c, head[u]); head[u] = top++; }
	void add(int u, int v, int f, int c) { add1(u, v, f, c); add1(v, u, 0, -c); }
};

struct Network {  // 最小费用最大流模板 
	Graph G;
	int s, t;
	int dis[N], pre[N];
	bool vis[N];
	
	bool SPFA() {  // SPFA找最小费用增广路 
		memset(vis, 0, sizeof(vis)); vis[s] = true;
		memset(dis, 0x3f, sizeof(dis)); dis[s] = 0;
		memset(pre, -1, sizeof(pre));
		queue<int> q; q.push(s);
		while (!q.empty()) {
			int u = q.front(); q.pop(); vis[u] = false;
			for (int i = G.head[u]; ~i; i = G.e[i].nxt) {
				int v = G.e[i].to;
				if (G.e[i].f && dis[u] + G.e[i].c < dis[v]) {
					dis[v] = dis[u] + G.e[i].c;
					pre[v] = i;
					if (!vis[v]) {
						vis[v] = true;
						q.push(v);
					}
				}
			}
		}
		return dis[t] < INF;
	}
	
	pair<int, int> MCMF(int _s, int _t) {  // 返回值first为流量，second为费用 
		s = _s; t = _t;
		int flow = 0, cost = 0;
		while (SPFA()) {
			int curFlow = INF;  // curFlow为当前最小费用增广路能增广的最大流量 
			for (int i = pre[t]; ~i; i = pre[G.e[i^1].to])
				curFlow = min(curFlow, G.e[i].f);
			flow += curFlow; cost += dis[t] * curFlow;
			for (int i = pre[t]; ~i; i = pre[G.e[i^1].to])
				G.e[i].f -= curFlow, G.e[i^1].f += curFlow;
		}
		return make_pair(flow, cost);
	}
} net;

int main() {
	ios::sync_with_stdio(false);
	int n, m, s, t; cin >> n >> m >> s >> t;
	for (int u, v, f, c; m--; net.G.add(u, v, f, c))
		cin >> u >> v >> f >> c;
	pair<int, int> ans = net.MCMF(s, t);
	cout << ans.first << ' ' << ans.second << endl;
	return 0;
}

