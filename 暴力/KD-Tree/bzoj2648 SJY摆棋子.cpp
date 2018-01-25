#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;
const int N = 1e6+50, INF = 0x3f3f3f3f;

struct Point {
	int pos[2];
	Point(int _x=0, int _y=0) { pos[0] = _x; pos[1] = _y; }
	void Input() { scanf("%d%d", &pos[0], &pos[1]); }
};
	
struct Cmp {
	bool id;
	Cmp(int _id): id(_id) {}
	bool operator () (Point t1, Point t2) {
		return t1.pos[id] < t2.pos[id];
	}
};

struct KDTree {
	struct Node {
		struct D {
			int pos, mi, mx;
			D(int _pos=0) { pos = mi = mx = _pos; }
		} d[2];
		int ch[2];
		Node(Point poi = Point(0, 0)) {
			ch[0] = ch[1] = 0;
			d[0] = D(poi.pos[0]);
			d[1] = D(poi.pos[1]);
		}
	} tr[N];
	
	int top, root;
	
	KDTree() {
		for (int i = 0; i < 2; i++) {
			tr[0].d[i].mi = INF;
			tr[0].d[i].mx = -INF;
		}
	}
	
	void Update(int u) {
		int ls = tr[u].ch[0], rs = tr[u].ch[1];
		for (int i = 0; i < 2; i++) {
			tr[u].d[i].mi = min(tr[u].d[i].mi, min(tr[ls].d[i].mi, tr[rs].d[i].mi));
			tr[u].d[i].mx = max(tr[u].d[i].mx, max(tr[ls].d[i].mx, tr[rs].d[i].mx));
		}
	}
	
	int Build(Point *poi, int L, int R, int curD) {
		int mid = L + R >> 1;
		nth_element(poi + L, poi + mid, poi + R + 1, Cmp(curD));
		tr[mid] = Node(poi[mid]);
		if (L < mid) tr[mid].ch[0] = Build(poi, L, mid - 1, curD ^ 1);
		if (mid < R) tr[mid].ch[1] = Build(poi, mid + 1, R, curD ^ 1);
		Update(mid);
		return mid;
	}
	
	void Build(int n, Point *poi) {
		root = Build(poi, 1, n, 0);
		top = n + 1;
	}
	
	void Insert(int &u, int curD, Point poi) {
		if (!u) { tr[u = top++] = Node(poi); return; }
		bool lr = poi.pos[curD] >= tr[u].d[curD].pos;
		Insert(tr[u].ch[lr], curD ^ 1, poi);
		Update(u);
	}
	
	void Insert(Point poi) {
		Insert(root, 0, poi);
	}
	
	bool MightIn(int u, Point poi, int ans) {
		if (!u) return 0;
		int dis = 0;
		for (int i = 0; i < 2; i++) {
			dis += max(tr[u].d[i].mi - poi.pos[i], 0);
			dis += max(poi.pos[i] - tr[u].d[i].mx, 0);
		}
		return dis < ans;
	}
	
	int MinDis(int u, int curD, Point poi, int &ans) {
		int dis = abs(tr[u].d[0].pos - poi.pos[0]) + abs(tr[u].d[1].pos - poi.pos[1]);
		ans = min(ans, dis);
		bool lr = poi.pos[curD] >= tr[u].d[curD].pos;
		for (int cnt = 0; cnt < 2; lr ^= 1, cnt++)
			if (MightIn(tr[u].ch[lr], poi, ans))
				MinDis(tr[u].ch[lr], curD ^ 1, poi, ans);
	}
	
	int MinDis(Point poi) {
		int ans = INF;
		MinDis(root, 0, poi, ans);
		return ans;
	}
} kdTree;

Point init[N];

int main() {
	int n, m; scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) init[i].Input();
	kdTree.Build(n, init);
	while (m--) {
		int opt; scanf("%d", &opt);
		Point poi; poi.Input();
		if (opt == 1) kdTree.Insert(poi);
		else printf("%d\n", kdTree.MinDis(poi));
	}
	return 0;
}

