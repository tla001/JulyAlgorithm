/*
 * DealString.cpp
 *
 *  Created on: 2016年10月17日
 *      Author: tla001
 */

#include "DealString.h"

void PrintStr(char *s) {
	int i = 0;
	while (s[i] != '\0') {
		cout << s[i];
		i++;
	}
	cout << endl;
}

/*
 * 问题一：旋转字符串
 * 给定一个字符串，要求把字符串前面的若干个字符移动到字符串的尾部，
 * 如把字符串“abcdef”前面的2个字符'a'和'b'移动到字符串的尾部，
 * 使得原字符串变成字符串“cdefab”。请写一个函数完成此功能，
 * 要求对长度为n的字符串操作的时间复杂度为 O(n)，空间复杂度为 O(1)。
 */
//暴力移位
void StrLeftShiftOne(char *s, int n) {
	char temp = s[0];
	for (int i = 1; i < n; i++) {
		s[i - 1] = s[i];
	}
	s[n - 1] = temp;
}
void StrLeftRotate1(char *s, int n, int m) {
	while (m--) {
		StrLeftShiftOne(s, n);
	}
}
//三步反转
/*
 * 例如，字符串 abcdef ，若要让def翻转到abc的前头，只要按照下述3个步骤操作即可：
 首先将原字符串分为两个部分，即X:abc，Y:def；
 将X反转，X->X^T，即得：abc->cba；将Y反转，Y->Y^T，即得：def->fed。
 反转上述步骤得到的结果字符串X^TY^T，即反转字符串cbafed的两部分（cba和fed）给予反转，
 cbafed得到defabc，形式化表示为(X^TY^T)^T=YX，这就实现了整个反转。
 时间复杂度为O(n)，空间复杂度为O(1)
 */
void StrReverseString(char *s, int from, int to) {
	while (from < to) {
		char t = s[from];
		s[from++] = s[to];
		s[to--] = t;
	}
}
void StrLeftRotate2(char *s, int n, int m) {
	m %= n;
	StrReverseString(s, 0, m - 1);
	StrReverseString(s, m, n - 1);
	StrReverseString(s, 0, n - 1);
}
void StrSolveTest_1() {
	char s[] = "abcde";
	int n = sizeof(s) / sizeof(s[0]);
	int m = 3;
	//StrLeftRotate1(s, n - 1, m);
	StrLeftRotate2(s, n - 1, m);
	PrintStr(s);
}
/*
 * 问题二：字符串包含
 * 给定两个分别由字母组成的字符串A和字符串B，字符串B的长度比字符串A短。
 * 请问，如何最快地判断字符串B中所有字母是否都在字符串A里？
 */
/*
 * 针对string2中每一个字符，逐个与string1中每个字符比较，看它是否在String1中
 * 假设n是字符串String1的长度，m是字符串String2的长度，那么此算法，需要O(n*m)次操作
 */
bool StrContain1(string &a, string &b) {
	for (int i = 0; i < b.length(); i++) {
		int j;
		for (j = 0; j < a.length(); j++) {
			if (b[i] == a[j])
				break;
		}
		if (j >= a.length())
			return false;
	}
	return true;
}
/*
 * 先对这两个字符串的字母进行排序，然后再同时对两个字串依次轮询。
 * 两个字串的排序需要(常规情况)O(m log m) + O(n log n)次操作，
 * 之后的线性扫描需要O(m+n)次操作
 */
bool StrContain2(string &a, string &b) {
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());

	for (int pa = 0, pb = 0; pb < b.length();) {
		while ((pa < a.length()) && (a[pa] < b[pb])) {
			pa++;
		}
		if (pa >= a.length() || a[pa] > b[pb]) {
			return false;
		}
		pb++;
	}
	return true;
}
/*
 *先把长字符串a中的所有字符都放入一个Hashtable里，然后轮询短字符串b，
 *看短字符串b的每个字符是否都在Hashtable里，如果都存在，说明长字符串a包含短字符串b，否则，说明不包含。
 *这个方法的实质是用一个整数代替了hashtable，空间复杂度为O(1)，时间复杂度还是O(n + m)。
 *
 */
bool StrContain3(string &a, string &b) {
	int hash = 0;
	for (int i = 0; i < a.length(); i++) {
		hash |= (1 << (a[i] - 'a')); //对小写字母建立索引
	}
	for (int i = 0; i < b.length(); i++) {
		if ((hash & (1 << (b[i] - 'a'))) == 0) {
			return false;
		}
	}
	return true;
}
void StrSolveTest_2() {
	string a = "akfbcde";
	string b = "dfve";
	//bool ret = StrContain1(a, b);
	//bool ret = StrContain2(a, b);
	bool ret = StrContain3(a, b);
	cout << "ret= " << ret << endl;
}
/*
 * 问题三：字符串转换成整数
 *输入一个由数字组成的字符串，把它转换成整数并输出。例如：输入字符串"123"，输出整数123。
 */
