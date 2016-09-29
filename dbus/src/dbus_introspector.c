/************************************************
*  Dbus test suite
*  Author: Thundersoft
*  2016, all rights reserved.
************************************************/

#include "dbus_log.h"
#include <dbus/dbus.h>
#include "dbus_xml_parse.h"
#include <gio/gio.h>

guchar property_acc[3][11] = { "read", "write", "readwrite" };
bool   print_introspect = false;
extern const char* igd1_interface;
extern const char* igd1_service;
extern const char* freedesktop_service;

size_t delim(char d, char *whole_str, char *output_str)
{
    size_t len = strlen(whole_str);
    char   *p  = whole_str;
    char   *q  = output_str;
    int    u   = 0;

    for (u = 0; u < len; u++)
    {
        if (*p == d)
        {
            *q = '\0';
            return(u + 1);
        }
        else
        {
            (*q) = (*p);
            q++;
            p++;
        }
    }
    *q = '\0';
    return(u + 1);
}


guchar propertyaccesstoflags(guchar *str)
{
    if (g_strcmp0(str, &property_acc[0][0]) == 0)
    {
        return(1);
    }
    else if (g_strcmp0(str, &property_acc[2][0]) == 0)
    {
        return(3);
    }
    else if (g_strcmp0(str, &property_acc[1][0]) == 0)
    {
        return(2);
    }
}

int remote_object_introspectable(struct dbus_object *dbus_object_list);
int introspect_data_compare(struct dbus_object *dbus_object_list, gchar *compare_data, bool trace);


