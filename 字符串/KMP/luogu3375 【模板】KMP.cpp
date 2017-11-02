#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 1000050, M = 1000000;
int nxt[M];

void getNxt(const string &p) {
	nxt[0] = 0;
	for (int lp = p.size(), i = 1, j = 0; i < lp; i++) {  // i要从1开始，否则nxt[0]=1 
		while (j && p[j] != p[i]) j = nxt[j-1];
		if (p[j] == p[i]) ++j;
		nxt[i] = j;
	}
}

void kmp(const string &s, const string &p) {
	getNxt(p);
	for (int ls = s.size(), lp = p.size(), i = 0, j = 0; i < ls; i++) {
		// i是当前要匹配的位置，j是模式串失配位置 
		while (j && p[j] != s[i]) j = nxt[j-1];
		if (p[j] == s[i]) ++j;
		if (j == lp) { cout << i - lp + 2 << endl; j = nxt[j-1]; }
	}
	for (int lp = p.size(), i = 0; i < lp; i++)
		cout << nxt[i] << ' ';
	cout << endl;
}

int main() {
	string s, p;
	cin >> s >> p;
	kmp(s, p); 
	return 0;
}

