/************************************************
*  Dbus test suite
*  Author: Thundersoft
*  2016, all rights reserved.
************************************************/
#include "dbus_xml_parse.h"
#include "dbus_log.h"
#include <gio/gio.h>
#include "list.h"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <glib/gvariant-serialiser.h>
//#include "gvariant-internal.h"
//#include <glib/gvariant-core.h>
#include <glib/gtestutils.h>
#include <glib/gstrfuncs.h>
#include <glib/gslice.h>
#include <glib/ghash.h>
#include <glib/gmem.h>
#include <glib/gatomic.h>
#include <string.h>
#include <dbus/dbus.h>
#include <dbus_cts.h>

extern dbus_command_s run_args;
bool                  check_notification = true;
bool                  check_Get_in_SCC   = true;
bool                  timeout_judgement  = true;
bool                  in_parallel_test   = false;
extern bool           redundancy;
extern bool           open_tag_about_test_all;
extern bool           lib_debug;
extern bool           Quick_Get;
extern bool           open_log;
extern const char*    igd1_interface;
extern const char*    igd1_service;
extern const char*    freedesktop_service;

//#define NORMAL_WAIT_SEC 8
#define NORMAL_WAIT_SEC    30
#define LONG_WAIT_SEC      300

//#define  EXIT_IF_NULL(a) {if(a==NULL){dbus_printf("####### NULL point. exit in %s line %d\n",__func__,__LINE__);exit(0);}};
#define EXIT_IF_NULL(a)    do { } while (0)
gint32 wait_signal_with = NORMAL_WAIT_SEC;
/*typedef enum {
        DBUS_SIGNAL_TIMEOUT = -3,
        DBUS_SIGNAL_CANT_CONNECT = -2,
        DBUS_SIGNAL_UNKNOWN = -1,
        DBUS_SIGNAL_SUCCESS = 0,
        DBUS_SIGNAL_FREEDESKTOP_PROPERTY_CHANGED ,
        DBUS_SIGNAL_IDG1_PROPERTY_CHANGED ,
        DBUS_SIGNAL_IDG1_INTERFACE_ADD ,
        DBUS_SIGNAL_IDG1_INTERFACE_REMOVE ,
        DBUS_SIGNAL_FREEDESKTOP_INTERFACE_ADD ,
        DBUS_SIGNAL_FREEDESKTOP_INTERFACE_REMOVE ,
   }dbus_cts_signal;*/
typedef enum
{
    DBUS_SIGNAL_TIMEOUT                      = 0x001,
    DBUS_SIGNAL_CANT_CONNECT                 = 0x002,
    DBUS_SIGNAL_UNKNOWN                      = 0x004,
    DBUS_SIGNAL_SUCCESS                      = 0x008,
    DBUS_SIGNAL_FREEDESKTOP_PROPERTY_CHANGED = 0x010,
    DBUS_SIGNAL_IDG1_PROPERTY_CHANGED        = 0x020,
    DBUS_SIGNAL_IDG1_INTERFACE_ADD           = 0x040,
    DBUS_SIGNAL_IDG1_INTERFACE_REMOVE        = 0x080,
    DBUS_SIGNAL_FREEDESKTOP_INTERFACE_ADD    = 0x100,
    DBUS_SIGNAL_FREEDESKTOP_INTERFACE_REMOVE = 0x200,
} dbus_cts_signal;

static pthread_mutex_t mtx         = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t  cond        = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t mtx2        = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t  cond2       = PTHREAD_COND_INITIALIZER;
unsigned int           filter_kret = DBUS_SIGNAL_UNKNOWN;
unsigned int           kret        = DBUS_SIGNAL_UNKNOWN;
unsigned int           aim_signal  = DBUS_SIGNAL_UNKNOWN;


typedef struct _ParseSignalData
{
    dbus_bool_t bool_value;
    bool        signal_has_bool_value;
    guchar      type_value;
    bool        signal_has_type_value;
    gint16      int16_value;
    bool        signal_has_int16_value;
    guint16     uint16_value;
    bool        signal_has_uint16_value;
    gint32      int32_value;
    bool        signal_has_int32_value;
    guint32     uint32_value;
    bool        signal_has_uint32_value;
    gint64      int64_value;
    bool        signal_has_int64_value;
    guint64     uint64_value;
    bool        signal_has_uint64_value;
    gdouble     double_value;
    bool        signal_has_double_value;
    gchar       *string_value;
    bool        signal_has_string_value;
    gchar       *objpath_value;
    bool        signal_has_objpath_value;
    gchar       *signature_value;
    bool        signal_has_signature_value;
} _ParseSignalData;
/*        guchar byte_value;
        bool signal_has_byte_value;
        gint32 int32_value;
        bool signal_has_int32_value;
        guint32 uint32_value;
        bool signal_has_uint32_value;*/


struct _ParseSignalData ParseSignalData;//={0,false,0,false,0,false};
struct DBusMessage      *thread_msg = NULL;


void clear_ParseSignalData(void)
{
    ParseSignalData.signal_has_bool_value      = false;
    ParseSignalData.signal_has_type_value      = false;
    ParseSignalData.signal_has_int16_value     = false;
    ParseSignalData.signal_has_uint16_value    = false;
    ParseSignalData.signal_has_int32_value     = false;
    ParseSignalData.signal_has_uint32_value    = false;
    ParseSignalData.signal_has_int64_value     = false;
    ParseSignalData.signal_has_uint64_value    = false;
    ParseSignalData.signal_has_double_value    = false;
    ParseSignalData.signal_has_string_value    = false;
    ParseSignalData.signal_has_objpath_value   = false;
    ParseSignalData.signal_has_signature_value = false;

    thread_msg = NULL;
/*	ParseSignalData.signal_has_byte_value = false;
        ParseSignalData.signal_has_int32_value = false;
        ParseSignalData.signal_has_uint32_value = false;*/
}

typedef struct
{
    GThread               *thread;
    GMainLoop             *thread_loop;
    guint                 signal_count;
    struct dbus_property  *dbus_property_list;
    struct dbus_interface *dbus_interface_list;
    struct dbus_object    *dbus_object_list;
} DeliveryData;


void ____g_properties_changed(GDBusProxy         *proxy,
                              GVariant           *changed_properties,
                              const gchar *const *invalidated_properties)
{
    dbus_printf("____g_properties_changed.....\n");
}


void ____g_signal(GDBusProxy  *proxy,
                  const gchar *sender_name,
                  const gchar *signal_name,
                  GVariant    *parameters)
{
    dbus_printf("____g_signal ......\n");
}


static void signal_handler(GDBusConnection *connection,
                           const gchar     *sender_name,
                           const gchar     *object_path,
                           const gchar     *interface_name,
                           const gchar     *signal_name,
                           GVariant        *parameters,
                           gpointer        user_data)
{
    DeliveryData *data = user_data;

    const gchar  *interface_name_for_signal;
    GVariant     *changed_properties;
    gchar        **invalidated_properties;
    GVariantIter iter;
    gchar        *key;
    GVariant     *value;

    dbus_printf("@@ signal handle \n");
    if (0 != g_strcmp0(data->dbus_object_list->name, object_path) && (g_strcmp0(signal_name, "PropertiesChanged") != 0))
    {
        dbus_printf("Error signal %s\n", signal_name);
        return;
    }
    if (g_variant_is_of_type(parameters, G_VARIANT_TYPE("(sa{sv}as)")))
    {
        g_variant_get(parameters,
                      "(&s@a{sv}^a&s)",
                      &interface_name_for_signal,
                      &changed_properties,
                      &invalidated_properties);

        g_variant_iter_init(&iter, changed_properties);
        while (g_variant_iter_next(&iter, "{sv}", &key, &value))
        {
            dbus_printf("%s \n", key);
            //if(g_strcmp0(key,data->dbus_property_list->name) == 0)
            //dbus_g_value_variant_get(dbus_interface_list, dbus_object_list, data->dbus_property_list,value);
        }
    }

    data->signal_count++;

    g_main_loop_quit(data->thread_loop);
}


static void dbus_1_message_append(GString         *s,
                                  guint           indent,
                                  DBusMessageIter *iter)
{
    gint            arg_type;
    DBusMessageIter sub;

    g_string_append_printf(s, "%*s", indent, "");

    arg_type = dbus_message_iter_get_arg_type(iter);
    switch (arg_type)
    {
    case DBUS_TYPE_BOOLEAN:
    {
        dbus_bool_t value;
        dbus_message_iter_get_basic(iter, &value);
        g_string_append_printf(s, "bool: %s\n", value ? "true" : "false");
        ParseSignalData.signal_has_bool_value = true;
        ParseSignalData.bool_value            = value;
        break;
    }

    case DBUS_TYPE_BYTE:
    {
        guchar value;
        dbus_message_iter_get_basic(iter, &value);
        g_string_append_printf(s, "byte: 0x%02x\n", (guint)value);
        break;
    }

    case DBUS_TYPE_INT16:
    {
        gint16 value;
        dbus_message_iter_get_basic(iter, &value);
        g_string_append_printf(s, "int16: %" G_GINT16_FORMAT "\n", value);
        break;
    }

    case DBUS_TYPE_UINT16:
    {
        guint16 value;
        dbus_message_iter_get_basic(iter, &value);
        g_string_append_printf(s, "uint16: %" G_GUINT16_FORMAT "\n", value);
        break;
    }

    case DBUS_TYPE_INT32:
    {
        gint32 value;
        dbus_message_iter_get_basic(iter, &value);
        g_string_append_printf(s, "int32: %" G_GINT32_FORMAT "\n", value);
        break;
    }

    case DBUS_TYPE_UINT32:
    {
        guint32 value;
        dbus_message_iter_get_basic(iter, &value);
        g_string_append_printf(s, "uint32: %" G_GUINT32_FORMAT "\n", value);
        break;
    }

    case DBUS_TYPE_INT64:
    {
        gint64 value;
        dbus_message_iter_get_basic(iter, &value);
        g_string_append_printf(s, "int64: %" G_GINT64_FORMAT "\n", value);
        break;
    }

    case DBUS_TYPE_UINT64:
    {
        guint64 value;
        dbus_message_iter_get_basic(iter, &value);
        g_string_append_printf(s, "uint64: %" G_GUINT64_FORMAT "\n", value);
        break;
    }

    case DBUS_TYPE_DOUBLE:
    {
        gdouble value;
        dbus_message_iter_get_basic(iter, &value);
        g_string_append_printf(s, "double: %f\n", value);
        break;
    }

    case DBUS_TYPE_STRING:
    {
        const gchar *value;
        dbus_message_iter_get_basic(iter, &value);
        g_string_append_printf(s, "string: '%s'\n", value);
        break;
    }

    case DBUS_TYPE_OBJECT_PATH:
    {
        const gchar *value;
        dbus_message_iter_get_basic(iter, &value);
        g_string_append_printf(s, "object_path: '%s'\n", value);
        break;
    }

    case DBUS_TYPE_SIGNATURE:
    {
        const gchar *value;
        dbus_message_iter_get_basic(iter, &value);
        g_string_append_printf(s, "signature: '%s'\n", value);
        break;
    }

    case DBUS_TYPE_VARIANT:
        g_string_append_printf(s, "variant:\n");
        dbus_message_iter_recurse(iter, &sub);
        while (dbus_message_iter_get_arg_type(&sub))
        {
            dbus_1_message_append(s, indent + 2, &sub);
            dbus_message_iter_next(&sub);
        }
        break;

    case DBUS_TYPE_ARRAY:
        g_string_append_printf(s, "array:\n");
        dbus_message_iter_recurse(iter, &sub);
        while (dbus_message_iter_get_arg_type(&sub))
        {
            dbus_1_message_append(s, indent + 2, &sub);
            dbus_message_iter_next(&sub);
        }
        break;

    case DBUS_TYPE_STRUCT:
        g_string_append_printf(s, "struct:\n");
        dbus_message_iter_recurse(iter, &sub);
        while (dbus_message_iter_get_arg_type(&sub))
        {
            dbus_1_message_append(s, indent + 2, &sub);
            dbus_message_iter_next(&sub);
        }
        break;

    case DBUS_TYPE_DICT_ENTRY:
        g_string_append_printf(s, "dict_entry:\n");
        dbus_message_iter_recurse(iter, &sub);
        while (dbus_message_iter_get_arg_type(&sub))
        {
            dbus_1_message_append(s, indent + 2, &sub);
            dbus_message_iter_next(&sub);
        }
        break;

    default:
        g_printerr("Error serializing D-Bus message to GVariant. Unsupported arg type '%c' (%d)",
                   arg_type,
                   arg_type);
        g_assert_not_reached();
        break;
    } /* switch */
} /* dbus_1_message_append */


static gchar *dbus_1_message_print(DBusMessage *message)
{
    GString         *s;
    guint           n;
    DBusMessageIter iter;

    s = g_string_new(NULL);
    n = 0;
    dbus_message_iter_init(message, &iter);
    while (dbus_message_iter_get_arg_type(&iter) != DBUS_TYPE_INVALID)
    {
        g_string_append_printf(s, "value %d: ", n);
        dbus_1_message_append(s, 2, &iter);
        dbus_message_iter_next(&iter);
        n++;
    }
    //dbus_printf("##%s\n",s);
    return(g_string_free(s, FALSE));
}


dbus_bool_t sigint_received = FALSE;


static void sigint_handler(int signum)
{
    dbus_printf("sigint_handler\n");
    sigint_received = TRUE;
}


static DBusHandlerResult monitor_filter_func(DBusConnection *connection,
                                             DBusMessage    *message,
                                             void           *user_data)
{
    if (dbus_message_is_signal(message, "com.ctc.igd1.Properties", "PropertiesChanged"))
    {
        dbus_printf("   Recv signal of igd1 PropertiesChanged\n");
        filter_kret = DBUS_SIGNAL_IDG1_PROPERTY_CHANGED;
        //thread_msg=message;
    }
    /*else if(dbus_message_is_signal(message,"org.freedesktop.DBus.Properties","PropertiesChanged")){
        filter_kret= DBUS_SIGNAL_FREEDESKTOP_PROPERTY_CHANGED;
            thread_msg=message;
       }*/
    else if (dbus_message_is_signal(message, "com.ctc.igd1.ObjectManager", "InterfacesAdded"))
    {
        dbus_printf("  Recv signal of igd1 interfaces add\n");
        filter_kret = DBUS_SIGNAL_IDG1_INTERFACE_ADD;
        //thread_msg=message;
    }
    else if (dbus_message_is_signal(message, "com.ctc.igd1.ObjectManager", "InterfacesRemoved"))
    {
        dbus_printf("  Recv signal of igd1 interfaces remove\n");

        filter_kret = DBUS_SIGNAL_IDG1_INTERFACE_REMOVE;
        //thread_msg=message;
    }

    else if (dbus_message_is_signal(message, "org.freedesktop.DBus.ObjectManager", "InterfacesAdded"))
    {
        dbus_printf("  Recv signal of freedesktop interfaces add\n");

        //filter_kret= DBUS_SIGNAL_FREEDESKTOP_INTERFACE_ADD;
        //thread_msg=message;
    }
    else if (dbus_message_is_signal(message, "org.freedesktop.DBus.ObjectManager", "InterfacesRemoved"))
    {
        dbus_printf("  Recv signal freedesttop of interfaces remove\n");

        //filter_kret= DBUS_SIGNAL_FREEDESKTOP_INTERFACE_REMOVE;
        //thread_msg=message;
    }

    if ((filter_kret & aim_signal) > 0)
    {
        thread_msg = message;
    }
    //else
    //dbus_printf("####listen kret=0x%x, but aim=0x%x use... thread_msg\n",filter_kret,aim_signal);
    //return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
    return(DBUS_HANDLER_RESULT_HANDLED);
} /* monitor_filter_func */


