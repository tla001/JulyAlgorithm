/*
 * DealArr.cpp
 *
 *  Created on: 2016��10��25��
 *      Author: tla001
 */

#include "DealArr.h"

/*
 * ����һ��Ѱ����С��k����
 *����n�����������������С��k����
 */
#define CUTOFF 2
void DirectInsertSort(int a[], int n) {
	for (int i = 1; i < n; i++) {
		if (a[i] < a[i - 1]) { //�ҵ�С��
			int j = i - 1;
			int x = a[i]; //����Ϊ�ڱ������洢������Ԫ��
			a[i] = a[i - 1]; //��������һ��
			while (x < a[j] && j > -1) {
				a[j + 1] = a[j]; //�ҵ�С��Ӧ���ڵ�λ��
				j--;
			}
			a[j + 1] = x; //����С��
		}
	}
}
void swap(int &a, int &b) {
	int temp;
	temp = a;
	a = b;
	b = temp;
}
int median3(int a[], int left, int right) {
	int center = (left + right) / 2;
	if (a[left] > a[center]) {
		swap(a[left], a[center]);
	}
	if (a[right] < a[center]) {
		swap(a[right], a[center]);
	}
	//if (a[left] > a[right]) {
	//    swap1(&a[left], &a[right]);
	//}
	if (a[left] > a[center]) {
		swap(a[left], a[center]);
	}
	swap(a[center], a[right - 1]);
	return a[right - 1];
}
void print(int a[], int size) {
	for (int i = 0; i < size; i++)
		cout << a[i] << "\t";
	cout << endl;
}
//ѡ��ǰk��С��������a[0]--a[k-1]
//QuickSelect ����kС��Ԫ�ط��� a[k-1]
void QuickSelect(int a[], int k, int left, int right) {
	int i, j;
	int pivot;

	if (left + CUTOFF <= right) {
		pivot = median3(a, left, right);
		//ȡ������ֵ��Ϊ��ŦԪ�����Ժܴ�̶��ϱ�������
		i = left;
		j = right - 1;
		for (;;) {
			while (a[++i] < pivot) {
			}
			while (a[--j] > pivot) {
			}
			if (i < j)
				swap(a[i], a[j]);
			else
				break;
		}
		//������ŦԪ
		swap(a[i], a[right - 1]);

		if (k <= i)
			QuickSelect(a, k, left, i - 1);
		else if (k > i + 1)
			QuickSelect(a, k, i + 1, right);
	} else
		DirectInsertSort(a + left, right - left + 1);
}
//ѡ����k��С��
int quickfindk(int a[], int k, int left, int right) {
	QuickSelect(a, k, left, right);
	return a[k - 1];
}
int QuickSelect1(int a[], int k, int left, int right) {
	int i, j;
	int pivot;
	pivot = a[left];
	i = left;
	j = right + 1;
	for (;;) {
		while (a[++i] < pivot) {
		}
		while (a[--j] > pivot) {
		}
		if (i < j)
			swap(a[i], a[j]);
		else
			break;
	}
	//������ŦԪ
	swap(a[j], a[left]);

	if (k - 1 == j - left)
		return a[j];
	else if (k <= j - left)
		return QuickSelect1(a, k, left, j - 1);
	else
		return QuickSelect1(a, k - (j - left + 1), j + 1, right);
}
void QuickSort(int a[], int left, int right) {
	int i, j;
	int pivot;

	if (left + CUTOFF <= right) {
		pivot = median3(a, left, right);
		//ȡ������ֵ��Ϊ��ŦԪ�����Ժܴ�̶��ϱ�������
		i = left;
		j = right - 1;
		for (;;) {
			while (a[++i] < pivot) {
			}
			while (a[--j] > pivot) {
			}
			if (i < j)
				swap(a[i], a[j]);
			else
				break;
		}
		//������ŦԪ
		swap(a[i], a[right - 1]);

		QuickSort(a, left, i - 1);
		QuickSort(a, i + 1, right);
	} else
		DirectInsertSort(a + left, right - left + 1);
}
void QuickSort1(int a[], int k, int left, int right) {
	int i, j;
	int pivot;
	pivot = a[left];
	i = left;
	j = right + 1;
	for (;;) {
		while (a[++i] < pivot) {
		}
		while (a[--j] > pivot) {
		}
		if (i < j)
			swap(a[i], a[j]);
		else
			break;
	}
	//������ŦԪ
	swap(a[j], a[left]);

//	if (k - 1 == j - left)
//		return a[j];
	if (k <= j - left)
		QuickSort1(a, k, left, j - 1);
	else if (k > j - left + 1)
		QuickSort1(a, k - (j - left + 1), j + 1, right);
}
void ArrSolveTest_1() {
	int a[] = { 2, 7, 3, 0, 4, 5 };
	int size = sizeof(a) / sizeof(a[0]);
//	swap(a[0], a[1]);
//	print(a, size);

	int k = 4;
//	QuickSort(a, 0, size - 1);
	QuickSort1(a, k, 0, size - 1);
	//QuickSelect(a, k, 0, size - 1);
	//QuickSelect1(a, k, 0, size - 1);
	//cout << quickfindk(a, k, 0, size - 1) << endl;
	//cout << QuickSelect1(a, k, 0, size - 1) << endl;
	print(a, size);
}
/*
 * ����� ��������������
 * ����һ���������飬������������Ҳ�и�����������������һ�������������һ�������飬
 * ÿ�������鶼��һ���͡� ������������ĺ͵����ֵ��Ҫ��ʱ�临�Ӷ�ΪO(n)��
 *	�������������Ϊ  1, -2, 3, 10, -4, 7, 2, -5  ��������������Ϊ
 *	 3, 10, -4, 7, 2  �� ������Ϊ��������ĺ�18��
 */
