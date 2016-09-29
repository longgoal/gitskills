/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2, as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

#include <gio/gio.h>

#include "capi.h"


int running = 1;
static gchar *_global_title = NULL;
static int _global_date = 0;
/*
static void uds_cb(struct ustream *s, int bytes)
{
	struct ustream_buf *buf = s->r.head;
	char *str;
	int len;

	do {
		str = ustream_get_read_buf(s, NULL);
		if (!str)
			break;
		len = strlen(buf->data);
		if (!len) {
			bytes -= 1;
			ustream_consume(s, 1);
			continue;
		}

		ustream_consume(s, len);
		bytes -= len;
	} while (bytes > 0);
}

struct ustream_fd uds = {
	.stream.string_data = true,
	.stream.notify_read = uds_cb,
};
*/
/* Introspection data for the service we are exporting */

static const unsigned char intro_xml[] =
	"<node>"
	"  <interface name='com.thundersoft.testapp1.intf2'>"
	"    <method name='testapp1Config'>"
	"      <arg type='s' name='name' direction='in'/>"
	"	   <arg type='i' name='response' direction='out'/>"
	"    </method>"
	"    <method name='testapp1Func1'>"
	"      <arg type='s' name='name' direction='in'/>"
	"	 <arg type='s' name='response' direction='out'/>"
	"    </method>"
	"    <method name='testapp1Func2' >"
	"      <arg type='s' name='name' direction='in'/>"
	"	   <arg type='s' name='response' direction='out'/>"
	"    </method>"
	"    <method name='testapp1ReadOption' >"
	"	   <arg type='s' name='section_name' direction='in'/>"
	"	   <arg type='s' name='option' direction='in'/>"
	"	   <arg type='s' name='value' direction='out'/>"
	"    </method>"
	"    <method name='testapp1WriteOption' >"
	"	   <arg type='s' name='section_name' direction='in'/>"
	"	   <arg type='s' name='option' direction='in'/>"
	"	   <arg type='s' name='value' direction='in'/>"
	"    </method>"
	"    <method name='testapp1ReadSectionByName' >"
	"	   <arg type='s' name='section_name' direction='in'/>"
	"    </method>"
	"    <method name='testapp1ReadSectionByType' >"
	"	   <arg type='s' name='section_type' direction='in'/>"
	"    </method>"
	"    <signal name='testapp1Signal'>"
    "    </signal>"
	"	 <property type='s' name='testapp1Title' access='readwrite'/>"
	"	 <property type='i' name='testapp1Date' access='readwrite'/>"
	"	 <property type='s' name='testapp1ReadingAlwaysThrowsError' access='read'/>"
	"	 <property type='s' name='testapp1WritingAlwaysThrowsError' access='readwrite'/>"
	"  </interface>"
	"</node>";

/*
zengchen add property set and get
*/

int testCtSgwDBusPropSetFunction ( const char *path,
                                           const char *prop,
                                           GVariant *value,
                                           void *userdata)
										 {
	 if (g_strcmp0 (prop, "testapp1Title") == 0)
    { 
	  CtSgwLog(LOG_NOTICE, "testCtSgwDBusPropSetFunction testapp1Title\n");
	  g_print("testCtSgwDBusPropSetFunction testapp1Title\n");	
      if (g_strcmp0 (_global_title, g_variant_get_string (value, NULL)) != 0)
        {
          g_free (_global_title);
          _global_title = g_variant_dup_string (value, NULL);
        }									 
	}
	else if(g_strcmp0 (prop, "testapp1Date") == 0)
	{
	     CtSgwLog(LOG_NOTICE, "testCtSgwDBusPropSetFunction testapp1Date\n");
	     g_print("testCtSgwDBusPropSetFunction testapp1Date\n");	
	     _global_date= g_variant_get_int32(value);

    }	
 }

