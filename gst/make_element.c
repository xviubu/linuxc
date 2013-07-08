/*
 * =====================================================================================
 *
 *       Filename:  element.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月07日 15时58分45秒 CST
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
	GstElement  * element;
	gst_init(&argc,&argv);

	element = gst_element_factory_make("fakesrc","source");
	if(!element)
	{
		g_print("Failed to create element of fakesrc \n");
		return -1;
	}
	else
		g_print("OK");

	gst_object_unref(element);

	return 0;

	
}