/*
 * ����forѭ��������������������ÿһ��������ĺͣ����������Щ�����������һ��ֵ
 * �˷�����ʱ�临�Ӷ�ΪO(n^3)��
 */
int MaxSubArray(int *A, int n) {
	int maxSum = A[0];
	int curSum = 0;
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			for (int k = i; k < j; k++) {
				curSum += A[k];
			}
			if (curSum > maxSum)
				maxSum = curSum;
			curSum = 0;
		}
	}
	return maxSum;
}
/*
 * �Ե�j+1��Ԫ��������ѡ��Ҫô����ǰ���ҵ��������飬Ҫô��Ϊ��������ĵ�һ��Ԫ�أ�
 *���currSum���ϵ�ǰԪ��a[j]��С��a[j]������currSum����a[j]��
 *   ����currSum���¸�ֵ����Ϊ��һ��Ԫ�أ���currSum = a[j]��
 *ͬʱ����currSum > maxSum�������maxSum = currSum�����򱣳�ԭֵ�������¡�
 */
int MaxSubArray1(int *A, int n) {
	int maxSum = A[0];
	int curSum = 0;
	for (int i = 0; i < n; i++) {
		curSum = (A[i] > curSum + A[i]) ? A[i] : curSum + A[i];
		maxSum = (curSum > maxSum) ? curSum : maxSum;
	}
	return maxSum;
}
void ArrSolveTest_2() {
	int a[] = { 1, -2, 3, 10, -4, 7, 2, -5 };
	int n = sizeof(a) / sizeof(a[0]);
	cout << MaxSubArray1(a, n) << endl;
}
/*
 * ������ Ѱ�Һ�Ϊ��ֵ��������
 * �������������ģ�������(N log N)��Ȼ��������ָ��i��j������ָ���������β���ˣ���i=0��j=n-1��Ȼ��i++��j--������ж�a[i]+a[j]?=sum��

 ���ĳһ��a[i]+a[j] > sum����Ҫ��취��sum��ֵ��С�����Դ˿�i������j--��
 ���ĳһ��a[i]+a[j] < sum����Ҫ��취��sum��ֵ�������Դ˿�i++��j������
 ���ԣ����������ʱ��ʱ�临�Ӷ�����ΪO(N log N + N)=O(N log N)��

 ���ԭ����������ģ�����Ҫ���ȵ�����ֱ������ָ��ֱ��ͷ��β���м�ɨ�裬O(N)�㶨���ҿռ临�ӶȻ���O(1)
 */
