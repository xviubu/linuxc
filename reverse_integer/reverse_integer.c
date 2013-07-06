/*
 * =====================================================================================
 *
 *       Filename:  reverse_integer.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月01日 18时41分10秒 CST
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

int reverse(int );
int nbits(int x);
int reverse(int x)
{
	int count = nbits(x);
	int y=0,r=0;
	while( x != 0)
	{
		y = x % 10;
		x = x / 10;
		r += y * pow(10,--count);
		
	}
	return r;

}
int nbits(int x)
{
	int count = 0;
	while(x != 0)
	{
		x=x/10;
		count ++;
	}
	return count;
}
int main()
{
	int n;
	printf("Please input a integer:");
	scanf("%d",&n);

	printf("%d",reverse(n));
}

