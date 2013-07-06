/*
 * =====================================================================================
 *
 *       Filename:  quick.c
 *
 *    Description:  quick sort  HOARE-PARTITION
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
	i = p;
	j = r;
	while(1)
	{
		while(A[j] > x)
			j--;
		while(A[i] < x)
			i++;
		if(i<j)
		{
			swap(&A[i],&A[j]);
		}
		else
			return j;
	}
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
/**************************************************
 * HOARE-PARTITION
 * HOARE-PARTITION(A,p,r)
 * x= A[p]
 * i = p-1
 * j = r+1
 * while TRUE
 * 		do repeat j=j-1
 * 		   until A[j] <= x
 * 		   repeat i=i+1	
 * 		   until A[i] >= x
 * 		if i<j
 * 		then
 * 			exchange A[i] <--> A[j]
 * 			else
 * 				return j
 *************************************************/