int StrToInt(char *str) {
	static const int MAX_INT = (int) ((unsigned int) ~0 >> 1);
	static const int MIN_INT = -(int) ((unsigned) ~0 >> 1) - 1;
	unsigned int n = 0;

	//判断是否输入为空
	if (str == NULL) {
		return 0;
	}
	//处理空格
	while (isspace(*str))
		++str;
	//处理正负
	int sign = 1;
	if (*str == '+' || *str == '-') {
		if (*str == '-')
			sign = -1;
		str++;
	}
	//确定是数字后再进行后续操作
	while (isdigit(*str)) {
		//处理溢出
		int c = *str - '0';
		if (sign > 0
				&& (n > MAX_INT / 10 || (n == MAX_INT / 10 && c > MAX_INT % 10))) {
			n = MAX_INT;
			break;
		} else if (sign < 0
				&& (n > (unsigned) MIN_INT / 10
						|| (n == (unsigned) MIN_INT
								&& c > (unsigned) MIN_INT % 10))) {
			n = MIN_INT;
			break;
		}
		n = n * 10 + c;
		str++;
	}
	return sign > 0 ? n : -n;
}
void StrSolveTest_3() {
	char str[] = " -155884";
	cout << StrToInt(str) << endl;
}
/*
 * 问题四：回文判断
 *判断一个字串是否是回文？
 */
/*
 * 同时从字符串头尾开始向中间扫描字串，如果所有字符都一样，那么这个字串就是一个回文。
 * 采用这种方法的话，我们只需要维护头部和尾部两个扫描指针即可
 * 时间复杂度：O(n)，空间复杂度：O(1)。
 */
bool Ispalindrome(char *str) {
	if (str == NULL)
		return false;
	int length = strlen(str);
	//cout << "length= " << length << endl;
	int head = 0;
	int tail = length - 1;
	while (head <= tail) {
		if (str[head] == str[tail]) {
			head++;
			tail--;
		} else {
			return false;
		}
	}
	return true;
}
/*
 * 先从中间开始、然后向两边扩展查看字符是否相等
 *
 */
bool Ispalindrome2(char *str) {
	if (str == NULL)
		return false;
	int length = strlen(str);
	int mid;
	int tohead;
	int totail;
	if (length % 2 == 0) {
		mid = length / 2;
		tohead = mid - 1;
		totail = mid;
	} else {
		mid = (length - 1) / 2;
		tohead = mid - 1;
		totail = mid + 1;
	}
	while (tohead >= 0) {
		if (str[tohead--] != str[totail++])
			return false;
	}
	return true;
}
void StrSolveTest_4() {
	char str[20];
	cout << "input :" << endl;
	while (cin >> str) {
		if (str != NULL) {
			cout << "ret = " << Ispalindrome2(str) << endl;
		} else
			cout << "redo " << endl;
	}
}
/*
 * 问题五：最长回文子串
 *给定一个字符串，求它的最长回文子串的长度。
 */
/*
 * 如果一段字符串是回文，那么以某个字符为中心的前缀和后缀都是相同的
 * 可以枚举中心位置，然后再在该位置上用扩展法，记录并更新得到的最长的回文长度
 */
int LongestPalindrom(const char *str) {
	if (str == NULL)
		return 0;
	int length = strlen(str);
	int max = 0;
	int c = 0;
	for (int i = 0; i < length; i++) {
		for (int j = 0; (i - j >= 0) && (i + j) < length; j++) {
			if (str[i - j] != str[i + j])
				break;
			c = 2 * j + 1;
		}
		if (c > max)
			max = c;
		for (int j = 0; (i - j >= 0) && (i + j) < length; j++) {
			if (str[i - j] != str[i + j + 1])
				break;
			c = 2 * j + 2;
		}
		if (c > max)
			max = c;
	}
	return max;
}
/*
 * Manacher算法，且这个算法求最长回文子串的时间复杂度是线性O(N)的。
 */
int LongestPalindrom2(const char *str) {

}
void StrSolveTest_5() {
	char str[20];
	cout << "input :" << endl;
	while (cin >> str) {
		if (str != NULL) {
			cout << "ret = " << LongestPalindrom(str) << endl;
		} else
			cout << "redo " << endl;
	}
}
/*
 * 问题六：字符串的全排列
 *输入一个字符串，打印出该字符串中字符的所有排列。
 *例如输入字符串abc，则输出由字符a、b、c 所能排列出来的所有字符串
 *abc、acb、bac、bca、cab 和 cba
 */
/*
 * 从集合中依次选出每一个元素，作为排列的第一个元素，
 * 然后对剩余的元素进行全排列，如此递归处理，从而得到所有元素的全排列
 * O(n!)
 */
void CalcAllPermutation(char* perm, int from, int to) {
	if (to <= 1) {
		return;
	}
	if (from == to) {
		for (int i = 0; i <= to; i++)
			cout << perm[i];
		cout << endl;
	} else {
		for (int j = from; j <= to; j++) {
			swap(perm[j], perm[from]);
			CalcAllPermutation(perm, from + 1, to);
			swap(perm[j], perm[from]);
		}
	}
}
void StrSolveTest_6() {
	char str[] = "abc";
	CalcAllPermutation(str, 0, strlen(str) - 1);
}
