#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;
const int N = 10050, D = 10000050;

struct Edge {
	int to, w, nxt;
	Edge(int _to=0, int _w=0, int _nxt=-1): to(_to), w(_w), nxt(_nxt) {}
}e[N<<1];
int ecnt, head[N];
int siz[N], mx[N], dtop, dis[N], dcnt[D];
bool vis[N];

void add(int u, int v, int w) {
	e[ecnt] = Edge(v, w, head[u]); head[u] = ecnt++;
	e[ecnt] = Edge(u, w, head[v]); head[v] = ecnt++;
}

/*
getroot()：找分治树根
fa是getroot访问路径上的u的前驱结点，调用时值必为0（因为getroot访问路径为空） 
n是需要找树根的子树的大小 
*/
int getroot(int u, int fa, int n) {
	siz[u] = 1; mx[u] = 0;
	int ret = 0;
	for (int i = head[u]; ~i; i = e[i].nxt) {
		int v = e[i].to;
		if (!vis[v] && v != fa) {  // v!=fa防止走回头路，!vis[v]防止走到需要求根的范围外的结点 
			int tmp = getroot(v, u, n);
			siz[u] += siz[v];
			mx[u] = max(mx[u], siz[v]);
			if (!ret || mx[tmp] < mx[ret])
				ret = tmp;
		}
	}
	mx[u] = max(mx[u], n - siz[u]);  // 把u拎起来，还有一棵以fa为根的子树，大小是n-siz[u] 
	if (!ret || mx[u] < mx[ret]) ret = u;
	return ret;
}

void getdis(int u, int fa, int curdis) {
	dis[dtop++] = curdis;
	for (int i = head[u]; ~i; i = e[i].nxt) {
		int v = e[i].to;
		if (!vis[v] && v != fa)
			getdis(v, u, curdis + e[i].w);
	}
}

void work(int u, int t, int add) {
	dtop = 0;
	getdis(u, 0, 0);
	for (int i = 0; i < dtop; i++)
		for (int j = i+1; j < dtop; j++)
			if (dis[i] + dis[j] + t < D)
				dcnt[dis[i]+dis[j]+t] += add;
}

void dfs(int u, int n) {
	work(u, 0, 1);  // 答案加上所有路径 
	vis[u] = true;
	for (int i = head[u]; ~i; i = e[i].nxt) {
		int v = e[i].to;
		if (!vis[v]) {
			work(v, e[i].w << 1, -1);  // 答案减去不过根路径，剩下的就是过根路径 
			// 现在过根u的路径已经统计完了，接下来递归统计过其他点的路径 
			/*
			此时计算v子树的大小vsiz， 
			由于siz是以点1为根计算的，有可能计算的时候v是u的父亲，
			则siz[v]就会大于siz[u]，此时正确的vsiz是n-siz[u] 
			*/
			int vsiz = siz[v] <= siz[u] ? siz[v] : n - siz[u];
			dfs(getroot(v, 0, vsiz), vsiz);  // 注意这里dfs的根不是v，要重新getroot 
		}
	}
}

// 题意：询问树上是否存在距离为K的点对，多组询问
// 复杂度O(n2)，因为这题询问太多，就把所有可能的距离都求出来了，不过对于一次询问点分治可以达到O(nlogn)
int main() {
	memset(head, -1, sizeof(head));
	int n, m;
	scanf("%d%d", &n, &m);
	for (int u, v, w, i = 1; i < n; i++) {
		scanf("%d%d%d", &u, &v, &w);
		add(u, v, w);
	}
	int root = getroot(1, 0, 0);
	dfs(root, n);
	for (int d; m--; ) {
		scanf("%d", &d);
		printf(dcnt[d] ? "AYE\n" : "NAY\n");
	}
    return 0;
}

