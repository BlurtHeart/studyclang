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
*������:find_item
*����:�ҵ�����arr�е�k���Ԫ�ز�����
*����:��ǰk��Ԫ�ض������鲢�Եݼ���˳��������򡣽��ţ���ʣ�µ�Ԫ����������롣
*����Ԫ�ر�����ʱ�������С�������еĵ�k��Ԫ������ԣ�������ŵ���������ȷ��λ
*���ϣ����������е�һ��Ԫ�ؼ������顣���㷨��ֹʱ��λ�ڵ�k��λ���ϵ�Ԫ����Ϊ��
*���ء� 
*����:����arr�����鳤��n�����k 
*���:��k�����ֵ 
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
*������:sort_arr
*����:������arr�Ӵ�С���� 
*����:ð������ 
*����:����arr�����鳤��n
*���:��
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
*������:insert_arr
*����:����������arr�в���Ԫ��value 
*����:����arr�����鳤��n������Ԫ��value 
*���:��
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
*������:move_right
*����:������arr��startλ�õ�endλ��ѭ������һλ 
*����:����arr��������ʼ�±�start����������±�end 
*���:��
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
