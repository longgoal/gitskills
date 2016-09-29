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
//#include "demolib.h"

int running = 1;

typedef struct {
	GDBusInterfaceSkeleton parent;
	gint number;
} DemoInterface;

typedef struct {
	GDBusInterfaceSkeletonClass parent_class;
} DemoInterfaceClass;

static GType demo_interface_get_type(void);
G_DEFINE_TYPE(DemoInterface, demo_interface, G_TYPE_DBUS_INTERFACE_SKELETON);

	static void
demo_interface_init(DemoInterface *self)
{
	//do nothing
}

	static GDBusInterfaceInfo *
demo_interface_get_info(GDBusInterfaceSkeleton *skeleton)
{
	static GDBusPropertyInfo key1_info = {
		-1,
		"key1",
		"s",
		G_DBUS_PROPERTY_INFO_FLAGS_READABLE | G_DBUS_PROPERTY_INFO_FLAGS_WRITABLE,
		NULL,
	};

	static GDBusPropertyInfo key2_info = {
		-1,
		"key2",
		"s",
		G_DBUS_PROPERTY_INFO_FLAGS_READABLE | G_DBUS_PROPERTY_INFO_FLAGS_WRITABLE,
		NULL,
	};
	static GDBusPropertyInfo key3_info = {
		-1,
		"key3",
		"s",
		G_DBUS_PROPERTY_INFO_FLAGS_READABLE | G_DBUS_PROPERTY_INFO_FLAGS_WRITABLE,
		NULL,
	};

	static GDBusPropertyInfo *property_info[] = {
		&key1_info, &key2_info, &key3_info,
		NULL
	};

	static GDBusInterfaceInfo interface_info = {
		-1,
		(gchar *) "com.thundersoft.demoapp1.Config.section",
		NULL,
		NULL,
		(GDBusPropertyInfo **) &property_info,
		NULL
	};

	return &interface_info;
}

static void _get_uci_section_val(const char *section_type, int idx, const char *opt_name, char *opt_val)
{
	char line[64] = {0};
	int len = 0;
	FILE *fp = NULL;
	char cmd[128] = {0};

	sprintf(cmd, "uci get demoapp.@section[%d].%s", idx, opt_name);
	fp = popen(cmd, "r");

	if (fp) {
		fgets(line, 64, fp);
		len = strlen(line);

		if (line[len - 1] == '\n')
			line[len - 1] = '\0';

		pclose(fp);
	}

	g_strlcpy(opt_val, line, 32);
	return;
}

	static GVariant *
demo_interface_get_property(GDBusConnection *connection,
		const gchar *sender,
		const gchar *object_path,
		const gchar *interface_name,
		const gchar *property_name,
		GError **error,
		gpointer user_data)
{
	DemoInterface *self = user_data;

	if (g_strstr_len(property_name, -1, "key")) {
		char val[32] = {0};
		_get_uci_section_val("section", self->number, property_name, val);
		return g_variant_new_string(val);
	} else
		return NULL;
}

static gboolean demo_interface_set_property(GDBusConnection       *connection,
		const gchar           *sender,
		const gchar           *object_path,
		const gchar           *interface_name,
		const gchar           *property_name,
		GVariant              *value,
		GError               **error,
		gpointer               user_data)
{
	DemoInterface *self = user_data;
	char cmd[128] = {0};
	gchar *val;

	if (g_strstr_len(property_name, -1, "key")) {
		g_variant_get(value, "&s", &val);

		sprintf(cmd, "uci set demoapp.@section[%d].%s=%s", self->number, property_name, val);
		system(cmd);
		system("uci commit demoapp");
	}

	return TRUE;
}

	static GDBusInterfaceVTable *
demo_interface_get_vtable(GDBusInterfaceSkeleton *interface)
{
	static GDBusInterfaceVTable vtable = {
		NULL,
		demo_interface_get_property,
		demo_interface_set_property,
	};

	return &vtable;
}

	static GVariant *
