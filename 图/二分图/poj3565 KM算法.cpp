#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
const int N = 105, D = 100000, INF = 0x3f3f3f3f;
int n, pre[N];
double a[N][N], dx[N], dy[N], slack[N];
bool px[N], py[N];

bool dfs(int u) {
	px[u] = true;
	for (int v = 1; v <= n; v++)
		if (!py[v]) {
			double t = dx[u] + dy[v] - a[u][v];
			if (!t) {  // v 在相等子图中 
				py[v] = true;
				if (!pre[v] || dfs(pre[v])) {  // 匈牙利算法 
					pre[v] = u;
					return true;
				}
			}
			else slack[v] = min(slack[v], t);  // v in T'，则更新 slack[v] 
		}
	return false;
}

void km() {
	/*
	km算法：求二分图最大权匹配，即边权和最大的完美匹配
	算法对每个点构造了一个可行顶标dx和dy，而且保证 dx[u] + dy[v] >= w(u,v)  
	定义相等子图为所有点和满足 dx[u] + dy[v] = w(u,v) 的所有边
	易证相等子图的完美匹配为最大权匹配，则要想办法构造可行顶标使相等子图存在完美匹配
	设dfs到的点集为 S 和 T ，没dfs到的为 S' 和 T'
	则 S -> T' 无边， S' -> T 无匹配边
	这时候需要改变 S 的顶标，使 S -> T' 有新边进入
	所以让 dx[S] -= a, dy[T] += a (a = min(dx[u] + dy[v] - w(u, v)), u in S, v in T')
	若 a 比这个值小则无新边进入，比这个值大则顶标不合法
	每个点 v in T' 的 min(dx[u] + dy[v] - w(u, v), u in S) ，用slack数组来维护 
	复杂度 O(n3) 
	*/
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			dx[i] = max(dx[i], a[i][j]);  // 随便构造一个初始可行顶标，dx[u]=max(w(u, v)), dy[u]=0 
	for (int i = 1; i <= n; i++) {  // 每个点找一条增广路 
		for (int j = 1; j <= n; j++)
			slack[j] = INF;
		while (true) {
			memset(px, 0, sizeof(px));
			memset(py, 0, sizeof(py));
			if (dfs(i)) break;  // 找到增广路就退出 
			double t = INF;
			for (int j = 1; j <= n; j++)
				if (!py[j]) t = min(t, slack[j]);  // 在 T' 中找一个最小的slack值来更新 
			for (int j = 1; j <= n; j++) {
				if (px[j]) dx[j] -= t;
				if (py[j]) dy[j] += t;
				else slack[j] -= t;  // S 中每个点的顶标都 +t ，则 T' 中的 slack 对应要减 t 
			}
		}
	}
}

int main() {
	int x[N<<1], y[N<<1];
	cin >> n;
	for (int i = 1; i <= 2 * n; i++)
		cin >> x[i] >> y[i];
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			int xx = x[i] - x[j+n], yy = y[i] - y[j+n];
			a[i][j] = D - sqrt(xx * xx + yy * yy);
		}
	km();
	int ans[N];
	for (int i = 1; i <= n; i++)
		ans[pre[i]] = i;
	for (int i = 1; i <= n; i++)
		cout << ans[i] << endl;
	return 0;
}

