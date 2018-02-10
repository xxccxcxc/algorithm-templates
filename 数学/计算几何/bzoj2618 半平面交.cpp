#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;
const int N = 1050, M = 55;
const double EPS = 1e-8;

int Sgn(double x) {
    return x > EPS ? 1 : (x < -EPS ? -1 : 0);
}

struct Point {
    double x, y;
    void Input() { scanf("%lf%lf", &x, &y); }
    Point(double _x=0, double _y=0): x(_x), y(_y) {}
    Point operator + (const Point &b) const { return Point(x + b.x, y + b.y); }
    Point operator - (const Point &b) const { return Point(x - b.x, y - b.y); }
    double operator ^ (const Point &b) const { return x * b.y - y * b.x; }
    Point operator * (double t) const { return Point(x * t, y * t); }
    Point operator / (double t) const { return Point(x / t, y / t); }
    double Angle() const { return atan2(y, x); }
};

double Cross(const Point &a, const Point &b, const Point &c) {
    return (b - a) ^ (c - a);
}

struct Line {
    Point a, b;
    Line() { a = Point(); b = Point(); }
    Line(Point _a, Point _b): a(_a), b(_b) {}
    double Angle() const { return (b-a).Angle(); }
    Point operator * (const Line &t) const {
        double area1 = Cross(a, t.a, t.b), area2 = Cross(b, t.b, t.a);
        return (a * area2 + b * area1) / (area1 + area2);
    }
};

bool Cmp1(Line t1, Line t2) {
    int sgn = Sgn(t1.Angle() - t2.Angle());
    if (sgn) return sgn < 0;
    return Sgn(Cross(t1.a, t2.a, t2.b)) > 0;
}

bool Cmp2(Line t1, Line t2) {
    return !Sgn(t1.Angle() - t2.Angle());
}

bool InPlane(const Point &p, const Line &t) {
    return Sgn(Cross(t.a, t.b, p)) > 0;
}

void HPI(int n, Line *line, vector<Point> &res) {
    sort(line + 1, line + n + 1, Cmp1);
    n = unique(line + 1, line + n + 1, Cmp2) - line - 1;
    Line deq[N]; int l = 1, r = 2;
    deq[1] = line[1]; deq[2] = line[2];
    for (int i = 3; i <= n; i++) {
        while (l < r && !InPlane(deq[r-1] * deq[r], line[i])) r--;
        while (l < r && !InPlane(deq[l+1] * deq[l], line[i])) l++;
        deq[++r] = line[i];
    }
    while (l < r && !InPlane(deq[r-1] * deq[r], deq[l])) r--;
    deq[r+1] = deq[l];
    for (int i = l; i <= r; i++) res.push_back(deq[i] * deq[i+1]);
}

int main() {
    int rcnt; scanf("%d", &rcnt);
    int n = 0; Line line[N];
    for (int m; rcnt--; ) {
        scanf("%d", &m);
        Point first, pre, r;
        first.Input(); pre = first;
        for (int i = 2; i <= m; i++) {
            r.Input();
            line[++n] = Line(pre, r);
            pre = r;
        }
        line[++n] = Line(pre, first);
    }
    vector<Point> res; HPI(n, line, res);
    int siz = res.size(); double ans = 0;
    if (siz >= 3) {
        res.push_back(res[0]);
        for (int i = 0; i < siz; i++)
            ans += res[i] ^ res[i+1];
        ans /= 2;
    }
    printf("%.3lf\n", ans);
    return 0;
}

