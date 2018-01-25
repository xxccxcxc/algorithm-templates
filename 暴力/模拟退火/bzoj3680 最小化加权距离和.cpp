#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;
const int N = 10050;

struct Point { double x, y; };

double GetDis(const Point &t1, const Point &t2) {
    return sqrt((t1.x-t2.x)*(t1.x-t2.x)+(t1.y-t2.y)*(t1.y-t2.y));
}

struct Node {
    Point pos; double g;
    void Input() { scanf("%lf%lf%lf", &pos.x, &pos.y, &g); }
} a[N];

int n;

struct Ans {
    Point pos; double val;
    void CalcVal() {
        val = 0;
        for (int i = 1; i <= n; i++)
            val += GetDis(pos, a[i].pos) * a[i].g;
    }
} ans;

double GetRand() { return rand() % 10000 / 10000.0; }

void Move() {
    Ans u = ans;
    double T;
    for (T = 100000; T > 0.001; T *= 0.98) {
        Ans v;
        v.pos.x = u.pos.x + T * (GetRand() * 2 - 1);
        v.pos.y = u.pos.y + T * (GetRand() * 2 - 1);
        v.CalcVal(); if (v.val < ans.val) ans = v;
        double delta = u.val - v.val;
        if (delta > 0 || GetRand() < exp(delta / T)) u = v;
    }
    for (int i = 1; i <= 1000; i++) {
        u.pos.x = ans.pos.x + T * (GetRand() * 2 - 1);
        u.pos.y = ans.pos.y + T * (GetRand() * 2 - 1);
        u.CalcVal(); if (u.val < ans.val) ans = u;
    }
}

int main() {
    srand(546546546);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        a[i].Input();
        ans.pos.x += a[i].pos.x;
        ans.pos.y += a[i].pos.y;
    }
    ans.pos.x /= 1.0 * n;
    ans.pos.y /= 1.0 * n;
    ans.CalcVal();
    Move();
    printf("%.3lf %.3lf\n", ans.pos.x, ans.pos.y);
    return 0;
}

