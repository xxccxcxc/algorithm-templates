#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;
const int N = 2048;

struct Tree {
	struct BIT {
		int a[N+50][N+50];
		
		int Lowbit(int x) { return x & -x; }
		
		void Add(int x, int y, int val) {
			for (int i = x; i <= N; i += Lowbit(i))
				for (int j = y; j <= N; j += Lowbit(j))
					a[i][j] += val;
		}
		
		int Query(int x, int y) {
			int ret = 0;
			for (int i = x; i; i -= Lowbit(i))
				for (int j = y; j; j -= Lowbit(j))
					ret += a[i][j];
			return ret;
		}
	} a, b, c, d;
	
	void Add(int x1, int y1, int x2, int y2, int val) {
		a.Add(x1, y1, val); a.Add(x2+1, y2+1, val);
		a.Add(x1, y2+1, -val); a.Add(x2+1, y1, -val);
		
		b.Add(x1, y1, val*x1); b.Add(x2+1, y2+1, val*(x2+1));
		b.Add(x1, y2+1, -val*x1); b.Add(x2+1, y1, -val*(x2+1));
		
		c.Add(x1, y1, val*y1); c.Add(x2+1, y2+1, val*(y2+1));
		c.Add(x1, y2+1, -val*(y2+1)); c.Add(x2+1, y1, -val*y1);
		
		d.Add(x1, y1, val*x1*y1); d.Add(x2+1, y2+1, val*(x2+1)*(y2+1));
		d.Add(x1, y2+1, -val*x1*(y2+1)); d.Add(x2+1, y1, -val*(x2+1)*y1);
	}
	
	int Query(int x, int y) {
		return (x+1)*(y+1)*a.Query(x, y) - (y+1)*b.Query(x, y) - (x+1)*c.Query(x, y) + d.Query(x, y);
	}
	
	int Query(int x1, int y1, int x2, int y2) {
		return Query(x2, y2) - Query(x1-1, y2) - Query(x2, y1-1) + Query(x1-1, y1-1);
	}
} tree;


int main() {
	scanf("X %*d %*d\n");
	for (char opt[10]; ~scanf("%s", opt); ) {
		int x1, y1, x2, y2, val;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		if (opt[0] == 'L') {
			scanf("%d", &val);
			tree.Add(x1, y1, x2, y2, val);
		}
		else printf("%d\n", tree.Query(x1, y1, x2, y2));
	}
    return 0;
}

