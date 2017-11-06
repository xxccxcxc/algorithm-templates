#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 6050, MOD = 10000;
typedef int bigint[N];  // bigint表示大小为N的int数组 

void input(bigint a) {
	memset(a, 0, sizeof(int) * N);
	string s;
	cin >> s;
	while (s.size() % 4) s = '0' + s;  // 压4位，在前面补0 
	a[0] = s.size() / 4;
	for (int i = 0; i < a[0]; i++) {
		int t = 0;
		for (int j = 0; j < 4; j++)
			t = t * 10 + s[i*4+j] - '0';
		a[a[0]-i] = t;
	}
}

void clear(bigint a) {  // 处理进位和去前导0 
	for (int i = 1; i <= a[0]; i++) {
		a[i+1] += a[i] / MOD;
		a[i] %= MOD;
	}
	if (a[a[0]+1]) ++a[0];
	while (a[0] > 1 && !a[a[0]]) --a[0];
}

void print(bigint a, bool sgn=true) {
	if (!sgn) putchar('-');
	cout << a[a[0]];  // 第一位不用补0 
	for (int i = a[0] - 1; i >= 1; i--)
		printf("%04d", a[i]);  // %04d 在前面补0，补足4位 
	cout << endl;
}

void add(bigint a, bigint b, bigint c) {
	memcpy(c, a, sizeof(int) * N);
	c[0] = max(a[0], b[0]) + 1;
	for (int i = 1; i <= b[0]; i++)
		c[i] += b[i];
	clear(c);
}

bool canMinus(bigint a, bigint b) {  // return a >= b 
	if (a[0] > b[0]) return true;
	if (a[0] < b[0]) return false;
	for (int i = a[0]; i >= 1; i--)
		if (a[i] > b[i]) return true;
		else if (a[i] < b[i]) return false;
	return true;
}

bool reduce(bigint a, bigint b, bigint c) {
	bool sgn = true;
	if (!canMinus(a, b)) swap(a, b), sgn = false;
	memcpy(c, a, sizeof(int) * N);
	for (int i = 1; i <= b[0]; i++) {
		if (c[i] < b[i]) --c[i+1], c[i] += MOD;  // 借位 
		c[i] -= b[i];
	}
	clear(c);
	return sgn;
}

void mul(bigint a, bigint b, bigint c) {
	memset(c, 0, sizeof(int) * N);
	c[0] = a[0] + b[0];
	for (int i = 1; i <= a[0]; i++)
		for (int j = 1; j <= b[0]; j++) {
			// 因为压了4位，这里必须边做边进位，不然会爆int 
			c[i+j-1] += a[i] * b[j];
			c[i+j] += c[i+j-1] / MOD;
			c[i+j-1] %= MOD;
		}
	clear(c);
}

void div(bigint a, bigint b, bigint c, bigint d) {
	memset(c, 0, sizeof(int) * N);
	memset(d, 0, sizeof(int) * N);
	c[0] = a[0];
	for (int i = a[0]; i >= 1; i--) {
		// d = d * 10 + a[i]
		for (int j = ++d[0]; j >= 2; j--)
			d[j] = d[j-1];
		d[1] = a[i]; 
		while (canMinus(d, b)) {
			++c[i];
			reduce(d, b, d);  //用减来模拟除 
		}
	}
	clear(c); clear(d);
}


int main() {
	bigint a, b, c, d;
	input(a); input(b);
	add(a, b, c); print(c);
	bool sgn = reduce(a, b, c); print(c, sgn);
	mul(a, b, c); print(c);
	div(a, b, c, d); print(c); print(d);
	return 0;
}