int listen_signal()
{
    DBusMessage               *msg;
    DBusMessageIter           arg;
    DBusConnection            *connection;
    DBusError                 err;
    int                       ret;
    char                      *sigvalue;
    DBusHandleMessageFunction filter_func = monitor_filter_func;


    dbus_error_init(&err);
    thread_msg = NULL;
    connection = dbus_bus_get(DBUS_BUS_SYSTEM, &err);
    if (dbus_error_is_set(&err))
    {
        fprintf(stderr, "ConnectionError %s\n", err.message);
        dbus_error_free(&err);
    }
    if (connection == NULL)
    {
        return(DBUS_SIGNAL_CANT_CONNECT);
    }

    ret = dbus_bus_request_name(connection, "com.ctc.igd1", DBUS_NAME_FLAG_REPLACE_EXISTING, &err);
    if (dbus_error_is_set(&err))
    {
        dbus_printf("Name Error%s\n", err.message);
        dbus_error_free(&err);
    }
    //if(ret !=DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER)
    //    return;

    dbus_bus_add_match(connection, "type='signal',interface='org.freedesktop.DBus'", &err);
    if (dbus_error_is_set(&err))
    {
        dbus_printf("org.freedesktop.DBus add match for signal Error%s\n", err.message);
        dbus_error_free(&err);
    }
    dbus_bus_add_match(connection, "type='signal',interface='com.ctc.igd1.Properties'", &err);
    if (dbus_error_is_set(&err))
    {
        dbus_printf("com.ctc.igd1.Properties add match for signal Error%s\n", err.message);
        dbus_error_free(&err);
    }
    dbus_bus_add_match(connection, "type='signal',interface='org.freedesktop.DBus.Properties'", &err);
    if (dbus_error_is_set(&err))
    {
        dbus_printf("org.freedesktop.Properties add match for signal Error%s\n", err.message);
        dbus_error_free(&err);
    }
    dbus_bus_add_match(connection, "type='signal',interface='com.ctc.igd1.ObjectManager'", &err);
    if (dbus_error_is_set(&err))
    {
        dbus_printf("com.ctc.igd1.ObjectManager add match for signal Error%s\n", err.message);
        dbus_error_free(&err);
    }
    dbus_bus_add_match(connection, "type='signal',interface='org.freedesktop.DBus.ObjectManager'", &err);
    if (dbus_error_is_set(&err))
    {
        dbus_printf("org.freedesktop.DBus.ObjectManager add match for signal Error%s\n", err.message);
        dbus_error_free(&err);
    }
    dbus_connection_flush(connection);

    if (!dbus_connection_add_filter(connection, filter_func, NULL, NULL))
    {
        dbus_printf("Notes: Couldn't add filter!\n");
        //exit (1);
    }
    //signal (SIGINT, sigint_handler);
    //int t=0;
    int t = wait_signal_with;
#if 1
    filter_kret = DBUS_SIGNAL_TIMEOUT;
    dbus_printf("	+Wait signal with %ds.Aim_signal=0x%x                    \n", (t), (aim_signal));
    int show_t = 0;
    while (dbus_connection_read_write_dispatch(connection, 0))
    //&& !sigint_received)
    {
        if (thread_msg)
        {
            break;
        }
        //dbus_printf("	+Wait signal for %ds                    \n",(8-t));
        if(show_t == 50 )
        {
            dbus_printf("	+Wait signal with %ds                    \n", (t));
            show_t = 0;
            t -= 5;
        }
        //t--;
        //if(t>8)
        if (t <= 0)
        {
            return(DBUS_SIGNAL_TIMEOUT);
        }

        //sleep(1);
        usleep(100000);
        show_t++;
        continue;
    }
    //sigint_received=FALSE;
    return(filter_kret);

#else
    //dbus_printf("	Wait signal for 8s\n");
    while (1)
    {
        dbus_connection_read_write(connection, 0);
        msg = dbus_connection_pop_message(connection);
        if (msg == NULL)
        {
            //system("echo \33[2A");
            dbus_printf("	Wait signal for %ds                    \n", (8 - t));
            t++;
            if (t > 8)
            {
                return(DBUS_SIGNAL_TIMEOUT);
            }
            sleep(1);
            continue;
        }
        //dbus_printf("now, check the signal\n");
        //if(dbus_message_is_signal(msg,"org.freedesktop.DBus.Properties","PropertiesChanged")){
        if (dbus_message_is_signal(msg, "com.ctc.igd1.Properties", "PropertiesChanged"))
        {
            /*if(!dbus_message_iter_init(msg,&arg))
                dbus_printf("MessageHas no Param\n");
               else if(dbus_message_iter_get_arg_type(&arg)!= DBUS_TYPE_STRING)
                dbus_printf("Param isnot string\n");
               else
                dbus_message_iter_get_basic(&arg,&sigvalue);
               dbus_printf("Got Singal withvalue : %s\n",sigvalue);*/
            /*sigvalue=dbus_1_message_print(msg);
               dbus_printf("--Got Singal withvalue : %s\n",sigvalue);*/
            thread_msg = msg;
            return(DBUS_SIGNAL_IDG1_PROPERTY_CHANGED);
        }
        else if (dbus_message_is_signal(msg, "org.freedesktop.DBus.Properties", "PropertiesChanged"))
        {
            /*if(!dbus_message_iter_init(msg,&arg))
                dbus_printf("MessageHas no Param\n");
               else if(dbus_message_iter_get_arg_type(&arg)!= DBUS_TYPE_STRING)
                dbus_printf("Param isnot string\n");
               else
                dbus_message_iter_get_basic(&arg,&sigvalue);
               dbus_printf("Got Singal withvalue : %s\n",sigvalue);*/
            /*sigvalue=dbus_1_message_print(msg);
               dbus_printf("--Got Singal withvalue : %s\n",sigvalue);*/
            thread_msg = msg;
            return(DBUS_SIGNAL_FREEDESKTOP_PROPERTY_CHANGED);
        }
        else if (dbus_message_is_signal(msg, "com.ctc.igd1.ObjectManager", "InterfacesAdded"))
        {
            if (!dbus_message_iter_init(msg, &arg))
            {
                dbus_printf("InterfacesAdded MessageHas no Param\n");
            }
            else if (dbus_message_iter_get_arg_type(&arg) != DBUS_TYPE_STRING)
            {
                dbus_printf("InterfacesAdded Param isnot string\n");
            }
            else
            {
                dbus_message_iter_get_basic(&arg, &sigvalue);
            }
            dbus_printf("igd1 InterfacesAdded Got Singal withvalue : %s\n", sigvalue);
            return(DBUS_SIGNAL_IDG1_INTERFACE_ADD);
        }
        else if (dbus_message_is_signal(msg, "com.ctc.igd1.ObjectManager", "InterfacesRemoved"))
        {
            if (!dbus_message_iter_init(msg, &arg))
            {
                dbus_printf("InterfacesRemoved MessageHas no Param\n");
            }
            else if (dbus_message_iter_get_arg_type(&arg) != DBUS_TYPE_STRING)
            {
                dbus_printf("InterfacesRemoved Param isnot string\n");
            }
            else
            {
                dbus_message_iter_get_basic(&arg, &sigvalue);
            }
            dbus_printf("igd1 InterfacesRemoved Got Singal withvalue : %s\n", sigvalue);
            return(DBUS_SIGNAL_IDG1_INTERFACE_REMOVE);
        }

        else if (dbus_message_is_signal(msg, "org.freedesktop.DBus.ObjectManager", "InterfacesAdded"))
        {
            if (!dbus_message_iter_init(msg, &arg))
            {
                dbus_printf("InterfacesAdded MessageHas no Param\n");
            }
            else if (dbus_message_iter_get_arg_type(&arg) != DBUS_TYPE_STRING)
            {
                dbus_printf("InterfacesAdded Param isnot string\n");
            }
            else
            {
                dbus_message_iter_get_basic(&arg, &sigvalue);
            }
            dbus_printf("freedestop InterfacesAdded Got Singal withvalue : %s\n", sigvalue);
            return(DBUS_SIGNAL_FREEDESKTOP_INTERFACE_ADD);
        }
        else if (dbus_message_is_signal(msg, "org.freedesktop.DBus.ObjectManager", "InterfacesRemoved"))
        {
            if (!dbus_message_iter_init(msg, &arg))
            {
                dbus_printf("InterfacesRemoved MessageHas no Param\n");
            }
            else if (dbus_message_iter_get_arg_type(&arg) != DBUS_TYPE_STRING)
            {
                dbus_printf("InterfacesRemoved Param isnot string\n");
            }
            else
            {
                dbus_message_iter_get_basic(&arg, &sigvalue);
            }
            dbus_printf("freedestop InterfacesRemoved Got Singal withvalue : %s\n", sigvalue);
            return(DBUS_SIGNAL_FREEDESKTOP_INTERFACE_REMOVE);
        }

        dbus_message_unref(msg);
    }//End of while
#endif
    return(DBUS_SIGNAL_UNKNOWN);
} /* listen_signal */

#if 1//PTHREAD_CHECK_SIGNAL


static void *thread_func(void *arg)
{
    //clear_ParseSignalData();
    int ret = listen_signal();

    pthread_mutex_lock(&mtx);
    kret = ret;
    pthread_mutex_unlock(&mtx);
    //dbus_printf("wake up main thread kret=%d\n",kret);
    pthread_cond_signal(&cond);

    return(0);
}
#endif


void remote_object_igd1_properties_signal(struct dbus_object *dbus_object_list, struct dbus_interface *dbus_interface_list, struct dbus_property *dbus_property_list)
{
    GDBusConnection       *bus;
    GDBusProxy            *remote_object;
    GVariant              *result;
    GError                *error = NULL;
    gint                  ret    = 0;
    GVariant              *value;

    struct timeval        start;
    struct timeval        end;
    guint                 elapsed_time = 0;
    struct listnode       *property_list_item_p;
    struct dbus_property  *property_p;
    struct dbus_interface *interface_p;

    sleep(1);
    GDBusConnection *connection;
    value = (GVariant *)dbus_g_variant_test_and_return_new(dbus_property_list, 0x01);
    //value = (GVariant*)dbus_g_variant_test_and_return_new(dbus_property_list);
    if (value == NULL)
    {
        dbus_printf("not test_value for signal test\n");
        return;
    }
    /***signal listen**/
    DeliveryData data;
    GMainLoop    *thread_loop;
    GMainContext *thread_context;
    thread_context = g_main_context_new();


    thread_loop       = g_main_loop_new(thread_context, FALSE);
    data.thread_loop  = thread_loop;
    data.thread       = g_thread_self();
    data.signal_count = 0;

    data.dbus_object_list = (struct dbus_object *)malloc(sizeof(struct dbus_object));
    if (!data.dbus_object_list)
    {
        dbus_printf("failed to alloc struct dbus_object memory\n");
        return;
    }
    memset(data.dbus_object_list, 0, sizeof(struct dbus_object));


    data.dbus_interface_list = (struct dbus_interface *)malloc(sizeof(struct dbus_interface));
    if (!data.dbus_interface_list)
    {
        dbus_printf("failed to alloc struct dbus_interface memory\n");
        return;
    }
    memset(data.dbus_interface_list, 0, sizeof(struct dbus_interface));

    data.dbus_property_list = (struct dbus_property *)malloc(sizeof(struct dbus_property));
    if (!data.dbus_property_list)
    {
        dbus_printf("failed to alloc struct dbus_interface memory\n");
        return;
    }

    memset(data.dbus_property_list, 0, sizeof(struct dbus_property));


    data.dbus_object_list    = dbus_object_list;
    data.dbus_interface_list = dbus_interface_list;
    data.dbus_property_list  = dbus_property_list;


    connection = g_bus_get_sync(G_BUS_TYPE_SYSTEM, NULL, &error);
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

    if (!bus)
    {
        dbus_printf("Couldn't connect to system  bus\n");
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
                                          "com.ctc.igd1.Properties", //"org.freedesktop.DBus.Properties",//
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
    DBusMessage *msg;

#if 0//___.... use gbus subscribe................
    ret = g_dbus_connection_signal_subscribe(bus,
                                             NULL,
                                             "org.freedesktop.DBus.Properties",     //dbus_interface_list->name,
                                             "PropertiesChanged",                   //NULL,//"PropertiesChanged",//NULL,
                                             "/com/ctc/igd1/Config/Peripheral/LED", //dbus_object_list->name,
                                             NULL,
                                             G_DBUS_SIGNAL_FLAGS_NONE,              //G_DBUS_SIGNAL_FLAGS_NO_MATCH_RULE,//G_DBUS_SIGNAL_FLAGS_NONE,
                                             &signal_handler,
                                             &data,
                                             NULL);
    /*************************/

//g_dbus_connection_flush(connection,NULL,NULL,NULL);
#endif

#if 1//PTHREAD_CHECK_SIGNAL
    pthread_t tid;
    int       i;
    aim_signal = DBUS_SIGNAL_IDG1_PROPERTY_CHANGED;
    pthread_create(&tid, NULL, thread_func, NULL);
    sleep(1);
#endif


    G_DBUS_PROXY_GET_CLASS(remote_object)->g_properties_changed = &____g_properties_changed;
    G_DBUS_PROXY_GET_CLASS(remote_object)->g_signal             = &____g_signal;
    result                                                      = g_dbus_proxy_call_sync(remote_object,
                                                                                         "Set",
                                                                                         g_variant_new("(ssv)", dbus_interface_list->name, dbus_property_list->name, value),
                                                                                         G_DBUS_CALL_FLAGS_NONE,
                                                                                         -1,
                                                                                         NULL,
                                                                                         &error);
    gettimeofday(&end, NULL);

    if (error)
    {
        dbus_cts_error_print(error);
        g_variant_unref(result);
        g_variant_unref(value);
        g_object_unref(G_OBJECT(remote_object));
        g_object_unref(bus);
        g_error_free(error);
        error = NULL;
        goto SET_ERROR;
    }
    elapsed_time = (end.tv_sec - start.tv_sec) * 1000000 +
                   (end.tv_usec - start.tv_usec);
    //dbus_printf("%s, Time :%d us\n",
    //                              (elapsed_time > 200000)?"FAILED":"OK",elapsed_time);


    g_object_unref(G_OBJECT(remote_object));
    g_object_unref(bus);

#if 1//PTHREAD_CHECK_SIGNAL
    pthread_cond_wait(&cond, &mtx);
    //pthread_mutex_lock(&mtx);
    //pthread_mutex_unlock(&mtx);
//dbus_printf("kill signal thread kret=%d\n",kret);
    if (kret == DBUS_SIGNAL_IDG1_PROPERTY_CHANGED)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name, "", "PropertiesChanged", "", "OK", "Check the PropertiesChanged signal", "check signal", "");
    }
    /*else if(kret == DBUS_SIGNAL_IDG1_INTERFACE_ADD )
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, "com.ctc.igd1.ObjectManager","" ,"","InterfacesAdded","","OK","","check signal","");
       else if(kret == DBUS_SIGNAL_IDG1_INTERFACE_REMOVE )
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, "com.ctc.igd1.ObjectManager","" ,"","InterfacesRemoved","","OK","","check signal","");
       else if(kret == DBUS_SIGNAL_FREEDESKTOP_INTERFACE_ADD )
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, "org.freedesktop.DBus.ObjectManager","" ,"","InterfacesAdded","","OK","","check signal","");
       else if(kret == DBUS_SIGNAL_FREEDESKTOP_INTERFACE_REMOVE )
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, "org.freedesktop.DBus.ObjectManager","" ,"","InterfacesRemoved","","OK","","check signal","");*/
    else if (kret == DBUS_SIGNAL_TIMEOUT)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s%d%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name, "", "PropertiesChanged", "", "Failed", "Wait signal more than ", wait_signal_with, "s", "check signal", "");
        dbus_object_list->test_result   |= NO_RECIVE_SIGNAL;
        dbus_property_list->test_result |= NO_RECIVE_SIGNAL;
    }
    else if (kret == DBUS_SIGNAL_FREEDESKTOP_PROPERTY_CHANGED)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name, "", "PropertiesChanged", "", "Failed", "Check the freedesktop PropertiesChanged signal", "check signal", "");
    }

    else
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name, "", "PropertiesChanged", "", "Failed", "Unknown error..", "check signal", "");
    }


    pthread_cancel(tid);
    pthread_join(tid, NULL);
#endif
    //g_main_loop_run (thread_loop);
SET_ERROR:
    g_object_unref(connection);
    g_main_loop_unref(thread_loop);
} /* remote_object_igd1_properties_signal */


