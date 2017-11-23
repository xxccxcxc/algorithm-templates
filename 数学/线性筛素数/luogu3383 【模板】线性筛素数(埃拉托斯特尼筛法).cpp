#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const int N = 1e7+5;
bool p[N];

int main() {  // 埃拉托斯特尼筛法，O(nloglogn) 
	int n, m;
	scanf("%d%d", &n, &m);
	p[0] = p[1] = true;
	for (int i = 2; i <= n; i++)
		if (!p[i])
			for (int j = i << 1; j <= n; j += i)  // 从i*2开始，不然i会被置为合数 
				p[j] = true;
	for (int u; m--; ) {
		scanf("%d", &u);
		printf(p[u] ? "No\n" : "Yes\n");
	}
	return 0;
}