int introspect_data_compare(struct dbus_object *dbus_object_list, gchar *compare_data, bool trace)
{
    GDBusNodeInfo        *node_info;
    GDBusInterfaceInfo   *interface_info;
    GDBusPropertyInfo    *property_info;
    GDBusMethodInfo      *method_info;
    GDBusSignalInfo      *signal_info;

    struct listnode      *interface_list_item_p;
    struct listnode      *method_list_item_p;
    struct listnode      *signal_list_item_p;
    struct listnode      *property_list_item_p;
    struct listnode      *arg_list_item_p;
    struct dbus_property *property_p = NULL;
    struct dbus_signal   *signal_p   = NULL;
    struct dbus_method   *method_p   = NULL;
    GError               *error      = NULL;

    if (compare_data)
    {
        node_info = g_dbus_node_info_new_for_xml(compare_data, &error);
        if (node_info)
        {
            list_for_each(interface_list_item_p, &dbus_object_list->interface_list)
            {
                struct dbus_interface *dbus_interface_p = node_to_item(interface_list_item_p,
                                                                       struct dbus_interface, list);

                interface_info = g_dbus_node_info_lookup_interface(node_info, dbus_interface_p->name);
                if (interface_info)
                {
                    if (trace)
                    {
                        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, "", "", "", "", "OK", "Find interface", __func__, dbus_interface_p->name);
                    }
                    dbus_object_list->test_result &= (~UNPASS);
                    dbus_interface_p->test_result &= (~UNPASS);

                    dbus_interface_p->introspect_has_interface = true;
                    /*property***********************************************************/
                    list_for_each(property_list_item_p, &dbus_interface_p->property_list)
                    {
                        //struct dbus_property * property_p = node_to_item(property_list_item_p,
                        property_p = node_to_item(property_list_item_p,
                                                  struct dbus_property, list);

#if 0
                        char name_buf[50] = { 0 };
                        int  u            = 0;
                        char *t           = property_p->name;
                        int  check_len    = 0;
                        int  len          = 0;
                        int  name_len     = strlen(property_p->name);

                        while (check_len < name_len)
                        {
                            len        = delim('|', t, name_buf);
                            t         += len;
                            check_len += len;
                            //dbus_printf("#%s, retlen=%d, check_len=%d, name_len=%d, goto %s\n\n",name_buf,len,check_len,name_len,t);
                            if (len > 1)
                            {
                                property_info = g_dbus_interface_info_lookup_property(interface_info, name_buf);
                                if (property_info)
                                {
                                    //strcpy(property_p->name,name_buf);
                                    goto go_on_check_property;
                                }
                            }
                            for (u = 0; u < 50; u++)
                            {
                                name_buf[u] = '\0';
                            }
                        }
#else
                        property_info = g_dbus_interface_info_lookup_property(interface_info, property_p->name);
#endif
go_on_check_property:
                        if (property_info)
                        {
                            //dbus_printf("@@ %s %s %d \n",property_info->name,property_info->signature,property_info->flags);
                            if (g_strcmp0(property_info->signature, property_p->type) == 0)
                            {
                                guchar flags = propertyaccesstoflags(property_p->access);
                                if (flags != property_info->flags)
                                {
                                    if (trace)
                                    {
                                        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "", "", "", "Failed", "Wrong access type", __func__, &flags, &property_info->flags);
                                    }
                                    dbus_object_list->test_result |= PROPERTY_WRONG_ACCESS;
                                    property_p->test_result       |= PROPERTY_WRONG_ACCESS;
                                }
                                else
                                {
                                    //dbus_printf("The property is ok\n");
                                    if (trace)
                                    {
                                        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "", "", "", "OK", "Have the property", __func__, property_p->name);
                                    }
                                    property_p->introspect_has_property = true;
                                    dbus_object_list->test_result      &= (~UNPASS);
                                    dbus_interface_p->test_result      &= (~UNPASS);
                                    property_p->test_result            &= (~UNPASS);
                                }
                            }
                            else
                            {
                                //dbus_printf("Failed,The property [%s] type  is wrong %s (stand %s ) in [%s]@[%s] \n",property_p->name, property_info->signature, property_p->type, dbus_object_list->name, dbus_interface_p->name);
                                if (trace)
                                {
                                    dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "", "", "", "Failed", "Wrong type", __func__, property_p->type, property_info->signature);
                                }
                                dbus_object_list->test_result |= PROPERTY_WRONG_TYPE;
                                property_p->test_result       |= PROPERTY_WRONG_TYPE;
                            }
                        }
                        else
                        {
                            //dbus_printf("Failed,There is no property [%s] in [%s]@[%s]\n",property_p->name,dbus_object_list->name, dbus_interface_p->name);
                            if (trace)
                            {
                                dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "", "", "", "Failed", "No property", __func__, property_p->name);
                            }
                            property_p->introspect_has_property = false;
                            dbus_object_list->test_result      |= NO_PROPERTY;
                            property_p->test_result            |= NO_PROPERTY;
                        }
                    }
                    /**************************************************************************************/
                    gchar    k               = 0;
                    gboolean property_status = 0;
                    for (k = 0; interface_info->properties != NULL && interface_info->properties[k] != NULL; k++)
                    {
                        property_info = interface_info->properties[k];
                        list_for_each(property_list_item_p, &dbus_interface_p->property_list)
                        {
                            //struct dbus_property * property_p = node_to_item(property_list_item_p,
                            property_p = node_to_item(property_list_item_p,
                                                      struct dbus_property, list);
                            if (g_strcmp0(property_info->name, property_p->name) != 0)
                            {
                                property_status = 1;
                                continue;
                            }
                            else
                            {
                                property_status = 0;
                                break;
                            }
                        }
                        if (property_status)
                        {
                            //dbus_printf("Failed, [%s]@[%s] add the NEW property %s \n", dbus_object_list->name, dbus_interface_p->name, property_info->name);
                            if (trace)
                            {
                                dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, property_info->name, "", "", "", "Failed", "New property", __func__, property_info->name);
                            }
                            dbus_object_list->test_result |= NEW_PROPERTY;
                            property_p->test_result       |= NEW_PROPERTY;
                        }
                        /*else
                                dbus_printf("@@ %s ok\n",property_info->name);*/
                    }
                    /**************************************************************************************/
                    /*method++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
                    list_for_each(method_list_item_p, &dbus_interface_p->method_list)
                    {
                        //struct dbus_method* method_p = node_to_item(method_list_item_p,
                        method_p = node_to_item(method_list_item_p,
                                                struct dbus_method, list);

                        method_info = g_dbus_interface_info_lookup_method(interface_info, method_p->name);

                        if (method_info)
                        {
                            if (method_info->in_args == NULL && method_info->out_args == NULL && (list_empty(&method_p->arg_list)))
                            {
                                //dbus_printf("OK the method %s has no arg\n",method_p->name);
                                if (trace)
                                {
                                    dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, "", method_info->name, "", "", "Failed", "No arg", __func__, "No ANY arg.");
                                }
                                dbus_object_list->test_result |= NO_METHOD_ARG;
                                method_p->test_result         |= NO_METHOD_ARG;
                                continue;
                            }

                            unsigned short arg_status    = 0;
                            unsigned short method_status = 0;
                            list_for_each(arg_list_item_p, &method_p->arg_list)
                            {
                                struct dbus_method_arg *arg_item_p = node_to_item(arg_list_item_p,
                                                                                  struct dbus_method_arg, list);
                                gchar                  n = 0;
                                gchar                  m = 0;

                                dbus_object_list->test_result &= (~UNPASS);
                                dbus_interface_p->test_result &= (~UNPASS);
                                method_p->test_result         &= (~UNPASS);
                                arg_item_p->test_result       &= (~UNPASS);
                                for (n = 0; method_info->in_args != NULL && method_info->in_args[n] != NULL; n++)
                                {
#if 1                               //Check the in arg with '|'
                                    {
                                        char name_buf[50] = { 0 };
                                        int  u            = 0;
                                        char *t           = arg_item_p->name;
                                        int  check_len    = 0;
                                        int  len          = 0;
                                        int  name_len     = strlen(arg_item_p->name);
                                        while (check_len < name_len)
                                        {
                                            len        = delim('|', t, name_buf);
                                            t         += len;
                                            check_len += len;
                                            if (len > 1)
                                            {
                                                //dbus_printf("%s, %s, %s\n",__func__,method_info->in_args[m]->name, name_buf);
                                                if ((g_strcmp0(method_info->in_args[n]->name, name_buf) == 0) && (g_strcmp0(arg_item_p->name, name_buf) != 0))
                                                {
                                                    //dbus_printf("arg update[%s]to[%s] in method %s [%s]@[%s]\n", arg_item_p->name,name_buf, method_p->name,dbus_object_list->name, dbus_interface_p->name);
                                                    strcpy(arg_item_p->name, name_buf);            //Update the arg!!!!!!!!!!!!!!!!!!!! xml_data
                                                    goto go_on_check_method_in_arg;
                                                }
                                            }
                                            for (u = 0; u < 50; u++)
                                            {
                                                name_buf[u] = '\0';
                                            }
                                        }
                                    }
go_on_check_method_in_arg:
#endif


                                    //dbus_printf("@@ %s %s \n",method_info->in_args[n]->name,arg_item_p->name);
                                    if (g_strcmp0(arg_item_p->name, method_info->in_args[n]->name) == 0)
                                    {
                                        arg_status = 0;
                                        if (g_strcmp0(arg_item_p->type, method_info->in_args[n]->signature) == 0)
                                        {
                                            if (g_strcmp0(arg_item_p->direction, "in") != 0)
                                            {
                                                //dbus_printf("Failed The method [%s], [%s]@[%s],the arg %s direction is wrong %s (stand %s)\n",method_p->name, dbus_object_list->name, dbus_interface_p->name,arg_item_p->name,"out", arg_item_p->direction);
                                                if (trace)
                                                {
                                                    dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, "", method_p->name, "", "", "Failed", "Direction Not in", __func__, arg_item_p->name);
                                                }
                                                dbus_object_list->test_result |= NO_METHOD_ARG;
                                                arg_item_p->test_result       |= NO_METHOD_ARG;
                                                method_status                  = 1;
                                                goto METHOD_ARG;
                                            }
                                            else
                                            {
                                                //dbus_printf("The arg %s in method %s is ok\n",arg_item_p->name,method_p->name);
                                                if (trace)
                                                {
                                                    dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, "", method_p->name, "", "", "OK", "Have the arg", __func__, arg_item_p->name);
                                                }

                                                /*dbus_object_list->test_result &=(~UNPASS);
                                                   dbus_interface_p->test_result &=(~UNPASS);
                                                   method_p->test_result &=(~UNPASS);
                                                   arg_item_p->test_result &=(~UNPASS);*/
                                                //break;
                                                goto METHOD_ARG;
                                            }
                                        }
                                        else
                                        {
                                            //dbus_printf("Failed The method [%s], [%s]@[%s],the arg %s type is wrong %s (stand %s)\n",method_p->name, dbus_object_list->name, dbus_interface_p->name,arg_item_p->name,method_info->in_args[n]->signature, arg_item_p->type);
                                            if (trace)
                                            {
                                                dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, "", method_p->name, "", "", "Failed", "Wrong arg type", __func__, arg_item_p->type, method_info->in_args[n]->signature);
                                            }
                                            dbus_object_list->test_result |= NO_METHOD_ARG;
                                            arg_item_p->test_result       |= NO_METHOD_ARG;
                                            method_status                  = 2;
                                            goto METHOD_ARG;
                                        }
                                    }
                                    else
                                    {
                                        arg_status    = 1;
                                        method_status = 3;
                                    }
                                }
                                for (m = 0; method_info->out_args != NULL && method_info->out_args[m] != NULL; m++)
                                {
#if 1                               //Check the out arg with '|'
                                    {
                                        char name_buf[50] = { 0 };
                                        int  u            = 0;
                                        char *t           = arg_item_p->name;
                                        int  check_len    = 0;
                                        int  len          = 0;
                                        int  name_len     = strlen(arg_item_p->name);
                                        while (check_len < name_len)
                                        {
                                            len        = delim('|', t, name_buf);
                                            t         += len;
                                            check_len += len;
                                            if (len > 1)
                                            {
                                                //dbus_printf("%s, %s, %s\n",__func__,method_info->out_args[m]->name, name_buf);
                                                if ((g_strcmp0(method_info->out_args[m]->name, name_buf) == 0) && (g_strcmp0(arg_item_p->name, name_buf) != 0))
                                                {
                                                    //dbus_printf("arg update[%s]to[%s] in method %s [%s]@[%s]\n", arg_item_p->name,name_buf, method_p->name,dbus_object_list->name, dbus_interface_p->name);
                                                    strcpy(arg_item_p->name, name_buf);            //Update the arg!!!!!!!!!!!!!!!!!!!! xml_data
                                                    goto go_on_check_method_out_arg;
                                                }
                                            }
                                            for (u = 0; u < 50; u++)
                                            {
                                                name_buf[u] = '\0';
                                            }
                                        }
                                    }
go_on_check_method_out_arg:
#endif


                                    //dbus_printf("@@ %s %s \n",method_info->out_args[m]->name,arg_item_p->name);
                                    if (g_strcmp0(arg_item_p->name, method_info->out_args[m]->name) == 0)
                                    {
                                        arg_status = 0;
                                        if (g_strcmp0(arg_item_p->type, method_info->out_args[m]->signature) == 0)
                                        {
                                            if (g_strcmp0(arg_item_p->direction, "out") != 0)
                                            {
                                                //dbus_printf("Failed The method [%s], [%s]@[%s],the arg %s direction is wrong %s (stand %s)\n",method_p->name, dbus_object_list->name, dbus_interface_p->name,arg_item_p->name,"in", arg_item_p->direction);
                                                if (trace)
                                                {
                                                    dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, "", method_p->name, "", "", "Failed", "Direction Not out", __func__, arg_item_p->name);
                                                }
                                                dbus_object_list->test_result |= NO_METHOD_ARG;
                                                arg_item_p->test_result       |= NO_METHOD_ARG;
                                                method_status                  = 4;
                                                goto METHOD_ARG;
                                            }
                                            else
                                            {
                                                //dbus_printf("The arg %s in method %s is ok\n",arg_item_p->name,method_p->name);
//												if(trace)dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_p->name,"", method_p->name,"","","OK","",__func__,"arg ok");
                                                goto METHOD_ARG;
                                            }
                                        }
                                        else
                                        {
                                            //dbus_printf("Failed The method [%s], [%s]@[%s],the arg [%s] tyep is wrong %s (stand %s)\n",method_p->name, dbus_object_list->name, dbus_interface_p->name,arg_item_p->name,method_info->out_args[m]->signature, arg_item_p->type);
                                            if (trace)
                                            {
                                                dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, "", method_p->name, "", "", "Failed", "Wrong arg type", __func__, arg_item_p->type, method_info->out_args[m]->signature);
                                            }
                                            dbus_object_list->test_result |= NO_METHOD_ARG;
                                            arg_item_p->test_result       |= NO_METHOD_ARG;
                                            method_status                  = 5;
                                            goto METHOD_ARG;
                                        }
                                    }
                                    else
                                    {
                                        arg_status    = 2;
                                        method_status = 6;
                                    }
                                }
                                if (arg_status == 1)
                                {
                                    //dbus_printf("Failed There is no arg [%s] in method %s [%s]@[%s]\n", arg_item_p->name,method_p->name,dbus_object_list->name, dbus_interface_p->name);
                                    if (trace)
                                    {
                                        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, "", method_p->name, "", "", "Failed", "No in arg", __func__, arg_item_p->name);
                                    }
                                    dbus_object_list->test_result |= NO_METHOD_ARG;
                                    arg_item_p->test_result       |= NO_METHOD_ARG;
                                }
                                if (arg_status == 2)
                                {
                                    //dbus_printf("Failed There is no arg [%s] in method %s [%s]@[%s]\n", arg_item_p->name,method_p->name,dbus_object_list->name, dbus_interface_p->name);
                                    if (trace)
                                    {
                                        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, "", method_p->name, "", "", "Failed", "No out arg", __func__, arg_item_p->name);
                                    }
                                    dbus_object_list->test_result |= NO_METHOD_ARG;
                                    arg_item_p->test_result       |= NO_METHOD_ARG;
                                }
