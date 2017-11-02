#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 11000050;
char r[N], t[N<<1];
// string可能会TLE
// 预处理后的串空间要记得开两倍 
int len[N<<1];

char* init(char *a) {
	t[0] = '^'; t[1] = '#';
	int la = strlen(a);
	for (int i = 0; i < la; i++)
		t[(i<<1)+2] = a[i], t[(i<<1)+3] = '#';
	t[(la<<1)+2] = '$'; t[(la<<1)+3] = '\0';
	return t;
}

int manacher(char *a) {
	char *s = init(a);
	int ret = 0, mx = 0, id;
	for (int ls = strlen(s), i = 0; i < ls; i++) {
		len[i] = i < mx ? min(len[(id<<1)-i], mx-i) : 1;
		// i+len在mx以内（当前串在之前的大回文串之内）才能保证正确性 
		while (s[i+len[i]] == s[i-len[i]]) ++len[i];
		if (i + len[i] > mx) mx = i + len[i], id = i;
		ret = max(ret, len[i] - 1);
		// 回文串真正长度 = len-1 
		// #a#b#a#   len=4 ans=3
		// #a#b#b#a# len=5 ans=4
	}
	return ret;
}

int main() {
	scanf("%s", r);
	printf("%d\n", manacher(r));
	return 0;
}

