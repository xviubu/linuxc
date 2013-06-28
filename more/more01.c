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
#include <sys/ioctl.h>

#define LINELEN 512
int PAGELEN;
int PAGECOUNT = 1;
int LINECOUNT;
off_t file_size;
off_t file_pos;
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
	int reply;
	int num_of_lines = 0;
	FILE * fp_tty ;
	struct winsize size;
	struct termios term,save_term;   
	struct stat buf;
	if((fp_tty = fopen("/dev/tty","r")) == NULL)
		exit(1);
	/*获取终端屏幕大小*/
	if(ioctl(fileno(fp_tty),TIOCGWINSZ,&size) == -1)
		perror("get term size failed \n");
	PAGELEN = size.ws_row;
	/*获取文件大小*/
	if(fstat(fileno(fp),&buf) < 0)
		perror("get file stat failed\n");
	file_size = buf.st_size;
	/* 改变终端的属性为无回显按下q 或 ' ' 无需再按Enter即可执行*/
	if(tcgetattr(fileno(fp_tty),&term) < 0)
		perror("tcgetattr failed\n");
	save_term = term;
	term.c_lflag &= ~( ECHO | ICANON); 
	if(tcsetattr(fileno(fp_tty),TCSANOW,&term) < 0)
		perror("tcsetattr failed\n");
	while(fgets(line,LINELEN,fp))
	{
		file_pos = ftello(fp);
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
		perror("restore from save_term failed \n");
}

int see_more(FILE * cmd)
{
	int c;
	printf("\033[7m %d---more--- %2.2f%%  \033[m",PAGECOUNT,file_pos*100.0/file_size);
	while((c=getc(cmd)) != EOF)
	{
		if(c == 'q')
			return 0;
		if(c == ' ')
		{
			printf("\033[J"); //清屏  VT100控制码
			PAGECOUNT ++;
			printf("\033[B\033[2K"); //光标下移一行并删除该行
			return PAGELEN;
		}
		if(c == '\n')
		{
			printf("\033[B\033[2K"); //光标下移一行并删除该行
			LINECOUNT++;
			if(LINECOUNT == PAGELEN)
			{
				PAGECOUNT++;
				LINECOUNT = 0;
			}
			return 1;
		}
	}

	return 0;
}

