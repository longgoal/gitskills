/************************************************
*  Dbus test suite
*  Author: Thundersoft
*  2016, all rights reserved.
************************************************/

/*
   1所有lookup,先去list确定object,然后再去case list再确定一次object
   2所有lookup,如果传入参数非空，则是全跑
 */
#include "dbus_log.h"
#include <dbus/dbus.h>
#include <stdio.h>
#include <dbus_xml_parse.h>
#include <dbus_cts.h>
#include <gio/gio.h>
const char* igd1_interface		=	"com.ctc.igd1.Properties";
const char* igd1_service		=	"com.ctc.igd1";
const char* freedesktop_service 	=	"com.ctc.saf1";

extern dbus_command_s run_args;
extern bool           check_Get_in_SCC;
extern bool           open_tag_about_test_all;
extern bool           check_notification;
bool                  bind_test_method = false;
//#define TS_METHOD_PROXY
//proxy not set out param.... so not use...
char        *WANConnectionInfo_IfName = NULL;
char        *LANHost_MAC              = NULL;
char        *LANHost_Port             = NULL;
gchar       LANHost_ConnectionType    = 0xff;
extern bool in_parallel_test;
extern bool redundancy;
bool        lib_debug = true;
extern bool        open_log;
#define ARG_NUM              20
#define METHOD_ARG_MAXNUM    5 //Parse less then 5 input parameter
//#define  EXIT_IF_NULL(a) {if(a==NULL){dbus_printf("####### NULL point. exit in %s line %d\n",__func__,__LINE__);exit(0);}};
#define EXIT_IF_NULL(a)    do { } while (0)

guint32 Copy_TransactionId = 0;
//liuxy 0906-003 : KickOutDevice_flag for do "KickOutDevice" in advance.
extern bool               KickOutDevice_flag;

//int remote_object_method_igd1_Lookup_Set(char *object_name, char *interface_name, char *property_name);
int igd1_Set(struct dbus_object *dbus_object_list, struct dbus_interface *dbus_interface_list, struct dbus_property *dbus_property_list);

//int remote_object_method_igd1_Lookup_Get(char *object_name, char *interface_name, char *property_name);
int igd1_Get(struct dbus_object *dbus_object_list, struct dbus_interface *dbus_interface_list, struct dbus_property *dbus_property_list);

//int remote_object_method_igd1_Lookup_SetMulti(char *object_name, char *interface_name);
int igd1___SetMulti(struct dbus_object *dbus_object_list, struct dbus_interface *dbus_interface_list);

int remote_object_method(struct dbus_object *dbus_object_list, struct dbus_interface *dbus_interface_list, struct dbus_method *dbus_method_list);


