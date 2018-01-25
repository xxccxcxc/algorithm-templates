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
	Point(int _x=0, int _y=0) {
		pos[0] = _x;
		pos[1] = _y;
	}
};

int Dis(Point a, Point b) {
	return abs(a.pos[0] - b.pos[0]) + abs(a.pos[1] - b.pos[1]);
}
	
struct Cmp {
	bool id;
	Cmp(int _id): id(_id) {}
	bool operator () (Point t1, Point t2) {
		return t1.pos[id] < t2.pos[id];
	}
};

struct KDTree {
	struct Node {
		Point p;
		int ch[2], mi[2], mx[2];
		Node(Point _p = Point(0, 0)) {
			p = _p;
			for (int i = 0; i < 2; i++) {
				ch[i] = 0;
				mi[i] = mx[i] = p.pos[i];
			}
		}
	} tr[N];
	
	int top, root;
	
	KDTree() {
		for (int i = 0; i < 2; i++) {
			tr[0].mi[i] = INF;
			tr[0].mx[i] = -INF;
		}
	}
	
	void Update(int u) {
		int ls = tr[u].ch[0], rs = tr[u].ch[1];
		for (int i = 0; i < 2; i++) {
			tr[u].mi[i] = min(tr[u].mi[i], min(tr[ls].mi[i], tr[rs].mi[i]));
			tr[u].mx[i] = max(tr[u].mx[i], max(tr[ls].mx[i], tr[rs].mx[i]));
		}
	}
	
	int Build(Point *p, int L, int R, int d) {
		int mid = L + R >> 1;
		nth_element(p + L, p + mid, p + R + 1, Cmp(d));
		tr[mid] = Node(p[mid]);
		if (L < mid) tr[mid].ch[0] = Build(p, L, mid - 1, d ^ 1);
		if (mid < R) tr[mid].ch[1] = Build(p, mid + 1, R, d ^ 1);
		Update(mid);
		return mid;
	}
	
	void Build(int n, Point *p) {
		root = Build(p, 1, n, 0);
		top = n + 1;
	}
	
	void Insert(int &u, int d, Point p) {
		if (!u) { tr[u = top++] = Node(p); return; }
		bool lr = p.pos[d] >= tr[u].p.pos[d];
		Insert(tr[u].ch[lr], d ^ 1, p);
		Update(u);
	}
	
	void Insert(Point p) {
		Insert(root, 0, p);
	}
	
	bool MightIn(int u, Point p, int ans) {
		if (!u) return 0;
		int dis = 0;
		for (int i = 0; i < 2; i++) {
			dis += max(tr[u].mi[i] - p.pos[i], 0);
			dis += max(p.pos[i] - tr[u].mx[i], 0);
		}
		return dis < ans;
	}
	
	int MinDis(int u, int d, Point p, int &ans) {
		ans = min(ans, Dis(tr[u].p, p));
		bool lr = p.pos[d] >= tr[u].p.pos[d];
		for (int cnt = 0; cnt < 2; lr ^= 1, cnt++)
			if (MightIn(tr[u].ch[lr], p, ans))
				MinDis(tr[u].ch[lr], d ^ 1, p, ans);
	}
	
	int MinDis(Point p) {
		int ans = INF;
		MinDis(root, 0, p, ans);
		return ans;
	}
} kd;

Point init[N];

int main() {
	int n, m; scanf("%d%d", &n, &m);
	for (int x, y, i = 1; i <= n; i++) {
		scanf("%d%d", &x, &y);
		init[i] = Point(x, y);
	}
	kd.Build(n, init);
	while (m--) {
		int opt, x, y; scanf("%d%d%d", &opt, &x, &y);
		Point p(x, y);
		if (opt == 1) kd.Insert(p);
		else printf("%d\n", kd.MinDis(p));
	}
	return 0;
}