void remote_object_normal_signal(struct dbus_object *dbus_object_list)
{
    pthread_t tid;
    int       i;

    aim_signal = DBUS_SIGNAL_FREEDESKTOP_PROPERTY_CHANGED | DBUS_SIGNAL_IDG1_PROPERTY_CHANGED | DBUS_SIGNAL_IDG1_INTERFACE_ADD | DBUS_SIGNAL_IDG1_INTERFACE_REMOVE | DBUS_SIGNAL_FREEDESKTOP_INTERFACE_ADD | DBUS_SIGNAL_FREEDESKTOP_INTERFACE_REMOVE;
    pthread_create(&tid, NULL, thread_func, NULL);
    sleep(1);

#if 1//PTHREAD_CHECK_SIGNAL
    pthread_cond_wait(&cond, &mtx);
    //pthread_mutex_lock(&mtx);
    //pthread_mutex_unlock(&mtx);

    if (kret == DBUS_SIGNAL_IDG1_INTERFACE_ADD)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, "com.ctc.igd1.ObjectManager", "", "", "InterfacesAdded", "", "OK", "Check the interface add signal", "check signal", "");
    }
    else if (kret == DBUS_SIGNAL_IDG1_INTERFACE_REMOVE)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, "com.ctc.igd1.ObjectManager", "", "", "InterfacesRemoved", "", "OK", "Check the interface remove signal", "check signal", "");
    }
    else if (kret == DBUS_SIGNAL_FREEDESKTOP_INTERFACE_ADD)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, "org.freedesktop.DBus.ObjectManager", "", "", "InterfacesAdded", "", "OK", "Check the interface add signal", "check signal", "");
    }
    else if (kret == DBUS_SIGNAL_FREEDESKTOP_INTERFACE_REMOVE)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, "org.freedesktop.DBus.ObjectManager", "", "", "InterfacesRemoved", "", "OK", "Check the interface remove signal", "check signal", "");
    }
    else if (kret == DBUS_SIGNAL_TIMEOUT)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s%d%s,%s,%s\n", dbus_object_list->name, "", "", "", "", "", "Failed", "Wait signal more than ", wait_signal_with, "s", "check signal", "");
        dbus_object_list->test_result |= NO_RECIVE_SIGNAL;
    }
    else
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%d\n", dbus_object_list->name, "", "", "", "", "", "Failed", "unknown reason", "check signal", kret);
        dbus_object_list->test_result |= NO_RECIVE_SIGNAL;
    }

    pthread_cancel(tid);
    pthread_join(tid, NULL);
#endif
} /* remote_object_normal_signal */


int remote_object_signal_Lookup(char *object_name, char *interface_name, char *property_name)
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
    struct listnode      *method_list_item_p;
    struct listnode      *arg_list_item_p;
    struct listnode      *signal_list_item_p;

    if (object_name == NULL)
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
    if (list_empty(&dbus_case_list))
    {
        dbus_printf("object case list is empty.\n");
        return(-1);
    }
    list_for_each(dbus_case_item_p, &dbus_case_list)
    {
        //set 在dbus_case_list中查找
        struct dbus_case *dbus_case_p;

        dbus_case_p = node_to_item(dbus_case_item_p, struct dbus_case, list);
        list_for_each(obj_list_item_p, &dbus_case_p->object_list)
        {
            //struct dbus_object *dbus_object_p;
            dbus_object_p = node_to_item(obj_list_item_p, struct dbus_object, list);
            if (g_strcmp0(dbus_object_p->name, dbus_object_list->name) == 0)
            {
                goto check_interface;
            }
            else if (dbus_object_list->form_name != NULL)
            {
                if (g_strcmp0(dbus_object_p->name, dbus_object_list->form_name) == 0)
                {
                    goto check_interface;
                }
                else
                {
                    continue;
                }
            }
            else
            {
                continue;
            }
check_interface:
            list_for_each(interface_list_item_p, &dbus_object_p->interface_list)
            {
                struct dbus_interface *interface_p = node_to_item(interface_list_item_p, struct dbus_interface, list);

                if (interface_p == NULL)
                {
                    continue;
                }
                if (interface_name != NULL)
                {
                    if ((g_strcmp0("org.freedesktop.DBus.ObjectManager", interface_name) == 0) || (g_strcmp0("com.ctc.igd1.ObjectManager", interface_name) == 0))
                    {
                        //Notes org.freedesktop.DBus.ObjectManager not in xml now. So use interface_name but not interface_p->name
                        remote_object_normal_signal(dbus_object_list);
                        return(0);
                    }
                    if (g_strcmp0(interface_p->name, interface_name) != 0)
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
                        if (property_name != NULL)
                        {
                            if (g_strcmp0(property_p->name, property_name) == 0)
                            {
                                remote_object_igd1_properties_signal(dbus_object_list, interface_p, property_p);
                                //Notes use dbus_object_list->name , Not dbus_object_p->name. For instance issue.
                                goto func_end;
                            }
                        }
                        else
                        {
                            remote_object_igd1_properties_signal(dbus_object_list, interface_p, property_p);
                            //Notes use dbus_object_list->name , Not dbus_object_p->name. For instance issue.
                        }
                    }
                }
            }
        }
    }

    //return -1;
func_end:
    return(0);
} /* remote_object_signal_Lookup */


#define ARG_NUM              20
#define METHOD_ARG_MAXNUM    5 //Parse less then 5 input parameter


void callback1(GDBusProxy   *proxy,
               GAsyncResult *res,
               gpointer     user_data)
{
}

#if 1
int igd1_Get_Set_or_Checksignal(struct dbus_object *dbus_object_list, struct dbus_interface *dbus_interface_list, struct dbus_property *dbus_property_list)
{
    dbus_object_list->test_result    &= (~UNPASS);
    dbus_interface_list->test_result &= (~UNPASS);
    dbus_property_list->test_result  &= (~UNPASS);
    if (!dbus_property_list->introspect_has_property)
    {
        dbus_printf("%s not pass introspect, so stop test\n", dbus_property_list->name);
        return(0);
    }
    if (g_strcmp0(dbus_property_list->access, "read") == 0)
    {
        dbus_printf("    access is read, just test Get\n");
        igd1_Get(dbus_object_list, dbus_interface_list, dbus_property_list);
        return(0);
    }
    if (!dbus_property_list->notification)
    {
        dbus_printf("    notification is n, just test Get and Set\n");
        //return 0;
    }
    else
    {
        dbus_printf("    Test Get and Set and Check nofification signal\n");
    }


    //Set method under "com.ctc.igd1.Properties"
    struct dbus_interface *dbus_interface_p;
    struct dbus_property  *property_p;
    dbus_interface_p = dbus_interface_list;
    property_p       = dbus_property_list;

    GDBusConnection *bus;
    GDBusProxy      *remote_object;
    GError          *error = NULL;
    GVariant        *Method_Get_Out;
    GVariant        *method_input_param;
    GVariant        *Set_value = NULL;
    struct timeval  start;
    struct timeval  end;
    guint           elapsed_time = 0;
    pthread_t       tid;

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

    method_input_param = g_variant_new(property_in_express, dbus_interface_p->name, property_p->name);

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
    Method_Get_Out = g_dbus_proxy_call_sync(remote_object,
                                            "Get",
                                            method_input_param,
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
        dbus_printf("%s\n", gstring->str);

        //dbus_cts_error_print(error);
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Get", "", "", "Failed", "Error when get", __func__, gstring->str);

        dbus_object_list->test_result   |= PROPERTY_CANT_GET_OR_GETALL;
        dbus_property_list->test_result |= PROPERTY_CANT_GET_OR_GETALL;
        g_string_free(gstring, TRUE);
        g_error_free(error);
        error = NULL;
        goto Get_error_out;
    }

    elapsed_time = (end.tv_sec - start.tv_sec) * 1000000 +
                   (end.tv_usec - start.tv_usec);

    //dbus_printf("%s, performace  is %s ,the perform time is %d us\n",
    //    dbus_object_list->name,(elapsed_time > 200000)?"FAILED":"OK",elapsed_time);

    //dbus_printf_twice("%s,%s,%s,%s,%s,%d(us),%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_p->name, property_p->name,"Get","",elapsed_time,(elapsed_time > 200000)?"Failed":"OK",(elapsed_time > 200000)?"Time out":"",__func__,"");

    g_variant_get(Method_Get_Out, "(v)", &info);
    if (!g_variant_is_of_type(info, G_VARIANT_TYPE(dbus_property_list->type)))
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s:%s but not:%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name, "", "", "", "Failed", "Type must be", dbus_property_list->type, g_variant_get_type_string(info), __func__, g_variant_get_type_string(info));

        dbus_object_list->test_result   |= PROPERTY_WRONG_TYPE;
        dbus_property_list->test_result |= PROPERTY_WRONG_TYPE;
        return;
    }

    if (0 == g_strcmp0(property_p->type, "s"))
    {
        g_variant_get(Method_Get_Out, "(v)", &info);
        g_variant_get(info, "s", &str_val);
        //dbus_printf ("property name : %s  , %s\n ",property_p->name,str_val);
        dbus_printf("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Get", "", "", "OK", "Get the value", __func__, str_val);
        dbus_printf_logfile("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Get", "", "", "OK", "Get the value", __func__, str_val);
        char *p = str_val;
        if (*p == '\0')
        {
            Set_value = g_variant_new_string("0");
            dbus_printf("For Set, change the value to 0\n");
        }
        else if (*p == '0')
        {
            *p        = '1';
            Set_value = g_variant_new_string(str_val);
            dbus_printf("For Set, change the value to %s\n", str_val);
        }
        else
        {
            *p        = '0';
            Set_value = g_variant_new_string(str_val);
            dbus_printf("For Set, change the value to %s\n", str_val);
        }
        //Notes: for % specail char
    }
    else if (0 == g_strcmp0(property_p->type, "o"))
    {
        g_variant_get(Method_Get_Out, "(v)", &info);
        g_variant_get(info, "o", &str_val);
        //dbus_printf ("property name : %s  , %s\n ",property_p->name,str_val);
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Get", "", "", "OK", "Get the value", __func__, str_val);

        Set_value = g_variant_new_object_path("/home/pub");
        dbus_printf("For Set, change the value to %s\n", "/home/pub");
    }
    else if (0 == g_strcmp0(property_p->type, "g"))
    {
        g_variant_get(Method_Get_Out, "(v)", &info);
        g_variant_get(info, "g", &str_val);
        //dbus_printf ("property name : %s  , %s\n ",property_p->name,str_val);
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Get", "", "", "OK", "Get the value", __func__, str_val);
        Set_value = g_variant_new_signature("www.189.cn");
        dbus_printf("For Set, change the value to %s\n", "www.189.cn");
    }
    else if (0 == g_strcmp0(property_p->type, "b"))
    {
        g_variant_get(Method_Get_Out, "(v)", &info);
        g_variant_get(info, "b", &bool_val);
        if (bool_val)
        {
            //dbus_printf ("property name : %s  , %d\n ",property_p->name,byte_val);
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,true\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Get", "", "", "OK", "Get the value", __func__);
        }
        else
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,false\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Get", "", "", "OK", "Get the value", __func__);
        }
        if (bool_val)
        {
            bool_val = false;
        }
        else
        {
            bool_val = true;
        }
        Set_value = g_variant_new_boolean(bool_val);
        if (bool_val)
        {
            dbus_printf("For Set, change the value to true\n");
        }
        else
        {
            dbus_printf("For Set, change the value to false\n");
        }
    }
    else if (0 == g_strcmp0(property_p->type, "y"))
    {
        g_variant_get(Method_Get_Out, "(v)", &info);
        g_variant_get(info, "y", &byte_val);
        //dbus_printf ("property name : %s  , %d\n ",property_p->name,byte_val);
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%d\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Get", "", "", "OK", "Get the value", __func__, byte_val);
        if (byte_val == '0')
        {
            byte_val = '1';
        }
        else
        {
            byte_val = '0';
        }
        Set_value = g_variant_new_byte(byte_val);
        dbus_printf("For Set, change the value to %d\n", byte_val);
    }
    else if (0 == g_strcmp0(property_p->type, "n"))
    {
        g_variant_get(Method_Get_Out, "(v)", &info);
        g_variant_get(info, "n", &int16_val);
        //dbus_printf ("property name : %s  , %d\n ",property_p->name,int16_val);
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%d\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Get", "", "", "OK", "Get the value", __func__, int16_val);
        if (int16_val == 0)
        {
            int16_val = 1;
        }
        else
        {
            int16_val = 0;
        }
        Set_value = g_variant_new_int16(int16_val);
        dbus_printf("For Set, change the value to %d\n", int16_val);
    }
    else if (0 == g_strcmp0(property_p->type, "q"))
    {
        g_variant_get(Method_Get_Out, "(v)", &info);
        g_variant_get(info, "q", &uint16_val);
        //dbus_printf ("property name : %s  , %d\n ",property_p->name,uint16_val);
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%d\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Get", "", "", "OK", "Get the value", __func__, uint16_val);
        if (uint16_val == 0)
        {
            uint16_val = 1;
        }
        else
        {
            uint16_val = 0;
        }
        Set_value = g_variant_new_uint16(uint16_val);
        dbus_printf("For Set, change the value to %d\n", uint16_val);
    }
    else if (0 == g_strcmp0(property_p->type, "i"))
    {
        g_variant_get(Method_Get_Out, "(v)", &info);
        g_variant_get(info, "i", &int32_val);
        //dbus_printf ("property name : %s  , %d\n ",property_p->name,int32_val);
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%d\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Get", "", "", "OK", "Get the value", __func__, int32_val);
        if (int32_val == 0)
        {
            int32_val = 1;
        }
        else
        {
            int32_val = 0;
        }
        Set_value = g_variant_new_int32(int32_val);
        dbus_printf("For Set, change the value to %d\n", int32_val);
    }
    else if (0 == g_strcmp0(property_p->type, "u"))
    {
        g_variant_get(Method_Get_Out, "(v)", &info);
        g_variant_get(info, "u", &uint32_val);
        //dbus_printf ("property name : %s  , %d\n ",property_p->name,uint32_val);
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%d\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Get", "", "", "OK", "Get the value", __func__, uint32_val);
        if (uint32_val == 0)
        {
            uint32_val = 1;
        }
        else
        {
            uint32_val = 0;
        }
        Set_value = g_variant_new_uint32(uint32_val);
        dbus_printf("For Set, change the value to %d\n", uint32_val);
    }
    else if (0 == g_strcmp0(property_p->type, "x"))
    {
        g_variant_get(Method_Get_Out, "(v)", &info);
        g_variant_get(info, "x", &int64_val);
        //dbus_printf ("property name : %s  , %lld\n ",property_p->name,int64_val);
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%lld\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Get", "", "", "OK", "Get the value", __func__, int64_val);
        if (int64_val == 0)
        {
            int64_val = 1;
        }
        else
        {
            int64_val = 0;
        }
        Set_value = g_variant_new_int64(int64_val);
        dbus_printf("For Set, change the value to %lld\n", int64_val);
    }
    else if (0 == g_strcmp0(property_p->type, "t"))
    {
        g_variant_get(Method_Get_Out, "(v)", &info);
        g_variant_get(info, "t", &uint64_val);
        //dbus_printf ("property name : %s  , %lld\n ",property_p->name,uint64_val);
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%lld\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Get", "", "", "OK", "Get the value", __func__, uint64_val);
        if (uint64_val == 0)
        {
            uint64_val = 1;
        }
        else
        {
            uint64_val = 0;
        }
        Set_value = g_variant_new_uint64(uint64_val);
        dbus_printf("For Set, change the value to %lld\n", uint64_val);
    }
    else if (0 == g_strcmp0(property_p->type, "h"))
    {
        g_variant_get(Method_Get_Out, "(v)", &info);
        g_variant_get(info, "h", &uint32_val);
        //dbus_printf ("property name : %s  , %d\n ",property_p->name,uint32_val);
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%d\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Get", "", "", "OK", "Get the value", __func__, uint32_val);
        if (uint32_val == 0)
        {
            uint32_val = 1;
        }
        else
        {
            uint32_val = 0;
        }
        Set_value = g_variant_new_uint32(uint32_val);
        dbus_printf("For Set, change the value to %d\n", uint32_val);
    }
    else if (0 == g_strcmp0(property_p->type, "d"))
    {
        g_variant_get(Method_Get_Out, "(v)", &info);
        g_variant_get(info, "d", &double_val);
        //dbus_printf ("property name : %s  , %lf\n ",property_p->name,double_val);
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%lf\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Get", "", "", "OK", "Get the value", __func__, double_val);
        if (double_val == 0)
        {
            double_val = 1;
        }
        else
        {
            double_val = 0;
        }
        Set_value = g_variant_new_double(double_val);
        dbus_printf("For Set, change the value to %lf\n", double_val);
    }
    else if (0 == g_strcmp0(property_p->type, "as"))
    {
        if (g_variant_is_of_type(Method_Get_Out, G_VARIANT_TYPE("(v)")))
        {
            GVariant        *wps_devparse_info = NULL;
            GVariantIter    *iter              = NULL;
            gchar           *parse_info        = NULL;

            GVariantBuilder *setmulti_builder;
            setmulti_builder = g_variant_builder_new(G_VARIANT_TYPE("as"));
            g_variant_get(Method_Get_Out, "(v)", &wps_devparse_info);
            g_variant_get(wps_devparse_info, "as", &iter);
            if (iter == NULL)
            {
                dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name, "", "", "", "OK", "Get the value", __func__, "");
            }

            while (g_variant_iter_next(iter, "s", &parse_info))
            {
                //dbus_printf("   Device Info: %s\n", parse_info);  //add your customizaition code
                dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name, "", "", "", "OK", "Get the value", __func__, parse_info);
                if (*parse_info == '\0')
                {
                    g_variant_builder_add(setmulti_builder, "s", "0");
                }
                else if (*parse_info == '0')
                {
                    *parse_info = '1';
                    g_variant_builder_add(setmulti_builder, "s", parse_info);
                }
                else
                {
                    *parse_info = '0';
                    g_variant_builder_add(setmulti_builder, "s", parse_info);
                }
                dbus_printf("For Set, change the value to %s\n", parse_info);
                g_free(parse_info);
            }
            Set_value = g_variant_builder_end(setmulti_builder);
            g_variant_builder_unref(setmulti_builder);
            g_variant_unref(wps_devparse_info);
            g_variant_iter_free(iter);
        }


