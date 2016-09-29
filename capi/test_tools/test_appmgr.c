#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "command_util.h"
#include "cJSON.h"
#include "map.h"
#include "test_appmgr.h"
#include "capi-app-mgr.h"

typedef struct function_entry
{
	char * fun_name;
	int index;
}function_entry_t;

typedef struct param_entry
{
	char * param_name;
	int index;
}param_entry_t;
#define NUMBER 10
const function_entry_t FUCTION_MAP[NUMBER] = {
	{ "CtSgwInstallApp", 0},
	{ "CtSgwUpgradeApp", 1},
	{ "CtSgwUninstallApp", 2},
        { "CtSgwStartApp", 3},
	{ "CtSgwStopApp", 4},	
	{ "CtSgwGetAppStatus", 5},
        { "CtSgwReloadApp",6}



};
/*function_entry_t PARAM_MAP[] = {
	{ "CtSgwDeviceInfo_t", 0 },
	{ "CtSgwNetworkInfo_t", 1 },
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",

};*/
static map_t fuction_map ;
static map_t param_map;
int start(gchar *command){
   int mode;
   gchar * extral = NULL;
   int index=0;
   map_init(&fuction_map);
   for (index = 0; index < NUMBER; index++)
   {
	   map_insert_alloc(&fuction_map, &(FUCTION_MAP[index].fun_name),
		   &FUCTION_MAP[index].index, sizeof(int), NULL);
   }
   mode =TS_TYPE_A;// Get_mode(command, extral);
  switch(mode){
   case TS_TYPE_A:
     Process_test_all();
   	 break;
   case TS_TYPE_M:
	   Process_test_module(extral);
	 break;
   case TS_TYPE_S:
	   Process_test_single(extral);
   	 break;	   


  }

}

/*test the system*/
int Process_test_all(){
	/*
	1.json caseindex
	2. loop json cases
	3. comfirm function
	4. construction inparam and out param
	5.run fuction 
	6.check return and outparam
	*/
	gchar *module_name = NULL;
	cJSON * case_index_root= dofile("./case/appmgr/caseindex");
	cJSON *caseindex = cJSON_GetObjectItem(case_index_root, "caseindex");
	cJSON * module = cJSON_GetObjectItem(caseindex, "module");
        int index=0;
	for (index= 0; index < cJSON_GetArraySize(module);index++)
	{
		module_name = cJSON_GetArrayItem(module, index)->string;
		Process_test_module(module_name);
	}
	cJSON_Delete(module); 
	cJSON_Delete(caseindex);
	cJSON_Delete(case_index_root);
}
/*test the module*/
int Process_test_module(gchar* extral){
	gchar* path = "../case/appmgr/";
	gchar* module_full_name = NULL;
	cJSON * testcase = NULL;
	module_full_name = malloc(strlen(path) + strlen(extral)); //get
	strcat(module_full_name, path);
	strcat(module_full_name, extral);
	cJSON * case_list_root = dofile(module_full_name);
	cJSON *caselist = cJSON_GetObjectItem(case_list_root, "caselist");
        int index=0;
	for (index = 0; index < cJSON_GetArraySize(caselist); index++)
	{
		testcase = cJSON_GetArrayItem(caselist, index);
		Process_test_case(testcase);
	}
}
int Process_test_single(gchar* extral){


}

