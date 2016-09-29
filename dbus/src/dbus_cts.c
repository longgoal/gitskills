/************************************************
*  Dbus test suite
*  Author: Thundersoft
*  2016, all rights reserved.
************************************************/

#include <dbus_cts.h>
#include <expat.h>
#include "list.h"
#include <dbus_xml_parse.h>
#include <gio/gio.h>
#include <glib/gmessages.h>
#include <stdio.h>
//#include<conio.h>
extern char        result_file[100];
char               *o_set    = NULL;
char               *i_set    = NULL;
char               *p_set    = NULL;
char               *m_set    = NULL;
char               version[] = "0912";
struct main_args   *main_args_p;
bool               param_need = false;
extern char        log_path[100];
extern char        *root_path;
extern bool        open_log;
extern bool        in_parallel_test;
bool               redundancy = true;
extern int         test_parallel_second;
extern bool        check_notification;
int                parallel_process_index  = 0;
bool               loop_test               = false;
bool               clean_bak               = true;
bool               open_tag_about_test_all = false;
bool               Introspect_step         = true;
bool               Set_step                = true;
bool               Get_step                = true;
bool               GetAll_step             = true;
bool               SetMulti_step           = true;
bool               Peer_step               = true;
bool               Method_step             = true;
bool               Add_Del_Obj_step             = true;
bool               Get_Check_step          = true;
bool               Get_Result_file         = true;
bool               Quick_Get               = false;
bool               Parallel_mode           = false;
bool               no_instance_scan        = false;
dbus_command_s     run_args                = DBUS_COMMAND_INVALID;
static dbus_bool_t sigint_received         = FALSE;
static char        **record_argv           = NULL;
extern char        xml_path[100];
extern char        noinstance_xml_path[100];
extern char        xml_case_path[100];
extern char        xml_case_bak_path[100];
bool               Close_Device            = true;
//liuxy 0906-003 : KickOutDevice_flag for do "KickOutDevice" in advance.
//                 do "KickOutDevice" after introspect and Wlan device sync and before close device.
//                 because we can not find a available device to kick out if we do "KickOutDevice" after close device or set propertis of "com.ctc.igd1.WLANConfiguration".
bool               KickOutDevice_flag      = false;
extern struct dbus_object *KickOutDevice_Lookup(void);
extern char        *LANHost_MAC;
extern char        *LANHost_Port;
extern gchar       LANHost_ConnectionType;

