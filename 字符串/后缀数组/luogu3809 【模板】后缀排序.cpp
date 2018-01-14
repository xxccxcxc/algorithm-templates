#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;
const int N = 2e6+50;
char s[N];
int n, t[N], rk[N], tmp[N], sa[N], height[N];

void GetSA() {  // 求sa,rk,height数组 

    int m = 'z' + 5;  // m是桶排的上界，可变 
    
    // 先桶排，相当于把字符离散化一下 
    for (int i = 1; i <= n; i++) t[rk[i] = s[i]]++;
    for (int i = 1; i <= m; i++) t[i] += t[i-1];
    for (int i = n; i >= 1; i--) sa[t[rk[i]]--] = i;  // 倒序循环，保证排序稳定 
    
    for (int k = 1; ; k <<= 1) {  // k表示当前要排序的串长度/2 
        int cnt = 0;
        
        // y中存储待排序二元组的第一关键字的位置 
        // 后k个串没有第二关键字，优先级最高，先放进来 
        for (int i = n - k + 1; i <= n; i++) tmp[++cnt] = i;  
        
        // 有第二关键字的二元组，按第二关键字从小到大放进来，保证双关键字排序 
        for (int i = 1; i <= n; i++) if (sa[i] > k) tmp[++cnt] = sa[i] - k;
        
        // 对第一关键字进行桶排序（rk中保存的是上一次排序的结果） 
        memset(t, 0, sizeof(int) * (m + 5));
        for (int i = 1; i <= n; i++) t[rk[tmp[i]]]++;
        for (int i = 1; i <= m; i++) t[i] += t[i-1];
        for (int i = n; i >= 1; i--) sa[t[rk[tmp[i]]]--] = tmp[i];
        
        // 把上次排序结果暂时放在tmp里（跟tmp的意义没关系），更新这次排序结果rk 
        // 这个swap只是交换指针，既省空间又省时间 
        swap(rk, tmp); rk[sa[1]] = cnt = 1;
        for (int i = 2; i <= n; i++)
            // 如果串相同则结果相同 
            rk[sa[i]] = tmp[sa[i]] == tmp[sa[i-1]] && tmp[sa[i]+k] == tmp[sa[i-1]+k] ? cnt : ++cnt;
        
        // 更新桶排上界（即不同的元素个数），若上界为n则已经排好序，没必要继续做 
        if ((m = cnt) >= n) break;
    }
    
    // height[i]>=height[i的前一名]-1，利用这个性质O(n)计算 
    for (int i = 1, k = 0, j; i <= n; height[rk[i++]] = k)
        for (k = k ? k - 1 : k, j = sa[rk[i]-1]; rk[i] != 1 && s[i+k] == s[j+k]; k++);
}

/*
题意：把字符串的所有非空后缀按字典序从小到大排序，然后按顺序输出后缀的第一个字符在原串中的位置
（即求sa数组） 
*/
int main() { 
    scanf("%s", s + 1); n = strlen(s + 1);
    GetSA();
    for (int i = 1; i <= n; i++)
        printf("%d ", sa[i]);
    putchar('\n');
    return 0;
}


