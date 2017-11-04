#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;
const int N = 10050;
int fa[N];

int find(int x) { return fa[x] == x ? x : (fa[x] = find(fa[x])); }  // 路径压缩 

void unionn(int x, int y) { fa[find(x)] = find(y); }

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)  // 写并查集记得初始化fa数组 
		fa[i] = i;
	for (int opt, x, y; m--; ) {
		scanf("%d%d%d", &opt, &x, &y);
		if (opt == 1) unionn(x, y);
		else puts(find(x) == find(y) ? "Y" : "N");
	}
    return 0;
}

