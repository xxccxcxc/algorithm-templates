/*
luoguU19723 day1T1 真因数(factor) 100pts

题意：求[l,r]之间每个合数除以最小质因数的和, l,r<=1e9

解法：
设f[i][j]表示[2,i]内的数筛掉前j个质数，剩下的数的和
第j个质数筛掉的数形如pri[j]*x
如果pri[j]^2>i，筛不掉任何数，f[i][j]=f[i][j-1]
否则2<=x<=i/pri[j]，且x不含前j-1个质数
那么x在f[i/pri[j]][j-1]中，且不为前j-1个质数 
f[i][j]=f[i][j-1]-pri[i]*(f[i/pri[j]][j-1]-sum[j-1])
sum[j-1]为前j-1个质数之和 
求出答案后，pri[j]作为minp对答案的贡献为(f[i][j-1]-f[i][j])/pri[j]
关于空间，n/i下取整只有2*sqrt(n)种取值
那么把真实值和数组下标做相互映射即可 
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int M = 1e5;
const int PoolSize = 1e7;

LL n, m;
LL pool[PoolSize];
LL *f[M*2+50], *it;
int siz[M*2+50];
int pri[M+50]; int pTop;
bool vis[M+50];
LL pSum[M+50];

void Sieve() {
    for (LL i = 2; i <= M; i++) {
        if (!vis[i]) {
            pri[++pTop] = i;
            pSum[pTop] = pSum[pTop-1] + i;
        }
        for (int j = 1; j <= pTop && 1LL*i*pri[j] <= M; j++) {
            vis[i*pri[j]] = true;
            if (i % pri[j] == 0) break;
        }
    }
}

LL GetF(LL i, int j) {
    LL pos = i <= m ? i : m*2+1-n/i;  // 这是下面的逆运算 
    return f[pos][min(j, siz[pos])];
}

LL Solve(LL lim) {
    if (!lim) return 0;
    m = sqrt(n = lim); it = pool;
    for (LL pos = 1; pos <= m * 2; pos++) {
        LL i = pos <= m ? pos : n/(m*2+1-pos);
        // i为真实值，pos为下标，真实值1~m对应下标1~m，真实值m~n每一段对应下标m+1~2m 
        f[pos] = it; siz[pos] = 0;
        f[pos][0] = 1LL*i*(i+1)/2-1;
        for (int j = 1; 1LL*pri[j]*pri[j] <= i; j++, siz[pos]++)
            f[pos][j] = f[pos][j-1] - 1LL * pri[j] * (GetF(i/pri[j], j-1) - pSum[j-1]);
        it += siz[pos] + 1;
    }
    LL ret = 0;
    for (LL i = 0; i < siz[m*2]; i++)
        ret += (f[m*2][i] - f[m*2][i+1]) / pri[i+1];
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    Sieve();
    LL l, r; cin >> l >> r;
    cout << Solve(r) - Solve(l - 1) << endl;
    return 0;
}