int remote_object_method_Lookup(char *object_name, char *interface_name, char *property_name, char *method_name)
{
    //set method under "com.ctc.igd1.Properties"
    struct listnode      *interface_list_item_p;
    //struct dbus_interface *dbus_interface_p;
    struct listnode      *property_list_item_p;
    struct dbus_property *property_p;

    struct listnode      *obj_list_item_p;
    struct dbus_object   *dbus_case_object_p;
    struct dbus_object   *dbus_object_list = NULL;

    struct listnode      *dbus_case_item_p;
    struct listnode      *method_list_item_p;
    struct listnode      *arg_list_item_p;
    struct listnode      *signal_list_item_p;

    bool                 find_object    = false;
    bool                 find_interface = false;
    bool                 find_property  = false;
    bool                 find_method    = false;

    if (object_name == NULL)
    {
        return(-1);
    }

    if (list_empty(&dbus_list))
    {
        dbus_printf("object list is empty.\n");
        return(-1);
    }
    if ((DBUS_CMD_ALL == run_args) || (DBUS_CMD_ALL_BY_STEP == run_args) || open_tag_about_test_all)
    {
        if (redundancy)
        {
            sleep(1);
        }
        //else
        {
            //liuxy 0907-001 begin : postpone "Restore" of com.ctc.igd1.SysCmd.
            if ((strcmp(method_name, "Restore") == 0)&&(g_strcmp0(interface_name, "com.ctc.igd1.SysCmd") == 0))
            {
                dbus_printf("   In all test. Don't execive Restore of com.ctc.igd1.SysCmd\n");
                return(0);
            }
            //liuxy 0907-001 end
            
            if (strcmp(method_name, "SetDateTime") == 0)
            {
                dbus_printf("   In all test. Don't execive SetDateTime\n");
                return(0);
            }
        }
        //usleep(100000);
        //sleep(1);
    }
    list_for_each(obj_list_item_p, &dbus_list)
    {
        dbus_object_list = node_to_item(obj_list_item_p, struct dbus_object, list);
        if (g_strcmp0(dbus_object_list->name, object_name) != 0)
        {
            if (dbus_object_list->form_name != NULL)
            {
                if (g_strcmp0(dbus_object_list->form_name, object_name) == 0)
                {
                    goto still_ok;
                }
            }
            continue;
        }
        else
        {
            goto still_ok;
        }
    }
    dbus_printf("can't find the object %s\n", object_name);
    return(-1);

still_ok:
    if (interface_name == NULL)
    {
        find_interface = true;
    }
    if (property_name == NULL)
    {
        find_property = true;
    }
    if (method_name == NULL)
    {
        find_method = true;
    }
    /*if (list_empty(&dbus_case_list))
       {
            dbus_printf("object case list is empty.\n");
            return -1;
       }
       list_for_each(dbus_case_item_p, &dbus_case_list) {
       //set 在dbus_case_list中查找
            struct dbus_case *dbus_case_p;
            dbus_case_p = node_to_item(dbus_case_item_p, struct dbus_case, list);
            list_for_each(obj_list_item_p, &dbus_case_p->object_list) {
                    //struct dbus_object *dbus_case_object_p;
                    dbus_case_object_p = node_to_item(obj_list_item_p, struct dbus_object, list);

                    if(g_strcmp0(dbus_case_object_p->name, dbus_object_list->name) == 0){
                            goto check_interface;
                    }
                    else if (dbus_object_list->form_name!=NULL){
                            if(g_strcmp0(dbus_case_object_p->name, dbus_object_list->form_name) == 0){
                                    goto check_interface;
                            }
                            else
                                    continue;
                    }
                    else
                            continue;
       check_interface:*/

    //Because case.xml sync to xml....So,don't check in case list
    dbus_case_object_p = dbus_object_list;

    list_for_each(interface_list_item_p, &dbus_object_list->interface_list)
    {
        //Notes: Check instrospect info , from object list
        struct dbus_interface *interface_p = node_to_item(interface_list_item_p, struct dbus_interface, list);

        if (interface_p == NULL)
        {
            continue;
        }
        if ((interface_name != NULL) && (method_name != NULL))
        {
            if (g_strcmp0(interface_p->name, "com.ctc.igd1.Properties") == 0)
            {
                if (((strcmp(method_name, "Set") == 0) || (strcmp(method_name, "Get") == 0) || (strcmp(method_name, "SetMulti") == 0) || (strcmp(method_name, "GetAll") == 0)) && (!interface_p->introspect_has_interface))
                {
                    dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s%s%s,%s,%s%s\n", dbus_object_list->name, interface_p->name, "", "", "", "", "Failed", "No interface ", interface_p->name, " from introspect", __func__, "Stop execve method ", method_name);
                    dbus_object_list->test_result |= NO_INTERFACE;
                    goto func_end;
                }
            }
            else
            {
                if (g_strcmp0(interface_p->name, interface_name) == 0)
                {
                    if (!interface_p->introspect_has_interface)
                    {
                        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s%s%s,%s,%s\n", dbus_object_list->name, interface_p->name, "", "", "", "", "Failed", "No interface ", interface_p->name, " from introspect", __func__, "Stop execve");
                        dbus_object_list->test_result |= NO_INTERFACE;
                        goto func_end;
                    }

                    list_for_each(method_list_item_p, &interface_p->method_list)
                    {
                        struct dbus_method *dbus_method_p = node_to_item(method_list_item_p, struct dbus_method, list);

                        if (dbus_method_p == NULL)
                        {
                            continue;
                        }
                        if (g_strcmp0(dbus_method_p->name, method_name) == 0)
                        {
                            if (!dbus_method_p->introspect_has_method)
                            {
                                dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s%s%s,%s,%s\n", dbus_object_list->name, interface_p->name, "", dbus_method_p->name, "", "", "Failed", "Error method ", dbus_method_p->name, " from introspect", __func__, "Stop execve");
                                dbus_object_list->test_result |= NO_INTERFACE;
                                goto func_end;
                            }
                        }
                    }
                    list_for_each(property_list_item_p, &interface_p->property_list)
                    {
                        property_p = node_to_item(property_list_item_p, struct dbus_property, list);
                        if (property_p == NULL)
                        {
                            continue;
                        }
                        if (property_name != NULL)
                        {
                            if (g_strcmp0(property_p->name, property_name) == 0)
                            {
                                if (!property_p->introspect_has_property)
                                {
                                    dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s%s%s,%s,%s\n", dbus_object_list->name, interface_p->name, property_p->name, "", "", "", "Failed", "No property ", property_p->name, " from introspect", __func__, "Stop execve");
                                    interface_p->test_result      |= NO_PROPERTY;
                                    dbus_object_list->test_result |= NO_PROPERTY;
                                    goto func_end;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    list_for_each(interface_list_item_p, &dbus_case_object_p->interface_list)
    {
        struct dbus_interface *interface_p = node_to_item(interface_list_item_p, struct dbus_interface, list);

        if (interface_p == NULL)
        {
            continue;
        }
        if (interface_name != NULL)
        {
            if (g_strcmp0(interface_p->name, interface_name) != 0)
            {
                continue;
            }
            else
            {
                find_interface = true;
            }
        }
        //Set / SetMulti / normal method ,use case object
        //Get / Getall , use object

        if (method_name != NULL)
        {
            if ((g_strcmp0(method_name, "Set") == 0))
            {
                list_for_each(property_list_item_p, &interface_p->property_list)
                {
                    property_p = node_to_item(property_list_item_p, struct dbus_property, list);
                    if (property_p == NULL)
                    {
                        continue;
                    }
                    if ((DBUS_CMD_ALL == run_args) || (DBUS_CMD_ALL_BY_STEP == run_args) || open_tag_about_test_all)
                    {
                        /*if(g_strcmp0(property_p->name,"ControlStatus")==0)
                           {
                                dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s %s\n",dbus_case_object_p->name, interface_p->name, property_p->name,"Set","","","OK","",__func__,"Don't execve Set",property_p->name);
                                return 0;
                           }*/
                    }

                    if (property_name != NULL)
                    {
                        if (g_strcmp0(property_p->name, property_name) == 0)
                        {
                            igd1_Set(dbus_case_object_p, interface_p, property_p);
                            //Notes use dbus_object_list->name , Not dbus_case_object_p->name. For instance issue.
                            goto func_end;
                        }
                    }
                    else
                    {
                        find_property = true;
                        igd1_Set(dbus_object_list, interface_p, property_p);
                        //Notes use dbus_object_list->name , Not dbus_case_object_p->name. For instance issue.
                    }
                }
            }
            else if ((g_strcmp0(method_name, "Get") == 0))
            {
                list_for_each(property_list_item_p, &interface_p->property_list)
                {
                    property_p = node_to_item(property_list_item_p, struct dbus_property, list);
                    if (property_p == NULL)
                    {
                        continue;
                    }
                    if (property_name != NULL)
                    {
                        if (g_strcmp0(property_p->name, property_name) == 0)
                        {
                            igd1_Get(dbus_object_list, interface_p, property_p);
                            //Notes use dbus_object_list->name , Not dbus_case_object_p->name. For instance issue.
                            goto func_end;
                        }
                    }
                    else
                    {
                        find_property = true;
                        igd1_Get(dbus_object_list, interface_p, property_p);
                        //Notes use dbus_object_list->name , Not dbus_case_object_p->name. For instance issue.
                    }
                }
            }
            else if ((g_strcmp0(method_name, "GCS") == 0))
            {
                list_for_each(property_list_item_p, &interface_p->property_list)
                {
                    property_p = node_to_item(property_list_item_p, struct dbus_property, list);
                    if (property_p == NULL)
                    {
                        continue;
                    }
                    if (property_name != NULL)
                    {
                        if (g_strcmp0(property_p->name, property_name) == 0)
                        {
                            igd1_Get_Set_or_Checksignal(dbus_object_list, interface_p, property_p);
                            //Notes use dbus_object_list->name , Not dbus_case_object_p->name. For instance issue.
                            goto func_end;
                        }
                    }
                    else
                    {
                        find_property = true;
                        igd1_Get_Set_or_Checksignal(dbus_object_list, interface_p, property_p);
                        //Notes use dbus_object_list->name , Not dbus_case_object_p->name. For instance issue.
                    }
                }
            }
            else if ((g_strcmp0(method_name, "SCC") == 0))
            {
                list_for_each(property_list_item_p, &interface_p->property_list)
                {
                    property_p = node_to_item(property_list_item_p, struct dbus_property, list);
                    if (property_p == NULL)
                    {
                        continue;
                    }

                    if ((DBUS_CMD_ALL == run_args) || (DBUS_CMD_ALL_BY_STEP == run_args) || open_tag_about_test_all)
                    {
                        /*if(g_strcmp0(property_p->name,"ControlStatus")==0)
                           {
                                dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s %s\n",dbus_case_object_p->name, interface_p->name, property_p->name,"Set","","","OK","",__func__,"Don't execve Set",property_p->name);
                                return 0;
                           }*/
                    }

                    if (property_name != NULL)
                    {
                        if (g_strcmp0(property_p->name, property_name) == 0)
                        {
                            igd1_Set_Checksignal_CheckGet(dbus_object_list, interface_p, property_p, 0);
                            //Notes use dbus_object_list->name , Not dbus_case_object_p->name. For instance issue.
                            goto func_end;
                        }
                    }
                    else
                    {
                        find_property = true;
                        igd1_Set_Checksignal_CheckGet(dbus_object_list, interface_p, property_p, 0);
                        //Notes use dbus_object_list->name , Not dbus_case_object_p->name. For instance issue.
                    }
                }
            }
            else if ((g_strcmp0(method_name, "GCR") == 0))
            {
                list_for_each(property_list_item_p, &interface_p->property_list)
                {
                    property_p = node_to_item(property_list_item_p, struct dbus_property, list);
                    if (property_p == NULL)
                    {
                        continue;
                    }
                    if (property_name != NULL)
                    {
                        if (g_strcmp0(property_p->name, property_name) == 0)
                        {
                            igd1_Get_CheckSetResult(dbus_object_list, interface_p, property_p);
                            //Notes use dbus_object_list->name , Not dbus_case_object_p->name. For instance issue.
                            goto func_end;
                        }
                    }
                    else
                    {
                        find_property = true;
                        igd1_Get_CheckSetResult(dbus_object_list, interface_p, property_p);
                        //Notes use dbus_object_list->name , Not dbus_case_object_p->name. For instance issue.
                    }
                }
            }

            else if ((g_strcmp0(method_name, "SetMulti") == 0))
            {
                igd1_SetMulti(dbus_object_list, interface_p);
                goto func_end;
                //Notes use dbus_object_list->name , Not dbus_case_object_p->name. For instance issue.
            }
            else if ((g_strcmp0(method_name, "GetAll") == 0))
            {
                //Notes use dbus_object_list->name , Not dbus_case_object_p->name. For instance issue.
                remote_object_igd1_properties_get_all(interface_p, dbus_object_list);
                goto func_end;
            }
            else if ((g_strcmp0(method_name, "ACDC") == 0))
            {
                //Notes use dbus_object_list->name , Not dbus_case_object_p->name. For instance issue.
                igd1_AddObject_CheckSignal_DeleteObject_CheckSignal(dbus_object_list, interface_p);
                goto func_end;
            }
            else
            {
                list_for_each(method_list_item_p, &interface_p->method_list)
                {
                    struct dbus_method *dbus_method_p = node_to_item(method_list_item_p, struct dbus_method, list);

                    if (dbus_method_p == NULL)
                    {
                        continue;
                    }
                    if (g_strcmp0(dbus_method_p->name, method_name) != 0)
                    {
                        continue;
                    }
                    //remote_object_method(dbus_case_object_p, interface_p, dbus_method_p);
                    remote_object_method(dbus_object_list, interface_p, dbus_method_p);
                    goto func_end;
                }
            }
        }
        else
        {
            list_for_each(method_list_item_p, &interface_p->method_list)
            {
                struct dbus_method *dbus_method_p = node_to_item(method_list_item_p, struct dbus_method, list);

                if (dbus_method_p == NULL)
                {
                    continue;
                }
                //remote_object_method(dbus_case_object_p, interface_p, dbus_method_p);
                remote_object_method(dbus_object_list, interface_p, dbus_method_p);
            }
        }
    }
    /*}
       }*/

    if (!find_interface)
    {
        dbus_printf("Can't find interface %s\n", interface_name);
    }
    if (!find_property)
    {
        dbus_printf("Can't find property %s\n", property_name);
    }
    //return -1;
func_end:
    return(0);
} /* remote_object_method_Lookup */


#if 1
//int KickOutDevice_Lookup(char *object_name, char *interface_name, char *property_name, char* method_name)
struct dbus_object *KickOutDevice_Lookup(void)
{
    //set method under "com.ctc.igd1.Properties"
    struct listnode      *interface_list_item_p;
    //struct dbus_interface *dbus_interface_p;
    struct listnode      *property_list_item_p;
    struct dbus_property *property_p;

    struct listnode      *obj_list_item_p;
    struct dbus_object   *dbus_case_object_p;
    struct dbus_object   *dbus_object_list = NULL;

    struct listnode      *dbus_case_item_p;
    struct listnode      *method_list_item_p;
    struct listnode      *arg_list_item_p;
    struct listnode      *signal_list_item_p;

    bool                 find_object    = false;
    bool                 find_interface = false;
    bool                 find_property  = false;
    bool                 find_method    = false;

    //if(object_name == NULL)
    //	return -1;

    if (list_empty(&dbus_list))
    {
        dbus_printf("object list is empty.\n");
        return(NULL);
    }
    if ((DBUS_CMD_ALL == run_args) || (DBUS_CMD_ALL_BY_STEP == run_args) || open_tag_about_test_all)
    {
        if (redundancy)
        {
            sleep(1);
        }
        //usleep(100000);
        //sleep(1);
    }
    list_for_each(obj_list_item_p, &dbus_list)
    {
        dbus_object_list = node_to_item(obj_list_item_p, struct dbus_object, list);
        //if(g_strcmp0(dbus_object_list->name, object_name)!=0)
        {
            if (dbus_object_list->form_name != NULL)
            {
                if (g_strcmp0(dbus_object_list->form_name, "/com/ctc/igd1/Config/LANHosts/{i}") == 0)
                {
                    remote_object_method_Lookup(dbus_object_list->name, "com.ctc.igd1.LANHost", "ConnectionType", "Get");

                    if (LANHost_ConnectionType == 1)         //For SSIDIndex
                    {
                        LANHost_ConnectionType = 0xff;
                        dbus_printf("  Find %s with ConnectionType==1\n", dbus_object_list->name);

                        return(dbus_object_list);
                    }
                    LANHost_ConnectionType = 0xff;
                }
            }
            continue;
        }
        //else
        //goto still_ok;
    }

    dbus_printf("  Can't find the object /com/ctc/igd1/Config/LANHosts/{i} with ConnectionType==1\n");
    dbus_printf_twice("/com/ctc/igd1/Info/WiFi,com.ctc.igd1.WiFiInfo, ,KickOutDevice, , ,%s,%s,%s,%s\n", "Failed", "Method SSIDIndex arg can't get", __func__, "Can't find the object /com/ctc/igd1/Config/LANHosts/{i} with ConnectionType==1");
    return(NULL);
} /* KickOutDevice_Lookup */
#endif


int remote_object_property_Lookup_check_range(char *object_name, char *interface_name, char *property_name, int value)
{
    //set method under "com.ctc.igd1.Properties"
    struct listnode      *interface_list_item_p;
    //struct dbus_interface *dbus_interface_p;
    struct listnode      *property_list_item_p;
    struct dbus_property *property_p;

    struct listnode      *obj_list_item_p;
    struct dbus_object   *dbus_object_p;
    struct dbus_object   *dbus_object_list = NULL;

    struct listnode      *dbus_case_item_p;

    //struct listnode *method_list_item_p;
    //struct listnode *arg_list_item_p;
    //struct listnode *signal_list_item_p;

    if ((object_name == NULL) || (interface_name == NULL) || (property_name == NULL))
    {
        return(-1);
    }

    if (list_empty(&dbus_list))
    {
        dbus_printf("object list is empty.\n");
        return(-1);
    }

    list_for_each(obj_list_item_p, &dbus_list)
    {
        dbus_object_list = node_to_item(obj_list_item_p, struct dbus_object, list);
        if (g_strcmp0(dbus_object_list->name, object_name) != 0)
        {
            if (dbus_object_list->form_name != NULL)
            {
                if (g_strcmp0(dbus_object_list->form_name, object_name) == 0)
                {
                    goto still_ok;
                }
            }
            continue;
        }
        else
        {
            goto still_ok;
        }
    }
    dbus_printf("can't find the object %s\n", object_name);
    return(-1);

still_ok:
    list_for_each(interface_list_item_p, &dbus_object_list->interface_list)
    {
        struct dbus_interface *interface_p = node_to_item(interface_list_item_p, struct dbus_interface, list);

        if (interface_p == NULL)
        {
            continue;
        }
        list_for_each(property_list_item_p, &interface_p->property_list)
        {
            property_p = node_to_item(property_list_item_p, struct dbus_property, list);
            if (property_p == NULL)
            {
                continue;
            }
            if (g_strcmp0(property_p->name, property_name) == 0)
            {
                //igd1_Set(dbus_object_list, interface_p, property_p);
                //Notes use dbus_object_list->name , Not dbus_object_p->name. For instance issue.
                if (property_p->case_property_has_min)
                {
                    int check_value = 0;
                    if (g_strcmp0(property_p->type, "u") == 0)
                    {
                        check_value = (property_p->min.uint32_v);
                    }
                    else if (g_strcmp0(property_p->type, "i") == 0)
                    {
                        check_value = (property_p->min.int32_v);
                    }
                    else if (g_strcmp0(property_p->type, "y") == 0)
                    {
                        check_value = (property_p->min.byte_v);
                    }
                    else
                    {
                        dbus_printf("check min range need parse more type!\n");
                        return(-1);
                    }
                    if (value < check_value)
                    {
                        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%d\n", dbus_object_list->name, interface_p->name, property_p->name, "", "", "", "Failed", "Value less than min", "check_range", value, check_value);
                        dbus_object_list->test_result |= RANGE_ERROR;
                        property_p->test_result       |= RANGE_ERROR;
                    }
                    else
                    {
                        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%d\n", dbus_object_list->name, interface_p->name, property_p->name, "", "", "", "OK", "Value bigger than min", "check_range", value, check_value);
                        dbus_object_list->test_result &= (~UNPASS);
                        interface_p->test_result      &= (~UNPASS);
                        property_p->test_result       &= (~UNPASS);
                    }
                }
                else
                {
                    dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%d\n", dbus_object_list->name, interface_p->name, property_p->name, "", "", "", "OK", "No need to check min", "check_range", value);
                    dbus_object_list->test_result &= (~UNPASS);
                    interface_p->test_result      &= (~UNPASS);
                    property_p->test_result       &= (~UNPASS);
                }
                if (property_p->case_property_has_max)
                {
                    int check_value = 0;
                    if (g_strcmp0(property_p->type, "u") == 0)
                    {
                        check_value = (property_p->max.uint32_v);
                    }
                    else if (g_strcmp0(property_p->type, "i") == 0)
                    {
                        check_value = (property_p->max.int32_v);
                    }
                    else if (g_strcmp0(property_p->type, "y") == 0)
                    {
                        check_value = (property_p->max.byte_v);
                    }
                    else
                    {
                        dbus_printf("check max range need parse more type!\n");
                        return(-1);
                    }
                    if (value > check_value)
                    {
                        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%d\n", dbus_object_list->name, interface_p->name, property_p->name, "", "", "", "Failed", "Value bigger than max", "check_range", value, check_value);
                        dbus_object_list->test_result |= RANGE_ERROR;
                        property_p->test_result       |= RANGE_ERROR;
                    }
                    else
                    {
                        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%d\n", dbus_object_list->name, interface_p->name, property_p->name, "", "", "", "OK", "Value less than max", "check_range", value, check_value);
                        dbus_object_list->test_result &= (~UNPASS);
                        interface_p->test_result      &= (~UNPASS);
                        property_p->test_result       &= (~UNPASS);
                    }
                }
                else
                {
                    dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%d\n", dbus_object_list->name, interface_p->name, property_p->name, "", "", "", "OK", "No need to check max", "check_range", value);
                    dbus_object_list->test_result &= (~UNPASS);
                    interface_p->test_result      &= (~UNPASS);
                    property_p->test_result       &= (~UNPASS);
                }
                goto func_end;
            }
        }
    }
    //return -1;
func_end:
    return(0);
} /* remote_object_property_Lookup_check_range */


int remote_object_method(struct dbus_object    *dbus_object_list,
                         struct dbus_interface *dbus_interface_list,
                         struct dbus_method    *dbus_method_list)
{
    //Set method under "com.ctc.igd1.Properties"
    EXIT_IF_NULL(dbus_object_list);
    EXIT_IF_NULL(dbus_object_list->name);
    EXIT_IF_NULL(dbus_interface_list);
    EXIT_IF_NULL(dbus_interface_list->name);
    EXIT_IF_NULL(dbus_method_list);
    EXIT_IF_NULL(dbus_method_list->name);
    if (dbus_object_list == NULL)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "unknown", "unknown", "unknown", "", "", "", "Failed", "dbus_object is NULL", __func__, "NULL point Error");
        return(-1);
    }
    if (dbus_object_list->name == NULL)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "unknown", "unknown", "unknown", "", "", "", "Failed", "dbus_object->name is NULL", __func__, "NULL point Error");
        return(-1);
    }
    if (dbus_interface_list == NULL)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, "unknown", "unknown", "", "", "", "Failed", "dbus_interface is NULL", __func__, "NULL point Error");
        return(-1);
    }
    if (dbus_interface_list->name == NULL)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, "unknown", "unknown", "", "", "", "Failed", "dbus_interface->name is NULL", __func__, "NULL point Error");
        return(-1);
    }
    if (dbus_method_list == NULL)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "unknown", "unknown", "", "", "Failed", "dbus_method is NULL", __func__, "NULL point Error");
        return(-1);
    }
    if (dbus_method_list->name == NULL)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "unknown", "unknown", "", "", "Failed", "dbus_method->name is NULL", __func__, "NULL point Error");
        return(-1);
    }


    dbus_printf("  interface[object_method] %s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, dbus_method_list->name);


    GDBusConnection *bus = NULL;
    GDBusProxy      *remote_object;
    GError          *error = NULL;
    GVariant        *Method_Out;
    GVariant        *Method_Out2;
    GVariant        *method_input_param;
    gchar           *str;
    gchar           *str2;
    gchar           *objpath;
    guint32         out1 = 1;
    guint32         out2 = 1;
    gint            ret  = 0;
    struct timeval  start;
    struct timeval  end;
    guint           elapsed_time = 0;
    struct listnode *arg_list_item_p;
    bool            no_input_method = false;

    char            method_in_arg[ARG_NUM]  = "(";
    char            method_out_arg[ARG_NUM] = "(";
    //struct GVariant *arg_in[METHOD_ARG_MAXNUM]={0};
    void            *arg_in[METHOD_ARG_MAXNUM] = { 0 };
    //void arg_in[METHOD_ARG_MAXNUM]={0};
    struct GVariant *arg_out[METHOD_ARG_MAXNUM] = { 0 };
    int             in_arg_num                  = 0;
    int             out_arg_num                 = 0;
    char            *p_in                       = method_in_arg + sizeof("(") - 1;
    char            *p_out                      = method_out_arg + sizeof("(") - 1;
    GVariantBuilder *method_in_builder;
    //GVariantBuilder builder;
    GVariant        *method_in_value;
    struct listnode *method_list_item_p;

    if ((DBUS_CMD_ALL == run_args) || (DBUS_CMD_ALL_BY_STEP == run_args) || open_tag_about_test_all)
    {
        //usleep(10000);
        //sleep(1);
        if (g_strcmp0(dbus_method_list->name, "Reboot") == 0)
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "OK", "", __func__, "Don't execve reboot method");
            return(0);
        }
        //liuxy 0901-002 begin : "Restore" method do not trigger to reboot device,so we need to test the "Restore" method.
        //                       "LocalRecovery" method trigger to reboot device,so we need not to test the "Restore" method.
        /*if (g_strcmp0(dbus_method_list->name, "Restore") == 0)
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "OK", "", __func__, "Don't execve Restore method");
            return(0);
        }*/
        if (g_strcmp0(dbus_method_list->name, "LocalRecovery") == 0)
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "OK", "", __func__, "Don't execve LocalRecovery method");
            return(0);
        }
        //liuxy 0901-002 end
        if ((g_strcmp0(dbus_method_list->name, "SetLOID") == 0) && !(bind_test_method))
        {
            dbus_printf("\n\n       SetLOID bind to CheckLOID, please test CheckLOID\n");
            return(0);
        }
        if ((g_strcmp0(dbus_method_list->name, "RegisterLOID") == 0) && !(bind_test_method))
        {
            dbus_printf("\n\n       RegisterLOID bind to CheckLOID, please test CheckLOID\n");
            return(0);
        }
        if (g_strcmp0(dbus_method_list->name, "CheckLOID") == 0)
        {
            //dbus_com_ctc_igd1_usb_devices__Mount(dbus_object_list,dbus_interface_list,dbus_method_list);
            dbus_printf("   Before execive CheckLOID, execive SetLOID & RegisterLOID\n");
            dbus_printf("   Execive SetLOID \n");
            bind_test_method = true;
            remote_object_method_Lookup("/com/ctc/igd1/Telecom/System", "com.ctc.igd1.SysCmd", NULL, "SetLOID");
            sleep(1);
            dbus_printf("   Execive RegisterLOID \n");
            remote_object_method_Lookup("/com/ctc/igd1/Telecom/System", "com.ctc.igd1.SysCmd", NULL, "RegisterLOID");
            sleep(1);
            dbus_printf("   Execve CheckLOID \n");
            bind_test_method = false;
        }


        if ((g_strcmp0(dbus_method_list->name, "SetUAPasswd") == 0) && !(bind_test_method))
        {
            dbus_printf("\n\n       SetUAPasswd bind to CheckUAPasswd, please test CheckUAPasswd\n");
            return(0);
        }
        if (g_strcmp0(dbus_method_list->name, "CheckUAPasswd") == 0)
        {
            //dbus_com_ctc_igd1_usb_devices__Mount(dbus_object_list,dbus_interface_list,dbus_method_list);
            dbus_printf("   Before execive CheckUAPasswd, execive SetUAPasswd\n");
            dbus_printf("   Execive SetUAPasswd \n");
            bind_test_method = true;
            remote_object_method_Lookup("/com/ctc/igd1/Telecom/System", "com.ctc.igd1.SysCmd", NULL, "SetUAPasswd");
            sleep(1);
            dbus_printf("   Execive CheckUAPasswd \n");
            bind_test_method = false;
        }


        if ((g_strcmp0(dbus_method_list->name, "Rename") == 0) && !(bind_test_method))
        {
            dbus_printf("\n\n       Rename bind to Remove, please test Remove\n");
            return(0);
        }
        if ((g_strcmp0(dbus_method_list->name, "Move") == 0) && !(bind_test_method))
        {
            dbus_printf("\n\n       Move bind to Remove, please test Remove\n");
            return(0);
        }
        if ((g_strcmp0(dbus_method_list->name, "CreateFolder") == 0) && !(bind_test_method))
        {
            dbus_printf("\n\n       CreateFolder bind to Remove, please test Remove\n");
            return(0);
        }
        if (g_strcmp0(dbus_method_list->name, "Remove") == 0)
        {
            //dbus_com_ctc_igd1_usb_devices__Mount(dbus_object_list,dbus_interface_list,dbus_method_list);
            dbus_printf("   Execive CreateFolder & Rename & Move & Remove\n");
            dbus_printf("   Please make sure the value in case xml!\n");
            dbus_printf("   Execive CreateFolder \n");
            bind_test_method = true;
            remote_object_method_Lookup("/com/ctc/igd1/Storage/nas", "com.ctc.igd1.NASAccess", NULL, "CreateFolder");
            sleep(1);
            dbus_printf("   Execive Rename \n");
            remote_object_method_Lookup("/com/ctc/igd1/Storage/nas", "com.ctc.igd1.NASAccess", NULL, "Rename");
            sleep(1);
            dbus_printf("   Execve Move \n");
            remote_object_method_Lookup("/com/ctc/igd1/Storage/nas", "com.ctc.igd1.NASAccess", NULL, "Move");
            sleep(1);
            dbus_printf("   Execve Remove \n");
            bind_test_method = false;
        }

        if (g_strcmp0(dbus_method_list->name, "Move") == 0)
        {
            list_for_each(arg_list_item_p, &dbus_method_list->arg_list)
            {
                struct dbus_method_arg *dbus_arg_p = node_to_item(arg_list_item_p, struct dbus_method_arg, list);

                if (g_strcmp0(dbus_arg_p->name, "destFolderName") == 0)
                {
                    if (dbus_arg_p->case_method_arg_has_value == false)
                    {
                        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, dbus_arg_p->name, dbus_method_list->name, "", "", "Failed", "Method arg haven't value", __func__, dbus_arg_p->name);
                        dbus_object_list->test_result |= METHOD_ARG_NO_VALUE;
                        dbus_arg_p->test_result       |= METHOD_ARG_NO_VALUE;
                        return(-1);
                    }
                    dbus_printf("   Test Move. Try to mkdir %s\n", dbus_arg_p->value.path_str);
                    char cmd[100];
                    sprintf(cmd, "mkdir %s", dbus_arg_p->value.path_str);
                    system(cmd);
                }
            }
        }


        if ((g_strcmp0(dbus_method_list->name, "Unmount") == 0) && !(bind_test_method))
        {
            dbus_printf("\n\n       Unmount bind to SetLabel, please test SetLabel\n");
            return(0);
        }
        if ((g_strcmp0(dbus_method_list->name, "Format") == 0) && !(bind_test_method))
        {
            dbus_printf("\n\n       Format bind to SetLabel, please test SetLabel\n");
            return(0);
        }
        if ((g_strcmp0(dbus_method_list->name, "Mount") == 0) && !(bind_test_method))
        {
            dbus_printf("\n\n       Mount bind to SetLabel, please test SetLabel\n");
            return(0);
        }
        if (g_strcmp0(dbus_method_list->name, "SetLabel") == 0)
        {
            //dbus_com_ctc_igd1_usb_devices__Mount(dbus_object_list,dbus_interface_list,dbus_method_list);
            //dbus_printf("   Execive Mount & SetLabel & Format Unmount\n");
            dbus_printf("   Execive Unmount & Format & Mount & SetLabel\n");
            dbus_printf("   Please make sure the value in case xml! This will format the u-disk!\n");
            dbus_printf("   Sync disk before test\n");
            sync();
            sleep(1);
            dbus_printf("   Execive Unmount \n");

            bind_test_method = true;
            remote_object_method_Lookup("/com/ctc/igd1/Storage/usb/devices/{i}", "com.ctc.igd1.usb.FileSystem", NULL, "Unmount");
            sleep(1);
            dbus_printf("   Execive Format \n");
            remote_object_method_Lookup("/com/ctc/igd1/Storage/usb/devices/{i}", "com.ctc.igd1.usb.FileSystem", NULL, "Format");
            int u;
            for (u = 0; u < 61; u += 5)
            {
                sleep(5);
                dbus_printf("wait (%d)s for Format\n", (90 - u));
            }

            sleep(1);
            dbus_printf("   Execve Mount \n");
            remote_object_method_Lookup("/com/ctc/igd1/Storage/usb/devices/{i}", "com.ctc.igd1.usb.FileSystem", NULL, "Mount");
            for (u = 0; u < 61; u += 5)
            {
                sleep(5);
                dbus_printf("wait (%d)s for Mount\n", (90 - u));
            }
            dbus_printf("   Execve SetLabel \n");
            bind_test_method = false;
        }


        if ((g_strcmp0(dbus_method_list->name, "GetWANConnByName") == 0))
        {
            dbus_printf("\n\n       GetWANConnByName bind to Get /com/ctc/igd1/Info/Network/WANConnectionDb/{i}.com.ctc.igd1.WANConnectionInfo.IfName\n");
            remote_object_method_Lookup("/com/ctc/igd1/Info/Network/WANConnectionDb/{i}", "com.ctc.igd1.WANConnectionInfo", "IfName", "Get");
            if (WANConnectionInfo_IfName == NULL)
            {
                dbus_printf("com.ctc.igd1.WANConnectionInfo.IfName can't get\n");
                return(0);
            }

            list_for_each(arg_list_item_p, &dbus_method_list->arg_list)
            {
                struct dbus_method_arg *dbus_arg_p = node_to_item(arg_list_item_p, struct dbus_method_arg, list);

                if (g_strcmp0(dbus_arg_p->name, "name") == 0)
                {
                    //if(dbus_arg_p->value.path_str!=NULL)
                    //	free(dbus_arg_p->value.path_str);
                    dbus_arg_p->value.path_str            = WANConnectionInfo_IfName;
                    dbus_arg_p->case_method_arg_has_value = true;
                }
            }
        }


        if ((g_strcmp0(dbus_method_list->name, "KickOutDevice") == 0))
        {
            struct dbus_object *LANHost_for_kick = NULL;

            //liuxy 0906-003 : KickOutDevice_flag for do "KickOutDevice" in advance.
            if(KickOutDevice_flag == true)
            {
                //"KickOutDevice" has been called. Just ignore it now.
                return (0);
            }
            LANHost_for_kick = KickOutDevice_Lookup();
            if (LANHost_for_kick == NULL)
            {
                return(0);
            }
            dbus_printf("\n\n       KickOutDevice bind to Get %s.com.ctc.igd1.LANHost.MAC\n", LANHost_for_kick->name);

            //remote_object_method_Lookup("/com/ctc/igd1/Config/LANHosts/{i}","com.ctc.igd1.LANHost","MAC","Get");
            remote_object_method_Lookup(LANHost_for_kick->name, "com.ctc.igd1.LANHost", "MAC", "Get");
            if (LANHost_MAC == NULL)
            {
                dbus_printf("com.ctc.igd1.LANHost.MAC can't get\n");
                return(0);
            }

            list_for_each(arg_list_item_p, &dbus_method_list->arg_list)
            {
                struct dbus_method_arg *dbus_arg_p = node_to_item(arg_list_item_p, struct dbus_method_arg, list);

                if (g_strcmp0(dbus_arg_p->name, "MAC") == 0)
                {
                    //if(dbus_arg_p->value.path_str!=NULL)
                    //	free(dbus_arg_p->value.path_str);
                    dbus_arg_p->value.path_str            = LANHost_MAC;
                    dbus_arg_p->case_method_arg_has_value = true;
                }
            }


            dbus_printf("\n\n       KickOutDevice bind to Get %s.com.ctc.igd1.LANHost.Port\n", LANHost_for_kick->name);
            //remote_object_method_Lookup("/com/ctc/igd1/Config/LANHosts/{i}","com.ctc.igd1.LANHost","Port","Get");
            remote_object_method_Lookup(LANHost_for_kick->name, "com.ctc.igd1.LANHost", "Port", "Get");
            if (LANHost_Port == NULL)
            {
                dbus_printf("com.ctc.igd1.LANHost.Port can't get\n");
                return(0);
            }

            list_for_each(arg_list_item_p, &dbus_method_list->arg_list)
            {
                struct dbus_method_arg *dbus_arg_p = node_to_item(arg_list_item_p, struct dbus_method_arg, list);

                if (g_strcmp0(dbus_arg_p->name, "SSIDIndex") == 0)
                {
                    //if(dbus_arg_p->value.path_str!=NULL)
                    //	free(dbus_arg_p->value.path_str);
                    dbus_arg_p->value.path_str            = LANHost_Port;
                    dbus_arg_p->case_method_arg_has_value = true;
                }
            }
        }


        if ((g_strcmp0(dbus_interface_list->name, "com.ctc.igd1.NASAccess") == 0) && (g_strcmp0(dbus_method_list->name, "GetCopyProgress") == 0))
        {
            dbus_printf("\n\n       GetCopyProgress bind to Copy, please test Copy\n");
            return(0);
        }


        if (g_strcmp0(dbus_method_list->name, "Copy") == 0)
        {
            list_for_each(arg_list_item_p, &dbus_method_list->arg_list)
            {
                struct dbus_method_arg *dbus_arg_p = node_to_item(arg_list_item_p, struct dbus_method_arg, list);

                if (g_strcmp0(dbus_arg_p->name, "destFolderName") == 0)
                {
                    if (dbus_arg_p->case_method_arg_has_value == false)
                    {
                        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, dbus_arg_p->name, dbus_method_list->name, "", "", "Failed", "Method arg haven't value", __func__, dbus_arg_p->name);
                        dbus_object_list->test_result |= METHOD_ARG_NO_VALUE;
                        dbus_arg_p->test_result       |= METHOD_ARG_NO_VALUE;
                        return(-1);
                    }
                    dbus_printf("   Test Copy. Try to mkdir %s\n", dbus_arg_p->value.path_str);
                    char cmd[100];
                    char cmd2[100];
                    sprintf(cmd, "mkdir %s", dbus_arg_p->value.path_str);
                    system(cmd);
                    dbus_printf("   Test Copy. Try to rm %s/*\n", dbus_arg_p->value.path_str);
                    sprintf(cmd2, "rm %s/* -rf", dbus_arg_p->value.path_str);
                    system(cmd2);
                }
                if (g_strcmp0(dbus_arg_p->name, "name") == 0)
                {
                    if (dbus_arg_p->case_method_arg_has_value == false)
                    {
                        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, dbus_arg_p->name, dbus_method_list->name, "", "", "Failed", "Method arg haven't value", __func__, dbus_arg_p->name);
                        dbus_object_list->test_result |= METHOD_ARG_NO_VALUE;
                        dbus_arg_p->test_result       |= METHOD_ARG_NO_VALUE;
                        return(-1);
                    }
                    if (access((char *)dbus_arg_p->value.path_str, 0) < 0)
                    {
                        dbus_printf("   Test Copy. Try to generate 10M %s\n", dbus_arg_p->value.path_str);
                        char cmd[100] = { 0 };
                        int  i;
                        //sprintf(cmd,"dd if=/dev/zero of=%s bs=50M count=1000", dbus_arg_p->value);
                        //system(cmd);
                        /*sprintf(cmd,"echo 1234567890 >> %s", dbus_arg_p->value.path_str);
                           for(i=0; i<5*1024*1024;i++) // 5*10*1024*1024*
                                system(cmd);*/
                        FILE *fp;

                        fp = fopen(dbus_arg_p->value.path_str, "a+");
                        if (fp)
                        {
                            for (i = 0; i < 1024 * 1024; i++)             // 5*10*1024*1024*
                            {
                                //fwrite(cmd, 1, 50, fp);
                                fwrite(cmd, 1, 10, fp);
                            }
                            fclose(fp);
                        }

                        sleep(15);
                        sync();
                        dbus_printf("   Test Copy. Try to generate 10M %s End\n", dbus_arg_p->value.path_str);
                        //system("ls -l /mnt/USB_disc1/dianxintest.tar");
                    }
                }
            }
        }
    }


    //dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s%s\n",dbus_object_list->name, dbus_interface_list->name, "",dbus_method_list->name,"","","OK","",__func__,"Don't execve ",dbus_method_list->name);
    //return 0;


    if (!list_empty(&dbus_method_list->arg_list))
    {
        list_for_each(arg_list_item_p, &dbus_method_list->arg_list)
        {
            struct dbus_method_arg *dbus_arg_p = node_to_item(arg_list_item_p, struct dbus_method_arg, list);

            if (g_strcmp0(dbus_arg_p->direction, "in") == 0)
            {
                if (dbus_arg_p->case_method_arg_has_value == false)
                {
                    dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "Failed", "Method arg haven't value", __func__, dbus_arg_p->name);
                    dbus_object_list->test_result |= METHOD_ARG_NO_VALUE;
                    dbus_arg_p->test_result       |= METHOD_ARG_NO_VALUE;
                    return(-1);
                }


                /*if(in_arg_num>METHOD_ARG_MAXNUM)
                   {
                        //dbus_printf("Failed,Crash.The [%s] IN arg more than %d  in [%s]@[%s]\n",dbus_method_list->name,METHOD_ARG_MAXNUM, dbus_object_list->name, dbus_interface_list->name);
                        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name, "",dbus_method_list->name,"","","Failed","Method has new IN arg ",__func__,"");
                        //g_assert(1);
                        return -1;
                   }*/

                if (g_strcmp0(dbus_arg_p->type, "s") == 0 || g_strcmp0(dbus_arg_p->type, "p") == 0)
                {
                    strcpy(p_in, "s");
                    p_in += 1;
                    dbus_printf("%s == %s\n", dbus_arg_p->name, dbus_arg_p->value.path_str);
                    //arg_in[in_arg_num]=g_variant_new(dbus_arg_p->type, g_variant_new_string(dbus_arg_p->value.path_str));
                    //arg_in[in_arg_num]=dbus_arg_p->value.path_str;
                    arg_in[in_arg_num] = dbus_arg_p->value.path_str;


                    //g_variant_builder_add(method_in_builder, dbus_arg_p->type, dbus_arg_p->value.path_str);
                }
                else if (g_strcmp0(dbus_arg_p->type, "o") == 0)
                {
                    strcpy(p_in, "o");
                    p_in += 1;
                    dbus_printf("%s == %s\n", dbus_arg_p->name, dbus_arg_p->value.path_str);
                    //arg_in[in_arg_num]=g_variant_new(dbus_arg_p->type, g_variant_new_string(dbus_arg_p->value.path_str));
                    //arg_in[in_arg_num]=dbus_arg_p->value.path_str;
                    arg_in[in_arg_num] = dbus_arg_p->value.path_str;
                    //g_variant_builder_add(method_in_builder, dbus_arg_p->type, dbus_arg_p->value.path_str);
                }
                else if (g_strcmp0(dbus_arg_p->type, "u") == 0)
                {
                    strcpy(p_in, "u");
                    p_in += 1;
                    dbus_printf("%s == %d\n", dbus_arg_p->name, dbus_arg_p->value.uint32_v);
                    //arg_in[in_arg_num]=g_variant_new(dbus_arg_p->type, g_variant_new_uint32(dbus_arg_p->value.uint32_v));
                    arg_in[in_arg_num] = dbus_arg_p->value.uint32_v;          //Pass the test
                    //g_variant_builder_add(method_in_builder, dbus_arg_p->type, dbus_arg_p->value.uint32_v);
                }
                else if (g_strcmp0(dbus_arg_p->type, "d") == 0)
                {
                    strcpy(p_in, "d");
                    p_in += 1;          //sizeof("d");
                    dbus_printf("%s == %d\n", dbus_arg_p->name, dbus_arg_p->value.double_v);
                    //arg_in[in_arg_num]=g_variant_new(dbus_arg_p->type, g_variant_new_double(dbus_arg_p->value.double_v));
                    arg_in[in_arg_num] = &dbus_arg_p->value.double_v;
                    //g_variant_builder_add(method_in_builder, dbus_arg_p->type, dbus_arg_p->value.double_v);
                }
                else if (g_strcmp0(dbus_arg_p->type, "t") == 0)
                {
                    strcpy(p_in, "t");
                    p_in += 1;
                    //arg_in[in_arg_num]=g_variant_new(dbus_arg_p->type, g_variant_new_uint64(dbus_arg_p->value.uint64_v));
                    arg_in[in_arg_num] = dbus_arg_p->value.uint64_v;
                    //g_variant_builder_add(method_in_builder, dbus_arg_p->type, dbus_arg_p->value.uint64_v);
                }
                else if (g_strcmp0(dbus_arg_p->type, "x") == 0)
                {
                    strcpy(p_in, "x");
                    p_in += 1;
                    //arg_in[in_arg_num]=g_variant_new(dbus_arg_p->type, g_variant_new_int64(dbus_arg_p->value.int64_v));
                    arg_in[in_arg_num] = dbus_arg_p->value.int64_v;
                    //g_variant_builder_add(method_in_builder, dbus_arg_p->type, dbus_arg_p->value.int64_v);
                }
                else if (g_strcmp0(dbus_arg_p->type, "y") == 0)
                {
                    strcpy(p_in, "y");
                    p_in += 1;
                    dbus_printf("%s == %d\n", dbus_arg_p->name, dbus_arg_p->value.byte_v);
                    //arg_in[in_arg_num]=g_variant_new(dbus_arg_p->type, g_variant_new_byte(dbus_arg_p->value.byte_v));
                    arg_in[in_arg_num] = dbus_arg_p->value.byte_v;
                    //g_variant_builder_add(method_in_builder, dbus_arg_p->type, dbus_arg_p->value.byte_v);
                }
                else if (g_strcmp0(dbus_arg_p->type, "b") == 0)
                {
                    strcpy(p_in, "b");
                    p_in += 1;
                    dbus_printf("%s == %d\n", dbus_arg_p->name, dbus_arg_p->value.bool_v);
                    //arg_in[in_arg_num]=g_variant_new(dbus_arg_p->type, g_variant_new_boolean(dbus_arg_p->value.bool_v));
                    arg_in[in_arg_num] = dbus_arg_p->value.bool_v;
                    //g_variant_builder_add(method_in_builder, dbus_arg_p->type, dbus_arg_p->value.bool_v);
                }
                else if (g_strcmp0(dbus_arg_p->type, "i") == 0)
                {
                    strcpy(p_in, "i");
                    p_in += 1;
                    dbus_printf("%s == %d\n", dbus_arg_p->name, dbus_arg_p->value.int32_v);
                    //arg_in[in_arg_num]=g_variant_new(dbus_arg_p->type, g_variant_new_int32(dbus_arg_p->value.int32_v));
                    arg_in[in_arg_num] = dbus_arg_p->value.int32_v;
                    //g_variant_builder_add(method_in_builder, dbus_arg_p->type, dbus_arg_p->value.int32_v);
                }
                else if (g_strcmp0(dbus_arg_p->type, "q") == 0)
                {
                    strcpy(p_in, "q");
                    p_in += 1;
                    //arg_in[in_arg_num]=g_variant_new(dbus_arg_p->type, g_variant_new_uint16(dbus_arg_p->value.uint16_v));
                    arg_in[in_arg_num] = dbus_arg_p->value.uint16_v;
                    //g_variant_builder_add(method_in_builder, dbus_arg_p->type, dbus_arg_p->value.uint16_v);
                }
                else if (g_strcmp0(dbus_arg_p->type, "n") == 0)
                {
                    strcpy(p_in, "n");
                    p_in += 1;
                    //arg_in[in_arg_num]=g_variant_new(dbus_arg_p->type, g_variant_new_int16(dbus_arg_p->value.int16_v));
                    arg_in[in_arg_num] = dbus_arg_p->value.int16_v;
                    //g_variant_builder_add(method_in_builder, dbus_arg_p->type, dbus_arg_p->value.int16_v);
                }
                else if (g_strcmp0(dbus_arg_p->type, "a{sv}") == 0)
                {
                    strcpy(p_in, "@a{sv}");
                    p_in += 6;          //5;

                    char *str_p         = NULL;
                    char *str_tmp_p     = NULL;
                    char *comma_brace_p = NULL;
                    char *tag_p         = NULL;
                    char *info_p        = NULL;
                    str_p = malloc(strlen(dbus_arg_p->value.path_str) + 1);
                    strcpy(str_p, dbus_arg_p->value.path_str);
                    str_tmp_p = str_p;
                    int             count = 1;

                    GVariantBuilder *setmulti_builder;
                    setmulti_builder = g_variant_builder_new(G_VARIANT_TYPE("a{sv}"));
                    GVariant        *setmulti_value;
                    while (*str_tmp_p)
                    {
                        if ((comma_brace_p = strchr(str_tmp_p, ' ')) != NULL)
                        {
                            *comma_brace_p = 0;
                            count++;
                            str_tmp_p = comma_brace_p + 1;
                        }
                        else
                        {
                            break;
                        }
                    }
                    str_tmp_p = str_p;
                    do
                    {
                        //dbus_printf("a{sv} str_tmp_p is %s\n",str_tmp_p);
                        if ((g_strcmp0(str_tmp_p, "-t") == 0) || (g_strcmp0(str_tmp_p, "-o") == 0))
                        {
                            if (count == 1)
                            {
                                dbus_printf("lack of %s info.\n", str_tmp_p);
                                goto early_out;
                            }
                            info_p = str_tmp_p + strlen(str_tmp_p) + 1;
                            if (*info_p == '-')
                            {
                                dbus_printf("lack of %s info\n", str_tmp_p);
                                goto early_out;
                            }
                            g_variant_builder_add(setmulti_builder, "{sv}", str_tmp_p, g_variant_ref((GVariant *)g_variant_new_string(info_p)));
                            str_tmp_p += strlen(str_tmp_p) + 1 + strlen(info_p) + 1;
                            --count;
                        }
                        else if (g_strcmp0(str_tmp_p, "-r") == 0)
                        {
                            g_variant_builder_add(setmulti_builder, "{sv}", str_tmp_p, g_variant_ref((GVariant *)g_variant_new_string("NULL")));
                            str_tmp_p += strlen(str_tmp_p) + 1;
                        }
                        else
                        {
                            if (strlen(str_tmp_p) != 0)
                            {
                                g_variant_builder_add(setmulti_builder, "{sv}", "NULL", g_variant_ref((GVariant *)g_variant_new_string(str_tmp_p)));
                            }
                            str_tmp_p += strlen(str_tmp_p) + 1;
                        }
                    } while (--count > 0);


                    setmulti_value = g_variant_builder_end(setmulti_builder);


                    //method_input_param=g_variant_new ("(@a{sv})", setmulti_value);

                    //arg_in[in_arg_num]=dbus_arg_p->value.int16_v;
                    arg_in[in_arg_num] = setmulti_value;
                }
                else
                {
                    //dbus_printf("Failed,crash.the property [%s] type[%s] is unknown in [%s]@[%s]\n", dbus_arg_p->name,dbus_arg_p->type, dbus_object_list->name, dbus_interface_list->name);
                    dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "Failed", "Method arg type is unknown", __func__, dbus_arg_p->name);
                    dbus_object_list->test_result |= METHOD_ARG_NO_VALUE;
                    dbus_arg_p->test_result       |= METHOD_ARG_NO_VALUE;
                    //g_assert(1);
                    return(-1);
                }

                in_arg_num++;
            }


            if (g_strcmp0(dbus_arg_p->direction, "out") == 0)
            {
                if (out_arg_num > METHOD_ARG_MAXNUM)
                {
                    //dbus_printf("Failed,Crash.The [%s] in arg more than %d  in [%s]@[%s]\n",dbus_method_list->name,METHOD_ARG_MAXNUM, dbus_object_list->name, dbus_interface_list->name);
                    dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "Failed", "Arg is too much", __func__, "");
                    //g_assert(1);
                    return(-1);
                }

                if (g_strcmp0(dbus_arg_p->type, "s") == 0 || g_strcmp0(dbus_arg_p->type, "p") == 0)
                {
                    strcpy(p_out, "s");
                    p_out += 1;
                    //arg_out[out_arg_num]=g_variant_new(dbus_arg_p->type, g_variant_new_string(dbus_arg_p->value.path_str));
                }
                else if (g_strcmp0(dbus_arg_p->type, "o") == 0)
                {
                    strcpy(p_out, "o");
                    p_out += 1;
                    //arg_out[out_arg_num]=g_variant_new(dbus_arg_p->type, g_variant_new_object_path(dbus_arg_p->value.path_str));
                }
                else if (g_strcmp0(dbus_arg_p->type, "u") == 0)
                {
                    strcpy(p_out, "u");
                    p_out += 1;
                    //arg_out[out_arg_num]=g_variant_new(dbus_arg_p->type, g_variant_new_uint32(dbus_arg_p->value.uint32_v));
                }
                else if (g_strcmp0(dbus_arg_p->type, "d") == 0)
                {
                    strcpy(p_out, "d");
                    p_out += 1;          //sizeof("d");
                    //arg_out[out_arg_num]=g_variant_new(dbus_arg_p->type, g_variant_new_double(dbus_arg_p->value.double_v));
                }
                else if (g_strcmp0(dbus_arg_p->type, "t") == 0)
                {
                    strcpy(p_out, "t");
                    p_out += 1;
                    //arg_out[out_arg_num]=g_variant_new(dbus_arg_p->type, g_variant_new_uint64(dbus_arg_p->value.uint64_v));
                }
                else if (g_strcmp0(dbus_arg_p->type, "x") == 0)
                {
                    strcpy(p_out, "x");
                    p_out += 1;
                    //arg_out[out_arg_num]=g_variant_new(dbus_arg_p->type, g_variant_new_int64(dbus_arg_p->value.int64_v));
                }
                else if (g_strcmp0(dbus_arg_p->type, "y") == 0)
                {
                    strcpy(p_out, "y");
                    p_out += 1;
                    //arg_out[out_arg_num]=g_variant_new(dbus_arg_p->type, g_variant_new_byte(dbus_arg_p->value.byte_v));
                }
                else if (g_strcmp0(dbus_arg_p->type, "b") == 0)
                {
                    strcpy(p_out, "b");
                    p_out += 1;
                    //arg_out[out_arg_num]=g_variant_new(dbus_arg_p->type, g_variant_new_boolean(dbus_arg_p->value.bool_v));
                }
                else if (g_strcmp0(dbus_arg_p->type, "i") == 0)
                {
                    strcpy(p_out, "i");
                    p_out += 1;
                    //arg_out[out_arg_num]=g_variant_new(dbus_arg_p->type, g_variant_new_int32(dbus_arg_p->value.int32_v));
                }
                else if (g_strcmp0(dbus_arg_p->type, "q") == 0)
                {
                    strcpy(p_out, "q");
                    p_out += 1;
                    //arg_out[out_arg_num]=g_variant_new(dbus_arg_p->type, g_variant_new_uint16(dbus_arg_p->value.uint16_v));
                }
                else if (g_strcmp0(dbus_arg_p->type, "n") == 0)
                {
                    strcpy(p_out, "n");
                    p_out += 1;
                    //arg_out[out_arg_num]=g_variant_new(dbus_arg_p->type, g_variant_new_int16(dbus_arg_p->value.int16_v));
                }
                else if (g_strcmp0(dbus_arg_p->type, "a{oa{sa{sv}}}") == 0)
                {
                    strcpy(p_out, "a{oa{sa{sv}}}");
                    p_out += 13;
                    //arg_out[out_arg_num]=g_variant_new(dbus_arg_p->type, g_variant_new_int16(dbus_arg_p->value.int16_v));
                }
                else if (g_strcmp0(dbus_arg_p->type, "a(ssbus)") == 0)
                {
                    strcpy(p_out, "a(ssbus)");
                    p_out += 8;
                    //arg_out[out_arg_num]=g_variant_new(dbus_arg_p->type, g_variant_new_int16(dbus_arg_p->value.int16_v));
                }
                else if (g_strcmp0(dbus_arg_p->type, "a{ssbus}") == 0)
                {
                    strcpy(p_out, "a{ssbus}");
                    p_out += 8;
                    //arg_out[out_arg_num]=g_variant_new(dbus_arg_p->type, g_variant_new_int16(dbus_arg_p->value.int16_v));
                }
                //liuxy 0901-001 begin :ListFolder out arg, FileSize type UINT32 -> UINT64
                else if (g_strcmp0(dbus_arg_p->type, "a(ssbts)") == 0)
                {
                    strcpy(p_out, "a(ssbts)");
                    p_out += 8;
                    //arg_out[out_arg_num]=g_variant_new(dbus_arg_p->type, g_variant_new_int16(dbus_arg_p->value.int16_v));
                }
                //liuxy 0901-001 end
                else
                {
                    //dbus_printf("Failed,crash.the property [%s] type[%s] is unknown in [%s]@[%s]\n", dbus_arg_p->name,dbus_arg_p->type, dbus_object_list->name, dbus_interface_list->name);
                    dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "Failed", "Method arg type is  unknown", __func__, dbus_arg_p->name);
                    dbus_object_list->test_result |= METHOD_ARG_NO_VALUE;
                    dbus_arg_p->test_result       |= METHOD_ARG_NO_VALUE;
                    //g_assert(1);
                    return(-1);
                }
                out_arg_num++;
            }
        }
    }
    else
    {
        //method haven't the arg........
    }
    //g_variant_new("(ssv)", dbus_interface_list->name,dbus_property_list->name,value),
    strcpy(p_in, ")");
    p_in += 1;
    strcpy(p_out, ")");
    p_out += 1;
    *p_in  = '\0';
    *p_out = '\0';
    dbus_printf("METHOD [%s] in [%s]@[%s] bytest\n IN[%s],    OUT[%s]\n", dbus_method_list->name, dbus_object_list->name, dbus_interface_list->name, method_in_arg, method_out_arg);
    switch (in_arg_num)
    {
    case 0: method_input_param = NULL;
        no_input_method        = true;
        break;

    case 1: method_input_param = g_variant_new(method_in_arg, arg_in[0]);
        break;

    case 2: method_input_param = g_variant_new(method_in_arg, arg_in[0], arg_in[1]);
        break;

    case 3: method_input_param = g_variant_new(method_in_arg, arg_in[0], arg_in[1], arg_in[2]);
        break;

    case 4: method_input_param = g_variant_new(method_in_arg, arg_in[0], arg_in[1], arg_in[2], arg_in[3]);
        break;

    case 5: method_input_param = g_variant_new(method_in_arg, arg_in[0], arg_in[1], arg_in[2], arg_in[3], arg_in[4]);
        break;
    }

