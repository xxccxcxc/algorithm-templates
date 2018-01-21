#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
const int N = 2e5+50;

struct ChairmanTree {
	struct Node {
		int ls, rs, cnt;
		Node(): ls(0), rs(0), cnt(0) {}
	} tr[N*40];
	int top, root[N], mx, tim;
	
	ChairmanTree(): top(1) {}
	
	void Init(int _mx) { mx = _mx; }
	
	void Insert(int &cur, int pre, int L, int R, int pos) {
		(tr[cur = top++] = tr[pre]).cnt++;
		if (L == R) return;
		int mid = L + R >> 1;
		if (pos <= mid) Insert(tr[cur].ls, tr[pre].ls, L, mid, pos);
		else Insert(tr[cur].rs, tr[pre].rs, mid + 1, R, pos);
	}
	
	void Insert(int pos) {
		tim++;
		Insert(root[tim], root[tim-1], 0, mx, pos);
	}
	
	int Query(int lu, int ru, int L, int R, int k) {
		if (L == R) return L;
		int mid = L + R >> 1, lCnt = tr[tr[ru].ls].cnt - tr[tr[lu].ls].cnt;
		if (k <= lCnt) return Query(tr[lu].ls, tr[ru].ls, L, mid, k);
		else return Query(tr[lu].rs, tr[ru].rs, mid + 1, R, k - lCnt);
	}
	
	int Query(int t1, int t2, int k) {
		return Query(root[t1-1], root[t2], 0, mx, k);
	}
} tree;

int a[N];

int main() {
	int n, m, mx = 0; scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]), mx = max(mx, a[i]);
	tree.Init(mx);
	for (int i = 1; i <= n; i++)
		tree.Insert(a[i]);
	for (int l, r, k; m--; ) {
		scanf("%d%d%d", &l, &r, &k);
		printf("%d\n", tree.Query(l, r, k));
	}
	return 0;
}