void QuickSortF(int a[], int left, int right) {
	if (left > right)
		return;
	int proKey = a[left];
	int i, j;
	i = left;
	j = right;
	while (i != j) {
		while (a[j] >= proKey && j > i) {
			j--;
		}
		while (a[i] <= proKey && i < j) {
			i++;
		}
		if (i < j) {
			int temp = a[i];
			a[i] = a[j];
			a[j] = temp;
		}
	}
	a[left] = a[i];
	a[i] = proKey;
	//��ʾ����켣
	//PrintQuickSort(a, 10, i);
	QuickSort(a, left, i - 1);
	QuickSort(a, i + 1, right);
}
void TwoSum(int data[], unsigned int length, int sum) {
	//�������������Ҫ��������
	QuickSortF(data, 0, length - 1);
	int begin = 0;
	int end = length - 1;
	//���������м�ƽ�
	while (begin < end) {
		long curSum = data[begin] + data[end];
		if (curSum == sum) {
			printf("%d %d\n", data[begin], data[end]);
			break;
		} else {
			if (curSum < sum)
				begin++;
			else
				end--;
		}
	}
}
void ArrSolveTest_3() {
	int a[] = { 1, 7, 2, 3, 0, 12, 5 };
	int length = sizeof(a) / sizeof(a[0]);
	int sum = 9;
	TwoSum(a, length, sum);
}
/*
 * �����ģ�Ѱ�Һ�Ϊ��ֵ�Ķ����
 * ������������n��sum��������1��2��3.......n ������ȡ��������
 * ʹ��͵���sum��Ҫ���������еĿ�������г���
 */
/*
 * ע�⵽ȡn���Ͳ�ȡn�����𼴿ɣ������Ƿ�ȡ��n�����Ĳ��ԣ�����ת��Ϊһ��ֻ��ǰn-1������ص����⡣

 ���ȡ��n��������ô�����ת��Ϊ��ȡǰn-1����ʹ�����ǵĺ�Ϊsum-n������Ӧ�Ĵ���������sumOfkNumber(sum - n, n - 1)��
 �����ȡ��n��������ô�����ת��Ϊ��ȡǰn-1����ʹ�����ǵĺ�Ϊsum������Ӧ�Ĵ������ΪsumOfkNumber(sum, n - 1)��
 */

void SumOfKNum(list<int>&list, int sum, int n) {
	if (n <= 0 || sum <= 0)
		return;
	if (sum == n) {
		//cout << "find" << endl;
		list.reverse();
		for (std::list<int>::iterator ite = list.begin(); ite != list.end();
				ite++) {
			cout << *ite << " +";
		}
		cout << n << endl;
		list.reverse();
	}
	list.push_front(n);
	SumOfKNum(list, sum - n, n - 1);
	list.pop_front();
	SumOfKNum(list, sum, n - 1);
}
void ArrSolveTest_4() {
	list<int> list;
	int sum = 20;
	int n = 50;
	SumOfKNum(list, sum, n);
}
/*
 * �����壺����������
 *
 */
/*
 * һ��ǰָ��begin��һ����ָ��current��һ����ָ��end��currentָ����������������У���

 currentָ����ָԪ��Ϊ0ʱ����beginָ����ָ��Ԫ�ؽ���������current++��begin++ ��
 currentָ����ָԪ��Ϊ1ʱ�������κν��������򲻶���������current++ ��
 currentָ����ָԪ��Ϊ2ʱ����endָ����ָ��Ԫ�ؽ���������currentָ�벻����end--
 */
