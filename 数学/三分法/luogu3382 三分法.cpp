#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 15;
const double EPS = 1e-6;
int n; 
double a[N];

double f(double x) {  // 秦九韶算法 
    double ret = a[0];
    for (int i = 1; i <= n; i++)
        ret = ret * x + a[i];
    return ret;
}

int main() {
    double l, r;
    cin >> n >> l >> r;
    for (int i = 0; i <= n; i++)
        cin >> a[i];
    while (l + EPS <= r) {
        double size = (r - l) / 9, m1 = l + size * 4, m2 = l + size * 5;
        // 分成4,1,4，则每次都可以排除掉4/9，比平均三分更快，而且不会卡精度 
        if (f(m1) < f(m2)) l = m1;
        else r = m2;
    }
    printf("%.5lf\n", l);
    return 0;
}

