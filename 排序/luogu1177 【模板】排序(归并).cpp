#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;
const int N = 100050;
int a[N], b[N];

void mergeSort(int l, int r) {
	if (l == r) return;
	int mid = (l + r) >> 1;
	mergeSort(l, mid);
	mergeSort(mid+1, r);
	int i = l, j = mid + 1, k = 0;
	while (i <= mid && j <= r)
		b[k++] = a[i] < a[j] ? a[i++] : a[j++];
	while (i <= mid) b[k++] = a[i++];
	while (j <= r) b[k++] = a[j++];
	memcpy(a+l, b, sizeof(int) * (r-l+1));
}

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	mergeSort(1, n);
	for (int i = 1; i <= n; i++)
		printf("%d ", a[i]);
	printf("\n");
    return 0;
}

