/*
 * =====================================================================================
 *
 *       Filename:  mu.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月07日 15时38分15秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lishan (xviubu), xviubu@gmail.com
 *        Company:  qdu
 *
 * =====================================================================================
 */

#include <gst/gst.h>
int main(int argc,char **argv)
{
	const gchar *nano_str;
	guint major,minor,micro,nano;
	
	gst_init(&argc,&argv);
	gst_version(&major,&minor,&micro,&nano);

	if(nano == 1)
		nano_str = "(CVS)";
	else if(nano == 2)
		nano_str ="(Prerelease)";
	else 
		nano_str = "";

	printf("This program is linked against GStreamer %d.%d.%d %s\n",major,minor,micro,nano_str);

	return 0;

}
