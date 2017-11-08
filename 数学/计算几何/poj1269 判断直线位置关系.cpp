#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const double EPS = 1e-8;

struct Point {
	double x, y;
	Point(double _x=0, double _y=0): x(_x), y(_y) {}
	Point operator-(const Point &t) const { return Point(x - t.x, y - t.y); }
	double operator^(const Point &t) const { return x * t.y - y * t.x; }
	void input() { scanf("%lf%lf", &x, &y); }
	void print() { printf("POINT %.2lf %.2lf\n", x, y); }
};

struct Line {
	Point a, b;
	void input() { a.input(); b.input(); }
};

int sgn(double t) { return t > EPS ? 1 : t < -EPS ? -1 : 0; }

Point jiao(Line t1, Line t2) {  // 求直线交点 
	// 先算出一般式 
	double a1 = t1.a.y - t1.b.y, b1 = t1.b.x - t1.a.x, c1 = t1.a ^ t1.b;  // c刚好等于叉乘 
	double a2 = t2.a.y - t2.b.y, b2 = t2.b.x - t2.a.x, c2 = t2.a ^ t2.b;
	return Point((b2 * c1 - b1 * c2) / (b1 * a2 - b2 * a1), (a2 * c1 - a1 * c2) / (a1 * b2 - a2 * b1)); 
}

int main() {
	printf("INTERSECTING LINES OUTPUT\n");
	int T;
	scanf("%d", &T);
	for (Line t1, t2; T--; ) {
		t1.input(); t2.input();
		if (!sgn((t1.b - t1.a) ^ (t2.b - t2.a)))  // t1与t2平行 
			// t1与t2的一个端点共线，则t1t2共线 
			if (!sgn((t1.b - t1.a) ^ (t2.a - t1.a))) printf("LINE\n");
			else printf("NONE\n");  // 否则平行 
		else jiao(t1, t2).print();
	}
	printf("END OF OUTPUT\n");
	return 0;
}

