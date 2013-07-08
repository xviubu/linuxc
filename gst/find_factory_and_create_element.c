/*
 * =====================================================================================
 *
 *       Filename:  find_factory_and_create_element.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月07日 16时05分04秒 CST
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
	GstElement * element;
	GstElementFactory * factory;

	gst_init(&argc,&argv);
	if((factory=gst_element_factory_find("fakesrc")) == 0)
	{
		g_print("Failed to find factory fakesrc\n");
		return -1;
	}

	if((element=gst_element_factory_create(factory,"source")) == 0)
	{
		g_print("Failed to create element\n");	
		return -1;
	}

	g_print("Everything is OK\n");

	gst_object_unref(element);
	gst_object_unref(factory);

	return 0;
}