#if 0
        {
            //g_variant_get(value, "(v)", &info);
            g_variant_get(info, "s", &str_val);
            if (str_val == NULL)
            {
                //dbus_printf("NULL....\n");
                dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name, "", "", "", "OK", "Get the value", __func__, "");
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
        //g_print ("result type = %s, %s\n", g_variant_get_type_string(Method_Get_Out), g_variant_print (Method_Get_Out, true));
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Get", "", "", "Failed", "property type no find    ", __func__, "");
        //g_variant_get(result, "s", &str_val);
        //dbus_printf ("type other = %s\n",(gchar *) str_val);
        dbus_object_list->test_result   |= PROPERTY_WRONG_TYPE;
        dbus_property_list->test_result |= PROPERTY_WRONG_TYPE;
        goto Get_end;
    }

    if (Set_value == NULL)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, "", "Set", "", "", "Failed", "No Set_value", __func__, "");
        dbus_object_list->test_result   |= PROPERTY_NO_VALUE;
        dbus_property_list->test_result |= PROPERTY_NO_VALUE;
        goto Get_end;
    }


    if (dbus_property_list->notification)
    {
        int i;
        aim_signal = DBUS_SIGNAL_IDG1_PROPERTY_CHANGED;
        pthread_create(&tid, NULL, thread_func, NULL);

        sleep(1);
    }


#if 1
    {
        //set method under "com.ctc.igd1.Properties"
        //struct listnode *interface_list_item_p;
        struct dbus_interface *dbus_interface_p;
        //struct listnode *property_list_item_p;
        struct dbus_property  *property_p;

        dbus_interface_p = dbus_interface_list;
        property_p       = dbus_property_list;
        GVariant        *set_value;
        GDBusConnection *bus;
        GDBusProxy      *remote_object;
        GError          *error = NULL;
        GVariant        *Method_Set_Out;
        GVariant        *method_input_param;
        struct timeval  start;
        struct timeval  end;
        guint           elapsed_time = 0;

        GCancellable    *cancellable;
        cancellable = g_cancellable_new();

        char property_in_express[ARG_NUM]     = "(ssv";
        char property_out_express[ARG_NUM]    = "(";
        void *property_in[METHOD_ARG_MAXNUM]  = { 0 };
        void *property_out[METHOD_ARG_MAXNUM] = { 0 };
        int  in_arg_num                       = 0;
        int  out_arg_num                      = 0;
        char *p_in                            = property_in_express + sizeof("(ssv") - 1;
        char *p_out                           = property_out_express + sizeof("(") - 1;

        /*set_value = dbus_g_variant_test_and_return_new(property_p, NULL);
           if(set_value==NULL)
           {
                dbus_printf("Not value  %s,%s,%s\n",dbus_object_list->name,dbus_interface_list->name,dbus_property_list->name);
                return -1;
           }*/

        set_value = Set_value;


        //g_variant_new("(ssv)", dbus_interface_list->name,dbus_property_list->name,value),
        strcpy(p_in, ")");
        p_in += 1;
        strcpy(p_out, ")");
        p_out += 1;
        *p_in  = '\0';
        *p_out = '\0';
        //dbus_printf("igd1 [set] the property [%s] type[%s] in [%s]@[%s]\n", property_p->name,property_p->type, dbus_object_list->name, dbus_interface_p->name);


        method_input_param = g_variant_new(property_in_express, dbus_interface_p->name, property_p->name, set_value);

#if 1
/*
   void      g_dbus_connection_call                              (GDBusConnection    *connection,
                                                               const gchar        *bus_name,
                                                               const gchar        *object_path,
                                                               const gchar        *interface_name,
                                                               const gchar        *method_name,
                                                               GVariant           *parameters,
                                                               const GVariantType *reply_type,
                                                               GDBusCallFlags      flags,
                                                               gint                timeout_msec,
                                                               GCancellable       *cancellable,
                                                               GAsyncReadyCallback callback,
                                                               gpointer            user_data);
   GLIB_AVAILABLE_IN_ALL
   GVariant *g_dbus_connection_call_finish                       (GDBusConnection    *connection,
                                                               GAsyncResult       *res,
                                                               GError            **error);
   GLIB_AVAILABLE_IN_ALL
   GVariant *g_dbus_connection_call_sync                         (GDBusConnection    *connection,
                                                               const gchar        *bus_name,
                                                               const gchar        *object_path,
                                                               const gchar        *interface_name,
                                                               const gchar        *method_name,
                                                               GVariant           *parameters,
                                                               const GVariantType *reply_type,
                                                               GDBusCallFlags      flags,
                                                               gint                timeout_msec,
                                                               GCancellable       *cancellable,
                                                               GError            **error);
 */

#if 1
//g_cancellable_is_cancelled
//g_dbus_is_member_name()
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
        gchar *user_data;
        user_data = NULL;

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
        //g_assert_no_error(error);
        g_dbus_proxy_call(remote_object, "Set", method_input_param, G_DBUS_CALL_FLAGS_NONE, -1, NULL, NULL, NULL);

#if 0   //M_SYNC
        Method_Set_Out = g_dbus_proxy_call_sync(remote_object,
                                                "Set",
                                                method_input_param,
                                                G_DBUS_CALL_FLAGS_NONE,
//G_DBUS_CALL_FLAGS_NO_AUTO_START,
                                                5000,
                                                cancellable,
                                                &error);
        //cancellable,//NULL,
        //(GAsyncReadyCallback)callback1,//&error//);
        //(void*)&user_data);
#endif
#else
        bus = g_bus_get_sync(G_BUS_TYPE_SYSTEM, NULL, NULL);

        gettimeofday(&start, NULL);
        Method_Set_Out = g_dbus_connection_call_sync(bus,
                                                     "com.ctc.igd1",            //"org.freedesktop.UPower",////
                                                     dbus_object_list->name,    //object path
                                                     "com.ctc.igd1.Properties", //"org.freedesktop.DBus.Properties", ////
                                                     "Set",
                                                     method_input_param,        //g_variant_new("(ss)", dbus_interface_list->name,dbus_property_list->name),
                                                     G_VARIANT_TYPE("()"),
                                                     G_DBUS_CALL_FLAGS_NONE,
                                                     5000,
                                                     cancellable,//NULL,
                                                     &error);
#endif

        gettimeofday(&end, NULL);

        if (error)
        {
            //dbus_cts_error_print(error);
            GString *gstring;
            gstring = g_string_new(" ");
            g_string_append_printf(gstring, "%s", error->message);
            dbus_printf("%s\n", gstring->str);

            //dbus_cts_error_print(error);
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Set", "", "", "Failed", "Error when set", __func__, gstring->str);
            dbus_object_list->test_result   |= PROPERTY_CANT_SET_OR_SETMULTI;
            dbus_property_list->test_result |= PROPERTY_CANT_SET_OR_SETMULTI;
            g_string_free(gstring, TRUE);
/*if(g_cancellable_is_cancelled(cancellable))
        dbus_printf("g_cancellable_is_cancelled......true \n");
   else
        dbus_printf("g_cancellable_is_cancelled......false \n");*/

            //g_cancellable_cancel (cancellable);
            //g_object_unref (cancellable);
//g_dbus_connection_call_finish(remote_object,NULL,&error);
            g_object_unref(G_OBJECT(remote_object));
            g_object_unref(bus);
            if (dbus_property_list->notification)
            {
                pthread_cancel(tid);
//			pthread_join(tid,NULL);
            }
            g_error_free(error);
            error = NULL;
            goto Get_end;
        }
#endif

        elapsed_time = (end.tv_sec - start.tv_sec) * 1000000 +
                       (end.tv_usec - start.tv_usec);

        //dbus_printf("%s, performace  is %s ,the perform time is %d us\n",
        //    dbus_object_list->name,(elapsed_time > 200000)?"FAILED":"OK",elapsed_time);


        dbus_printf_twice("%s,%s,%s,%s,%s,%d(us),%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Set", "", elapsed_time, (elapsed_time > 200000) ? "Failed" : "OK", (elapsed_time > 200000) ? "Time out when Set" : "Set the value not timeout", __func__, "");
        if (elapsed_time > 200000)
        {
            dbus_object_list->test_result   |= PROPERTY_GET_SET_TIMEOUT;
            dbus_property_list->test_result |= PROPERTY_GET_SET_TIMEOUT;
        }
        if (!dbus_property_list->notification)
        {
            sleep(2);
        }
#if 0   //M_SYNC
        g_variant_unref(Method_Set_Out);
#endif
        g_object_unref(G_OBJECT(remote_object));
        g_object_unref(bus);

        //return 0;
    }
#endif


    if (dbus_property_list->notification)
    {
        pthread_cond_wait(&cond, &mtx);
        //pthread_mutex_lock(&mtx);
        //pthread_mutex_unlock(&mtx);
        if (kret == DBUS_SIGNAL_FREEDESKTOP_PROPERTY_CHANGED)
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name, "", "PropertiesChanged", "", "Failed", "Receive org.freedesktop.DBus.Properties PropertiesChanged signal", __func__, "");
            //if(thread_msg!=NULL)
            //dbus_1_message_print(thread_msg);
        }
        else if (kret == DBUS_SIGNAL_IDG1_PROPERTY_CHANGED)
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name, "", "PropertiesChanged", "", "OK", "Receive the igd1 PropertiesChanged signal", __func__, "");
        }
        else if (kret == DBUS_SIGNAL_TIMEOUT)
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s%d%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name, "", "PropertiesChanged", "", "Failed", "Wait signal more than ", wait_signal_with, "s", __func__, "");
            dbus_object_list->test_result   |= NO_RECIVE_SIGNAL;
            dbus_property_list->test_result |= NO_RECIVE_SIGNAL;
        }
        else
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name, "", "PropertiesChanged", "", "Failed", "unknown", __func__, "");
        }

        pthread_cancel(tid);
        //pthread_join(tid,NULL);
    }


Get_end:
    g_variant_unref(Method_Get_Out);
Get_error_out:
    g_object_unref(G_OBJECT(remote_object));
    g_object_unref(bus);
    return(0);
} /* igd1_Get_Set_or_Checksignal */
#endif

