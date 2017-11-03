#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
const int N = 1050, M = 1050;
int n, m;
vector<int> e[N];
int pre[N];
bool vis[N];

bool dfs(int u) {
	for (int siz = e[u].size(), i = 0; i < siz; i++) {
		int v = e[u][i];
		if (!vis[v]) {
			vis[v] = true;
			if (!pre[v] || dfs(pre[v])) {  // 是dfs(pre[v])而不是dfs(v) ，dfs的参数是左边的点 
				pre[v] = u;
				return true;
			}
		}
	}
	return false;
}

int Hungary() {  // O(nE) 
	int ret = 0;
	for (int i = 1; i <= n; i++) {
		memset(vis, 0, sizeof(vis));  // vis每次都要清零 
		ret += dfs(i);
	}
	return ret;
}

int main() {
	int ecnt;
	scanf("%d%d%d", &n, &m, &ecnt);
	for (int u, v; ecnt--; ) {
		scanf("%d%d", &u, &v);
		if (v <= m) e[u].push_back(v);  // 数据有坑 
	}
	printf("%d\n", Hungary());
	return 0;
}

