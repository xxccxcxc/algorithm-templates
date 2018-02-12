/*
luoguU19765 day2T2 逆序对(perm) 100pts

题意：定义相似区间为离散化后相同的区间
设P1,P2都是[1,n]的排列，F(P1,P2)为满足P1[l,r]与P2[l,r]相似，
且P1[l,r]逆序对数不超过m的(l,r)数目
求P1,P2取遍[1,n]的所有排列的F(P1,P2)之和

解法：
设g(i,j)为长度为i的序列，逆序对数目为j的方案数
则g(i,j)=g(i-1,j-k)，0<=k<=i-1，表示新增的逆序对数为k 
f(i,j)为长度为i的序列，逆序对数目不大于j的方案数
则f(i,j)为g(i,j)的前缀和
考虑如何求答案
首先考虑[l,r]区间
[l,r]在整个排列中的位置有(n-len+1)种
每个区间有哪几个数，方案数都为C(n,len)，合起来为C(n,len)^2 
区间几个数的大小关系有f(len,m)种
再考虑剩余区间，两个区间中每个数都可以任意取，方案数为((n-len)!)^2
ans(len)=(n-len+1)*f(len,m)*(C(n,len)*(n-len)!)^2
   =(n-len+1)*f(len,m)*(n!/len!)^2
*/
#include <bits/stdc++.h>
using namespace std;
const int N = 500, MOD = 1e9+7;

int f[N+50][N*N/2+50], fac[N+50], inv[N+50];

int qPow(int a, int k) {
	int ret = 1, tmp = a;
	for (; k; k >>= 1, tmp = 1LL * tmp * tmp % MOD)
		if (k & 1) ret = 1LL * ret * tmp % MOD;
	return ret;
}

void Pret() {
	f[1][0] = f[1][1] = 1;
	for (int i = 2; i <= N; i++) {
		int k = i*(i-1)/2;  // 逆序对总数 
		for (int j = 0; j <= k; j++) {
			f[i][j] = f[i-1][j];
			if (j - i >= 0) f[i][j] = (f[i][j] - f[i-1][j-i] + MOD) % MOD;
			// g[i][j]=f[i-1][(j-i+1)~j]，则f[i][j]=f[i-1][j]-f[i-1][j-i] 
			if (j > 0) f[i][j] = (f[i][j] + f[i][j-1]) % MOD;  // 因为是前缀和，加上上一个f 
		}
		int k1 = (i+1)*i/2;
		for (int j = k + 1; j <= k1; j++)
			f[i][j] = f[i][j-1];
		// 因为f[i+1][j]会用到f[i][j]，所以第i层的j要处理到i+1层的范围 
	}
	fac[0] = fac[1] = inv[0] = inv[1] = 1;
	for (int i = 2; i <= N; i++) {
		fac[i] = 1LL * fac[i-1] * i % MOD;
		inv[i] = qPow(fac[i], MOD - 2);
	}
}

int main() {
	ios::sync_with_stdio(false);
	Pret();
	int T; cin >> T;
	for (int n, m; T--; ) {
		cin >> n >> m;
		int ans = 0;
		for (int len = 1; len <= n; len++) {  // 枚举区间长度len 
			int k = min(m, len*(len-1)/2);  // m最多只要到逆序对总数 
			int tmp = 1LL * fac[n] * inv[len] % MOD;
			ans = (ans + 1LL * (n-len+1) * f[len][k] % MOD * tmp % MOD * tmp % MOD) % MOD;
			// 见上面公式，记得取模 
		}
		cout << ans << endl;
	}
    return 0;
}

