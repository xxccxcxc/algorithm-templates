#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;
const int N = 100050;
int a[N];

void qsort(int l, int r) {
	int i = l, j = r, mid = a[rand()%(r-l+1)+l];  // Ëæ»úmid·ÀÖ¹±»¿¨ 
	while (i <= j) {
		while (a[i] < mid) ++i;
		while (a[j] > mid) --j;
		if (i <= j) swap(a[i++], a[j--]);
	}
	if (l < j) qsort(l, j);
	if (i < r) qsort(i, r);
}

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	qsort(1, n);
	for (int i = 1; i <= n; i++)
		printf("%d ", a[i]);
	printf("\n");
    return 0;
}