struct main_args *parse_args(int argc, char *argv[])
{
    main_args_p = (struct main_args *)malloc(sizeof(struct main_args));
    memset(main_args_p, sizeof(main_args_p), 0);
    if (argc == 1)
    {
        main_args_p->dbus_cmd = DBUS_CMD_ALL;
        return(main_args_p);
    }
    else if (argc == 2)
    {
        argv++;
        if (strcmp(*argv, "-h") == 0)
        {
            main_args_p->dbus_cmd = DBUS_CMD_HELP;
            return(main_args_p);
        }
        if (strcmp(*argv, "-nc") == 0)
        {
            clean_bak             = false;
            main_args_p->dbus_cmd = DBUS_CMD_ALL;
            return(main_args_p);
        }
        if ((strcmp(*argv, "-ncd") == 0) || (strcmp(*argv, "-no_close_device") == 0))
        {
            Close_Device             = false;
            main_args_p->dbus_cmd = DBUS_CMD_ALL;
            return(main_args_p);
        }
        if (strcmp(*argv, "-result") == 0)
        {
            Get_Result_file       = true;
            main_args_p->dbus_cmd = DBUS_CMD_ALL;
        }
        if ((strcmp(*argv, "-no_i_scan") == 0) || (strcmp(*argv, "-direct_copy") == 0) || (strcmp(*argv, "-dc") == 0))
        {
            no_instance_scan       = true;
            main_args_p->dbus_cmd = DBUS_CMD_ALL;
        }
        else if (strcmp(*argv, "-loop") == 0)
        {
            loop_test             = true;
            main_args_p->dbus_cmd = DBUS_CMD_ALL;
            return(main_args_p);
        }
        else if (strcmp(*argv, "-parallel") == 0)
        {
            main_args_p->dbus_cmd = DBUS_CMD_PARALLEL;
            Parallel_mode         = true;
            Get_Result_file       = false;
            return(main_args_p);
        }
        else if (strcmp(*argv, "-step") == 0)
        {
            main_args_p->dbus_cmd = DBUS_CMD_ALL_BY_STEP;
            return(main_args_p);
        }
        else if (strcmp(*argv, "-more") == 0)
        {
            main_args_p->dbus_cmd = DBUS_CMD_TEST_MORE_METHOD;
            return(main_args_p);
        }
        else if ((strcmp(*argv, "-quick_get") == 0) || (strcmp(*argv, "-q_g") == 0))
        {
            Quick_Get = true;
            main_args_p->dbus_cmd = DBUS_CMD_ALL;
        }
#if 0
        else if (strcmp(*argv, "-e") == 0)
        {
            main_args_p->dbus_cmd = DBUS_CMD_UPDATE_INSTANCE;
            return(main_args_p);
        }
#endif
        else if (strcmp(*argv, "-instance") == 0)
        {
            main_args_p->dbus_cmd = DBUS_COMMAND_INVALID;
            return(main_args_p);
        }
        else if (strcmp(*argv, "-v") == 0)
        {
            main_args_p->dbus_cmd = DBUS_CMD_VERSION;
            return(main_args_p);
        }
        else if (strcmp(*argv, "-print_introspect") == 0)
        {
            main_args_p->dbus_cmd = DBUS_CMD_ALL;
            print_introspect      = true;
            return(main_args_p);
        }
        else if ((strcmp(*argv, "-no_redundancy") == 0) || (strcmp(*argv, "-no_re") == 0))
        {
            redundancy            = false;
            main_args_p->dbus_cmd = DBUS_CMD_ALL;
            return(main_args_p);
        }
        else
        {
            main_args_p->dbus_cmd = DBUS_COMMAND_INVALID;
            dbus_printf("Error Command\n");
            return(main_args_p);
        }
    }
    //dbus_printf("%d\n" ,argc);
    argv += 1;
    while (*argv)
    {
        if (strcmp(*argv, "-o") == 0)
        {
            argv++;
            if (*argv)
            {
                main_args_p->object_path = argv;
                main_args_p->dbus_cmd    = DBUS_CMD_OBJECT;
                o_set                    = *argv;
            }
            else
            {
                main_args_p->dbus_cmd = DBUS_COMMAND_INVALID;
                dbus_printf("Error Command\n");
                return(main_args_p);
            }
        }
        else if (strcmp(*argv, "-i") == 0)
        {
            argv++;
            if (*argv)
            {
                main_args_p->dbus_interface = argv;
                main_args_p->dbus_cmd       = DBUS_CMD_INTERFACE;
                i_set                       = *argv;
            }
            else
            {
                dbus_printf("Error Command\n");
                main_args_p->dbus_cmd = DBUS_COMMAND_INVALID;
                return(main_args_p);
            }
        }
        else if (strcmp(*argv, "-p") == 0)
        {
            argv++;
            if (*argv)
            {
                main_args_p->dbus_property = argv;
                main_args_p->dbus_cmd      = DBUS_CMD_OBJECT;
                p_set                      = *argv;
            }
            else
            {
                main_args_p->dbus_cmd = DBUS_COMMAND_INVALID;
                dbus_printf("Error Command\n");
                return(main_args_p);
            }
        }
        else if (strcmp(*argv, "-loop") == 0)
        {
            loop_test             = true;
            main_args_p->dbus_cmd = DBUS_CMD_ALL;
        }
        else if (strcmp(*argv, "-Set") == 0)
        {
            //main_args_p->dbus_method = &"Set";
            main_args_p->dbus_cmd = DBUS_CMD_OBJECT;
            m_set                 = "Set";
        }
        else if (strcmp(*argv, "-Get") == 0)
        {
            //main_args_p->dbus_method = &"Get";
            main_args_p->dbus_cmd = DBUS_CMD_OBJECT;
            m_set                 = "Get";
        }
        else if (strcmp(*argv, "-m") == 0)
        {
            argv++;
            if (*argv)
            {
                main_args_p->dbus_method = argv;
                main_args_p->dbus_cmd    = DBUS_CMD_OBJECT;
                m_set                    = *argv;
            }
            else
            {
                main_args_p->dbus_cmd = DBUS_COMMAND_INVALID;
                dbus_printf("Error Command\n");
                return(main_args_p);
            }
        }
        else if (strcmp(*argv, "-s") == 0)
        {
            /*argv++;
               if(*argv && (main_args_p->dbus_cmd == DBUS_CMD_INTERFACE)){
                    main_args_p->dbus_cmd = DBUS_CMD_SIGNAL;
               }*/
            main_args_p->dbus_cmd = DBUS_CMD_SIGNAL;
        }
        else if (strcmp(*argv, "-h") == 0)
        {
            main_args_p->dbus_cmd = DBUS_CMD_HELP;
            return(main_args_p);
        }
        else if (strcmp(*argv, "-print_introspect") == 0)
        {
            argv++;
            print_introspect = true;
        }
        else if (strcmp(*argv, "-path") == 0)
        {
            argv++;
            if (!((main_args_p->dbus_cmd == DBUS_CMD_OBJECT) || (main_args_p->dbus_cmd == DBUS_CMD_SIGNAL)))
            {
                main_args_p->dbus_cmd = DBUS_CMD_ALL;
            }
            root_path = *argv;
        }
        else if (strcmp(*argv, "-instance") == 0)
        {
            main_args_p->dbus_cmd = DBUS_COMMAND_INVALID;
        }
        else if (strcmp(*argv, "-nc") == 0)
        {
            clean_bak             = false;
            main_args_p->dbus_cmd = DBUS_CMD_ALL;
        }
        if ((strcmp(*argv, "-ncd") == 0) || (strcmp(*argv, "-no_close_device") == 0))
        {
            Close_Device             = false;
            main_args_p->dbus_cmd = DBUS_CMD_ALL;
        }
        if (strcmp(*argv, "-result") == 0)
        {
            Get_Result_file       = true;
            main_args_p->dbus_cmd = DBUS_CMD_ALL;
        }
        if ((strcmp(*argv, "-no_i_scan") == 0) || (strcmp(*argv, "-direct_copy") == 0) || (strcmp(*argv, "-dc") == 0))
        {
            no_instance_scan       = true;
            main_args_p->dbus_cmd = DBUS_CMD_ALL;
        }
        else if (strcmp(*argv, "-testall") == 0)
        {
            open_tag_about_test_all = true;
        }
        else if (strcmp(*argv, "-test_parallel_second") == 0)
        {
            argv++;
            if (*argv)
            {
                test_parallel_second = atoi(*argv);
                dbus_printf("parallel test %d seconds\n", test_parallel_second);
            }
        }
        else if ((strcmp(*argv, "-no_redundancy") == 0) || (strcmp(*argv, "-no_re") == 0))
        {
            redundancy            = false;
            main_args_p->dbus_cmd = DBUS_CMD_ALL;
        }
        else if (strcmp(*argv, "-parallel_no_redundancy") == 0)
        {
            main_args_p->dbus_cmd = DBUS_CMD_PARALLEL;
            redundancy            = false;
            Get_Result_file       = false;
            Parallel_mode         = true;
            argv++;
            if (*argv)
            {
                if (strcmp(*argv, "1") == 0)
                {
                    parallel_process_index = 1;
                }
                else if (strcmp(*argv, "2") == 0)
                {
                    parallel_process_index = 2;
                }
                else if (strcmp(*argv, "3") == 0)
                {
                    parallel_process_index = 3;
                }
                else if (strcmp(*argv, "4") == 0)
                {
                    parallel_process_index = 4;
                }
                else if (strcmp(*argv, "5") == 0)
                {
                    parallel_process_index = 5;
                }
                else
                {
                    dbus_printf("parallel just support 1~5\n");
                }
            }
        }
        else if (strcmp(*argv, "-parallel") == 0)
        {
            main_args_p->dbus_cmd = DBUS_CMD_PARALLEL;
            Get_Result_file       = false;
            Parallel_mode         = true;
            argv++;
            if (*argv)
            {
                if (strcmp(*argv, "1") == 0)
                {
                    parallel_process_index = 1;
                }
                else if (strcmp(*argv, "2") == 0)
                {
                    parallel_process_index = 2;
                }
                else if (strcmp(*argv, "3") == 0)
                {
                    parallel_process_index = 3;
                }
                else if (strcmp(*argv, "4") == 0)
                {
                    parallel_process_index = 4;
                }
                else if (strcmp(*argv, "5") == 0)
                {
                    parallel_process_index = 5;
                }
                else
                {
                    dbus_printf("parallel just support 1~5\n");
                }
            }
        }
        else if (strcmp(*argv, "-ddos") == 0)
        {
            main_args_p->dbus_cmd = DBUS_CMD_TEST_DDOS;
        }
        else if (strcmp(*argv, "-step") == 0)
        {
            main_args_p->dbus_cmd = DBUS_CMD_ALL_BY_STEP;
            return(main_args_p);
        }
        else if (strcmp(*argv, "-more") == 0)
        {
            main_args_p->dbus_cmd = DBUS_CMD_TEST_MORE_METHOD;
            record_argv           = argv;
            record_argv++;
            return(main_args_p);
        }
        else if ((strcmp(*argv, "-introspect") == 0) || (strcmp(*argv, "-intro") == 0))
        {
            argv++;
            main_args_p->dbus_cmd = DBUS_CMD_INTROSPECT;
            print_introspect      = true;
            if (*argv)
            {
                o_set = *argv;
            }
            return(main_args_p);
        }
        else if ((strcmp(*argv, "-quick_get") == 0) || (strcmp(*argv, "-q_g") == 0))
        {
            Quick_Get = true;
        }
        if (*argv)
        {
            argv++;
        }
    }
    return(main_args_p);
} /* parse_args */


void dbus_cts_help()
{
    dbus_printf("##########################################################################\n");
    dbus_printf("\t dbus_cts   \n");
    dbus_printf("\t\t  perform all object \n");
    dbus_printf("\t dbus_cts -nc \n");
    dbus_printf("\t\t  not clean the bak file\n");
    dbus_printf("\t dbus_cts -ncd \n");
    dbus_printf("\t\t  not close some device before test\n");
    dbus_printf("\t dbus_cts -quick_get \n");
    dbus_printf("\t\t  Quick Get the property after Set it\n");
    dbus_printf("\t dbus_cts -parallel \n");
    dbus_printf("\t\t  do parallel test\n");
    dbus_printf("\t dbus_cts -no_redundancy \n");
    dbus_printf("\t\t  no redundancy time when test\n");
    dbus_printf("\t dbus_cts -o object -intro\n");
    dbus_printf("\t\t  do introspect one object\n");
    dbus_printf("\t dbus_cts -print_introspect \n");
    dbus_printf("\t\t  print the introspect info when testing\n");
    dbus_printf("\t dbus_cts -path /tmp \n");
    dbus_printf("\t\t  set the program root path to /tmp \n");
    dbus_printf("\t dbus_cts -o object_path\n");
    dbus_printf("\t\t perform the method and get properties about the object\n");
    dbus_printf("\t dbus_cts -o object_path -i interface_name\n");
    dbus_printf("\t\t perform the method and get properties in interface_name\n");
    dbus_printf("\t dbus_cts -o object_path -i interface_name -p property_name -m Get\n");
    dbus_printf("\t\t get the property value about interface\n");
    dbus_printf("\t dbus_cts -o object_path -i interface_name -p property_name -m Set\n");
    dbus_printf("\t\t set the property value about interface\n");
    dbus_printf("\t dbus_cts -o object_path -i interface_name -m GetAll\n");
    dbus_printf("\t\t get all the properties value about interface\n");
    dbus_printf("\t dbus_cts -o object_path -i interface_name -m SetMulti\n");
    dbus_printf("\t\t Set the properties value about interface\n");
    dbus_printf("\t dbus_cts -o object_path -i interface_name -m method_name\n");
    dbus_printf("\t\t method the interface\n");
    dbus_printf("\t dbus_cts -o object_path -i interface_name -p property_name -s\n");
    dbus_printf("\t\t check signal of the property is changed\n");
    dbus_printf("###########################################################################\n");
}



