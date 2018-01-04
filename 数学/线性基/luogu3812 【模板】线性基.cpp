#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long LL;
const int N = 51, L = 55;

struct LinearBasis{
	LL bin[L+5], b[L+5];
	
	LinearBasis() {
		memset(b, 0, sizeof(b));
		bin[0] = 1;
		for (int i = 1; i <= L; i++)
			bin[i] = bin[i-1] << 1;
	}
	
	bool Insert(LL x) {
		for (int i = L; i >= 0 && x; i--)
			if (x & bin[i]) {
				if (!b[i]) { b[i] = x; return true; }  // 如果没有数覆盖第i位，就把x选进来 
				else x ^= b[i];  // 把x的第i位消成0 
			}
		// 最后要么x被消成0，即x可以被线性基中的元素异或出来，要么x被丢进线性基 
		return false;
	}
	
	LL QueryMax(LL x=0) {  // 求x异或线性基中的元素能得到的最大值 
		for (int i = L; i >= 0; i--)
			x = max(x, x ^ b[i]);  // 从高位开始贪心选
		return x;
	}
};

/*
题意：在n个数中任取若干个数异或，求最大异或和
线性基：原集合的一个最小子集，使异或的值域与原集合相同
求出线性基后在线性基上贪心 
*/
int main() {
	int n; cin >> n;
	LinearBasis lb;
	for (int i = 1; i <= n; i++) {
		LL r; cin >> r;
		lb.Insert(r);
	}
	cout << lb.QueryMax() << endl;
	return 0;
}

