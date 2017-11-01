#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;
const int N = 500050, M = 500050;

struct Edge {
	int to, nxt;
	Edge(int _to = 0, int _nxt = -1): to(_to), nxt(_nxt) {}
}e[N<<1];

int ecnt, head[N];
int dfscnt, dfx[N<<1], dep[N<<1], first[N];
bool vis[N];
int f[N<<1][25];

void add(int u, int v) {
	e[ecnt] = Edge(v, head[u]); head[u] = ecnt++;
	e[ecnt] = Edge(u, head[v]); head[v] = ecnt++;
}

void dfs(int u, int curDep) {
	vis[u] = true;
	dfx[++dfscnt] = u;
	dep[dfscnt] = curDep;
	first[u] = dfscnt;
	for (int i = head[u]; ~i; i = e[i].nxt) {
		int v = e[i].to;
		if (!vis[v]) {
			// 每经过u点就要扔进dfs序 
			dfs(v, curDep+1);
			dfx[++dfscnt] = u;
			dep[dfscnt] = curDep;
		}
	}
}

void ST() {
	int n = dfscnt;
	for (int i = 1; i <= n; i++)
		f[i][0] = i;
	for (int j = 1; j <= log(n)/log(2); j++)
		for (int i = 1; i <= n-(1<<j)+1; i++) {
			int f1 = f[i][j-1], f2 = f[i+(1<<(j-1))][j-1];
			f[i][j] = dep[f1] < dep[f2] ? f1 : f2;  // 存的是位置，比较是比深度 
		}
}

int query(int a, int b) {
	int l = first[a], r = first[b];
	if (l > r) swap(l, r);
	int t = log(r-l) / log(2), f1 = f[l][t], f2 = f[r-(1<<t)+1][t];
	return dfx[dep[f1] < dep[f2] ? f1 : f2];  // f数组中保存的是LCA在dfs序中的位置，所以要返回dfx[f] 
}

int main() {
	memset(head, -1, sizeof(head));
	int n, m, root;
	scanf("%d%d%d", &n, &m, &root);
	for (int i = 1, u, v; i < n; i++) {
		scanf("%d%d", &u, &v);
		add(u, v);
	}
	dfs(root, 1); ST();
	for (int u, v; m--; ) {
		scanf("%d%d", &u, &v);
		printf("%d\n", query(u, v));
	}
    return 0;
}

