#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;
const int N = 1050;
int n, ma[N][N];
vector<int> ans;

void dfs(int u) {
	for (int v = 1; v <= n; v++)
		if (ma[u][v]) {
			--ma[u][v]; --ma[v][u];
			dfs(v);
		}
	/*
	在退栈的时候记录答案
	因为第一次退栈肯定是因为走到死路了
	而欧拉路只有起点和终点是死路
	所以把第一次退栈的点作为终点进队
	如果入栈的时候记录答案，走到终点时就会发现有些点还没走过，所以是错误的 
	*/ 
	ans.push_back(u);
}

int main() {  // 欧拉路模板 
	int m, d[N] = {0};
	scanf("%d", &m);
	for (int u, v; m--; ) {
		scanf("%d%d", &u, &v);
		++ma[u][v]; ++ma[v][u];
		++d[u]; ++d[v];  // 计算每个结点的度 
		n = max(n, max(u, v));
	}
	int st = 1;
	for (int i = 1; i <= n; i++)
		if (d[i] & 1) { st = i; break; }  // 找度为奇数的点开始dfs，注意如果每个点的度都为偶数就随便找个点
	dfs(st);
	for (int siz = ans.size(), i = siz - 1; ~i; i--)  // ans是倒序存储，要反着输出 
		printf("%d\n", ans[i]);
    return 0;
}

