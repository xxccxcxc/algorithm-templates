#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <queue> 
using namespace std;
const int N = 100050;

struct Trie {
	int num, cnt, ch[10];
}tr[N<<4];
int trTop = 2;

void insert(const string &s) {
	int u = 1;
	for (int i = 0; i < s.size(); i++) {
		int v = s[i] - '0';
		if (!tr[u].ch[v]) {
			tr[u].ch[v] = trTop++;
			tr[tr[u].ch[v]].num = tr[u].num * 10 + v;
		}
		u = tr[u].ch[v];
	}
	++tr[u].cnt;
}

void bfs() {
	queue<int> q; q.push(1);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int i = 0; i < tr[u].cnt; i++)
			cout << tr[u].num << ' ';
		for (int i = 0; i < 10; i++)
			if (tr[u].ch[i]) q.push(tr[u].ch[i]);
	}
}

int main() {
	int n;
	cin >> n;
	for (string s; n--; insert(s))
		cin >> s;
	bfs();
	return 0;
}

