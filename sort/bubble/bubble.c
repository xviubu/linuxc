/*
 * =====================================================================================
 *
 *       Filename:  bubble.c
 *
 *    Description:  冒泡排序
 *    				1 i,j 不同向 i 遍历一遍列表 j 遍历 从 0 -- i 比较相邻两个数大的下沉
 *					小的上升
 *					2 设置一个标志，用来设置这一趟是否发生变化，如果没有发生变换则说明
 *					  已经排完了
 *					3 将标志设为最后一次变换的位置，这样已排好序的部分就无需再排序
 *        Version:  1.0
 *        Created:  2013年07月06日 21时21分54秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lishan (xviubu), xviubu@gmail.com
 *        Company:  qdu
 *
 * =====================================================================================
 */

#include <stdio.h>
#define FALSE 0
#define TRUE 1
void swap(int *x,int *y)
{
	int tmp = *x;
	*x = *y;
	*y = tmp;
}
void bubble_sort(int A[],int n)
{
	int i,j,flag = TRUE;
	while(flag)
	{
		flag = FALSE;
		for(i=n-1;i>0;i--)
		{
			for(j=0;j<i;j++)
			{
				if(A[j] > A[j+1])
				{
					swap(&A[j],&A[j+1]);
					flag = TRUE;
				}
			}
		}
	}
}
void bubble_sort_pos(int A[],int n)
{
	int i,k,flag;
	flag = n-1;

	while(flag > 0)
	{
		k = flag ;
		flag = 0;
		for(i=0;i<k;i++)
		{
			if(A[i] > A[i+1])
			{
				swap(&A[i],&A[i+1]);
				flag = i;
			}
		}
	}
}
void main()
{
	int i, A[8] = {2,8,7,1,6,5,3,4};
	bubble_sort_pos(A,8);
	for(i=0;i<8;i++)
		printf("%d\t",A[i]);
}
/********************************
 * 2     2    2-|  1   1     
 * 8-|   7-|  1 |--2   2
 * 7 |   1 |  6-|  5   3 
 * 1 |   6 |  5 |  3   4
 * 6 |   5 |  3 |  4   5
 * 5 |   3 |  4 |--6   6
 * 3 |   4 |--7    7   7
 * 4 |-- 8    8    8   8 
 * T     T    T    T   F
 * ***********************************/
