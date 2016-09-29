/************************************************ 
*  Dbus test suite
*  Author: Thundersoft
*  2016, all rights reserved.
************************************************/

#include "dbus_log.h"
#include <dbus/dbus.h>
#include <stdio.h>
#include <dbus_xml_parse.h>
#include <gio/gio.h>  
extern const char* igd1_interface;
extern const char* igd1_service;
extern const char* freedesktop_service;

int  machineId_compare(char *machineID);

int remote_object_peer(struct dbus_interface *dbus_interface_list ,
						struct dbus_object *dbus_object_list);

int  machineId_compare(gchar* machineID)
{
	FILE * fp;
	gchar buffer[80];
	gint ret = 0;
		
	fp=popen("cat /var/lib/dbus/machine-id","r");
	fgets(buffer,sizeof(buffer),fp);
	pclose(fp);

	if(strncmp(buffer,machineID, strlen(machineID)))
		ret = -1;
	return ret;
}

int remote_object_peer( struct dbus_interface *dbus_interface_list ,
                          				struct dbus_object *dbus_object_list)
{
	GDBusConnection  *bus; 
	GDBusConnection  *connection;
	GDBusProxy  *remote_object;  
	GError *error = NULL;  
	GVariant* machineId;
	gchar * str;
	gint ret = 0;
	struct timeval start;
	struct timeval mid;
	struct timeval end;
	guint elapsed_time = 0;
	dbus_object_list->test_result &= (~UNPASS);
	dbus_interface_list->test_result &= (~UNPASS);
	struct listnode *interface_list_item_p;
	struct listnode *method_list_item_p;


#if 1
	bus = g_bus_get_sync (G_BUS_TYPE_SYSTEM, NULL, &error);		
	//g_assert_no_error(error);

	if(error){
	        GString *gstring;
	        gstring = g_string_new (" ");
	        g_string_append_printf (gstring, "%s", error->message);
	        dbus_printf("%s line%d\n",gstring->str,__LINE__);
		g_string_free (gstring, TRUE);
		g_error_free(error);
		error=NULL;
	}
	char* service_name = igd1_service;
        if(dbus_object_list->name != NULL)
            if(strcmp(dbus_object_list->name,"/com/ctc/saf1") == 0)
                service_name = freedesktop_service;


	remote_object = g_dbus_proxy_new_sync (bus,
                        G_DBUS_PROXY_FLAGS_NONE,
                        NULL,
                        service_name, 
                        dbus_object_list->name,
                        "org.freedesktop.DBus.Peer",
                        NULL,
                        &error);
	
	if(error){
	        GString *gstring;
	        gstring = g_string_new (" ");
	        g_string_append_printf (gstring, "%s", error->message);
	        dbus_printf("%s line%d\n",gstring->str,__LINE__);
		g_string_free (gstring, TRUE);
		g_error_free(error);
		error=NULL;
	}	
        //g_assert_no_error(error);

	gettimeofday(&mid, NULL);
	gettimeofday(&start, NULL);
        machineId = g_dbus_proxy_call_sync(remote_object,
                                            "GetMachineId",
                                            NULL,
                                            G_DBUS_CALL_FLAGS_NONE,
                                            -1,
                                            NULL,
                                            &error);
#else
        bus = g_bus_get_sync(G_BUS_TYPE_SYSTEM, NULL, NULL);

	gettimeofday(&mid, NULL);
	gettimeofday(&start, NULL);

        char* service_name = igd1_service;
        if(dbus_object_list->name != NULL)
            if(strcmp(dbus_object_list->name,"/com/ctc/saf1") == 0)
                service_name = freedesktop_service;

        machineId = g_dbus_connection_call_sync(bus,
                                                service_name,   
                                                dbus_object_list->name, //object path
                                                "org.freedesktop.DBus.Peer",//"org.freedesktop.DBus.Properties", ////
                                                "GetMachineId",
                                                NULL,//g_variant_new("(ss)", dbus_interface_list->name,dbus_property_list->name),
                                                G_VARIANT_TYPE("(s)"),
                                                G_DBUS_CALL_FLAGS_NONE,
                                                -1,
                                                NULL,
                                                &error);

#endif
	gettimeofday(&end, NULL);

	if(error){
	        GString *gstring;
	        gstring = g_string_new (" ");
	        g_string_append_printf (gstring, "%s", error->message);
	        dbus_printf("%s line%d\n",gstring->str,__LINE__);
		g_string_free (gstring, TRUE);
		g_error_free(error);
		error=NULL;
	}	
	if(machineId==NULL)
	{

		dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name,"","GetMachineId","","","Failed","machineid compare",__func__,"NULL poiter");
		goto error_out;
	} 
