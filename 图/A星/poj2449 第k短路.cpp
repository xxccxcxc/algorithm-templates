#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int N = 1050, M = 100050, INF = 0x3f3f3f3f;

struct Edge {
	int to, w, nxt;
	Edge(int _to=0, int _w=0, int _nxt=-1): to(_to), w(_w), nxt(_nxt) {}
}e[M], e2[M];

int ecnt, head[N], e2cnt, head2[N];
int dis[N];

struct Node {
	int u, g;
	Node(int _u=0, int _g=0): u(_u), g(_g) {}
	bool operator<(const Node &t) const { return g + dis[u] > t.g + dis[t.u]; }
	// 这题的估价函数h是用SPFA预处理的从终点到该点的实际距离，是精准的，所以既能找到最优解，速度又快 
};

void add(int u, int v, int w) {
	e[ecnt] = Edge(v, w, head[u]); head[u] = ecnt++;
	e2[e2cnt] = Edge(u, w, head2[v]); head2[v] = e2cnt++;
}

void clear() {
	ecnt = e2cnt = 0;
	memset(head, -1, sizeof(head));
	memset(head2, -1, sizeof(head2));
}

void spfa(int s) {
	memset(dis, 0x3f, sizeof(dis)); dis[s] = 0;
	queue<int> q; q.push(s);
	int vis[N] = {0}; vis[s] = true;
	while (!q.empty()) {
		int u = q.front(); q.pop(); vis[u] = false;
		for (int i = head2[u]; ~i; i = e2[i].nxt) {
			int v = e2[i].to;
			if (dis[u] + e2[i].w < dis[v]) {
				dis[v] = dis[u] + e2[i].w;
				if (!vis[v]) {
					vis[v] = true;
					q.push(v);
				}
			}
		}
	}
}

int Astar(int s, int t, int k) {
	priority_queue<Node> q; q.push(Node(s, 0));  // 用优先队列，保证估价优的先做
	while (!q.empty()) {
		int u = q.top().u, g = q.top().g; q.pop();
		if (u == t) --k;
		if (!k) return g;
		for (int i = head[u]; ~i; i = e[i].nxt)
			q.push(Node(e[i].to, g + e[i].w));
	}
	return -1;
}

int main() {
	int n, m;
	while (scanf("%d%d", &n, &m) == 2) {
		clear();
		for (int u, v, w; m--; add(u, v, w))
			scanf("%d%d%d", &u, &v, &w);
		int s, t, k; scanf("%d%d%d", &s, &t, &k);
		spfa(t);  // 反向spfa预处理估价
		if (dis[s] == INF) { puts("-1"); continue; }
		k += s == t;
		printf("%d\n", Astar(s, t, k));
	}
	return 0;
}
