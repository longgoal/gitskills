#include <gio/gio.h>

#include "capi.h"



int start(gchar *command);
int Process_test_single();
int Process_test_module();
int Process_test_all();
cJSON*  dofile(char *filename);

/* ---------------------------------------- */
/*Files:
  test case module index
    |dbus_service_test_case //module index
        |
        |
        |
    |sys_service_test_case //module index
        |DeviceInfo_test case
           |testcase1 
           |testcase2
           |...
        |NetworkInfo_test_case
        |WANConnectionInfo_test_case
        |.....
    |app_mgr_test_case //module index
        |
        |TBD no interface
        |
    |ctsgw_test_case //module index
        |
        |TBD no interface
        |

 test case defined:
   sample:
    return: int (void ...)
    fuction:fuction(in,in,out,out);
    inparameter1:
    <---begin--->
                        type:CtSgwObjPath_t
                        value:{
                            type:char
                            value:xxxxxxxxxx
                            type:int
                            value:xxxxxxxxxx
                            type:obj_t
                            value:{
                            
                            }
                            type:obj_t *
                            value:{
                            
                            }
                        }
     <---end--->
    inparameter2:
    inparameter3:
    ...
    targetparameter1:type:
    targetparameter2:type:
*/


