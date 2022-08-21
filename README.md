# QuickSort
快速排序算法及其思想的应用Select K
# 快速排序算法
## 第一版快速排序法
### partition()方法将数组分为两部分
选取第一个值为标定点v，将数组分为<v,>v和v，最终v左边都是小于v的值，右边是大于等于v的值，返回v对应的索引值。
| v | <v 的元素|<v|>=v的元素| 未知| 未知|
|--|----|--|--|--|--|
| 索引l指向第一个元素 |      |索引j指向| |索引i|索引r指向最后一个元素

i循环遍历整个数组，循环不变量为

> arr[l+1,j]<v
> arr[j+1,i-1]>=v

当arr[i]<v，j++；arr[j]与arr[i]交换；
循环结束后arr[l]与arr[j]交换，此时索引j代表的元素等于标定值，arr[l,j-1]<v;arr[j,r]>=v,返回索引j。
```c++
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
```
此时数组被分为两部分，再分别将两个子数组排序，用递归调用函数。
### 递归实现排序
首先找到递归最基本的问题：
```c++
if (l >= r) return;
```
调用partition()方法返回给p后，将问题分解，对arr[l,p-1]排序，然后对arr[p+1,r]排序。
```c++
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
```
最后调用该Sort()函数
```c++
template <typename T>
void QuickSort1(T arr[], int length)
{
	Sort1(arr, 0, length - 1);
}
```
###  使用插入排序优化
像之前归并排序一样，数据规模小时用插入排序算法更快，因此只需要更改递归的Sort()方法将最基本问题改为
```c++
if(r-l<=15){
InsertionSort(arr,l,r);//调用插入排序方法
return;
}
```
### 第一版快速排序的问题
对于完全有序的数组，每次调用partition()方法返回的都是0，即每次排序选取的标定点都是第一个元素，这样算法时间复杂度为O($n^2$)，因此运行时间变得很长，算法发生退化。而且递归深度为O(n),当n规模大一些就会导致堆栈溢出。
**添加随机化**可以解决这个问题，在l~r内随机取一个索引值，将对应元素与第一个元素交换作为标定点。这里要注意**随机性**，不是选取中间值什么的，保证每次标定点随机，这样就能保证无法找到特定用例使算法一定退化。
随机化后的算法如下
```c++
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
```
但是这样该算法依然有问题，对于元素全部相同的数组，随机化就没有用了，算法依然发生退化，对于有大量相同元素的数组，算法性能大大降低。
双路快速排序算法可以解决这个问题。
## 双路快速排序算法
随机选取好标定值v，让索引i、j分别从数组两侧遍历，当arr[i]<=v时，i++;当arr[j]>=v时，j--；等i、j都停止交换两者元素的值，i>=j时停止遍历，最后交换arr[l]与arr[j]返回索引j。
```c++
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
```
对于测试用例 随机数组、有序数组、等值数组，双路排序算法都有良好的性能。
## 复杂度分析
优化后双路快速排序算法时间复杂度最坏情况依然是O($n^2$)但是添加随机化后，发生最坏情况的概率非常非常非常低。因此可以说快速排序算法是一个随机算法，在分析复杂度时，应分析使用期望，时间复杂度为O($nlogn$)。
>普通算法：看最差情况  能找到一组数据使算法100%恶化
>随机算法：看期望  没有一组数据使算法100%恶化
>多次调用：均摊分析复杂度

## 三路快速排序算法
将数组分为<v、=v、>v三部分。
对于含大量相同元素的数组排序有优势，若所有元素都相同，算法时间复杂度变为O(n)只需执行一次partition()方法。
```c++
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
```
### 其他需要用到的函数代码
```c++
//交换
template <typename T>
void swap(T arr[], int i, int j)
{
	T t = arr[j];
	arr[j] = arr[i];
	arr[i] = t;
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
```
### 主函数
```c++
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
```
# leetcode 中的相关题运用到快速排序算法的思想
## leetcode 75.颜色分类
运用三路快速排序算法的思想
```c++
void sortColors(vector<int>& nums) {
	int lt = -1, i = 0 , gt = nums.size() ;
	while (i < gt) {
		if (nums[i] ==0) {
			lt++;
			swap(nums, i, lt);
			i++;
		}
		else if (nums[i]==2) {
			gt--;
			swap(nums, i, gt);
		}
		else if(nums[i]==1) {
			i++;
		}
	}
    }
    void swap(vector<int>& arr,int i,int j){
        int t=arr[i];
        arr[i]=arr[j];
        arr[j]=t;
    }
```
## Select k
找出第k大或第k小的元素，使用快速排序算法的思想使时间复杂度为O(n)。
>找出第k小的元素
>p=partition()
>k==p? 找到该元素
>k<p?  在p 左边找
>k>p?  在p右边找

代码在.txt文件中。

# 总结
### 快速排序整体思想
| <v | v |>v|
|--|--|--|

每次选定标定点v，将待处理数组整理成<v;=v;>v 的区间，再分别递归的将< 和> 两部分进行处理。

 - 单路快速排序：对于完全有序数据，发生退化->引入随机化->所有元素一样时还是退化。
 - 双路快速排序：解决单路的问题，从两边遍历，但是若所有元素一样，处理后两边子数组元素依然都一样，递归显得很没有必要。
 - 三路快速排序算法：解决上面算法退化问题，同时，在大量相等元素时，性能更好；全部相等元素的数组，时间复杂度为O(n)。

快速排序算法的思想不仅可以用到排序上，对于Select K 在无序数组中寻找第k大或第k小的元素也很适用。
## 小结
本周学习了快速排序算法，从第一版最简单的快速排序开始，逐步发现问题，优化算法，分析复杂度，用不同类型数组进行测试，了解了三种快速排序算法的方法特点，进一步理解了递归思想。最后通过快速排序思想解决了一些leetcode相关问题。
