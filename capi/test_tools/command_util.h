#include <gio/gio.h>
typedef enum
{
    TS_TYPE_A ,
    TS_TYPE_M ,
    TS_TYPE_S ,
} test_type_t;

/* 
-M module
-S single 
-A all*/
int Get_mode(gchar* command, gchar* extral);
