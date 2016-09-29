/************************************************ 
*  Dbus test suite
*  Author: Thundersoft
*  2016, all rights reserved.
************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <gio/gio.h>  

#define dbus_printf g_print

//extern GDBusConnection  *bus; 
void dbus_cts_error_print(GError   *error);
void dbus_cts_ok_print();
//int dbus_printf(const char * fmt,...);