int testCtSgwDBusPropGetFunction ( const char    *path,
                                           const char    *prop,
                                           GVariant     **value,
                                           void          *userdata){
	int ret =0;
 if (g_strcmp0 (prop, "testapp1Title") == 0)
    { 
	 CtSgwLog(LOG_NOTICE, "testCtSgwDBusPropGetFunction testapp1Title\n");
	 g_print("testCtSgwDBusPropGetFunction testapp1Title\n");
      if (_global_title == NULL)
        _global_title = g_strdup ("Back To C!");
      *value = g_variant_new_string (_global_title);

    }
 else if (g_strcmp0 (prop, "testapp1Date") == 0)
    { 
       CtSgwLog(LOG_NOTICE, "testCtSgwDBusPropGetFunction testapp1Date\n"); 
       g_print("testCtSgwDBusPropGetFunction testapp1Date\n");
      //if (_global_title == NULL)
       // _global_title = g_strdup ("Back To C!");
      *value = g_variant_new_int32(_global_date);

    }
  else if (g_strcmp0 (prop, "ReadingAlwaysThrowsError") == 0)
    {
      /*g_set_error (error,
                   G_IO_ERROR,
                   G_IO_ERROR_FAILED,
                   "Hello %s. I thought I said reading this property "
                   "always results in an error. kthxbye",
                   sender);*/
      *value = g_variant_new_string ("I thought I said reading this property,always results in an error");
	  ret =-1;             
                   
    }
  else if (g_strcmp0 (prop, "WritingAlwaysThrowsError") == 0)
    {
      *value = g_variant_new_string ("There's no home like home");
	  ret =-1;
    }


  return ret;									   
										 
 }

int testCtSgwDBusPropGetAllFunction ( const char *path,
                                              GVariant  **value,
                                              void       *userdata){
CtSgwLog(LOG_NOTICE, "testCtSgwDBusPropGetAllFunction\n"); 
												  
		GVariantBuilder *builder;									  
		builder = g_variant_builder_new (G_VARIANT_TYPE_ARRAY);
        g_variant_builder_add (builder,
                                 "{sv}",
                                 "testapp1Title",
                                 g_variant_new_string (_global_title));	
        g_variant_builder_add (builder,
                                 "{sv}",
                                 "testapp1Date",
                                 g_variant_new_int32 (_global_date));	
        *value   =   g_variant_builder_end(builder);							 
 }

int testCtSgwDBusPropSetMultiFunction ( const char    *path,
                                                GVariant      *value,
                                                void          *userdata){
	GVariantIter * _iter;  
    GVariant * _item, *itemvalue; 											
	 _iter   =   g_variant_iter_new( value );  
    char *prop;
CtSgwLog(LOG_NOTICE, "testCtSgwDBusPropSetMultiFunction\n");
	g_print("testCtSgwDBusPropSetMultiFunction\n");
    while( g_variant_iter_next( _iter, "sv", &_item ))  
    {  
       g_variant_get( _item,"sv",prop,itemvalue);
	 if (g_strcmp0 (prop, "testapp1Title") == 0)
        {  g_print("testCtSgwDBusPropSetMultiFunction testapp1Title\n");		
      if (g_strcmp0 (_global_title, g_variant_get_string (itemvalue, NULL)) != 0)
        {
          GVariantBuilder *builder;
          GError *local_error;

          g_free (_global_title);
          _global_title = g_variant_dup_string (itemvalue, NULL);

        }									 
	}
	else if(g_strcmp0 (prop, "testapp1Date") == 0)
	{
	     g_print("testCtSgwDBusPropSetMultiFunction testapp1Date\n");	
	     _global_date= g_variant_get_int32(value);
		 
		 
    }	       
    }  											 										 
 }

