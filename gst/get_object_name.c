/*
 * =====================================================================================
 *
 *       Filename:  get_object_name.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月07日 16时13分58秒 CST
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
	GstElement *element;
	gchar *name;

	gst_init(&argc,&argv);

	element = gst_element_factory_make("fakesrc","source");

	g_object_get(element,"name",&name,NULL);
	g_print("The name of element is %s\n",name);

	g_free(name);
	gst_object_unref(element);

	return 0;
}
