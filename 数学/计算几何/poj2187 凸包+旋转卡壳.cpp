#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
const int N = 5e4+50;

struct Point {
	int x, y;
	Point(int _x=0, int _y=0): x(_x), y(_y) {}
	bool operator < (const Point &t) const { return x != t.x ? x < t.x : y < t.y; }
	Point operator - (const Point &b) const { return Point(x - b.x, y - b.y); }
	int operator ^ (const Point &b) const { return x * b.y - y * b.x; }
	int Len2() const { return x * x + y * y; }
	friend int Cross(const Point &a, const Point &b, const Point &c) { return (b - a) ^ (c - a); }
	friend int Dis2(const Point &a, const Point &b) { return (b - a).Len2(); }
} p[N];

bool Cmp(const Point &a, const Point &b) {
	int tmp = Cross(p[1], a, b);
	return tmp ? tmp > 0 : Dis2(p[1], a) < Dis2(p[1], b);
}

int n;
Point st[N];
int top;

void Convex() {
	sort(p + 2, p + n + 1, Cmp);
	st[1] = p[1]; st[top = 2] = p[2];
	for (int i = 3; i <= n; i++) {
		while (top > 1 && Cross(st[top-1], st[top], p[i]) <= 0) top--;
		st[++top] = p[i];
	}
	st[top+1] = st[1];
}

int Rotate() {
	int ans = 0;
	for (int i = 1, j = 2; i <= top; i++) {
		// 若加等号，只有两个点会死循环 
		while (Cross(st[i], st[i+1], st[j]) < Cross(st[i], st[i+1], st[j+1]))
			j = j % top + 1;
		ans = max(ans, max(Dis2(st[i], st[j]), Dis2(st[i+1], st[j+1])));
	}
	return ans;
}

int main() {
	scanf("%d", &n);	
	for (int i = 1, x, y; i <= n; i++) {
		scanf("%d%d", &x, &y);
		p[i] = Point(x, y);
		if (p[i] < p[1]) swap(p[i], p[1]);
	}
	if (n == 2) { printf("%d\n", Dis2(p[1], p[2])); return 0; }
	Convex();
	printf("%d\n", Rotate());
	return 0;
}

