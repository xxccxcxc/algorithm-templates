#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;

int read() {  // 流氓行为，仅适用于暴力算法卡常 
	char ch; int x, sgn = 1;
	for (ch = getchar(); !isdigit(ch); ch = getchar())
		if (ch == '-') sgn = -1;
	for (x = 0; isdigit(ch); ch = getchar())
		x = x * 10 + ch - '0';
	return x * sgn;
}

void write(int x) {  // 同上 
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

int main() {
	int a = read(), b = read();
	write(a + b); putchar('\n');
    return 0;
}

