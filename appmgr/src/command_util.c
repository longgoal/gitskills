#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "command_util.h"

int Get_mode(gchar* command){

	int mode = APP_ALL ;
	gchar *p = NULL;
        if(NULL == command)return mode;// compare command 
        g_print("Get_mode command %s\n",mode);

	p = strstr(command, "APP_ALL"); //compare the string and return NULL if they are diff       
	if (NULL != p){
		mode = APP_ALL;
        g_print("mode=%d\n",mode);
		
	}

	p = strstr(command, "APP_ONE");
	if (NULL != p){
		mode = APP_ONE;
	g_print("mode=%d\n",mode);	
	}

        p = strstr(command, "APP_INSTALL");
        if (NULL !=p){
                 mode = APP_INSTALL;
        g_print("mode=%d\n",mode);         
        }

        p = strstr(command, "APP_UPGRADE");
        if (NULL !=p){
                 mode = APP_UPGRADE;                

        }

        p = strstr(command, "APP_START");
        if (NULL !=p){
                 mode = APP_START;                 

        }

        p = strstr(command, "APP_STOP");
        if (NULL !=p){
                 mode = APP_STOP;
                 
        }

        p = strstr(command, "APP_RELOAD");
        if (NULL !=p){
                 mode = APP_RELOAD;                 

        }

        p = strstr(command, "APP_UNINSTALL");
        if (NULL !=p){
                 mode = APP_UNINSTALL;                 

        }

        p = strstr(command, "UCI_CAPI");
        if (NULL !=p){
                 mode = UCI_CAPI;                
        }

        p = strstr(command, "TEST_LOG");
        if (NULL !=p){
                 mode = TEST_LOG;                
        }

        p = strstr(command, "PRESSURE_TEST");
        if (NULL !=p){
                 mode = PRESSURE_TEST;
                
        }

        p = strstr(command, "SAFE_TEST");
        if (NULL !=p){
                 mode = SAFE_TEST;
                
        }

        p = strstr(command, "APPNUM_TEST");
        if (NULL !=p){
                 mode = APPNUM_TEST;
                
        }

    return mode;
}