int igd1_Set_Checksignal_CheckGet(struct dbus_object *dbus_object_list, struct dbus_interface *dbus_interface_list, struct dbus_property *dbus_property_list, int Want_Set)
{
    EXIT_IF_NULL(dbus_object_list);
    EXIT_IF_NULL(dbus_object_list->name);
    EXIT_IF_NULL(dbus_interface_list);
    EXIT_IF_NULL(dbus_interface_list->name);
    EXIT_IF_NULL(dbus_property_list);
    EXIT_IF_NULL(dbus_property_list->name);

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
    if (dbus_property_list == NULL)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "unknown", "", "", "", "Failed", "dbus_property is NULL", __func__, "NULL point Error");
        return(-1);
    }
    if (dbus_property_list->name == NULL)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "unknown", "", "", "", "Failed", "dbus_property->name is NULL", __func__, "NULL point Error");
        return(-1);
    }


    dbus_object_list->test_result    &= (~UNPASS);
    dbus_interface_list->test_result &= (~UNPASS);
    dbus_property_list->test_result  &= (~UNPASS);


    dbus_printf("  igd1[Set or SCC] %s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name);


    if (redundancy)
    {
        sleep(1);
    }
    //Want_Set, choose test_value or test_value2.
    //if Want_Set==0, check Get value to decide the set_value*
    if ((DBUS_CMD_ALL == run_args) || (DBUS_CMD_ALL_BY_STEP == run_args) || open_tag_about_test_all)
    {
        if (g_strcmp0(dbus_interface_list->name, "com.ctc.igd1.DHCPServer") == 0 && g_strcmp0(dbus_property_list->name, "IPAddr") == 0)
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name, "", "", "", "OK", "", __func__, "Don't Set com.ctc.igd1.DHCPServer.IPAddr");
            return(0);
        }
    }
    if (g_strcmp0(dbus_property_list->access, "read") == 0)
    {
        //dbus_printf("\n      %s access is read, just test Get\n",dbus_property_list->name);
        dbus_printf("\n      %s access is read, Don't deal the Set test\n", dbus_property_list->name);
        //igd1_Get(dbus_object_list, dbus_interface_list, dbus_property_list);
        return(0);
    }
    if (g_strcmp0(dbus_property_list->name, "ControlCycle") == 0)
    {
        dbus_printf("\n      %s.ControlCycle only can set Day, don't test notification\n", dbus_interface_list->name);
        dbus_property_list->notification = false;
    }

    if (check_notification)
    {
        if (!dbus_property_list->notification)
        {
            dbus_printf("\n      %s notification is n, just test Set , and Get again to compare\n", dbus_property_list->name);
            //return 0;
        }
        else
        {
            dbus_printf("\n      %s Test Set and Check nofification signal, and Get again to compare\n", dbus_property_list->name);
        }
    }
    //Set method under "com.ctc.igd1.Properties"
    struct dbus_interface *dbus_interface_p;
    struct dbus_property  *property_p;
    dbus_interface_p = dbus_interface_list;
    property_p       = dbus_property_list;

    GDBusConnection *bus;
    GDBusProxy      *remote_object;
    GError          *error = NULL;
    GVariant        *Method_Get_Out;
    GVariant        *Method_Get_Out2;
    GVariant        *Get_input_param;
    GVariant        *Get_input_param2;
    GVariant        *Set_input_param;
    GVariant        *Set_value           = NULL;
    GVariant        *Check_Variant_value = NULL;
    struct timeval  start;
    struct timeval  end;
    guint           elapsed_time = 0;
    pthread_t       tid;

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

    //dbus_printf("igd1 %s[SCC] the property [%s] type[%s] in [%s]@[%s]\n", property_in_express, property_p->name,property_p->type, dbus_object_list->name, dbus_interface_p->name);

    //Get_input_param=g_variant_new(property_in_express, dbus_interface_p->name, property_p->name);
    Get_input_param = g_variant_new("(ss)", dbus_interface_p->name, property_p->name);
    EXIT_IF_NULL(Get_input_param);
    if (Get_input_param == NULL)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name, "", "", "", "Failed", "Get_input_param is NULL", __func__, "NULL point Error");
        dbus_object_list->test_result   |= NULL_PARAM;
        dbus_property_list->test_result |= NULL_PARAM;
        return(-1);
    }


    bus = g_bus_get_sync(G_BUS_TYPE_SYSTEM, NULL, &error);
    EXIT_IF_NULL(bus);
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
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name, "", "", "", "Failed", "bus is NULL", __func__, "NULL point Error after g_bus_get_sync");
        dbus_object_list->test_result   |= CONNECTION_NULL;
        dbus_property_list->test_result |= CONNECTION_NULL;
        //return(-1);
        //liuxy 0922-001 :need free Get_input_param
        goto Get_connect_error;
    }
    //g_assert_no_error(error);
    if (lib_debug)
    {
        dbus_printf(" Into g_dbus_proxy_new_sync line %d \n", __LINE__);
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
                                          "com.ctc.igd1.Properties",
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
    //g_assert_no_error(error);

    EXIT_IF_NULL(remote_object);
    if (remote_object == NULL)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name, "", "", "", "Failed", "remote_object is NULL", __func__, "NULL point Error after g_dbus_proxy_new_sync");
        dbus_object_list->test_result   |= CONNECTION_NULL;
        dbus_property_list->test_result |= CONNECTION_NULL;

        //return(-1);
        //liuxy 0922-001 : need free Get_input_param and bus
        goto Get_proxy_error;
    }
    if (Get_input_param != NULL)
    {
        gchar *s;
        dbus_printf("First to Get_input_param :\n");
        //liuxy 0922-001 : need free return value of g_variant_print
        s = g_variant_print(Get_input_param, true);
        //dbus_printf("                         %s\n", g_variant_print(Get_input_param, true));
        dbus_printf("                         %s\n", s);
        g_free(s);
        dbus_printf("First to Get_input_param....type %s\n", g_variant_get_type_string(Get_input_param));
    }
    else
    {
        dbus_printf("First to Get_input_param is NULL. exit.\n");
        exit(0);
    }
    gettimeofday(&start, NULL);

    if (lib_debug)
    {
        dbus_printf(" Into g_dbus_proxy_call_sync line %d \n", __LINE__);
    }
    Method_Get_Out = g_dbus_proxy_call_sync(remote_object,
                                            "Get",
                                            Get_input_param,
                                            G_DBUS_CALL_FLAGS_NONE,
                                            -1,
                                            NULL,
                                            &error);
    gettimeofday(&end, NULL);

    EXIT_IF_NULL(Method_Get_Out);
    if (lib_debug)
    {
        dbus_printf(" Out g_dbus_proxy_call_sync line %d \n", __LINE__);
    }
    /*if (Method_Get_Out == NULL)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name, "", "", "", "Failed", "Method_Get_Out is NULL", __func__, "NULL point Error after g_dbus_proxy_call_sync");
        dbus_object_list->test_result   |= NULL_OBJECT_BY_METHOD_CALL;
        dbus_property_list->test_result |= NULL_OBJECT_BY_METHOD_CALL;

        return(-1);
    }*/
    if (error)
    {
        GString *gstring;
        gstring = g_string_new(" ");
        g_string_append_printf(gstring, "%s", error->message);
        dbus_printf("%s\n", gstring->str);

        //dbus_cts_error_print(error);
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Get", "", "", "Failed", "Error when get", __func__, gstring->str);
        dbus_object_list->test_result   |= PROPERTY_CANT_GET_OR_GETALL;
        dbus_property_list->test_result |= PROPERTY_CANT_GET_OR_GETALL;
        g_string_free(gstring, TRUE);

        //g_variant_unref (Get_input_param);
        g_error_free(error);
        error = NULL;
        //goto Get_error_out;
    }
    if (Method_Get_Out == NULL)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name, "", "", "", "Failed", "Method_Get_Out is NULL", __func__, "NULL point Error after g_dbus_proxy_call_sync");
        dbus_object_list->test_result   |= NULL_OBJECT_BY_METHOD_CALL;
        dbus_property_list->test_result |= NULL_OBJECT_BY_METHOD_CALL;

        //return(-1);
        //liuxy 0922-001 : need free bus and remote_object,Get_input_param is consumed.
        goto Get_call_get_method_error;
    }
    elapsed_time = (end.tv_sec - start.tv_sec) * 1000000 +
                   (end.tv_usec - start.tv_usec);

    //dbus_printf("%s, performace  is %s ,the perform time is %d us\n",
    //    dbus_object_list->name,(elapsed_time > 200000)?"FAILED":"OK",elapsed_time);

    //dbus_printf_twice("%s,%s,%s,%s,%s,%d(us),%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_p->name, property_p->name,"Get","",elapsed_time,(elapsed_time > 200000)?"Failed":"OK",(elapsed_time > 200000)?"Time out":"Get single the value not timeout",__func__,"");

    if (in_parallel_test)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%d(us),%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Get", "", elapsed_time, "Human judge", "Get the value for Set", __func__, "");
    }

    g_variant_get(Method_Get_Out, "(v)", &info);
    if (!g_variant_is_of_type(info, G_VARIANT_TYPE(dbus_property_list->type)))
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s:%s but not:%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name, "", "", "", "Failed", "Type must be", dbus_property_list->type, g_variant_get_type_string(info), __func__, g_variant_get_type_string(info));
        dbus_object_list->test_result   |= PROPERTY_WRONG_TYPE;
        dbus_property_list->test_result |= PROPERTY_WRONG_TYPE;

        //return;
        //liuxy 0922-001 : need free bus and remote_object and Method_Get_Out.
        goto Get_call_get_method_out_error;
    }


    Set_value = (GVariant *)dbus_g_variant_test_and_return_new(dbus_property_list, 0x01);
    if (Set_value == NULL)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, dbus_property_list->name, "Set", "", "", "Failed", "No Set_value", __func__, "");
        dbus_object_list->test_result   |= PROPERTY_NO_VALUE;
        dbus_property_list->test_result |= PROPERTY_NO_VALUE;

        //goto Get_end;
        //liuxy 0922-001 : need free bus and remote_object and Method_Get_Out.
        goto Get_call_get_method_out_error;
    }
    else
    {
        gchar *s;
        s = g_variant_print(Set_value, true);
        dbus_printf("#The Set_value: %s .line = %d\n", s,__LINE__);
        dbus_printf("Set_value....type %s\n", g_variant_get_type_string(Set_value));
        g_free(s);
    }
    g_variant_ref(Set_value);    //Add count
    //liuxy 0922-001 : Set_value is consumed one time by g_variant_new() here.
    Check_Variant_value                         = g_variant_new("(v)", Set_value);
    dbus_property_list->case_property_set_value = 1;
    {
        gchar *s,*s1;
        s = g_variant_print(Method_Get_Out, true);
        s1 = g_variant_print(Check_Variant_value, true);
        //dbus_printf("#The Current value: %s\n", g_variant_print(Method_Get_Out, true));
        //dbus_printf("#The test_value: %s\n", g_variant_print(Check_Variant_value, true));
        dbus_printf("#The Current value: %s\n", s);
        dbus_printf("#The test_value: %s\n", s1);
        g_free(s);
        g_free(s1);
        dbus_printf("Check_Variant_value....type %s\n", g_variant_get_type_string(Check_Variant_value));
        dbus_printf("Method_Get_Out....type %s\n", g_variant_get_type_string(Method_Get_Out));
    }
    if ((g_variant_equal(Check_Variant_value, Method_Get_Out)) || (Want_Set == 2))
    {
        if (Want_Set == 2)
        {
            dbus_printf("Not check current value. Only Set test_value2\n");
        }
        else
        {
            dbus_printf("Current value equal to test_value. So Set test_value2\n");
        }
        g_variant_unref(Check_Variant_value);
        g_variant_unref(Set_value);
        Set_value = (GVariant *)dbus_g_variant_test_and_return_new(dbus_property_list, 0x02);

        if (Set_value == NULL)
        {
            dbus_property_list->case_property_set_value = 0;

            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, dbus_property_list->name, "Set", "", "", "Failed", "No Set_value2", __func__, "");
            dbus_object_list->test_result   |= PROPERTY_NO_VALUE;
            dbus_property_list->test_result |= PROPERTY_NO_VALUE;

            //goto Get_end;
            //liuxy 0922-001 : need free bus and remote_object and Method_Get_Out
            goto Get_call_get_method_out_error;
        }
        g_variant_ref(Set_value);        //Add count
        //liuxy 0922-001 : Set_value is consumed one time by g_variant_new() here.
        Check_Variant_value = g_variant_new("(v)", Set_value);
        {
            gchar *s;
            s = g_variant_print(Check_Variant_value, true);
            //dbus_printf("#The test_value2: %s\n", g_variant_print(Check_Variant_value, true));
            dbus_printf("#The test_value2: %s\n", s);
            g_free(s);
        }
        dbus_property_list->case_property_set_value = 2;
    }
    else
    {
        dbus_printf("Current value not equal to test_value. So Set test_value\n");
    }


    if (redundancy)
    {
        sleep(1);
    }

    if (check_notification)
    {
        if (dbus_property_list->notification)
        {
            int i;
            aim_signal = DBUS_SIGNAL_IDG1_PROPERTY_CHANGED;
            pthread_create(&tid, NULL, thread_func, NULL);
            sleep(1);
        }
    }

#if 1
    {
        //set method under "com.ctc.igd1.Properties"
        //struct listnode *interface_list_item_p;
        struct dbus_interface *dbus_interface_p;
        //struct listnode *property_list_item_p;
        struct dbus_property  *property_p;

        dbus_interface_p = dbus_interface_list;
        property_p       = dbus_property_list;
        GVariant        *set_value;
        //GDBusConnection *bus;
        //GDBusProxy      *Set_remote_object;
        GError          *error = NULL;
        GVariant        *Method_Set_Out;
        GVariant        *method_input_param;
        struct timeval  start;
        struct timeval  end;
        guint           elapsed_time = 0;

        //GCancellable *cancellable;
        //cancellable = g_cancellable_new ();

        char property_in_express[ARG_NUM]     = "(ssv";
        char property_out_express[ARG_NUM]    = "(";
        void *property_in[METHOD_ARG_MAXNUM]  = { 0 };
        void *property_out[METHOD_ARG_MAXNUM] = { 0 };
        int  in_arg_num                       = 0;
        int  out_arg_num                      = 0;
        char *p_in                            = property_in_express + sizeof("(ssv") - 1;
        char *p_out                           = property_out_express + sizeof("(") - 1;

        /*set_value = dbus_g_variant_test_and_return_new(property_p, NULL);
           if(set_value==NULL)
           {
                dbus_printf("Not value  %s,%s,%s\n",dbus_object_list->name,dbus_interface_list->name,dbus_property_list->name);
                return -1;
           }*/

        //set_value = Set_valuefalse;//Method_Get_Out;
        //set_value = Check_Variant_value;//Method_Get_Out;
        //set_value = Set_value;//Method_Get_Out;


        //g_variant_new("(ssv)", dbus_interface_list->name,dbus_property_list->name,value),
        strcpy(p_in, ")");
        p_in += 1;
        strcpy(p_out, ")");
        p_out += 1;
        *p_in  = '\0';
        *p_out = '\0';
        //dbus_printf("igd1 [set] the property [%s] type[%s] in [%s]@[%s]\n", property_p->name,property_p->type, dbus_object_list->name, dbus_interface_p->name);


        //Set_input_param=g_variant_new(property_in_express, dbus_interface_p->name, property_p->name, set_value);
        Set_input_param = g_variant_new("(ssv)", dbus_interface_p->name, property_p->name, Set_value);
        if (Set_input_param != NULL)
        {
            gchar *s = NULL;
            s = g_variant_print(Set_input_param, true);
            dbus_printf("Set_input_param %s\n", s);
            g_free(s);
            dbus_printf("Set_input_param....type %s\n", g_variant_get_type_string(Set_input_param));
        }
        else
        {
            dbus_printf("Set_input_param is NULL. exit.\n");
            exit(0);
        }

#if 1
/*
   void      g_dbus_connection_call                              (GDBusConnection    *connection,
                                                               const gchar        *bus_name,
                                                               const gchar        *object_path,
                                                               const gchar        *interface_name,
                                                               const gchar        *method_name,
                                                               GVariant           *parameters,
                                                               const GVariantType *reply_type,
                                                               GDBusCallFlags      flags,
                                                               gint                timeout_msec,
                                                               GCancellable       *cancellable,
                                                               GAsyncReadyCallback callback,
                                                               gpointer            user_data);
   GLIB_AVAILABLE_IN_ALL
   GVariant *g_dbus_connection_call_finish                       (GDBusConnection    *connection,
                                                               GAsyncResult       *res,
                                                               GError            **error);
   GLIB_AVAILABLE_IN_ALL
   GVariant *g_dbus_connection_call_sync                         (GDBusConnection    *connection,
                                                               const gchar        *bus_name,
                                                               const gchar        *object_path,
                                                               const gchar        *interface_name,
                                                               const gchar        *method_name,
                                                               GVariant           *parameters,
                                                               const GVariantType *reply_type,
                                                               GDBusCallFlags      flags,
                                                               gint                timeout_msec,
                                                               GCancellable       *cancellable,
                                                               GError            **error);
 */

#if 1
//g_cancellable_is_cancelled
//g_dbus_is_member_name()
        //liuxy 0922-001 : don't get g_bus connect and proxy again.
        /*
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
        gchar *user_data;
        user_data = NULL;
        //GAsyncReadyCallback callback;
        if (lib_debug)
        {
            dbus_printf(" Into g_dbus_proxy_new_sync line %d \n", __LINE__);
        }
        */
        /*
        service_name = igd1_service;
        if(dbus_object_list->name != NULL)
            if(strcmp(dbus_object_list->name,"/com/ctc/saf1") == 0)
                service_name = freedesktop_service;

        Set_remote_object = g_dbus_proxy_new_sync(bus,
                                                  G_DBUS_PROXY_FLAGS_NONE,
                                                  NULL,
                                                  service_name,
                                                  dbus_object_list->name,
                                                  "com.ctc.igd1.Properties",
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
        */

        //liuxy 0922-001 : has been checked before.
        /*
        if (Set_input_param != NULL)
        {
            gchar *s = NULL;
            s = g_variant_print(Set_input_param, true);
            dbus_printf("Set_input_param %s\n", g_variant_print(Set_input_param, true));
            dbus_printf("Set_input_param %s\n", s);
            g_free(s);
            dbus_printf("Set_input_param....type %s\n", g_variant_get_type_string(Set_input_param));
        }
        else
        {
            dbus_printf("Set_input_param is NULL. exit.\n");
            exit(0);
        }
        */
        //liuxy 0922-001 : use g_dbus_proxy_call_sync instead of g_dbus_proxy_call and sleep here.
        sleep(1);
        gettimeofday(&start, NULL);
        //g_assert_no_error(error);
        if (lib_debug)
        {
            dbus_printf(" Into g_dbus_proxy_call %d \n", __LINE__);
        }
        //g_dbus_proxy_call(Set_remote_object, "Set", Set_input_param, G_DBUS_CALL_FLAGS_NONE, -1, NULL, NULL, NULL);
        Method_Set_Out = g_dbus_proxy_call_sync(remote_object,
                                            "Set",
                                            Set_input_param,
                                            G_DBUS_CALL_FLAGS_NONE,
                                            -1,
                                            NULL,
                                            &error);
        
        gettimeofday(&end, NULL);
        if (lib_debug)
        {
            dbus_printf(" Out g_dbus_proxy_call %d \n", __LINE__);
        }

#if 0   //M_SYNC
        Method_Set_Out = g_dbus_proxy_call_sync(Set_remote_object,
                                                "Set",
                                                method_input_param,
                                                G_DBUS_CALL_FLAGS_NONE,
//G_DBUS_CALL_FLAGS_NO_AUTO_START,
                                                5000,
                                                cancellable,
                                                &error);
        //cancellable,//NULL,
        //(GAsyncReadyCallback)callback1,//&error//);
        //(void*)&user_data);
#endif
#else
        bus = g_bus_get_sync(G_BUS_TYPE_SYSTEM, NULL, NULL);

        gettimeofday(&start, NULL);
        Method_Set_Out = g_dbus_connection_call_sync(bus,
                                                     "com.ctc.igd1",            //"org.freedesktop.UPower",////
                                                     dbus_object_list->name,    //object path
                                                     "com.ctc.igd1.Properties", //"org.freedesktop.DBus.Properties", ////
                                                     "Set",
                                                     method_input_param,        //g_variant_new("(ss)", dbus_interface_list->name,dbus_property_list->name),
                                                     G_VARIANT_TYPE("()"),
                                                     G_DBUS_CALL_FLAGS_NONE,
                                                     5000,
                                                     cancellable,//NULL,
                                                     &error);
#endif


        if (error)
        {
            //dbus_cts_error_print(error);
            GString *gstring;
            gstring = g_string_new(" ");
            g_string_append_printf(gstring, "%s", error->message);
            dbus_printf("%s\n", gstring->str);

            //dbus_cts_error_print(error);
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Set", "", "", "Failed", "Error when set", __func__, gstring->str);
            dbus_object_list->test_result   |= PROPERTY_CANT_SET_OR_SETMULTI;
            dbus_property_list->test_result |= PROPERTY_CANT_SET_OR_SETMULTI;
            g_string_free(gstring, TRUE);

/*if(g_cancellable_is_cancelled(cancellable))
        dbus_printf("g_cancellable_is_cancelled......true \n");
   else
        dbus_printf("g_cancellable_is_cancelled......false \n");*/

            //g_cancellable_cancel (cancellable);
            //g_object_unref (cancellable);
//g_dbus_connection_call_finish(Set_remote_object,NULL,&error);
            //liuxy 0922-001 : don't free here.
            //g_object_unref(G_OBJECT(Set_remote_object));
            //g_object_unref(bus);
            //liuxy 0922-001 : check (check_notification == true).
            if ((check_notification == true)&&(dbus_property_list->notification))
            {
                pthread_cancel(tid);
//			pthread_join(tid,NULL);
            }
            g_error_free(error);
            error = NULL;
            //goto Set_end;
        }
#endif
        if (Method_Set_Out == NULL)
        {
            //liuxy 0922-001 : in set part,Set_input_param is consumed.
            goto Set_call_set_method_error;
        }

        elapsed_time = (end.tv_sec - start.tv_sec) * 1000000 +
                       (end.tv_usec - start.tv_usec);

        //dbus_printf("%s, performace  is %s ,the perform time is %d us\n",
        //    dbus_object_list->name,(elapsed_time > 200000)?"FAILED":"OK",elapsed_time);


        if (in_parallel_test)
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%d(us),%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, dbus_property_list->name, "Set", "", elapsed_time, "Human judge", "Set the value ", __func__, "");
        }
        else
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%d(us),%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, dbus_property_list->name, "Set", "", elapsed_time, (elapsed_time > 200000) ? "Failed" : "OK", (elapsed_time > 200000) ? "Time out when Set" : "Set the value not timeout", __func__, "");
        }
        if (elapsed_time > 200000)
        {
            dbus_object_list->test_result   |= PROPERTY_GET_SET_TIMEOUT;
            dbus_property_list->test_result |= PROPERTY_GET_SET_TIMEOUT;
        }
        if (check_notification)
        {
            if (!dbus_property_list->notification)
            {
                sleep(2);
            }
        }
