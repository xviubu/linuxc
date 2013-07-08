/*
 * =====================================================================================
 *
 *       Filename:  oggplayer.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年07月07日 18时39分53秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lishan (xviubu), xviubu@gmail.com
 *        Company:  qdu
 *
 * =====================================================================================
 */

#include <gst/gst.h>

GstElement *pipeline,*source,*parser,*decoder,*conv,*sink;
/*消息处理器*/
static gboolean bus_call(GstBus *bus,GstMessage *msg,gpointer data)
{
	GMainLoop *loop = data;  

	gchar * debug;
	GError * err;
	switch(GST_MESSAGE_TYPE(msg))
	{
		case GST_MESSAGE_EOS : 
			g_print("End_Of_Stream\n");
			g_main_loop_quit(loop);
			break;
		case GST_MESSAGE_ERROR:
			gst_message_parse_error(msg,&err,&debug);
			g_free(debug);

			g_print("Error:%s\n",err->message);
			g_error_free(err);

			g_main_loop_quit(loop);
			break;
		default:
			break;

	}

	return 1;
}
//动态创建接受pad
static void new_pad(GstElement *element,GstPad * pad,gpointer data)
{
	GstPad *sinkpad;
	g_print("Dynamic pad created, linking parser/decoder\n");

	sinkpad = gst_element_get_pad(decoder,"sink");
	gst_pad_link(pad,sinkpad);

	gst_object_unref(sinkpad);
}

int main(int argc,char **argv)
{
	GMainLoop *loop; // Glib or GTK main event loop
	GstBus *bus;

	gst_init(&argc,&argv);

	loop = g_main_loop_new(NULL,FALSE); //g_main_loop_new(GMainContext *context,gboolean is_running) 
										// NULL ---- 默认的context 会被使用   is_running : TRUE 正在运行

	if(argc!=2)
	{
		g_print("Usage:%s<Ogg/Vorbis filename>\n",argv[0]);
		return -1;
	}

	if(!(pipeline = gst_pipeline_new("audio-player")))  // 以给予的名字创建一个pipeline
	{
		g_print("pipeline created failed\n");
		return -1;
	}
	if(!(source = gst_element_factory_make("filesrc","file-source"))) // 第一个参数为factory,创建输入源 
	{
		g_print("source created failed\n");
		return -1;
	}
	if(!(parser = gst_element_factory_make("oggdemux","ogg-parser")))  //创建解析器
	{
		g_print("parser created failed\n");
		return -1;
	}
	if(!(decoder = gst_element_factory_make("vorbisdec","vorbis-decoder"))) //解码器
	{
		g_print("decoder created failed\n");
		return -1;
	}
	if(!(conv = gst_element_factory_make("audioconvert","converter")))//转换器
	{
		g_print("conv created failed\n");
		return -1;
	}
	if(!(sink = gst_element_factory_make("alsasink","alsa-output")))//输出到声卡
	{
		g_print("sink created failed\n");
		return -1;
	}

	g_object_set(G_OBJECT(source),"location",argv[1],NULL); //Glib 将source的属性 location 设为 argv[1]

	bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline)); // 得道pipeline 的bus ，bus可以用来接受Message
	gst_bus_add_watch(bus,bus_call,loop);//将消息处理器添加到bus上以监听是否有消息产生
	gst_object_unref(bus);

	gst_bin_add_many(GST_BIN(pipeline),source,parser,decoder,conv,sink,NULL);//将所有的元素都添加到箱柜中 
//  gst_bin_add_many(GstBin *bin, GstElement * elementl ,...)  elementl : 元素列表 ... ：附加元素不是GstElement

	gst_element_link(source,parser); //(src,dest) 在使用之前必须将元素添加到箱柜中
	gst_element_link_many(decoder,conv,sink,NULL);//unlink 解除link
	g_signal_connect(parser,"pad-added",G_CALLBACK(new_pad),NULL);

	g_print("Setting to playing\n");
	gst_element_set_state(pipeline,GST_STATE_PLAYING); //启动pipeline NULL READY PLAYING  PAUSED
	g_print("Running\n");
	g_main_loop_run(loop);

	g_print("Returned,stopping playing\n");
	gst_element_set_state(pipeline,GST_STATE_NULL);
	g_print("Deleting pipeline\n");
	gst_object_unref(pipeline);

	return 0;

}