METHOD_ARG:
                                continue;
                            }

                            if (method_status == 0)
                            {
                                if (trace)
                                {
                                    dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, "", method_p->name, "", "", "OK", "Have the Method", __func__, "");
                                }
                                dbus_object_list->test_result &= (~UNPASS);
                                method_p->test_result         &= (~UNPASS);
                            }
                            //else
                            //	dbus_printf("Error %s  %s......0x%x\n",dbus_object_list->name, method_p->name, method_status);
                        }
                        else
                        {
                            //dbus_printf("Failed,There is no method [%s] in [%s]@[%s]\n",method_p->name, dbus_object_list->name, dbus_interface_p->name);
                            if (trace)
                            {
                                dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, "", method_p->name, "", "", "Failed", "No method", __func__, method_p->name);
                            }
                            dbus_object_list->test_result  |= NO_METHOD;
                            method_p->test_result          |= NO_METHOD;
                            method_p->introspect_has_method = false;
                        }
                    }
                    /*******************************************************************************************************/
                    gboolean method_status = 0;
                    for (k = 0; interface_info->methods != NULL && interface_info->methods[k] != NULL; k++)
                    {
                        method_info = interface_info->methods[k];
                        list_for_each(method_list_item_p, &dbus_interface_p->method_list)
                        {
                            //struct dbus_method* method_p = node_to_item(method_list_item_p,
                            method_p = node_to_item(method_list_item_p,
                                                    struct dbus_method, list);
                            if (g_strcmp0(method_info->name, method_p->name) != 0)
                            {
                                method_status = 1;
                            }
                            else
                            {
                                method_status = 0;
                                break;
                            }
                        }
                        if (method_status)
                        {
                            //dbus_printf("Failed, [%s]@[%s] add the NEW method %s \n",dbus_object_list->name, dbus_interface_p->name, method_info->name);
                            if (!((strcmp(dbus_object_list->name, "/com/ctc/igd1/Storage/usb/devices") == 0) ||
                                  (strcmp(dbus_object_list->name, "/com/ctc/igd1/Config/WLAN/Devices") == 0) ||
                                  (strcmp(dbus_object_list->name, "/com/ctc/igd1/Info/Network/WANConnectionDb/{i}") == 0) ||
                                  (strcmp(dbus_object_list->name, "/com/ctc/igd1/Info/Network/WANConnectionDb") == 0) ||
                                  (strcmp(dbus_object_list->name, "/com/ctc/igd1/Config/IncomingFilter") == 0) ||
                                  (strcmp(dbus_object_list->name, "/com/ctc/igd1/Config/LANHosts") == 0) ||
                                  //liuxy 0906-001 begin : ignore AddObject / DeleteObject check for /com/ctc/igd1/Network/Telnetserver/Accounts
                                  (strcmp(dbus_object_list->name, "/com/ctc/igd1/Network/Telnetserver/Accounts") == 0)))
                            {
                                if (trace)
                                {
                                    dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, "", method_info->name, "", "", "Failed", "New method", __func__, method_info->name);
                                }

                                dbus_object_list->test_result |= NEW_METHOD;
                                method_p->test_result         |= NEW_METHOD;
                            }
                        }
                        /*else
                                dbus_printf("@@ %s ok\n",method_info->name);*/
                    }
                    /*******************************************************************************************************/
                    /*method*/
                    /*signal**************************************************************************************************/
                    list_for_each(signal_list_item_p, &dbus_interface_p->signal_list)
                    {
                        //struct dbus_signal *signal_p =node_to_item(signal_list_item_p,
                        signal_p = node_to_item(signal_list_item_p,
                                                struct dbus_signal, list);
                        signal_info = g_dbus_interface_info_lookup_signal(interface_info, signal_p->name);
                        if (signal_info)
                        {
                            int signal_arg_status = 0;
                            list_for_each(arg_list_item_p, &signal_p->arg_list)
                            {
                                struct dbus_signal_arg *arg_item_p = node_to_item(arg_list_item_p,
                                                                                  struct dbus_signal_arg, list);

                                for (k = 0; signal_info->args != NULL && signal_info->args[k] != NULL; k++)
                                {
                                    if (g_strcmp0(arg_item_p->name, signal_info->args[k]->name) == 0)
                                    {
                                        if (g_strcmp0(arg_item_p->type, signal_info->args[k]->signature) != 0)
                                        {
                                            //dbus_printf("Failed the type %s (stand %s) is error in signal %s\n",signal_info->args[k]->signature, arg_item_p->type, arg_item_p->name);
                                            if (trace)
                                            {
                                                dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, "", "", signal_info->name, "", "Failed", "Wrong signal arg type", __func__, arg_item_p->type, signal_info->args[k]->signature);
                                            }
                                            signal_arg_status              = 1;
                                            dbus_object_list->test_result |= NO_SIGNAL_ARG;
                                            signal_p->test_result         |= NO_SIGNAL_ARG;
                                        }
                                        else
                                        {
                                            dbus_object_list->test_result &= (~UNPASS);
                                            dbus_interface_p->test_result &= (~UNPASS);
                                            signal_p->test_result         &= (~UNPASS);
                                            arg_item_p->test_result       &= (~UNPASS);
                                        }
                                    }
                                    /*else
                                            //dbus_printf("Failed.There is no arg %s in signal[%s], [%s]@[%s] \n", arg_item_p->name,signal_info->name,dbus_object_list->name,dbus_interface_p->name);
                                            if(trace)dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_p->name,"","",signal_info->name,"","Failed","No signal arg",__func__,arg_item_p->name);*/
                                }
                            }
                            if (signal_arg_status == 0)
                            {
                                if (trace)
                                {
                                    dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, "", "", signal_info->name, "", "OK", "Have the signal", __func__, signal_info->name);
                                }

                                dbus_object_list->test_result &= (~UNPASS);
                                dbus_interface_p->test_result &= (~UNPASS);
                                signal_p->test_result         &= (~UNPASS);
                            }
                        }
                        else
                        {
                            //dbus_printf("Failed.There is no signal [%s] in [%s]@[%s]\n",signal_p->name,dbus_object_list->name,dbus_interface_p->name);
                            if (trace)
                            {
                                dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, "", "", signal_p->name, "", "Failed", "NO signal", __func__, signal_p->name);
                            }
                            dbus_object_list->test_result |= NO_SIGNAL;
                            signal_p->test_result         |= NO_SIGNAL;
                        }
                    }
                    /********************************************************************************************************/
                    gboolean signal_status = 0;
                    for (k = 0; interface_info->signals != NULL && interface_info->signals[k] != NULL; k++)
                    {
                        signal_info = interface_info->signals[k];
                        list_for_each(signal_list_item_p, &dbus_interface_p->signal_list)
                        {
                            //struct dbus_signal *signal_p =node_to_item(signal_list_item_p,
                            signal_p = node_to_item(signal_list_item_p,
                                                    struct dbus_signal, list);
                            if (g_strcmp0(signal_info->name, signal_p->name) != 0)
                            {
                                signal_status = 1;
                            }
                            else
                            {
                                signal_status = 0;
                                break;
                            }
                        }
                        if (signal_status)
                        {
                            //dbus_printf("Failed the interface add the signal %s in interface %s\n",signal_info->name,dbus_interface_p->name);
                            if (trace)
                            {
                                dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, "", "", signal_info->name, "", "Failed", "New signal", __func__, signal_info->name);
                            }
                            dbus_object_list->test_result |= NEW_METHOD_ARG;
                            signal_p->test_result         |= NEW_METHOD_ARG;
                        }
                        /*else
                                dbus_printf("@@ %s ok\n",method_info->name);*/
                    }
                    /*signal end***********************************************************************************************/
                }
                else
                {
                    //dbus_printf("Failed There is no %s in %s\n",dbus_interface_p->name,dbus_object_list->name);
                    if (trace)
                    {
                        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, "", "", "", "", "Failed", "No interface", __func__, dbus_interface_p->name);
                    }
                    dbus_interface_p->introspect_has_interface = false;
                    dbus_object_list->test_result             |= NO_INTERFACE;
                    dbus_interface_p->test_result             |= NO_INTERFACE;
                }
            }
        }
    }
    return(0);
} /* introspect_data_compare */


