#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "command_util.h"

int Get_mode(gchar* mode){
	int Type = TS_TYPE_A;
	gchar *p = NULL;
	if(NULL == mode)
		return Type;
        //g_print("Get_mode command %s\n",mode);
	p = strstr(mode, "-M");
        //g_print("Get_mode p %s\n",p);
	if (NULL != p){
		Type = TS_TYPE_M;
		/*p = p + 2;
		while (*p ==' ')
		{
		  p=p+sizeof(gchar);
		}
		extral = p;*/
	}
	p = strstr(mode, "-S");
        //g_print("Get_mode p2 %s\n",p);
	if (NULL != p){
		Type = TS_TYPE_S;
		/*p = p + 2;
		while (*p == ' ')
		{
			p = p + 1;
		}
		extral = p;*/
	}
	p = strstr(mode, "-E");
       // g_print("Get_mode p2 %s\n",p);
	if (NULL != p){
		Type = TS_TYPE_Y;
		/*p = p + 2;
		while (*p == ' ')
		{
			p = p + 1;
		}
		extral = p;*/
	}
       // g_print("Get_mode %s\n",extral);
       // g_print("Get_mode %d\n",Type);
	return Type;
}