#ifdef BUILD_IN_PARAM
    method_in_builder = g_variant_builder_new(G_VARIANT_TYPE(method_in_arg));

    list_for_each(arg_list_item_p, &dbus_method_list->arg_list)
    {
        struct dbus_method_arg *dbus_arg_p = node_to_item(arg_list_item_p, struct dbus_method_arg, list);

        if (g_strcmp0(dbus_arg_p->direction, "in") == 0)
        {
            if (dbus_arg_p->case_method_arg_has_value == false)
            {
                dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "Failed", "Method arg haven't value", __func__, dbus_arg_p->name);
                dbus_object_list->test_result |= METHOD_ARG_NO_VALUE;
                dbus_arg_p->test_result       |= METHOD_ARG_NO_VALUE;
                return(-1);
            }


            /*if(in_arg_num>METHOD_ARG_MAXNUM)
               {
                    //dbus_printf("Failed,Crash.The [%s] IN arg more than %d  in [%s]@[%s]\n",dbus_method_list->name,METHOD_ARG_MAXNUM, dbus_object_list->name, dbus_interface_list->name);
                    dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name, "",dbus_method_list->name,"","","Failed","Method has new IN arg ",__func__,"");
                    //g_assert(1);
                    return -1;
               }*/

            if (g_strcmp0(dbus_arg_p->type, "s") == 0 || g_strcmp0(dbus_arg_p->type, "p") == 0)
            {
                //strcpy(p_in, "s");
                //p_in+=1;
                //dbus_printf("%s == %s\n",dbus_arg_p->name, dbus_arg_p->value.path_str);
                g_variant_builder_add(method_in_builder, dbus_arg_p->type, (dbus_arg_p->value.path_str));
            }
            else if (g_strcmp0(dbus_arg_p->type, "o") == 0)
            {
                //strcpy(p_in, "o");
                //p_in+=1;
                //dbus_printf("%s == %s\n",dbus_arg_p->name, (const gchar *)dbus_arg_p->value.path_str);
                g_variant_builder_add(method_in_builder, dbus_arg_p->type, dbus_arg_p->value.path_str);
            }
            else if (g_strcmp0(dbus_arg_p->type, "u") == 0)
            {
                //strcpy(p_in, "u");
                //p_in+=1;
                //dbus_printf("%s == %d\n",dbus_arg_p->name, dbus_arg_p->value.uint32_v);
                ////arg_in[in_arg_num]=g_variant_new(dbus_arg_p->type, g_variant_new_uint32(dbus_arg_p->value.uint32_v));
                //arg_in[in_arg_num]=&dbus_arg_p->value.uint32_v;//Pass the test
                g_variant_builder_add(method_in_builder, dbus_arg_p->type, dbus_arg_p->value.uint32_v);
            }
            else if (g_strcmp0(dbus_arg_p->type, "d") == 0)
            {
                //strcpy(p_in, "d");
                //p_in+=1;//sizeof("d");
                //dbus_printf("%s == %d\n",dbus_arg_p->name, dbus_arg_p->value.double_v);
                ////arg_in[in_arg_num]=g_variant_new(dbus_arg_p->type, g_variant_new_double(dbus_arg_p->value.double_v));
                //arg_in[in_arg_num]=&dbus_arg_p->value.double_v;
                g_variant_builder_add(method_in_builder, dbus_arg_p->type, dbus_arg_p->value.double_v);
            }
            else if (g_strcmp0(dbus_arg_p->type, "t") == 0)
            {
                //strcpy(p_in, "t");
                //p_in+=1;
                //arg_in[in_arg_num]=&dbus_arg_p->value.uint64_v;
                g_variant_builder_add(method_in_builder, dbus_arg_p->type, dbus_arg_p->value.uint64_v);
            }
            else if (g_strcmp0(dbus_arg_p->type, "x") == 0)
            {
                //strcpy(p_in, "x");
                //p_in+=1;
                //arg_in[in_arg_num]=&dbus_arg_p->value.int64_v;
                g_variant_builder_add(method_in_builder, dbus_arg_p->type, dbus_arg_p->value.int64_v);
            }
            else if (g_strcmp0(dbus_arg_p->type, "y") == 0)
            {
                //strcpy(p_in, "y");
                //p_in+=1;
                //dbus_printf("%s == %d\n",dbus_arg_p->name, dbus_arg_p->value.byte_v);
                //arg_in[in_arg_num]=&dbus_arg_p->value.byte_v;
                g_variant_builder_add(method_in_builder, dbus_arg_p->type, dbus_arg_p->value.byte_v);
            }
            else if (g_strcmp0(dbus_arg_p->type, "b") == 0)
            {
                //strcpy(p_in, "b");
                //p_in+=1;
                //dbus_printf("%s == %d\n",dbus_arg_p->name, dbus_arg_p->value.bool_v);
                //arg_in[in_arg_num]=&dbus_arg_p->value.bool_v;
                g_variant_builder_add(method_in_builder, dbus_arg_p->type, dbus_arg_p->value.bool_v);
            }
            else if (g_strcmp0(dbus_arg_p->type, "i") == 0)
            {
                //strcpy(p_in, "i");
                //p_in+=1;
                //dbus_printf("%s == %d\n",dbus_arg_p->name, dbus_arg_p->value.int32_v);
                //arg_in[in_arg_num]=&dbus_arg_p->value.int32_v;
                g_variant_builder_add(method_in_builder, dbus_arg_p->type, dbus_arg_p->value.int32_v);
            }
            else if (g_strcmp0(dbus_arg_p->type, "q") == 0)
            {
                //strcpy(p_in, "q");
                //p_in+=1;
                //arg_in[in_arg_num]=&dbus_arg_p->value.uint16_v;
                g_variant_builder_add(method_in_builder, dbus_arg_p->type, dbus_arg_p->value.uint16_v);
            }
            else if (g_strcmp0(dbus_arg_p->type, "n") == 0)
            {
                //strcpy(p_in, "n");
                //p_in+=1;
                //arg_in[in_arg_num]=&dbus_arg_p->value.int16_v;
                g_variant_builder_add(method_in_builder, dbus_arg_p->type, dbus_arg_p->value.int16_v);
            }
            else
            {
                //dbus_printf("Failed,crash.the property [%s] type[%s] is unknown in [%s]@[%s]\n", dbus_arg_p->name,dbus_arg_p->type, dbus_object_list->name, dbus_interface_list->name);
                dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "Failed", "Method arg type is unknown", __func__, dbus_arg_p->name);
                dbus_object_list->test_result |= METHOD_ARG_NO_VALUE;
                dbus_arg_p->test_result       |= METHOD_ARG_NO_VALUE;
                //g_assert(1);
                return(-1);
            }
        }
    }
