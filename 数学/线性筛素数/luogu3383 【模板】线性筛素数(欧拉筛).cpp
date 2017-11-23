#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 10000050;
bool p[N];
int prime[N], pcnt;

int main() {  // 欧拉筛法 
	int n, m;
	scanf("%d%d", &n, &m);
	p[1] = true;
	for (int i = 2; i <= n; i++) {
		if (!p[i]) prime[pcnt++] = i;
		for (int j = 0; j < pcnt; j++) {
			if (i * prime[j] > n) break;
			p[i*prime[j]] = true;
			// 若 p[j]|i，则 p[j]|i*p[j+1]，没必要继续做。
			// 这保证了p[j]是i*p[j]的最小质因子（如果不是那就循环不到这里了） 
			if (i % prime[j] == 0) break;
		}
	}
	for (int r; m--; printf(p[r] ? "No\n" : "Yes\n"))
		scanf("%d", &r);
	return 0;
}