int remote_object_introspectable_check(
    /* struct dbus_interface *dbus_interface_list ,*/
    struct dbus_object *dbus_object_list, bool trace)
{
    GDBusConnection *bus;
    GDBusProxy      *RemoteObjectIntrospectable;
    GError          *error = NULL;
    GVariant        *introspect_data;
    gchar           *xml_data;
    //GMainLoop * g_main_loop;
    gint            ret = 0;
    struct timeval  start;
    struct timeval  end;
    guint           elapsed_time = 0;


    bus = g_bus_get_sync(G_BUS_TYPE_SYSTEM, NULL, &error);      //G_BUS_TYPE_SYSTEM //G_BUS_TYPE_SESSION
    g_assert_no_error(error);

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
    char* service_name = igd1_service;
    if(dbus_object_list->name != NULL)
        if(strcmp(dbus_object_list->name,"/com/ctc/saf1") == 0)
            service_name = freedesktop_service;
    RemoteObjectIntrospectable = g_dbus_proxy_new_sync(bus,
                                                       G_DBUS_PROXY_FLAGS_NONE,
                                                       NULL,
                                                       service_name,
                                                       dbus_object_list->name,
                                                       "org.freedesktop.DBus.Introspectable",
                                                       NULL,
                                                       &error);

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

    gettimeofday(&start, NULL);
    introspect_data = g_dbus_proxy_call_sync(RemoteObjectIntrospectable,
                                             "Introspect",
                                             NULL,
                                             G_DBUS_CALL_FLAGS_NONE,
                                             -1,
                                             NULL,
                                             &error);