#endif


/*
   1 proxy need set out param
   2 single s type can't into builder
 */
#ifdef TS_METHOD_PROXY
    bus = g_bus_get_sync(G_BUS_TYPE_SYSTEM, NULL, &error);

    if (error)
    {
        GString *gstring;
        gstring = g_string_new(" ");
        g_string_append_printf(gstring, "%s", error->message);
        dbus_printf("%s line%d\n", gstring->str, __LINE__);
        g_string_free(gstring, TRUE);
        g_error_free(error);
        error = NULL;
    }
    //g_assert_no_error(error);
    if (g_dbus_connection_is_closed(bus))
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "Failed", "Error, execve method when dbus connection is closed", __func__, "");
        dbus_object_list->test_result |= CONNECTION_CLOSED;
        dbus_method_list->test_result |= CONNECTION_CLOSED;
        goto early_out;
    }

    char* service_name = igd1_service;
    if(dbus_object_list->name != NULL)
        if(strcmp(dbus_object_list->name,"/com/ctc/saf1") == 0)
            service_name = freedesktop_service;

    remote_object = g_dbus_proxy_new_sync(bus,
                                          G_DBUS_PROXY_FLAGS_NONE,
                                          NULL,
                                          service_name,
                                          dbus_object_list->name,
                                          dbus_interface_list->name,
                                          NULL,
                                          &error);
    if (error)
    {
        GString *gstring;
        gstring = g_string_new(" ");
        g_string_append_printf(gstring, "%s", error->message);
        dbus_printf("%s line%d\n", gstring->str, __LINE__);
        g_string_free(gstring, TRUE);
        g_error_free(error);
        error = NULL;
    }
    //g_assert_no_error(error);
    gettimeofday(&start, NULL);

    Method_Out = g_dbus_proxy_call_sync(remote_object,
                                        dbus_method_list->name,
                                        method_input_param,
                                        G_DBUS_CALL_FLAGS_NONE,
                                        -1,
                                        NULL,
                                        &error);
    if (error)
    {
        GString *gstring;
        gstring = g_string_new(" ");
        g_string_append_printf(gstring, "%s", error->message);
        dbus_printf("%s line%d\n", gstring->str, __LINE__);
        g_string_free(gstring, TRUE);
        g_error_free(error);
        error = NULL;
    }