int testCtSgwDBusMethodFunction ( const char    *path,
                                          const char    *interface,
                                          const char    *method,
                                          GVariant      *inargs,
                                          GVariant     **outargs,
                                          void          *userdata){
										  
	gchar *section, *option, *value;
	uint32_t size = 0, i = 0;
	CtSgwUCIOpt_t *opts = NULL;
CtSgwLog(LOG_NOTICE, "testCtSgwDBusMethodFunction\n");
g_print("testCtSgwDBusMethodFunction\n");
	//g_print("%s,%d: call %s\n", __func__, __LINE__, method_name);
	if (g_strcmp0(method, "testapp1ReadOption") == 0) {

		CtSgwUCIOptVal_t value = {0};
		g_variant_get(inargs, "(&s&s)", &section, &option);

		CtSgwUCIReadOption("demoapp", section, option, value);

		*outargs = g_variant_new("(s)", value);
	} else if (g_strcmp0(method, "testapp1WriteOption") == 0) {

		g_variant_get(inargs, "(&s&s&s)", &section, &option, &value);

		CtSgwUCIWriteOption("demoapp", section, option, value);

	} else if (g_strcmp0(method, "testapp1ReadSectionByName") == 0) {

		g_variant_get(inargs, "(&s)", &section);

		CtSgwUCIReadSection("demoapp", NULL, section, &opts, &size);

		for (i = 0; i < size && opts; i++, opts++) {
			g_print("[%d] %s.%s.%s = %s\n", i, "demoapp", section, opts->name, opts->value);
		}
	} else if (g_strcmp0(method, "testapp1ReadSectionByType") == 0) {

		g_variant_get(inargs, "(&s)", &section);

		CtSgwUCIReadSection("demoapp", section, NULL, &opts, &size);

		for (i = 0; i < size && opts; i++, opts++) {
			g_print("[%d] %s.@%s[].%s = %s\n", i, "demoapp", section, opts->name, opts->value);
		}
	} else if (g_strcmp0(method, "testapp1Func1") == 0) {
		const gchar *name = NULL;
		char str[64] = {0};
g_print("testCtSgwDBusMethodFunction testapp1Func1\n");
		g_variant_get (inargs, "(&s)", &name);		

		sprintf(str, "Hello %s", name);
		*outargs = g_variant_new("(s)", str);
	} else if (g_strcmp0(method, "testapp1Func2") == 0) {
g_print("testCtSgwDBusMethodFunction testapp1Func2\n");	
		gchar *response = "Byebye2";
		*outargs = g_variant_new("(s)", response);
		g_print("CtSgwDBusEmitSignal\n");
	     CtSgwDBusEmitSignal(NULL, //*service_name,
			"/com/thundersoft/testapp1",//object_path,
			"com.thundersoft.testapp1.intf2",//interface_name,
			"testapp1Signal",//*signal_name,
			NULL);	
		//g_print("CtSgwDBusEmitSignal22\n");			
		// CtSgwDBusEmitSignal("com.thundersoft.demoapp1", //*service_name,
		//	"com.thundersoft.demoapp1",//"/com/thundersoft/testapp1",//object_path,
		//	"com.thundersoft.demoapp1.service",//interface_name,
		//	"testapp1Signal",//*signal_name,
		//	CtSgwVariantNew("(s)","testapp1Signal_name"));	
	}

	return 0;										  
										 
 }

int testCtSgwDBusSignalFunction ( const char    *sender_name,
                                          const char    *path,
                                          const char    *interface,
                                          const char    *signal,
                                          GVariant      *args,
                                          void          *userdata){
										 
 }


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

static const unsigned char config_global_xml[] =
	"<node>"
	"  <interface name='com.thundersoft.testapp1.Config.global'>"
	"	 <property type='s' name='testappproperty1' access='readwrite'/>"
	"	 <property type='s' name='testappproperty2' access='read'/>"
	"	 <property type='s' name='testappproperty3' access='readwrite'/>"
	"  </interface>"
	"</node>";

static int _config_handle_method_call(const char *section_name, const char *section_type, int section_idx,
								 const char           *method_name,
								 GVariant           *inargs,
								 GVariant           **outargs)
{
	const gchar *intf, *key, *val;
	GVariant *value;
	char cmd[128] = {0};

	if (g_strcmp0(method_name, "Get") == 0) {

		char line[64] = {0};
		int len = 0;
		FILE *fp = NULL;
		
		g_variant_get(inargs, "(&s&s)", &intf, &key);

		if (section_name)
			sprintf(cmd, "uci get testapp.%s.%s", section_name, key);
		else if (section_type)
			sprintf(cmd, "uci get testapp.@%s[%d].%s", section_type, section_idx, key);
		fp = popen(cmd, "r");
		if (fp) {
			fgets(line, 64, fp);
			len = strlen(line);
			if (line[len - 1] == '\n')
				line[len - 1] = '\0';	
			pclose(fp);
		}

		*outargs = g_variant_new("(v)", g_variant_new("s", line));
	} else if (g_strcmp0(method_name, "Set") == 0) {

		g_variant_get(inargs, "(&s&sv)", &intf, &key, &value);
		g_variant_get(value, "&s", &val);

		if (section_name)
			sprintf(cmd, "uci set testapp.%s.%s=%s", section_name, key, val);
		else if (section_type)
			sprintf(cmd, "uci set testapp.@%s[%d].%s=%s", section_type, section_idx, key, val);
			
		system(cmd);	
		system("uci commit demoapp");
	}

	return 0;
}