#if 0   //M_SYNC
        g_variant_unref(Method_Set_Out);
#endif

        //g_dbus_connection_close_sync(bus,NULL,NULL);
        //Can't close.... segmentation fault
        //liuxy 0922-001 : don't free here.
        //g_object_unref(G_OBJECT(Set_remote_object));
        //g_object_unref(bus);
        //liuxy 0922-001 : in set part,need free Method_Set_Out of the set part.
        g_variant_unref(Method_Set_Out);

        //return 0;
    }
#endif

    if (check_notification)
    {
        if (dbus_property_list->notification)
        {
            pthread_cond_wait(&cond, &mtx);
            //pthread_mutex_lock(&mtx);
            //pthread_mutex_unlock(&mtx);
            if (kret == DBUS_SIGNAL_FREEDESKTOP_PROPERTY_CHANGED)
            {
                dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name, "", "PropertiesChanged", "", "Failed", "Receive org.freedesktop.DBus.Properties PropertiesChanged signal", __func__, "");
                //if(thread_msg!=NULL)
                //dbus_1_message_print(thread_msg);
            }
            else if (kret == DBUS_SIGNAL_IDG1_PROPERTY_CHANGED)
            {
                dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name, "", "PropertiesChanged", "", "OK", "Receive the igd1 PropertiesChanged signal", __func__, "");
            }
            else if (kret == DBUS_SIGNAL_TIMEOUT)
            {
                dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s%d%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name, "", "PropertiesChanged", "", "Failed", "Wait signal more than ", wait_signal_with, "s", __func__, "");
                dbus_object_list->test_result   |= NO_RECIVE_SIGNAL;
                dbus_property_list->test_result |= NO_RECIVE_SIGNAL;
            }
            else
            {
                dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name, "", "PropertiesChanged", "", "Failed", "unknown", __func__, "");
            }

            pthread_cancel(tid);
            //pthread_join(tid,NULL);
        }
        else
        {
            /*dbus_printf("Wait 2s to sync Set\n");
               sleep(2);//for sync Set*/
        }
    }

    //if(!check_Get_in_SCC)
    //	goto Set_end;
#if 1 //Not check Get for Set
    if (Quick_Get)
    {
        if (redundancy)
        {
            sleep(2);
        }

        Get_input_param2 = g_variant_new("(ss)", (const gchar *)dbus_interface_p->name, (const gchar *)property_p->name);

        if (Get_input_param2 != NULL)
        {
            gchar *s;
            s = g_variant_print(Get_input_param2, true);
            //dbus_printf("Second to Get_input_param2 %s\n", g_variant_print(Get_input_param2, true));
            dbus_printf("Second to Get_input_param2 %s\n", s);
            g_free(s);
            dbus_printf("Second to Get_input_param2....type %s\n", g_variant_get_type_string(Get_input_param2));
        }
        else
        {
            dbus_printf("Second to Get_input_param2 is NULL. exit.\n");
            exit(0);
        }

        if (lib_debug)
        {
            dbus_printf(" Into g_dbus_proxy_call_sync line %d \n", __LINE__);
        }
        Method_Get_Out2 = g_dbus_proxy_call_sync(remote_object,
                                                 "Get",
                                                 Get_input_param2,
                                                 G_DBUS_CALL_FLAGS_NONE,
                                                 -1,
                                                 NULL,
                                                 &error);

        if (lib_debug)
        {
            dbus_printf(" Out g_dbus_proxy_call_sync line %d \n", __LINE__);
        }

        if (error)
        {
            GString *gstring;
            gstring = g_string_new(" ");
            g_string_append_printf(gstring, "Quickly Get, %s", error->message);
            dbus_printf("%s\n", gstring->str);

            g_string_free(gstring, TRUE);
            //dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_p->name, property_p->name,"Get","","","Failed","Error when get after set",__func__,gstring->str);
            //g_variant_unref (Get_input_param2);
            g_error_free(error);
            error = NULL;
            //goto Set_end;
        }
        if (Method_Get_Out2 == NULL)
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name, "", "", "", "Failed", "Method_Get_Out2 is NULL", __func__, "NULL point Error after g_dbus_proxy_call_sync");
            goto Get2_call_get_method_error;
        }
        //close the log output in SCC....  because of G_
        /*if(g_variant_equal(Check_Variant_value, Method_Get_Out2))
                dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_p->name, property_p->name,"Get","","","OK","Quickly, Get the value equal to the Set value",__func__,"");
           else
                dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_p->name, property_p->name,"Get","","","Failed","Quickly, Get the value Not equal to the Set value",__func__,"");*/
        if (g_variant_equal(Check_Variant_value, Method_Get_Out2))
        {
            gchar *s;
            s = g_variant_print(Check_Variant_value, true);            
            //dbus_printf("##The Set and Quickly Get: %s\n", g_variant_print(Check_Variant_value, true));
            dbus_printf("##The Set and Quickly Get: %s\n", s);
            g_free(s);
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Quickly, Get for check Set", "", "OK", "Quickly, Get the value equal to the Set value", __func__, "", "");
        }
        else
        {
            if (dbus_property_list->case_property_set_value == 1)
            {
                gchar *s;
                s = g_variant_print(Check_Variant_value, true);            
                //dbus_printf("##The Set(test_value): %s\n", g_variant_print(Check_Variant_value, true));
                dbus_printf("##The Set(test_value): %s\n", s);
                g_free(s);
            }
            else if (dbus_property_list->case_property_set_value == 2)
            {
                gchar *s;
                s = g_variant_print(Check_Variant_value, true);            
                //dbus_printf("##The Set(test_value2): %s\n", g_variant_print(Check_Variant_value, true));
                dbus_printf("##The Set(test_value2): %s\n", s);
                g_free(s);
            }
            else
            {
                gchar *s;
                s = g_variant_print(Check_Variant_value, true);            
                //dbus_printf("##The Set(test_valueunknown): %s\n", g_variant_print(Check_Variant_value, true));
                dbus_printf("##The Set(test_valueunknown): %s\n", s);
                g_free(s);
            }
            {
            gchar *s;
            s = g_variant_print(Method_Get_Out2, true);            
            //dbus_printf("##The Quickly Get: %s\n", g_variant_print(Method_Get_Out2, true));
            dbus_printf("##The Quickly Get: %s\n", s);
            g_free(s);
            }
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Quickly, Get for check Set", "", "Failed", "", "Quickly, Get the value Not equal to the Set value", __func__, "");
        }


        g_variant_unref(Method_Get_Out2);
        //liuxy 0922-001 : don't need free Get_input_param2,it is consumed by g_dbus_proxy_call_sync.
        //g_variant_unref(Get_input_param2); //del
    }
    else
    {
        dbus_printf("     No Quickly Get\n");
    }
#endif
//Set_end:
//    g_variant_unref(Set_input_param);      //del
//    g_variant_unref(Check_Variant_value);  //del
//    g_variant_unref(Set_value);


//Get_end:

    if (g_strcmp0(dbus_property_list->name, "AdminPassword") == 0)
    {
        if (dbus_property_list->case_property_set_value == 1)
        {
            dbus_printf("   ###back AdminPassword to base! Please make sure test_value2 is default passwd\n");
            bool current_log = true;
            current_log = open_log;
            open_log = false;
            bool current_check_notification = true;
            current_check_notification = check_notification;
            check_notification = false;
            dbus_printf("%s. Close the log and notification_check for adjust device.\n",__func__);
 
            igd1_Set_Checksignal_CheckGet(dbus_object_list, dbus_interface_list, dbus_property_list, 2);
            dbus_property_list->case_property_set_value = 2;
            dbus_printf("%s. After adjust device reset the log and notification_check tag.\n",__func__);
            check_notification = current_check_notification;
            open_log=current_log;

        }
    }
    //liuxy 0922-001 : need free bus and remote_object and Method_Get_Out and Check_Variant_value.   
    g_object_unref(bus);
    g_object_unref(remote_object);
    g_variant_unref(Method_Get_Out);
    g_variant_unref(Check_Variant_value);
    return (0);    
Get_connect_error:
    g_variant_unref (Get_input_param);
    return (0);
Get_proxy_error:
    g_variant_unref (Get_input_param);
    g_object_unref(bus);
    return (0);
Get_call_get_method_error:
    g_object_unref(bus);
    g_object_unref(remote_object);
    return (0);
Get_call_get_method_out_error:
    g_object_unref(bus);
    g_object_unref(remote_object);
    g_variant_unref(Method_Get_Out);
    return (0);
Set_call_set_method_error:
Get2_call_get_method_error:
    g_object_unref(bus);
    g_object_unref(remote_object);
    g_variant_unref(Method_Get_Out);
    g_variant_unref(Check_Variant_value);
    return (0);
//Get_error_out:

    //return(0);
} /* igd1_Set_Checksignal_CheckGet */


int igd1_Get_CheckSetResult(struct dbus_object *dbus_object_list, struct dbus_interface *dbus_interface_list, struct dbus_property *dbus_property_list)
{
    EXIT_IF_NULL(dbus_object_list);
    EXIT_IF_NULL(dbus_object_list->name);
    EXIT_IF_NULL(dbus_interface_list);
    EXIT_IF_NULL(dbus_interface_list->name);
    EXIT_IF_NULL(dbus_property_list);
    EXIT_IF_NULL(dbus_property_list->name);


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
    if (dbus_property_list == NULL)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "unknown", "", "", "", "Failed", "dbus_property is NULL", __func__, "NULL point Error");
        return(-1);
    }
    if (dbus_property_list->name == NULL)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "unknown", "", "", "", "Failed", "dbus_property->name is NULL", __func__, "NULL point Error");
        return(-1);
    }


    dbus_printf("  igd1[Get CheckSetResult] %s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name);


    if (redundancy)
    {
        sleep(1);
    }

    if ((DBUS_CMD_ALL == run_args) || (DBUS_CMD_ALL_BY_STEP == run_args) || open_tag_about_test_all)
    {
        if (g_strcmp0(dbus_interface_list->name, "com.ctc.igd1.DHCPServer") == 0 && g_strcmp0(dbus_property_list->name, "IPAddr") == 0)
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name, "Get", "", "", "OK", "", __func__, "Don't Get com.ctc.igd1.DHCPServer.IPAddr for check Set");
            return(0);
        }
        if (g_strcmp0(dbus_interface_list->name, "com.ctc.igd1.HTTPServer") == 0 && g_strcmp0(dbus_property_list->name, "AdminPassword") == 0)
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name, "Get", "", "", "OK", "", __func__, "Don't Get com.ctc.igd1.HTTPServer.AdminPassword for check Set");
            return(0);
        }
    }

    if (g_strcmp0(dbus_property_list->access, "read") == 0)
    {
        dbus_printf("\n      %s access is read, don't check Set result\n", dbus_property_list->name);
        return(0);
    }
    if (dbus_property_list->case_property_set_value == 0)
    {
        dbus_printf("\n      %s haven't Set by tester, don't check Set result\n", dbus_property_list->name);
        return(0);
    }

    //Set method under "com.ctc.igd1.Properties"
    struct dbus_interface *dbus_interface_p;
    struct dbus_property  *property_p;
    dbus_interface_p = dbus_interface_list;
    property_p       = dbus_property_list;

    GDBusConnection *bus;
    GDBusProxy      *remote_object;
    GError          *error = NULL;
    GVariant        *Method_Get_Out;
    GVariant        *Get_input_param;
    GVariant        *Set_value           = NULL;
    GVariant        *Check_Variant_value = NULL;
    struct timeval  start;
    struct timeval  end;
    guint           elapsed_time = 0;
    pthread_t       tid;

    char            property_in_express[ARG_NUM] = "(ss";
    //char property_out_express[ARG_NUM]="(";
    char            *p_in = property_in_express + sizeof("(ss") - 1;
    //char *p_out=property_out_express+sizeof("(")-1;

    GVariant *info    = NULL;
    gchar    *str_val = NULL;

    strcpy(p_in, ")");
    p_in += 1;
    //strcpy(p_out,")");
    //p_out +=1;
    *p_in = '\0';
    //*p_out='\0';
    //dbus_printf("igd1 %s[Get] the property [%s] type[%s] in [%s]@[%s]\n", property_in_express, property_p->name,property_p->type, dbus_object_list->name, dbus_interface_p->name);

    //Get_input_param=g_variant_new(property_in_express, dbus_interface_p->name, property_p->name);
    Get_input_param = g_variant_new("(ss)", dbus_interface_p->name, property_p->name);

    if (Get_input_param != NULL)
    {
        dbus_printf("Get Result Get_input_param %s\n", g_variant_print(Get_input_param, true));
        dbus_printf("Get Result Get_input_param....type %s\n", g_variant_get_type_string(Get_input_param));
    }
    else
    {
        dbus_printf("Get Result Get_input_param is NULL. exit.\n");
        exit(0);
    }

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
    if (lib_debug)
    {
        dbus_printf(" Into g_dbus_proxy_new_sync line %d \n", __LINE__);
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
                                          "com.ctc.igd1.Properties",
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
    if (lib_debug)
    {
        dbus_printf(" Out g_dbus_proxy_new_sync line %d \n", __LINE__);
    }
    //g_assert_no_error(error);

    gettimeofday(&start, NULL);
    if (lib_debug)
    {
        dbus_printf(" Into g_dbus_proxy_call_sync line %d \n", __LINE__);
    }
    Method_Get_Out = g_dbus_proxy_call_sync(remote_object,
                                            "Get",
                                            Get_input_param,
                                            G_DBUS_CALL_FLAGS_NONE,
                                            -1,
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

        //dbus_cts_error_print(error);
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Get", "", "", "Failed", "Error when get", __func__, gstring->str);
        dbus_object_list->test_result   |= PROPERTY_CANT_GET_OR_GETALL;
        dbus_property_list->test_result |= PROPERTY_CANT_GET_OR_GETALL;
        g_string_free(gstring, TRUE);

        //g_variant_unref (Get_input_param);
        //goto Get_error_out;
        g_error_free(error);
        error = NULL;
        goto Get_error_out;
    }
    elapsed_time = (end.tv_sec - start.tv_sec) * 1000000 +
                   (end.tv_usec - start.tv_usec);

    //dbus_printf("%s, performace  is %s ,the perform time is %d us\n",
    //    dbus_object_list->name,(elapsed_time > 200000)?"FAILED":"OK",elapsed_time);

    //dbus_printf_twice("%s,%s,%s,%s,%s,%d(us),%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_p->name, property_p->name,"Get","",elapsed_time,(elapsed_time > 200000)?"Failed":"OK",(elapsed_time > 200000)?"Time out":"Get single the value not timeout",__func__,"");

    /*g_variant_get(Method_Get_Out, "(v)", &info);
       if(!g_variant_is_of_type (info, G_VARIANT_TYPE (dbus_property_list->type)))
       {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s:%s but not:%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name,dbus_property_list->name,"","","","Failed","Type must be",dbus_property_list->type,g_variant_get_type_string(info),__func__, g_variant_get_type_string(info));
            return;
       }*/


    if (dbus_property_list->case_property_set_value == 1)
    {
        Set_value = (GVariant *)dbus_g_variant_test_and_return_new(dbus_property_list, 0x01);
    }
    else if (dbus_property_list->case_property_set_value == 2)
    {
        Set_value = (GVariant *)dbus_g_variant_test_and_return_new(dbus_property_list, 0x02);
    }
    if (Set_value == NULL)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, dbus_property_list->name, "Get", "", "", "Failed", "No value form xml", __func__, "");
        goto Get_end;
    }

    g_variant_ref(Set_value);    //Add count


    Check_Variant_value = g_variant_new("(v)", Set_value);
    if (g_variant_equal(Check_Variant_value, Method_Get_Out))
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Get for check Set", "", "", "OK", "Get the value equal to the Set value", __func__, "");
    }
    else
    {
        if (dbus_property_list->case_property_set_value == 1)
        {
            dbus_printf("##The Set(test_value): %s\n", g_variant_print(Check_Variant_value, true));
        }
        else if (dbus_property_list->case_property_set_value == 2)
        {
            dbus_printf("##The Set(test_value2): %s\n", g_variant_print(Check_Variant_value, true));
        }
        else
        {
            dbus_printf("##The Set(test_valueunknown): %s\n", g_variant_print(Check_Variant_value, true));
        }
        dbus_printf("##The Get: %s\n", g_variant_print(Method_Get_Out, true));
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, property_p->name, "Get for check Set", "", "", "Failed", "Get the value Not equal to the Set value", __func__, "");
        dbus_object_list->test_result   |= PROPERTY_SET_GET_NOT_EQUAL;
        dbus_property_list->test_result |= PROPERTY_SET_GET_NOT_EQUAL;
    }


    g_variant_unref(Check_Variant_value);
    g_variant_unref(Set_value);

