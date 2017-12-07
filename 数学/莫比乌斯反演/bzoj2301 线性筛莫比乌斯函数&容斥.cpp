#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;
const int N = 50000;
bool vis[N+50];
int miu[N+50], sum[N+50];
int prime[N+50], pcnt;

void calcMiu() {  // miu是积性函数，可以线性筛
	miu[1] = 1;
	for (int i = 2; i <= N; i++) {
		if (!vis[i]) miu[i] = -1, prime[pcnt++] = i;  // 质数miu=-1 
		for (int j = 0; j < pcnt && i * prime[j] <= N; j++) {
			vis[i*prime[j]] = true;
			if (i % prime[j] == 0) break;  // 若 p[j]|i，则 p[j]*p[j]|i*p[j]，miu[i*p[j]]=0 
			miu[i*prime[j]] = -miu[i];  // 若p[j]与i互质，由积性函数得miu[i*p[j]]=miu[i]*miu[p[j]]=-miu[i]
		}
	}
	for (int i = 1; i <= N; i++)
		sum[i] = sum[i-1] + miu[i];  // 前缀和 
}

int calc(int n, int m) {
	if (n > m) swap(n, m);
	int ret = 0;
	for (int l = 1, r; l <= n; l = r + 1) {
		r = min(n / (n/l), m / (m/l));  // 满足n/i=n/l的i最大为n/(n/l)
		ret += (sum[r] - sum[l-1]) * (n/l) * (m/l);  // 求[l,r]内的Σmiu(i)*f(i) 
	}
	return ret;
}

/*
问题描述：求[1,n]和[1,m]内各选一个数互质的数对个数

莫比乌斯函数：
miu[1] = 1
miu[p1*p2*...*pk] = (-1)^k
miu[other] = 0
因为由单数个质数组成的数miu=-1，双数个miu=1，可以用作容斥系数，快速解决与质数有关的容斥问题

设f(i)为 i|gcd(a,b) 的数对个数
f(i) = (n/i) * (m/i) （这里的除是下取整） 
则互质数对个数 = f(1) - f(2) - f(3) + 0*f(4) - f(5) + f(2*3=6)...
f(i)前的系数为miu[i] 
注意到 n/i 的值对于相邻好几个数都是相同的，可证明为O(根号n)段 
所以对miu做一个前缀和，然后一段一段做，时间复杂度 O(根号n) 
*/
int main() {
	calcMiu();
	int T; scanf("%d", &T);
	for (int xl, xr, yl, yr, g; T--; ) {
		scanf("%d%d%d%d%d", &xl, &xr, &yl, &yr, &g);
		xl = (xl - 1) / g; yl = (yl - 1) / g; xr /= g; yr /= g;
		printf("%d\n", calc(xl, yl) + calc(xr, yr) - calc(xl, yr) - calc(xr, yl));
	}
    return 0;
}

