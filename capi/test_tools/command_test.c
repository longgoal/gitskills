#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "command_test.h"

int Get_mode(gchar* command){
	int mode = TS_TYPE_API;
	gchar *p = NULL;
	p = strstr(command, "-api");
	if (NULL != p){
		mode = TS_TYPE_API;
		p = p + 2*sizeof(gchar);
		while (*p ==' ')
		{
		  p=p+sizeof(gchar);
		}
		//extral = p;
	}
	p = strstr(command, "-mgr");
	if (NULL != p){
		mode = TS_TYPE_MGR;
		p = p + 2*sizeof(gchar);
		while (*p == ' ')
		{
			p = p + 1;
		}
		//extral = p;
	}

	return mode;
}
