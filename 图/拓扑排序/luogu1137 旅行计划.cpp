#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;
const int N = 100050, M = 200050;
struct Edge {
	int to, nxt;
	Edge(int _to=0, int _nxt=-1): to(_to), nxt(_nxt) {}
}e[M];
int ecnt, head[N];

void add(int u, int v) {
	e[ecnt] = Edge(v, head[u]);
	head[u] = ecnt++;
}

int main() {  // 拓扑排序 + DAG上DP 
	/*
	对于一个有向无环图，可以用拓扑排序把点转成一个序列， 
	使得对于所有边(u, v)，u在序列中的位置在v之后，就可以按顺序dp
	*/ 
	memset(head, -1, sizeof(head));
	int n, m, in[N] = {0}, f[N] = {0};
	scanf("%d%d", &n, &m);
	for (int u, v; m--; add(u, v), ++in[v])
		scanf("%d%d", &u, &v);
	queue<int> q;
	for (int i = 1; i <= n; i++)
		if (!in[i]) f[i] = 1, q.push(i);  // 先把入度为0的点入队 
	while (!q.empty()) {
		int u = q.front(); q.pop();  // 取出u，扔进拓扑序里 
		for (int i = head[u]; ~i; i = e[i].nxt) {  // 把u点所有出边去掉 
			int v = e[i].to;
			f[v] = max(f[v], f[u] + 1);  // 可以边拓扑边dp 
			if (!--in[v]) q.push(v);  // 如果v没有入边就可以入队了 
		}
	}
	for (int i = 1; i <= n; i++)
		printf("%d\n", f[i]);
    return 0;
}

