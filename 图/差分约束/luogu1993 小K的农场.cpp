#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;
const int N = 10050, M = 10050;

struct Edge {
	int to, w, nxt;
	Edge(int _to=0, int _w=0, int _nxt=-1): to(_to), w(_w), nxt(_nxt) {}
}e[M*3];
int ecnt, head[N];
int dis[N];
bool vis[N];

void add(int u, int v, int w) {  // 不要习惯性加双向边 
	e[ecnt] = Edge(v, w, head[u]);
	head[u] = ecnt++;
}

bool spfa(int u) {  // spfa求负环模板 
	vis[u] = true;
	for (int i = head[u]; ~i; i = e[i].nxt) {
		int v = e[i].to;
		if (dis[u] + e[i].w < dis[v]) {
			dis[v] = dis[u] + e[i].w;
			if (vis[v] || spfa(v)) return true;
		}
	}
	vis[u] = false;
	return false;
}

int main() {  // 差分约束：add(u, v, w)意义为dis[v] - dis[u] <= w(u, v) 
	memset(head, -1, sizeof(head));
	int n, m;
	scanf("%d%d", &n, &m);
	for (int opt, u, v, w; m--; ) {
		scanf("%d%d%d", &opt, &u, &v);
		if (opt <= 2) {
			scanf("%d", &w);
			if (opt == 1) add(u, v, -w);  // dis[u] - dis[v] >= w 转成 dis[v] - dis[u] <= -w 
			else add(v, u, w);  // dis[u] - dis[v] <= w
		}
		else add(u, v, 0), add(v, u, 0);  // dis[u] - dis[v] <= 0 && dis[v] - dis[u] <= 0
	}
	for (int i = 1; i <= n; i++) add(0, i, 0);  // 添加虚拟起点0，方便dfs，没什么实际意义 
	memset(dis, 0x3f, sizeof(dis)); dis[0] = 0;
	printf(spfa(0) ? "No\n" : "Yes\n");  // 若有负环则不存在合法解 
    return 0;
}
//扩展：若要求两个点差值的最大值，把所有不等式化为<=建边然后求最短路，若求最小值化为>=求最长路 

