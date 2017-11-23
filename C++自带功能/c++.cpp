#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <set>
#include <utility>
using namespace std;

void testVector() {
	vector<int> a;
	
	for (int i = 0; i < 10; i++)
		a.push_back(i);
		
	a.pop_back();  // 删除末尾元素 
	
	a.erase(a.begin()+5);  // 删除a[5] 
	a.erase(a.begin()+1, a.begin()+3);  // 删除[1,3)区间 
	
	for (vector<int>::iterator it = a.begin(); it != a.end(); it++)
		cout << *it << ' ';  // 0 3 4 6 7 8
	cout << endl;
	
	for (int siz = a.size(), i = 0; i < siz; i++)
		cout << a[i] << ' ';  // 0 3 4 6 7 8
	cout << endl;
	
	for (vector<int>::reverse_iterator rit = a.rbegin(); rit != a.rend(); rit++)
		cout << *rit << ' ';  // 8 7 6 4 3 0
		
	cout << endl << a.front() << ' ' << a.back() << a.empty() << endl;  // 0 8 0
	
	vector<int> b(a);  // STL好像都可以这么赋值 
	for (int siz = b.size(), i = 0; i < siz; i++)
		cout << b[i] << ' ';  // 0 3 4 6 7 8
	cout << endl << (b == a) << endl;  // 1
	
	a.clear();
	
	vector<int> c(b.begin()+1, b.begin()+3);
	for (int siz = c.size(), i = 0; i < siz; i++)
		cout << c[i] << ' ';  // 3 4
	cout << endl;
	
	vector<int> d(5, 2);
	for (int siz = d.size(), i = 0; i < siz; i++)
		cout << d[i] << ' ';  // 2 2 2 2 2
}

void testStack() {
	stack<int> a;
	cout << a.size() << ' ' << a.empty() << endl;  // 0 1
	for (int i = 0; i < 5; i++)
		a.push(i);
	cout << a.top() << endl;  // 4
	a.pop();
}

void testQueue() {
	queue<int> a;
	
	for (int i = 0; i < 10; i++)
		a.push(i);
	
	cout << a.front() << ' ' << a.back() << endl;  // 0 9
	
	a.pop();  // pop 0
	cout << a.front() << endl;  // 1
	
	cout << a.size() << ' ' << a.empty() << endl;  // 9 0
}

void testDeque() {
	deque<int> a;
	for (int i = 0; i < 5; i++)
		a.push_back(i);
	a.pop_back();
	a.pop_front();
	a.push_front(5);
	for (int siz = a.size(), i = 0; i < siz; i++)
		cout << a[i] << ' ';  // 5 1 2 3
	cout << endl;
	// 其他同vector 
}

void testMap() {
	map<int, string> a;
	a[1] = "one";
	cout << a.size() << endl;  // 1
	a[2];
	cout << a.size() << endl;  // 2
	cout << a.count(1) << endl;  // 1
	
	map<int, string>::iterator it = a.find(1);
	if (it != a.end()) a.erase(it);
	cout << a.count(1) << endl;  // 0
	
	a[1] = "one";
	a[2] = "two";
	for (map<int, string>::iterator it = a.begin(); it != a.end(); it++)
		cout << it->first << ' ' << it->second << endl;  // 1 one 2 two
	
	a.clear();
}

void testSet() {
	set<int> a;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 2; j++)
			a.insert(i);
			
	for (set<int>::iterator it = a.begin(); it != a.end(); it++)
		cout << *it << ' ';  // 0 1 2 3 4
	cout << endl;
	
	a.erase(1);
	for (set<int>::iterator it = a.begin(); it != a.end(); it++)
		cout << *it << ' ';  // 0 2 3 4
	cout << endl;
	
	cout << a.count(1) << ' ' << a.count(2) << endl;  // 0 1
	
	int b[5] = {5, 6, 7, 8, 9};
	a.insert(b, b+5);
	for (set<int>::iterator it = a.begin(); it != a.end(); it++)
		cout << *it << ' ';  // 0 2 3 4 5 6 7 8 9
	cout << endl;
	
	cout << *a.lower_bound(2) << ' ' << *a.upper_bound(2) << endl;  // 2 3
}