#else
    bus = g_bus_get_sync(G_BUS_TYPE_SYSTEM, NULL, NULL);
    EXIT_IF_NULL(bus);
    if (bus == NULL)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "Failed", "connection is NULL", __func__, "NULL point Error after g_bus_get_sync");
        dbus_object_list->test_result |= CONNECTION_NULL;
        dbus_method_list->test_result |= CONNECTION_NULL;

        return(-1);
    }
#ifdef BUILD_IN_PARAM
    method_in_value = g_variant_new(method_in_arg, g_variant_builder_end(method_in_builder));
//dbus_printf("method_in_value %s\n",g_variant_print(method_in_value, true));
//dbus_printf("method_in_value....type %s\n",g_variant_get_type_string(method_in_value));
#endif
    if (method_input_param != NULL)
    {
        dbus_printf("method_input_param %s\n", g_variant_print(method_input_param, true));
        dbus_printf("method_input_param....type %s\n", g_variant_get_type_string(method_input_param));
    }
    else
    {
        if (no_input_method)
        {
            dbus_printf("method_input_param is NULL. No IN arg method call. .\n");
        }
        else
        {
            dbus_printf("method_input_param is NULL. exit.\n");
            exit(0);
        }
    }
    if (lib_debug)
    {
        dbus_printf(" Into %s\n", dbus_method_list->name);
    }
    gettimeofday(&start, NULL);

    char* service_name = igd1_service;
    if(dbus_object_list->name != NULL)
        if(strcmp(dbus_object_list->name,"/com/ctc/saf1") == 0)
            service_name = freedesktop_service;

    Method_Out = g_dbus_connection_call_sync(bus,
                                             service_name,
                                             dbus_object_list->name,
                                             dbus_interface_list->name,
                                             dbus_method_list->name,
                                             method_input_param, 
                                             G_VARIANT_TYPE(method_out_arg),
                                                                 //G_VARIANT_TYPE("(a(ssbus)us)"),
                                             G_DBUS_CALL_FLAGS_NONE,
                                             -1,
                                             NULL,
                                             &error);
    gettimeofday(&end, NULL);
    if (lib_debug)
    {
        dbus_printf(" Out %s\n", dbus_method_list->name);
    }

    EXIT_IF_NULL(Method_Out);
    if (Method_Out == NULL)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "Failed", "Method_Out is NULL", __func__, "NULL point Error after g_dbus_connection_call_sync");
        dbus_object_list->test_result |= CONNECTION_NULL;
        dbus_method_list->test_result |= CONNECTION_NULL;
        return(-1);
    }
#endif
    if (error)
    {
        GString *gstring;
        gstring = g_string_new(" ");
        g_string_append_printf(gstring, "%s", error->message);
        dbus_printf("%s\n", gstring->str);

        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "Failed", "Error when execve method", __func__, gstring->str);
        dbus_object_list->test_result |= METHOD_CALL_FAIL;
        dbus_method_list->test_result |= METHOD_CALL_FAIL;
        g_string_free(gstring, TRUE);
        g_error_free(error);
        error = NULL;
        goto error_end;
    }
    else
    {
        dbus_object_list->test_result    &= (~UNPASS);
        dbus_interface_list->test_result &= (~UNPASS);
        dbus_method_list->test_result    &= (~UNPASS);
    }

    elapsed_time = (end.tv_sec - start.tv_sec) * 1000000 +
                   (end.tv_usec - start.tv_usec);

    //dbus_printf("%s, performace  is %s ,the perform time is %d us\n",
    //    dbus_object_list->name,(elapsed_time > 200000)?"FAILED":"OK",elapsed_time);
    if (strcmp(dbus_method_list->name, "SetDateTime") != 0)
    {
        //liuxy 0829-002 begin : Do not output "Failed" when ListFolder for "com.ctc.igd1.NASAccess" interface.
        if((g_strcmp0(dbus_interface_list->name, "com.ctc.igd1.NASAccess") == 0) && (g_strcmp0(dbus_method_list->name, "ListFolder") == 0))
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%d(us),%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", elapsed_time, "OK", (elapsed_time > 200000) ? "Time out" : "", __func__, "Do not output \"Failed\" when ListFolder for \"com.ctc.igd1.NASAccess\" interface.");
        }
        //liuxy 0829-002 end
        //liuxy 0829-003 begin : Do not output "Failed" when SetWPS for "com.ctc.igd1.WPS" interface.
        else if((g_strcmp0(dbus_interface_list->name, "com.ctc.igd1.WPS") == 0) && (g_strcmp0(dbus_method_list->name, "SetWPS") == 0))
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%d(us),%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", elapsed_time, "OK", (elapsed_time > 200000) ? "Time out" : "", __func__, "Do not output \"Failed\" when SetWPS for \"com.ctc.igd1.WPS\" interface.");
        }
        //liuxy 0829-003 end
        //liuxy 0829-004 begin :
        else if(g_strcmp0(dbus_method_list->name, "GetManagedObjects") == 0)
        {
            GVariantIter iter;
            GVariant     *entry;
            GVariant     *out_tmp;
            guint        objcount = 0;            
            g_variant_get(Method_Out,"(@a{oa{sa{sv}}})",&out_tmp);
            g_variant_iter_init(&iter, out_tmp);
            while ((entry = g_variant_iter_next_value(&iter)))
            {
                objcount++;
                g_variant_unref(entry);
            }
            dbus_printf("elapsed_time = %d,objcount = %d\n", elapsed_time,objcount);
            if(objcount <= 1)
                //normal check (elapsed_time > 200000)
                dbus_printf_twice("%s,%s,%s,%s,%s,%d(us),%s,%s,%s,%s%d\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", elapsed_time, (elapsed_time > 200000) ? "Failed" : "OK", (elapsed_time > 200000) ? "Time out" : "", __func__, "Total objects: ",objcount);
            else
            {
                //multi objects,check (elapsed_time/objcount > 200000)
                dbus_printf_twice("%s,%s,%s,%s,%s,%d(us),%s,%s,%s,%s%d\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", elapsed_time, (elapsed_time/objcount > 200000) ? "Failed" : "OK", (elapsed_time/objcount > 200000) ? "Time out" : "",__func__, "Total objects: ",objcount);
            }
        }
        //liuxy 0829-004 end
        //liuxy 0906-002 begin : Do not output "Failed" when Switch for "com.ctc.saf1.framework" interface.
        else if((g_strcmp0(dbus_interface_list->name, "com.ctc.saf1.framework") == 0) && (g_strcmp0(dbus_method_list->name, "Switch") == 0))
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%d(us),%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", elapsed_time, "OK", (elapsed_time > 200000) ? "Time out" : "", __func__, "Do not output \"Failed\" when Switch for \"com.ctc.saf1.framework\" interface.");
        }
        else
        //liuxy 0906-002 end
            dbus_printf_twice("%s,%s,%s,%s,%s,%d(us),%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", elapsed_time, (elapsed_time > 200000) ? "Failed" : "OK", (elapsed_time > 200000) ? "Time out" : "", __func__, "");
        if (elapsed_time > 200000)
        {
            dbus_object_list->test_result |= METHOD_CALL_TIMEOUT;
            dbus_method_list->test_result |= METHOD_CALL_TIMEOUT;
        }
    }

    /*if(! (g_variant_is_of_type (Method_Out, G_VARIANT_TYPE(method_out_arg))))
       {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s:%s but not:%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name,"",dbus_method_list->name,"","","Failed","Type must be",method_out_arg,g_variant_get_type_string(Method_Out),__func__, g_variant_get_type_string(Method_Out));
            return;
       }*/
    /*
            1 result errdesc are as the lastest two data.
            2 result =0 is ok, =1 is failed
     */

