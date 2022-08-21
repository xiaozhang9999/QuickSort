#include<iostream>
using namespace std;
#include<string>
#include<algorithm>
#include<stdlib.h>
#include<Windows.h>
#include<time.h>
//����
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
	//��arr[l,p-1]����
	Sort1(arr, l, p - 1);
	//��arr[p+1,r]����
	Sort1(arr, p + 1, r);
}
template <typename T>
void QuickSort1(T arr[], int length)
{
	Sort1(arr, 0, length - 1);
}
//��������
template <typename T>
int partition2(T arr[], int l, int r)
{
	srand(time(NULL));//����ʱ������
	int rnd = l + rand() % (r - l + 1);//��������Ϊ[l,r]�������
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
	//��arr[l,p-1]����
	Sort2(arr, l, p - 1);
	//��arr[p+1,r]����
	Sort2(arr, p + 1, r);
}
template <typename T>
void QuickSort2(T arr[], int length)
{
	Sort2(arr, 0, length - 1);
}
//˫·��������
template <typename T>
int partition2ways(T arr[], int l, int r)
{
	srand(time(NULL));//����ʱ������
	int rnd = l + rand() % (r - l + 1);//��������Ϊ[l,r]�������
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
	//��arr[l,p-1]����
	Sort2ways(arr, l, p - 1);
	//��arr[p+1,r]����
	Sort2ways(arr, p + 1, r);
}
template <typename T>
void QuickSort2ways(T arr[], int length)
{
	Sort2ways(arr, 0, length - 1);
}
//��·��������
template <typename T>
void Sort3ways(T arr[], int l, int r)
{
	if (l >= r) return;
	srand(time(NULL));//����ʱ������
	int rnd = l + rand() % (r - l + 1);//��������Ϊ[l,r]���������
	swap(arr, l, rnd);
	int lt = l, i = l + 1, gt = r + 1;
	//v=arr[l]ѡȡ���������l����;arr[l+1,lt]<v;arr[lt+1,i-1]=v;arr[gt,r]>v
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
		else {//����iԪ����궨��v���
			i++;
		}
	}
	swap(arr, lt, l);//��arr[l]=v��Ԫ�������һ��<v��Ԫ�ؽ���,�ŵ�=v����
	//��ʱ��arr[l,lt-1]<v;arr[lt,gt-1]=v;arr[gt,r]>v
	//��arr[l,lt-1]����
	Sort3ways(arr, l, lt-1);
	//��arr[gt,r]����
	Sort3ways(arr, gt, r);
}
template <typename T>
void QuickSort3ways(T arr[], int length)
{
	Sort3ways(arr, 0, length - 1);
}
//�����������
template <typename T>
void generateRandomArray(T arr[], int length, int max)
{
	srand(time(NULL));//����ʱ������
	for (int i = 0; i < length; i++)
	{
		arr[i] = rand() % (max + 1);//��������Ϊ[0-max]�������
	}
}
//������������
template <typename T>
void generateOrderArray(T arr[], int length)
{
	for (int i = 0; i < length; i++)
	{
		arr[i] = i;
	}
}
//���������㷨�Ƿ���ȷ
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
//�����㷨����
template <typename T>
void test(string str, T arr[], int length)
{
	//QueryPerformanceCounter()��ʱ
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
	cout << str << ":��ʱ�� " << time * 1000 << "ms" << endl;  //����λ��ms��

	/*for (int i = 0; i < length;i++) {
		cout << arr[i] << " ";
	}
	cout << endl;*/
	if (Judge(arr, length))
		cout << "������ȷ��" << endl;
	else
		cout << "�������" << endl;
}
int main()
{
	const int n = 10000;
	int arr[n];
	generateRandomArray(arr, n, n);//��������Ϊn��0-n��������
	int arr1[n];
	memcpy(arr1, arr, sizeof(arr));//������ͬ����
	/*for (int i = 0; i < n;i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
	for (int j = 0; j < n;j++) {
		cout << arr1[j] << " ";
	}
	cout << endl;*/
	cout << "�������" << endl;
//	test("QuickSort1", arr, n);
	test("QuickSort2", arr1, n);
	test("QuickSort3ways", arr, n);
	//��������
	cout << "��������" << endl;
	generateOrderArray(arr, n);
	memcpy(arr1, arr, sizeof(arr));
//	test("QuickSort1", arr, n);
	test("QuickSort2", arr1, n);
	test("QuickSort3ways", arr, n);
	//�������
	cout << "��ֵ����" << endl;
	generateRandomArray(arr, n, 0);
	memcpy(arr1, arr, sizeof(arr));
//	test("QuickSort2", arr, n);
	test("QuickSort2ways", arr1, n);
	test("QuickSort3ways", arr, n);
}
