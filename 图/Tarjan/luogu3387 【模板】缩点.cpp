#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <vector>
#include <stack>
using namespace std;
const int N = 10050, INF = 0x3f3f3f3f;
vector<int> e[N], e2[N];
int a[N], dfscnt, dfn[N], low[N], bcnt, belong[N], val[N], f[N];
bool vis[N];
stack<int> st;

void tarjan(int u) {  // 缩点（强连通分量） 
	low[u] = dfn[u] = ++dfscnt;
	vis[u] = true;
	st.push(u);
	for (int siz = e[u].size(), i = 0; i < siz; i++) {
		int v = e[u][i];
		if (!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
		}
		else if (vis[v]) low[u] = min(low[u], dfn[v]);  // 指向已经出栈的点的边对答案无影响 
	}
	if (low[u] == dfn[u]) {  // 讲不清楚，背下来就好 
		++bcnt;
		vis[u] = false;  // 点出栈时vis置0 
		while (!st.empty()) {
			int tmp = st.top(); st.pop();
			vis[tmp] = false;
			belong[tmp] = bcnt;
			val[bcnt] += a[tmp];
			if (tmp == u) break;
		}
	}
}

int dfs(int u) {
	if (f[u] < INF) return f[u];
	f[u] = 0;
	for (int siz = e2[u].size(), i = 0; i < siz; i++) {
		int v = e2[u][i];
		f[u] = max(f[u], dfs(v));
	}
	return f[u] += val[u];
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for (int u, v; m--; e[u].push_back(v))
		scanf("%d%d", &u, &v);
	for (int i = 1; i <= n; i++)
		if (!dfn[i]) tarjan(i);
	for (int i = 1; i <= n; i++)
		for (int u = belong[i], siz = e[i].size(), j = 0; j < siz; j++)
			e2[u].push_back(belong[e[i][j]]);  // 缩点完重新建边 
	memset(f, 0x3f, sizeof(f));
	int ans = 0;
	for (int i = 1; i <= bcnt; i++)
		ans = max(ans, dfs(i));
	printf("%d\n", ans);
    return 0;
}

