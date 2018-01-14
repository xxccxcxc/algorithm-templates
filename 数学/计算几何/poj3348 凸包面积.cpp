#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const int N = 10050;
const double EPS = 1e-6;
struct Point {
	double x, y;
	Point(double _x=0, double _y=0): x(_x), y(_y) {}
	Point operator-(const Point &t) const { return Point(x - t.x, y - t.y); }
	double operator^(const Point &t) const { return x * t.y - y * t.x; }
	double operator*(const Point &t) const { return x * t.x + y * t.y; }
	bool operator<(const Point &t) const { return x < t.x || x == t.x && y < t.y; }
	void input() { cin >> x >> y; }
	void print() { cout << x << ' ' << y << endl; }
}point[N];

int sgn(double t) { return t > EPS ? 1 : t < -EPS ? -1 : 0; }
double xc(const Point &a, const Point &b, const Point &c) { return (b - a) ^ (c - a); }
double dis(const Point &a, const Point &b) { return sqrt((a-b)*(a-b)); }
bool cmp(Point t1, Point t2) {
	int t = sgn(xc(point[0], t1, t2));
	return t > 0 || t == 0 && dis(point[0], t1) < dis(point[0], t2);
} 

int main() {  // 求凸包面积 
	int n; cin >> n;
	if (n < 3) { cout << 0 << endl; return 0; }  // 少于3个点不能构成凸包 
	for (int i = 0; i < n; i++) {
		point[i].input();
		if (point[i] < point[0])  // 以x坐标最小的点为原点来极角排序 
			swap(point[i], point[0]); 
	}
	sort(point + 1, point + n, cmp);
	int st[N], top = 1;
	st[0] = 0; st[1] = 1;
	for (int i = 2; i < n; i++) {  // 凸包 
		while (top > 0 && xc(point[st[top-1]], point[st[top]], point[i]) <= 0) --top;
		st[++top] = i;
	}
	int ans = 0;
	for (int i = 1; i < top; i++)
		ans += xc(point[st[0]], point[st[i]], point[st[i+1]]);  // 叉乘计算面积 
	cout << ans / 2 / 50 << endl;  // 叉乘要/2，题目要求/50 
	return 0;
}

