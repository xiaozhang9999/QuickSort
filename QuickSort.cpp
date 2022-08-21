#include<iostream>
using namespace std;
#include<string>
#include<algorithm>
#include<stdlib.h>
#include<Windows.h>
#include<time.h>
//交换
template <typename T>
void swap(T arr[], int i, int j)
{
	T t = arr[j];
	arr[j] = arr[i];
	arr[i] = t;
}
template <typename T>
int partition(T arr[], int l, int r)
{
	int j = l;
	for (int i = l + 1; i <= r; i++) {
		if (arr[i] < arr[l]) {
			j++;
			swap(arr, i, j);
		}
	}
	swap(arr, l, j);
	return j;
}

template <typename T>
void Sort1(T arr[], int l, int r)
{
	if (l >= r) return;
	int p = partition(arr, l, r);
	//对arr[l,p-1]排序
	Sort1(arr, l, p - 1);
	//对arr[p+1,r]排序
	Sort1(arr, p + 1, r);
}
template <typename T>
void QuickSort1(T arr[], int length)
{
	Sort1(arr, 0, length - 1);
}
//添加随机化
template <typename T>
int partition2(T arr[], int l, int r)
{
	srand(time(NULL));//设置时间种子
	int rnd = l + rand() % (r - l + 1);//生成区间为[l,r]的随机数
	int j = l;
	swap(arr, j, rnd);
	for (int i = l + 1; i <= r; i++) {
		if (arr[i] < arr[l]) {
			j++;
			swap(arr, i, j);
		}
	}
	swap(arr, l, j);
	return j;
}
template <typename T>
void Sort2(T arr[], int l, int r)
{
	if (l >= r) return;
	int p = partition2(arr, l, r);
	//对arr[l,p-1]排序
	Sort2(arr, l, p - 1);
	//对arr[p+1,r]排序
	Sort2(arr, p + 1, r);
}
template <typename T>
void QuickSort2(T arr[], int length)
{
	Sort2(arr, 0, length - 1);
}
//双路快速排序法
template <typename T>
int partition2ways(T arr[], int l, int r)
{
	srand(time(NULL));//设置时间种子
	int rnd = l + rand() % (r - l + 1);//生成区间为[l,r]的随机数
	swap(arr, l, rnd);
	int i = l + 1, j = r;
	while (true) {
		while (i <= j && arr[i] < arr[l]) { i++; }
		while (j >= i && arr[j] > arr[l]) { j--; }
		if (i >= j) break;

		swap(arr, i, j);
		i++;
		j--;
	}
	swap(arr, l, j);
	return j;
}
template <typename T>
void Sort2ways(T arr[], int l, int r)
{
	if (l >= r) return;
	int p = partition2ways(arr, l, r);
	//对arr[l,p-1]排序
	Sort2ways(arr, l, p - 1);
	//对arr[p+1,r]排序
	Sort2ways(arr, p + 1, r);
}
template <typename T>
void QuickSort2ways(T arr[], int length)
{
	Sort2ways(arr, 0, length - 1);
}
//三路快速排序
template <typename T>
void Sort3ways(T arr[], int l, int r)
{
	if (l >= r) return;
	srand(time(NULL));//设置时间种子
	int rnd = l + rand() % (r - l + 1);//生成区间为[l,r]的随机索引
	swap(arr, l, rnd);
	int lt = l, i = l + 1, gt = r + 1;
	//v=arr[l]选取随机索引与l交换;arr[l+1,lt]<v;arr[lt+1,i-1]=v;arr[gt,r]>v
	while (i < gt) {
		if (arr[i] < arr[l]) {
			lt++;
			swap(arr, i, lt);
			i++;
		}
		else if (arr[i] > arr[l]) {
			gt--;
			swap(arr, i, gt);
		}
		else {//索引i元素与标定点v相等
			i++;
		}
	}
	swap(arr, lt, l);//将arr[l]=v的元素与最后一个<v的元素交换,放到=v区间
	//此时，arr[l,lt-1]<v;arr[lt,gt-1]=v;arr[gt,r]>v
	//对arr[l,lt-1]排序
	Sort3ways(arr, l, lt-1);
	//对arr[gt,r]排序
	Sort3ways(arr, gt, r);
}
template <typename T>
void QuickSort3ways(T arr[], int length)
{
	Sort3ways(arr, 0, length - 1);
}
//生成随机数组
template <typename T>
void generateRandomArray(T arr[], int length, int max)
{
	srand(time(NULL));//设置时间种子
	for (int i = 0; i < length; i++)
	{
		arr[i] = rand() % (max + 1);//生成区间为[0-max]的随机数
	}
}
//生成有序数组
template <typename T>
void generateOrderArray(T arr[], int length)
{
	for (int i = 0; i < length; i++)
	{
		arr[i] = i;
	}
}
//测试排序算法是否正确
template <typename T>
bool Judge(T arr[], int length)
{
	for (int i = 1; i < length; i++)
	{
		if (arr[i - 1] > arr[i]) {
			return false;
		}
	}
	return true;
}
//测试算法性能
template <typename T>
void test(string str, T arr[], int length)
{
	//QueryPerformanceCounter()计时
	LARGE_INTEGER t1, t2, tc;
	QueryPerformanceFrequency(&tc);
	QueryPerformanceCounter(&t1);
	if (str == "QuickSort1") {
		QuickSort1(arr, length);
	}
	else if (str == "QuickSort2") {
		QuickSort2(arr, length);
	}
	else if (str == "QuickSort2ways") {
		QuickSort2ways(arr, length);
	}
	else if (str == "QuickSort3ways") {
		QuickSort3ways(arr, length);
	}
	QueryPerformanceCounter(&t2);
	double time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
	cout << str << ":用时： " << time * 1000 << "ms" << endl;  //（单位：ms）

	/*for (int i = 0; i < length;i++) {
		cout << arr[i] << " ";
	}
	cout << endl;*/
	if (Judge(arr, length))
		cout << "排序正确！" << endl;
	else
		cout << "排序错误！" << endl;
}
int main()
{
	const int n = 10000;
	int arr[n];
	generateRandomArray(arr, n, n);//生成容量为n的0-n测试数组
	int arr1[n];
	memcpy(arr1, arr, sizeof(arr));//复制相同数组
	/*for (int i = 0; i < n;i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
	for (int j = 0; j < n;j++) {
		cout << arr1[j] << " ";
	}
	cout << endl;*/
	cout << "随机数组" << endl;
//	test("QuickSort1", arr, n);
	test("QuickSort2", arr1, n);
	test("QuickSort3ways", arr, n);
	//有序数组
	cout << "有序数组" << endl;
	generateOrderArray(arr, n);
	memcpy(arr1, arr, sizeof(arr));
//	test("QuickSort1", arr, n);
	test("QuickSort2", arr1, n);
	test("QuickSort3ways", arr, n);
	//相等数组
	cout << "等值数组" << endl;
	generateRandomArray(arr, n, 0);
	memcpy(arr1, arr, sizeof(arr));
//	test("QuickSort2", arr, n);
	test("QuickSort2ways", arr1, n);
	test("QuickSort3ways", arr, n);
}
