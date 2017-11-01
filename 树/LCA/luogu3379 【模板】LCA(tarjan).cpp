#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;
const int N = 500050, M = 500050;

struct Ques {
	int to, nxt;
	Ques(int _to = 0, int _nxt = -1): to(_to), nxt(_nxt) {}
}q[M<<1];

struct Edge {
	int to, nxt;
	Edge(int _to = 0, int _nxt = -1): to(_to), nxt(_nxt) {}
}e[N<<1];

int qcnt, qhead[N];
int ecnt, ehead[N];
int fa[N];
bool vis[N];
int ans[N];

void addQues(int u, int v) {
	q[qcnt] = Ques(v, qhead[u]); qhead[u] = qcnt++;
	q[qcnt] = Ques(u, qhead[v]); qhead[v] = qcnt++;
}

void addEdge(int u, int v) {
	e[ecnt] = Edge(v, ehead[u]); ehead[u] = ecnt++;
	e[ecnt] = Edge(u, ehead[v]); ehead[v] = ecnt++;
}

int find(int x) {
	if (fa[x] != x) fa[x] = find(fa[x]);
	return fa[x];
}

void unionn(int x, int y) {
	fa[find(x)] = find(y);
}

void tarjan(int u) {
	vis[u] = true;
	for (int i = ehead[u]; ~i; i = e[i].nxt) {
		int v = e[i].to;
		if (!vis[v]) {
			tarjan(v);
			unionn(v, u);  // 这里注意顺序，是把v链到u上，这样find(v)才能查到u 
		}
	}
	for (int i = qhead[u]; ~i; i = q[i].nxt) {
		int v = q[i].to;
		if (vis[v]) ans[i/2] = find(v);
	}
}

int main() {
	memset(qhead, -1, sizeof(qhead));
	memset(ehead, -1, sizeof(ehead));
	int n, m, root;
	scanf("%d%d%d", &n, &m, &root);
	for (int i = 1; i <= n; i++)
		fa[i] = i;
	for (int i = 1, u, v; i < n; i++) {
		scanf("%d%d", &u, &v);
		addEdge(u, v);
	}
	for (int i = 0, u, v; i < m; i++) {
		scanf("%d%d", &u, &v);
		addQues(u, v);
	}
	tarjan(root);
	for (int i = 0; i < m; i++)
		printf("%d\n", ans[i]);
    return 0;
}