void close_device(char* object_name, char* object_form_name, char* interface_name, char* property_name)
{
    struct listnode       *obj_list_item_p;
    struct listnode       *interface_list_item_p;
    struct listnode       *interface_list_item_p2;
    struct dbus_object    *dbus_object_p;
    struct dbus_interface *dbus_interface_p;
    struct dbus_interface *dbus_interface_p2;
    struct listnode       *dbus_case_item_p;
    int                   obj_count   = 0;
    int                   current_obj = 0;
    struct listnode       *method_list_item_p;
    struct listnode       *property_list_item_p;
    struct dbus_property  *property_p;
    if((interface_name == NULL) || (property_name == NULL))
        return;
    if((object_name == NULL) && (object_form_name == NULL))
        return;
    if(Close_Device)
        dbus_printf("%s \n",__func__);
    else
    {
        dbus_printf("Not Close device\n");
        return;
    }

    bool current_log = true;
    current_log = open_log;
    open_log = false;
    bool current_check_notification = true;
    current_check_notification = check_notification;
    check_notification = false;
    dbus_printf("%s. Close the log and notification_check for adjust device.\n",__func__);
    list_for_each(obj_list_item_p, &dbus_list)
    {
        dbus_object_p = node_to_item(obj_list_item_p, struct dbus_object, list);
        if((object_form_name != NULL) && (dbus_object_p->form_name != NULL))
        {
            if (strcmp(dbus_object_p->form_name,object_form_name) == 0)
            {
                list_for_each(interface_list_item_p, &dbus_object_p->interface_list)
                {
                    dbus_interface_p = node_to_item(interface_list_item_p,
                                                    struct dbus_interface, list);
                    if (strcmp((dbus_interface_p->name), interface_name) == 0)
                    {
                        list_for_each(property_list_item_p, &dbus_interface_p->property_list)
                        {
                            property_p = node_to_item(property_list_item_p,
                                                  struct dbus_property, list);
                            if(strcmp(property_p->name,"Enable") == 0)
                            {
                                if(dbus_object_p->name != NULL)
                                    dbus_printf("%s set test_value2 to close %s.%s.Enable\n",__func__,dbus_object_p->name,dbus_interface_p->name);
                                //Notes. The close setting is setten by test_value2.
                                igd1_Set_Checksignal_CheckGet(dbus_object_p, dbus_interface_p, property_p, 2);
                            }
                        }
                    }
                }
            }
        }
        if((object_name != NULL) && (dbus_object_p->name != NULL))
        {
            if (strcmp(dbus_object_p->name,object_name) == 0)
            {
                list_for_each(interface_list_item_p, &dbus_object_p->interface_list)
                {
                    dbus_interface_p = node_to_item(interface_list_item_p,
                                                    struct dbus_interface, list);
                    if (strcmp((dbus_interface_p->name), interface_name) == 0)
                    {
                        list_for_each(property_list_item_p, &dbus_interface_p->property_list)
                        {
                            property_p = node_to_item(property_list_item_p,
                                                  struct dbus_property, list);
                            if(strcmp(property_p->name,"Enable") == 0)
                            {
                                if(dbus_object_p->name != NULL)
                                    dbus_printf("%s set test_value2 to close %s.%s.Enable\n",__func__,dbus_object_p->name,dbus_interface_p->name);
                                //Notes. The close setting is setten by test_value2.
                                igd1_Set_Checksignal_CheckGet(dbus_object_p, dbus_interface_p, property_p, 2);
                            }
                        }
                    }
                }
            }
        }

    }
    dbus_printf("%s. After adjust device reset the log and notification_check tag.\n",__func__);
    check_notification = current_check_notification;
    open_log=current_log;
}

