#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long LL;
/*
exgcd(a, b)求ax+by=gcd(a, b)的一组特解
原理：
递归先求 b*x' + (a%b)*y' = g 的一组特解 
因为a%b = a - a/b*b
所以原式等价于 b*x' + (a-a/b*b)*y' = g 
b*x' + a*y' - a/b*b*y' = g
a*y' + b*(x'-a/b*y') = g
所以x = y', y = x'-a/b*y' 
边界：当b=0时，ax+0y=a，得x = 1, y = 0 
*/
void exgcd(LL a, LL b, LL &x, LL &y, LL &g) {
	b ? (exgcd(b, a%b, y, x, g), y -= a / b * x) : (x = 1, y = 0, g = a);
}

/*
tyfc(a, b, c)求ax+by=c的最小正整数解 
首先用exgcd(a, b)求ax+by=g的特解
然后把两边同时扩大c/g倍得
a(x*c/g) + b(y*c/g) = c
（若g不是c的因数，则c/g不为整数，无解） 
所以把之前的x扩大c/g倍即是特解
通解为x + t * (b/g)
因为ax+by=c的通解为x + t * b
而ax+by=c两边同除g得 a/g*x +  b/g*y = c/g
此时a与b互质，通解为x + t * (b/g) 
*/
LL tyfc(LL a, LL b, LL c) {  // 同余方程（实在不会取名了） 
	LL x, y, g;
	exgcd(a, b, x, y, g);
	if (c % g) return -1;
	int t = b / g;
	return (x * c/g % t + t) % t;
}

int main() {
	LL x, y, m, n, L;
	cin >> x >> y >> m >> n >> L;
	if (m < n) swap(m, n), swap(x, y);
	int ans = tyfc(m - n, L, y - x);
	if (~ans) cout << ans << endl;
	else puts("Impossible");
	return 0;
}

