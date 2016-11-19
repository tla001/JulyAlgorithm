/*
 * DealArr.cpp
 *
 *  Created on: 2016年10月25日
 *      Author: tla001
 */

#include "DealArr.h"

/*
 * 问题一：寻找最小的k个数
 *输入n个整数，输出其中最小的k个。
 */
#define CUTOFF 2
void DirectInsertSort(int a[], int n) {
	for (int i = 1; i < n; i++) {
		if (a[i] < a[i - 1]) { //找到小数
			int j = i - 1;
			int x = a[i]; //复制为哨兵，即存储待排序元素
			a[i] = a[i - 1]; //大数后移一次
			while (x < a[j] && j > -1) {
				a[j + 1] = a[j]; //找到小数应该在的位置
				j--;
			}
			a[j + 1] = x; //插入小数
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
//选出前k的小数，放在a[0]--a[k-1]
//QuickSelect 将第k小的元素放在 a[k-1]
void QuickSelect(int a[], int k, int left, int right) {
	int i, j;
	int pivot;

	if (left + CUTOFF <= right) {
		pivot = median3(a, left, right);
		//取三数中值作为枢纽元，可以很大程度上避免最坏情况
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
		//重置枢纽元
		swap(a[i], a[right - 1]);

		if (k <= i)
			QuickSelect(a, k, left, i - 1);
		else if (k > i + 1)
			QuickSelect(a, k, i + 1, right);
	} else
		DirectInsertSort(a + left, right - left + 1);
}
//选出第k的小数
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
	//重置枢纽元
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
		//取三数中值作为枢纽元，可以很大程度上避免最坏情况
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
		//重置枢纽元
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
	//重置枢纽元
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
 * 问题二 最大连续子数组和
 * 输入一个整形数组，数组里有正数也有负数。数组中连续的一个或多个整数组成一个子数组，
 * 每个子数组都有一个和。 求所有子数组的和的最大值，要求时间复杂度为O(n)。
 *	例如输入的数组为  1, -2, 3, 10, -4, 7, 2, -5  ，和最大的子数组为
 *	 3, 10, -4, 7, 2  ， 因此输出为该子数组的和18。
 */
/*
 * 三个for循环三层遍历，求出数组中每一个子数组的和，最终求出这些子数组的最大的一个值
 * 此方法的时间复杂度为O(n^3)。
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
 * 对第j+1个元素有两种选择：要么放入前面找到的子数组，要么做为新子数组的第一个元素；
 *如果currSum加上当前元素a[j]后不小于a[j]，则令currSum加上a[j]，
 *   否则currSum重新赋值，置为下一个元素，即currSum = a[j]。
 *同时，当currSum > maxSum，则更新maxSum = currSum，否则保持原值，不更新。
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
 * 问题三 寻找和为定值的两个数
 * 如果数组是无序的，先排序(N log N)，然后用两个指针i，j，各自指向数组的首尾两端，令i=0，j=n-1，然后i++，j--，逐次判断a[i]+a[j]?=sum，

 如果某一刻a[i]+a[j] > sum，则要想办法让sum的值减小，所以此刻i不动，j--；
 如果某一刻a[i]+a[j] < sum，则要想办法让sum的值增大，所以此刻i++，j不动。
 所以，数组无序的时候，时间复杂度最终为O(N log N + N)=O(N log N)。

 如果原数组是有序的，则不需要事先的排序，直接用两指针分别从头和尾向中间扫描，O(N)搞定，且空间复杂度还是O(1)
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
	//显示排序轨迹
	//PrintQuickSort(a, 10, i);
	QuickSort(a, left, i - 1);
	QuickSort(a, i + 1, right);
}
void TwoSum(int data[], unsigned int length, int sum) {
	//如果输入无序，需要快排排序
	QuickSortF(data, 0, length - 1);
	int begin = 0;
	int end = length - 1;
	//从两端向中间逼近
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
 * 问题四：寻找和为定值的多个数
 * 输入两个整数n和sum，从数列1，2，3.......n 中随意取几个数，
 * 使其和等于sum，要求将其中所有的可能组合列出来
 */
/*
 * 注意到取n，和不取n个区别即可，考虑是否取第n个数的策略，可以转化为一个只和前n-1个数相关的问题。

 如果取第n个数，那么问题就转化为“取前n-1个数使得它们的和为sum-n”，对应的代码语句就是sumOfkNumber(sum - n, n - 1)；
 如果不取第n个数，那么问题就转化为“取前n-1个数使得他们的和为sum”，对应的代码语句为sumOfkNumber(sum, n - 1)。
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
 * 问题五：荷兰旗问题
 *
 */
/*
 * 一个前指针begin，一个中指针current，一个后指针end，current指针遍历整个数组序列，当

 current指针所指元素为0时，与begin指针所指的元素交换，而后current++，begin++ ；
 current指针所指元素为1时，不做任何交换（即球不动），而后current++ ；
 current指针所指元素为2时，与end指针所指的元素交换，而后，current指针不动，end--
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
 * 问题六：矩阵相乘
 * 请编程实现矩阵乘法，并考虑当矩阵规模较大时的优化方法。
 */
void ArrSolveTest_6() {

}
/*
 * 问题七：完美洗牌算法
 *
 */
/*
 * 第i个元素去了第 (2 * (i - n) ) - 1 = 2 * i - (2 * n + 1) = (2 * i) % (2 * n + 1) 个位置
 */
// 时间O(n)，空间O(n) 数组下标从1开始
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
 * 问题八：最大连续乘积子串
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
 * 问题九：交替字符串
 * 输入三个字符串s1、s2和s3，判断第三个字符串s3是否由前两个字符串s1和s2交错而成，
 * 即不改变s1和s2中各个字符原有的相对顺序，例如当s1 = “aabcc”，
 * s2 = “dbbca”，s3 = “aadbbcbcac”时，则输出true，但如果s3=“accabdbbca”，
 * 则输出false。
 */
//boolean IsInterleave(String s1, String 2, String 3) {
//	int n = s1.length(), m = s2.length(), s = s3.length();
//
//	//如果长度不一致，则s3不可能由s1和s2交错组成
//	if (n + m != s)
//	return false;
//
//	boolean[][]dp = new boolean[n + 1][m + 1];
//
//	//在初始化边界时，我们认为空串可以由空串组成，因此dp[0][0]赋值为true。
//	dp[0][0] = true;
//
//	for (int i = 0; i < n + 1; i++) {
//		for (int j = 0; j < m + 1; j++) {
//			if ( dp[i][j] || (i - 1 >= 0 && dp[i - 1][j] == true &&
//							//取s1字符
//							s1.charAT(i - 1) == s3.charAT(i + j - 1)) ||
//
//					(j - 1 >= 0 && dp[i][j - 1] == true &&
//							//取s2字符
//							s2.charAT(j - 1) == s3.charAT(i + j - 1)) )
//
//			dp[i][j] = true;
//			else
//			dp[i][j] = false;
//		}
//	}
//	return dp[n][m]
//}
