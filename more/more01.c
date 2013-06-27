/*
 * =====================================================================================
 *
 *       Filename:  more01.c
 *
 *    Description:  read and print 24 lines then pause for a few special commands
 *
 *        Version:  1.0
 *        Created:  2013年06月27日 21时26分15秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lishan (xviubu), xviubu@gmail.com
 *        Company:  qdu
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#define PAGELEN 24
#define LINELEN 512

void do_more(FILE *);
int see_more(FILE *);

int main(int argc,char **argv)
{
	FILE *fp;
	if(argc == 1)
		do_more(stdin);
	else
		while(--argc)
		{
			if((fp=fopen(*++argv,"r")) != NULL)
			{
				do_more(fp);
				fclose(fp);
			}
			else
				exit(1);
		}
	return 0;
}

void do_more(FILE * fp)
{
	char line[LINELEN];
	int num_of_lines = 0;
	int reply;
	FILE * fp_tty ;
	if((fp_tty = fopen("/dev/tty","r")) == NULL)
		exit(1);
	/* 改变终端的属性为无回显按下q 或 ' ' 无需再按Enter即可执行*/
	struct termios term,save_term;   
	if(tcgetattr(fileno(fp_tty),&term) < 0)
		printf("tcgetattr failed\n");
	save_term = term;
	term.c_lflag &= ~( ECHO | ICANON); 
	if(tcsetattr(fileno(fp_tty),TCSANOW,&term) < 0)
		printf("tcsetattr failed\n");
	while(fgets(line,LINELEN,fp))
	{
		if(num_of_lines == PAGELEN)
		{
			reply = see_more(fp_tty);
			if(reply == 0)
			{
				break;
			}
			num_of_lines -= reply;
		}
		if(fputs(line,stdout) == EOF)
			exit(1);
		num_of_lines++;
	}
	if(tcsetattr(fileno(fp_tty),TCSANOW,&save_term) < 0)
		printf("restore from save_term failed \n");
}

int see_more(FILE * cmd)
{
	int c;
	printf("\033[7m more? \033[m");
	while((c=getc(cmd)) != EOF)
	{
		if(c == 'q')
			return 0;
		if(c == ' ')
			return PAGELEN;
		if(c == '\n')
			return 1;
	}

	return 0;
}