void testString() {
	string a = "abc";
	a.insert(1, "def");
	cout << a << endl;  // adefbc
	a.replace(1, 2, "ghi");
	cout << a << endl;  // aghifbc
	cout << a.substr(3, 2) << endl;  // if
	cout << a.find('g') << endl;  // 1
	cout << a.find("ghi") << endl;  // 1
	int pos = a.find('j');
	if (pos < 0 || pos >= a.size()) cout << "not find" << endl;  // not find
	string d = "abcba";
	cout << d.find("b", 1) << ' ' << d.find("b", 2) << endl;  // 1 3
	char c[10];
	strcpy(c, d.c_str());
	c[1] = 'z';
	cout << c << endl;  // azcba
	char s[10] = "123";
	a = s;
	cout << a << endl;  // 123
	string e;
	getline(cin, e);  // input: 123 456
	cout << e << endl;   // 123 456
}

void testPair() {  // 头文件utility 
	pair<int, string> a(1, "one");
	pair<int, string> b = make_pair(2, "two");
	cout << a.first << ' ' << a.second << endl;
}

void testChar() {
	char a[10] = "abc", b[10] = "123";
	strcat(a, b);
	cout << a << endl;  // abc123
	strncat(a, a, 1);
	cout << a << endl;  // abc123a
	char c[10];
	strcpy(c, b);
	cout << c << endl;  // 123
	strncpy(c, a, 4);  // 把a前4个字符复制到c，若strlen(a)>strlen(c)则不在a后加'\0' 
	c[4] = '\0';
	cout << c << endl;  // abc1
	cout << strcmp("abc", "abd") << endl;  // 返回一个<0的数
	// a<b则返回值<0，a=b则返回值=0，a>b则返回值>0
	cout << strncmp("abcd", "abcef", 3) << endl;  // 0
	cout << strlen("abc") << endl;  // 3
	char d[10] = "aBc";
	strlwr(d);
	cout << d << endl;  // abc
	strupr(d);
	cout << d << endl;  // ABC
}

void testOther() {
	string a = "123";
	int b;
	sscanf(a.c_str(), "%d", &b);
	cout << b << endl;  // 123
	char c[10];
	sprintf(c, "%d", b);
	cout << c << endl;  // 123
	string d = c;
	cout << d << endl;  // 123
	
	int e[5] = {0, 1, 2, 3, 4};
	cout << lower_bound(e, e+5, 2) - e << endl;  // 2
	
	reverse(e, e+5);
	for (int i = 0; i < 5; i++)
		cout << e[i] << ' ';  // 4 3 2 1 0
	cout << endl;
	
	int f[5] = {1, 2, 3, 4, 5};
	random_shuffle(f, f+5);
	for (int i = 0; i < 5; i++)
		cout << f[i] << ' ';  // 打乱后的数组 
	cout << endl;
	
	int g[5] = {2, 4, 5, 1, 3};
	nth_element(g, g+3, g+5);  // 把g[3]置为升序排列应该放在g[3]的值，并且左边比g[3]小，右边比g[3]大 
	for (int i = 0; i < 5; i++)
		cout << g[i] << ' ';
	cout << endl;
	
	int h[5] = {3, 2, 4, 5, 1};
	next_permutation(h, h+5);
	for (int i = 0; i < 5; i++)
		cout << h[i] << ' ';  // 3 2 5 1 4
	cout << endl;
	prev_permutation(h, h+5);
	for (int i = 0; i < 5; i++)
		cout << h[i] << ' ';  // 3 2 4 5 1
	cout << endl;
	do {
		//do sth
	}while (next_permutation(h, h+5));  // 不成功返回false 
	
	int t[5] = {2, 4, 3, 2, 5};
	sort(t, t+5);
	cout << lower_bound(t, t+5, 2) - t << ' ' << upper_bound(t, t+5, 2) - t << endl;  // 0 2
	
	int r[5] = {0, 1, 2, 3, 4};
	fill(r, r+5, -1);  // 头文件<algorithm> 
	for (int i = 0; i < 5; i++)
		cout << r[i] << ' ';  // -1 -1 -1 -1 -1
	cout << endl;
	
	fill_n(r, 3, 5);
	for (int i = 0; i < 5; i++)
		cout << r[i] << ' ';  // 5 5 5 -1 -1
	cout << endl;
}

int main() {
	//testVector();
	//testStack();
	//testQueue();
	//testDeque();
	//testMap();
	//testSet();
	//testString();
	//testPair();
	//testChar();
	//testOther();
	return 0;
}

