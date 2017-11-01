#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;
typedef long long LL;
const int N = 100050;

struct Node {
	int l, r;
	LL sum, lazy;  // lazy表示子树上的点都需要更新，但自己已经更新完毕 
	int size() {
		return r - l + 1;
	}
}tr[N << 2];  // 一定要开4倍以上空间 

int son(int u, int p) {  // p最好不要开bool，会有奇怪的错误 
	return (u << 1) + p;  // 记得加括号 
}

void pushup(int u) {
	tr[u].sum = tr[son(u, 0)].sum + tr[son(u, 1)].sum;
}

void build(int u, int l, int r) {
	tr[u].l = l; tr[u].r = r;
	if (l == r) {
		scanf("%lld", &tr[u].sum);
		return;
	}
	int mid = (l + r) >> 1;
	build(son(u, 0), l, mid);
	build(son(u, 1), mid+1, r);
	pushup(u);
}

void pushdown(int u) {
	LL val = tr[u].lazy;
	for (int i = 0; i <= 1; i++) {
		int v = son(u, i);
		tr[v].sum += tr[v].size() * val;
		tr[v].lazy += val;
	}
	tr[u].lazy = 0;
} 

void update(int u, int l, int r, LL val) {
	if (tr[u].l == l && tr[u].r == r) {
		tr[u].sum += tr[u].size() * val;
		tr[u].lazy += val;
		return;
	}
	if (tr[u].lazy) pushdown(u);
	int mid = (tr[u].l + tr[u].r) >> 1;
	if (l <= mid) update(son(u, 0), l, min(r, mid), val);
	if (r > mid) update(son(u, 1), max(l, mid + 1), r, val);
	pushup(u);
}

LL query(int u, int l, int r) {
	if (tr[u].l == l && tr[u].r == r)
		return tr[u].sum;
	if (tr[u].lazy) pushdown(u);  // 记得pushdown 
	// int mid = (l + r) >> 1; 是错误的 
	int mid = (tr[u].l + tr[u].r) >> 1;
	LL ret = 0;
	if (l <= mid) ret += query(son(u, 0), l, min(r, mid));
	if (r > mid) ret += query(son(u, 1), max(l, mid + 1), r);
	return ret;
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	build(1, 1, n);
	for (int opt, l, r; m--; ) {
		scanf("%d%d%d", &opt, &l, &r);
		if (opt == 1) {
			LL val;
			scanf("%lld", &val);  // 线段树开long long的话，scanf要记得%lld 
			update(1, l, r, val);
		}
		else printf("%lld\n", query(1, l, r));
	}
    return 0;
}

