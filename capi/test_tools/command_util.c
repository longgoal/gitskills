#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "command_util.h"

int Get_mode(gchar* command,gchar* extral){
	int mode = TS_TYPE_A;
	gchar *p = NULL;
	p = strstr(command, "-M");
	if (NULL != p){
		mode = TS_TYPE_M;
		p = p + 2*sizeof(gchar);
		while (*p ==' ')
		{
		  p=p+sizeof(gchar);
		}
		extral = p;
	}
	p = strstr(command, "-S");
	if (NULL != p){
		mode = TS_TYPE_S;
		p = p + 2*sizeof(gchar);
		while (*p == ' ')
		{
			p = p + 1;
		}
		extral = p;
	}

	return mode;
}
