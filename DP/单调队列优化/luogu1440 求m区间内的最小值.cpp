#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <deque>
#include <utility>
using namespace std;
deque< pair<int, int> > q;
int main() {
	/*
	题意：求每个数前m个数最小值
	单调队列优化dp，可以在O(n)内解决形如：
	"f[x] = max or min{g(k) | b[x] <= k < x} + w[x]
	其中b[x]随x单调不降，g[k]表示一个和k或f[k]有关的函数，w[x]表示一个和x有关的函数"
	的问题
	做法：维护一个解的优秀程度下降的单调队列（可以看成窗口），每次移动窗口就把队首过时的元素扔掉，
	队尾扔进新元素时维护单调性，则最优决策点在队首 
	*/
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1, t; i <= n; i++) {
		// pair的first代表时间，second代表值 
		while (!q.empty() && q.front().first < i - m) q.pop_front();
		if (!q.empty()) printf("%d\n", q.front().second);
		else printf("0\n");
		scanf("%d", &t);
		while (!q.empty() && q.back().second > t) q.pop_back();
		q.push_back(make_pair(i, t));
	} 
    return 0;
}

