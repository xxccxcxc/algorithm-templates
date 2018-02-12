/*
luoguU19867 day3T1 半平面交(convex) 100pts

题意：在凸多边形中随机取一个点，求这个点与边(p[0],p[1])构成的三角形面积比其它小的概率

解法：用面积列n-1个不等式，转化为半平面，再加上原本凸多边形的范围限制
求出来的半平面交面积与总面积的比例即为答案 
*/ 
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+50;

struct Point {
	double x, y;
	Point(double _x=0, double _y=0): x(_x), y(_y) {}
	Point operator + (const Point &t) const { return Point(x + t.x, y + t.y); }
	Point operator - (const Point &t) const { return Point(x - t.x, y - t.y); }
	Point operator * (double k) const { return Point(x * k, y * k); }
	double operator * (const Point &t) const { return x * t.y - y * t.x; }
	friend ostream& operator << (ostream &out, const Point &t) {
		return out << '(' << t.x << ',' << t.y << ')';
	}
} poi[N];

struct Line {
	Point p, v;  // 直线用点p和向量v来表示 
	double ang;
	Line() {}
	Line(const Point &a, const Point &b): p(a), v(b-a) {}
	bool operator < (const Line &t) const { return ang < t.ang; }
	Point operator * (const Line &t) const {
		/*
			求直线(p,u)与(q,v)的交点
			设交点为p+ku，则(p+ku-q)*v=0
			则k=(q-p)*v/(u*v)
		*/
		double k = (t.p - p) * t.v / (v * t.v);
		return p + v * k;
	}
	friend ostream& operator << (ostream &out, const Line &t) {
		return out << '[' << t.p << ';' << t.v << ']';
	}
} line[N*2];

bool Side(Point a, Line l) {
	return (l.p - a) * l.v > 0;
}

Line New(int i, int j) {
	Line ret;
	double a = (poi[i].y - poi[j].y) - (poi[0].y - poi[1].y);
	double b = (poi[j].x - poi[i].x) - (poi[1].x - poi[0].x);
	double c = poi[i] * poi[j] - poi[0] * poi[1];
	// abc用面积瞎推即可 
	if (b) ret.p = Point(0, -c / b);
	else ret.p = Point(-c / a, 0);
	// 看情况选择是用与x轴交点还是与y轴交点 
	ret.v = Point(b, -a);
	// ax+by+c=0的斜率为-a/b，至于向量用(b,-a)还是(-b,a)，特殊值或叉积推一下即可 
	// 总之要保证向量左边满足ax+by+c>=0 
	return ret;
}

Line deq[N*2];
int l, r;

double Hpl(int n) {
	for (int i = 1; i <= n; i++)
		line[i].ang = atan2(line[i].v.y, line[i].v.x);
	sort(line + 1, line + n + 1);
	l = 1; r = 0;
	for (int i = 1; i <= n; i++) {
		while (l < r && !Side(deq[r-1] * deq[r], line[i])) r--;
		while (l < r && !Side(deq[l] * deq[l+1], line[i])) l++;
		deq[++r] = line[i];
	}
	while (l < r && !Side(deq[r-1] * deq[r], deq[l])) r--;
	// 每条直线入队时已经保证队首交点在其正方向，所以这里不用弹队首 
	deq[l-1] = deq[r]; deq[r+1] = deq[l];
	double area = 0;
	for (int i = l; i <= r; i++)
		area += (deq[i-1] * deq[i]) * (deq[i] * deq[i+1]);
	return area / 2;
}

int main() {
	int n; scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%lf%lf", &poi[i].x, &poi[i].y);
	int ltop = 0;
	for (int i = 0; i < n; i++) {
		line[++ltop] = Line(poi[i], poi[(i+1)%n]);
		if (i) line[++ltop] = New(i, (i+1)%n);
	}
	double area = 0;
	for (int i = 0; i < n; i++)
		area += poi[i] * poi[(i+1)%n];
	area = area / 2;
	printf("%.4lf\n", Hpl(ltop) / area);
    return 0;
}

