
#ifndef _COMMAND_UTIL_H_
#define _COMMAND_UTIL_H_

#include <gio/gio.h>

#endif

int Get_mode(gchar *command);
typedef enum
{
    APP_ALL,
    APP_ONE,
    APP_INSTALL,
    APP_UPGRADE,
    APP_START,
    APP_STOP,
    APP_RELOAD,
    APP_UNINSTALL,      
    UCI_CAPI, 
    TEST_LOG, 
    PRESSURE_TEST,
    SAFE_TEST,   
    APPNUM_TEST,
  
} test_type_t;

/* 
-M module
-S single 
-A all*/

