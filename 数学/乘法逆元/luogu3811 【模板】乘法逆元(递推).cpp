#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long LL;
const int N = 3000050;
LL n, p, inv[N];
/*
设 a = p % i = p - p / i * i 同余 p / i * i 
两边同除 a * i
inv(i) 同余 -p / i * inv(p % i) 
-p/i是负数，加个p
所以得到逆元递推式 inv[i] = (p - p / i) * inv[p % i] % p 
*/
int main() {
	cin >> n >> p;
	inv[1] = 1; puts("1");
	for (int i = 2; i <= n; i++) {
		inv[i] = (p - p/i) * inv[p%i] % p;
		printf("%lld\n", inv[i]);
	}
	return 0;
}

