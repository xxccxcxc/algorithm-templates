/*
luoguU19868 day3T2 二分图(match) 100pts

题意：给定一个二分图，求满足[存在一个匹配覆盖S中所有点]且[点权和不超过t]的子集S个数 

解法：首先有一个hall定理
hall定理：若对于X部的所有子集W，设|W|=k，都满足与W连通的Y部结点个数>=k，则存在覆盖X的匹配
一个结论：若对于左边的一个子集X和右边的一个子集Y，分别满足hall定理，则它们的并符合题意
证明方法：把覆盖X的匹配转成从左到右的有向图，反之亦然，就会形成若干个环和路径
每个环和路径都交替选边，即符合题意（易证路径最后一个点一定不在选出来的点中） 
用子集DP求一个集合是否满足hall，左右都求一遍，然后把所有合法状态按点权排序
最后两把指针扫一下即可 
*/ 
#include <bits/stdc++.h>
using namespace std;
const int N = 22, S = (1 << N) + 50;
int n, m, mx, val[N];
bool e[N][N];
int bits[S], w[S], c[S];
bool hall[S];
int a[S], atop, b[S], btop;

int Lb(int x) { return x & -x; }

void Work(int *q, int &top) {
	for (int i = 0; i < n; i++) {
		w[1<<i] = val[i];  // w[i]为i状态的点权和 
		c[1<<i] = 0;  // c[i]为i状态的连边情况 
		for (int j = 0; j < m; j++)
			if (e[i][j]) c[1<<i] |= 1<<j;
	}
	hall[0] = true; q[top=1] = 0;
	for (int s = 1; s < 1 << n; s++) {
		w[s] = w[Lb(s)] + w[s^Lb(s)];
		c[s] = c[Lb(s)] | c[s^Lb(s)];
		hall[s] = bits[s] <= bits[c[s]];  // hall[i]为i状态是否满足hall定理 
		for (int i = 0; i < n && hall[s]; i++)
			if (s & 1<<i) hall[s] &= hall[s ^ 1<<i];  // 转移都从当前状态去掉一个1转移 
		if (hall[s]) q[++top] = w[s];
	}
	sort(q+1, q+top+1);
}

int main() {
	scanf("%d%d", &n, &m);
	char r[N];
	for (int i = 0; i < n; i++) {
		scanf("%s", r);
		for (int j = 0; j < m; j++)
			e[i][j] = r[j] - '0';
	}
	mx = max(n, m);
	for (int i = 1; i <= 1 << mx; i++)
		bits[i] = bits[i>>1] + (i & 1);  // bits[i]为i状态1的个数 
	for (int i = 0; i < n; i++)
		scanf("%d", &val[i]);
	Work(a, atop);  // 做一遍X部 
	for (int i = 0; i < m; i++)
		scanf("%d", &val[i]);
	swap(n, m);  // n,m调换 
	for (int i = 0; i < mx; i++)
		for (int j = 0; j < i; j++)
			swap(e[i][j], e[j][i]);  // 把边反向 
	Work(b, btop);  // 再做一遍Y部 
	int tar; scanf("%d", &tar);
	long long ans = 0;
	for (int i = 1, j = btop+1; i <= atop && j >= 1; i++) {
		// 两把指针快速求a[i]+b[j]>=t的最小b[j]，因为j是单调不增的 
		while (j > 1 && a[i] + b[j-1] >= tar) j--;
		ans += btop-j+1;
	}
	cout << ans << endl;
    return 0;
}

