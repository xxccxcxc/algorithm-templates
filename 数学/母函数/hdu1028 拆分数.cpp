#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
const int N = 120;
int a[N+5], b[N+5];
 
int main() {  // 母函数
	/*
	题意：求拆分数n的方案数
	构造母函数，x的次数表示选的数的总和，数i用(1 + x^i + x^2i + ...)来表示（不选，选一次，选两次） 
	则拆分n的方案数为1~n的母函数相乘后，x^n的系数 
	*/ 
	for (int i = 0; i <= N; i++)
		 a[i] = 1;
	for (int i = 2; i <= N; i++) {  // 乘上(1 + x^i + x^2i + ...) 
		memset(b, 0, sizeof(b));
		for (int j = 0; j <= N; j++)
			for (int k = 0; j + k <= N; k += i)  // 枚举放几个i数，总和不能大于N 
				b[j+k] += a[j];  // a里面每一项与b里面的k次项相乘 
		memcpy(a, b, sizeof(b));
	}
	for (int n; cin >> n; )
		cout << a[n] << endl;
	return 0;
}