Get_end:
    g_variant_unref(Method_Get_Out);
Get_error_out:
    g_object_unref(G_OBJECT(remote_object));
    g_object_unref(bus);
    return(0);
} /* igd1_Get_CheckSetResult */


//int igd1_Get_2_4G_or_5G(struct dbus_object *dbus_object_list, struct dbus_interface *dbus_interface_list, struct dbus_property *dbus_property_list)
int igd1_Get_2_4G_or_5G(struct dbus_object *dbus_object_list)
{
    if (redundancy)
    {
        sleep(1);
    }


    guint32         out1 = 1;
    GDBusConnection *bus;
    GDBusProxy      *remote_object;
    GError          *error = NULL;
    GVariant        *Method_Get_Out;
    GVariant        *Get_input_param;
    char property_in_express[ARG_NUM] = "(ss";
    //char property_out_express[ARG_NUM]="(";
    char *p_in = property_in_express + sizeof("(ss") - 1;
    //char *p_out=property_out_express+sizeof("(")-1;

    GVariant *info    = NULL;
    gchar    *str_val = NULL;

    strcpy(p_in, ")");
    p_in += 1;
    //strcpy(p_out,")");
    //p_out +=1;
    *p_in = '\0';
    //*p_out='\0';
    //dbus_printf("igd1 %s[Get] the property [%s] type[%s] in [%s]@[%s]\n", property_in_express, property_p->name,property_p->type, dbus_object_list->name, dbus_interface_p->name);

    //Get_input_param=g_variant_new("(ss)", dbus_interface_p->name, property_p->name);
    Get_input_param = g_variant_new("(ss)", "com.ctc.igd1.WLANConfiguration", "RFBand");

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
    remote_object = g_dbus_proxy_new_sync(bus,
                                          G_DBUS_PROXY_FLAGS_NONE,
                                          NULL,
                                          "com.ctc.igd1",
                                          dbus_object_list->name,
                                          "com.ctc.igd1.Properties",
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

    //gettimeofday(&start, NULL);
    Method_Get_Out = g_dbus_proxy_call_sync(remote_object,
                                            "Get",
                                            Get_input_param,
                                            G_DBUS_CALL_FLAGS_NONE,
                                            -1,
                                            NULL,
                                            &error);
    //gettimeofday(&end, NULL);

    if (error)
    {
        GString *gstring;
        gstring = g_string_new(" ");
        g_string_append_printf(gstring, "%s", error->message);
        dbus_printf("%s\n", gstring->str);

        //dbus_cts_error_print(error);
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, "com.ctc.igd1.WLANConfiguration", "RFBand", "Get", "", "", "Failed", "Error when get", __func__, gstring->str);
        //g_variant_unref (Get_input_param);
        //goto Get_error_out;
        g_string_free(gstring, TRUE);
        g_error_free(error);
        error = NULL;
        goto Get_error_out;
    }

    dbus_printf("#Get the RFBand:%s\n", g_variant_print(Method_Get_Out, true));
    //dbus_printf("#Get the variant....type %s\n",g_variant_get_type_string(Method_Get_Out));
    g_variant_get(Method_Get_Out, "(v)", &info);
    g_variant_get(info, "u", &out1);
    if (out1 == 0)
    {
        dbus_printf("This is 2.4G devices, using /com/ctc/igd1/Config/WLAN/Devices_2_4G/{i} value\n");
    }
    else if (out1 == 1)
    {
        dbus_printf("This is 5G devices, using /com/ctc/igd1/Config/WLAN/Devices_5G/{i} value\n");
    }
    else
    {
        dbus_printf("This is unknown-G devices\n");
    }

Get_end:
    g_variant_unref(Method_Get_Out);
Get_error_out:
    g_object_unref(G_OBJECT(remote_object));
    g_object_unref(bus);
    if (out1 == 1)
    {
        return(1);
    }
    else
    {
        return(0);
    }
} /* igd1_Get_2_4G_or_5G */


int igd1_LANHost_DeleteObject_CheckSignal(struct dbus_object *dbus_object_list, struct dbus_interface *dbus_interface_list)
//int igd1_LANHost_DeleteObject_CheckSignal(void)
{
    if (redundancy)
    {
        sleep(1);
    }


    EXIT_IF_NULL(dbus_object_list);
    EXIT_IF_NULL(dbus_object_list->name);
    EXIT_IF_NULL(dbus_interface_list);
    EXIT_IF_NULL(dbus_interface_list->name);

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


    dbus_object_list->test_result    &= (~UNPASS);
    dbus_interface_list->test_result &= (~UNPASS);


    struct listnode    *obj_list_item_p;
    struct dbus_object *dbus_son_object_p    = NULL;
    struct dbus_object *dbus_son_object_list = NULL;
    if (!list_empty(&dbus_list))
    {
        list_for_each(obj_list_item_p, &dbus_list)
        {
            dbus_son_object_p = node_to_item(obj_list_item_p, struct dbus_object, list);
            if (dbus_son_object_p->form_name != NULL)
            {
                //Notes... I had want add the judgement into one sentence, like p!=NULL && p...
                //         But there is so many compiler.....
                if (g_strcmp0(dbus_son_object_p->form_name, "/com/ctc/igd1/Config/LANHosts") == 0)
                {
                    dbus_son_object_list = dbus_son_object_p;
                    break;
                }
            }
        }
    }

    if (dbus_son_object_list != NULL)
    {
        dbus_printf("Can't find /com/ctc/igd1/Config/LANHosts/{i}. Please check enrionment and update bak file.\n");
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, "com.ctc.igd1.ObjectManager", "", "DeleteObject", "", "", "Failed", "No instance /com/ctc/igd1/Config/LANHosts/{i}", __func__, "");
        dbus_object_list->test_result    |= METHOD_CALL_FAIL;
        dbus_interface_list->test_result |= METHOD_CALL_FAIL;
        return(-1);
    }


    dbus_printf("  method[ DeleteObject ] %s\n", dbus_son_object_list->name);


    //Set method under "com.ctc.igd1.Properties"
    struct dbus_interface *dbus_interface_p;
    //struct dbus_property *property_p;
    dbus_interface_p = dbus_interface_list;
    //property_p=dbus_property_list;

    GDBusConnection *bus;
    GDBusProxy      *remote_object;
    GError          *error                    = NULL;
    GVariant        *LANHost_Method_Addobject = NULL;
    struct timeval  start;
    struct timeval  end;
    guint           elapsed_time = 0;
    pthread_t       listen_add_tid;
    pthread_t       listen_del_tid;
    GVariant        *info = NULL;

    wait_signal_with         = LONG_WAIT_SEC;
    LANHost_Method_Addobject = g_variant_new_object_path(dbus_son_object_list->name);
    if (LANHost_Method_Addobject == NULL)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, "com.ctc.igd1.ObjectManager", "", "DeleteObject", "", "", "Failed", "Can't get the LANHost instance path", __func__, "");
        dbus_object_list->test_result    |= METHOD_CALL_FAIL;
        dbus_interface_list->test_result |= METHOD_CALL_FAIL;
        return(-1);
    }
    //int i;
    //aim_signal= DBUS_SIGNAL_IDG1_INTERFACE_ADD;
    //pthread_create(&listen_add_tid,NULL,thread_func,NULL);

    if (lib_debug)
    {
        dbus_printf(" Into g_dbus_get_sync line %d \n", __LINE__);
    }
    bus = g_bus_get_sync(G_BUS_TYPE_SYSTEM, NULL, &error);
    if (lib_debug)
    {
        dbus_printf(" Out g_dbus_get_sync line %d \n", __LINE__);
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
    //g_assert_no_error(error);
    if (lib_debug)
    {
        dbus_printf(" Into g_dbus_proxy_new_sync line %d \n", __LINE__);
    }
    remote_object = g_dbus_proxy_new_sync(bus,
                                          G_DBUS_PROXY_FLAGS_NONE,
                                          NULL,
                                          "com.ctc.igd1",
                                          dbus_object_list->name,
                                          "com.ctc.igd1.ObjectManager",
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
    sleep(1);
    //g_assert_no_error(error);
#if 0
    if (lib_debug)
    {
        dbus_printf(" Into g_dbus_proxy_call_sync line %d \n", __LINE__);
    }
    gettimeofday(&start, NULL);
    Method_Addobject = g_dbus_proxy_call_sync(remote_object,
                                              "AddObject",
                                              NULL,//Get_input_param,
                                              G_DBUS_CALL_FLAGS_NONE,
                                              -1,
                                              NULL,
                                              &error);
    gettimeofday(&end, NULL);
    if (lib_debug)
    {
        dbus_printf(" Into g_dbus_proxy_call_sync line %d \n", __LINE__);
    }

    if (error)
    {
        GString *gstring;
        gstring = g_string_new(" ");
        g_string_append_printf(gstring, "%s", error->message);
        dbus_printf("%s\n", gstring->str);

        //dbus_cts_error_print(error);
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, "", "AddObject", "", "", "Failed", "Error when AddObject", __func__, gstring->str);
        dbus_object_list->test_result    |= METHOD_CALL_FAIL;
        dbus_interface_list->test_result |= METHOD_CALL_FAIL;
        g_string_free(gstring, TRUE);

        {
            pthread_cancel(listen_add_tid);
//			pthread_join(listen_add_tid,NULL);
        }
        g_error_free(error);
        error = NULL;
        goto AddObject_error_out;
    }
    elapsed_time = (end.tv_sec - start.tv_sec) * 1000000 +
                   (end.tv_usec - start.tv_usec);

    //dbus_printf("%s, performace  is %s ,the perform time is %d us\n",
    //    dbus_object_list->name,(elapsed_time > 200000)?"FAILED":"OK",elapsed_time);

    dbus_printf_twice("%s,%s,%s,%s,%s,%d(us),%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, "", "AddObject", "", elapsed_time, (elapsed_time > 200000) ? "Failed" : "OK", (elapsed_time > 200000) ? "AddObject Time out" : "AddObject not timeout", __func__, "");
    if (elapsed_time > 200000)
    {
        dbus_object_list->test_result    |= METHOD_CALL_TIMEOUT;
        dbus_interface_list->test_result |= METHOD_CALL_TIMEOUT;
    }
    pthread_cond_wait(&cond, &mtx);
    //pthread_mutex_lock(&mtx);
    //pthread_mutex_unlock(&mtx);
    if (kret == DBUS_SIGNAL_FREEDESKTOP_PROPERTY_CHANGED)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", "AddObject", "PropertiesChanged", "", "Failed", "Receive org.freedesktop.DBus.Properties.PropertiesChanged when test AddObject", __func__, "");
        //if(thread_msg!=NULL)
        //dbus_1_message_print(thread_msg);
    }
    else if (kret == DBUS_SIGNAL_IDG1_INTERFACE_ADD)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", "AddObject", "InterfacesAdded", "", "OK", "Receive com.ctc.igd1.ObjectManager.InterfacesAdded when test AddObject", __func__, "");
    }
    else if (kret == DBUS_SIGNAL_IDG1_INTERFACE_REMOVE)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", "AddObject", "InterfacesRemoved", "", "Failed", "Receive com.ctc.igd1.ObjectManager.InterfacesRemoved when test AddObject", __func__, "");
    }

    else if (kret == DBUS_SIGNAL_TIMEOUT)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s%d%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", "AddObject", "singal timeout", "", "Failed", "When test AddOject.Wait signal more than ", wait_signal_with, "s", __func__, "");
        dbus_object_list->test_result    |= NO_RECIVE_SIGNAL;
        dbus_interface_list->test_result |= NO_RECIVE_SIGNAL;
    }
    else
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", "AddObject", "unknown issue", "", "Failed", "unknown when test AddObject", __func__, "");
    }

    pthread_cancel(listen_add_tid);
    //pthread_join(listen_add_tid,NULL);

    if (g_variant_is_of_type(Method_Addobject, G_VARIANT_TYPE_OBJECT_PATH))
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, "", "AddObject", "", "", "OK", "AddObject success", __func__, g_variant_get_string(Method_Addobject, NULL));
    }

    else
    {
        //dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_p->name, "","AddObject","","","Failed","AddObject error",__func__,"##Can't parse the return object_path");
        //goto AddObject_error_out;
    }


    sleep(1);
