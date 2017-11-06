#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
const int N = 1050;
vector<int> e[N];
int sg[N];

int SG(int u) {
	/*
	sg[u]>0则u是必胜点，sg[u]=0则是必败点
	sg[u]=mex(sg[v])，v是u的后继状态，mex是最小的不在集合中的数 
	对于不相干的多个局面总的胜负，若各个局面sg函数异或和为0则必败，否则必胜
	因为若 sg[u] = k，则 sg[u] 走一步可以到达 0 ~ k-1 的每一个sg值，而走到sg值为0就是必败点
	这和尼姆博弈是相同的，所以胜负判定也和尼姆博弈相同，异或和为0则必败
	（尼姆博弈：有n堆石子，每次可以从任意一堆取任意多个，先取完的胜） 
	唯一的不同点就是sg函数走一步可以变多，但只有必败的一方才会想变多，而必胜的一方只要再变回来就好了 
	*/
	if (~sg[u]) return sg[u];
	bool vis[N] = {0};
	for (int siz = e[u].size(), i = 0; i < siz; i++)
		vis[SG(e[u][i])] = true;  // 遍历后继状态 
	for (sg[u] = 0; vis[sg[u]]; sg[u]++);  // 在后继状态中求mex 
	return sg[u];
}

int main() {
	for (int n; scanf("%d", &n) == 1; ) {
		memset(sg, -1, sizeof(sg));
		for (int i = 0; i < n; i++)
			e[i].clear();
		for (int u = 0, siz; u < n; u++) {
			scanf("%d", &siz);
			if (!siz) sg[u] = 0;
			for (int v; siz--; e[u].push_back(v))
				scanf("%d", &v);
		}
		for (int m; scanf("%d", &m) == 1 && m; ) {
			int s = 0;
			for (int u; m--; s ^= SG(u))  // s保存异或和 
				scanf("%d", &u);
			printf(s ? "WIN\n" : "LOSE\n");
		}
	}
	return 0;
}

