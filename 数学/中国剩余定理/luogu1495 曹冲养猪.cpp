#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;
typedef long long LL;
const int N = 15;

void exgcd(LL a, LL b, LL &x, LL &y) {
	b ? (exgcd(b, a%b, y, x), y -= a/b*x) : (x = 1, y = 0);
}

LL inv(LL a, LL b) {  // 求a关于b的乘法逆元 
	LL x, y;
	exgcd(a, b, x, y);
	return (x % b + b) % b;
}

int main() {
	/*
	题意：给定方程组 x 三 r[i] (mod m[i])，求最小正整数解 
	中国剩余定理模板
	解法：
	设 msum 为所有m的乘积，M[i] = msum / m[i] 
	设 a[i] 三 1 mod m[i]，且 ai 三 0 mod m[其他]
	则 a[i] * r[i] 求和再模msum即为x
	现在只需要求 a[i]，由 ai 三 0 mod m[其他] 得a[i]是M[i]的倍数 
	设 a[i] = k * M[i]，则 k * M[i] 三 1 mod m[i]
	所以k是M[i]关于m[i]的乘法逆元，用exgcd求出k后乘上M[i]即为a[i]
	*/
	int n;
	LL m[N], r[N], msum = 1;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> m[i] >> r[i];
		msum *= m[i];
	}
	LL ans = 0;
	for (int i = 1; i <= n; i++)
		ans = (ans + inv(msum / m[i], m[i]) * msum / m[i] * r[i]) % msum;  // inv(M[i]) * M[i] * r[i]
	cout << (ans % msum + msum) % msum << endl;   // 最小正整数解 
    return 0;
}

