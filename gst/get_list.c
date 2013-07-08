/*
 * =====================================================================================
 *
 *       Filename:  get_list.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月07日 17时19分02秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lishan (xviubu), xviubu@gmail.com
 *        Company:  qdu
 *
 * =====================================================================================
 */

#include <gst/gst.h>
#include <gst/gstelementfactory.h>

int main(int argc,char **argv)
{
	GstElementFactory * factory;

	gst_init(&argc,&argv);

	if(!(factory = gst_element_factory_find("audiotestsrc")))
	{
		g_print("Failed to find audiotestsrc\n");
		return -1;
	}

	g_print("The %s element is a member of the category %s . \n",gst_plugin_feature_get_name(GST_PLUGIN_FEATURE(factory)),
			gst_element_factory_get_klass(factory));

	return 0;
}
