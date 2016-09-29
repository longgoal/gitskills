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

#include "libubox/ustream.h"
#include "libubox/uloop.h"

int running = 1;

/* Introspection data for the service we are exporting */

static const unsigned char intro_xml[] =
	"<node>"
	"  <interface name='com.thundersoft.tsappcinterface1.Config.Man'>"
  	"      <property type='s' name='gender' access='readwrite'/>"
	"  </interface>"
	"  <interface name='com.thundersoft.tsappcinterface1.Config.secweather'>"
  	"      <property type='s' name='day' access='readwrite'/>"
  	"      <property type='s' name='date' access='readwrite'/>"
  	"      <property type='s' name='weath' access='readwrite'/>"
	"  </interface>"
	"  <interface name='com.thundersoft.tsappcinterface1.Config.Yellow'>"
  	"      <property type='s' name='shape' access='readwrite'/>"
  	"      <property type='s' name='colour' access='readwrite'/>"
  	"      <property type='s' name='appupgradeflag' access='readwrite'/>"
	"  </interface>"
	"</node>";


static int
handle_method_call(const char           *object_path,
		   const char           *interface_name,
		   const char           *method_name,
		   GVariant            *inargs,
		   GVariant            **outargs,
		   void                *user_data)
{
	return 0;
}


static void _get_uci_section_val(const char *section_name, const char *opt_name, char *opt_val)
{
        char line[64] = {0};
        int len = 0;
        FILE *fp = NULL;
        char cmd[128] = {0};

        sprintf(cmd, "/sbin/uci get tsappcinterface.%s.%s", section_name, opt_name);
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

static int
tsappcinterface_get_func	(const char	 *path,
		 const char	 *prop,
		 GVariant	**value,
		 void		 *userdata)
{
	char val[32] = "";

	if (g_strcmp0 (prop, "gender") == 0)
	{
		_get_uci_section_val ("Man", prop, val);
		*value = g_variant_new_string(val);
	}
	else if ((g_strcmp0 (prop, "day") == 0) ||
	    	 (g_strcmp0 (prop, "date") == 0) || 
	    	 (g_strcmp0 (prop, "weath") == 0))
	{
		_get_uci_section_val ("secweather", prop, val);
		*value = g_variant_new_string(val);
	}
	else if ((g_strcmp0 (prop, "shape") == 0) ||
	    	 (g_strcmp0 (prop, "colour") == 0))
	{
		_get_uci_section_val ("Yellow", prop, val);
		*value = g_variant_new_string(val);
	}

	return 0;
}


static int
tsappcinterface_set_func	(const char	 *path,
		 const char	 *prop,
		 GVariant	 *value,
		 void		 *userdata)
{
	char *val = NULL;
	char  cmd[64] = "";

	g_variant_get(value, "&s", &val);

	if ((g_strcmp0 (prop, "country") == 0) ||
	    (g_strcmp0 (prop, "prov") == 0) || 
	    (g_strcmp0 (prop, "city") == 0))
	{
		sprintf(cmd, "/sbin/uci set tsappcinterface.testsec.%s=\'%s\'", prop, val);
	}
	else if (g_strcmp0 (prop, "gender") == 0)
	{
		sprintf(cmd, "/sbin/uci set tsappcinterface.Man.%s=\'%s\'", prop, val);
	}
	else if ((g_strcmp0 (prop, "day") == 0) ||
	    	 (g_strcmp0 (prop, "date") == 0) || 
	    	 (g_strcmp0 (prop, "weath") == 0))
	{
		sprintf(cmd, "/sbin/uci set tsappcinterface.secweather.%s=\'%s\'", prop, val);
	}
	else if ((g_strcmp0 (prop, "shape") == 0) ||
	    	 (g_strcmp0 (prop, "colour") == 0))
	{
		sprintf(cmd, "/sbin/uci set tsappcinterface.Yellow.%s=\'%s\'", prop, val);
	}

	g_print ("set_func: %s\n", cmd);
        system(cmd);
	sleep (1);
	g_print ("set_func: /sbin/uci commit tsappcinterface\n");
        system("/sbin/uci commit tsappcinterface");

	return 0;
}


static CtSgwGDBusInterfaceVTable_t interface_vtable = { handle_method_call, tsappcinterface_get_func, tsappcinterface_set_func, NULL, NULL };


static int tsappcinterface_stop(void)
{
	CtSgwLog(LOG_NOTICE, "stopped\n");
	running = 0;
	return 0;
}

static int tsappcinterface_reload(void)
{
	CtSgwLog(LOG_NOTICE, "reloaded\n");
	return 0;
}

static void test_register_methods(CtSgwDBusNodeInfo_t *intro)
{
	guint registration_id;

	CtSgwLog(LOG_NOTICE, "%s: registering dbus object.", __func__);
	
	// path: /com/thundersoft/tsappcinterface1/Config/Man/Man
	// intf: com.thundersoft.tsappcinterface1.Config.Man
	registration_id = CtSgwDBusRegisterObject("/com/thundersoft/tsappcinterface1/Config/Man/Man",
					  intro->interfaces[0],
					  &interface_vtable,
					  NULL);
	g_assert(registration_id > 0);
	
	// path: /com/thundersoft/tsappcinterface1/Config/secweather/secweather
	// intf: com.thundersoft.tsappcinterface1.Config.secweather
	registration_id = CtSgwDBusRegisterObject("/com/thundersoft/tsappcinterface1/Config/secweather/secweather",
					  intro->interfaces[1],
					  &interface_vtable,
					  NULL);
	g_assert(registration_id > 0);
	
	// path: /com/thundersoft/tsappcinterface/Config/Yellow/Yellow
	// intf: com.thundersoft.tsappcinterface.Config.Yellow
	registration_id = CtSgwDBusRegisterObject("/com/thundersoft/tsappcinterface1/Config/Yellow/Yellow",
					  intro->interfaces[2],
					  &interface_vtable,
					  NULL);
	g_assert(registration_id > 0);
	CtSgwLog(LOG_NOTICE, "%s: registering dbus object.", __func__);
}

int main(int argc, char *argv[])
{
	CtSgwDBusNodeInfo_t *mm_data = NULL;
	CtSgwDBusNodeInfo_t *intro_data = NULL;

	CtSgwAppMgtCallbacks_t app_cbs = { 
		.stop = tsappcinterface_stop,
		.reload = tsappcinterface_reload,
		.restore_factory = NULL,
		.post_msg = NULL
	};

	CtSgwLogOpen(LOG_USER, "tsappcinterface");

	CtSgwLog(LOG_NOTICE, "start\n");
	
	CtSgwDBusStartService("com.thundersoft.tsappcinterface1");

	intro_data = CtSgwDBusNodeParseXml(intro_xml);

	test_register_methods(intro_data);

	CtSgwLog(LOG_NOTICE, "Register management Func\n");
	mm_data = CtSgwAppRegisterMgtFuncs(&app_cbs);

	CtSgwLog(LOG_NOTICE, "tsappcinterface Running\n");
	//g_print("ctsgw Running\n");
	while (running) {
		sleep(1);
	}
	//g_print("TESTAPP Exiting\n");
	CtSgwLog(LOG_NOTICE, "tsappcinterface Exiting\n");

	CtSgwDBusNodeInfoUnref(intro_data);
	CtSgwDBusNodeInfoUnref(mm_data);
	CtSgwDBusStopService();

	CtSgwLog(LOG_NOTICE, "exit\n");
	CtSgwLogClose();	

	return 0;
}