    gettimeofday(&end, NULL);

    //g_assert_no_error(error);

    //g_assert(introspect_data != NULL);


    elapsed_time = (end.tv_sec - start.tv_sec) * 1000000 +
                   (end.tv_usec - start.tv_usec);

    //dbus_printf("%s, performace  is %s ,the perform time is %d us\n",
    //    dbus_object_list->name,(elapsed_time > 200000)?"FAILED":"OK",elapsed_time);
    if (trace)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%d(us),%s,%s,%s,%s\n", dbus_object_list->name, "", "", "", "", elapsed_time, (elapsed_time > 200000) ? "Failed" : "OK", (elapsed_time > 200000) ? "Time out" : "Not time out", "remote_object_introspectable_check", "introspect data");
    }
    if (elapsed_time > 200000)
    {
        dbus_object_list->test_result |= METHOD_CALL_TIMEOUT;
    }
    g_variant_get(introspect_data, "(s)", &xml_data);

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
    if (print_introspect)
    {
        dbus_printf("introspect_data: %s\n", xml_data);
    }

    introspect_data_compare(dbus_object_list, xml_data, trace);


    //g_main_loop = g_main_loop_new(NULL, FALSE);
    //g_main_loop_run(g_main_loop);

    g_variant_unref(introspect_data);
    g_object_unref(G_OBJECT(RemoteObjectIntrospectable));
    g_object_unref(bus);

    return(ret);
} /* remote_object_introspectable_check */