#if 0//def Realtek
        g_variant_get(machineId, "(s)", &str);
#else
        g_variant_get(machineId, "(&s)", &str);
#endif
	   
	//dbus_printf ("machineid is %s\n", str);  

	elapsed_time = (end.tv_sec - start.tv_sec)*1000000 +
						(end.tv_usec - start.tv_usec);

	ret = machineId_compare(str);
	if(0==ret)
		//dbus_printf("%s %s is OK\n",dbus_object_list->name,dbus_interface_list->name);
		//dbus_printf_twice("%s,%s,%s,%s,%s,%d(us),%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name,"","GetMachineId","","","OK","machineid compare",__func__,str);
		dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name,"","GetMachineId","","","OK","machineid compare",__func__,str);
	else
		//dbus_printf("%s %s is NOK\n",dbus_object_list->name,dbus_interface_list->name);
		dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name,"","GetMachineId","","","Failed","machineid compare",__func__,str);
		
  
	//dbus_printf("%s, performace  is %s ,the perform time is %d us\n",
        //    dbus_object_list->name,(elapsed_time > 200000)?"FAILED":"OK",elapsed_time);
	dbus_printf_twice("%s,%s,%s,%s,%s,%d(us),%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name,"","GetMachineId","",elapsed_time,(elapsed_time > 200000)?"Failed":"OK",(elapsed_time > 200000)?"Time out":"Not time out",__func__,str);

	if(elapsed_time > 200000){
		list_for_each(interface_list_item_p, &dbus_object_list->interface_list) {
		//Notes: Check instrospect info , from object list
			struct dbus_interface *interface_p = node_to_item(interface_list_item_p, struct dbus_interface, list);
			if(interface_p==NULL)
				continue;
			if(strcmp("org.freedesktop.DBus.Peer",interface_p->name)==0)
			{
				list_for_each(method_list_item_p, &interface_p->method_list)
				{
					struct dbus_method *dbus_method_p = node_to_item(method_list_item_p, struct dbus_method, list);
					if(dbus_method_p == NULL)
						continue;
					if(g_strcmp0(dbus_method_p->name, "GetMachineId")==0)
					{
						dbus_object_list->test_result |= METHOD_CALL_TIMEOUT;
						dbus_method_p->test_result |= METHOD_CALL_TIMEOUT;
						break;
					}
				}
			}
		}
	}






	gettimeofday(&start, NULL);
       g_dbus_proxy_call_sync(remote_object,
                                            "Ping",
                                            NULL,
                                            G_DBUS_CALL_FLAGS_NONE,
                                            -1,
                                            NULL,
                                            &error);
	gettimeofday(&end, NULL);
	elapsed_time = (end.tv_sec - start.tv_sec)*1000000 +
						(end.tv_usec - start.tv_usec);


	dbus_printf_twice("%s,%s,%s,%s,%s,%d(us),%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name,"","Ping","",elapsed_time,(elapsed_time > 200000)?"Failed":"OK",(elapsed_time > 200000)?"Time out":"Not time out",__func__,"");
	if(elapsed_time > 200000){
		list_for_each(interface_list_item_p, &dbus_object_list->interface_list) {
		//Notes: Check instrospect info , from object list
			struct dbus_interface *interface_p = node_to_item(interface_list_item_p, struct dbus_interface, list);
			if(interface_p==NULL)
				continue;
			if(strcmp("org.freedesktop.DBus.Peer",interface_p->name)==0)
			{
				list_for_each(method_list_item_p, &interface_p->method_list)
				{
					struct dbus_method *dbus_method_p = node_to_item(method_list_item_p, struct dbus_method, list);
					if(dbus_method_p == NULL)
						continue;
					if(g_strcmp0(dbus_method_p->name, "Ping")==0)
					{
						dbus_object_list->test_result |= METHOD_CALL_TIMEOUT;
						dbus_method_p->test_result |= METHOD_CALL_TIMEOUT;
						break;
					}
				}
			}
		}
	}

	if(error){
	        GString *gstring;
	        gstring = g_string_new (" ");
	        g_string_append_printf (gstring, "%s", error->message);
	        dbus_printf("%s line%d\n",gstring->str,__LINE__);
		g_string_free (gstring, TRUE);
		g_error_free(error);
		error=NULL;
	}	
	g_variant_unref (machineId);
error_out: 
	//g_object_unref (G_OBJECT (remote_object));
	g_object_unref(bus);

	return ret;
}
