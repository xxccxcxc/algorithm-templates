/*
杜教筛模板
具体见http://xxccxcxc.top/post/15/ 
*/ 
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <map>
using namespace std;
typedef long long LL;
const int M = 3000000; 

LL phi[M+5], mu[M+5];
int prime[M], pcnt;
bool notPri[M+5];
map<int, LL> muAns, phiAns;

void Sieve() {
    phi[1] = mu[1] = 1;
    for (int i = 2; i < M; i++) {
        if (!notPri[i]) {
            prime[pcnt++] = i;
            phi[i] = i - 1;
            mu[i] = -1;
        }
        for (int j = 0; j < pcnt && 1LL * i * prime[j] < M; j++) {
            int t = 1LL * i * prime[j];
            notPri[t] = true;
            if (i % prime[j]) {
                phi[t] = phi[i] * phi[prime[j]];
                mu[t] = mu[i] * mu[prime[j]];
            }
            else {
                phi[t] = phi[i] * prime[j];
                mu[t] = 0;
                break;
            }
        }
    }
    for (int i = 2; i < M; i++) {
        phi[i] += phi[i - 1];
        mu[i] += mu[i - 1];
    }
}

LL CalcMu(LL n) {
    if (n < M) return mu[n];
    if (muAns.count(n)) return muAns[n];
    LL last; LL ans = 1;
    for (LL i = 2; i <= n; i = last + 1) {
        last = n / (n / i);
        ans -= (last - i + 1) * CalcMu(n / i);
    }
    return muAns[n] = ans;
}

LL CalcPhi(LL n) {
    if (n < M) return phi[n];
    if (phiAns.count(n)) return phiAns[n];
    LL last; LL ans = 1LL * n * (n + 1) >> 1;
    for (LL i = 2; i <= n; i = last + 1) {
        last = n / (n / i);
        ans -= (last - i + 1) * CalcPhi(n / i);
    }
    return phiAns[n] = ans;
}

int main() {
    Sieve();
    int T; scanf("%d", &T);
    for (int n; T--; ) {
        scanf("%d", &n);
        printf("%lld %lld\n", CalcPhi(n), CalcMu(n));
    }
    return 0;
}

