#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>  // log()需要cmath库 
using namespace std;
const int N = 100050, S = 20;
int f[N][S];
int main() {  // RMQ问题的ST算法 
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &f[i][0]);
    for (int j = 1; j <= log(n) / log(2); j++)
        for (int i = 1; i <= n - (1 << j) + 1; i++)
            f[i][j] = max(f[i][j-1], f[i+(1<<(j-1))][j-1]);
    for (int l, r; m--; ) {
        scanf("%d%d", &l, &r);
        int t = log(r - l + 1) / log(2);  // 这里区间长度是r-l+1不是r-l 
        printf("%d\n", max(f[l][t], f[r-(1<<t)+1][t]));
    }
    return 0;
}
