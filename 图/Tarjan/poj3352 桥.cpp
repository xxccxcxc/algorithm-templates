#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <vector>
#include <utility>
#include <stack>
using namespace std;
const int N = 1050;
vector<int> e[N];
int dfscnt, dfn[N], low[N], bcnt, kcnt, belong[N];
stack<int> st;
pair<int, int> bridge[N];

void tarjan(int u, int fa) {  // Tarjan求桥 
	low[u] = dfn[u] = ++dfscnt;
	st.push(u);  // 边双连通分量没有重复点，所以栈里存点，点双连通就存边 
	for (int siz = e[u].size(), i = 0; i < siz; i++) {
		int v = e[u][i];
		if (!dfn[v]) {
			tarjan(v, u);
			low[u] = min(low[u], low[v]);  // 记得更新low[u] 
			if (low[v] > dfn[u]) {  // 若v无法通过除(u,v)以外的边访问u和u的祖先，则(u,v)是桥 
				bridge[++bcnt] = make_pair(u, v);
				++kcnt;
				while (!st.empty()) {  // 把v子树上剩下的点都出栈，组成新的边双连通分量 
					int tmp = st.top(); st.pop();
					belong[tmp] = kcnt;
					if (tmp == v) break;
				}
			}
		}
		else if (v != fa) low[u] = min(low[u], dfn[v]);
	}
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for (int u, v; m--; e[u].push_back(v), e[v].push_back(u))
		scanf("%d%d", &u, &v);
	tarjan(1, 0);
	if (!st.empty()) {
		++kcnt;
		while (!st.empty()) {
			belong[st.top()] = kcnt;
			st.pop();
		}
	}
	int d[N] = {0};
	for (int i = 1; i <= bcnt; i++) {
		int u = bridge[i].first, v = bridge[i].second;
		++d[belong[u]]; ++d[belong[v]];  // 计算每个边双连通分量缩成一个结点后的的度 
	}
	int leaf = 0;
	for (int i = 1; i <= kcnt; i++)
		leaf += d[i] == 1;  // leaf是叶子结点数 
	printf("%d\n", (leaf + 1) >> 1);  // 一个结论：至少要加(leaf+1)/2条边才能使图没有桥（每次连接两个叶子） 
    return 0;
}

