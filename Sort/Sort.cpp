#include <iostream>
using namespace std;

//ð������
void BubbleSort(int *array, int length)
{
	int temp;
	//ִ��length-1��"ð��"����
	for (int i = 0; i < length - 1; ++i) {
		//��ʣ��������ִ�н�������
		for (int j = 0; j < length - i - 1; ++j) {
			if (array[j] > array[j + 1]) {
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}
}

//��ð�ݵĸĽ�������������
void Quicksort(int* array, int left, int right)
{
	int i, j, t, temp;
	if (left > right)
		return;
	temp = array[left];		//���û�׼ֵ
	i = left;
	j = right;
	while (i != j) {
		//���� j--,��Ϊ��׼ֵ������ߣ��� j-- ���Ա�֤ i��j ��������ֵ����С�ڻ���ڻ�׼ֵ
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
	Quicksort(array, left, i - 1);				//�����׼ֵ��ߵ�����
	Quicksort(array, i + 1, right);			//�����׼ֵ�ұߵ�����
}


//ѡ������
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

//��������
void InsertionSort(int* array, int len)
{
	int temp, preIndex;
	for (int i = 1; i < len; ++i) {
		temp = array[i];			//���浱ǰҪ�����������в����ֵ
		preIndex = i;
		while (preIndex > 0 && temp < array[preIndex - 1]) {
			array[preIndex] = array[preIndex - 1];
			preIndex--;
		}
		array[preIndex] = temp;
	}
}

//�������򣨵ݹ飩
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

//ϣ������(������Ĳ�������)
void ShellSort(int* array, int len)
{
	int temp, preIndex;
	//������grp��Ϊ1ʱ��������������в�������
	//������ʱ�����л��������ź�����ˡ�
	for (int grp = len / 2; grp > 0; grp /= 2) {
		//��ÿ����в�������
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

//�鲢����
void merge(int *array, int L_left, int L_right, int R_left, int R_right)
{
	//����һ�����������������ź��������
	int *temp = new int[R_right - L_left + 1];
	int i = L_left, j = R_left, k = 0;
	//���������е���������鲢��temp��
	while (i <= L_right && j <= R_right) {
		temp[k++] = (array[i] < array[j]) ? array[i++] : array[j++];
	}
	//�������������������ʣ����������й鲢��temp��
	while (i <= L_right) {
		temp[k++] = array[i++];
	}
	while (j <= R_right) {
		temp[k++] = array[j++];
	}
	//���ź���������滻��ԭ������
	k = 0;
	for (i = L_left; i <= R_right; ++i) {
		array[i] = temp[k++];
	}
	//�ͷ���ʱ���ٵĿռ�
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

//���������ѣ�
//���µ���
void SiftDown(int *array, int n, int i)
{
	//�����ǰ������ٴ���һ�����ӽ�㣬�Ƚ����뺢�ӽ��Ĵ�С
	while ((2 * i + 1) <= n) {
		int t = i;
		if (array[t] < array[2 * i + 1])
			t = 2 * i + 1;
		if ((2 * i + 2) <= n && array[t] < array[2 * i + 2])
			t = 2 * i + 2;
		//��ǰ�������ĺ��ӽ��С�����н���
		if (t != i) {
			int temp = array[t];
			array[t] = array[i];
			array[i] = temp;
			i = t;		//��ǰ����������Ϊt
		}
		//��ǰ�������������ӽ���ֵ�󣬽�������
		else
			break;
	}
}
void HeapSort(int *array, int n)
{
	//����ʼ���ѣ��Ӵ޺�һ����Ҷ���Ľ�㿪ʼ���ν������ϵ���
	for (int i = n / 2; i >= 0; --i) {
		SiftDown(array, n, i);
	}
	//���Ѷ�Ԫ�طŵ���󣬲���ʣ��� n-- ���ڶ��µĶѶ�Ԫ�����µ���
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