demo_interface_get_properties(GDBusInterfaceSkeleton *interface)
{
	GVariantBuilder builder;
	GDBusInterfaceInfo *info;
	GDBusInterfaceVTable *vtable;
	guint n;

	info = g_dbus_interface_skeleton_get_info(interface);
	vtable = g_dbus_interface_skeleton_get_vtable(interface);

	g_variant_builder_init(&builder, G_VARIANT_TYPE("a{sv}"));

	for (n = 0; info->properties[n] != NULL; n++) {
		if (info->properties[n]->flags & G_DBUS_PROPERTY_INFO_FLAGS_READABLE) {
			GVariant *value;
			g_return_val_if_fail(vtable->get_property != NULL, NULL);
			value = (vtable->get_property)(g_dbus_interface_skeleton_get_connection(interface), NULL,
					g_dbus_interface_skeleton_get_object_path(interface),
					info->name, info->properties[n]->name,
					NULL, interface);

			if (value != NULL) {
				g_variant_take_ref(value);
				g_variant_builder_add(&builder, "{sv}", info->properties[n]->name, value);
				g_variant_unref(value);
			}
		}
	}

	return g_variant_builder_end(&builder);
}

	static void
demo_interface_flush(GDBusInterfaceSkeleton *skeleton)
{
	//do nothing
}

	static void
demo_interface_class_init(DemoInterfaceClass *klass)
{
	GDBusInterfaceSkeletonClass *skeleton_class = G_DBUS_INTERFACE_SKELETON_CLASS(klass);
	skeleton_class->get_info = demo_interface_get_info;
	skeleton_class->get_properties = demo_interface_get_properties;
	skeleton_class->flush = demo_interface_flush;
	skeleton_class->get_vtable = demo_interface_get_vtable;
}


static const unsigned char intro_xml[] =
"<node>"
"  <interface name='com.thundersoft.demoapp1.service'>"
"    <method name='demoapp1Config'>"
"      <arg type='s' name='name' direction='in'/>"
"	 <arg type='i' name='response' direction='out'/>"
"    </method>"
"    <method name='demoapp1Func1'>"
"      <arg type='s' name='name' direction='in'/>"
"	 <arg type='s' name='response' direction='out'/>"
"    </method>"
"    <method name='demoapp1Func2' >"
"	   <arg type='s' name='response' direction='out'/>"
"    </method>"
"	 <property type='s' name='demoapp1Title' access='readwrite'/>"
"	 <property type='s' name='demoapp1ReadingAlwaysThrowsError' access='read'/>"
"	 <property type='s' name='demoapp1WritingAlwaysThrowsError' access='readwrite'/>"
"  </interface>"
"</node>";


	static int
handle_method_call(const char           *object_path,
		const char           *interface_name,
		const char           *method_name,
		GVariant            *inargs,
		GVariant            **outargs,
		void                      *user_data)
{
	//g_print("%s,%d: call %s\n", __func__, __LINE__, method_name);

	if (g_strcmp0(method_name, "Func1") == 0) {
		const gchar *name = NULL;
		char str[64] = {0};

		g_variant_get(inargs, "(&s)", &name);

		sprintf(str, "Hello %s", name);
		*outargs = g_variant_new("(s)", str);
	} else if (g_strcmp0(method_name, "Func2") == 0) {

		GDBusConnection *connection;
		GDBusProxy *proxy;
		GError *error = NULL;
		GVariant *result;
		const gchar *str = NULL;

		connection = g_bus_get_sync(DBUS_TYPE, NULL, &error);
		g_assert_no_error(error);

		proxy = g_dbus_proxy_new_sync(connection,
				G_DBUS_PROXY_FLAGS_NONE,
				NULL, 				  /* GDBusInterfaceInfo */
				"com.thundersoft.testapp1", /* name */
				"/com/thundersoft/testapp1", /* object path */
				"com.thundersoft.testapp1.intf2",		  /* interface */
				NULL, /* GCancellable */
				&error);
		g_assert_no_error(error);

		result = g_dbus_proxy_call_sync(proxy,
				"Func2",
				NULL,
				G_DBUS_CALL_FLAGS_NONE,
				-1,
				NULL,
				&error);
		g_assert_no_error(error);
		g_assert(result != NULL);
		g_variant_get(result, "(&s)", &str);

		*outargs = g_variant_new("(s)", str);

		g_variant_unref(result);
		g_object_unref(proxy);
		g_object_unref(connection);
	}

	return 0;
}

