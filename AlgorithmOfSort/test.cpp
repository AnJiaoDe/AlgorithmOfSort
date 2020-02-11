#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

#include <chrono>   
#include<iostream>
using namespace std;
using namespace chrono;

int sort_select(int arr[], int size) {
	int temp;
	int count_for = 0;
	for (int i = 0; i < size - 1; i++) {
		int minIndex = i;
		for (int j = i + 1; j < size; j++) {
			count_for++;
			if (arr[j] < arr[minIndex]) {
				minIndex = j;
			}
		}
		if (minIndex != i) {
			int temp = arr[i];
			arr[i] = arr[minIndex];
			arr[minIndex] = temp;
		}
	}
	return count_for;
}
int sort_bubbling(int arr[], int size) {
	//下面计算的size永远等于1，数组做函数参数退化成指针，32位操作系统中，sizeof(任何指针变量)永远=4
	//printf("size=%d\n", sizeof(arr) / sizeof(arr[0]));
	int temp;
	int count_for = 0;
	for (int i = 0; i < size - 1; i++) {
		for (int j = size - 1; j > i; j--) {
			count_for++;
			if (arr[j] < arr[j - 1]) {
				temp = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = temp;
			}
		}
	}
	return count_for;
}
int sort_bubbling_optimize(int arr[], int size) {
	int temp;
	boolean flag;
	int count_for = 0;
	for (int i = 0; i < size - 1; i++) {
		flag = false;
		for (int j = size - 1; j > i; j--) {
			count_for++;
			if (arr[j] < arr[j - 1]) {
				temp = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = temp;
				flag = true;
			}
		}
		if (!flag) break;
	}
	return count_for;
}
int sort_insert(int arr[], int size) {
	int temp;
	int count_for = 0;
	for (int i = 0; i < size - 1; i++) {
		for (int j = i + 1; j > 0; j--) {
			count_for++;
			if (arr[j] < arr[j - 1]) {
				temp = arr[j - 1];
				arr[j - 1] = arr[j];
				arr[j] = temp;
			}
			else {
				break;
			}
		}
	}
	return count_for;
}
int sort_sheer(int arr[], int size) {
	int gap = size;
	int temp;
	int count_for = 0;
	do {
		gap = gap / 3 + 1;
		for (int i = gap; i < size; i += gap) {
			for (int j = i - gap; j >= 0; j -= gap) {
				count_for++;
				if (arr[j] > arr[j + gap]) {
					temp = arr[j + gap];
					arr[j + gap] = arr[j];
					arr[j] = temp;
				}
				else {
					break;
				}
			}
		}
	} while (gap > 1);
	return count_for;
}
int separate(int arr[], int left, int right) {
	int key = arr[left];
	while (left < right) {
		while (left < right && arr[right] >= key) {
			right--;
		}
		arr[left] = arr[right];
		while (left < right && arr[left] <= key) {
			left++;
		}
		arr[right] = arr[left];
	}
	arr[left] = key;
	return left;
}
void sort_quick(int arr[], int left, int right) {
	int median = 0;
	if (left < right) {
		median = separate(arr, left, right);
		sort_quick(arr, left, median - 1);
		sort_quick(arr, median + 1, right);
	}
}
void merge(int src[], int des[], int left, int middle, int right) {
	int i = left;
	int j = middle + 1;
	int k = left;
	while ((i <= middle) && (j <= right)) {
		if (src[i] < src[j]) {
			des[k++] = src[i++];
		}
		else {
			des[k++] = src[j++];
		}
	}
	while (i <= middle) {
		des[k++] = src[i++];
	}
	while (j <= right) {
		des[k++] = src[j++];
	}
}
void sort_merge(int src[], int des[], int left, int right, int length) {
	if (left == right) {
		des[left] = src[left];
	}
	else {
		int middle = (left + right) / 2;
		int * array = (int*)malloc(sizeof(int)*length);
		if (array != NULL) {
			sort_merge(src, array, left, middle, length);
			sort_merge(src, array, middle + 1, right, length);
			merge(array, des, left, middle, right);
		}
		free(array);
	}
}
int  main() {
	int arr[] = { 3,9,12,1,6,7 };
	//int size = sizeof(arr) / sizeof(int);
	int size = sizeof(arr) / sizeof(arr[0]);

	auto start = system_clock::now();

	int count_for = 0;
	//count_for = sort_select(arr, size);
	//count_for=sort_bubbling(arr, size);
	//count_for = sort_bubbling_optimize(arr, size);
	//count_for = sort_insert(arr, size);
	//count_for = sort_sheer(arr, size);
	//sort_quick(arr, 0, size - 1);
	sort_merge(arr, arr, 0, size - 1, size);

	auto end = system_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	//cout <<"for循环"<<count_for<< "次花费了"<< double(duration.count()) * microseconds::period::num / microseconds::period::den<< "秒" << endl;
	cout << "for循环" << count_for << "次花费了" << double(duration.count()) << "微秒" << endl;

	for (int i = 0; i < size; i++) {
		printf("%d\n", arr[i]);
	}
	system("pause");
	return 0;
}