void dbus_cts_all()
{
    struct listnode       *obj_list_item_p;
    struct listnode       *interface_list_item_p;
    struct listnode       *interface_list_item_p2;
    struct dbus_object    *dbus_object_p;
    struct dbus_interface *dbus_interface_p;
    struct dbus_interface *dbus_interface_p2;
    struct listnode       *dbus_case_item_p;
    int                   obj_count   = 0;
    int                   current_obj = 0;
    struct listnode       *method_list_item_p;


    if (!list_empty(&dbus_list))
    {
        list_for_each(obj_list_item_p, &dbus_list)
        {
            obj_count++;
        }
        dbus_printf("Total object number is %d\n", obj_count);

        if (Introspect_step)
        {
            list_for_each(obj_list_item_p, &dbus_list)
            {
                dbus_object_p = node_to_item(obj_list_item_p, struct dbus_object, list);
                current_obj++;

                dbus_printf("(%d/%d)Begin++++ %s into introspect\n", current_obj, obj_count, dbus_object_p->name);
                remote_object_introspectable_check(dbus_object_p, true);
                dbus_printf("End  ==== %s out introspect\n", dbus_object_p->name);
                if (sigint_received)
                {
                    exit(0);
                }
            }    //Notes: 1, do introspect

#if !defined (x86)
            WLAN_Devices_object_sync();
            dbus_printf("Try to close some device for ready test\n");
            sleep(3);
            //liuxy 0906-003 begin : KickOutDevice_flag for do "KickOutDevice" in advance.
            if(KickOutDevice_flag == true)
            {
                struct listnode *arg_list_item_p;

                list_for_each(obj_list_item_p, &dbus_list)
                {
                    dbus_object_p = node_to_item(obj_list_item_p, struct dbus_object, list);

                    list_for_each(interface_list_item_p, &dbus_object_p->interface_list)
                    {
                        dbus_interface_p = node_to_item(interface_list_item_p,
                                                        struct dbus_interface, list);

                        if (!strncmp((dbus_interface_p->name), "com.ctc.igd1.WiFiInfo", strlen("com.ctc.igd1.WiFiInfo")))
                        {
                            list_for_each(method_list_item_p, &dbus_interface_p->method_list)
                            {
                                struct dbus_method *dbus_method_p = node_to_item(method_list_item_p, struct dbus_method, list);

                                if (!strncmp((dbus_method_p->name), "KickOutDevice", strlen("KickOutDevice")))
                                {
                                    //find method "KickOutDevice"
                                    dbus_printf(" find KickOutDevice. In %s at %d \n",__func__,__LINE__);
                                    
                                    struct dbus_object *LANHost_for_kick = NULL;
                                    LANHost_for_kick = KickOutDevice_Lookup();
                                    if (LANHost_for_kick == NULL)
                                    {
                                        break;
                                    }
                                    dbus_printf("\n\n       KickOutDevice bind to Get %s.com.ctc.igd1.LANHost.MAC\n", LANHost_for_kick->name);

                                    //remote_object_method_Lookup("/com/ctc/igd1/Config/LANHosts/{i}","com.ctc.igd1.LANHost","MAC","Get");
                                    remote_object_method_Lookup(LANHost_for_kick->name, "com.ctc.igd1.LANHost", "MAC", "Get");
                                    if (LANHost_MAC == NULL)
                                    {
                                        dbus_printf("com.ctc.igd1.LANHost.MAC can't get\n");
                                        //can not find MAC.
                                        dbus_printf("  Can't find the object /com/ctc/igd1/Config/LANHosts/{i} with MAC\n");
                                        dbus_printf_twice("/com/ctc/igd1/Info/WiFi,com.ctc.igd1.WiFiInfo, ,KickOutDevice, , ,%s,%s,%s,%s\n", "Failed", "Method MAC arg can't get", __func__, "Can't find the object /com/ctc/igd1/Config/LANHosts/{i} with MAC");
                                        break;
                                    }
                                    //set arg MAC
                                    list_for_each(arg_list_item_p, &dbus_method_p->arg_list)
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
                                        //can not find Port.
                                        dbus_printf("  Can't find the object /com/ctc/igd1/Config/LANHosts/{i} with Port\n");
                                        dbus_printf_twice("/com/ctc/igd1/Info/WiFi,com.ctc.igd1.WiFiInfo, ,KickOutDevice, , ,%s,%s,%s,%s\n", "Failed", "Method MAC arg can't get", __func__, "Can't find the object /com/ctc/igd1/Config/LANHosts/{i} with Port");
                                    }
                                    //set arg SSIDIndex
                                    list_for_each(arg_list_item_p, &dbus_method_p->arg_list)
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
                                    //call the method "KickOutDevice"
                                    remote_object_method_Lookup("/com/ctc/igd1/Info/WiFi", "com.ctc.igd1.WiFiInfo", NULL, "KickOutDevice");
                                }/*find method*/
                            }/*loop method*/
                        }/*find interface*/
                    }/*loop interface*/
                }/*loop object*/
            }
            //liuxy 0906-003 end
            close_device("/com/ctc/igd1/Info/WiFi", NULL,"com.ctc.igd1.WiFiInfo","Enable");
            close_device("/com/ctc/igd1/Config/WLAN/Timer", NULL,"com.ctc.igd1.WiFiTimer","Enable");
            close_device("/com/ctc/igd1/Config/Peripheral/LED", NULL,"com.ctc.igd1.LED","Enable");
            close_device("/com/ctc/igd1/Config/DHCPServer", NULL, "com.ctc.igd1.DHCPServer","Enable");
            close_device("/com/ctc/igd1/Network/HTTPServer",NULL, "com.ctc.igd1.HTTPServer","Enable");
            close_device(NULL, "/com/ctc/igd1/Config/WLAN/ExTimers/{i}","com.ctc.igd1.WiFiTimer1","Enable");
            close_device(NULL, "/com/ctc/igd1/Config/Power/SleepTimers/{i}","com.ctc.igd1.SleepTimer","Enable");
            close_device(NULL, "/com/ctc/igd1/Config/WLAN/Devices/{i}","com.ctc.igd1.WLANConfiguration","Enable");
            close_device(NULL, "/com/ctc/igd1/Config/PortMapping/{i}","com.ctc.igd1.PortMapping","Enable");
#endif
        }


        current_obj = 0;
        if (Peer_step)
        {
            list_for_each(obj_list_item_p, &dbus_list)
            {
                dbus_object_p = node_to_item(obj_list_item_p, struct dbus_object, list);
                current_obj++;
                list_for_each(interface_list_item_p, &dbus_object_p->interface_list)
                {
                    dbus_interface_p = node_to_item(interface_list_item_p,
                                                    struct dbus_interface, list);
                    if (!strncmp((dbus_interface_p->name), "org.freedesktop.DBus.Peer", strlen("org.freedesktop.DBus.Peer")))
                    {
                        dbus_printf("(%d/%d)Begin++++ %s,%s into peer\n", current_obj, obj_count, dbus_object_p->name, dbus_interface_p->name);
                        remote_object_peer(dbus_interface_p, dbus_object_p);
                        dbus_printf("End  ==== %s,%s out peer\n", dbus_object_p->name, dbus_interface_p->name);
                        if (sigint_received)
                        {
                            exit(0);
                        }
                    }
                }        //Notes: 2 , do peer
            }
        }


        current_obj = 0;
        if (Get_step)
        {
            list_for_each(obj_list_item_p, &dbus_list)
            {
                dbus_object_p = node_to_item(obj_list_item_p, struct dbus_object, list);
                current_obj++;

                list_for_each(interface_list_item_p, &dbus_object_p->interface_list)
                {
                    dbus_interface_p = node_to_item(interface_list_item_p,
                                                    struct dbus_interface, list);

                    if (!strncmp((dbus_interface_p->name), "com.ctc.igd1.Properties", strlen("com.ctc.igd1.Properties")))
                    {
                        list_for_each(interface_list_item_p2, &dbus_object_p->interface_list)
                        {
                            dbus_interface_p2 = node_to_item(interface_list_item_p2,
                                                             struct dbus_interface, list);
                            if (!list_empty(&dbus_interface_p2->property_list))
                            {
                                dbus_printf("(%d/%d)Begin++++ %s,%s into igd1 Get property\n", current_obj, obj_count, dbus_object_p->name, dbus_interface_p->name);
                                remote_object_method_Lookup(dbus_object_p->name, dbus_interface_p2->name, NULL, "Get");
                                dbus_printf("End  ==== %s,%s out igd1 Get property\n", dbus_object_p->name, dbus_interface_p->name);
                                if (sigint_received)
                                {
                                    exit(0);
                                }
                            }
                        }
                    }
                }        //Notes: 3 , do Get........Get will repeat in GCS or SCC
                         //Notes: Get will repeat in GCS or SCC, But GCS and SCC haven't the parse value log.
                         //       So.... Get method should do it himself.
            }
        }

        current_obj = 0;
        if (GetAll_step)
        {
            list_for_each(obj_list_item_p, &dbus_list)
            {
                dbus_object_p = node_to_item(obj_list_item_p, struct dbus_object, list);
                current_obj++;
                list_for_each(interface_list_item_p, &dbus_object_p->interface_list)
                {
                    dbus_interface_p = node_to_item(interface_list_item_p,
                                                    struct dbus_interface, list);

                    if (!strncmp((dbus_interface_p->name), "com.ctc.igd1.Properties", strlen("com.ctc.igd1.Properties")))
                    {
                        list_for_each(interface_list_item_p2, &dbus_object_p->interface_list)
                        {
                            dbus_interface_p2 = node_to_item(interface_list_item_p2,
                                                             struct dbus_interface, list);
                            if (!list_empty(&dbus_interface_p2->property_list))
                            {
                                dbus_printf("(%d/%d)Begin++++ %s,%s into igd1 GetAll property\n", current_obj, obj_count, dbus_object_p->name, dbus_interface_p->name);
                                remote_object_igd1_properties_get_all(dbus_interface_p2, dbus_object_p);
                                dbus_printf("End  ==== %s,%s out igd1 GetAll property\n", dbus_object_p->name, dbus_interface_p->name);
                                if (sigint_received)
                                {
                                    exit(0);
                                }
                            }
                        }
                    }
                }        //Notes: 4 , do Getall
            }
        }

#if 1
        current_obj = 0;
        if (Set_step)
        {
            list_for_each(obj_list_item_p, &dbus_list)
            {
                dbus_object_p = node_to_item(obj_list_item_p, struct dbus_object, list);
                current_obj++;
                list_for_each(interface_list_item_p, &dbus_object_p->interface_list)
                {
                    dbus_interface_p = node_to_item(interface_list_item_p,
                                                    struct dbus_interface, list);

                    if (!strncmp((dbus_interface_p->name), "com.ctc.igd1.Properties", strlen("com.ctc.igd1.Properties")))
                    {
                        list_for_each(interface_list_item_p2, &dbus_object_p->interface_list)
                        {
                            dbus_interface_p2 = node_to_item(interface_list_item_p2,
                                                             struct dbus_interface, list);
                            if (!list_empty(&dbus_interface_p2->property_list))
                            {
                                dbus_printf("(%d/%d)Begin++++ %s,%s into igd1 Set/Check signal/Check Get property\n", current_obj, obj_count, dbus_object_p->name, dbus_interface_p2->name);
                                remote_object_igd1_properties_SCC(dbus_interface_p2, dbus_object_p);
                                dbus_printf("End  ==== %s,%s out igd1 Set/Check signal/Check Get property\n", dbus_object_p->name, dbus_interface_p2->name);
                                if (sigint_received)
                                {
                                    exit(0);
                                }
                            }
                        }
                    }
                }        //Notes: 5 , do GCS  or do SCC. This is SCC
            }
        }

#else
        current_obj = 0;
        if (Set_Step)
        {
            list_for_each(obj_list_item_p, &dbus_list)
            {
                dbus_object_p = node_to_item(obj_list_item_p, struct dbus_object, list);
                current_obj++;

                list_for_each(interface_list_item_p, &dbus_object_p->interface_list)
                {
                    dbus_interface_p = node_to_item(interface_list_item_p,
                                                    struct dbus_interface, list);
                    if (!strncmp((dbus_interface_p->name), "com.ctc.igd1.Properties", strlen("com.ctc.igd1.Properties")))
                    {
                        dbus_printf("(%d/%d)Begin++++ %s,%s into igd1 Get/Set/Check signal property\n", current_obj, obj_count, dbus_object_p->name, dbus_interface_p->name);
                        remote_object_igd1_properties_GCS(dbus_interface_p, dbus_object_p);
                        dbus_printf("End  ==== %s,%s out igd1 Get/Set/Check signal property\n", dbus_object_p->name, dbus_interface_p->name);
                    }
                }        //Notes: 5 , do GCS  or do SCC. This is GCS
            }
        }
#endif

        current_obj = 0;
        if (Get_Check_step)
        {
            list_for_each(obj_list_item_p, &dbus_list)
            {
                dbus_object_p = node_to_item(obj_list_item_p, struct dbus_object, list);
                current_obj++;
                list_for_each(interface_list_item_p, &dbus_object_p->interface_list)
                {
                    dbus_interface_p = node_to_item(interface_list_item_p,
                                                    struct dbus_interface, list);
                    struct listnode      *property_list_item_p;
                    int                  readwrite_propertys = 0;
                    struct dbus_property *property_p;
                    list_for_each(property_list_item_p, &dbus_interface_p->property_list)
                    {
                        property_p = node_to_item(property_list_item_p,
                                                  struct dbus_property, list);
                        if (property_p != NULL)
                        {
                            if (g_strcmp0(property_p->access, "readwrite") == 0)
                            {
                                dbus_printf("(%d/%d)Begin++++ %s,%s into igd1 Get to check Set result\n", current_obj, obj_count, dbus_object_p->name, dbus_interface_p->name);
                                igd1_Get_CheckSetResult(dbus_object_p, dbus_interface_p, property_p);
                                dbus_printf("End  ==== %s,%s out igd1 Get to check Set result\n", dbus_object_p->name, dbus_interface_p->name);
                                if (sigint_received)
                                {
                                    exit(0);
                                }
                            }
                        }
                    }
                }        //Notes: 6 , do Get again, to check Set
            }
        }


        current_obj = 0;
        if (SetMulti_step)
        {
            list_for_each(obj_list_item_p, &dbus_list)
            {
                dbus_object_p = node_to_item(obj_list_item_p, struct dbus_object, list);
                current_obj++;
                list_for_each(interface_list_item_p, &dbus_object_p->interface_list)
                {
                    dbus_interface_p = node_to_item(interface_list_item_p,
                                                    struct dbus_interface, list);
                    struct listnode      *property_list_item_p;
                    int                  readwrite_propertys = 0;
                    struct dbus_property *property_p;
                    list_for_each(property_list_item_p, &dbus_interface_p->property_list)
                    {
                        property_p = node_to_item(property_list_item_p,
                                                  struct dbus_property, list);
                        if (property_p != NULL)
                        {
                            if (g_strcmp0(property_p->access, "readwrite") == 0)
                            {
                                readwrite_propertys++;
                            }
                        }
                    }
                    if (readwrite_propertys > 0)
                    {
                        dbus_printf("(%d/%d)Begin++++ %s,%s into igd1 SetMulti\n", current_obj, obj_count, dbus_object_p->name, dbus_interface_p->name);
                        remote_object_method_Lookup(dbus_object_p->name, dbus_interface_p->name, NULL, "SetMulti");
                        dbus_printf("End  ==== %s,%s out igd1 SetMulti\n", dbus_object_p->name, dbus_interface_p->name);
                        if (sigint_received)
                        {
                            exit(0);
                        }
                    }
                }        //Notes: 7 , do SetMulti
            }
        }

        current_obj = 0;
        if (Method_step)
        {
            list_for_each(obj_list_item_p, &dbus_list)
            {
                dbus_object_p = node_to_item(obj_list_item_p, struct dbus_object, list);
                current_obj++;
                list_for_each(interface_list_item_p, &dbus_object_p->interface_list)
                {
                    dbus_interface_p = node_to_item(interface_list_item_p,
                                                    struct dbus_interface, list);
                    if (!strncmp((dbus_interface_p->name), "org.freedesktop.DBus.Introspectable", strlen("org.freedesktop.DBus.Introspectable")))
                    {
                        continue;
                    }
                    else if (!strncmp((dbus_interface_p->name), "org.freedesktop.DBus.Peer", strlen("org.freedesktop.DBus.Peer")))
                    {
                        continue;
                    }
                    else if (!strncmp((dbus_interface_p->name), "com.ctc.igd1.Properties", strlen("com.ctc.igd1.Properties")))
                    {
                        continue;
                    }
                    else if (!strncmp((dbus_interface_p->name), "com.ctc.igd1.ObjectManager", strlen("com.ctc.igd1.ObjectManager")))
                    {
                        continue;
                    }
                    else if (!list_empty(&dbus_interface_p->method_list))
                    {
                        list_for_each(method_list_item_p, &dbus_interface_p->method_list)
                        {
                            struct dbus_method *dbus_method_p = node_to_item(method_list_item_p, struct dbus_method, list);

                            dbus_printf("(%d/%d)Begin++++ %s,%s,%s into method\n", current_obj, obj_count, dbus_object_p->name, dbus_interface_p->name, dbus_method_p->name);
                            //remote_object_method(dbus_object_p, dbus_interface_p, dbus_method_p);
                            //Notes: Some method use IN arg, so... must use case object.
                            remote_object_method_Lookup(dbus_object_p->name, dbus_interface_p->name, NULL, dbus_method_p->name);
                            dbus_printf("End ==== %s,%s,%s out method\n", dbus_object_p->name, dbus_interface_p->name, dbus_method_p->name);
                            if (sigint_received)
                            {
                                exit(0);
                            }
                        }
                    }
                    else
                    {
                        continue;
                    }
                }        //Notes: 8, do normal call.
            }
        }

        current_obj = 0;
        if (Add_Del_Obj_step){
            list_for_each(obj_list_item_p, &dbus_list)
            {
                dbus_object_p = node_to_item(obj_list_item_p, struct dbus_object, list);
                current_obj++;
                list_for_each(interface_list_item_p, &dbus_object_p->interface_list)
                {
                    dbus_interface_p = node_to_item(interface_list_item_p,
                                                    struct dbus_interface, list);

                    if (!strncmp((dbus_interface_p->name), "com.ctc.igd1.ObjectManager", strlen("com.ctc.igd1.ObjectManager")))
                    {
                        /*dbus_printf("(%d/%d)Begin++++ %s,%s, GetManagedObjects into method\n",current_obj, obj_count,dbus_object_p->name,dbus_interface_p->name);
                           remote_object_method_Lookup(dbus_object_p->name, dbus_interface_p->name, NULL,"GetManagedObjects");
                           dbus_printf("End ==== %s,%s, GetManagedObjects out method\n",dbus_object_p->name,dbus_interface_p->name);
                           dbus_printf("(%d/%d)Begin++++ %s,%s, AddObject/DeleteObject into method\n",current_obj, obj_count,dbus_object_p->name,dbus_interface_p->name);
                           remote_object_method_Lookup(dbus_object_p->name, dbus_interface_p->name, NULL,"ACDC");
                           dbus_printf("End ==== %s,%s, AddObject/DeleteObject out method\n",dbus_object_p->name,dbus_interface_p->name);*/

                        list_for_each(method_list_item_p, &dbus_interface_p->method_list)
                        {
                            struct dbus_method *dbus_method_p = node_to_item(method_list_item_p, struct dbus_method, list);

                            //remote_object_method(dbus_object_p, dbus_interface_p, dbus_method_p);
                            //Notes: Some method use IN arg, so... must use case object.
                            if (!strncmp((dbus_method_p->name), "AddObject", strlen("AddObject")))
                            {
                                if ((strcmp(dbus_object_p->name, "/com/ctc/igd1/Storage/usb/devices") == 0) ||
                                    (strcmp(dbus_object_p->name, "/com/ctc/igd1/Config/WLAN/Devices") == 0) ||
                                    (strcmp(dbus_object_p->name, "/com/ctc/igd1/Info/Network/WANConnectionDb/{i}") == 0) ||
                                    (strcmp(dbus_object_p->name, "/com/ctc/igd1/Info/Network/WANConnectionDb") == 0) ||
                                    //liuxy 0906-001 begin : ignore AddObject / DeleteObject check for /com/ctc/igd1/Network/Telnetserver/Accounts
                                    (strcmp(dbus_object_p->name, "/com/ctc/igd1/Network/Telnetserver/Accounts") == 0))
                                {
                                    dbus_printf("(%d/%d)Don't test %s,%s AddObject / DeleteObject method \n", current_obj, obj_count, dbus_object_p->name, dbus_interface_p->name);
                                    continue;
                                }
                                dbus_printf("(%d/%d)Begin++++ %s,%s,AddObject / DeleteObject into method\n", current_obj, obj_count, dbus_object_p->name, dbus_interface_p->name);
                                remote_object_method_Lookup(dbus_object_p->name, dbus_interface_p->name, NULL, "ACDC");
                                dbus_printf("End ==== %s,%s, AddObject / DeleteObject  out method\n", dbus_object_p->name, dbus_interface_p->name);
                            }
                            else if (!strncmp((dbus_method_p->name), "DeleteObject", strlen("DeleteObject")))
                            {
                                continue;
                            }
                            else
                            {
                                dbus_printf("(%d/%d)Begin++++ %s,%s,%s into method\n", current_obj, obj_count, dbus_object_p->name, dbus_interface_p->name, dbus_method_p->name);
                                remote_object_method_Lookup(dbus_object_p->name, dbus_interface_p->name, NULL, dbus_method_p->name);
                                dbus_printf("End ==== %s,%s,%s out method\n", dbus_object_p->name, dbus_interface_p->name, dbus_method_p->name);
                            }
                            if (sigint_received)
                            {
                                exit(0);
                            }
                        }
                    }
                }        //Notes: 9, do ObjectManager call.
            }
        }
    }
    else
    {
        dbus_printf("Failed There is no object to test,Please check /tmp/dbus_cts.xml\n");
    }
} /* dbus_cts_all */