#if 1
    dbus_printf("print method_out %s\n", g_variant_print(Method_Out, true));
    if (g_strcmp0(method_out_arg, "(s)") == 0)
    {
        g_variant_get(Method_Out, "(s)", &str);
        //dbus_printf("method OUT (s) string=%s\n",str);
        //dbus_printf("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name, "",dbus_method_list->name,"","", "OK","method return(s)",__func__,str);
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "OK", "method return(s)", __func__, str);
    }
    else if (g_strcmp0(method_out_arg, "(u)") == 0)
    {
        g_variant_get(Method_Out, "(u)", &out1);
        //dbus_printf("method OUT (u) uint32=%d\n",out1);
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%u\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "OK", "method return(u)", __func__, out1);
    }
    else if (g_strcmp0(method_out_arg, "(su)") == 0)
    {
        g_variant_get(Method_Out, "(su)", &str, &out1);
        //dbus_printf("method OUT (su) string=%s, uint32=%d\n",str,out1);
        if (out1 == 0)
        {
            //dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%d\n",dbus_object_list->name, dbus_interface_list->name, "",dbus_method_list->name,"","", "OK","method return(su)",__func__,str,out1);
            dbus_printf("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%u\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "OK", "method return(su)", __func__, str, out1);
            dbus_printf_logfile("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%u\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "OK", "method return(su)", __func__, str, out1);
            //Notes: for % specail char
        }
        else
        {
            //dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%d\n",dbus_object_list->name, dbus_interface_list->name, "",dbus_method_list->name,"","", "Failed","method return(su)",__func__,str,out1);
            dbus_printf("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%u\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "Failed", "method return(su)", __func__, str, out1);
            dbus_printf_logfile("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%u\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "Failed", "method return(su)", __func__, str, out1);
            dbus_object_list->test_result |= METHOD_CALL_FAIL;
            dbus_method_list->test_result |= METHOD_CALL_FAIL;
            //Notes: for % specail char
        }
    }
    else if (g_strcmp0(method_out_arg, "(us)") == 0)
    {
        g_variant_get(Method_Out, "(us)", &out1, &str);
        //dbus_printf("method OUT (us) uint32=%d string=%s\n", out1, str);
        if (out1 == 0)
        {
            //dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%s\n",dbus_object_list->name, dbus_interface_list->name, "",dbus_method_list->name,"","", "OK","method return(us)",__func__,out1,str);
            dbus_printf("%s,%s,%s,%s,%s,%s,%s,%s,%s,%u,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "OK", "method return(us)", __func__, out1, str);
            dbus_printf_logfile("%s,%s,%s,%s,%s,%s,%s,%s,%s,%u,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "OK", "method return(us)", __func__, out1, str);
            //dbus_printf("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_p->name, property_p->name,"Get","","","OK","Get the value  ",__func__,str_val);
            //dbus_printf_logfile("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_p->name, property_p->name,"Get","","","OK","Get the value  ",__func__,str_val);
            //Notes: for % specail char
        }
        else
        {
            if (g_strcmp0(dbus_method_list->name, "CheckLOID") == 0)
            {
                if ((out1 > 199) && (out1 < 300))
                {
                    dbus_printf("%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "OK", "method CheckLOID return(us)", __func__, out1, str);
                    dbus_printf_logfile("%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "OK", "method CheckLOID return(us)", __func__, out1, str);
                    //dbus_printf("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_p->name, property_p->name,"Get","","","OK","Get the value  ",__func__,str_val);
                    //dbus_printf_logfile("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_p->name, property_p->name,"Get","","","OK","Get the value  ",__func__,str_val);
                    //Notes: for % specail char
                }
                else
                {
                    //dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%s\n",dbus_object_list->name, dbus_interface_list->name, "",dbus_method_list->name,"","", "Failed","method return(us)",__func__,out1,str);
                    dbus_printf("%s,%s,%s,%s,%s,%s,%s,%s,%s,%u,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "Failed", "method CheckLOID return(us)", __func__, out1, str);
                    dbus_printf_logfile("%s,%s,%s,%s,%s,%s,%s,%s,%s,%u,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "Failed", "method CheckLOID return(us)", __func__, out1, str);
                    dbus_object_list->test_result |= METHOD_CALL_FAIL;
                    dbus_method_list->test_result |= METHOD_CALL_FAIL;
                }
            }
            else
            {
                //dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%s\n",dbus_object_list->name, dbus_interface_list->name, "",dbus_method_list->name,"","", "Failed","method return(us)",__func__,out1,str);
                dbus_printf("%s,%s,%s,%s,%s,%s,%s,%s,%s,%u,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "Failed", "method return(us)", __func__, out1, str);
                dbus_printf_logfile("%s,%s,%s,%s,%s,%s,%s,%s,%s,%u,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "Failed", "method return(us)", __func__, out1, str);
                //Notes: for % specail char
                dbus_object_list->test_result |= METHOD_CALL_FAIL;
                dbus_method_list->test_result |= METHOD_CALL_FAIL;
            }
        }
    }
    else if (g_strcmp0(method_out_arg, "(ous)") == 0)
    {
        g_variant_get(Method_Out, "(ous)", &objpath, &out1, &str);
        //dbus_printf("method OUT (ous) o=%s, uint32=%d string=%s\n", objpath, out1, str);
        if (out1 == 0)
        {
            //dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%s\n",dbus_object_list->name, dbus_interface_list->name, "",dbus_method_list->name,"","", "OK","method return(ous)",__func__,objpath,out1,str);
            dbus_printf("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%u,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "OK", "method return(ous)", __func__, objpath, out1, str);
            dbus_printf_logfile("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%u,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "OK", "method return(ous)", __func__, objpath, out1, str);
            //Notes: for % specail char
        }
        else
        {
            //dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%s\n",dbus_object_list->name, dbus_interface_list->name, "",dbus_method_list->name,"","", "Failed","method return(ous)",__func__,objpath,out1,str);
            dbus_printf("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%u,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "Failed", "method return(ous)", __func__, objpath, out1, str);
            dbus_printf_logfile("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%u,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "Failed", "method return(ous)", __func__, objpath, out1, str);
            //Notes: for % specail char
            dbus_object_list->test_result |= METHOD_CALL_FAIL;
            dbus_method_list->test_result |= METHOD_CALL_FAIL;
        }
    }
    else if (g_strcmp0(method_out_arg, "(uus)") == 0)
    {
        g_variant_get(Method_Out, "(uus)", &out1, &out2, &str);
        //dbus_printf("method OUT (uus) uint32=%d uint32=%d string=%s\n", out1, out2, str);
        if (out2 == 0)
        {
            //dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%d,%s\n",dbus_object_list->name, dbus_interface_list->name, "",dbus_method_list->name,"","", "OK","method return(uus)",__func__,out1,out2,str);
            dbus_printf("%s,%s,%s,%s,%s,%s,%s,%s,%s,%u,%u,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "OK", "method return(uus)", __func__, out1, out2, str);
            dbus_printf_logfile("%s,%s,%s,%s,%s,%s,%s,%s,%s,%u,%u,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "OK", "method return(uus)", __func__, out1, out2, str);
            //Notes: for % specail char
        }
        else
        {
            //dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%d,%s\n",dbus_object_list->name, dbus_interface_list->name, "",dbus_method_list->name,"","", "Failed","method return(uus)",__func__,out1,out2,str);
            dbus_printf("%s,%s,%s,%s,%s,%s,%s,%s,%s,%u,%u,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "Failed", "method return(uus)", __func__, out1, out2, str);
            dbus_printf_logfile("%s,%s,%s,%s,%s,%s,%s,%s,%s,%u,%u,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "Failed", "method return(uus)", __func__, out1, out2, str);
            //Notes: for % specail char
            dbus_object_list->test_result |= METHOD_CALL_FAIL;
            dbus_method_list->test_result |= METHOD_CALL_FAIL;
        }
    }
    else if (g_strcmp0(method_out_arg, "(sus)") == 0)
    {
        g_variant_get(Method_Out, "(sus)", &str, &out1, &str2);
        //dbus_printf("method OUT (sus) string=%s uint32=%d string=%s\n", str, out1, str2);
        if (out1 == 0)
        {
            //dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%s\n",dbus_object_list->name, dbus_interface_list->name, "",dbus_method_list->name,"","", "OK","method return(sus)",__func__,str,out1,str2);
            dbus_printf("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%u,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "OK", "method return(sus)", __func__, str, out1, str2);
            dbus_printf_logfile("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%u,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "OK", "method return(sus)", __func__, str, out1, str2);
            //Notes: for % specail char
        }
        else
        {
            //dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%s\n",dbus_object_list->name, dbus_interface_list->name, "",dbus_method_list->name,"","", "Failed","method return(sus)",__func__,str,out1,str2);
            dbus_printf("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%u,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "Failed", "method return(sus)", __func__, str, out1, str2);
            dbus_printf_logfile("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%u,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "Failed", "method return(sus)", __func__, str, out1, str2);
            //Notes: for % specail char
            dbus_object_list->test_result |= METHOD_CALL_FAIL;
            dbus_method_list->test_result |= METHOD_CALL_FAIL;
        }
    }
    else if (g_strcmp0(method_out_arg, "(a(ssbus)us)") == 0 || g_strcmp0(method_out_arg, "(a{ssbus}us)") == 0)
    {
        GVariantIter iter;
        GVariantIter iter2;
        GVariantIter iter3;
        GVariantIter iter4;
        GVariant     *entry;
        GVariant     *entry2;
        GVariant     *entry3;
        GVariant     *entry4;
        GVariant     *value;
        GVariant     *dict_1;
        GVariant     *out_1;
        GVariant     *str_1;
        GVariant     *str_2_1;
        GVariant     *str_2_2;
        GVariant     *bool_2_1;
        GVariant     *uint32_2_1;
        GVariant     *str_2_3;
        GVariant     *info                         = NULL;
        char         *actionprint                  = (char *)__func__;
        char         *actionprintGetManagedObjects = "ListFolder";
        if (g_strcmp0(dbus_method_list->name, "ListFolder") == 0)
        {
            actionprint = actionprintGetManagedObjects;
        }
        if (g_variant_is_of_type(Method_Out, G_VARIANT_TYPE("(a(ssbus)us)")))
        {
            dbus_printf("check the (a(ssbus)us)\n");
        }
        else
        {
            //dbus_printf("check the Not  (a{oa{sa{sv}}})\n");
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "Failed", "method not return (a(ssbus)us)", actionprint, "");
        }

        dict_1 = g_variant_get_child_value(Method_Out, 0);
        out_1  = g_variant_get_child_value(Method_Out, 1);
        str_1  = g_variant_get_child_value(Method_Out, 2);

        g_variant_iter_init(&iter, dict_1);

        while ((entry = g_variant_iter_next_value(&iter)))
        {
            if (g_variant_n_children(entry) == 0)
            {
                dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "OK", "method return (ssbus)", __func__, "NULL");
                goto error_end;
            }

            str_2_1    = g_variant_get_child_value(entry, 0);
            str_2_2    = g_variant_get_child_value(entry, 1);
            bool_2_1   = g_variant_get_child_value(entry, 2);
            uint32_2_1 = g_variant_get_child_value(entry, 3);
            str_2_3    = g_variant_get_child_value(entry, 4);

            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "OK", "method return(ssbus)", __func__, g_variant_get_string(str_2_1, NULL), g_variant_get_string(str_2_2, NULL), (g_variant_get_boolean(bool_2_1)) ? "true" : "false", g_variant_get_uint32(uint32_2_1), g_variant_get_string(str_2_3, NULL));

            g_variant_unref(str_2_1);
            g_variant_unref(str_2_2);
            g_variant_unref(bool_2_1);
            g_variant_unref(uint32_2_1);
            g_variant_unref(str_2_3);
        }
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%d\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "OK", "method return u", __func__, g_variant_get_uint32(out_1));
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "OK", "method return s", __func__, g_variant_get_string(str_1, NULL));
        g_variant_unref(dict_1);
        g_variant_unref(out_1);
        g_variant_unref(str_1);
    }
    else if (g_strcmp0(method_out_arg, "(a{oa{sa{sv}}})") == 0)
    {
        GVariantIter iter;
        GVariantIter iter2;
        GVariantIter iter3;
        GVariantIter iter4;
        GVariant     *entry;
        GVariant     *entry2;
        GVariant     *entry3;
        GVariant     *entry4;
        GVariant     *value;
        GVariant     *out_tmp;
        char         *actionprint                  = (char *)__func__;
        char         *actionprintGetManagedObjects = "GetManagedObjects";
        if (g_strcmp0(dbus_method_list->name, "GetManagedObjects") == 0)
        {
            actionprint = actionprintGetManagedObjects;
        }
        if (g_variant_is_of_type(Method_Out, G_VARIANT_TYPE("(a{oa{sa{sv}}})")))
        {
            dbus_printf("check the (a{oa{sa{sv}}})\n");
        }
        else
        {
            //dbus_printf("check the Not  (a{oa{sa{sv}}})\n");
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "Failed", "method not return a{oa{sa{sv}}}", actionprint, "");
        }
        //liuxy 0831-001 : iter init error,first get to out_tmp,then iter init.
        g_variant_get(Method_Out,"(@a{oa{sa{sv}}})",&out_tmp);
        //g_variant_iter_init(&iter, Method_Out);
        g_variant_iter_init(&iter, out_tmp);

        while ((entry = g_variant_iter_next_value(&iter)))
        {
            if (g_variant_n_children(entry) == 0)
            {
                dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "OK", "method return a{oa{sa{sv}}}", actionprint, "NULL");
                goto error_end;
            }
            //GVariant *dict_1;
            GVariant *dict_2_entry;
            GVariant *dict_2;
            GVariant *dict_3_entry;
            GVariant *object_path;
            GVariant *str_name2;
            GVariant *str_name3;
            GVariant *str_name4;
            GVariant *v_3;
            GVariant *v_3_info;
            gboolean matches;
            //liuxy 0831-001
            //dict_1      = g_variant_get_child_value(entry, 0);
            //object_path = g_variant_get_child_value(dict_1, 0);
            object_path = g_variant_get_child_value(entry, 0);
            //dbus_printf("object_path... %s\n",g_variant_get_string (object_path, NULL));
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "OK", "parse object_path", actionprint, g_variant_get_string(object_path, NULL));
            //liuxy 0831-001
            //dict_2_entry = g_variant_get_child_value(dict_1, 1);
            dict_2_entry = g_variant_get_child_value(entry, 1);
            g_variant_iter_init(&iter2, dict_2_entry);
            while ((entry2 = g_variant_iter_next_value(&iter2)))
            {
                str_name2 = g_variant_get_child_value(entry2, 0);
                //dbus_printf("string... %s\n",g_variant_get_string (str_name2, NULL));
                dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s %s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "OK", "parse object_path' string", actionprint, g_variant_get_string(object_path, NULL), g_variant_get_string(str_name2, NULL));

                dict_3_entry = g_variant_get_child_value(entry2, 1);
                g_variant_iter_init(&iter3, dict_3_entry);
                while ((entry3 = g_variant_iter_next_value(&iter3)))
                {
                    str_name3 = g_variant_get_child_value(entry3, 0);
                    //dbus_printf("string... %s\n",g_variant_get_string (str_name3, NULL));
                    //v_3=g_variant_get_child_value (entry3, 1);
                    //dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s %s %s\n",dbus_object_list->name, dbus_interface_list->name, "",dbus_method_list->name,"","", "OK","parse object_path' string string",actionprint,g_variant_get_string (object_path, NULL),g_variant_get_string (str_name2, NULL),g_variant_get_string (str_name3, NULL));


                    v_3 = g_variant_get_child_value(entry3, 1);
                    g_variant_get(v_3, "v", &v_3_info);
                    if (g_variant_is_of_type(v_3_info, G_VARIANT_TYPE_STRING))
                    {
                        //dbus_printf("v_3_info ...%s\n",g_variant_get_string (v_4, NULL));
                        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s %s %s %s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "OK", "parse object_path' string varaint(string)", actionprint, g_variant_get_string(object_path, NULL), g_variant_get_string(str_name2, NULL), g_variant_get_string(str_name3, NULL), g_variant_get_string(v_3_info, NULL));
                    }
                    else if (g_variant_is_of_type(v_3_info, G_VARIANT_TYPE_BOOLEAN))
                    {
                        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s %s %s %d\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "OK", "parse object_path' string varaint(boolean)", actionprint, g_variant_get_string(object_path, NULL), g_variant_get_string(str_name2, NULL), g_variant_get_string(str_name3, NULL), g_variant_get_boolean(v_3_info));
                    }
                    else if (g_variant_is_of_type(v_3_info, G_VARIANT_TYPE_INT16))
                    {
                        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s %s %s %d\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "OK", "parse object_path' string varaint(int16)", actionprint, g_variant_get_string(object_path, NULL), g_variant_get_string(str_name2, NULL), g_variant_get_string(str_name3, NULL), g_variant_get_int16(v_3_info));
                    }
                    else if (g_variant_is_of_type(v_3_info, G_VARIANT_TYPE_UINT16))
                    {
                        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s %s %s %d\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "OK", "parse object_path' string varaint(uint16)", actionprint, g_variant_get_string(object_path, NULL), g_variant_get_string(str_name2, NULL), g_variant_get_string(str_name3, NULL), g_variant_get_uint16(v_3_info));
                    }
                    else if (g_variant_is_of_type(v_3_info, G_VARIANT_TYPE_INT32))
                    {
                        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s %s %s %d\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "OK", "parse object_path' string varaint(int32)", actionprint, g_variant_get_string(object_path, NULL), g_variant_get_string(str_name2, NULL), g_variant_get_string(str_name3, NULL), g_variant_get_int32(v_3_info));
                    }
                    else if (g_variant_is_of_type(v_3_info, G_VARIANT_TYPE_UINT32))
                    {
                        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s %s %s %d\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "OK", "parse object_path' string varaint(uint32)", actionprint, g_variant_get_string(object_path, NULL), g_variant_get_string(str_name2, NULL), g_variant_get_string(str_name3, NULL), g_variant_get_uint32(v_3_info));
                    }
                    else if (g_variant_is_of_type(v_3_info, G_VARIANT_TYPE_INT64))
                    {
                        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s %s %s %lld\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "OK", "parse object_path' string varaint(int64)", actionprint, g_variant_get_string(object_path, NULL), g_variant_get_string(str_name2, NULL), g_variant_get_string(str_name3, NULL), g_variant_get_int64(v_3_info));
                    }
                    else if (g_variant_is_of_type(v_3_info, G_VARIANT_TYPE_UINT64))
                    {
                        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s %s %s %lld\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "OK", "parse object_path' string varaint(uint64)", actionprint, g_variant_get_string(object_path, NULL), g_variant_get_string(str_name2, NULL), g_variant_get_string(str_name3, NULL), g_variant_get_uint64(v_3_info));
                    }
                    else if (g_variant_is_of_type(v_3_info, G_VARIANT_TYPE_DOUBLE))
                    {
                        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s %s %s %lf\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "OK", "parse object_path' string varaint(double)", actionprint, g_variant_get_string(object_path, NULL), g_variant_get_string(str_name2, NULL), g_variant_get_string(str_name3, NULL), g_variant_get_double(v_3_info));
                    }
                    else if (g_variant_is_of_type(v_3_info, G_VARIANT_TYPE_OBJECT_PATH))
                    {
                        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s %s %s %s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "OK", "parse object_path' string varaint(object_path)", actionprint, g_variant_get_string(object_path, NULL), g_variant_get_string(str_name2, NULL), g_variant_get_string(str_name3, NULL), g_variant_get_string(v_3_info, NULL));
                    }
                    else
                    {
                        //dbus_printf("v_3_info other type\n");
                        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s %s %s %s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "OK", "parse object_path' string varaint(unknown)", actionprint, g_variant_get_string(object_path, NULL), g_variant_get_string(str_name2, NULL), g_variant_get_string(str_name3, NULL), "");
                    }

                    g_variant_unref(v_3);
                    g_variant_unref(v_3_info);

                    g_variant_unref(str_name3);
                    g_variant_unref(entry3);
                }
                g_variant_unref(dict_3_entry);
                g_variant_unref(str_name2);
                g_variant_unref(entry2);
            }
            g_variant_unref(dict_2_entry);
            g_variant_unref(object_path);
            //g_variant_unref(dict_1);
            g_variant_unref(entry);
        }
    }

    else
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", dbus_method_list->name, "", "", "OK", "method return, need more type parse", __func__, method_out_arg);
    }
    //g_variant_get(Method_Out, "(&s)", &str);
#endif

    if (out2 == 0)
    {
        if ((g_strcmp0(dbus_interface_list->name, "com.ctc.igd1.NASAccess") == 0) && (g_strcmp0(dbus_method_list->name, "Copy") == 0))
        //if((g_strcmp0(dbus_interface_list->name,"com.ctc.igd1.NASAccess")==0) && (g_strcmp0(dbus_method_list->name,"GetFileNum")==0))
        {
            Copy_TransactionId = out1;
            dbus_printf("\n\n       GetCopyProgress bind to Copy. Using the  Copy_TransactionId=%d\n\n", Copy_TransactionId);
            dbus_printf("         Sleep 1s to get the copy process\n");
            sleep(1);
#ifdef TS_METHOD_PROXY
            //remote_object_method_Lookup(dbus_object_list->name, dbus_interface_list->name,NULL,"GetCopyProgress");
            Method_Out2 = g_dbus_proxy_call_sync(remote_object,
                                                 "GetCopyProgress",                        //dbus_method_list->name,
                                                                                           //g_variant_new("(u)", &Copy_TransactionId),//method_input_param,
                                                 g_variant_new("(u)", Copy_TransactionId), //method_input_param,
                                                 G_DBUS_CALL_FLAGS_NONE,
                                                 -1,
                                                 NULL,
                                                 &error);
            if (error)
            {
                GString *gstring;
                gstring = g_string_new(" ");
                g_string_append_printf(gstring, "%s", error->message);
                dbus_printf("%s line%d\n", gstring->str, __LINE__);
                g_string_free(gstring, TRUE);
                g_error_free(error);
                error = NULL;
            }
#else
            if (lib_debug)
            {
                dbus_printf(" Into %s\n", dbus_method_list->name);
            }
            Method_Out2 = g_dbus_connection_call_sync(bus,
                                                      "com.ctc.igd1",
                                                      dbus_object_list->name,
                                                      dbus_interface_list->name,
                                                      "GetCopyProgress",                        //dbus_method_list->name,
                                                      g_variant_new("(u)", Copy_TransactionId), //method_input_param,//g_variant_new("(ss)", dbus_interface_list->name,dbus_property_list->name),
                                                                                                //g_variant_new("(suu)", "/mnt/usb1_1", 1,5),
                                                                                                //g_variant_new("(s)", "/mnt/usb1_1"),
                                                                                                //method_in_value,
                                                      G_VARIANT_TYPE("(uus)"),
                                                                                                //G_VARIANT_TYPE("(a(ssbus)us)"),
                                                      G_DBUS_CALL_FLAGS_NONE,
                                                      -1,
                                                      NULL,
                                                      &error);
            if (lib_debug)
            {
                dbus_printf(" Out %s\n", dbus_method_list->name);
            }
#endif
            if (error)
            {
                GString *gstring;
                gstring = g_string_new(" ");
                g_string_append_printf(gstring, "%s", error->message);
                dbus_printf("%s\n", gstring->str);

                dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", "GetCopyProgress", "", "", "Failed", "Error when execve method", __func__, gstring->str);
                dbus_object_list->test_result |= METHOD_CALL_FAIL;
                //dbus_method_list->test_result |= METHOD_CALL_FAIL;
                list_for_each(method_list_item_p, &dbus_interface_list->method_list)
                {
                    struct dbus_method *dbus_method_getcopyprogress_p = node_to_item(method_list_item_p, struct dbus_method, list);
    
                    if (dbus_method_getcopyprogress_p == NULL)
                    {
                        continue;
                    }
                    if (strcmp(dbus_method_getcopyprogress_p->name,"GetCopyProgress")==0)
                    {
                        dbus_method_getcopyprogress_p->test_result |= METHOD_CALL_FAIL;
                    }
                }

                g_string_free(gstring, TRUE);
                g_error_free(error);
                error = NULL;
                goto error2_end;
            }

            g_variant_get(Method_Out2, "(uus)", &out1, &out2, &str);
            dbus_printf("method OUT (uus) uint32=%d uint32=%d string=%s\n", out1, out2, str);
            if (out2 == 0)
            {
                dbus_printf_logfile("%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%d,%s\n", dbus_object_list->name, dbus_interface_list->name, "", "GetCopyProgress", "", "", "OK", "method return(uus)", __func__, out1, out2, str);
            }
            else
            {
                dbus_printf_logfile("%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%d,%s\n", dbus_object_list->name, dbus_interface_list->name, "", "GetCopyProgress", "", "", "Failed", "method return(uus)", __func__, out1, out2, str);
                dbus_object_list->test_result |= METHOD_CALL_FAIL;
                //dbus_method_list->test_result |= METHOD_CALL_FAIL;
                list_for_each(method_list_item_p, &dbus_interface_list->method_list)
                {
                    struct dbus_method *dbus_method_getcopyprogress_p = node_to_item(method_list_item_p, struct dbus_method, list);
    
                    if (dbus_method_getcopyprogress_p == NULL)
                    {
                        continue;
                    }
                    if (strcmp(dbus_method_getcopyprogress_p->name,"GetCopyProgress")==0)
                    {
                        dbus_method_getcopyprogress_p->test_result |= METHOD_CALL_FAIL;
                    }
                }
            }

            dbus_printf("   sleep tools for sync copy. Current Percent is %d\n", out1);
            guint32         finished = 1;
            if (out2 > 100)
            {
                dbus_printf("   Current Percent more then 100??? Sleep 1s\n");
            }
            else if (out2 == 100 )
            {
                dbus_printf("   Current Percent equal to 100??? Sleep 1s\n");
            }
            else 
            {
                //dbus_printf("   Current Percent more then 100??? Sleep 1s\n");
                finished = 100 - out1;
            }
            {
                guint32 s = 200;
                if (finished >= 1)
                {
                    s = 100 / finished;
                    if (s > 100)
                    {
                        s = 100;
                    }
                }
                else
                {
                    dbus_printf("   finished<1, sleep 100s time\n");
                    s = 100;
                }
                dbus_printf(" Wait (%d)s for Copy last %d\n", s, out1);
                int k = 0;
                for (k = 0; k < s; )
                {
                    sleep(5);
                    k += 5;
                    dbus_printf("wait (%d)s\n", k);
                }
                //system("ls -l /mnt/USB_disc1/dianxintest.tar");//USB_disc1 is not the path in tongwei.
                dbus_printf("##############\n");
                //system("ls -l /mnt/USB_disc1/2");
                dbus_printf("##############\n");
                //system("ls -l /mnt/USB_disc1/");
            }
            g_variant_unref(Method_Out2);
        }
    }

    if (WANConnectionInfo_IfName != NULL)
    {
        dbus_printf("free WANConnectionInfo_IfName\n");
        free(WANConnectionInfo_IfName);
        WANConnectionInfo_IfName = NULL;
        dbus_printf("free WANConnectionInfo_IfName end\n");
    }

    if (LANHost_MAC != NULL)
    {
        dbus_printf("free LANHost_MAC\n");
        free(LANHost_MAC);
        LANHost_MAC = NULL;
        dbus_printf("free LANHost_MAC end\n");
    }

    if (LANHost_Port != NULL)
    {
        dbus_printf("free LANHost_Port\n");
        free(LANHost_Port);
        LANHost_Port = NULL;
        dbus_printf("free LANHost_Port end\n");
    }
error2_end:
    g_variant_unref(Method_Out);
error_end:
#ifdef TS_METHOD_PROXY
    g_object_unref(G_OBJECT(remote_object));
#endif
    g_object_unref(bus);
early_out:
    return(ret);
} /* remote_object_method */


int igd1_Set(struct dbus_object *dbus_object_list, struct dbus_interface *dbus_interface_list, struct dbus_property *dbus_property_list)
{
    //return igd1_Get_Set_or_Checksignal(dbus_object_list, dbus_interface_list, dbus_property_list);
    return(igd1_Set_Checksignal_CheckGet(dbus_object_list, dbus_interface_list, dbus_property_list, 0));
}


int igd1_Get(struct dbus_object *dbus_object_list, struct dbus_interface *dbus_interface_list, struct dbus_property *dbus_property_list)
{
    //Set method under "com.ctc.igd1.Properties"
    struct dbus_interface *dbus_interface_p;
    struct dbus_property  *property_p;

    dbus_interface_p = dbus_interface_list;
    property_p       = dbus_property_list;

    GDBusConnection *bus;
    GDBusProxy      *remote_object;
    GError          *error = NULL;
    GVariant        *Method_Out;
    GVariant        *method_input_param;
    struct timeval  start;
    struct timeval  stepa;
    struct timeval  stepb;
    struct timeval  end;
    guint           elapsed_time = 0;

    char            property_in_express[ARG_NUM] = "(ss";
    //char property_out_express[ARG_NUM]="(";
    char            *p_in = property_in_express + sizeof("(ss") - 1;
    //char *p_out=property_out_express+sizeof("(")-1;

    GVariant *info    = NULL;
    gchar    *str_val = NULL;
    guint16  uint16_val;
    gint16   int16_val;
    gint32   int32_val;
    guint32  uint32_val;
    gint64   int64_val;
    guint64  uint64_val;
    gchar    byte_val;
    gdouble  double_val;
    gboolean bool_val;


    strcpy(p_in, ")");
    p_in += 1;
    //strcpy(p_out,")");
    //p_out +=1;
    *p_in = '\0';
    //*p_out='\0';
    //dbus_printf("igd1 %s[Get] the property [%s] type[%s] in [%s]@[%s]\n", property_in_express, property_p->name,property_p->type, dbus_object_list->name, dbus_interface_p->name);
    dbus_printf("%s line%d\n", __func__, __LINE__);
    method_input_param = g_variant_new(property_in_express, dbus_interface_p->name, property_p->name);

    gettimeofday(&stepa, NULL);
    bus = g_bus_get_sync(G_BUS_TYPE_SYSTEM, NULL, &error);
    EXIT_IF_NULL(bus);
    dbus_printf("%s line%d\n", __func__, __LINE__);
    if (error)
    {
        GString *gstring;
        gstring = g_string_new(" ");
        g_string_append_printf(gstring, "%s", error->message);
        dbus_printf("%s line%d\n", gstring->str, __LINE__);
        g_string_free(gstring, TRUE);
        g_error_free(error);
        error = NULL;
    }
    if (bus == NULL)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name, "", "", "", "Failed", "connection is NULL", __func__, "NULL point Error after g_bus_get_sync");
        dbus_object_list->test_result   |= CONNECTION_NULL;
        dbus_property_list->test_result |= CONNECTION_NULL;
        return(-1);
    }
    dbus_printf("%s line%d\n", __func__, __LINE__);
    gettimeofday(&stepb, NULL);
    //g_assert_no_error(error);
    char* service_name = igd1_service;
    if(dbus_object_list->name != NULL)
        if(strcmp(dbus_object_list->name,"/com/ctc/saf1") == 0)
            service_name = freedesktop_service;

    remote_object = g_dbus_proxy_new_sync(bus,
                                          G_DBUS_PROXY_FLAGS_NONE,
                                          NULL,
                                          service_name,
                                          dbus_object_list->name,
                                          "com.ctc.igd1.Properties",
                                          NULL,
                                          &error);
    dbus_printf("%s line%d\n", __func__, __LINE__);
    if (error)
    {
        GString *gstring;
        gstring = g_string_new(" ");
        g_string_append_printf(gstring, "%s", error->message);
        dbus_printf("%s line%d\n", gstring->str, __LINE__);
        g_string_free(gstring, TRUE);
        g_error_free(error);
        error = NULL;
    }
    //g_assert_no_error(error);
    gettimeofday(&start, NULL);
    dbus_printf("%s line%d\n", __func__, __LINE__);

    if (method_input_param != NULL)
    {
        gchar *s;
        s = g_variant_print(method_input_param, true);
    dbus_printf("%s line%d\n", __func__, __LINE__);
        //dbus_printf("method_input_param %s\n", g_variant_print(method_input_param, true));
        dbus_printf("method_input_param %s\n", s);
    dbus_printf("%s line%d\n", __func__, __LINE__);
        g_free(s);
    dbus_printf("%s line%d\n", __func__, __LINE__);
        dbus_printf("method_input_param....type %s\n", g_variant_get_type_string(method_input_param));
    dbus_printf("%s line%d\n", __func__, __LINE__);
    }
    else
    {
        dbus_printf("method_input_param is NULL. exit.\n");
        //exit(0);
        return(-1);
    }
    dbus_printf("%s line%d\n", __func__, __LINE__);
    Method_Out = g_dbus_proxy_call_sync(remote_object,
                                        "Get",
                                        method_input_param,
                                        G_DBUS_CALL_FLAGS_NONE,
                                        3000,//-1,
                                        NULL,
                                        &error);
    gettimeofday(&end, NULL);
    dbus_printf("%s line%d\n", __func__, __LINE__);

    if (error)
    {
        GString *gstring;
        gstring = g_string_new(" ");
        g_string_append_printf(gstring, "%s", error->message);
        dbus_printf("%s\n", gstring->str);
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "", "", "", "Failed", "Error when get", __func__, gstring->str);
        dbus_object_list->test_result   |= PROPERTY_CANT_GET_OR_GETALL;
        dbus_property_list->test_result |= PROPERTY_CANT_GET_OR_GETALL;
        g_string_free(gstring, TRUE);
        g_error_free(error);
        error = NULL;
        goto Get_error_end;
    }
    else
    {
        dbus_object_list->test_result    &= (~UNPASS);
        dbus_interface_list->test_result &= (~UNPASS);
        property_p->test_result          &= (~UNPASS);
    }

    dbus_printf("%s line%d\n", __func__, __LINE__);
    if (Method_Out != NULL)
    {
        gchar *s;
    dbus_printf("%s line%d\n", __func__, __LINE__);
        s = g_variant_print(Method_Out, true);
        //dbus_printf("Method_Out %s\n", g_variant_print(Method_Out, true));
    dbus_printf("%s line%d\n", __func__, __LINE__);
        dbus_printf("Method_Out %s\n", s);
        g_free(s);
    dbus_printf("%s line%d\n", __func__, __LINE__);
        dbus_printf("Method_Out....type %s\n", g_variant_get_type_string(Method_Out));
    }
    else
    {
        dbus_printf("Method_Out is NULL. exit.\n");
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Get", "", "", "Failed", "Get NULL object", __func__, "");
        dbus_object_list->test_result |= NULL_OBJECT_BY_METHOD_CALL;
        property_p->test_result       |= NULL_OBJECT_BY_METHOD_CALL;
        //exit(0);
        return(-1);
    }
    elapsed_time = (end.tv_sec - start.tv_sec) * 1000000 +
                   (end.tv_usec - start.tv_usec);

    dbus_printf("%s line%d\n", __func__, __LINE__);
    //dbus_printf("stepb.sec=%d, stepa.sec=%d,  stepb.usec=%d, stepa.usec=%d. diff=%d(us)\n",stepb.tv_sec,stepa.tv_sec, stepb.tv_usec, stepa.tv_usec,((stepb.tv_sec - stepa.tv_sec)*1000000 + (stepb.tv_usec - stepa.tv_usec)));
    //dbus_printf("start.sec=%d, stepb.sec=%d,  start.usec=%d, stepb.usec=%d. diff=%d(us)\n",start.tv_sec,stepb.tv_sec, start.tv_usec, stepb.tv_usec,((start.tv_sec - stepb.tv_sec)*1000000 + (start.tv_usec - stepb.tv_usec)));
    //dbus_printf("end.sec=%d, start.sec=%d,  end.usec=%d, start.usec=%d. diff=%d(us)\n",end.tv_sec,start.tv_sec, end.tv_usec, start.tv_usec,((end.tv_sec - start.tv_sec)*1000000 + (end.tv_usec - start.tv_usec)));
    if (in_parallel_test)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%d(us),%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Get", "", elapsed_time, "Human judge", "Get the value", __func__, "");
    }
    else
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%d(us),%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Get", "", elapsed_time, (elapsed_time > 200000) ? "Failed" : "OK", (elapsed_time > 200000) ? "Time out" : "", __func__, "");
        if (elapsed_time > 200000)
        {
            dbus_object_list->test_result   |= PROPERTY_GET_SET_TIMEOUT;
            dbus_property_list->test_result |= PROPERTY_GET_SET_TIMEOUT;
        }
    }
    g_variant_get(Method_Out, "(v)", &info);
    if (!g_variant_is_of_type(info, G_VARIANT_TYPE(dbus_property_list->type)))
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s:%s but not:%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name, "", "", "", "Failed", "Type must be", dbus_property_list->type, g_variant_get_type_string(info), __func__, g_variant_get_type_string(info));
        dbus_object_list->test_result   |= PROPERTY_WRONG_TYPE;
        dbus_property_list->test_result |= PROPERTY_WRONG_TYPE;
        return;
    }

    if (0 == g_strcmp0(property_p->type, "s"))
    {
        g_variant_get(Method_Out, "(v)", &info);
        g_variant_get(info, "s", &str_val);
        //dbus_printf ("property name : %s  , %s\n ",property_p->name,str_val);
        dbus_printf("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Get", "", "", "OK", "Get the value  ", __func__, str_val);
        dbus_printf_logfile("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Get", "", "", "OK", "Get the value  ", __func__, str_val);
        //Notes: for % specail char

        if (strcmp(dbus_interface_p->name, "com.ctc.igd1.WANConnectionInfo") == 0 && strcmp(property_p->name, "IfName") == 0)
        {
            dbus_printf("   Record com.ctc.igd1.WANConnectionInfo.IfName=%s . For GetWANConnByName\n", str_val);
            WANConnectionInfo_IfName = malloc(strlen(str_val) + 1);
            //strncpy(WANConnectionInfo_IfName,str_val,strlen(str_val));
            strcpy(WANConnectionInfo_IfName, str_val);
        }
        if (strcmp(dbus_interface_p->name, "com.ctc.igd1.LANHost") == 0 && strcmp(property_p->name, "MAC") == 0)
        {
            dbus_printf("   Record %s.com.ctc.igd1.LANHost.MAC=%s . For KickOutDevice\n", dbus_object_list->name, str_val);
            LANHost_MAC = malloc(strlen(str_val) + 1);
            //strncpy(LANHost_MAC,str_val,strlen(str_val));
            strcpy(LANHost_MAC, str_val);
        }
    }
    else if (0 == g_strcmp0(property_p->type, "o"))
    {
        g_variant_get(Method_Out, "(v)", &info);
        g_variant_get(info, "o", &str_val);
        //dbus_printf ("property name : %s  , %s\n ",property_p->name,str_val);
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Get", "", "", "OK", "Get the value  ", __func__, str_val);
    }
    else if (0 == g_strcmp0(property_p->type, "g"))
    {
        g_variant_get(Method_Out, "(v)", &info);
        g_variant_get(info, "g", &str_val);
        //dbus_printf ("property name : %s  , %s\n ",property_p->name,str_val);
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Get", "", "", "OK", "Get the value  ", __func__, str_val);
    }
    else if (0 == g_strcmp0(property_p->type, "b"))
    {
        g_variant_get(Method_Out, "(v)", &info);
        g_variant_get(info, "b", &bool_val);
        //dbus_printf ("property name : %s  , %d\n ",property_p->name,byte_val);
        if (bool_val)
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,true\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Get", "", "", "OK", "Get the value  ", __func__);
        }
        else
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,false\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Get", "", "", "OK", "Get the value  ", __func__);
        }
    }
    else if (0 == g_strcmp0(property_p->type, "y"))
    {
        g_variant_get(Method_Out, "(v)", &info);
        g_variant_get(info, "y", &byte_val);
        //dbus_printf ("property name : %s  , %d\n ",property_p->name,byte_val);
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%d\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Get", "", "", "OK", "Get the value  ", __func__, byte_val);

        if (strcmp(dbus_interface_p->name, "com.ctc.igd1.LANHost") == 0 && strcmp(property_p->name, "Port") == 0)
        {
            char cmd[100];
            char *p = cmd;
            dbus_printf("   Record %s.com.ctc.igd1.LANHost.Port=%d . For KickOutDevice\n", dbus_object_list->name, byte_val);
            sprintf(p, "%d", byte_val);
            LANHost_Port = malloc(strlen(p) + 1);
            //strncpy(LANHost_Port,p,strlen(p));
            strcpy(LANHost_Port, p);
        }
        if (strcmp(dbus_interface_p->name, "com.ctc.igd1.LANHost") == 0 && strcmp(property_p->name, "ConnectionType") == 0)
        {
            char cmd[100];
            char *p = cmd;
            dbus_printf("   Record %s.com.ctc.igd1.LANHost.ConnectionType=%d . For KickOutDevice\n", dbus_object_list->name, byte_val);
            //sprintf(p,"%d",byte_val);
            //LANHost_Port=malloc(strlen(p)+1);
            //strncpy(LANHost_Port,p,strlen(p));
            //strcpy(LANHost_Conn,p);
            LANHost_ConnectionType = byte_val;
        }
    }
    else if (0 == g_strcmp0(property_p->type, "n"))
    {
        g_variant_get(Method_Out, "(v)", &info);
        g_variant_get(info, "n", &int16_val);
        //dbus_printf ("property name : %s  , %d\n ",property_p->name,int16_val);
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%d\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Get", "", "", "OK", "Get the value  ", __func__, int16_val);
    }
    else if (0 == g_strcmp0(property_p->type, "q"))
    {
        g_variant_get(Method_Out, "(v)", &info);
        g_variant_get(info, "q", &uint16_val);
        //dbus_printf ("property name : %s  , %d\n ",property_p->name,uint16_val);
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%d\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Get", "", "", "OK", "Get the value  ", __func__, uint16_val);
    }
    else if (0 == g_strcmp0(property_p->type, "i"))
    {
        g_variant_get(Method_Out, "(v)", &info);
        g_variant_get(info, "i", &int32_val);
        //dbus_printf ("property name : %s  , %d\n ",property_p->name,int32_val);
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%d\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Get", "", "", "OK", "Get the value  ", __func__, int32_val);
    }
    else if (0 == g_strcmp0(property_p->type, "u"))
    {
        g_variant_get(Method_Out, "(v)", &info);
        g_variant_get(info, "u", &uint32_val);
        //dbus_printf ("property name : %s  , %d\n ",property_p->name,uint32_val);
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%d\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Get", "", "", "OK", "Get the value  ", __func__, uint32_val);
    }
    else if (0 == g_strcmp0(property_p->type, "x"))
    {
        g_variant_get(Method_Out, "(v)", &info);
        g_variant_get(info, "x", &int64_val);
        //dbus_printf ("property name : %s  , %ld\n ",property_p->name,int64_val);
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%lld\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Get", "", "", "OK", "Get the value  ", __func__, int64_val);
    }
    else if (0 == g_strcmp0(property_p->type, "t"))
    {
        g_variant_get(Method_Out, "(v)", &info);
        g_variant_get(info, "t", &uint64_val);

        //dbus_printf ("property name : %s  , %ld\n ",property_p->name,uint64_val);
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%llu\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Get", "", "", "OK", "Get the value  ", __func__, uint64_val);
    }
    else if (0 == g_strcmp0(property_p->type, "h"))
    {
        g_variant_get(Method_Out, "(v)", &info);
        g_variant_get(info, "h", &uint32_val);
        //dbus_printf ("property name : %s  , %d\n ",property_p->name,uint32_val);
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%d\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Get", "", "", "OK", "Get the value  ", __func__, uint32_val);
    }
    else if (0 == g_strcmp0(property_p->type, "d"))
    {
        g_variant_get(Method_Out, "(v)", &info);
        g_variant_get(info, "d", &double_val);
        //dbus_printf ("property name : %s  , %lf\n ",property_p->name,double_val);
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%lf\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Get", "", "", "OK", "Get the value  ", __func__, double_val);
    }
    else if (0 == g_strcmp0(property_p->type, "as"))
    {
#if 1
        if (g_variant_is_of_type(Method_Out, G_VARIANT_TYPE("(v)")))
        {
            GVariant     *wps_devparse_info = NULL;
            GVariantIter *iter              = NULL;
            gchar        *parse_info        = NULL;
            g_variant_get(Method_Out, "(v)", &wps_devparse_info);
            g_variant_get(wps_devparse_info, "as", &iter);
            //g_variant_get(Method_Out, "s", &iter);
            //gsize size;
            //g_variant_get_strv (str_out, &size);
            dbus_printf("as type data warp with (v)\n");
            if (iter == NULL)
            {
                dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name, "", "", "", "OK", "Get the (as)value  ", __func__, "");
            }
            else
            {
                while (g_variant_iter_next(iter, "s", &parse_info))
                {
                    //dbus_printf("   Device Info: %s\n", parse_info);  //add your customizaition code
                    dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name, "", "", "", "OK", "Get the (as)value  ", __func__, parse_info);
                    g_free(parse_info);
                }

                g_variant_unref(wps_devparse_info);
                g_variant_iter_free(iter);
            }
        }
        else
        {
            GVariant     *wps_devparse_info = NULL;
            GVariantIter *iter              = NULL;
            gchar        *parse_info        = NULL;

            dbus_printf("as type data not warp with (v)\n");
            //g_variant_get (Method_Out, "(v)", &wps_devparse_info);
            //g_variant_get(wps_devparse_info, "as", &iter);
            //g_variant_get(Method_Out, "s", &iter);
            g_variant_get(Method_Out, "as", &iter);
            if (iter == NULL)
            {
                dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name, "", "", "", "OK", "Get the (as) value  ", __func__, "");
            }
            else
            {
                while (g_variant_iter_next(iter, "s", &parse_info))
                {
                    //dbus_printf("   Device Info: %s\n", parse_info);  //add your customizaition code
                    dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name, "", "", "", "OK", "Get the (as) value  ", __func__, parse_info);
                    g_free(parse_info);
                }

                //g_variant_unref(wps_devparse_info);
                g_variant_iter_free(iter);
            }
        }
