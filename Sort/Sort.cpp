#include <iostream>
using namespace std;

//冒泡排序
void BubbleSort(int *array, int length)
{
	int temp;
	//执行length-1趟"冒泡"操作
	for (int i = 0; i < length - 1; ++i) {
		//在剩余数列中执行交换操作
		for (int j = 0; j < length - i - 1; ++j) {
			if (array[j] > array[j + 1]) {
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}
}

//对冒泡的改进——快速排序
void Quicksort(int* array, int left, int right)
{
	int i, j, t, temp;
	if (left > right)
		return;
	temp = array[left];		//设置基准值
	i = left;
	j = right;
	while (i != j) {
		//先让 j--,因为基准值在最左边，先 j-- 可以保证 i，j 相遇处的值绝对小于或等于基准值
		while (array[j] >= temp && i < j)
			j--;
		while (array[i] <= temp && i < j)
			i++;
		if (i < j) {
			t = array[i];
			array[i] = array[j];
			array[j] = t;
		}
	}
	array[left] = array[i];
	array[i] = temp;
	Quicksort(array, left, i - 1);				//排序基准值左边的数列
	Quicksort(array, i + 1, right);			//排序基准值右边的数列
}


//选择排序
void SelectionSort(int* array, int len)
{
	int temp, minIndex;
	for (int i = 0; i < len - 1; ++i) {
		minIndex = i;
		for (int j = i + 1; j < len; ++j) {
			if (array[minIndex] > array[j])
				minIndex = j;
		}
		temp = array[i];
		array[i] = array[minIndex];
		array[minIndex] = temp;
	}
}

//插入排序
void InsertionSort(int* array, int len)
{
	int temp, preIndex;
	for (int i = 1; i < len; ++i) {
		temp = array[i];			//储存当前要向有序链表中插入的值
		preIndex = i;
		while (preIndex > 0 && temp < array[preIndex - 1]) {
			array[preIndex] = array[preIndex - 1];
			preIndex--;
		}
		array[preIndex] = temp;
	}
}

//插入排序（递归）
void InsertionSort2(int* array, int len)
{
	if (len == 1)
		return;
	InsertionSort2(array, len - 1);

	int preIndex, temp;
	temp = array[len - 1];
	preIndex = len - 1;
	while (preIndex > 0 && temp < array[preIndex - 1]) {
		array[preIndex] = array[preIndex - 1];
		--preIndex;
	}
	array[preIndex] = temp;
}

//希尔排序(改良版的插入排序)
void ShellSort(int* array, int len)
{
	int temp, preIndex;
	//增量（grp）为1时，对整个数组进行插入排序，
	//不过此时的数列基本上是排好序的了。
	for (int grp = len / 2; grp > 0; grp /= 2) {
		//对每组进行插入排序
		for (int i = grp; i < len; ++i) {
			preIndex = i - grp;
			temp = array[i];
			while (preIndex >= 0 && array[preIndex] > temp) {
				array[preIndex + grp] = array[preIndex];
				preIndex -= grp;
			}
			array[preIndex + grp] = temp;
		}
	}
}

//归并排序
void merge(int *array, int L_left, int L_right, int R_left, int R_right)
{
	//申请一个新数组用来储存排好序的数组
	int *temp = new int[R_right - L_left + 1];
	int i = L_left, j = R_left, k = 0;
	//将两数组中的数据有序归并到temp中
	while (i <= L_right && j <= R_right) {
		temp[k++] = (array[i] < array[j]) ? array[i++] : array[j++];
	}
	//将左数组或者右数组中剩余的有序数列归并到temp中
	while (i <= L_right) {
		temp[k++] = array[i++];
	}
	while (j <= R_right) {
		temp[k++] = array[j++];
	}
	//将排好序的数列替换到原数列中
	k = 0;
	for (i = L_left; i <= R_right; ++i) {
		array[i] = temp[k++];
	}
	//释放临时开辟的空间
	delete[] temp;
}
void MergeSort(int *array, int left, int right)
{
	if (left + 1 <= right) {
		MergeSort(array, left, (right + left) / 2);
		MergeSort(array, (right + left) / 2 + 1, right);
		merge(array, left, (right + left) / 2, (right + left) / 2 + 1, right);
	}
}

//堆排序（最大堆）
//向下调整
void SiftDown(int *array, int n, int i)
{
	//如果当前结点至少存在一个孩子结点，比较它与孩子结点的大小
	while ((2 * i + 1) <= n) {
		int t = i;
		if (array[t] < array[2 * i + 1])
			t = 2 * i + 1;
		if ((2 * i + 2) <= n && array[t] < array[2 * i + 2])
			t = 2 * i + 2;
		//当前结点比它的孩子结点小，进行交换
		if (t != i) {
			int temp = array[t];
			array[t] = array[i];
			array[i] = temp;
			i = t;		//当前结点的索引变为t
		}
		//当前结点比它两个孩子结点的值大，结束调整
		else
			break;
	}
}
void HeapSort(int *array, int n)
{
	//（初始化堆）从崔侯一个非叶结点的结点开始依次进行向上调整
	for (int i = n / 2; i >= 0; --i) {
		SiftDown(array, n, i);
	}
	//将堆顶元素放到最后，并在剩余的 n-- 数内对新的堆顶元素向下调整
	while (n >= 0) {
		int temp = array[n];
		array[n] = array[0];
		array[0] = temp;
		SiftDown(array, --n, 0);
	}
}

int main()
{
	const int len = 10;
	int array[5][len] = { { 6, 0, 12, 10, 3, 5, 7, 1, 2, 3 },
	{ 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 },
	{ 789, 0, 20, 67, 76, 9, 1, 5, 2, 8 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 } };

	for (int i = 0; i < 5; ++i) {
		//BubbleSort(array[i], len);
		//SelectionSort(array[i], len);
		//InsertionSort(array[i], len);
		//InsertionSort2(array[i], len);
		//ShellSort(array[i], len);
		//Quicksort(array[i], 0, 9);
		//MergeSort(array[i], 0, 9);
		HeapSort(array[i], len - 1);
	}

	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < len; ++j) {
			cout << array[i][j] << " ";
		}
		cout << endl;
	}
	system("pause");
	return 0;
}
