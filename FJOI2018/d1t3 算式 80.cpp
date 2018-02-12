/*
luoguU19736 day1T3 算式(expr) 80pts

题意：在算式中填入1到n的数，每个数最多填一次，求结果的期望

解法：
先把表达式展开，求出每一次项的系数，第i次项系数为a[i]
设f[i][j]表示1~i中取j个的乘积之和 
f[i][j]=f[i-1][j]（i不选）+i*f[i-1][j-1]（i选），和01背包差不多，第一维可以不要
总和除以方案数等于期望 
sigma a[j]*f[n][j]/C(n,j) 即为答案 
*/
#include <bits/stdc++.h>
using namespace std;
const int N = 1e4+50;

struct Mint {
    static const int MOD = 1e9+7;
    int x;
    
    Mint(int _x=0): x((_x % MOD + MOD) % MOD) {}
    friend Mint operator + (const Mint &a, const Mint &b) { return (a.x + b.x) % MOD; }
    Mint operator += (const Mint &b) { return *this = *this + b; }
    Mint operator - () const { return MOD - x; }
    friend Mint operator - (const Mint &a, const Mint &b) { return a + -b; }
    Mint operator -= (const Mint &b) { return *this = *this - b; }
    friend Mint operator * (const Mint &a, const Mint &b) { return 1LL * a.x * b.x % MOD; }
    Mint operator *= (const Mint &b) { return *this = *this * b; }
    Mint operator ^ (int k) const {
        Mint ret = 1;
        for (Mint tmp = *this; k; k >>= 1, tmp *= tmp)
            if (k & 1) ret *= tmp;
        return ret;
    }
    Mint operator ^= (int k) { return *this = *this ^ k; }
    Mint operator ~ () const { return *this ^ MOD-2; }
    friend Mint operator / (const Mint &a, const Mint &b) { return a * ~b; }
    Mint operator /= (const Mint &b) { return *this = *this / b; }
    friend istream& operator>>(istream &in, Mint &a) { return in >> a.x; }
    friend ostream& operator<<(ostream &out, const Mint &a) { return out << a.x; }
};

struct Item {
    int mx; Mint *a;
    Item(int _mx=0): mx(_mx) {
        a = new Mint[mx+1];
        memset(a, 0, sizeof(Mint)*(mx+1));
        // 动态开空间，记得置初值为0 
    }
};

Item Opt(Item a, char opt, Item b) {  // 返回多项式a,b做opt运算的结果 
    Item ret(opt == '*' ? a.mx + b.mx : max(a.mx, b.mx));
    if (opt == '*') {
        for (int i = 0; i <= a.mx; i++)
            for (int j = 0; j <= b.mx; j++)
                ret.a[i+j] += a.a[i] * b.a[j];
    } else {
        for (int i = 0; i <= ret.mx; i++) {
            if (i <= a.mx) ret.a[i] = a.a[i];
            if (i <= b.mx) {
                if (opt == '+') ret.a[i] += b.a[i];
                if (opt == '-') ret.a[i] -= b.a[i];
            }
        }
    }
    return ret;
}

Item Calc(char*&);

Item Num(char* &s) {  // 取出表达式s中的第一个数字，若第一个是括号则返回括号内的计算结果 
    Item t;
    if (*s == '_') t = Item(1), t.a[1] = 1;
    else t = Calc(++s);
    s++; return t;  // s++起跳过'_'或')'的作用 
}

Item Mul(char* &s) {  // 把表达式s中连续的一段乘法乘起来 
    Item t = Num(s);
    while (*s == '*') t = Opt(t, '*', Num(++s));
    return t;
}

Item Calc(char* &s) {  // 计算表达式s的值，如遇右括号则退出 
    Item t = Mul(s);
    for (char ch; (ch=*s) == '+' || ch == '-'; )
        t = Opt(t, ch, Mul(++s));
    return t;
}

char s[N];
int n;
Mint f[N];

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> s;
    char *p = s;
    Item t = Calc(p);
    f[0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = i; j >= 1; j--)
            f[j] += f[j-1] * i;  // 背包 
    Mint c = 1, ans = 0;
    for (int i = 1; i <= t.mx; i++) {
        c = c * (n-i+1) / i;  // 组合数的递推求法 
        ans += t.a[i] * f[i] / c;
    }
    cout << ans << endl;
    return 0;
}

