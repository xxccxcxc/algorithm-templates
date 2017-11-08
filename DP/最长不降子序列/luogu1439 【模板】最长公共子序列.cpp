#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 100050, INF = 0x3f3f3f3f;
int ma[N], a[N], f[N];

int main() {
	/*
	题意：给两个1~n的排列，求最长公共子序列（可以不连续）
	解法：
	3 2 1 4 5
	1 2 3 4 5
	把 3 2 1 4 5 看成 1 2 3 4 5 (3->1, 2->2, 1->3...)
	则按照映射关系，第二个序列变为 3 2 1 4 5 
	则原序列的公共子序列对应第二个序列的上升子序列
	于是套最长上升子序列 nlogn 模板 
	*/ 
	int n; cin >> n;
	for (int i = 0, r; i < n; ma[r] = i++)
		cin >> r;
	for (int i = 0; i < n; i++)
		cin >> a[i], a[i] = ma[a[i]];
	/*
	f[i]表示a[0~i]的最长上升子序列
	插入a[i]时，先用二分找出第一个>=a[i]的f[j]，然后在0~j-1的最长上升子序列后接上a[i]，即 f[j]=a[i] 
	因为往前不够优，往后接不上 
	最后答案为最后一个有值的f的位置 
	*/ 
	memset(f, 0x3f, sizeof(f));
	for (int i = 0; i < n; i++)
		*lower_bound(f, f + n, a[i]) = a[i];
	cout << lower_bound(f, f + n, INF) - f << endl;
	return 0;
}

