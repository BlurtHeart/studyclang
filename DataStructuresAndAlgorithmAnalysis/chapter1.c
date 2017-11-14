/*****************************************************************************
Copyright: 2017 Blurt. All rights reserved.
	Use of this source code is governed by a BSD-style
	license that can be found in the LICENSE file.
File name: chapter1 
Description: Chapter 1 of Data Structures and Algorithm Analysis in C 
Author: Blurt 
Version: 1.0 
Date: 2017.11.14 
History:
*****************************************************************************/

#include<stdio.h>
#include<stdlib.h>

static void sort_arr(int* arr, int n);
static void insert_arr(int* arr, int n, int value);
static void move_right(int* arr, int start, int end);

/****************************************************************************
*函数名:find_item
*功能:找到数组arr中第k大的元素并返回
*描述:把前k个元素读入数组并以递减的顺序对其排序。接着，将剩下的元素再逐个读入。
*当新元素被读到时，如果它小于数组中的第k个元素则忽略，否则将其放到数组中正确的位
*置上，并把数组中的一个元素挤出数组。当算法终止时，位于第k个位置上的元素作为答案
*返回。 
*输入:数组arr，数组长度n，序号k 
*输出:第k个最大值 
*/
static int find_item(int* arr, int n, int k) {
	int* res = (int*)malloc(k*sizeof(int));
	int i, ret;
	for (i=0; i<k; i++) {
		res[i] = arr[i];
	}
	sort_arr(res, k);
	for (i=k; i<n; i++) {
		insert_arr(res, k, arr[i]);
	}
	ret = res[k-1];
	free(res);
	return ret;
}

/****************************************************************************
*函数名:sort_arr
*功能:对数组arr从大到小排序 
*描述:冒泡排序 
*输入:数组arr，数组长度n
*输出:无
*/
static void sort_arr(int* arr, int n) {
	int i, j, temp;
	for (i=0; i<n-1; i++) {
		for (j=0; j<n-1-i; j++) {
			if (arr[i] < arr[i+1]) {
				temp = arr[i];
				arr[i] = arr[i+1];
				arr[i+1] = temp;
			}
		}
	}
}

/****************************************************************************
*函数名:insert_arr
*功能:在有序数组arr中插入元素value 
*输入:数组arr，数组长度n，插入元素value 
*输出:无
*/
static void insert_arr(int* arr, int n, int value) {
	int i, temp;
	for (i=n-1; i>0; i--) {
		if (arr[i] < value && arr[i-1] > value) {
			move_right(arr, i, n-1);
			arr[i] = value;
			return;
		}
	}
	if (arr[0] < value) {
		move_right(arr, 0, n-1);
		arr[0] = value;
	}
}

/****************************************************************************
*函数名:move_right
*功能:把数组arr从start位置到end位置循环右移一位 
*输入:数组arr，数组起始下标start，数组结束下标end 
*输出:无
*/
static void move_right(int* arr, int start, int end) {
	int end_value = arr[end];
	int i;
	for (i=end; i>start; i--) {
		arr[i] = arr[i-1];
	}
	arr[start] = end_value;
}

int main() {
	int arr[10] = {11, 2, 23, 14, 5, 16, 7, 9, 8};
	printf("result:%d\n", find_item(arr, 10, 5));
	return 0;
}
