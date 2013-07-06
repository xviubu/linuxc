/*
 * =====================================================================================
 *
 *       Filename:  quick.c
 *
 *    Description:  quick sort  以第一个元素作为比较对象
 *
 *        Version:  1.0
 *        Created:  2013年07月02日 12时15分56秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lishan (xviubu), xviubu@gmail.com
 *        Company:  qdu
 *
 * =====================================================================================
 */

#include <stdio.h>

void swap(int *x ,int * y)
{
	int tmp = *x;
	*x = *y;
	*y = tmp;
}
int partition(int A[],int p ,int r)
{
	int x,i,j;
	x = A[p];
	i=p;j=r;
	while( i != j)
	{
		while(A[j] > x && i < j)
			j--;
		if(i<j)
		{
			A[i] = A[j];
			i++;
		}
		while(A[i] < x && i < j)
			i++;
		if(i<j)
		{
			A[j] = A[i];
			j--;
		}
	}
	A[i] = x;
	return i;
}
void quick_sort(int A[],int p ,int r)
{
	int q;
	if(p < r)
	{
		q = partition(A,p,r);
		quick_sort(A,p,q-1);
		quick_sort(A,q+1,r);
	}
} 

void main()
{
	int a[8] = {2,8,7,1,3,5,6,4};
	int i;
	quick_sort(a,0,7);
	for(i=0;i<8;i++) 
		printf("%d\t",a[i]);
}
