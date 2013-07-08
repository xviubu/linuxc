/*
 * =====================================================================================
 *
 *       Filename:  quick.c
 *
 *    Description:  quick sort  以最后一个元素作为比较对象
 *    				N.Lomto Partition
 *    				i j 同向j 扫描整个列表一遍，当遇到比x小的数i++ 交换A[i] 与 A[j]
 *    				i 只会出现在比x小的数
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
	x = A[r];
	i = p-1;
	for(j=p;j<r;j++)
	{
		if(A[j] <= x)
		{
			i++;
			swap(&A[i],&A[j]);
		}
	}
	swap(&A[i+1],&A[r]);
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