#endif
    dbus_printf("Check the DeleteObject \n");
    aim_signal = DBUS_SIGNAL_IDG1_INTERFACE_REMOVE;
    pthread_create(&listen_del_tid, NULL, thread_func, NULL);
    sleep(2);

    /*bus = g_bus_get_sync (G_BUS_TYPE_SYSTEM, NULL, &error);
       //g_assert_no_error(error);
       remote_object = g_dbus_proxy_new_sync (bus,
            G_DBUS_PROXY_FLAGS_NONE,
            NULL,
            "com.ctc.igd1",
            dbus_object_list->name,
            "com.ctc.igd1.ObjectManager",
            NULL,
            &error);
     */
    //g_assert_no_error(error);

    if (lib_debug)
    {
        dbus_printf(" Into g_dbus_proxy_call_sync line %d \n", __LINE__);
    }
    gettimeofday(&start, NULL);
    g_dbus_proxy_call_sync(remote_object,
                           "DeleteObject",
                           LANHost_Method_Addobject,//g_variant_new(property_in_express, dbus_interface_p->name, property_p->name);
                           G_DBUS_CALL_FLAGS_NONE,
                           -1,
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

        //dbus_cts_error_print(error);
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, "", "DeleteObject", "", "", "Failed", "Error when DeleteObject", __func__, gstring->str);
        dbus_object_list->test_result    |= METHOD_CALL_FAIL;
        dbus_interface_list->test_result |= METHOD_CALL_FAIL;
        g_string_free(gstring, TRUE);
        {
            pthread_cancel(listen_del_tid);
//			pthread_join(listen_del_tid,NULL);
        }
        g_error_free(error);
        error = NULL;
        goto DeleteObject_error_out;
    }
    elapsed_time = (end.tv_sec - start.tv_sec) * 1000000 +
                   (end.tv_usec - start.tv_usec);

    //dbus_printf("%s, performace  is %s ,the perform time is %d us\n",
    //    dbus_object_list->name,(elapsed_time > 200000)?"FAILED":"OK",elapsed_time);

    dbus_printf_twice("%s,%s,%s,%s,%s,%d(us),%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, "", "DeleteObject", "", elapsed_time, (elapsed_time > 200000) ? "Failed" : "OK", (elapsed_time > 200000) ? "Time out" : "DeleteObject not timeout", __func__, "");
    if (elapsed_time > 200000)
    {
        dbus_object_list->test_result    |= METHOD_CALL_TIMEOUT;
        dbus_interface_list->test_result |= METHOD_CALL_TIMEOUT;
    }
    pthread_cond_wait(&cond, &mtx);
    //pthread_mutex_lock(&mtx);
    //pthread_mutex_unlock(&mtx);
    if (kret == DBUS_SIGNAL_FREEDESKTOP_PROPERTY_CHANGED)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", "DeleteObject", "PropertiesChanged", "", "Failed", "Receive org.freedesktop.DBus.Properties.PropertiesChanged when test DeleteObject", __func__, "");
        //if(thread_msg!=NULL)
        //dbus_1_message_print(thread_msg);
    }
    else if (kret == DBUS_SIGNAL_IDG1_INTERFACE_ADD)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", "DeleteObject", "InterfacesAdded", "", "Failed", "Receive com.ctc.igd1.ObjectManager.InterfacesAdded when test DeleteObject", __func__, "");
    }
    else if (kret == DBUS_SIGNAL_IDG1_INTERFACE_REMOVE)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", "DeleteObject", "InterfacesRemoved", "", "OK", "Receive com.ctc.igd1.ObjectManager.InterfacesRemoved when test DeleteObject", __func__, "");
    }
    /*else if(kret == DBUS_SIGNAL_IDG1_PROPERTY_CHANGED)
                    dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name,"","DeleteObject","PropertiesChanged","","Failed","Receive  com.ctc.igd1.Properties.PropertiesChanged when test DeleteObject",__func__,"");*/
    else if (kret == DBUS_SIGNAL_TIMEOUT)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s%d%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", "DeleteObject", "signal timeout", "", "Failed", "When test DeleteOject. Wait signal more than ", wait_signal_with, "s", __func__, "");
        dbus_object_list->test_result    |= NO_RECIVE_SIGNAL;
        dbus_interface_list->test_result |= NO_RECIVE_SIGNAL;
    }
    else
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,kret=0x%x\n", dbus_object_list->name, dbus_interface_list->name, "", "DeleteObject", "unknown issue", "", "Failed", "unknown when test DeleteObject", __func__, kret);
    }

    pthread_cancel(listen_del_tid);
    //pthread_join(listen_del_tid,NULL);


DeleteObject_error_out:
    //g_object_unref (LANHost_Method_Addobject);
AddObject_error_out:
    wait_signal_with = NORMAL_WAIT_SEC;
    g_object_unref(G_OBJECT(remote_object));
    g_object_unref(bus);
    return(0);
} /* igd1_LANHost_DeleteObject_CheckSignal */


int igd1_AddObject_CheckSignal_DeleteObject_CheckSignal(struct dbus_object *dbus_object_list, struct dbus_interface *dbus_interface_list)
{
    if (redundancy)
    {
        sleep(1);
    }


    EXIT_IF_NULL(dbus_object_list);
    EXIT_IF_NULL(dbus_object_list->name);
    EXIT_IF_NULL(dbus_interface_list);
    EXIT_IF_NULL(dbus_interface_list->name);

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

    if (strcmp(dbus_interface_list->name, "com.ctc.igd1.LANHostManager") == 0)
    {
        return(igd1_LANHost_DeleteObject_CheckSignal(dbus_object_list, dbus_interface_list));
    }

    dbus_object_list->test_result    &= (~UNPASS);
    dbus_interface_list->test_result &= (~UNPASS);


    dbus_printf("  method[AddObject DeleteObject] %s,%s\n", dbus_object_list->name, dbus_interface_list->name);


    //Set method under "com.ctc.igd1.Properties"
    struct dbus_interface *dbus_interface_p;
    //struct dbus_property *property_p;
    dbus_interface_p = dbus_interface_list;
    //property_p=dbus_property_list;

    GDBusConnection *bus;
    GDBusProxy      *remote_object;
    GError          *error = NULL;
    GVariant        *Method_Addobject;
    struct timeval  start;
    struct timeval  end;
    guint           elapsed_time = 0;
    pthread_t       listen_add_tid;
    pthread_t       listen_del_tid;
    GVariant        *info = NULL;

    wait_signal_with = LONG_WAIT_SEC;
    //int i;
    aim_signal = DBUS_SIGNAL_IDG1_INTERFACE_ADD;
    pthread_create(&listen_add_tid, NULL, thread_func, NULL);
    sleep(1);

    if (lib_debug)
    {
        dbus_printf(" Into g_dbus_get_sync line %d \n", __LINE__);
    }
    bus = g_bus_get_sync(G_BUS_TYPE_SYSTEM, NULL, &error);
    if (lib_debug)
    {
        dbus_printf(" Out g_dbus_get_sync line %d \n", __LINE__);
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
    //g_assert_no_error(error);
    if (lib_debug)
    {
        dbus_printf(" Into g_dbus_proxy_new_sync line %d \n", __LINE__);
    }
    remote_object = g_dbus_proxy_new_sync(bus,
                                          G_DBUS_PROXY_FLAGS_NONE,
                                          NULL,
                                          "com.ctc.igd1",
                                          dbus_object_list->name,
                                          "com.ctc.igd1.ObjectManager",
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
    //g_assert_no_error(error);

    if (lib_debug)
    {
        dbus_printf(" Into g_dbus_proxy_call_sync line %d \n", __LINE__);
    }
    gettimeofday(&start, NULL);
    Method_Addobject = g_dbus_proxy_call_sync(remote_object,
                                              "AddObject",
                                              NULL,//Get_input_param,
                                              G_DBUS_CALL_FLAGS_NONE,
                                              -1,
                                              NULL,
                                              &error);
    gettimeofday(&end, NULL);
    if (lib_debug)
    {
        dbus_printf(" Into g_dbus_proxy_call_sync line %d \n", __LINE__);
    }

    if (error)
    {
        GString *gstring;
        gstring = g_string_new(" ");
        g_string_append_printf(gstring, "%s", error->message);
        dbus_printf("%s\n", gstring->str);

        //dbus_cts_error_print(error);
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, "", "AddObject", "", "", "Failed", "Error when AddObject", __func__, gstring->str);
        dbus_object_list->test_result    |= METHOD_CALL_FAIL;
        dbus_interface_list->test_result |= METHOD_CALL_FAIL;
        g_string_free(gstring, TRUE);

        {
            pthread_cancel(listen_add_tid);
//			pthread_join(listen_add_tid,NULL);
        }
        g_error_free(error);
        error = NULL;
        goto AddObject_error_out;
    }
    elapsed_time = (end.tv_sec - start.tv_sec) * 1000000 +
                   (end.tv_usec - start.tv_usec);

    //dbus_printf("%s, performace  is %s ,the perform time is %d us\n",
    //    dbus_object_list->name,(elapsed_time > 200000)?"FAILED":"OK",elapsed_time);

    dbus_printf_twice("%s,%s,%s,%s,%s,%d(us),%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, "", "AddObject", "", elapsed_time, (elapsed_time > 200000) ? "Failed" : "OK", (elapsed_time > 200000) ? "AddObject Time out" : "AddObject not timeout", __func__, "");
    if (elapsed_time > 200000)
    {
        dbus_object_list->test_result    |= METHOD_CALL_TIMEOUT;
        dbus_interface_list->test_result |= METHOD_CALL_TIMEOUT;
    }
    pthread_cond_wait(&cond, &mtx);
    //pthread_mutex_lock(&mtx);
    //pthread_mutex_unlock(&mtx);
    if (kret == DBUS_SIGNAL_FREEDESKTOP_PROPERTY_CHANGED)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", "AddObject", "PropertiesChanged", "", "Failed", "Receive org.freedesktop.DBus.Properties.PropertiesChanged when test AddObject", __func__, "");
        //if(thread_msg!=NULL)
        //dbus_1_message_print(thread_msg);
    }
    else if (kret == DBUS_SIGNAL_IDG1_INTERFACE_ADD)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", "AddObject", "InterfacesAdded", "", "OK", "Receive com.ctc.igd1.ObjectManager.InterfacesAdded when test AddObject", __func__, "");
    }
    else if (kret == DBUS_SIGNAL_IDG1_INTERFACE_REMOVE)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", "AddObject", "InterfacesRemoved", "", "Failed", "Receive com.ctc.igd1.ObjectManager.InterfacesRemoved when test AddObject", __func__, "");
    }
    /*else if(kret == DBUS_SIGNAL_IDG1_PROPERTY_CHANGED)
                    dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name,"","AddObject","PropertiesChanged","","Failed","Receive com.ctc.igd1.Properties.PropertiesChanged when test AddObject",__func__,"");*/
    /*else if(kret == DBUS_SIGNAL_FREEDESKTOP_INTERFACE_ADD)
                    dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name,"","AddObject","InterfacesAdded","","Failed","Receive org.freedesktop.DBus.ObjectManager.InterfacesAdded when test AddObject",__func__,"");
       else if(kret == DBUS_SIGNAL_FREEDESKTOP_INTERFACE_REMOVE)
                    dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name,"","AddObject","InterfacesRemoved","","Failed","Receive org.freedesktop.DBus.ObjectManager.InterfacesRemoved when test AddObject",__func__,"");*/
    else if (kret == DBUS_SIGNAL_TIMEOUT)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s%d%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", "AddObject", "singal timeout", "", "Failed", "When test AddOject.Wait signal more than ", wait_signal_with, "s", __func__, "");
        dbus_object_list->test_result    |= NO_RECIVE_SIGNAL;
        dbus_interface_list->test_result |= NO_RECIVE_SIGNAL;
    }
    else
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", "AddObject", "unknown issue", "", "Failed", "unknown when test AddObject", __func__, "");
    }

    pthread_cancel(listen_add_tid);
    //pthread_join(listen_add_tid,NULL);

    if (g_variant_is_of_type(Method_Addobject, G_VARIANT_TYPE_OBJECT_PATH))
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, "", "AddObject", "", "", "OK", "AddObject success", __func__, g_variant_get_string(Method_Addobject, NULL));
    }

    else
    {
        //dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_p->name, "","AddObject","","","Failed","AddObject error",__func__,"##Can't parse the return object_path");
        //goto AddObject_error_out;
    }


    sleep(1);
    dbus_printf("Check the DeleteObject \n");
    aim_signal = DBUS_SIGNAL_IDG1_INTERFACE_REMOVE;
    pthread_create(&listen_del_tid, NULL, thread_func, NULL);
    sleep(2);

    if (lib_debug)
    {
        dbus_printf(" Into g_dbus_proxy_call_sync line %d \n", __LINE__);
    }
    gettimeofday(&start, NULL);
    g_dbus_proxy_call_sync(remote_object,
                           "DeleteObject",
                           Method_Addobject,//g_variant_new(property_in_express, dbus_interface_p->name, property_p->name);
                           G_DBUS_CALL_FLAGS_NONE,
                           -1,
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

        //dbus_cts_error_print(error);
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, "", "DeleteObject", "", "", "Failed", "Error when DeleteObject", __func__, gstring->str);
        dbus_object_list->test_result    |= METHOD_CALL_FAIL;
        dbus_interface_list->test_result |= METHOD_CALL_FAIL;
        g_string_free(gstring, TRUE);
        {
            pthread_cancel(listen_del_tid);
//			pthread_join(listen_del_tid,NULL);
        }
        g_error_free(error);
        error = NULL;
        goto DeleteObject_error_out;
    }
    elapsed_time = (end.tv_sec - start.tv_sec) * 1000000 +
                   (end.tv_usec - start.tv_usec);

    //dbus_printf("%s, performace  is %s ,the perform time is %d us\n",
    //    dbus_object_list->name,(elapsed_time > 200000)?"FAILED":"OK",elapsed_time);

    dbus_printf_twice("%s,%s,%s,%s,%s,%d(us),%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_p->name, "", "DeleteObject", "", elapsed_time, (elapsed_time > 200000) ? "Failed" : "OK", (elapsed_time > 200000) ? "Time out" : "DeleteObject not timeout", __func__, "");
    if (elapsed_time > 200000)
    {
        dbus_object_list->test_result    |= METHOD_CALL_TIMEOUT;
        dbus_interface_list->test_result |= METHOD_CALL_TIMEOUT;
    }
    pthread_cond_wait(&cond, &mtx);
    //pthread_mutex_lock(&mtx);
    //pthread_mutex_unlock(&mtx);
    if (kret == DBUS_SIGNAL_FREEDESKTOP_PROPERTY_CHANGED)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", "DeleteObject", "PropertiesChanged", "", "Failed", "Receive org.freedesktop.DBus.Properties.PropertiesChanged when test DeleteObject", __func__, "");
        //if(thread_msg!=NULL)
        //dbus_1_message_print(thread_msg);
    }
    else if (kret == DBUS_SIGNAL_IDG1_INTERFACE_ADD)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", "DeleteObject", "InterfacesAdded", "", "Failed", "Receive com.ctc.igd1.ObjectManager.InterfacesAdded when test DeleteObject", __func__, "");
    }
    else if (kret == DBUS_SIGNAL_IDG1_INTERFACE_REMOVE)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", "DeleteObject", "InterfacesRemoved", "", "OK", "Receive com.ctc.igd1.ObjectManager.InterfacesRemoved when test DeleteObject", __func__, "");
    }
    /*else if(kret == DBUS_SIGNAL_IDG1_PROPERTY_CHANGED)
                    dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name,"","DeleteObject","PropertiesChanged","","Failed","Receive  com.ctc.igd1.Properties.PropertiesChanged when test DeleteObject",__func__,"");*/
    else if (kret == DBUS_SIGNAL_TIMEOUT)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s%d%s,%s,%s\n", dbus_object_list->name, dbus_interface_list->name, "", "DeleteObject", "signal timeout", "", "Failed", "When test DeleteOject. Wait signal more than ", wait_signal_with, "s", __func__, "");
        dbus_object_list->test_result    |= NO_RECIVE_SIGNAL;
        dbus_interface_list->test_result |= NO_RECIVE_SIGNAL;
    }
    else
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,kret=0x%x\n", dbus_object_list->name, dbus_interface_list->name, "", "DeleteObject", "unknown issue", "", "Failed", "unknown when test DeleteObject", __func__, kret);
    }

    pthread_cancel(listen_del_tid);
    //pthread_join(listen_del_tid,NULL);


DeleteObject_error_out:
    //g_object_unref (Method_Addobject);
AddObject_error_out:
    wait_signal_with = NORMAL_WAIT_SEC;
    g_object_unref(G_OBJECT(remote_object));
    g_object_unref(bus);
    return(0);
} /* igd1_AddObject_CheckSignal_DeleteObject_CheckSignal */

