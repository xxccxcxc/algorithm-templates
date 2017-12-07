#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;
const int N = 4000050;
const double pi = acos(-1.0);

struct Complex {  // 复数 
    double r, i;  // r为实部，i为虚部i的系数 
    Complex(double _r=0, double _i=0): r(_r), i(_i) {}
    Complex operator+(const Complex &b) const { return Complex(r + b.r, i + b.i); }
    Complex operator-(const Complex &b) const { return Complex(r - b.r, i - b.i); }
	// 乘法与实数相似，不过注意i^2=-1
    Complex operator*(const Complex &b) const { return Complex(r*b.r - i*b.i, r*b.i + b.r*i); } 
    Complex operator*=(const Complex &b) { return *this = *this * b; }
    // 这里只用到复数除以实数，直接除就好 
    Complex operator/(double b) const { return Complex(r / b, i / b); }
    Complex operator/=(double b) { return *this = *this / b; }
} a[N], b[N];

int n, R[N], c[N];

void FFT(Complex *f, int sgn) {  // FFT非递归实现，sgn=1做DFT变换，-1做逆DFT变换 
    for (int i = 0; i < n; i++)
        if (i < R[i]) swap(f[i], f[R[i]]);  // 蝴蝶变换 
    for (int i = 1; i < n; i <<= 1) {  // 当前区间长度为2*i 
    	// 单位根wn=e^(2*pi/n*i)，用欧拉公式求 
    	// 欧拉公式：e^(x*i) = cos(x) + sin(x) * i
    	// 若做逆DFT，wn=wn^(-1)
        Complex wn(cos(pi / i), sgn * sin(pi / i));
        for (int j = 0; j < n; j += i << 1) {  // j为当前区间起始位置 
            Complex w(1, 0);
            for (int k = 0; k < i; k++, w *= wn) {  // 处理当前区间的第k个和第k+i个系数
            	// 把多项式A分成奇数系数组成的n/2次多项式A[0]和偶数A[1]
				// A(x) = A[0](x^2) + x*A[1](x^2)
				// 根据w的性质，w^(i+n/2) = -w^i
				// 得A(x+n/2) = A[0](x^2) - x*A[1](x^2)
                Complex x = f[j + k], y = w * f[j + k + i];
                f[j + k] = x + y; f[j + k + i] = x - y;
            }
        }
    }
    if (sgn == -1) for (int i = 0; i < n; i++) f[i] /= n;  // 逆DFT结果除以n
	// 逆DFT证明要用到矩阵，见下方链接 
}

/*
FFT算法详解：http://www.gatevin.moe/acm/fft%E7%AE%97%E6%B3%95%E5%AD%A6%E4%B9%A0%E7%AC%94%E8%AE%B0/
题目大意：给定两个多项式，求多项式的乘积，输出系数，n<=1e6
分析：
FFT（快速傅里叶变换）能在O(nlogn)时间内解决多项式乘法问题
FFT算法本质是利用复数的一些性质和分治的思想，在O(nlogn)内解决DFT和逆DFT问题
（多项式系数表示法和点值表示法的相互转化）
而点值表示法相乘是O(n)，算法流程是先O(nlogn)转成点值表示法，O(n)相乘，再O(nlogn)转回来，总复杂度是O(nlogn) 
*/
int main() {
	int la, lb; scanf("%d%d", &la, &lb);
    for (int i = 0; i <= la; i++) scanf("%lf", &a[i].r);
    for (int i = 0; i <= lb; i++) scanf("%lf", &b[i].r);
    int m = la + lb, len;
    // FFT用在2^n次多项式比较方便，所以把n适当扩大 
    for (n = 1, len = 0; n <= m; n <<= 1, ++len);
	// 预处理蝴蝶变换，R[i]表示递归到最底层后第i位是原来的第R[i]位，R[i]=(i换成len位二进制再左右颠倒)
    for (int i = 1; i < n; i++) R[i] = R[i >> 1] >> 1 | (i & 1) << len - 1;
    FFT(a, 1); FFT(b, 1);  // 对a和b做DFT变换，把系数表示法转为点值表示法 
    for (int i = 0; i < n; i++) a[i] *= b[i];  // 点值相乘，O(n) 
    FFT(a, -1);  // 对ab乘积做逆DFT变换，把点值表示法转回系数表示法 
    for (int i = 0; i <= m; i++) c[i] = int(a[i].r + 0.5);  // 浮点可能有误差，四舍五入 
    for (int i = 0; i <= m; i++) printf("%d ", c[i]);
    putchar('\n');
    return 0;
}