#endif


#if 0   //Tongwei oK.......
     //if(g_variant_is_of_type (Method_Out, G_VARIANT_TYPE ("(v)")))
        {
            GVariant     *wps_devparse_info = NULL;
            GVariantIter *iter              = NULL;
            gchar        *parse_info        = NULL;

            //g_variant_get (Method_Out, "(v)", &wps_devparse_info);
            //g_variant_get(wps_devparse_info, "as", &iter);
            g_variant_get(Method_Out, "s", &iter);
            if (iter == NULL)
            {
                dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name, "", "", "", "OK", "Get the value  ", __func__, "");
            }
            else
            {
                while (g_variant_iter_next(iter, "s", &parse_info))
                {
                    //dbus_printf("   Device Info: %s\n", parse_info);  //add your customizaition code
                    dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name, "", "", "", "OK", "Get the value  ", __func__, parse_info);
                    g_free(parse_info);
                }

                g_variant_unref(wps_devparse_info);
                g_variant_iter_free(iter);
            }
        }
#endif


#if 0
        {
            //g_variant_get(value, "(v)", &info);
            g_variant_get(info, "s", &str_val);
            if (str_val == NULL)
            {
                //dbus_printf("NULL....\n");
                dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name, "", "", "", "OK", "", __func__, "");
                return(0);
            }
        }


        GVariantIter *iter;
        g_variant_get(info, "as", &iter);
        while (g_variant_iter_loop(iter, "s", &str_val))
        {
            //dbus_printf ("property name :string , %s\n ",str_val);
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Get", "", "", "OK", "", __func__, str_val);
        }
        g_variant_iter_free(iter);
