#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;
const int N = 500050, M = 500050, D = 20;

struct Edge {
	int to, nxt;
	Edge(int _to = 0, int _nxt = -1): to(_to), nxt(_nxt) {}
}e[N<<1];

int ecnt, head[N];
bool vis[N];
int dep[N], anc[N][D+5];  //anc[i][j]表示i向上走第2^j个点 

void add(int u, int v) {
	e[ecnt] = Edge(v, head[u]); head[u] = ecnt++;
	e[ecnt] = Edge(u, head[v]); head[v] = ecnt++;
}

void dfs(int u) {  // 倍增LCA，自带大常数 
	vis[u] = true;
	for (int i = 1, dis = 1; i <= D; i++, dis <<= 1) {
		// i要从1开始，因为anc[u][0]在进入函数前就赋值成u的父亲，而且i=0的话anc[u][i-1]会出错 
		if (dis > dep[u]) break;
		anc[u][i] = anc[anc[u][i-1]][i-1];
	}
	for (int i = head[u]; ~i; i = e[i].nxt) {
		int v = e[i].to;
		if (!vis[v]) {
			dep[v] = dep[u] + 1;
			anc[v][0] = u;
			dfs(v);
		}
	}
}

int query(int u, int v) {
	if (dep[u] > dep[v]) swap(u, v);
	int td = dep[v] - dep[u];
	for (int i = 0, bin = 1; i <= D; i++, bin <<= 1)
		if (td & bin) v = anc[v][i];
	if (u == v) return u;
	for (int i = D; i >= 0; i--)
		if (anc[u][i] != anc[v][i])
			u = anc[u][i], v = anc[v][i];
	return anc[u][0];
}

int main() {
	memset(head, -1, sizeof(head));
	int n, m, root;
	scanf("%d%d%d", &n, &m, &root);
	for (int i = 1, u, v; i < n; i++) {
		scanf("%d%d", &u, &v);
		add(u, v);
	}
	dfs(root);
	for (int u, v; m--; ) {
		scanf("%d%d", &u, &v);
		printf("%d\n", query(u, v));
	}
    return 0;
}