static int
config_global_hmcall(const char           *object_path,
								 const char           *interface_name,
								 const char           *method_name,
								 GVariant           *inargs,
								 GVariant           **outargs,
								 void *user_data)
{
	_config_handle_method_call("global", NULL, 0, method_name, inargs, outargs);
	return 0;
}


static CtSgwGDBusInterfaceVTable_t interface_vtable = { testCtSgwDBusMethodFunction, testCtSgwDBusPropGetFunction, testCtSgwDBusPropSetFunction, testCtSgwDBusPropGetAllFunction, testCtSgwDBusPropSetMultiFunction };

static CtSgwGDBusInterfaceVTable_t interface_global_vtable = { config_global_hmcall, NULL, NULL, NULL, NULL };

static int testapp_stop(void)
{
	running = 0;
	return 0;
}

static int testapp_reload(void)
{
	CtSgwLog(LOG_NOTICE, "reloaded\n");
	return 0;
}

static void test_register_methods(CtSgwDBusNodeInfo_t *intro, CtSgwDBusNodeInfo_t *config_g)
{
	guint registration_id;

	CtSgwLog(LOG_NOTICE, "%s: registering dbus object.", __func__);
	
	registration_id = CtSgwDBusRegisterObject("/com/thundersoft/testapp1",
					  intro->interfaces[0],
					  &interface_vtable,
					  NULL);
	g_assert(registration_id > 0);

//	registration_id = CtSgwDBusRegisterObject("/com/thundersoft/demoapp1/Config/global/global",
//					  config_g->interfaces[0],
//					  &interface_global_vtable,
//					  NULL);
	g_assert(registration_id > 0);

	//setup response for method: GetManagedObjects
	GDBusObjectManagerServer *manager = NULL;
	GDBusObjectSkeleton *skeleton;

	manager = g_dbus_object_manager_server_new("/com/thundersoft/testapp1/Config");

	skeleton = g_dbus_object_skeleton_new("/com/thundersoft/testapp1/Config/global/global");
	g_dbus_object_manager_server_export(manager, skeleton);

	//TODO: add api func to return connection
	g_dbus_object_manager_server_set_connection(manager, sgw_dbus_service_context->connection);


}

int main(int argc, char *argv[])
{
	CtSgwDBusNodeInfo_t *mm_data = NULL;
	CtSgwDBusNodeInfo_t *intro_data = NULL;
	CtSgwDBusNodeInfo_t *config_g_data = NULL;

	CtSgwAppMgtCallbacks_t app_cbs = { 
		.stop = testapp_stop,
		.reload = testapp_reload,
		.restore_factory = NULL,
		.post_msg = NULL
	};

	CtSgwLogOpen(LOG_USER, "testapp");

	CtSgwLog(LOG_NOTICE, "start\n");
	
	CtSgwDBusStartService("com.thundersoft.testapp1");

	intro_data = CtSgwDBusNodeParseXml(intro_xml);
	config_g_data = CtSgwDBusNodeParseXml(config_global_xml);

	test_register_methods(intro_data, config_g_data);

	mm_data = CtSgwAppRegisterMgtFuncs(&app_cbs);

	g_print("TESTAPP Running\n");
	while (running) {
		sleep(1);
	}
	g_print("TESTAPP Exiting\n");

	CtSgwDBusNodeInfoUnref(intro_data);
	CtSgwDBusNodeInfoUnref(config_g_data);
	CtSgwDBusNodeInfoUnref(mm_data);
	CtSgwDBusStopService();

	CtSgwLog(LOG_NOTICE, "exit\n");
	CtSgwLogClose();	

	return 0;
}