#endif
    }
    else
    {
        //dbus_printf ("property type no find \n");
        //g_print ("result type = %s, %s\n", g_variant_get_type_string(Method_Out), g_variant_print (Method_Out, true));
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Get", "", "", "Failed", "property type no find    ", __func__, "");
        dbus_object_list->test_result   |= PROPERTY_WRONG_TYPE;
        dbus_property_list->test_result |= PROPERTY_WRONG_TYPE;
        //g_variant_get(result, "s", &str_val);
        //dbus_printf ("type other = %s\n",(gchar *) str_val);
    }

    g_variant_unref(Method_Out);
Get_error_end:
    g_object_unref(G_OBJECT(remote_object));
    g_object_unref(bus);
    return(0);
} /* igd1_Get */


#if defined (Broadcom)
#define CT_DBUS_KNOWN_NAME               "com.ctc.igd1"
#define CT_INTERFACE_PROPERTIES          "com.ctc.igd1.Properties"
#define CT_METHOD_PROPERTIES_SETMULTI    "SetMulti"


GDBusConnection *dbus_get_connection(void)
{
    static GDBusConnection *dbus_connection_volatile = NULL;

    if (g_once_init_enter(&dbus_connection_volatile))
    {
        GError          *err             = NULL;
        GDBusConnection *dbus_connection = g_bus_get_sync(G_BUS_TYPE_SYSTEM,  //DBUS_TYPE,
                                                          NULL,
                                                          &err);

        if (NULL == dbus_connection)
        {
            g_print("%s->Error: %s\n", __FUNCTION__, err->message);
            g_error_free(err);
        }
        g_once_init_leave(&dbus_connection_volatile, dbus_connection);
    }
    return(dbus_connection_volatile);
}


int dbus_set_multi_property(const char *service_name,
                            const char *object_path,
                            const char *interface_name,
                            GVariant   *values)
{
    GVariant        *res      = NULL;
    GError          *error    = NULL;
    GVariantBuilder *builder  = NULL;
    GVariantBuilder *builder1 = NULL;

    GVariantIter    *iter       = NULL;
    GVariant        *prop_val   = NULL;
    gchar           *prop_name  = NULL;
    GVariant        *multivals2 = NULL;

    g_print("%s: %s->%s\n", __FUNCTION__, interface_name, object_path);

    if (NULL == dbus_get_connection())
    {
        g_print("  Null connection?\n");
        return(-1);
    }

    res = g_dbus_connection_call_sync(dbus_get_connection(),
                                      service_name,
                                      object_path,
                                      CT_INTERFACE_PROPERTIES,
                                      CT_METHOD_PROPERTIES_SETMULTI,
                                      g_variant_new("(s@a{sv})", interface_name, values),
                                      NULL,
                                      G_DBUS_CALL_FLAGS_NONE,
                                      -1,
                                      NULL,
                                      &error);

    if (error != NULL)
    {
        g_print("  Error: %s\n", error->message);
        g_error_free(error);
        return(-1);
    }

    return(0);
}


void unitest_pushweb_setmulti_property(void)
{
    GVariantBuilder *builder   = NULL;
    GVariant        *multivals = NULL;

    builder = g_variant_builder_new(G_VARIANT_TYPE("a{sv}"));

    /*please refer to glib/gvariant.c for other types*/
    g_variant_builder_add(builder, "{sv}", "Enable", g_variant_new_boolean(TRUE));
    g_variant_builder_add(builder, "{sv}", "Width", g_variant_new_uint32(160));
    g_variant_builder_add(builder, "{sv}", "Height", g_variant_new_uint32(90));
    //multivals = g_variant_new("(a{sv})", builder, NULL);
    multivals = g_variant_new("@a{sv}", g_variant_builder_end(builder));
    g_variant_builder_unref(builder);
    int ret = dbus_set_multi_property(CT_DBUS_KNOWN_NAME,
                                      "/com/ctc/igd1/Config/TE/PushWeb",
                                      "com.ctc.igd1.PushWeb",
                                      multivals);

    g_print("  %s\n", (ret == 0) ? "succeed" : "failed");
}
#endif

int igd1_SetMulti(struct dbus_object *dbus_object_list, struct dbus_interface *dbus_interface_list)
{

    if (redundancy)
    {
        sleep(1);
    }

    //Set method under "com.ctc.igd1.Properties"
    struct listnode       *interface_list_item_p;
    struct dbus_interface *dbus_interface_p;
    struct listnode       *property_list_item_p;
    struct dbus_property  *property_p;


    dbus_interface_p = dbus_interface_list;
    if (!list_empty(&dbus_interface_p->property_list))
    {
        int             readwrite_num = 0;
        list_for_each(property_list_item_p, &dbus_interface_p->property_list)
        {
            property_p = node_to_item(property_list_item_p, struct dbus_property, list);

            if (g_strcmp0(property_p->access, "readwrite") == 0)
            {
                readwrite_num ++;
            }
        }
        if (readwrite_num == 0 )
        {

            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", "SetMulti ", "", "", "OK", "no readwrite property", __func__, "");
            return (0);  
        }
    }

    if (!list_empty(&dbus_interface_p->property_list))
    {
        GVariantBuilder *setmulti_builder;
        //GVariantBuilder setmulti_builder;
        GVariantBuilder setmulti_builder2;
        GVariant        *setmulti_value;
        GVariant        *setmulti_value2;
        setmulti_builder = g_variant_builder_new(G_VARIANT_TYPE("a{sv}"));
        //g_variant_builder_init (&setmulti_builder, (G_VARIANT_TYPE("a{sv}")));

        GDBusConnection *bus;
        GDBusProxy      *remote_object;
        GError          *error = NULL;
        GVariant        *Method_Out;
        GVariant        *method_input_param;
        struct timeval  start;
        struct timeval  end;
        guint           elapsed_time = 0;
        struct listnode *arg_list_item_p;
        char            property_in_express[ARG_NUM]  = "(sa{sv}";
        char            property_out_express[ARG_NUM] = "(";
        char            *p_in                         = property_in_express + sizeof("(sa{sv}") - 1;
        char            *p_out                        = property_out_express + sizeof("(") - 1;

 

        list_for_each(property_list_item_p, &dbus_interface_p->property_list)
        {
            property_p = node_to_item(property_list_item_p, struct dbus_property, list);

            if (g_strcmp0(property_p->access, "read") == 0)
            {
                //don't "set" only "read" property
                //dbus_printf("failed. no test_value. standrd [set] the property [%s] type[%s] in [%s]@[%s]\n", property_p->name,property_p->type, dbus_object_list->name, dbus_interface_p->name);
                continue;
            }
            dbus_printf("   SetMulti set the %s with test_value\n", property_p->name);
            g_variant_builder_add(setmulti_builder, "{sv}", (const gchar *)property_p->name, g_variant_ref((GVariant *)dbus_g_variant_test_and_return_new(property_p, 0x01)));
        }

        /*setmulti_value = g_variant_new ("@a{sv}", g_variant_builder_end (setmulti_builder));
           //setmulti_value = g_variant_new ("a{sv}", g_variant_builder_end (setmulti_builder));
           //setmulti_value = g_variant_new ("(@a{sv})", g_variant_builder_end (setmulti_builder));
           //setmulti_value = g_variant_new ("(a{sv})", g_variant_builder_end (setmulti_builder));
           g_variant_builder_unref (setmulti_builder);//delete when stack object
           //setmulti_value = g_variant_new ("a{sv}", g_variant_builder_end (&setmulti_builder));
           //Bus error .... in Tongwei.*/


        setmulti_value = g_variant_builder_end(setmulti_builder);

        //setmulti_value = g_variant_new ("@a{sv}", &setmulti_builder);
        //setmulti_value = g_variant_new ("a{sv}", setmulti_builder);


        strcpy(p_in, ")");
        p_in += 1;
        strcpy(p_out, ")");
        p_out += 1;
        *p_in  = '\0';
        *p_out = '\0';

        method_input_param = g_variant_new("(s@a{sv})", (const gchar *)dbus_interface_p->name, setmulti_value);


#if 1
        bus = g_bus_get_sync(G_BUS_TYPE_SYSTEM, NULL, &error);
        //g_assert_no_error(error);
        if (error)
        {
            GString *gstring;
            gstring = g_string_new(" ");
            g_string_append_printf(gstring, "%s", error->message);
            dbus_printf("%s line%d\n", gstring->str, __LINE__);
            g_string_free(gstring, TRUE);
            g_error_free(error);
            error = NULL;
        }
        if (lib_debug)
        {
            dbus_printf(" Into g_dbus_proxy_new_sync line %d \n", __LINE__);
        }
        remote_object = g_dbus_proxy_new_sync(bus,
                                              G_DBUS_PROXY_FLAGS_NONE,
                                              NULL,
                                              "com.ctc.igd1",
                                              dbus_object_list->name,
                                              "com.ctc.igd1.Properties",//"org.freedesktop.dbus.peer",
                                              NULL,
                                              &error);

        if (lib_debug)
        {
            dbus_printf(" Out g_dbus_proxy_new_sync line %d \n", __LINE__);
        }
        if (error)
        {
            GString *gstring;
            gstring = g_string_new(" ");
            g_string_append_printf(gstring, "%s", error->message);
            dbus_printf("%s line%d\n", gstring->str, __LINE__);
            g_string_free(gstring, TRUE);
            g_error_free(error);
            error = NULL;
        }
        gettimeofday(&start, NULL);


        if (method_input_param != NULL)
        {
            dbus_printf("method_input_param %s\n", g_variant_print(method_input_param, true));
            dbus_printf("method_input_param....type %s\n", g_variant_get_type_string(method_input_param));
        }
        else
        {
            dbus_printf("method_input_param is NULL. exit.\n");
            exit(0);
        }
        if (lib_debug)
        {
            dbus_printf(" Into g_dbus_proxy_call_sync line %d \n", __LINE__);
        }
        Method_Out = g_dbus_proxy_call_sync(remote_object,
                                            "SetMulti",
                                            method_input_param,
                                            G_DBUS_CALL_FLAGS_NONE,
                                            600000,//-1,
                                            NULL,
                                            &error);
        gettimeofday(&end, NULL);
        if (lib_debug)
        {
            dbus_printf(" Out g_dbus_proxy_call_sync line %d \n", __LINE__);
        }

        if (error)
        {
            GString *gstring;
            gstring = g_string_new(" ");
            g_string_append_printf(gstring, "%s", error->message);
            dbus_printf("%s\n", gstring->str);

            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", "SetMulti ", "", "", "Failed", "Error when execve method", __func__, gstring->str);
            dbus_object_list->test_result    |= PROPERTY_CANT_SET_OR_SETMULTI;
            dbus_interface_list->test_result |= PROPERTY_CANT_SET_OR_SETMULTI;
            g_string_free(gstring, TRUE);
            g_error_free(error);
            error = NULL;
            goto error;
        }
        else
        {
            dbus_object_list->test_result    &= (~UNPASS);
            dbus_interface_list->test_result &= (~UNPASS);
        }
#endif

        //dbus_printf("%s, performace  is %s ,the perform time is %d us\n",
        //    dbus_object_list->name,(elapsed_time > 200000)?"failed":"ok",elapsed_time);

        g_variant_unref(Method_Out);
        elapsed_time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
        if (strcmp(dbus_interface_list->name, "com.ctc.igd1.SysCmd") != 0)
        {
            //if(strcmp(dbus_method_list->name,"SetDateTime")!=0)
            //liuxy 0829-001 begin: Do not output "Failed" when SetMulti for "com.ctc.igd1.WLANConfiguration" interface.
            if(strcmp(dbus_interface_list->name, "com.ctc.igd1.WLANConfiguration") == 0)
            {
                dbus_printf_twice("%s,%s,%s,%s,%s,%d(us),%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, "", "SetMulti", "", elapsed_time, "OK", (elapsed_time > 200000) ? "Time out" : "Not time out", __func__, "Do not output \"Time out\" when SetMulti for \"com.ctc.igd1.WLANConfiguration\" interface.");
            }
            else
            //liuxy 0829-001 end
                dbus_printf_twice("%s,%s,%s,%s,%s,%d(us),%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, "", "SetMulti", "", elapsed_time, (elapsed_time > 200000) ? "Failed" : "OK", (elapsed_time > 200000) ? "Time out" : "Not time out", __func__, "");
        }
        if (elapsed_time > 200000)
        {
            dbus_object_list->test_result    |= PROPERTY_SETMUL_GETALL_TIMEOUT;
            dbus_interface_list->test_result |= PROPERTY_SETMUL_GETALL_TIMEOUT;
        }

error:
        g_object_unref(G_OBJECT(remote_object));
        g_object_unref(bus);

        if (g_strcmp0(dbus_interface_p->name, "com.ctc.igd1.HTTPServer") == 0)
        {
            list_for_each(property_list_item_p, &dbus_interface_p->property_list)
            {
                property_p = node_to_item(property_list_item_p, struct dbus_property, list);

                if (g_strcmp0(property_p->name, "AdminPassword") == 0)
                {
                    dbus_printf("   ###back AdminPassword to base After SetMulti com.ctc.igd1.HTTPServer! Please make sure test_value2 is default passwd\n");
                    bool current_log = true;
                    current_log = open_log;
                    open_log = false;
                    bool current_check_notification = true;
                    current_check_notification = check_notification;
                    check_notification = false;
                    dbus_printf("%s. Close the log and notification_check for adjust device.\n",__func__);
                    igd1_Set_Checksignal_CheckGet(dbus_object_list, dbus_interface_list, property_p, 2);
                    dbus_printf("%s. After adjust device reset the log and notification_check tag.\n",__func__);
                    check_notification = current_check_notification;
                    open_log = current_log;
                    property_p->case_property_set_value = 2;
                }
            }
        }
    }


#if 0
    g_variant_unref(values);

    g_object_unref(connection);
#endif


    return(0);
} /* igd1_SetMulti */

