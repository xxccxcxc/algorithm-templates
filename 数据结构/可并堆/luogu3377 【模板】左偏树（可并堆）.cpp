#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;
const int N = 1e5+50;

struct Node {
	int ls, rs, dis;
	pair<int, int> data;
} tr[N];

int Merge(int x, int y) {
	if (!x) return y;
	if (!y) return x;
	if (tr[x].data > tr[y].data) swap(x, y);
	tr[x].rs = Merge(tr[x].rs, y);
	if (tr[tr[x].ls].dis < tr[tr[x].rs].dis)
		swap(tr[x].ls, tr[x].rs);
	tr[x].dis = tr[tr[x].rs].dis + 1;
	return x;
}

int fa[N];
int find(int x) { return fa[x] == x ? x : (fa[x] = find(fa[x])); }

bool die[N];

int main() {
	int n, m; scanf("%d%d", &n, &m);
	for (int i = 1, num; i <= n; i++) {
		scanf("%d", &num);
		tr[i].data = make_pair(num, i);
		fa[i] = i;
	}
	for (int opt, x, y; m--; ) {
		scanf("%d", &opt);
		if (opt == 1) {
			scanf("%d%d", &x, &y);
			if (die[x] || die[y]) continue;
			int fx = find(x), fy = find(y);
			if (fx == fy) continue;
			fa[fx] = fa[fy] = Merge(fx, fy);
		} else {
			scanf("%d", &x);
			if (die[x]) { printf("-1\n"); continue; }
			int fx = find(x);
			printf("%d\n", tr[fx].data.first);
			die[fx] = true;
			fa[fx] = Merge(tr[fx].ls, tr[fx].rs);  // 这里不把旧根的fa清零，而是指向新根 
			fa[fa[fx]] = fa[fx];  // fa[fx]作为新树根，它的fa必须指向自己 
		}
	}
	return 0;
}

