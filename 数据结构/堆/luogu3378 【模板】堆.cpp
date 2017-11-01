#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;
const int N = 1000050;

int heap[N], siz = 0;  // Ð¡¸ù¶Ñ 

void push(int val) {
	heap[++siz] = val;
	int u = siz;
	while (u > 1) {
		int fa = u >> 1;
		if (heap[fa] <= val) break;
		swap(heap[u], heap[fa]);
		u = fa;
	}
}

int top() {
	return heap[1];
}

void pop() {
	heap[1] = heap[siz--];
	int u = 1, son;
	while ((son = u << 1) <= siz) {
		if (son < siz && heap[son+1] < heap[son]) ++son;
		if (heap[u] < heap[son]) break;
		swap(heap[u], heap[son]);
		u = son;
	}
}

int main() {
	int m;
	scanf("%d", &m);
	for (int opt, val; m--; ) {
		scanf("%d", &opt);
		if (opt == 1) {
			scanf("%d", &val);
			push(val);
		}
		else if (opt == 2) printf("%d\n", top());
		else pop();
	}
    return 0;
}

