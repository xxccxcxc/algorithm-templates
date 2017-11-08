#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctime>
using namespace std;
const int N = 250;
const double EPS = 1e-6;

struct Point {
	double x, y;
	Point(double _x=0, double _y=0): x(_x), y(_y) {}
	Point operator-(const Point &t) const { return Point(x - t.x, y - t.y); }
	double operator^(const Point &t) const { return x * t.y - y * t.x; }
	void random() {  // 随机一个远点作为射线的另一端 
		x = (rand() % 546546546 + 546546546) * (rand() & 1 ? 1 : -1);
		y = (rand() % 546546546 + 546546546) * (rand() & 1 ? 1 : -1);
	}
	void input() { cin >> x >> y; }
	void print() { cout << x << ' ' << y << endl; }
}point[N];
int n;

int sgn(double t) { return t > EPS ? 1 : t < -EPS ? -1 : 0; }

double xc(Point a, Point b, Point c) {
	return (b - a) ^ (c - a);
}

bool judge1(Point a, Point b, Point c) {  // 判断a是否在线段bc上 
	if (b.x > c.x) swap(b, c);
	return !sgn(xc(a, b, c)) && sgn(a.x - b.x) >= 0 && sgn(a.x - c.x) <= 0;
}

bool judge2(Point a, Point b, Point c, Point d) {  // 判断线段ab和cd是否相交 
	// a和b在cd两边并且c和d在ab两边，用叉乘判断 
	return sgn(xc(a, b, c)) * sgn(xc(a, b, d)) < 0 && sgn(xc(c, d, a)) * sgn(xc(c, d, b)) < 0;
}

bool judge(Point u) {
	for (int i = 0; i < n; i++)
		if (judge1(u, point[i], point[(i+1)%n]))
			return true;
	int cnt = 0;
	for (int i = 0; i < 11; i++) {  // 随机若干条射线 
		Point v; v.random();
		int t = 0;
		for (int j = 0; j < n; j++)
			t += judge2(u, v, point[j], point[(j+1)%n]); 
		cnt += t & 1;  // 射线交的边数为奇数则在多边形内 
	}
	return cnt > 5;  // 成功次数在一半以上就return true 
}

int main() {  // 用随机射线法判断点是否在多边形内 
	for (int cas = 1, m; cin >> n && n; cas++) {
		cin >> m;
		if (cas > 1) cout << endl;
		printf("Problem %d:\n", cas);
		for (int i = 0; i < n; i++)
			point[i].input();
		for (Point u; m--; ) {
			u.input();
			cout << (judge(u) ? "Within" : "Outside") << endl;
		}
	}
	return 0;
}

