#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long LL;
const int N = 100050;
LL b[N], c[N];
int siz;

int lowbit(int x) { return x & (-x); }

void add1(LL *t, int pos, int val) {
	for (; pos <= siz; pos += lowbit(pos))
		t[pos] += val;
}

void add(int l, int r, LL val) {
	add1(b, l, val); add1(b, r+1, -val);
	add1(c, l, val * (l-1)); add1(c, r+1, -val * r);
}

LL query1(LL *t, int pos) {
	LL ret = 0;
	for (; pos; pos -= lowbit(pos))
		ret += t[pos];
	return ret;
}

LL query(int l, int r) {
	LL s1 = (l-1) * query1(b, l-1) - query1(c, l-1), s2 = r * query1(b, r) - query1(c, r);
	return s2 - s1;
}

/*
树状数组区间修改+区间查询（自带小常数） 
设a为原数组，b为差分数组
则1~n的区间和可以表示为
b[1] + (b[1]+b[2]) + (b[1]+b[2]+b[3]) + ... + (b[1]+b[2]+...+b[n])
= b[1]*n + b[2]*(n-1) + ... + b[n] * 1
= n * (b[1] + b[2] + ... + b[n]) - ( (1-1) * b[1] + (2-1) * b[2] + ... + (n-1) * b[n] )
于是维护数组c存放 (i - 1) * b[i]，修改b时顺便修改c，查询1~n之和时只要查 n * b[1~n] - c[1~n] 即可 
*/ 

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	siz = n;
	for (int i = 1; i <= n; i++) {
		LL val;
		scanf("%lld", &val);
		add(i, i, val);
	}
	for (int opt, l, r; m--; ) {
		scanf("%d%d%d", &opt, &l, &r);
		if (opt == 1) {
			LL val;
			scanf("%lld", &val);
			add(l, r, val);
		}
		else printf("%lld\n", query(l, r));
	}
    return 0;
}

