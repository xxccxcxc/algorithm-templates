#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const int N = 500050;
const double INF = 0x3f3f3f3f;
int n;
double a[N], f[N], g[N];

void bs(double *f, int ul, int ur, int l, int r) {  // 二分，处理的f区间为ul~ur，决策点区间为l~r 
	if (ul > ur || l > r) return;
	int mid = (ul + ur) >> 1, pos;
	f[mid] = -INF;
	for (int i = l; i <= r && i <= mid; i++)  // 暴力枚举f[mid]的决策点 
		if (a[i] + sqrt(mid - i) > f[mid])
			f[mid] = a[i] + sqrt(mid - i), pos = i;
	f[mid] -= a[mid];
	bs(f, ul, mid - 1, l, pos);  // 对于ul~mid-1区间，决策点必在l~pos之间 
	bs(f, mid + 1, ur, pos, r);  // 同理 
}

int main() {
	// 题意：一道决策单调dp，具体题面不重要 
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%lf", &a[i]);
	bs(f, 1, n, 1, n);
	reverse(a + 1, a + n + 1);
	bs(g, 1, n, 1, n);
	for (int i = 1; i <= n; i++)
		printf("%.0lf\n", ceil(max(f[i], g[n-i+1])));
	return 0;
}