static void sigint_handler(int signum)
{
    dbus_printf("sigint_handler\n");
    sigint_received = TRUE;
}


#if 1
struct stack_builder2
{
    GVariantBuilder    *parent;
    GVariantType       *type;
    const GVariantType *expected_type;
    const GVariantType *prev_item_type;
    gsize              min_items;
    gsize              max_items;
    GVariant           **children;
    gsize              allocated_children;
    gsize              offset;
    guint              uniform_item_types : 1;
    guint              trusted            : 1;
    gsize              magic;
};


struct heap_builder2
{
    GVariantBuilder builder;
    gsize           magic;
    gint            ref_count;
};
#define GVSB(b)                      ((struct stack_builder2 *)(b))
#define GVHB(b)                      ((struct heap_builder2 *)(b))
#define GVSB_MAGIC    ((gsize)1033660112u)
#define GVHB_MAGIC    ((gsize)3087242682u)
#define is_valid_builder2(b)         (b != NULL && \
                                      GVSB(b)->magic == GVSB_MAGIC)
#define is_valid_heap_builder2(b)    (GVHB(b)->magic == GVHB_MAGIC)
#endif


int main(int argc, char *argv[])
{
    //dbus_command_s  run_args = DBUS_COMMAND_INVALID;
    //run_args = DBUS_COMMAND_INVALID;

    struct timeval start;
    struct timeval end;

    gettimeofday(&start, NULL);
   
    root_path = g_getenv ("PWD");
    parse_args(argc, argv);

    dbus_printf("current path is %s\n",root_path);
//	check_root_path(0);
    if (parallel_process_index == 1)
    {
        check_root_path(1);
    }
    else if (parallel_process_index == 2)
    {
        check_root_path(2);
    }
    else if (parallel_process_index == 3)
    {
        check_root_path(3);
    }
    else if (parallel_process_index == 4)
    {
        check_root_path(4);
    }
    else if (parallel_process_index == 5)
    {
        check_root_path(5);
    }
    else
    {
        check_root_path(0);
    }


    dbus_printf("########\n");
    dbus_printf("########\n");
    dbus_printf("########\n");
    dbus_printf("########\n");

    signal(SIGINT, sigint_handler);


#if 1 //! defined(x86)
    if (main_args_p->dbus_cmd == DBUS_CMD_HELP)
    {
        goto print_help_info;
    }

    if ((access(xml_path, 0) == 0) && clean_bak)
    {
        remove(xml_path);
        dbus_printf("   Clear dbus_cts.xml.bak\n");
    }
    if ((access(xml_case_bak_path, 0) == 0) && clean_bak)
    {
        remove(xml_case_bak_path);
        dbus_printf("   Clear dbus_cts.case.xml.bak\n");
    }
    if ((access(xml_path, 0) != 0) && ((access(xml_case_bak_path, 0) != 0)))
    {
        if (access(noinstance_xml_path, 0) != 0)
        {
            //dbus_printf("   No dbus_cts.xml, return\n");
            dbus_printf("   No %s, return\n", noinstance_xml_path);
            return(-1);
        }
        if (access(xml_case_path, 0) != 0)
        {
            //dbus_printf("   No dbus_cts.case.xml, return\n");
            dbus_printf("   No %s, return\n", xml_case_path);
            return(-1);
        }

        dbus_printf("%s is not exist. Check instance and generate the xml.bak\n", xml_path);
        if(no_instance_scan)
        {
            char file_copy1[200] = {0};
            sprintf(file_copy1, "sed s/{i}/1/g %s > %s ", noinstance_xml_path, xml_path);
            system(file_copy1);
            char file_copy2[200] = {0};
            sprintf(file_copy2, "sed s/{i}/1/g %s > %s ", xml_case_path, xml_case_bak_path);
            system(file_copy2);
            dbus_printf("xml direct_copy xml.bak\n");
        }
        else
        {
            dbus_printf("Check the instance .....\n");
            if (-1 == instance_run())
            {
                dbus_printf("No %s\n", noinstance_xml_path);
                return(-1);
            }
        }
        dbus_printf("Check the instance end\n");
        dbus_printf("Note: Using the newest xml to parse\n");
    }
    dbus_printf("Parse the xml .....%s\n", xml_path);
#endif

    if (dbus_xml_init())
    {
        dbus_printf("dbus_xml_init fail!\n");
        return(-1);
    }
    if (dbus_case_xml_init())
    {
        dbus_printf("dbus_case_xml_init fail!\n");
        return(-1);
    }

    sleep(1);
    dbus_printf("Parse the xml end\n");
    object_sync();
    dbus_printf("Sync info from the case.xml into xml \n");
print_help_info:
    {
        GLogLevelFlags fatal_mask;
        fatal_mask  = g_log_set_always_fatal(G_LOG_FATAL_MASK);
        fatal_mask |= G_LOG_LEVEL_WARNING | G_LOG_LEVEL_CRITICAL;
        g_log_set_always_fatal(fatal_mask);
    }


    run_args = main_args_p->dbus_cmd;


    if (DBUS_CMD_ALL == run_args)
    {
        int retry = 0;

        //Checkoverlayfs();
        checkOSversion();
        checkoverlayfs();
        checklxc();
        checkulibc();
entry:
        //liuxy 0906-003 : KickOutDevice_flag for do "KickOutDevice" in advance.
        KickOutDevice_flag = true;
        dbus_cts_all();
        gettimeofday(&end, NULL);
        if (!Parallel_mode)
        {
            //liuxy 0907-001 begin : postpone "Restore" of com.ctc.igd1.SysCmd
            dbus_printf("Not in parallel mode , test Restore of com.ctc.igd1.SysCmd\n");
            run_args = DBUS_CMD_OBJECT;
            remote_object_method_Lookup("/com/ctc/igd1/Telecom/System", "com.ctc.igd1.SysCmd", NULL, "Restore");
            run_args = DBUS_CMD_ALL;
            //liuxy 0907-001 end
            
            dbus_printf("Not in parallel mode , test SetDateTime\n");
            run_args = DBUS_CMD_OBJECT;
            remote_object_method_Lookup("/com/ctc/igd1/Telecom/System", "com.ctc.igd1.SysCmd", NULL, "SetDateTime");
            run_args = DBUS_CMD_ALL;
        }
        //else
        //	dbus_printf("In parallel mode , Not test SetDateTime\n");


        if ((end.tv_sec - start.tv_sec) < 60)
        {
            //dbus_printf("Finish All test ... Spend (%d)sec\n",((end.tv_sec - start.tv_sec)));
            dbus_printf_twice("Finish All test ... Spend[%d, %d] (%d)sec\n", end.tv_sec, start.tv_sec, ((end.tv_sec - start.tv_sec)));
        }
        else
        {
            dbus_printf_twice("Finish All test ... Spend[%d, %d] (%d)min\n", end.tv_sec, start.tv_sec, ((end.tv_sec - start.tv_sec) / 60));
        }

        if (Get_Result_file)
        {
            dbus_printf("Generate the result file: %s\n\n", result_file);
            dbus_test_result();
        }
        else
        {
            dbus_printf("Not Generate the result file: %s\n\n", result_file);
        }
        dbus_printf("End all test. Generate the log file: %s\n\n", log_path);
        dbus_printf("######\n");
        dbus_printf("######\n");
        dbus_printf("######\n");
        dbus_printf("######\n");


        if (loop_test)
        {
            gettimeofday(&start, NULL);
            retry++;
            if (retry < 15)
            {
                goto entry;
            }
        }

        return(0);
    }
    if (DBUS_CMD_HELP == run_args)
    {
        dbus_cts_help();
        return(0);
    }
    else if (DBUS_CMD_VERSION == run_args)
    {
        dbus_printf("Current version %s\n", version);
        return(0);
    }
    else if (DBUS_COMMAND_INVALID == run_args)
    {
        return(0);
    }
    else if (DBUS_CMD_INTROSPECT == run_args)
    {
        struct listnode    *obj_list_item_p;
        struct dbus_object *dbus_object_p;


        list_for_each(obj_list_item_p, &dbus_list)
        {
            dbus_object_p = node_to_item(obj_list_item_p, struct dbus_object, list);
            if (o_set == NULL)
            {
                remote_object_introspectable_check(dbus_object_p, true);
            }
            else if (strcmp(o_set, dbus_object_p->name) == 0)
            {
                remote_object_introspectable_check(dbus_object_p, true);
            }
        }
        //liuxy 0908-001 begin : output result file for DBUS_CMD_INTROSPECT
        if (Get_Result_file)
        {
            dbus_printf("Generate the result file: %s\n\n", result_file);
            dbus_test_result();
        }
        else
        {
            dbus_printf("Not Generate the result file: %s\n\n", result_file);
        }
        //liuxy 0908-001
        return(0);
    }
#if !defined (x86)
    dbus_printf("Check the introspect info\n");
    {
        struct listnode       *obj_list_item_p;
        struct listnode       *interface_list_item_p;
        struct listnode       *interface_list_item_p2;
        struct dbus_object    *dbus_object_p;
        struct dbus_interface *dbus_interface_p;
        struct dbus_interface *dbus_interface_p2;
        struct listnode       *dbus_case_item_p;

        struct listnode       *method_list_item_p;

        list_for_each(obj_list_item_p, &dbus_list)
        {
            dbus_object_p = node_to_item(obj_list_item_p, struct dbus_object, list);
            remote_object_introspectable_check(dbus_object_p, false);
            //Notes: 1 , do introspect
        }
    }
    dbus_printf("Check the introspect end\n");
#endif
#if !defined (x86)
    WLAN_Devices_object_sync();
#endif

    if (DBUS_CMD_OBJECT == run_args)
    {
        remote_object_method_Lookup(o_set, i_set, p_set, m_set);
    }
    else if (DBUS_CMD_SIGNAL == run_args)
    {
        remote_object_signal_Lookup(o_set, i_set, p_set);
    }

    if (DBUS_CMD_PARALLEL == run_args)
    {
        dbus_printf("do parallel, parallel_process_index=%d\n", parallel_process_index);
        in_parallel_test   = true;
        check_notification = false;
        struct timeval start;
        struct timeval end;
        gettimeofday(&start, NULL);

        if (parallel_process_index == 1)
        {
            dbus_cts_parallel_1();
        }
        else if (parallel_process_index == 2)
        {
            dbus_cts_parallel_2();
        }
        else if (parallel_process_index == 3)
        {
            dbus_cts_parallel_3();
        }
        else if (parallel_process_index == 4)
        {
            dbus_cts_parallel_4();
        }
        else if (parallel_process_index == 5)
        {
            dbus_cts_parallel_5();
        }
        else
        {
            dbus_cts_parallel();
        }

        gettimeofday(&end, NULL);
        if ((end.tv_sec - start.tv_sec) < 60)
        {
            dbus_printf_twice("Finish (%d) test ... Spend[%d, %d] (%d)sec\n", parallel_process_index, end.tv_sec, start.tv_sec, ((end.tv_sec - start.tv_sec)));
        }
        else
        {
            dbus_printf_twice("Finish (%d) test ... Spend[%d, %d] (%d)min\n", parallel_process_index, end.tv_sec, start.tv_sec, ((end.tv_sec - start.tv_sec) / 60));
        }

        dbus_printf("Generate the log file: %s\n\n", log_path);
    }

    if (DBUS_CMD_TEST_DDOS == run_args)
    {
        guint32 test_times = 0;
        in_parallel_test = true;
        open_log         = false;
        for ( ; ; )
        {
            remote_object_method_Lookup("/com/ctc/igd1/Info/Device", "com.ctc.igd1.DeviceInfo", NULL, "GetAll");
            if (sigint_received)
            {
                exit(0);
            }
            remote_object_method_Lookup("/com/ctc/igd1/Info/Network", "com.ctc.igd1.NetworkInfo", NULL, "GetAll");
            if (sigint_received)
            {
                exit(0);
            }
            test_times++;
            dbus_printf("#test_times=%d\n", test_times);
        }
    }


    if (DBUS_CMD_ALL_BY_STEP == run_args)
    {
        char c;
        // int c;
        char cmd[100]    = { 0 };
        char cmd_ok[100] = { 0 };
        int  n           = 0;
        int  u           = 0;
        char *p          = cmd;
        char *pok        = cmd_ok;

        dbus_printf("\n   Please input the steps.\n   You can choose 'Set Get SetMulti GetAll Peer Method Add_Del_Obj Get_Check'. Separate with Space\n  :");
        int retry_times = 0;
        Introspect_step = false;      //Don't introspect again
retry:
        Set_step       = false;
        Get_step       = false;
        GetAll_step    = false;
        SetMulti_step  = false;
        Peer_step      = false;
        Method_step    = false;
        Add_Del_Obj_step    = false;
        Get_Check_step = false;


        for (u = 0; u < 99; u++)
        {
            cmd[u]    = '\0';
            cmd_ok[u] = '\0';
        }
        p   = cmd;
        pok = cmd_ok;
        n   = 0;
        while (c = getchar())
        {
            n++;
            if (n > 50)
            {
                dbus_printf("can't support too many input\n");
                if (retry_times++ < 3)
                {
                    dbus_printf("\nretry input:");
                    goto retry;
                }
                return;
            }
            if ((c != '\r') && (c != '\n') && (c != 10) && (c != 13))
            {
                //dbus_printf("%s\n",&c);
                *p++ = c;
            }
            else
            {
                *p++ = '\0';
                break;
            }
        }


        p = cmd;
retry_Set:
        p = strstr(p, "Set");
        if (p != NULL)
        {
            p += 3;
            if ((*p == ' ') || (*p == '\0'))
            {
                dbus_printf("Open Set step\n");
                Set_step = true;
            }
            else
            {
                goto retry_Set;
            }
        }
        p = strstr(cmd, "SCC");
        if (p != NULL)
        {
            p += 3;
            if ((*p == ' ') || (*p == '\0'))
            {
                dbus_printf("Open SCC(Set) step\n");
                Set_step = true;
            }
        }

        p = cmd;
retry_Get:
        p = strstr(p, "Get");
        if (p != NULL)
        {
            p += 3;
            if ((*p == ' ') || (*p == '\0'))
            {
                dbus_printf("Open Get step\n");
                Get_step = true;
            }
            else             //for "GetAll Get"
            {
                goto retry_Get;
            }
        }
        p = strstr(cmd, "SetMulti");
        if (p != NULL)
        {
            p += 8;
            if ((*p == ' ') || (*p == '\0'))
            {
                dbus_printf("Open SetMulti step\n");
                SetMulti_step = true;
            }
        }
        p = strstr(cmd, "GetAll");
        if (p != NULL)
        {
            p += 6;
            if ((*p == ' ') || (*p == '\0'))
            {
                dbus_printf("Open GetAll step\n");
                GetAll_step = true;
            }
        }
        p = strstr(cmd, "Peer");
        if (p != NULL)
        {
            p += 4;
            if ((*p == ' ') || (*p == '\0'))
            {
                dbus_printf("Open Peer step\n");
                Peer_step = true;
            }
        }
        p = strstr(cmd, "Method");
        if (p != NULL)
        {
            p += 6;
            if ((*p == ' ') || (*p == '\0'))
            {
                dbus_printf("Open Method step\n");
                Method_step = true;
            }
        }
        p = strstr(cmd, "Add_Del_Obj");
        if (p != NULL)
        {
            p += 11;
            if ((*p == ' ') || (*p == '\0'))
            {
                dbus_printf("Open Add_Del_Obj step\n");
                Add_Del_Obj_step = true;
            }
        }

        p = strstr(cmd, "Get_Check");
        if (p != NULL)
        {
            p += 9;
            if ((*p == ' ') || (*p == '\0'))
            {
                dbus_printf("Open Get_Check step\n");
                Get_Check_step = true;
            }
        }


        dbus_printf("[Yes/Retry/No]:  ", cmd);
        retry_times++;
        n = 0;

        while (c = getchar())
        {
            n++;
            if (n > 50)
            {
                dbus_printf("can't support too many input\n");
                if (retry_times++ < 3)
                {
                    dbus_printf("\nretry input:");
                    goto retry;
                }
                return;
            }
            if ((c != '\r') && (c != '\n') && (c != 10) && (c != 13))
            {
                //dbus_printf("%s\n",&c);
                *pok++ = c;
            }
            else
            {
                *pok++ = '\0';
                break;
            }
        }

        if ((strcmp("R", cmd_ok) == 0) || (strcmp("Retry", cmd_ok) == 0) || (strcmp("r", cmd_ok) == 0))
        {
            dbus_printf("Retry. input:\n");
            goto retry;
        }
        if ((strcmp("Y", cmd_ok) == 0) || (strcmp("Yes", cmd_ok) == 0) || (strcmp("y", cmd_ok) == 0))
        {
            dbus_printf("Test %s.\n", cmd);
            sleep(1);
        }
        else
        {
            dbus_printf("Do nothing %s\n", cmd_ok);
            return;
        }
        sleep(2);
        gettimeofday(&start, NULL);
        dbus_cts_all();
        gettimeofday(&end, NULL);
        if (!Parallel_mode)
        {
            //liuxy 0907-001 begin : postpone "Restore" of com.ctc.igd1.SysCmd
            dbus_printf("Not in parallel mode , test Restore of com.ctc.igd1.SysCmd\n");
            run_args = DBUS_CMD_OBJECT;
            remote_object_method_Lookup("/com/ctc/igd1/Telecom/System", "com.ctc.igd1.SysCmd", NULL, "Restore");
            run_args = DBUS_CMD_ALL;
            //liuxy 0907-001 end
            
            run_args = DBUS_CMD_OBJECT;
            dbus_printf("Not in parallel mode , test SetDateTime\n");
            remote_object_method_Lookup("/com/ctc/igd1/Telecom/System", "com.ctc.igd1.SysCmd", NULL, "SetDateTime");
            run_args = DBUS_CMD_ALL_BY_STEP;
        }
        //else
        //	dbus_printf("In parallel mode , Not test SetDateTime\n");

        if ((end.tv_sec - start.tv_sec) < 60)
        {
            //dbus_printf("Finish All test ... Spend (%d)sec\n",((end.tv_sec - start.tv_sec)));
            dbus_printf_twice("Finish All test ... Spend[%d, %d] (%d)sec\n", end.tv_sec, start.tv_sec, ((end.tv_sec - start.tv_sec)));
        }
        else
        {
            dbus_printf_twice("Finish All test ... Spend[%d, %d] (%d)min\n", end.tv_sec, start.tv_sec, ((end.tv_sec - start.tv_sec) / 60));
        }

        dbus_printf("Generate the log file: %s\n\n", log_path);
        if (Get_Result_file)
        {
            dbus_printf("Generate the result file: %s\n\n", result_file);
            dbus_test_result();
        }
        else
        {
            dbus_printf("Not Generate the result file: %s\n\n", result_file);
        }
        dbus_printf("######\n");
        dbus_printf("######\n");
        dbus_printf("######\n");
        dbus_printf("######\n");
        return 0;
    }


    if (DBUS_CMD_TEST_MORE_METHOD == run_args)
    {
        o_set = NULL;
        i_set = NULL;
        p_set = NULL;
        m_set = NULL;
        if (*record_argv)
        {
            do
            {
                if (strcmp(*record_argv, "-o") == 0)
                {
                    record_argv++;
                    if (*record_argv)
                    {
                        o_set = *record_argv;
                    }
                }
                if (strcmp(*record_argv, "-i") == 0)
                {
                    record_argv++;
                    if (*record_argv)
                    {
                        i_set = *record_argv;
                    }
                }
                if (strcmp(*record_argv, "-p") == 0)
                {
                    record_argv++;
                    if (*record_argv)
                    {
                        p_set = *record_argv;
                    }
                }
                if (strcmp(*record_argv, "-m") == 0)
                {
                    record_argv++;
                    if (*record_argv)
                    {
                        m_set = *record_argv;
                    }
                }
                if ((o_set != NULL) && (i_set != NULL) && (m_set != NULL))
                {
                    if (p_set != NULL)
                    {
                        dbus_printf("   ###Deal %s, %s, %s, %s\n\n", o_set, i_set, p_set, m_set);
                    }
                    else
                    {
                        dbus_printf("   ###Deal %s, %s, NULL, %s\n\n", o_set, i_set, m_set);
                    }
                    remote_object_method_Lookup(o_set, i_set, p_set, m_set);
                    o_set = NULL;
                    i_set = NULL;
                    p_set = NULL;
                    m_set = NULL;
                }
                record_argv++;
            } while (*record_argv);
        }
        else
        {
            dbus_printf("no more input! \n");
        }
    }


    if( (DBUS_CMD_RESULT != run_args) || (DBUS_CMD_ALL_BY_STEP != run_args)){
    if (Get_Result_file)
    {
        dbus_printf("test result...\n");
        dbus_test_result();
    }
    }
} /* main */
