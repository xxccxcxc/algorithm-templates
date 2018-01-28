#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;
const int L = 1e6+50;
char r1[L], r2[L];
int nxt[L];

void GetNxt(char *p) {
    int lp = strlen(p + 1);
    nxt[1] = 0;
    for (int i = 2, j = 0; i <= lp; i++) {
        while (j && p[j+1] != p[i]) j = nxt[j];
        if (p[j+1] == p[i]) j++;
        nxt[i] = j;
    }
}

void Kmp(char *s, char *p) {
    GetNxt(p);
    int ls = strlen(s + 1), lp = strlen(p + 1);
    for (int i = 1, j = 0; i <= ls; i++) {
        while (j && p[j+1] != s[i]) j = nxt[j];
        if (p[j+1] == s[i]) j++;
        if (j == lp) printf("%d\n", i - lp + 1);
    }
    for (int i = 1; i <= lp; i++)
        printf("%d ", nxt[i]);
    putchar('\n');
}

int main() {
    scanf("%s%s", r1 + 1, r2 + 1);
    Kmp(r1, r2);
    return 0;
}