void calHeLan(vector<int> &arr) {
	int begin = 0;
	int end = arr.size() - 1;
	int current = 0;
	while (current <= end) {
		if (arr[current] == 0) {
			swap(arr[current], arr[begin]);
			current++;
			begin++;
		} else if (arr[current] == 1) {
			current++;
		} else {
			swap(arr[current], arr[end]);
			end--;
		}
	}
}
void ArrSolveTest_5() {
	int a[] = { 1, 2, 0, 2, 0, 2, 1, 1, 0 };
	int size = sizeof(a) / sizeof(a[0]);
	vector<int> arr(a, a + size);
	calHeLan(arr);
	for (int i = 0; i < arr.size(); i++) {
		cout << arr[i] << "\t";
	}
	cout << endl;
}
/*
 * ���������������
 * ����ʵ�־���˷��������ǵ������ģ�ϴ�ʱ���Ż�������
 */
void ArrSolveTest_6() {

}
/*
 * �����ߣ�����ϴ���㷨
 *
 */
/*
 * ��i��Ԫ��ȥ�˵� (2 * (i - n) ) - 1 = 2 * i - (2 * n + 1) = (2 * i) % (2 * n + 1) ��λ��
 */
// ʱ��O(n)���ռ�O(n) �����±��1��ʼ
#define N 10
void PefectShuffle1(int *a, int n) {
	int n2 = n * 2, i, b[N];
	for (i = 1; i <= n2; ++i) {
		b[(i * 2) % (n2 + 1)] = a[i];
	}
	for (i = 1; i <= n2; ++i) {
		a[i] = b[i];
	}
}
void ArrSolveTest_7() {

}
/*
 * ����ˣ���������˻��Ӵ�
 *
 */
double maxProductSub(vector<double> a) {
	double maxEnd = a[0];
	double minEnd = a[0];
	double maxRes = a[0];
	for (int i = 1; i < a.size(); i++) {
		double end1 = maxEnd * a[i], end2 = minEnd * a[i];
		maxEnd = max(max(end1, end2), a[i]);
		minEnd = min(min(end1, end2), a[i]);
		maxRes = max(maxRes, maxEnd);
	}
	return maxRes;
}
void ArrSolveTest_8() {
	double a[] = { -2.5, 4, 0, 3, 0.5, 8, -1 };
	int size = sizeof(a) / sizeof(a[0]);
	vector<double> v(a, a + size);
	cout << maxProductSub(v) << endl;
}
/*
 * ����ţ������ַ���
 * ���������ַ���s1��s2��s3���жϵ������ַ���s3�Ƿ���ǰ�����ַ���s1��s2������ɣ�
 * �����ı�s1��s2�и����ַ�ԭ�е����˳�����統s1 = ��aabcc����
 * s2 = ��dbbca����s3 = ��aadbbcbcac��ʱ�������true�������s3=��accabdbbca����
 * �����false��
 */
//boolean IsInterleave(String s1, String 2, String 3) {
//	int n = s1.length(), m = s2.length(), s = s3.length();
//
//	//������Ȳ�һ�£���s3��������s1��s2�������
//	if (n + m != s)
//	return false;
//
//	boolean[][]dp = new boolean[n + 1][m + 1];
//
//	//�ڳ�ʼ���߽�ʱ��������Ϊ�մ������ɿմ���ɣ����dp[0][0]��ֵΪtrue��
//	dp[0][0] = true;
//
//	for (int i = 0; i < n + 1; i++) {
//		for (int j = 0; j < m + 1; j++) {
//			if ( dp[i][j] || (i - 1 >= 0 && dp[i - 1][j] == true &&
//							//ȡs1�ַ�
//							s1.charAT(i - 1) == s3.charAT(i + j - 1)) ||
//
//					(j - 1 >= 0 && dp[i][j - 1] == true &&
//							//ȡs2�ַ�
//							s2.charAT(j - 1) == s3.charAT(i + j - 1)) )
//
//			dp[i][j] = true;
//			else
//			dp[i][j] = false;
//		}
//	}
//	return dp[n][m]
//}
