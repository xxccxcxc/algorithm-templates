/*
luoguU20012 day5T3 环(tour) 100pts

题意：一张n个点的图，求长度小于m的环个数，n<=100，m<=1e6 

解法：求环的个数可以用floyd的思想，设邻接矩阵为a
则a+a^2+...+a^(m-1)这个矩阵的sigma(a[i][i])即为答案
用类似快速幂的方法求，最后要扣掉a^0的答案（即为n） 
*/
#include <bits/stdc++.h>
using namespace std;
const int N = 105;

int n, mod; 

struct Matrix {
	int a[N][N];
	Matrix() { memset(a, 0, sizeof(a)); }
	void Init() {
		for (int i = 1; i <= n; i++)
			a[i][i] = 1;
	}
	Matrix operator * (const Matrix &t) const {
		Matrix ret;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				for (int k = 1; k <= n; k++)
					ret.a[i][j] = (ret.a[i][j] + 1LL * a[i][k] * t.a[k][j]) % mod;
		return ret;
	}
	Matrix operator + (const Matrix &t) const {
		Matrix ret;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				ret.a[i][j] = (a[i][j] + t.a[i][j]) % mod;
		return ret;
	}
};

Matrix Solve(const Matrix &a, int k) {
	Matrix tmp, ret, ta = a;
	tmp.Init(); ret.Init();
	for (; k; k >>= 1) {
		if (k & 1) ret = ret * ta + tmp;
		tmp = tmp * ta + tmp;  // tmp=1+a+a^2+...+a^(2^p)
		ta = ta * ta;  // ta=a^(2^p)
	}
	return ret;
}

int main() {
	scanf("%d", &n);
	char r[N]; Matrix a;
	for (int i = 1; i <= n; i++) {
		scanf("%s", r);
		for (int j = 1; j <= n; j++)
			a.a[i][j] = r[j-1] == 'Y';
	}
	int m; scanf("%d%d", &m, &mod);
	Matrix res = Solve(a, m-1);
	int ans = 0;
	for (int i = 1; i <= n; i++)
		ans = (ans + res.a[i][i]) % mod;
	printf("%d\n", (ans + mod - n) % mod);  // 扣掉a^0 
    return 0;
}

