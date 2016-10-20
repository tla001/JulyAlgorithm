/*
 * DealString.cpp
 *
 *  Created on: 2016��10��17��
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
 * ����һ����ת�ַ���
 * ����һ���ַ�����Ҫ����ַ���ǰ������ɸ��ַ��ƶ����ַ�����β����
 * ����ַ�����abcdef��ǰ���2���ַ�'a'��'b'�ƶ����ַ�����β����
 * ʹ��ԭ�ַ�������ַ�����cdefab������дһ��������ɴ˹��ܣ�
 * Ҫ��Գ���Ϊn���ַ���������ʱ�临�Ӷ�Ϊ O(n)���ռ临�Ӷ�Ϊ O(1)��
 */
//������λ
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
//������ת
/*
 * ���磬�ַ��� abcdef ����Ҫ��def��ת��abc��ǰͷ��ֻҪ��������3������������ɣ�
 ���Ƚ�ԭ�ַ�����Ϊ�������֣���X:abc��Y:def��
 ��X��ת��X->X^T�����ã�abc->cba����Y��ת��Y->Y^T�����ã�def->fed��
 ��ת��������õ��Ľ���ַ���X^TY^T������ת�ַ���cbafed�������֣�cba��fed�����跴ת��
 cbafed�õ�defabc����ʽ����ʾΪ(X^TY^T)^T=YX�����ʵ����������ת��
 ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�ΪO(1)
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
 * ��������ַ�������
 * ���������ֱ�����ĸ��ɵ��ַ���A���ַ���B���ַ���B�ĳ��ȱ��ַ���A�̡�
 * ���ʣ���������ж��ַ���B��������ĸ�Ƿ����ַ���A�
 */
/*
 * ���string2��ÿһ���ַ��������string1��ÿ���ַ��Ƚϣ������Ƿ���String1��
 * ����n���ַ���String1�ĳ��ȣ�m���ַ���String2�ĳ��ȣ���ô���㷨����ҪO(n*m)�β���
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
 * �ȶ��������ַ�������ĸ��������Ȼ����ͬʱ�������ִ�������ѯ��
 * �����ִ���������Ҫ(�������)O(m log m) + O(n log n)�β�����
 * ֮�������ɨ����ҪO(m+n)�β���
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
 *�Ȱѳ��ַ���a�е������ַ�������һ��Hashtable�Ȼ����ѯ���ַ���b��
 *�����ַ���b��ÿ���ַ��Ƿ���Hashtable���������ڣ�˵�����ַ���a�������ַ���b������˵����������
 *���������ʵ������һ������������hashtable���ռ临�Ӷ�ΪO(1)��ʱ�临�ӶȻ���O(n + m)��
 *
 */
bool StrContain3(string &a, string &b) {
	int hash = 0;
	for (int i = 0; i < a.length(); i++) {
		hash |= (1 << (a[i] - 'a')); //��Сд��ĸ��������
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
 * ���������ַ���ת��������
 *����һ����������ɵ��ַ���������ת������������������磺�����ַ���"123"���������123��
 */
int StrToInt(char *str) {
	static const int MAX_INT = (int) ((unsigned int) ~0 >> 1);
	static const int MIN_INT = -(int) ((unsigned) ~0 >> 1) - 1;
	unsigned int n = 0;

	//�ж��Ƿ�����Ϊ��
	if (str == NULL) {
		return 0;
	}
	//����ո�
	while (isspace(*str))
		++str;
	//��������
	int sign = 1;
	if (*str == '+' || *str == '-') {
		if (*str == '-')
			sign = -1;
		str++;
	}
	//ȷ�������ֺ��ٽ��к�������
	while (isdigit(*str)) {
		//�������
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
