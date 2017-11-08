#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 100, S = 60;
int main() {
	/*
	题意：在n个数中任取若干个数异或，求最大异或和
	线性基：原集合的一个最小子集，使异或的值域与原集合相同
	求出线性基后在线性基上贪心 
	*/
	int n; cin >> n;
	LL a[S+5] = {0};
	for (int i = 1; i <= n; i++) {
		LL u; cin >> u;
		for (int j = S; ~j; j--)
			if (u & 1LL << j)
				if (!a[j]) { a[j] = u; break; }  // 如果没有数覆盖第j位，就把u选进来 
				else u ^= a[j];  // 把u的第j位消成0 
		// 最后要么u被消成0,，即u可以被线性基中的元素异或出来，要么u被丢进线性基 
	}
	LL ans = 0;
	for (int i = S; ~i; i--)
		ans = max(ans, ans ^ a[i]);  // 从高位开始贪心选 
	cout << ans << endl;
	return 0;
}

