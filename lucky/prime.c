/*
 * =====================================================================================
 *
 *       Filename:  prime.c
 *													1 000 000	  10 000 000	100 000 000	  8 300 000
 *		Description: 基本算法
 *      		  1	 原始版本 测试从1到n个数 		2:38.06s
 *    			  2	 改进版  1--->n/2+1  			1:19.60s
 *    			  3	 继续改进 1--->n的根 			1.721s    	    37.808s
 *    			  4	 将 sqrt(n) 改进 为 i*i < n     1.213s     		11.922s     4:38.52 
 *				  5  除去2,3,5的倍数				1.119s          10.068s     2:19.19        8.350
 *
 * 				  	 筛选算法
 *				  1  埃拉托斯特尼算法  				1.821s                                     8.430s 
 *        Version:  1.0
 *        Created:  2013年07月04日 18时58分55秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lishan (xviubu), xviubu@gmail.com
 *        Company:  qdu
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <math.h>
#include <string.h>
#define FALSE 0
#define TRUE 1
#define MAX 10000000
int is_prime(int n)
{
	int i;
	if(n <= 1)
		return FALSE;
	if(n == 2)
		return TRUE;
//  for(i = 2;i<n;i++)
//	for(i=2;i<n/2+1;i++)
//	for(i=2;i<sqrt(n);i++)
//	for(i=2;i*i<n;i++)
	if(n % 2 == 0)
		return n == 2;
	if(n % 3 == 0)
		return n == 3;
	if(n % 5 == 0)
		return n == 5;
	for(i=7;i*i<=n;i += 2)
	{
		if(n % i == 0)
			return FALSE;
	}
	return TRUE;
}
/*****************************
 * 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
 * 2 3   5   7   9    11    13    15    17    19    21    23    25    27    29   干掉2的倍数
 * 2 3   5   7        11    13          17    19          23                29   干掉3的倍数
 * 2 3   5   7        11    13          17    19          23                29   干掉5的倍数
 * 因为 5×7>30了所以可以停止
 */

void eratosthenes(int n)
{
	char  boolean[n];
	int i,j,k;
/*	for(i=2;i<n;i++)
	{
		boolean[i]=TRUE; //i 为数 boolean[i] 为 是否为素数
	}
	*/
	memset(boolean,'1',n);
	for(i=2;i*i<n;i++)
	{
		if(boolean[i] == '1')
		{
			for(j=i*i;j<n;j+=i)
			{
				if(j % i == 0)
					boolean[j] = '0';
			}
		}
	}
   	
    for(i=2;i<n;i++)
	{
		if(boolean[i] == '1')
			printf("%d\t",i);
	}
} 

int main()
{
	int x;
	for(x=1;x<MAX;x++)
	{
		if(is_prime(x))
			printf("%d\t",x);
	}
	
//	eratosthenes(MAX);
	return 0;
}