static const unsigned char config_global_xml[] =
"<node>"
"  <interface name='com.thundersoft.demoapp1.Config.global'>"
"	 <property type='s' name='demoappproperty1' access='readwrite'/>"
"	 <property type='s' name='demoappproperty2' access='readwrite'/>"
"	 <property type='s' name='demoappproperty3' access='readwrite'/>"
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


	if (g_strcmp0(method_name, "Set") == 0) {

		g_variant_get(inargs, "(&s&sv)", &intf, &key, &value);
		g_variant_get(value, "&s", &val);

		if (section_name)
			sprintf(cmd, "uci set demoapp.%s.%s=%s", section_name, key, val);
		else if (section_type)
			sprintf(cmd, "uci set demoapp.@%s[%d].%s=%s", section_type, section_idx, key, val);

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

static int config_global_propget(const char    *path,
		const char    *prop,
		GVariant     **value,
		void          *userdata)
{
	char line[64] = {0};
	int len = 0;
	FILE *fp = NULL;
	char cmd[128] = {0};
	//g_print("%s(%d): get %s\n", __func__, __LINE__, prop);

	sprintf(cmd, "uci get demoapp.global.%s", prop);
	fp = popen(cmd, "r");

	if (fp) {
		fgets(line, 64, fp);
		len = strlen(line);

		if (line[len - 1] == '\n')
			line[len - 1] = '\0';

		pclose(fp);
	}

	*value =g_variant_new("s", line);
	return 0;
}

static CtSgwGDBusInterfaceVTable_t interface_vtable = { handle_method_call, NULL, NULL, NULL, NULL };

static CtSgwGDBusInterfaceVTable_t interface_global_vtable = { config_global_hmcall, config_global_propget, NULL, NULL, NULL };
//static CtSgwGDBusInterfaceVTable_t interface_section_vtable = {config_section_hmcall, config_section_propget, NULL, NULL, NULL};
/*
#if 0 //DDBBGG
static gboolean
on_timeout_cb(gpointer user_data)
{

GDBusConnection *connection;
GDBusProxy *proxy;
GError *error = NULL;
GVariant *result;
const gchar *str = NULL;

connection = g_bus_get_sync(DBUS_TYPE, NULL, &error);
g_assert_no_error(error);

//fprintf(stderr, "************ call com.thundersoft.testapp1.intf2.Func2\n");
proxy = g_dbus_proxy_new_sync(connection,
G_DBUS_PROXY_FLAGS_NONE,
NULL, 				  // GDBusInterfaceInfo 
"com.thundersoft.testapp1", // name 
"/com/thundersoft/testapp1", // object path 
"com.thundersoft.testapp1.intf2",		  // interface 
NULL, // GCancellable 
&error);
g_assert_no_error(error);

result = g_dbus_proxy_call_sync(proxy,
"Func2",
NULL,
G_DBUS_CALL_FLAGS_NONE,
-1,
NULL,
&error);
g_assert_no_error(error);
g_assert(result != NULL);
g_variant_get(result, "(&s)", &str);

//fprintf(stderr, "************ ret %s\n", str);

g_variant_unref(result);
g_object_unref(proxy);
g_object_unref(connection);

return TRUE;
}
#endif
*/
static int demoapp_stop(void)
{g_print("demoapp_restore\n");
	running = 0;
	return 0;
}

static int demoapp_reload(void)
{g_print("demoapp_restore\n");
	CtSgwLog(LOG_NOTICE, "reloaded\n");
	return 0;
}

static int demoapp_restore(void)
{   g_print("demoapp_restore\n");
	CtSgwLog(LOG_NOTICE, "restore factory\n");
	return 0;
}

static void demoapp_postmsg(char *msg)
{
	g_print("PostMsg: %s\n", msg);
}

//static void demo_register_methods(CtSgwDBusNodeInfo_t *intro, CtSgwDBusNodeInfo_t *config_g, CtSgwDBusNodeInfo_t *config_s)
static void demo_register_methods(CtSgwDBusNodeInfo_t *intro, CtSgwDBusNodeInfo_t *config_g)
{
	guint registration_id;
	CtSgwGDBusInterfaceInfo_t *InterfaceInfo;
	char buf[128] = {0};

	FILE *fp = NULL;
	int cnt = 0, i = 0;

	fp = popen("/sbin/uci show demoapp | grep '=section' | wc -l", "r");

	if (fp) {
		fgets(buf, sizeof(buf), fp);
		cnt = atoi(buf);
		pclose(fp);
	}

	InterfaceInfo=CtSgwDBusNodeFindInterface(intro,"com.thundersoft.demoapp1.service");

	registration_id = CtSgwDBusRegisterObject("/com/thundersoft/demoapp1",
			intro->interfaces[0],
			&interface_vtable,
			NULL);
	g_assert(registration_id > 0);
	{
		registration_id = CtSgwDBusRegisterObject("/com/thundersoft/demoapp1/Config/global/global",
				config_g->interfaces[0],
				&interface_global_vtable,
				NULL);
		g_assert(registration_id > 0);
		CtSgwDBusUnRegisterObject(registration_id);
	}
	registration_id = CtSgwDBusRegisterObject("/com/thundersoft/demoapp1/Config/global/global",
			config_g->interfaces[0],
			&interface_global_vtable,
			NULL);
	g_assert(registration_id > 0);
	//setup response for method: GetManagedObjects
	GDBusObjectManagerServer *manager = NULL;
	GDBusObjectSkeleton *skeleton;
	DemoInterface *demo;

	manager = g_dbus_object_manager_server_new("/com/thundersoft/demoapp1/Config");

	skeleton = g_dbus_object_skeleton_new("/com/thundersoft/demoapp1/Config/global/global");
	g_dbus_object_manager_server_export(manager, skeleton);

	for (i = 0; i < cnt; i++) {
		sprintf(buf, "/com/thundersoft/demoapp1/Config/section/%d", i + 1);
		/*
#if 0
registration_id = CtSgwDBusRegisterObject(buf,
config_s->interfaces[0],
&interface_section_vtable,
(void *)i);
g_assert(registration_id > 0);
#endif
*/
		skeleton = g_dbus_object_skeleton_new(buf);
		demo = g_object_new(demo_interface_get_type(), NULL);
		demo->number = i;
		g_dbus_object_skeleton_add_interface(skeleton, G_DBUS_INTERFACE_SKELETON(demo));
		g_dbus_object_manager_server_export(manager, skeleton);
	}

	g_dbus_object_manager_server_set_connection(manager, sgw_dbus_service_context->connection);

	//DDBBGG
	//g_timeout_add_seconds (120, on_timeout_cb, sgw_dbus_service_context->connection);
}
int My_CtSgwDBusSignalFunction ( const char    *sender_name,
		const char    *path,
		const char    *interface,
		const char    *signal,
		GVariant      *args,
		void          *userdata){
	CtSgwLog(LOG_NOTICE, "callback My_CtSgwDBusSignalFunction\n"); 
	//g_print("callback My_CtSgwDBusSignalFunction\n");
}


void
test_node_on_signal_received (GDBusConnection *connection,
                        const gchar *sender_name,
                        const gchar *object_path,
                        const gchar *interface_name,
                        const gchar *signal_name,
                        GVariant *parameters,
                        gpointer user_data)
{

	g_print ("#################Received signal##############\n");
}
void demo_process_dbus_test(){
g_print("CtSgwDBusSetProperty\n");
	CtSgwLog(LOG_NOTICE, "CtSgwDBusSetProperty\n");
	CtSgwDBusSetProperty("com.thundersoft.testapp1", //*service_name,
			"/com/thundersoft/testapp1",//object_path,
			"com.thundersoft.testapp1.intf2",//interface_name,
			"testapp1Title",//*prop_name,
			CtSgwVariantNew("s","testapp1Title"));
	GVariant *outarg = NULL;
g_print("CtSgwDBusGetProperty\n");
	CtSgwLog(LOG_NOTICE, "CtSgwDBusGetProperty\n"); 
	CtSgwDBusGetProperty("com.thundersoft.testapp1", //*service_name,
			"/com/thundersoft/testapp1",//object_path,
			"com.thundersoft.testapp1.intf2",//interface_name,
			"testapp1Title",//*prop_name,
			&outarg);
	CtSgwVariant_t *argin = NULL;
	CtSgwVariant_t *arr[2];

	//arr[0] = CtSgwVariantNewDictEntry(CtSgwVariantNew("s","testapp1Title"), CtSgwVariantNew("v", CtSgwVariantNew("s","testapp1Title222")));
	//arr[1] = CtSgwVariantNewDictEntry(CtSgwVariantNew("s","testapp1Date"), CtSgwVariantNew("v", CtSgwVariantNew("i",1213)));
	//argin = CtSgwVariantNewArray(arr, 2);
		GVariantBuilder *builder;									  
		builder = g_variant_builder_new (G_VARIANT_TYPE_ARRAY);
        g_variant_builder_add (builder,
                                 "{sv}",
                                 "testapp1Title",
                                 g_variant_new_string ("testapp1Title222"));	
        g_variant_builder_add (builder,
                                 "{sv}",
                                 "testapp1Date",
                                 g_variant_new_int32 (1213));	
       // *value   =   g_variant_builder_end(builder);	
g_print("CtSgwDBusSetMultiProperty\n");	
	CtSgwLog(LOG_NOTICE, "CtSgwDBusSetMultiProperty\n"); 
	CtSgwDBusSetMultiProperty("com.thundersoft.testapp1", //*service_name,
			"/com/thundersoft/testapp1",//object_path,
			"com.thundersoft.testapp1.intf2",//interface_name,
			g_variant_builder_end(builder));
	GVariant *outarg2 = NULL;
g_print("CtSgwDBusGetAllProperty\n");
	CtSgwLog(LOG_NOTICE, "CtSgwDBusGetAllProperty\n"); 
	CtSgwDBusGetAllProperty("com.thundersoft.testapp1", //*service_name,
			"/com/thundersoft/testapp1",//object_path,
			"com.thundersoft.testapp1.intf2",//interface_name,
			&outarg);
g_print("CtSgwDBusGetAllProperty %s\n",CtSgwVariantPrint(outarg));
	//~~~~~~~~~~~~~~~~~~~~~~~~~~
	CtSgwVariant_t *argout = NULL;
	CtSgwDBusCallMethod("com.thundersoft.testapp1", //*service_name,
			"/com/thundersoft/testapp1",//object_path,
			"com.thundersoft.testapp1.intf2",//interface_name,
			"testapp1Func1",//*method_name,
			CtSgwVariantNew("(s)","name"),
			&argout,
			60);
g_print("CtSgwDBusSubscribeSignal\n");
	CtSgwLog(LOG_NOTICE, "CtSgwDBusSubscribeSignal\n"); 
	CtSgwDBusSignalFunction cb=My_CtSgwDBusSignalFunction;
	int id=CtSgwDBusSubscribeSignal("com.thundersoft.testapp1", //*service_name,
			"/com/thundersoft/testapp1",//object_path,
			"com.thundersoft.testapp1.intf2",//interface_name,
			"testapp1Signal",//*signal_name,
			My_CtSgwDBusSignalFunction,
			NULL);
sleep(2);
g_print("CtSgwDBusEmitSignal\n");
	CtSgwLog(LOG_NOTICE, "CtSgwDBusEmitSignal\n"); 
/*g_print("CtSgwDBusSubscribeSignal\n");
	CtSgwDBusEmitSignal("com.thundersoft.testapp1", //*service_name,
			"/com/thundersoft/testapp1",//object_path,
			"com.thundersoft.testapp1.intf2",//interface_name,
			"testapp1Signal",//*signal_name,
			CtSgwVariantNew("(s)","testapp1Signal_name"));	*/	
	CtSgwDBusCallMethod("com.thundersoft.testapp1", //*service_name,
			"/com/thundersoft/testapp1",//object_path,
			"com.thundersoft.testapp1.intf2",//interface_name,
			"testapp1Func2",//*method_name,
			CtSgwVariantNew("(s)","name"),
			&argout,
			60);	
 		
	CtSgwDBusUnSubscribeSignal(id);
g_print("CtSgwDBusEmitSignal\n");
	CtSgwLog(LOG_NOTICE, "CtSgwDBusEmitSignal\n"); 
	CtSgwDBusCallMethod("com.thundersoft.testapp1", //*service_name,
			"/com/thundersoft/testapp1",//object_path,
			"com.thundersoft.testapp1.intf2",//interface_name,
			"testapp1Func2",//*method_name,
			CtSgwVariantNew("(s)","name"),
			&argout,
			60);

}
int main(int argc, char *argv[])
{

	CtSgwDBusNodeInfo_t *intro_data = NULL;
	CtSgwDBusNodeInfo_t *config_g_data = NULL;
	//struct demo_list mylist;
	//struct demo_list *it,*next;
	char ver[128];
	CtSgwDBusNodeInfo_t *mm_data = NULL;
	CtSgwAppMgtCallbacks_t app_cbs = {
		.stop = demoapp_stop,
		.reload = demoapp_reload,
		.restore_factory = demoapp_restore,
		.post_msg = demoapp_postmsg
	};
	g_print("DEMOAPP Running main\n");

	CtSgwLogOpen(LOG_USER, "demoapp");
	CtSgwLog(LOG_NOTICE, "start\n");
	CtSgwGetAPIVersion(ver);//1
	CtSgwInit("com.thundersoft.demoapp1");


	CtSgwDBusStartService("com.thundersoft.demoapp1");
	g_print("DEMOAPP Running CtSgwDBusStartService\n");
	intro_data = CtSgwDBusNodeParseXml(intro_xml);
	config_g_data = CtSgwDBusNodeParseXml(config_global_xml);
	g_print("DEMOAPP Running CtSgwDBusNodeParseXml\n");
	demo_register_methods(intro_data, config_g_data);
	g_print("DEMOAPP Running demo_register_methods\n");
	mm_data = CtSgwAppRegisterMgtFuncs(&app_cbs);
	g_print("DEMOAPP Running CtSgwAppRegisterMgtFuncs\n");
	g_print("DEMOAPP Running\n");
	demo_process_dbus_test();

//	start(NULL);

	while (running) {
		int t;
		for(t = 0;t < 10;t ++)
			sleep(1);

		break;
	}

	g_print("DEMOAPP Exiting\n");

	CtSgwDBusNodeInfoUnref(intro_data);
	CtSgwDBusNodeInfoUnref(config_g_data);
	CtSgwDBusNodeInfoUnref(mm_data);
	CtSgwDBusStopService();
	//CtSgwDestroy();
	CtSgwLog(LOG_NOTICE, "exit\n");
	CtSgwLogClose();

	return 0;
}