int remote_object_introspectable(struct dbus_object *dbus_object_list)
{
    GDBusConnection *bus;
    GDBusProxy      *RemoteObjectIntrospectable;
    GError          *error = NULL;
    GVariant        *introspect_data;
    gchar           *xml_data;
    //GMainLoop * g_main_loop;
    gint            ret = 0;
    struct timeval  start;
    struct timeval  end;
    guint           elapsed_time = 0;


    bus = g_bus_get_sync(G_BUS_TYPE_SYSTEM, NULL, &error);      //G_BUS_TYPE_SYSTEM //G_BUS_TYPE_SESSION
    g_assert_no_error(error);

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

    char* service_name = igd1_service;
    if(dbus_object_list->name != NULL)
        if(strcmp(dbus_object_list->name,"/com/ctc/saf1") == 0)
            service_name = freedesktop_service;
    RemoteObjectIntrospectable = g_dbus_proxy_new_sync(bus,
                                                       G_DBUS_PROXY_FLAGS_NONE,
                                                       NULL,
                                                       service_name,
                                                       dbus_object_list->name,
                                                       "org.freedesktop.DBus.Introspectable",
                                                       NULL,
                                                       &error);

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
    gettimeofday(&start, NULL);
    introspect_data = g_dbus_proxy_call_sync(RemoteObjectIntrospectable,
                                             "Introspect",
                                             NULL,
                                             G_DBUS_CALL_FLAGS_NONE,
                                             -1,
                                             NULL,
                                             &error);

    gettimeofday(&end, NULL);

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
    //g_assert(introspect_data != NULL);

    elapsed_time = (end.tv_sec - start.tv_sec) * 1000000 +
                   (end.tv_usec - start.tv_usec);

    //dbus_printf("%s, performace  is %s ,the perform time is %d us\n",
    //    dbus_object_list->name,(elapsed_time > 200000)?"FAILED":"OK",elapsed_time);

    dbus_printf_twice("%s,%s,%s,%s,%s,%d(us),%s,%s,%s,%s\n", dbus_object_list->name, "", "", "", "", elapsed_time, (elapsed_time > 200000) ? "Failed" : "OK", (elapsed_time > 200000) ? "Time out" : "", "remote_object_introspectable", "introspect data");
    if (elapsed_time > 200000)
    {
        dbus_object_list->test_result |= METHOD_CALL_TIMEOUT;
    }
    g_variant_get(introspect_data, "(s)", &xml_data);
    dbus_printf("introspect_data: %s\n", xml_data);
    g_variant_unref(introspect_data);
    g_object_unref(G_OBJECT(RemoteObjectIntrospectable));
    g_object_unref(bus);
} /* remote_object_introspectable */