int Process_test_case(cJSON* testcase){
	gchar * return_type = cJSON_GetObjectItem(testcase, "return_type")->valuestring;
        gchar * return_target = cJSON_GetObjectItem(testcase, "return_target")->valuestring;
	gchar * function = cJSON_GetObjectItem(testcase, "function")->valuestring;
	//cJSON *inlist = cJSON_GetObjectItem(testcase, "in");
	//cJSON *outlist = cJSON_GetObjectItem(testcase, "out");
	//cJSON *in = NULL;
	//cJSON *out = NULL;
	gchar * type_value = NULL;
	gchar * value_value = NULL;
	int function_index=-1;
	int param_index = -1;
	int return_value;
	function_index = map_find(&fuction_map, function, NULL);
/*	for (int i = 0; i < cJSON_GetArraySize(inlist); i++)
	{
		in = cJSON_GetArrayItem(inlist, i);
		if (in->type == cJSON_Array){

		}
		else
		{

	
		type_value = cJSON_GetObjectItem(in, "type")->valuestring;
		if (is_base_type()){
			value_value = cJSON_GetObjectItem(in, "value")->valuestring;
			if (strstr(type_value,"int")){

			}
			else if (strstr(type_value, "bool"))
			{

			}
			else if (strstr(type_value, "char"))
			{

			}
		}else{
			value_value = cJSON_GetObjectItem(in, "value")
			param_index = map_find(&param_map, type_value, NULL);
			switch (param_index)
			{
			case 1:{  
					   CtSgwDeviceInfo_t CtSgwDeviceInfo;
					   CtSgwDeviceInfo.Capability=
			}
				break;
			default:
				break;
			}
		}
		}
	}

	
	for (int i = 0; i < cJSON_GetArraySize(outlist); i++)
	{

	}*/

switch(function_index){
   case 0:
   {        
                         /*Calling shell to set  the property of the appdemon*/
                         cJSON *in = cJSON_GetObjectItem(testcase,"in");
                         const char *app_name = cJSON_GetObjectItem(in,"app_name")->valuestring;
                         
                         /*Following the command such as:Install etc */
                         /*app from locate or URL*/
			 return_value = CtSgwInstallApp(app_name);                    
			 Check_return_result(return_value,atoi(return_target)); //check the return's value of the function 
                          

                         //strcpy(target_param1./opt/apps/app_1/lxc.conf,cJSON_GetObjectItem(target, "/opt/apps/app_1/lxc.conf")->valuestring);
                         //CheckCtSgwInstallApp_t(&out_param1,&target_param1);    //check the path
                         //Check_file_exist(file_path);
                      
                         //CtSgwStartApp(const char *app_normal_1);    /*start app_normal_1 waiting for the next testing */
                        // CtSgwInstallApp(const char *app_normal_2);  /*install the app_normal_2  */
                          
                         
  }

          break;
   case 1:
   {        
			 //CtSgwUpgradeApp_t out_param1;
			 //CtSgwUpgradeApp_t target_param1;
                         //cJSON *target = cJSON_GetObjectItem(testcase, "target");
                         /*   */

			 //return_value = CtSgwUpgradeApp(const char *app_name);
			 //Check_return_result(return_value,atoi(return_target));
                         
                         //strcpy(target_param1./opt/apps/app_normal_1/lxc.conf,cJSON_GetObjectItem(target, "/opt/apps/app_normal_1/lxc.conf")->valuestring);
                         //CheckCtSgwUpgradeApp_t(&out_param1,&target_param1);
                         
                        
                         //CtSgwinstallApp(const char *app_normal_3);     /*install all the app waitting for the next testing */
                         //CtSgwStartApp(const char *app_normal_3);
                         //CtSgwinstallApp(const char *app_normal_4);
                         
  }

          break;
  case 2:
   {        
			 //CtSgwDeviceInfo_t out_param1;
			 //CtSgwDeviceInfo_t target_param1;
                         //cJSON *target = cJSON_GetObjectItem(testcase, "target");

			 //return_value = CtSgwUninstallApp(const char *app_name); 
			 //Check_return_result(return_value,atoi(return_target));

                         //strcpy(target_param1./opt/apps/app_normal_2/lxc.conf,cJSON_GetObjectItem(target, "/opt/apps/app_normal_2/lxc.conf")->valuestring);
                         //strcpy(target_param1./etc/dbus-1/system.d/app_normal_2.conf,cJSON_GetObjectItem(target, "/etc/dbus-1/system.d/app_normal_2.conf")->valuestring);
                         //strcpy(target_param1./opt/apps/app_normal_2/config,cJSON_GetObjectItem(target, "/opt/apps/app_normal_2/config")->valuestring);



                         //CheckCtSgwUninstallApp_t(&out_param2,&target_param2);
  }

          break;
  case 3:
   {        
			 //CtSgwDeviceInfo_t out_param1;
			 //CtSgwDeviceInfo_t target_param1;
                         //cJSON *target = cJSON_GetObjectItem(testcase, "target");
			 //return_value = CtSgwStartApp(const char *app_name);
			 //Check_return_result(return_value,atoi(return_target));
                         //CheckCtSgwStartApp_t(&out_param1,&target_param1);
  }

          break;
  case 4:
   {        
			 //CtSgwDeviceInfo_t out_param1;
			 //CtSgwDeviceInfo_t target_param1;
                         //cJSON *target = cJSON_GetObjectItem(testcase, "target");
			 //return_value = CtSgwStopApp(const char *app_name);
			 //Check_return_result(return_value,atoi(return_target));
                         //CheckCtSgwStopApp_t(&out_param1,&target_param1);
  }

          break;
  case 5:
   {




   }
          break;
  case 6:
   {




   }
          break;

}

}
/*
int is_base_type(){
	if
}
Construct_fuction(char *){

}
Construct_param(char * ){

}*/

cJSON*  dofile(gchar *filename)
{
	FILE *f; long len; gchar *data; cJSON *json;

	f = fopen(filename, "rb"); fseek(f, 0, SEEK_END); len = ftell(f); fseek(f, 0, SEEK_SET);
	data = (gchar*)malloc(len + 1); fread(data, 1, len, f); fclose(f);
	//doit(data);
	json = cJSON_Parse(data);
	if (!json) { printf("Error before: [%s]\n", cJSON_GetErrorPtr()); }
	return json;
}
void doit(gchar *text)
{
	gchar *out; cJSON *json;

	json = cJSON_Parse(text);
	if (!json) { printf("Error before: [%s]\n", cJSON_GetErrorPtr()); }
	else
	{
		out = cJSON_Print(json);
		cJSON_Delete(json);
		printf("%s\n", out);
		free(out);
	}
}





