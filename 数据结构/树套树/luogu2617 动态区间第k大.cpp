#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;
const int N = 1e4+50, SIZ = 9e6+50;
const int MI = 0, MX = 1e9;

struct Tree {
	struct Node {
		int ch[2], cnt;
	} seg[SIZ];
	int top;
	int n, root[N];
	
	Tree(): top(1) {}
	void Init(int _n) { n = _n; }
	int Lowbit(int x) { return x & -x; }
	
	void SegAdd(int &u, int L, int R, int pos, int val) {
		seg[u ? u : u = top++].cnt += val;
		if (L == R) return;
		int mid = L + R >> 1;
		if (pos <= mid) SegAdd(seg[u].ch[0], L, mid, pos, val);
		else SegAdd(seg[u].ch[1], mid + 1, R, pos, val);
	}
	
	void Add(int t, int pos, int val) {
		for (int u = t; u <= n; u += Lowbit(u))
			SegAdd(root[u], MI, MX, pos, val);
	}
	
	int SegKth(vector<int> qu[2], int L, int R, int k) {
		if (L == R) return L;
		int mid = L + R >> 1, lCnt = 0;
		for (int i = 0; i < 2; i++)
			for (int siz = qu[i].size(), j = 0; j < siz; j++)
				lCnt += seg[seg[qu[i][j]].ch[0]].cnt * (i ? 1 : -1);
		bool lr = k > lCnt;
		for (int i = 0; i < 2; i++)
			for (int siz = qu[i].size(), j = 0; j < siz; j++)
				qu[i][j] = seg[qu[i][j]].ch[lr];
		return !lr ? SegKth(qu, L, mid, k) : SegKth(qu, mid + 1, R, k - lCnt);
	}
	
	int Kth(int t1, int t2, int k) {
		vector<int> qu[2];
		for (int u = t1 - 1; u; u -= Lowbit(u))
			qu[0].push_back(root[u]);
		for (int u = t2; u; u -= Lowbit(u))
			qu[1].push_back(root[u]);
		return SegKth(qu, MI, MX, k);
	}
} tree;

int a[N];

int main() {
	int n, m; scanf("%d%d", &n, &m); tree.Init(n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		tree.Add(i, a[i], 1);
	}
	while (m--) {
		char opt[3]; int r1, r2, r3;
		scanf("%s%d%d", opt, &r1, &r2);
		if (opt[0] == 'Q') {
			scanf("%d", &r3);
			printf("%d\n", tree.Kth(r1, r2, r3));
		} else {
			tree.Add(r1, a[r1], -1);
			a[r1] = r2;
			tree.Add(r1, a[r1], 1);
		}
	}
	return 0;
}

