#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;
const int N = 100050;
vector<int> e[N];
int dfscnt, dfn[N], low[N];  // low[u]表示u子树上的返祖边连接到的dfn最小的结点 
bool iscut[N];

void tarjan(int u, int fa) {  // Tarjan割点
	low[u] = dfn[u] = ++dfscnt;
	for (int siz = e[u].size(), i = 0, son = 0; i < siz; i++) {
		int v = e[u][i];
		if (!dfn[v]) {
			++son; tarjan(v, u);
			low[u] = min(low[u], low[v]);
			/*
			割点有两种情况，一种是自己是根，且子树个数大于1，则切掉这个点后子树间不连通
			另一种是存在一个子结点v，low[v]>=dfn[u]，说明v子树不能越过u访问u的祖先，则切掉u后图不连通 
			*/
			iscut[u] |= !fa && son > 1 || fa && low[v] >= dfn[u];
		}
		else if (v != fa) low[u] = min(low[u], dfn[v]);  // u有返祖边，更新low[u]（父边不算返祖边） 
	}
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for (int u, v; m--; e[u].push_back(v), e[v].push_back(u))
		scanf("%d%d", &u, &v);
	for (int i = 1; i <= n; i++)
		if (!dfn[i]) tarjan(i, 0);
	int cnt = 0;
	for (int i = 1; i <= n; i++)
		cnt += iscut[i];
	printf("%d\n", cnt);
	for (int i = 1; i <= n; i++)
		if (iscut[i]) printf("%d ", i);
	puts("");
    return 0;
}

