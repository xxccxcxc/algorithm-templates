#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;
const int N = 40050;
int main() {
	/*
	欧拉函数公式：φ(i)=n(1-1/p1)(1-1/p2)...(1-1/pm) （p为n的质因数）
	证明：
	当p是质数时，φ(p^k) = p^k - p^(k-1) = p^k(1-1/p)
	因为只有不是p的倍数才能与p^k互质，总共有p^k个数 ，p的倍数有p^(k-1)个
	由中国剩余定理（并不会）得，欧拉函数是积性函数
	所以φ(n)=p1^k1*p2^k2*...*pm^km*(1-1/p1)(1-1/p2)...(1-1/pm)=n(1-1/p1)(1-1/p2)...(1-1/pm)
	这玩意可以用筛法边筛质数边求 
	*/
	int n, a[N] = {0}, ans = 0;
	cin >> n;
	if (!--n) { cout << 0 << endl; return 0; }
	ans = a[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!a[i]) {  // i是质数 
			a[i] = i;
			for (int j = i; j <= n; j += i) {
				if (!a[j]) a[j] = j;
				a[j] = a[j] * (i - 1) / i;
			}
		}
		ans += a[i];
	}
	cout << ans * 2 + 1 << endl;
    return 0;
}

