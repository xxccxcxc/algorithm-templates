#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;
const int N = 100050;

struct Item {
	int val, id;
	Item(): val(0), id(0) {}
	Item(int _val, int _id): val(_val), id(_id) {}
	bool operator<(const Item &t) {
		return val < t.val || val == t.val && id < t.id;
	}
};

struct Node {
	int l, r, dis;
	Item data;
	Node(): l(0), r(0), dis(0), data(Item()) {}  // 空结点dis设为0 
	Node(int _val, int _id): l(0), r(0), dis(1), data(Item(_val, _id)) {}
	// 手写构造函数，未赋值的变量不会自动赋0，所以一定要赋全 
}tr[N];

int fa[N];
bool die[N];

int find(int x) {
	if (fa[x] != x) fa[x] = find(fa[x]);
	return fa[x];
}

int merge(int x, int y) {
	if (!x) return y;
	if (!y) return x;
	if (tr[y].data < tr[x].data) swap(x, y);
	tr[x].r = merge(tr[x].r, y);
	if (tr[tr[x].l].dis < tr[tr[x].r].dis)
		swap(tr[x].l, tr[x].r);
	tr[x].dis = tr[tr[x].r].dis + 1;
	return x;
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1, val; i <= n; i++) {
		scanf("%d", &val);
		tr[i] = Node(val, i);
		fa[i] = i;
	}
	for (int opt, x, y; m--; ) {
		scanf("%d", &opt);
		if (opt == 1) {
			scanf("%d%d", &x, &y);
			if (die[x] || die[y]) continue;
			int fx = find(x), fy = find(y);
			if (fx == fy) continue;
			fa[fx] = fa[fy] = merge(fx, fy);
		}
		else {
			scanf("%d", &x);
			if (die[x]) {
				printf("-1\n");
				continue;
			}
			int fx = find(x);
			printf("%d\n", tr[fx].data.val);
			die[fx] = true;
			fa[fx] = merge(tr[fx].l, tr[fx].r);  // 这里不把旧根的fa清零，而是指向新根 
			fa[fa[fx]] = fa[fx];  // fa[fx]作为新树根，它的fa必须指向自己 
		}
	}
    return 0;
}

