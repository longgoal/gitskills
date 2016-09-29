/************************************************ 
*  Dbus test suite
*  Author: Thundersoft
*  2016, all rights reserved.
************************************************/

#include "dbus_log.h"

#include <pthread.h>
#include <dbus/dbus.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <dirent.h>
#include <sys/time.h>
typedef enum {
	DBUS_COMMAND_INVALID = -1,
	DBUS_CMD_HELP,
	DBUS_CMD_ALL,
	DBUS_CMD_ALL_BY_STEP,
	DBUS_CMD_OBJECT,
	DBUS_CMD_INTERFACE,
	DBUS_CMD_PROPERTY,
	DBUS_CMD_PROPERTY_SET,
	DBUS_CMD_PROPERTY_GET,
	DBUS_CMD_METHOD_ARG,
	DBUS_CMD_METHOD_NO_ARG,
	DBUS_CMD_SIGNAL,
	DBUS_CMD_UPDATE_INSTANCE,
	DBUS_CMD_PARALLEL,
	DBUS_CMD_INTROSPECT,
	DBUS_CMD_VERSION,
	DBUS_CMD_TEST_DDOS,
	DBUS_CMD_TEST_MORE_METHOD,
	DBUS_CMD_RESULT,
}dbus_command_s;

struct main_args{
	dbus_command_s  dbus_cmd;
	gchar **object_path;
	gchar **dbus_interface;
	gchar **dbus_method;
	gchar   method_num;
	gchar **dbus_property;
	gchar   property_num;
	gchar **dbus_signal;
};

