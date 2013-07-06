/*
 * =====================================================================================
 *
 *       Filename:  lucky.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月04日 17时50分49秒 CST
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

#define FALSE 0
#define TRUE 1

int is_prime(int num)
{
	int i;
	if(num <= 1)
		return FALSE;
	if(num == 2)
		return TRUE;
	if(num % 2 ==0 ) 
		return num==2;
	if(num % 3 == 0)
		return num==3;
	if(num % 5 == 0)
		return num ==5; 
	for(i=7;i*i<=num;i+= 2)
	{
		if(num % i == 0)
			return FALSE;
	}
	return TRUE;
}

void lucky_num(int low,int high)
{
	int i,x,y,sum1,sum2;
	if(low <= high)
	{
		for(i=low;i<=high;i++)
		{	
			x = i;
			sum1 = 0;	
			sum2 = 0;
			while(x != 0)	
			{
				y = x % 10;   
				x = x / 10 ;
				sum1 += y; 
				sum2 += y*y;
			}
			if(is_prime(sum1) && is_prime(sum2))
				printf("%d\t",i);
		
		}
	}
	else
		printf("first number  must less than second number\n");
}

int main()
{
	int low=1 , high=20;
	lucky_num(low,high);
	return 0;
}
