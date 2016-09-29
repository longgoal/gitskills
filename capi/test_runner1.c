#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>
#include "command_util.h"
#include "cJSON.h"
//#include "map.h"

#include "capi-sys-service.h"
#include "capi-variable-type.h"
#include "test_runner.h"
#include "result_check_util.h"

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
#define NUMBER 200
const function_entry_t FUCTION_MAP[NUMBER] = {
	{ "CtSgwGetDeviceInfo", CtSgwGetDeviceInfo_NUM},
	{ "CtSgwGetNetworkInfo", CtSgwGetNetworkInfo_NUM},
	{ "CtSgwGetWANConnectionObjs", CtSgwGetWANConnectionObjs_NUM},
	{ "CtSgwGetWANConnection",CtSgwGetWANConnection_NUM},
	{ "CtSgwGetWANConnectionByName",CtSgwGetWANConnectionByName_NUM},
	{ "CtSgwGetInternetWANConnection",CtSgwGetInternetWANConnection_NUM},
	{ "CtSgwGetWiFiInfo", CtSgwGetWiFiInfo_NUM},
	{ "CtSgwWiFiDiscClient", CtSgwWiFiDiscClient_NUM},
	{ "CtSgwWiFiSetSameSSID", CtSgwWiFiSetSameSSID_NUM},
	{ "CtSgwWiFiCancelSameSSID", CtSgwWiFiCancelSameSSID_NUM},
	{ "CtSgwWiFiSetEnable", CtSgwWiFiSetEnable_NUM},
	{ "CtSgwGetPONInfo", CtSgwGetPONInfo_NUM},
	{ "CtSgwGetVoIPInfo", CtSgwGetVoIPInfo_NUM},
	{ "CtSgwGetLANHostMgr", CtSgwGetLANHostMgr_NUM},
	{ "CtSgwSetLANHostMgr",CtSgwSetLANHostMgr_NUM},
	{ "CtSgwGetLANHostObjs",CtSgwGetLANHostObjs_NUM},
	{ "CtSgwGetLANHost",CtSgwGetLANHost_NUM},
	{ "CtSgwSetLANHost", CtSgwSetLANHost_NUM},
	{ "CtSgwSetHttpDownloadTestURL",CtSgwSetHttpDownloadTestURL_NUM},
	{ "CtSgwGetHttpDownloadTestURL",CtSgwGetHttpDownloadTestURL_NUM},
	{ "CtSgwStartHttpDownloadTest", CtSgwStartHttpDownloadTest_NUM},
	{ "CtSgwGetHttpDownloadTestResult", CtSgwGetHttpDownloadTestResult_NUM},
	{ "CtSgwSetWPSConfig",CtSgwSetWPSConfig_NUM},
	{ "CtSgwGetWPSConfig", CtSgwGetWPSConfig_NUM},
	{ "CtSgwSetWPS", CtSgwSetWPS_NUM},
	{ "CtSgwGetWLANDeviceObjs",CtSgwGetWLANDeviceObjs_NUM},
	{ "CtSgwGetWLANDevice",CtSgwGetWLANDevice_NUM},
	{ "CtSgwGetWLANDeviceBySSID",CtSgwGetWLANDeviceBySSID_NUM},
	{ "CtSgwSetWLANDevice", CtSgwSetWLANDevice_NUM},
	{ "CtSgwGetWiFiTimer", CtSgwGetWiFiTimer_NUM},
	{ "CtSgwSetWiFiTimer", CtSgwSetWiFiTimer_NUM},
	{ "CtSgwGetWiFiExTimerObjs", CtSgwGetWiFiExTimerObjs_NUM},
	{ "CtSgwGetWiFiExTimer", CtSgwGetWiFiExTimer_NUM},
	{ "CtSgwSetWiFiExTimer", CtSgwSetWiFiExTimer_NUM},
	{ "CtSgwAddWiFiExTimer", CtSgwAddWiFiExTimer_NUM},
	{ "CtSgwDelWiFiExTimer", CtSgwDelWiFiExTimer_NUM},
	{ "CtSgwGetLED", CtSgwGetLED_NUM},
	{ "CtSgwSetLED", CtSgwSetLED_NUM},
	{ "CtSgwGetSleepTimerObjs", CtSgwGetSleepTimerObjs_NUM},
	{ "CtSgwGetSleepTimer", CtSgwGetSleepTimer_NUM},
	{ "CtSgwSetSleepTimer", CtSgwSetSleepTimer_NUM},
	{ "CtSgwAddSleepTimer", CtSgwAddSleepTimer_NUM},
	{ "CtSgwDelSleepTimer", CtSgwDelSleepTimer_NUM},
	{ "CtSgwSysCmdSetDateTime", CtSgwSysCmdSetDateTime_NUM},
	{ "CtSgwSysCmdSetDevName",CtSgwSysCmdSetDevName_NUM},
	{ "CtSgwSysCmdCheckUAPasswd", CtSgwSysCmdCheckUAPasswd_NUM},
	{ "CtSgwSysCmdSetUAPasswd", CtSgwSysCmdSetUAPasswd_NUM},
	{ "CtSgwSysCmdCheckTAPasswd", CtSgwSysCmdCheckTAPasswd_NUM},
	{ "CtSgwGetPPPoEConfig", CtSgwGetPPPoEConfig_NUM},
	{ "CtSgwGetDHCPServer", CtSgwGetDHCPServer_NUM},
	{ "CtSgwSetDHCPServer", CtSgwSetDHCPServer_NUM},
	{ "CtSgwGetPortMappingObjs", CtSgwGetPortMappingObjs_NUM},
	{ "CtSgwGetPortMapping", CtSgwGetPortMapping_NUM},
	{ "CtSgwAddPortMapping", CtSgwAddPortMapping_NUM},
	{ "CtSgwDelPortMapping", CtSgwDelPortMapping_NUM},
	{ "CtSgwSetPortMapping", CtSgwSetPortMapping_NUM},
	{ "CtSgw_USBMount", CtSgw_USBMount_NUM},
	{ "CtSgw_USBUnMount", CtSgw_USBUnMount_NUM},
	{ "CtSgw_USBSetLabel", CtSgw_USBSetLabel_NUM},
	{ "CtSgw_GetUSBDeviceObjs", CtSgw_GetUSBDeviceObjs_NUM},
	{ "CtSgw_GetUSBDevice", CtSgw_GetUSBDevice_NUM},
	{ "CtSgw_NAS_GetFileNum", CtSgw_NAS_GetFileNum_NUM},
	{ "CtSgw_NAS_ListFolder", CtSgw_NAS_ListFolder_NUM},
	{ "CtSgw_NAS_CreateFolter", CtSgw_NAS_CreateFolter_NUM},
	{ "CtSgw_NAS_ReName", CtSgw_NAS_ReName_NUM},
	{ "CtSgw_NAS_Remove", CtSgw_NAS_Remove_NUM},
	{ "CtSgw_NAS_Move", CtSgw_NAS_Move_NUM},
	{ "CtSgw_NAS_Copy", CtSgw_NAS_Copy_NUM},
	{ "CtSgw_NAS_GetCopyProgress", CtSgw_NAS_GetCopyProgress_NUM},
	{ "CtSgwAddVPNConnection", CtSgwAddVPNConnection_NUM},
	{ "CtSgwDelVPNConnByName", CtSgwDelVPNConnByName_NUM},
	{ "CtSgwAttachVPNConnection", CtSgwAttachVPNConnection_NUM},
	{ "CtSgwDetachVPNConnection", CtSgwDetachVPNConnection_NUM},
	{ "CtSgwGetVPNConnectionStatus", CtSgwGetVPNConnectionStatus_NUM},
	{ "CtSgwSetDNSServerConfig", CtSgwSetDNSServerConfig_NUM},
	{ "CtSgwGetDNSServerConfig", CtSgwGetDNSServerConfig_NUM},
	{ "CtSgwFlushDNS", CtSgwFlushDNS_NUM},
	{ "CtSgwGetDDNSServerObjs",CtSgwGetDDNSServerObjs_NUM},
	{ "CtSgwGetDDNSServerInstance", CtSgwGetDDNSServerInstance_NUM},
	{ "CtSgwSetDDNSServerInstance",CtSgwSetDDNSServerInstance_NUM},
	{ "CtSgwAddDDNSServerInstance", CtSgwAddDDNSServerInstance_NUM},
	{ "CtSgwDelDDNSServerInstance",CtSgwDelDDNSServerInstance_NUM},
	{ "CtSgw_SetFtpServer", CtSgw_SetFtpServer_NUM},
	{ "CtSgw_GetFTPServer", CtSgw_GetFTPServer_NUM},
	{ "CtSgw_GetFTPAccountObjs", CtSgw_GetFTPAccountObjs_NUM},
	{ "CtSgw_GetFTPAccount", CtSgw_GetFTPAccount_NUM},
	{ "CtSgw_AddFtpAccount", CtSgw_AddFtpAccount_NUM},
	{ "CtSgw_DelFtpAccount", CtSgw_DelFtpAccount_NUM},
	{ "CtSgw_GetSambaServer",CtSgw_GetSambaServer_NUM},
	{ "CtSgw_SetSambaServer", CtSgw_SetSambaServer_NUM},
	{ "CtSgw_GetSambaAccountObjs", CtSgw_GetSambaAccountObjs_NUM},
	{ "CtSgw_GetSambaAccount", CtSgw_GetSambaAccount_NUM},
	{ "CtSgw_AddSambaAccount", CtSgw_AddSambaAccount_NUM},
	{ "CtSgw_DelSambaAccount", CtSgw_DelSambaAccount_NUM},
	{ "CtSgw_GetHttpServer", CtSgw_GetHttpServer_NUM},
	{ "CtSgw_SetHttpServer", CtSgw_SetHttpServer_NUM},
	{ "CtSgwSysCmdSetLOID", CtSgwSysCmdSetLOID_NUM},
	{ "CtSgwSysCmdRegisterLOID", CtSgwSysCmdRegisterLOID_NUM},
	{ "CtSgwSysCmdCheckLOID", CtSgwSysCmdCheckLOID_NUM},
	{ "CtSgwSysCmdReboot", CtSgwSysCmdReboot_NUM},
	{ "CtSgwSysCmdRestore", CtSgwSysCmdRestore_NUM},
	{ "CtSgwSysCmdUpgrade", CtSgwSysCmdUpgrade_NUM},
        { "CtSgwDelVPNConnection", CtSgwDelVPNConnection_NUM},
        { "CtSgwWiFiSetRatePriority", CtSgwWiFiSetRatePriority_NUM},
        { "CtSgwDelLANHost", CtSgwDelLANHost_NUM},
        { "CtSgwSysCmdUploadTroubleLocationInfo", CtSgwSysCmdUploadTroubleLocationInfo_NUM},
        { "CtSgw_USBFormat", CtSgw_USBFormat_NUM},
        { "CtSgwGetDNSTunnelObjs", CtSgwGetDNSTunnelObjs_NUM},
        { "CtSgwSetDNSTunnel", CtSgwSetDNSTunnel_NUM},
        { "CtSgwDelDNSTunnel", CtSgwDelDNSTunnel_NUM},
	{ "CtSgwDNSTunnelDetachDomain", CtSgwDNSTunnelDetachDomain_NUM},
	{ "CtSgwDNSTunnelAttachDomain", CtSgwDNSTunnelAttachDomain_NUM},
	{ "CtSgwGetPlatformService", CtSgwGetPlatformService_NUM},
	{ "CtSgwSetPlatformService", CtSgwSetPlatformService_NUM},
        { "CtSgwAddDNSTunnel", CtSgwAddDNSTunnel_NUM},
	{ "GVariant", GVariant_NUM}
        
        
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
//static map_t fuction_map ;
//static map_t param_map;
int start(gchar *mode,gchar *extral){
	int Type=TS_TYPE_A;
	//gchar * extral = NULL;
	int index=0;
	// map_init(&fuction_map);
	// for (index = 0; index < NUMBER; index++)
	// {
	//	   map_insert_alloc(&fuction_map, &(FUCTION_MAP[index].fun_name),
	//		   &FUCTION_MAP[index].index, sizeof(int), NULL);
	// }
	//g_print("Test Running start\n");
	Type =Get_mode(mode);
	switch(Type){
	case TS_TYPE_A:{
		Process_test_all();
		break;
	}
	case TS_TYPE_M:
		Process_test_module(extral,NULL);
		break;
	case TS_TYPE_S:
		Process_test_single(extral);
		break;	
	case TS_TYPE_Y:
	   	Process_test_exception(extral);
		break;	
	}

}

typedef struct capi_result{
	char capi_name[STR_LEN_64];
	char capi_result[STR_LEN_16];
	int capi_return;
        double capi_time;
}capi_result_t;



int fill_capi_result(const char *name,const char*result,int ret,double time)
{
	 
	capi_result_t node;
	memset(&node,0,sizeof(capi_result_t));
	strcpy(node.capi_name,name);
	strcpy(node.capi_result,result);
	node.capi_return = ret;
        node.capi_time=time;
	xls_write(&node);
	return 0;
}

int xls_write(capi_result_t* node)
{
	FILE* fp = NULL; 

	fp = fopen("/tmp/capi.xls","a+");
	if(NULL == fp)
	{
		g_print("fopen error!\n");
		return -1;
	}

	fprintf(fp,"%s \t %s \t %d \t %lf\n",node->capi_name,node->capi_result,node->capi_return,node->capi_time);
	
	fclose(fp);
	return 0;
}

int Process_test_case_init(){
        g_print("Process_test_case_init+++++++++\n");
        FILE* fp = NULL; 
	fp = fopen("/tmp/capi.xls","a+");
	if(NULL == fp)
	{
		g_print("fopen error!\n");
		return -1;
	}
       
            fprintf(fp,"%s \t %s \t %s \t %s\n","API","Result","Return_value","Time");
            fclose(fp);
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
	cJSON * case_index_root= dofile("/tmp/case1/caseindex");
	cJSON *caseindex = cJSON_GetObjectItem(case_index_root, "caseindex");
	cJSON * module = cJSON_GetObjectItem(caseindex, "module");
	int index=0;
	//g_print("Test Running Process_test_all %p\n",case_index_root);
	//g_print("Test Running Process_test_all %p\n",caseindex);
	//g_print("Test Running Process_test_all module %p\n",module);
	for (index= 0; index < cJSON_GetArraySize(module);index++)
	{       
		module_name = cJSON_GetArrayItem(module, index)->child->string;
		//g_print("Test Running Process_test_all %s\n",module_name);
		Process_test_module(module_name,NULL);
	}
	cJSON_Delete(module);
	cJSON_Delete(caseindex);
	cJSON_Delete(case_index_root);
}
/*test the module*/
int Process_test_module(gchar* extral,gchar* extral2){
	gchar* path = "/tmp/case1/";
	gchar* module_full_name = NULL;
	cJSON * testcase = NULL;

	double start,end,t_diff;
	struct timeval t_start,t_end,t_cont;
        gboolean singlecase= extral2?TRUE:FALSE;
	//g_print("Test Running Process_test_module1 %s\n",extral);
	//g_print("Test Running Process_test_module2 %d\n",strlen(path));
	//g_print("Test Running Process_test_module3 %d\n",strlen(extral));
	module_full_name = (char*)malloc(strlen(path) + strlen(extral)+1); //get
	memset(module_full_name,0,strlen(path) + strlen(extral)+1);
	//g_print("Test Running Process_test_module4 %p\n",module_full_name);
	strcat(module_full_name, path);
	strcat(module_full_name, extral);
	//g_print("Test Running Process_test_module5 %s\n",module_full_name);
	cJSON * case_list_root = dofile(module_full_name);
	//g_print("Test Running Process_test_module6\n");
	cJSON *caselist = cJSON_GetObjectItem(case_list_root, "caselist");
	int index=0;
	//g_print("Test Running Process_test_module7,%d\n",cJSON_GetArraySize(caselist));
         
	for (index = 0; index < cJSON_GetArraySize(caselist); index++)
	{       
		testcase = cJSON_GetArrayItem(caselist, index);
		//g_print("Test Running Process_test_module8 %p\n",testcase->child);
                if(singlecase)
                  {
                    //g_print("Test Running Process_test_module9 %p\n",testcase->child);
                    if(!strcmp(extral2,cJSON_GetObjectItem(testcase->child, "fuction")->valuestring))
                       {
                         //g_print("Test Running Process_test_module10 %p\n",testcase->child);
                         Process_test_case(testcase->child);
		       }
               	   }
                else{
		gettimeofday(&t_start,0); 
		start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
		Process_test_case(testcase->child);
                //g_print("Test Running Process_test_module11 %p\n",testcase->child);
		//sleep(5);
		gettimeofday(&t_end,0);
		end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
		t_diff = end - start;
		g_print("time:%lfms\n",t_diff);
                }
	}
}
int Process_test_single(gchar* extral){
	cJSON * case_index_root= dofile("/tmp/case1/caseindex");
	cJSON *caseindex = cJSON_GetObjectItem(case_index_root, "caseindex");
	cJSON * module = cJSON_GetObjectItem(caseindex, "module");
        cJSON * caselist;
        gchar *module_name = NULL;
        gchar* fuction=NULL;
        int index,index2;
        //g_print("Test Running Process_test_single extral %s\n",extral);
	for (index= 0; index < cJSON_GetArraySize(module);index++)
	{       
                module_name = cJSON_GetArrayItem(module, index)->child->string;
		caselist = cJSON_GetArrayItem(module, index)->child;
		//g_print("Test Running Process_test_single %s\n",module_name);
                //g_print("Test Running Process_test_single %d\n",cJSON_GetArraySize(caselist));
                //g_print("Test Running Process_test_single fuction %s\n",cJSON_Print(caselist));
                for (index2= 0; index2 < cJSON_GetArraySize(caselist);index2++){
                  fuction=cJSON_GetArrayItem(caselist, index2)->valuestring;
                     // g_print("Test Running Process_test_single fuction0 %s\n",fuction);
                     // fuction=cJSON_GetArrayItem(caselist, index2)->string;
                     // g_print("Test Running Process_test_single fuction===== %s\n",fuction);
                //g_print("fuction============ %s\n",fuction);
                //g_print("extral============= %s\n",extral);
                 if(!strcmp(extral,fuction)){
                   Process_test_module(module_name,fuction);
                   return 0;
                 }
               }	
	}
}

int Process_test_exception(gchar* extral){
	gchar* path = "/tmp/case1/caselist3";
	//gchar* module_full_name = NULL;
	cJSON * testcase = NULL;

	//double start,end,t_diff;
	//struct timeval t_start,t_end,t_cont;
       // gboolean singlecase= extral2?TRUE:FALSE;
	g_print("Test Running Process_test_module1 %s\n",extral);
	//g_print("Test Running Process_test_module2 %d\n",strlen(path));
	//g_print("Test Running Process_test_module2 %d\n",strlen(extral));
	//module_full_name = (char*)malloc(strlen(path) + strlen(extral)+1); //get
	//memset(module_full_name,0,strlen(path) + strlen(extral)+1);
	//g_print("Test Running Process_test_module2 %p\n",module_full_name);
	//strcat(module_full_name, path);
	//strcat(module_full_name, extral);
	//g_print("Test Running Process_test_module3 %s\n",module_full_name);
	cJSON * case_list_root = dofile(path);
	g_print("Test Running Process_test_module4\n");
	cJSON *caselist = cJSON_GetObjectItem(case_list_root, "caselist");
	int index=0;
	g_print("Test Running Process_test_module5,%d\n",cJSON_GetArraySize(caselist));
         
	for (index = 0; index < cJSON_GetArraySize(caselist); index++)
	{       
		testcase = cJSON_GetArrayItem(caselist, index);
		//g_print("Test Running Process_test_module6 %p\n",testcase->child);

                //g_print("===before");
                if(!strcmp(extral,cJSON_GetObjectItem(testcase->child, "fuction")->valuestring)){
                g_print("=========Process_test_exception===before");
		Process_test_case(testcase->child);
                g_print("=========Process_test_exception===end");
		}

	}
}


int find(char* function_name){
	int index=0;
	for(index=0;index<NUMBER;index++){
                //g_print("Test Running find %d, %s,%s\n",index,FUCTION_MAP[index].fun_name,function_name);
		if(!strcmp(FUCTION_MAP[index].fun_name,function_name))
		{
			//g_print("Test Running find %d\n",index);
			return FUCTION_MAP[index].index;
		}
	}
	return -1;
}


int Process_test_case(cJSON* testcase){


        //FILE* fp = NULL; 
	//fp = fopen("/tmp/capi.xls","a+");
	//if(NULL == fp)
	//{
	//	g_print("fopen error!\n");
	//	return -1;
	//}
      
       //fprintf(fp,"%s \t %s \t %s \t %s\n","API","Result","Return_value","Time");   
       //fclose(fp);

	gchar * return_type =NULL;// cJSON_GetObjectItem(testcase, "return")->valuestring;
	gchar * return_target =NULL; //cJSON_GetObjectItem(testcase, "return_target")->valuestring;
	gchar * function_name =NULL;// cJSON_GetObjectItem(testcase, "function")->valuestring;
	//cJSON *inlist = cJSON_GetObjectItem(testcase, "in");
	//cJSON *outlist = cJSON_GetObjectItem(testcase, "out");
	//cJSON *in = NULL;
	//cJSON *out = NULL;
	gchar * type_value = NULL;
	gchar * value_value = NULL;
	int function_index=-1;
	int param_index = -1;
	int return_value;
	g_print("Test Running Process_test_case1 %p\n",testcase);
	return_type = cJSON_GetObjectItem(testcase, "return")->valuestring;
	g_print("Test Running Process_test_case2 %p\n",return_type);
	return_target = cJSON_GetObjectItem(testcase, "return_target")->valuestring;
	g_print("Test Running Process_test_case3 %p\n",return_target);
	function_name = cJSON_GetObjectItem(testcase, "fuction")->valuestring;
g_print("###################################################\n");
	g_print("Test Running Process_test_case %s\n",function_name);
	function_index = find(function_name);

	//g_print("Test Running Process_test_case5 %d\n",function_index);
	switch(function_index){
	case CtSgwGetDeviceInfo_NUM:
		{
			
			CtSgwDeviceInfo_t out_param1;
			CtSgwDeviceInfo_t target_param1;
			cJSON *target = cJSON_GetObjectItem(testcase, "target");
			cJSON *CtSgwDeviceInfo = cJSON_GetObjectItem(target, "CtSgwDeviceInfo_t");

                double start,end,t_diff=0; 
		struct timeval t_start,t_end,t_cont;
		gettimeofday(&t_start,0); 
		start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

			return_value = CtSgwGetDeviceInfo(&out_param1);


			if(FALSE == Check_return_result(return_value,atoi(return_target)))
			{	
				fill_capi_result("CtSgwGetDeviceInfo","failed",return_value,t_diff);
				break;
			}

		gettimeofday(&t_end,0);
		end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
		t_diff = end - start;
		g_print("gaohanyu time:%lfms\n",t_diff);

			target_param1.BusinessStatus=atoi(cJSON_GetObjectItem(CtSgwDeviceInfo, "BusinessStatus")->valuestring);			
			strcpy(target_param1.MAC,cJSON_GetObjectItem(CtSgwDeviceInfo, "MAC")->valuestring);
			strcpy(target_param1.ITMSProtocolVersion,cJSON_GetObjectItem(CtSgwDeviceInfo, "ITMSProtocolVersion")->valuestring);
			strcpy(target_param1.SWVersion,cJSON_GetObjectItem(CtSgwDeviceInfo, "SWVersion")->valuestring);
			strcpy(target_param1.HDVersion,cJSON_GetObjectItem(CtSgwDeviceInfo, "HDVersion")->valuestring);
			strcpy(target_param1.ProductClass,cJSON_GetObjectItem(CtSgwDeviceInfo, "ProductClass")->valuestring);
			strcpy(target_param1.CPUClass,cJSON_GetObjectItem(CtSgwDeviceInfo, "CPUClass")->valuestring);
			strcpy(target_param1.DevType,cJSON_GetObjectItem(CtSgwDeviceInfo, "DevType")->valuestring);
			strcpy(target_param1.DevType1,cJSON_GetObjectItem(CtSgwDeviceInfo, "DevType1")->valuestring);
			strcpy(target_param1.Capability,cJSON_GetObjectItem(CtSgwDeviceInfo, "Capability")->valuestring);
			target_param1.FlashSize=atoi(cJSON_GetObjectItem(CtSgwDeviceInfo, "FlashSize")->valuestring);
			target_param1.RamSize=atoi(cJSON_GetObjectItem(CtSgwDeviceInfo, "RamSize")->valuestring);
			strcpy(target_param1.DevName,cJSON_GetObjectItem(CtSgwDeviceInfo, "DevName")->valuestring);
			target_param1.CPUUsage=atoi(cJSON_GetObjectItem(CtSgwDeviceInfo, "CPUUsage")->valuestring);
			target_param1.MEMUsage=atoi(cJSON_GetObjectItem(CtSgwDeviceInfo, "MEMUsage")->valuestring);
			target_param1.FlashUsage=atoi(cJSON_GetObjectItem(CtSgwDeviceInfo, "FlashUsage")->valuestring);
			target_param1.SysDuration=atoi(cJSON_GetObjectItem(CtSgwDeviceInfo, "SysDuration")->valuestring);
			strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgwDeviceInfo, "path"),"str")->valuestring);
			if(FALSE == CheckCtSgwDeviceInfo_t(&out_param1,&target_param1))
				fill_capi_result("CtSgwGetDeviceInfo","failed",return_value,t_diff);
			else
				fill_capi_result("CtSgwGetDeviceInfo","pass",return_value,t_diff);
		}

		break;
	case CtSgwGetNetworkInfo_NUM:{
			    
			   CtSgwNetworkInfo_t out_param1;// define out_param
			   CtSgwNetworkInfo_t target_param1;
			   cJSON *target = cJSON_GetObjectItem(testcase,"target");//get the target of the testcae
			   cJSON *CtSgwNetworkInfo = cJSON_GetObjectItem(target,"CtSgwNetworkInfo_t"); 
                         double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
                        
			   return_value = CtSgwGetNetworkInfo(&out_param1);       //get the return's value of the networkinfo
			   if(FALSE == Check_return_result(return_value,atoi(return_target)))
			   {	
				fill_capi_result("CtSgwGetNetworkInfo","failed",return_value,t_diff);
				break;
			   }

			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;

			   target_param1.UPLink=atoi(cJSON_GetObjectItem(CtSgwNetworkInfo, "UPLink")->valuestring);  
			   target_param1.IPV6=atoi(cJSON_GetObjectItem(CtSgwNetworkInfo, "IPV6")->valuestring);   
			   target_param1.VLANbind=atoi(cJSON_GetObjectItem(CtSgwNetworkInfo, "VLANbind")->valuestring);   
			   strcpy(target_param1.WiFiMode,cJSON_GetObjectItem(CtSgwNetworkInfo, "WiFiMode")->valuestring);   
			   target_param1.PONDuration=atoi(cJSON_GetObjectItem(CtSgwNetworkInfo, "PONDuration")->valuestring);   
			   target_param1.PPPoEDuration=atoi(cJSON_GetObjectItem(CtSgwNetworkInfo, "PPPoEDuration")->valuestring);  
			   target_param1.LAN1Status=atoi(cJSON_GetObjectItem(CtSgwNetworkInfo, "LAN1Status")->valuestring);  
			   target_param1.LAN2Status=atoi(cJSON_GetObjectItem(CtSgwNetworkInfo, "LAN2Status")->valuestring);  
			   target_param1.LAN3Status=atoi(cJSON_GetObjectItem(CtSgwNetworkInfo, "LAN3Status")->valuestring);  
			   target_param1.LAN4Status=atoi(cJSON_GetObjectItem(CtSgwNetworkInfo, "LAN4Status")->valuestring);   
			   strcpy(target_param1.WANLinkStatus,cJSON_GetObjectItem(CtSgwNetworkInfo, "WANLinkStatus")->valuestring); 
			   strcpy(target_param1.WIFIModuleStatus,cJSON_GetObjectItem(CtSgwNetworkInfo, "WIFIModuleStatus")->valuestring);  
			   strcpy(target_param1.WANConnectionStatus,cJSON_GetObjectItem(CtSgwNetworkInfo, "WANConnectionStatus")->valuestring);  
			   strcpy(target_param1.PPPoEDialReason,cJSON_GetObjectItem(CtSgwNetworkInfo, "PPPoEDialReason")->valuestring);  
			   strcpy(target_param1.IPV6_WANConnectionStatus,cJSON_GetObjectItem(CtSgwNetworkInfo, "IPV6_WANConnectionStatus")->valuestring);  
			   strcpy(target_param1.IPV6_PPPoEDialReason,cJSON_GetObjectItem(CtSgwNetworkInfo, "IPV6_PPPoEDialReason")->valuestring);   
			   strcpy(target_param1.LANIPAddr,cJSON_GetObjectItem(CtSgwNetworkInfo, "LANIPAddr")->valuestring);
			   strcpy(target_param1.WANIPAddr,cJSON_GetObjectItem(CtSgwNetworkInfo, "WANIPAddr")->valuestring);  
			   strcpy(target_param1.WANIPV6Addr,cJSON_GetObjectItem(CtSgwNetworkInfo, "WANIPV6Addr")->valuestring);  
			   target_param1.WiFiBytes=atoi(cJSON_GetObjectItem(CtSgwNetworkInfo, "WiFiBytes")->valuestring);  
			   target_param1.WiFiTxBytes=atoi(cJSON_GetObjectItem(CtSgwNetworkInfo, "WiFiTxBytes")->valuestring); 
			   target_param1.WiFiRxBytes=atoi(cJSON_GetObjectItem(CtSgwNetworkInfo, "WiFiRxBytes")->valuestring);  
			   target_param1.WANBytes=atoi(cJSON_GetObjectItem(CtSgwNetworkInfo, "WANBytes")->valuestring);  
			   target_param1.WANTxBytes=atoi(cJSON_GetObjectItem(CtSgwNetworkInfo, "WANTxBytes")->valuestring);  
			   target_param1.WANRxBytes=atoi(cJSON_GetObjectItem(CtSgwNetworkInfo, "WANRxBytes")->valuestring);   
			   strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgwNetworkInfo, "path"),"str")->valuestring);
			   if (FALSE == CheckCtSgwNetworkInfo_t(&out_param1,&target_param1))
				 fill_capi_result("CtSgwGetNetworkInfo","failed",return_value,t_diff);
			   else
				 fill_capi_result("CtSgwGetNetworkInfo","pass",return_value,t_diff);
		   }

		   break;
	case CtSgwGetWANConnectionObjs_NUM:{
			    
			   CtSgwWANConnectionInfo_t *out_param1 = NULL;
			   guint32 out_count;
			   guint32 target_count;
			   CtSgwWANConnectionInfo_t target_param1;
			   cJSON *target = cJSON_GetObjectItem(testcase,"target");

 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

			   return_value = CtSgwGetWANConnectionObjs(&out_param1,&out_count);

			   if(FALSE == Check_return_result(return_value,atoi(return_target)))
			   {	
				 fill_capi_result("CtSgwGetWANConnectionObjs","failed",return_value,t_diff);
				g_free(out_param1);
				break;
			   }

			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;

			   cJSON * CtSgwWANConnectionInfo = cJSON_GetObjectItem(target, "CtSgwWANConnectionInfo_t");

			   target_count=atoi(cJSON_GetObjectItem(target, "count")->valuestring);
			   Check_int(out_count,target_count);
			   if(out_count > target_count)
			   {
				out_count = target_count;
			   }
			   else if(out_count == 0)
			   {
				fill_capi_result("CtSgwGetWANConnectionObjs","pass",return_value,t_diff);
				g_free(out_param1);
				break;
			   }
			   int index=0;
			   for (index = 0; index < out_count; index++)
			   { 
				   strcpy(target_param1.Index,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANConnectionInfo, index), "Index")->valuestring);  
				   strcpy(target_param1.IfName,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANConnectionInfo, index), "IfName")->valuestring);   
				   strcpy(target_param1.ServiceList,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANConnectionInfo, index), "ServiceList")->valuestring);   
				   strcpy(target_param1.ConnectionType,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANConnectionInfo, index), "ConnectionType")->valuestring);  
				   target_param1.VLANID=atoi(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANConnectionInfo, index), "VLANID")->valuestring);   
				   target_param1.VLAN8021P=atoi(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANConnectionInfo, index), "VLAN8021P")->valuestring);  
				   strcpy(target_param1.Protocol,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANConnectionInfo, index), "Protocol")->valuestring);  
				   strcpy(target_param1.ConnectionStatus,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANConnectionInfo, index), "ConnectionStatus")->valuestring);   
				   strcpy(target_param1.IPAddress,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANConnectionInfo, index), "IPAddress")->valuestring);   
				   strcpy(target_param1.SubnetMask,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANConnectionInfo, index), "SubnetMask")->valuestring);  
				   strcpy(target_param1.Gateway,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANConnectionInfo, index), "Gateway")->valuestring);   
				   strcpy(target_param1.DNS1,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANConnectionInfo, index), "DNS1")->valuestring);    
				   strcpy(target_param1.DNS2,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANConnectionInfo, index), "DNS2")->valuestring);  
				   strcpy(target_param1.IPV6_ConnectionStatus,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANConnectionInfo, index), "IPV6_ConnectionStatus")->valuestring);   
				   strcpy(target_param1.IPV6_IPAddress,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANConnectionInfo, index), "IPV6_IPAddress")->valuestring);   
				   strcpy(target_param1.IPV6_PrefixLength,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANConnectionInfo, index), "IPV6_PrefixLength")->valuestring);  
				   strcpy(target_param1.IPV6_Gateway,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANConnectionInfo, index), "IPV6_Gateway")->valuestring);   
				   strcpy(target_param1.IPV6_DNS1,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANConnectionInfo, index), "IPV6_DNS1")->valuestring);  
				   strcpy(target_param1.IPV6_DNS2,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANConnectionInfo, index), "IPV6_DNS2")->valuestring);  
				   strcpy(target_param1.IPV6_Prefix,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANConnectionInfo, index), "IPV6_Prefix")->valuestring);   
				   target_param1.RxBytes=atoi(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANConnectionInfo, index), "RxBytes")->valuestring);   
				   target_param1.TxBytes=atoi(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANConnectionInfo, index), "TxBytes")->valuestring);  
				   target_param1.RxPkts=atoi(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANConnectionInfo, index), "RxPkts")->valuestring);   
				   target_param1.TxPkts=atoi(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANConnectionInfo, index), "TxPkts")->valuestring);   
				   strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANConnectionInfo, index), "path"),"str")->valuestring);

			  	  if (FALSE == CheckCtSgwWANConnectionInfo_t(&(out_param1[index]),&target_param1))
					 fill_capi_result("CtSgwGetWANConnectionObjs","failed",return_value,t_diff);
			          else
					 fill_capi_result("CtSgwGetWANConnectionObjs","pass",return_value,t_diff);
			   }
		   g_free(out_param1);
		   }          
		   break;

	case CtSgwGetWANConnection_NUM:{
			    
			   CtSgwWANConnectionInfo_t out_param1;
			   CtSgwWANConnectionInfo_t target_param1;
			   CtSgwObjPath_t path;
			   cJSON *target = cJSON_GetObjectItem(testcase,"target");
			   cJSON *CtSgwWANConnectionInfo = cJSON_GetObjectItem(target,"CtSgwWANConnectionInfo_t");
			   cJSON *in = cJSON_GetObjectItem(testcase,"in");
			   strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring); 

 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
			   return_value = CtSgwGetWANConnection(path,&out_param1);       
			   if(FALSE == Check_return_result(return_value,atoi(return_target)))
			   {	
				 fill_capi_result("CtSgwGetWANConnection","failed",return_value,t_diff);
				break;
			   }

			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;

			   strcpy(target_param1.Index,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "Index")->valuestring);  
			   strcpy(target_param1.IfName,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "IfName")->valuestring);   
			   strcpy(target_param1.ServiceList,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "ServiceList")->valuestring);   
			   strcpy(target_param1.ConnectionType,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "ConnectionType")->valuestring);  
			   target_param1.VLANID=atoi(cJSON_GetObjectItem(CtSgwWANConnectionInfo, "VLANID")->valuestring);   
			   target_param1.VLAN8021P=atoi(cJSON_GetObjectItem(CtSgwWANConnectionInfo, "VLAN8021P")->valuestring);  
			   strcpy(target_param1.Protocol,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "Protocol")->valuestring);  
			   strcpy(target_param1.ConnectionStatus,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "ConnectionStatus")->valuestring);   
			   strcpy(target_param1.IPAddress,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "IPAddress")->valuestring);   
			   strcpy(target_param1.SubnetMask,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "SubnetMask")->valuestring);  
			   strcpy(target_param1.Gateway,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "Gateway")->valuestring);   
			   strcpy(target_param1.DNS1,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "DNS1")->valuestring);    
			   strcpy(target_param1.DNS2,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "DNS2")->valuestring);  
			   strcpy(target_param1.IPV6_ConnectionStatus,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "IPV6_ConnectionStatus")->valuestring);   
			   strcpy(target_param1.IPV6_IPAddress,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "IPV6_IPAddress")->valuestring);   
			   strcpy(target_param1.IPV6_PrefixLength,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "IPV6_PrefixLength")->valuestring);  
			   strcpy(target_param1.IPV6_Gateway,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "IPV6_Gateway")->valuestring);   
			   strcpy(target_param1.IPV6_DNS1,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "IPV6_DNS1")->valuestring);  
			   strcpy(target_param1.IPV6_DNS2,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "IPV6_DNS2")->valuestring);  
			   strcpy(target_param1.IPV6_Prefix,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "IPV6_Prefix")->valuestring);   
			   target_param1.RxBytes=atoi(cJSON_GetObjectItem(CtSgwWANConnectionInfo, "RxBytes")->valuestring);   
			   target_param1.TxBytes=atoi(cJSON_GetObjectItem(CtSgwWANConnectionInfo, "TxBytes")->valuestring);  
			   target_param1.RxPkts=atoi(cJSON_GetObjectItem(CtSgwWANConnectionInfo, "RxPkts")->valuestring);   
			   target_param1.TxPkts=atoi(cJSON_GetObjectItem(CtSgwWANConnectionInfo, "TxPkts")->valuestring);  
			   strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgwWANConnectionInfo, "path"),"str")->valuestring);
			   if (FALSE == CheckCtSgwWANConnectionInfo_t(&out_param1,&target_param1))
				 fill_capi_result("CtSgwGetWANConnection","failed",return_value,t_diff);
			   else
				 fill_capi_result("CtSgwGetWANConnection","pass",return_value,t_diff);
		   }
		   break;

	case CtSgwGetWANConnectionByName_NUM:{
			   CtSgwWANConnectionInfo_t out_param1;
			   CtSgwWANConnectionInfo_t target_param1;
			   char name[128]=""; 
                           int result=-1;
                           char *errmsg=NULL;
			   cJSON *target = cJSON_GetObjectItem(testcase,"target");
			   cJSON *CtSgwWANConnectionInfo = cJSON_GetObjectItem(target,"CtSgwWANConnectionInfo_t");
			   cJSON *in = cJSON_GetObjectItem(testcase,"in");
			   strcpy(name,cJSON_GetObjectItem(in, "name")->valuestring);  

 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
			   return_value = CtSgwGetWANConnectionByName(name,&out_param1,&result,&errmsg);       
			   if(FALSE == Check_return_result(return_value,atoi(return_target)))
			   {	
				 fill_capi_result("CtSgwGetWANConnectionByName","failed",return_value,t_diff);
				break;
			   }
 
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
			   strcpy(target_param1.Index,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "Index")->valuestring);  
			   strcpy(target_param1.IfName,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "IfName")->valuestring);   
			   strcpy(target_param1.ServiceList,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "ServiceList")->valuestring);   
			   strcpy(target_param1.ConnectionType,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "ConnectionType")->valuestring);  
			   target_param1.VLANID=atoi(cJSON_GetObjectItem(CtSgwWANConnectionInfo, "VLANID")->valuestring);   
			   target_param1.VLAN8021P=atoi(cJSON_GetObjectItem(CtSgwWANConnectionInfo, "VLAN8021P")->valuestring);  
			   strcpy(target_param1.Protocol,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "Protocol")->valuestring);  
			   strcpy(target_param1.ConnectionStatus,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "ConnectionStatus")->valuestring);   
			   strcpy(target_param1.IPAddress,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "IPAddress")->valuestring);   
			   strcpy(target_param1.SubnetMask,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "SubnetMask")->valuestring);  
			   strcpy(target_param1.Gateway,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "Gateway")->valuestring);   
			   strcpy(target_param1.DNS1,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "DNS1")->valuestring);    
			   strcpy(target_param1.DNS2,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "DNS2")->valuestring);  
			   strcpy(target_param1.IPV6_ConnectionStatus,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "IPV6_ConnectionStatus")->valuestring);   
			   strcpy(target_param1.IPV6_IPAddress,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "IPV6_IPAddress")->valuestring);   
			   strcpy(target_param1.IPV6_PrefixLength,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "IPV6_PrefixLength")->valuestring);  
			   strcpy(target_param1.IPV6_Gateway,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "IPV6_Gateway")->valuestring);   
			   strcpy(target_param1.IPV6_DNS1,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "IPV6_DNS1")->valuestring);  
			   strcpy(target_param1.IPV6_DNS2,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "IPV6_DNS2")->valuestring);  
			   strcpy(target_param1.IPV6_Prefix,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "IPV6_Prefix")->valuestring);   
			   target_param1.RxBytes=atoi(cJSON_GetObjectItem(CtSgwWANConnectionInfo, "RxBytes")->valuestring);   
			   target_param1.TxBytes=atoi(cJSON_GetObjectItem(CtSgwWANConnectionInfo, "TxBytes")->valuestring);  
			   target_param1.RxPkts=atoi(cJSON_GetObjectItem(CtSgwWANConnectionInfo, "RxPkts")->valuestring);   
			   target_param1.TxPkts=atoi(cJSON_GetObjectItem(CtSgwWANConnectionInfo, "TxPkts")->valuestring);  
			   strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgwWANConnectionInfo, "path"),"str")->valuestring);

			   if (FALSE == CheckCtSgwWANConnectionInfo_t(&out_param1,&target_param1))
				 fill_capi_result("CtSgwGetWANConnectionByName","failed",return_value,t_diff);
			   else
				 fill_capi_result("CtSgwGetWANConnectionByName","pass",return_value,t_diff);
                           g_free(errmsg);
		   }
		   break;
	case CtSgwGetInternetWANConnection_NUM:{
			    
                          int result=-1;
                          char *errmsg=NULL;
			   CtSgwWANConnectionInfo_t out_param1;
			   CtSgwWANConnectionInfo_t target_param1;
			   cJSON *target = cJSON_GetObjectItem(testcase,"target");
			   cJSON *CtSgwWANConnectionInfo = cJSON_GetObjectItem(target,"CtSgwWANConnectionInfo_t");

 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
			   return_value = CtSgwGetInternetWANConnection(&out_param1,&result,&errmsg);       
			   if(FALSE == Check_return_result(return_value,atoi(return_target)))
			   {	
				 fill_capi_result("CtSgwGetInternetWANConnection","failed",return_value,t_diff);
				break;
			   }
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;

			   strcpy(target_param1.Index,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "Index")->valuestring);  
			   strcpy(target_param1.IfName,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "IfName")->valuestring);   
			   strcpy(target_param1.ServiceList,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "ServiceList")->valuestring);   
			   strcpy(target_param1.ConnectionType,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "ConnectionType")->valuestring);  
			   target_param1.VLANID=atoi(cJSON_GetObjectItem(CtSgwWANConnectionInfo, "VLANID")->valuestring);   
			   target_param1.VLAN8021P=atoi(cJSON_GetObjectItem(CtSgwWANConnectionInfo, "VLAN8021P")->valuestring);  
			   strcpy(target_param1.Protocol,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "Protocol")->valuestring);  
			   strcpy(target_param1.ConnectionStatus,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "ConnectionStatus")->valuestring);   
			   strcpy(target_param1.IPAddress,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "IPAddress")->valuestring);   
			   strcpy(target_param1.SubnetMask,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "SubnetMask")->valuestring);  
			   strcpy(target_param1.Gateway,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "Gateway")->valuestring);   
			   strcpy(target_param1.DNS1,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "DNS1")->valuestring);    
			   strcpy(target_param1.DNS2,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "DNS2")->valuestring);  
			   strcpy(target_param1.IPV6_ConnectionStatus,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "IPV6_ConnectionStatus")->valuestring);   
			   strcpy(target_param1.IPV6_IPAddress,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "IPV6_IPAddress")->valuestring);   
			   strcpy(target_param1.IPV6_PrefixLength,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "IPV6_PrefixLength")->valuestring);  
			   strcpy(target_param1.IPV6_Gateway,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "IPV6_Gateway")->valuestring);   
			   strcpy(target_param1.IPV6_DNS1,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "IPV6_DNS1")->valuestring);  
			   strcpy(target_param1.IPV6_DNS2,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "IPV6_DNS2")->valuestring);  
			   strcpy(target_param1.IPV6_Prefix,cJSON_GetObjectItem(CtSgwWANConnectionInfo, "IPV6_Prefix")->valuestring);   
			   target_param1.RxBytes=atoi(cJSON_GetObjectItem(CtSgwWANConnectionInfo, "RxBytes")->valuestring);   
			   target_param1.TxBytes=atoi(cJSON_GetObjectItem(CtSgwWANConnectionInfo, "TxBytes")->valuestring);  
			   target_param1.RxPkts=atoi(cJSON_GetObjectItem(CtSgwWANConnectionInfo, "RxPkts")->valuestring);   
			   target_param1.TxPkts=atoi(cJSON_GetObjectItem(CtSgwWANConnectionInfo, "TxPkts")->valuestring);  
			   strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgwWANConnectionInfo, "path"),"str")->valuestring);

			   if (FALSE == CheckCtSgwWANConnectionInfo_t(&out_param1,&target_param1))
				 fill_capi_result("CtSgwGetInternetWANConnection","failed",return_value,t_diff);
			   else
				 fill_capi_result("CtSgwGetInternetWANConnection","pass",return_value,t_diff);
                         g_free(errmsg);
		   }
		   break;

	case CtSgwGetWiFiInfo_NUM:{
			    
			   CtSgwWiFiInfo_t out_param1;   
			   CtSgwWiFiInfo_t target_param1;
			   cJSON *target = cJSON_GetObjectItem(testcase,"target");
			   cJSON *CtSgwWiFiInfo = cJSON_GetObjectItem(target,"CtSgwWiFiInfo_t");

 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
			   return_value = CtSgwGetWiFiInfo(&out_param1);       
			   if(FALSE == Check_return_result(return_value,atoi(return_target)))
			   {	
				 fill_capi_result("CtSgwGetWiFiInfo","failed",return_value,t_diff);
				break;
			   }
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
			   strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgwWiFiInfo, "path"),"str")->valuestring);
			  // strcpy(target_param1.SSID,cJSON_GetObjectItem(CtSgwWiFiInfo, "SSID")->valuestring);  
			   target_param1.Enable=atoi(cJSON_GetObjectItem(CtSgwWiFiInfo, "Enable")->valuestring);   
			   target_param1.SameSSIDStatus=atoi(cJSON_GetObjectItem(CtSgwWiFiInfo, "SameSSIDStatus")->valuestring);
			   strcpy(target_param1.WiFiMode,cJSON_GetObjectItem(CtSgwWiFiInfo, "WiFiMode")->valuestring);    
			   //target_param1.Channel=atoi(cJSON_GetObjectItem(CtSgwWiFiInfo, "Channel")->valuestring);   
			   //target_param1.PowerLevel=atoi(cJSON_GetObjectItem(CtSgwWiFiInfo, "PowerLevel")->valuestring);  
			   //target_param1.PowerLevel_5G=atoi(cJSON_GetObjectItem(CtSgwWiFiInfo, "PowerLevel_5G")->valuestring);   
			  //strcpy(target_param1.PWD,cJSON_GetObjectItem(CtSgwWiFiInfo, "PWD")->valuestring); 

			   //target_param1.Encrypt=atoi(cJSON_GetObjectItem(CtSgwWiFiInfo, "Encrypt")->valuestring);  
			   target_param1.RxBytes=atoi(cJSON_GetObjectItem(CtSgwWiFiInfo, "RxBytes")->valuestring);   
			   target_param1.RxPkts=atoi(cJSON_GetObjectItem(CtSgwWiFiInfo, "RxPkts")->valuestring);   
			   target_param1.RxErrorPkts=atoi(cJSON_GetObjectItem(CtSgwWiFiInfo, "RxErrorPkts")->valuestring);  
			   target_param1.RxDropPkts=atoi(cJSON_GetObjectItem(CtSgwWiFiInfo, "RxDropPkts")->valuestring);   
			   target_param1.TxBytes=atoi(cJSON_GetObjectItem(CtSgwWiFiInfo, "TxBytes")->valuestring);   

			   target_param1.TxPkts=atoi(cJSON_GetObjectItem(CtSgwWiFiInfo, "TxPkts")->valuestring);  
			   target_param1.TxErrorPkts=atoi(cJSON_GetObjectItem(CtSgwWiFiInfo, "TxErrorPkts")->valuestring);   
			   target_param1.TxDropPkts=atoi(cJSON_GetObjectItem(CtSgwWiFiInfo, "TxDropPkts")->valuestring);   

			   if (FALSE == CheckCtSgwWiFiInfo_t(&out_param1,&target_param1))
				 fill_capi_result("CtSgwGetWiFiInfo","failed",return_value,t_diff);
			   else
				 fill_capi_result("CtSgwGetWiFiInfo","pass",return_value,t_diff);
		   }
		   break;
	case CtSgwWiFiDiscClient_NUM:{
			   gchar devMac[128]="";
			   gchar ssidIdx[128]="";
			   guint32 out_result = -1;
			   //guint32 target_result;
			   gchar *out_errmsg= NULL;
			   //gchar *target_errmsg= NULL;

			   //cJSON *target = cJSON_GetObjectItem(testcase,"target");
			   cJSON *in = cJSON_GetObjectItem(testcase,"in");
 			   
			   strcpy(devMac,cJSON_GetObjectItem(in, "devMac")->valuestring); 
			   strcpy(ssidIdx,cJSON_GetObjectItem(in, "ssidIdx")->valuestring);
		           
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
			   return_value = CtSgwWiFiDiscClient(devMac,ssidIdx,&out_result,&out_errmsg);
 			 gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;

			   if(FALSE == Check_return_result(return_value,atoi(return_target)))
			   {
				fill_capi_result("CtSgwWiFiDiscClient","failed",return_value,t_diff);
    			        Check_char(out_errmsg,NULL);
			   }				 
			   else
			   {
				 fill_capi_result("CtSgwWiFiDiscClient","pass",return_value,t_diff);
			  	 Check_int(out_result,0);
			   }
		   g_free(out_errmsg);
		   }
		   break;

	case CtSgwWiFiSetSameSSID_NUM:{
			   gchar ssidIdx24[128]="";
			   gchar ssidIdx58[128]="";
			   guint32 out_result=-1;
			   //guint32 target_result;
			   gchar *out_errmsg= NULL;
			   //gchar *target_errmsg= NULL;

			   cJSON *target = cJSON_GetObjectItem(testcase,"target");
			   cJSON *in = cJSON_GetObjectItem(testcase,"in");
 			   
			   strcpy(ssidIdx24,cJSON_GetObjectItem(in, "ssidIdx24")->valuestring); 
			   strcpy(ssidIdx58,cJSON_GetObjectItem(in, "ssidIdx58")->valuestring);
		           
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
			   return_value = CtSgwWiFiSetSameSSID(ssidIdx24,ssidIdx58,&out_result,&out_errmsg);
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
			   if(FALSE == Check_return_result(return_value,atoi(return_target)))
			   {
				fill_capi_result("CtSgwWiFiSetSameSSID","failed",return_value,t_diff);
				Check_char(out_errmsg,NULL);
			   }				 
			   else
			   {
				 fill_capi_result("CtSgwWiFiSetSameSSID","pass",return_value,t_diff);
			         Check_int(out_result,0);
			   }
		   g_free(out_errmsg);	   
		   }
		   break;

	case CtSgwWiFiCancelSameSSID_NUM:{
			   guint32 out_result = -1;
			   //guint32 target_result;
			   gchar *out_errmsg= NULL;
			   //gchar *target_errmsg= NULL;

			   //cJSON *target = cJSON_GetObjectItem(testcase,"target");
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
 		           

			   return_value = CtSgwWiFiCancelSameSSID(&out_result, &out_errmsg);


			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
		
			   if(FALSE == Check_return_result(return_value,atoi(return_target)))
			   {
				fill_capi_result("CtSgwWiFiCancelSameSSID","failed",return_value,t_diff);
				Check_char(out_errmsg,NULL);
			   }				 
			   else
			   {
				 fill_capi_result("CtSgwWiFiCancelSameSSID","pass",return_value,t_diff);
				 Check_int(out_result,0);
			   }
		   g_free(out_errmsg);   
		   }
		   break;

	case CtSgwWiFiSetEnable_NUM:{

			   gboolean enable;
			   cJSON *in = cJSON_GetObjectItem(testcase,"in");
		           enable=atoi(cJSON_GetObjectItem(in, "enable")->valuestring);  
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

			   return_value = CtSgwWiFiSetEnable(enable);

			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
			   if(FALSE == Check_return_result(return_value,atoi(return_target)))
				fill_capi_result("CtSgwWiFiSetEnable","failed",return_value,t_diff);			 
			   else
				 fill_capi_result("CtSgwWiFiSetEnable","pass",return_value,t_diff);
		   }
		   break;

	case CtSgwGetPONInfo_NUM:{
			    
			   CtSgwPONInfo_t out_param1;
			   CtSgwPONInfo_t target_param1;
			   cJSON *target = cJSON_GetObjectItem(testcase,"target");
			   cJSON *CtSgwPONInfo = cJSON_GetObjectItem(target,"CtSgwPONInfo_t");

 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
			   return_value = CtSgwGetPONInfo(&out_param1);       
			   if(FALSE == Check_return_result(return_value,atoi(return_target)))
			   {	
				 fill_capi_result("CtSgwGetPONInfo","failed",return_value,t_diff);
				break;
			   } 
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;

			   strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgwPONInfo, "path"),"str")->valuestring);
			   strcpy(target_param1.LOID,cJSON_GetObjectItem(CtSgwPONInfo, "LOID")->valuestring);  
			   strcpy(target_param1.Password,cJSON_GetObjectItem(CtSgwPONInfo, "Password")->valuestring);   
			   target_param1.Temperature=atof(cJSON_GetObjectItem(CtSgwPONInfo, "Temperature")->valuestring);   
			   target_param1.Vottage=atof(cJSON_GetObjectItem(CtSgwPONInfo, "Vottage")->valuestring);  
			   target_param1.Current=atof(cJSON_GetObjectItem(CtSgwPONInfo, "Current")->valuestring);   
			   target_param1.TXPower=atof(cJSON_GetObjectItem(CtSgwPONInfo, "TXPower")->valuestring);  
			   target_param1.RXPower=atof(cJSON_GetObjectItem(CtSgwPONInfo, "RXPower")->valuestring);  
			   target_param1.SupportPONStatusQuery=atoi(cJSON_GetObjectItem(CtSgwPONInfo, "SupportPONStatusQuery")->valuestring);   
			   strcpy(target_param1.PONStatus,cJSON_GetObjectItem(CtSgwPONInfo, "PONStatus")->valuestring);   

			   if (FALSE == CheckCtSgwPONInfo_t(&out_param1,&target_param1))
				 fill_capi_result("CtSgwGetPONInfo","failed",return_value,t_diff);
			   else
				 fill_capi_result("CtSgwGetPONInfo","pass",return_value,t_diff);
		   } 
		   break;
	case CtSgwGetVoIPInfo_NUM:{
			    
			   CtSgwVoIPInfo_t out_param1;
			   CtSgwVoIPInfo_t target_param1;
			   cJSON *target = cJSON_GetObjectItem(testcase,"target");
			   cJSON *CtSgwVoIPInfo = cJSON_GetObjectItem(target,"CtSgwVoIPInfo_t");

 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

			   return_value = CtSgwGetVoIPInfo(&out_param1);       
			   if(FALSE == Check_return_result(return_value,atoi(return_target)))
			   {	
				 fill_capi_result("CtSgwGetVoIPInfo","failed",return_value,t_diff);
				break;
			   }
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;

			   strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgwVoIPInfo, "path"),"str")->valuestring); 
			   strcpy(target_param1.VoIPName1,cJSON_GetObjectItem(CtSgwVoIPInfo, "VoIPName1")->valuestring);  
			   strcpy(target_param1.VoIPName2,cJSON_GetObjectItem(CtSgwVoIPInfo, "VoIPName2")->valuestring);   
			   strcpy(target_param1.Line1Status,cJSON_GetObjectItem(CtSgwVoIPInfo, "Line1Status")->valuestring);  
			   strcpy(target_param1.Line2Status,cJSON_GetObjectItem(CtSgwVoIPInfo, "Line2Status")->valuestring);  

			   if (FALSE == CheckCtSgwVoIPInfo_t(&out_param1,&target_param1))
				 fill_capi_result("CtSgwGetVoIPInfo","failed",return_value,t_diff);
			   else
				 fill_capi_result("CtSgwGetVoIPInfo","pass",return_value,t_diff);
		   }
		   break;   
	case CtSgwGetLANHostMgr_NUM:{
			         
				CtSgwLANHostMgr_t out_param1;
				CtSgwLANHostMgr_t target_param1;
				cJSON *target = cJSON_GetObjectItem(testcase,"target");
				cJSON *CtSgwLANHostMgr = cJSON_GetObjectItem(target,"CtSgwLANHostMgr_t");

 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
				return_value = CtSgwGetLANHostMgr(&out_param1);       
			        if(FALSE == Check_return_result(return_value,atoi(return_target)))
			       {	
					 fill_capi_result("CtSgwGetLANHostMgr","failed",return_value,t_diff);
					break;
			       }
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;

			        strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgwLANHostMgr, "path"),"str")->valuestring); 
				target_param1.EnableStats=atoi(cJSON_GetObjectItem(CtSgwLANHostMgr, "EnableStats")->valuestring);  
				target_param1.LANHostMaxNumber=atoi(cJSON_GetObjectItem(CtSgwLANHostMgr, "LANHostMaxNumber")->valuestring);  
				target_param1.LANHostNumber=atoi(cJSON_GetObjectItem(CtSgwLANHostMgr, "LANHostNumber")->valuestring);  
				target_param1.ControlListMaxNumber=atoi(cJSON_GetObjectItem(CtSgwLANHostMgr, "ControlListMaxNumber")->valuestring);  
				target_param1.ControlListNumber=atoi(cJSON_GetObjectItem(CtSgwLANHostMgr, "ControlListNumber")->valuestring);  

			  	 if (FALSE == CheckCtSgwLANHostMgr_t(&out_param1,&target_param1))
					 fill_capi_result("CtSgwGetLANHostMgr","failed",return_value,t_diff);
			         else
					 fill_capi_result("CtSgwGetLANHostMgr","pass",return_value,t_diff);
			}
			break;

	case CtSgwSetLANHostMgr_NUM:{
			         
				CtSgwLANHostMgr_t target_param1;
				cJSON *in = cJSON_GetObjectItem(testcase,"in");
				cJSON *CtSgwLANHostMgr = cJSON_GetObjectItem(in,"CtSgwLANHostMgr_t");
				target_param1.EnableStats=atoi(cJSON_GetObjectItem(CtSgwLANHostMgr, "EnableStats")->valuestring);
				target_param1.LANHostMaxNumber=atoi(cJSON_GetObjectItem(CtSgwLANHostMgr, "LANHostMaxNumber")->valuestring);
				target_param1.ControlListMaxNumber=atoi(cJSON_GetObjectItem(CtSgwLANHostMgr, "ControlListMaxNumber")->valuestring);
			        strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgwLANHostMgr, "path"),"str")->valuestring); 
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
				return_value = CtSgwSetLANHostMgr(&target_param1);      
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;

				if(FALSE == Check_return_result(return_value,atoi(return_target)))
					 fill_capi_result("CtSgwSetLANHostMgr","failed",return_value,t_diff);
			        else
					 fill_capi_result("CtSgwSetLANHostMgr","pass",return_value,t_diff);                      
			}
			break;

	case CtSgwGetLANHostObjs_NUM:{
			         
				CtSgwLANHost_t* out_param1 = NULL;
				int out_count;
				int target_count;
				CtSgwLANHost_t target_param1;    
				cJSON *target = cJSON_GetObjectItem(testcase,"target");

 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
				return_value = CtSgwGetLANHostObjs(&out_param1,&out_count);       
			        if(FALSE == Check_return_result(return_value,atoi(return_target)))
			        {	
					 fill_capi_result("CtSgwGetLANHostObjs","failed",return_value,t_diff);
					g_free(out_param1);
					break;
			        }

			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
				cJSON * CtSgwLANHost = cJSON_GetObjectItem(target, "CtSgwLANHost_t");

				target_count=atoi(cJSON_GetObjectItem(target, "count")->valuestring);
				Check_int(out_count,target_count);
			        if(out_count > target_count)
			        {
				    out_count = target_count;
			        }
				else if(out_count == 0)
				{
					fill_capi_result("CtSgwGetLANHostObjs","pass",return_value,t_diff);
					g_free(out_param1);
					break;
				}
				int index=0;
				for (index = 0; index < out_count; index++)
				{
				   	strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwLANHost, index), "path"),"str")->valuestring);
					strcpy(target_param1.MAC,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwLANHost, index), "MAC")->valuestring);  
					strcpy(target_param1.DevName,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwLANHost, index), "DevName")->valuestring);
					target_param1.InternetAccess=atoi(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwLANHost, index), "InternetAccess")->valuestring);
					target_param1.StorageAccess=atoi(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwLANHost, index), "StorageAccess")->valuestring);  
					target_param1.MaxUSBandwidth=atoi(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwLANHost, index), "MaxUSBandwidth")->valuestring);  
					target_param1.MaxDSBandwidth=atoi(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwLANHost, index), "MaxDSBandwidth")->valuestring);  
					target_param1.ControlStatus=atoi(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwLANHost, index), "ControlStatus")->valuestring);  
					target_param1.Active=atoi(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwLANHost, index), "Active")->valuestring);  
					strcpy(target_param1.DevType,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwLANHost, index), "DevType")->valuestring);  
					strcpy(target_param1.Model,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwLANHost, index), "Model")->valuestring);  
					strcpy(target_param1.LatestActiveTime,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwLANHost, index), "LatestActiveTime")->valuestring);  
					strcpy(target_param1.LatestInactiveTime,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwLANHost, index), "LatestInactiveTime")->valuestring); 
					strcpy(target_param1.IP,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwLANHost, index), "IP")->valuestring);  
					target_param1.ConnectionType=atoi(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwLANHost, index), "ConnectionType")->valuestring);  
					target_param1.Port=atoi(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwLANHost, index), "Port")->valuestring);  
					strcpy(target_param1.Brand,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwLANHost, index), "Brand")->valuestring);  
					strcpy(target_param1.OS,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwLANHost, index), "OS")->valuestring);  
					target_param1.OnlineTime=atoi(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwLANHost, index), "OnlineTime")->valuestring);  
					target_param1.RxBytes=atoi(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwLANHost, index), "RxBytes")->valuestring);  
					target_param1.TxBytes=atoi(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwLANHost, index), "TxBytes")->valuestring);  
					if(FALSE == CheckCtSgwLANHost_t(&(out_param1[index]),&target_param1))
						 fill_capi_result("CtSgwGetLANHostObjs","failed",return_value,t_diff); 
			   		else
						 fill_capi_result("CtSgwGetLANHostObjs","pass",return_value,t_diff);
				}
			g_free(out_param1);
			}
			break;

	case CtSgwGetLANHost_NUM:{
			         
				CtSgwLANHost_t out_param1;
				CtSgwObjPath_t path;
				CtSgwLANHost_t target_param1;    
				cJSON *target = cJSON_GetObjectItem(testcase,"target");
				cJSON *CtSgwLANHost = cJSON_GetObjectItem(target,"CtSgwLANHost_t");
				cJSON *in = cJSON_GetObjectItem(testcase,"in");
				strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring); 
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				return_value = CtSgwGetLANHost(path,&out_param1);       
			        if(FALSE == Check_return_result(return_value,atoi(return_target)))
			        {	
					 fill_capi_result("CtSgwGetLANHost","failed",return_value,t_diff);
					break;
			        }

			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
		

			  	strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgwLANHost, "path"),"str")->valuestring); 
				strcpy(target_param1.MAC,cJSON_GetObjectItem(CtSgwLANHost, "MAC")->valuestring);  
				strcpy(target_param1.DevName,cJSON_GetObjectItem(CtSgwLANHost, "DevName")->valuestring);  
				target_param1.InternetAccess=atoi(cJSON_GetObjectItem(CtSgwLANHost, "InternetAccess")->valuestring);  
				target_param1.StorageAccess=atoi(cJSON_GetObjectItem(CtSgwLANHost, "StorageAccess")->valuestring);  
				target_param1.MaxUSBandwidth=atoi(cJSON_GetObjectItem(CtSgwLANHost, "MaxUSBandwidth")->valuestring);  
				target_param1.MaxDSBandwidth=atoi(cJSON_GetObjectItem(CtSgwLANHost, "MaxDSBandwidth")->valuestring);  
				target_param1.ControlStatus=atoi(cJSON_GetObjectItem(CtSgwLANHost, "ControlStatus")->valuestring);  
				target_param1.Active=atoi(cJSON_GetObjectItem(CtSgwLANHost, "Active")->valuestring);  
				strcpy(target_param1.DevType,cJSON_GetObjectItem(CtSgwLANHost, "DevType")->valuestring);  
				strcpy(target_param1.Model,cJSON_GetObjectItem(CtSgwLANHost, "Model")->valuestring); 
				strcpy(target_param1.LatestActiveTime,cJSON_GetObjectItem(CtSgwLANHost, "LatestActiveTime")->valuestring); 
				strcpy(target_param1.LatestInactiveTime,cJSON_GetObjectItem(CtSgwLANHost, "LatestInactiveTime")->valuestring); 
				strcpy(target_param1.IP,cJSON_GetObjectItem(CtSgwLANHost, "IP")->valuestring);  
				target_param1.ConnectionType=atoi(cJSON_GetObjectItem(CtSgwLANHost, "ConnectionType")->valuestring);  
				target_param1.Port=atoi(cJSON_GetObjectItem(CtSgwLANHost, "Port")->valuestring);  

				strcpy(target_param1.Brand,cJSON_GetObjectItem(CtSgwLANHost, "Brand")->valuestring);  
				strcpy(target_param1.OS,cJSON_GetObjectItem(CtSgwLANHost, "OS")->valuestring);  
				target_param1.OnlineTime=atoi(cJSON_GetObjectItem(CtSgwLANHost, "OnlineTime")->valuestring);  
				target_param1.RxBytes=atoi(cJSON_GetObjectItem(CtSgwLANHost, "RxBytes")->valuestring);  
				target_param1.TxBytes=atoi(cJSON_GetObjectItem(CtSgwLANHost, "TxBytes")->valuestring);  

				if(FALSE == CheckCtSgwLANHost_t(&out_param1,&target_param1))
					 fill_capi_result("CtSgwGetLANHost","failed",return_value,t_diff);
			        else
					 fill_capi_result("CtSgwGetLANHost","pass",return_value,t_diff);
			}
			break;
	case CtSgwSetLANHost_NUM:{	
			        CtSgwObjPath_t path;			
				CtSgwLANHost_t target_param1;    
				cJSON *in = cJSON_GetObjectItem(testcase,"in");
				cJSON *CtSgwLANHost = cJSON_GetObjectItem(in,"CtSgwLANHost_t");
			  	
				strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring); 
				//strcpy(target_param1.MAC,cJSON_GetObjectItem(CtSgwLANHost, "MAC")->valuestring);  
				strcpy(target_param1.DevName,cJSON_GetObjectItem(CtSgwLANHost, "DevName")->valuestring);  
				target_param1.InternetAccess=atoi(cJSON_GetObjectItem(CtSgwLANHost, "InternetAccess")->valuestring);  
				target_param1.StorageAccess=atoi(cJSON_GetObjectItem(CtSgwLANHost, "StorageAccess")->valuestring);  
				target_param1.MaxUSBandwidth=atoi(cJSON_GetObjectItem(CtSgwLANHost, "MaxUSBandwidth")->valuestring);  
				target_param1.MaxDSBandwidth=atoi(cJSON_GetObjectItem(CtSgwLANHost, "MaxDSBandwidth")->valuestring);  
				target_param1.ControlStatus=atoi(cJSON_GetObjectItem(CtSgwLANHost, "ControlStatus")->valuestring);  

				//target_param1.DSBandwidth=atoi(cJSON_GetObjectItem(CtSgwLANHost, "DSBandwidth")->valuestring);  
				//strcpy(target_param1.DevType,cJSON_GetObjectItem(CtSgwLANHost, "DevType")->valuestring);  
				//strcpy(target_param1.IP,cJSON_GetObjectItem(CtSgwLANHost, "IP")->valuestring);  
				//target_param1.ConnectionType=atoi(cJSON_GetObjectItem(CtSgwLANHost, "ConnectionType")->valuestring);  
				//target_param1.Port=atoi(cJSON_GetObjectItem(CtSgwLANHost, "Port")->valuestring);  

				//strcpy(target_param1.Brand,cJSON_GetObjectItem(CtSgwLANHost, "Brand")->valuestring);  
				//strcpy(target_param1.OS,cJSON_GetObjectItem(CtSgwLANHost, "OS")->valuestring);  
				//target_param1.OnlineTime=atoi(cJSON_GetObjectItem(CtSgwLANHost, "OnlineTime")->valuestring);  
				//target_param1.RxBytes=atoi(cJSON_GetObjectItem(CtSgwLANHost, "RxBytes")->valuestring);  
				//target_param1.TxBytes=atoi(cJSON_GetObjectItem(CtSgwLANHost, "TxBytes")->valuestring);  
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				return_value = CtSgwSetLANHost(path,&target_param1);
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;

				if(FALSE == Check_return_result(return_value,atoi(return_target))) 
					 fill_capi_result("CtSgwSetLANHost","failed",return_value,t_diff);
			        else
					 fill_capi_result("CtSgwSetLANHost","pass",return_value,t_diff);
			}
			break;	

	case CtSgwSetHttpDownloadTestURL_NUM:{
			         
				char url[MAX_URL_LEN+1] = "";
				cJSON *in = cJSON_GetObjectItem(testcase,"in");

				strcpy(url,cJSON_GetObjectItem(in, "url")->valuestring); 

 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
				return_value = CtSgwSetHttpDownloadTestURL(url);  

     			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
				if(FALSE == Check_return_result(return_value,atoi(return_target))) 
					 fill_capi_result("CtSgwSetHttpDownloadTestURL","failed",return_value,t_diff);
			        else
					 fill_capi_result("CtSgwSetHttpDownloadTestURL","pass",return_value,t_diff);
			}
			break;

	case CtSgwGetHttpDownloadTestURL_NUM:{
			         
				char *out_url=NULL;
				char *target_url=NULL;
				cJSON *target = cJSON_GetObjectItem(testcase,"target");
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				return_value = CtSgwGetHttpDownloadTestURL(&out_url);  
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
     
				if(FALSE == Check_return_result(return_value,atoi(return_target))) 
				{
					 fill_capi_result("CtSgwGetHttpDownloadTestURL","failed",return_value,t_diff);
					 break;
				}
				else
					 fill_capi_result("CtSgwGetHttpDownloadTestURL","pass",return_value,t_diff);

				strcpy(target_url,cJSON_GetObjectItem(target, "url")->valuestring); 
				Check_char(out_url,target_url);
			}
			break;

	case CtSgwStartHttpDownloadTest_NUM:{ 
			          
				guint32 target_time;  
				guint32 out_result = -1;
				//guint32 target_result = -1;
				gchar *out_errdesc = NULL;
				//gchar *target_errdesc = NULL;

				cJSON *in = cJSON_GetObjectItem(testcase,"in");
				//cJSON *target = cJSON_GetObjectItem(testcase,"target"); 
				target_time=atoi(cJSON_GetObjectItem(in, "time")->valuestring); 
            
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				return_value = CtSgwStartHttpDownloadTest(target_time,&out_result,&out_errdesc);  

			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
     
				if(FALSE == Check_return_result(return_value,atoi(return_target))) 
				{
					 fill_capi_result("CtSgwStartHttpDownloadTest","failed",return_value,t_diff);
					 //strcpy(target_errdesc,cJSON_GetObjectItem(target, "errdesc")->valuestring); 
					 Check_char(out_errdesc,NULL);
					 g_free(out_errdesc);
				}
			        else
				{
					 fill_capi_result("CtSgwStartHttpDownloadTest","pass",return_value,t_diff);
					 //target_result = atoi(cJSON_GetObjectItem(target, "result")->valuestring); 
					 Check_int(out_result,0);
					g_free(out_errdesc);
				}
			}
			break;

	case CtSgwGetHttpDownloadTestResult_NUM:{
			         
				CtSgwHttpDownloadTestResult_t out_param1;
				CtSgwHttpDownloadTestResult_t target_param1;
				cJSON *target = cJSON_GetObjectItem(testcase,"target");
				cJSON *CtSgwHttpDownloadTestResult = cJSON_GetObjectItem(target,"CtSgwHttpDownloadTestResult_t");

 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				return_value = CtSgwGetHttpDownloadTestResult(&out_param1); 
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;

				strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgwHttpDownloadTestResult, "path"),"str")->valuestring);       
			        if(FALSE == Check_return_result(return_value,atoi(return_target)))
			        {	
					 fill_capi_result("CtSgwGetHttpDownloadTestResult","failed",return_value,t_diff);
					break;
			        }
				target_param1.Status=atoi(cJSON_GetObjectItem(CtSgwHttpDownloadTestResult, "Status")->valuestring);  
				strcpy(target_param1.Result,cJSON_GetObjectItem(CtSgwHttpDownloadTestResult, "Result")->valuestring);  
				strcpy(target_param1.URL,cJSON_GetObjectItem(CtSgwHttpDownloadTestResult, "URL")->valuestring);  

				if(FALSE == CheckCtSgwHttpDownloadTestResult_t(&out_param1,&target_param1))
					 fill_capi_result("CtSgwGetHttpDownloadTestResult","failed",return_value,t_diff);
			        else
					 fill_capi_result("CtSgwGetHttpDownloadTestResult","pass",return_value,t_diff);
			}
			break;
	case CtSgwSetWPSConfig_NUM:{
				CtSgwWPS_t target_param1;
				CtSgwObjPath_t path;

				cJSON *in = cJSON_GetObjectItem(testcase,"in");
				cJSON *CtSgwWPS = cJSON_GetObjectItem(in,"CtSgwWPS_t");

				strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring);
				target_param1.Enable=atoi(cJSON_GetObjectItem(CtSgwWPS, "Enable")->valuestring); 
				//target_param1.TimeOut=atoi(cJSON_GetObjectItem(CtSgwWPS, "TimeOut")->valuestring);  
			 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				return_value = CtSgwSetWPSConfig(path,&target_param1);

			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;

       
				if(FALSE == Check_return_result(return_value,atoi(return_target))) 
					 fill_capi_result("CtSgwSetWPSConfig","failed",return_value,t_diff); 
			        else
					 fill_capi_result("CtSgwSetWPSConfig","pass",return_value,t_diff); 
			}
			break;
	case CtSgwGetWPSConfig_NUM:{
			         
				CtSgwWPS_t out_param1;
				CtSgwWPS_t target_param1;
				CtSgwObjPath_t path;
				cJSON *target = cJSON_GetObjectItem(testcase,"target");
				cJSON *CtSgwWPS = cJSON_GetObjectItem(target,"CtSgwWPS_t");
				cJSON *DevInfo = cJSON_GetObjectItem(CtSgwWPS, "DevInfo");
				cJSON *in = cJSON_GetObjectItem(testcase,"in");
			        strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring); 
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				return_value = CtSgwGetWPSConfig(path,&out_param1);       
			        if(FALSE == Check_return_result(return_value,atoi(return_target)))
			        {	
					 fill_capi_result("CtSgwGetWPSConfig","failed",return_value,t_diff);
					break;
			        }
				if(0 == out_param1.AttdevNum)
                                 {
                                        fill_capi_result("CtSgwGetWPSConfig","failed",return_value,t_diff);
					break;//wjq
                                 }


 			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;

				strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgwWPS, "path"),"str")->valuestring);
				target_param1.Enable=atoi(cJSON_GetObjectItem(CtSgwWPS, "Enable")->valuestring); 
				//target_param1.TimeOut=atoi(cJSON_GetObjectItem(CtSgwWPS, "TimeOut")->valuestring); 
				target_param1.WPSStatus=atoi(cJSON_GetObjectItem(CtSgwWPS, "WPSStatus")->valuestring);  
				
				target_param1.DevInfo=malloc(sizeof(CtSgwWPSDevInfo_t));
		
				strcpy(target_param1.DevInfo->Info,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgwWPS, "DevInfo"),"Info")->valuestring);     
				

				if(FALSE == CheckCtSgwWPS_t(&out_param1,&target_param1))
					 fill_capi_result("CtSgwGetWPSConfig","failed",return_value,t_diff);   
			        else
					 fill_capi_result("CtSgwGetWPSConfig","pass",return_value,t_diff);
			}
			break;
	case CtSgwSetWPS_NUM:{
			        CtSgwObjPath_t path;
				gint32 status;
				guint32 time;
				guint32 out_result = -1;
				//guint32 target_result;
				gchar *out_errdesc = NULL;
				//gchar *target_errdesc = NULL;

				cJSON *in = cJSON_GetObjectItem(testcase,"in");
				//cJSON *target = cJSON_GetObjectItem(testcase,"target");
				
				strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring); 
				status = atoi(cJSON_GetObjectItem(in, "status")->valuestring);
				time = atoi(cJSON_GetObjectItem(in, "time")->valuestring);
				

 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
				return_value = CtSgwSetWPS(path,status,time,&out_result,&out_errdesc); 

			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;

			        if(FALSE == Check_return_result(return_value,atoi(return_target)))
				{
					 fill_capi_result("CtSgwSetWPS","failed",return_value,t_diff);  
					//strcpy(target_errdesc,cJSON_GetObjectItem(target, "errdesc")->valuestring);
					Check_char(out_errdesc,NULL);
					g_free(out_errdesc);
				} 
			        else
				{
					 fill_capi_result("CtSgwSetWPS","pass",return_value,t_diff);
					//target_result = atoi(cJSON_GetObjectItem(target, "result")->valuestring);
					Check_int(out_result,0);
					g_free(out_errdesc);
				}

			}
			break;
	case CtSgwGetWLANDeviceObjs_NUM:{
			         
				CtSgwWLANDevice_t* out_param1 = NULL;
				guint32 out_count;
				guint32 target_count;
				CtSgwWLANDevice_t target_param1;
				cJSON *target = cJSON_GetObjectItem(testcase,"target");
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				return_value = CtSgwGetWLANDeviceObjs(&out_param1,&out_count);
			
       
			        if(FALSE == Check_return_result(return_value,atoi(return_target)))
			        {	
					 fill_capi_result("CtSgwGetWLANDeviceObjs","failed",return_value,t_diff);
					g_free(out_param1);
					break;
			        }
                        gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;


				cJSON * CtSgwWLANDevice = cJSON_GetObjectItem(target, "CtSgwWLANDevice_t");
				target_count=atoi(cJSON_GetObjectItem(target, "count")->valuestring);
				Check_int(out_count,target_count);
			        if(out_count > target_count)
			        {
				     out_count = target_count;
			        }
				else if(out_count == 0)
				{
					fill_capi_result("CtSgwGetWLANDeviceObjs","pass",return_value,t_diff);
					g_free(out_param1);
					break;
				}
				int index=0;
				for (index = 0; index < out_count; index++)
				{
				   	strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWLANDevice, index), "path"),"str")->valuestring);
					strcpy(target_param1.SSID,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWLANDevice, index), "SSID")->valuestring); 
					target_param1.Enable=atoi(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWLANDevice, index), "Enable")->valuestring);  
					target_param1.Channel=atoi(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWLANDevice, index), "Channel")->valuestring);  
					target_param1.ChannelInUse=atoi(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWLANDevice, index), "ChannelInUse")->valuestring);  
					strcpy(target_param1.BeaconType,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWLANDevice, index), "BeaconType")->valuestring);   
					strcpy(target_param1.Standard,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWLANDevice, index), "Standard")->valuestring); 
					strcpy(target_param1.WEPEncryptionLevel,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWLANDevice, index), "WEPEncryptionLevel")->valuestring);  
					strcpy(target_param1.BasicAuthenticationMode,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWLANDevice, index), "BasicAuthenticationMode")->valuestring);  
					strcpy(target_param1.WPAEncryptionModes,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWLANDevice, index), "WPAEncryptionModes")->valuestring);  
					target_param1.SSIDHide=atoi(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWLANDevice, index), "SSIDHide")->valuestring);   
					target_param1.RFBand=atoi(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWLANDevice, index), "RFBand")->valuestring); 
					target_param1.ChannelWidth=atoi(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWLANDevice, index), "ChannelWidth")->valuestring);  
					target_param1.GuardInterval=atoi(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWLANDevice, index), "GuardInterval")->valuestring);  
					target_param1.RetryTimeout=atoi(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWLANDevice, index), "RetryTimeout")->valuestring);  
					target_param1.Powerlevel=atoi(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWLANDevice, index), "Powerlevel")->valuestring);   
					//target_param1.PowerLevel_5G=atoi(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWLANDevice, index), "PowerLevel_5G")->valuestring); 
					target_param1.PowerValue=atoi(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWLANDevice, index), "PowerValue")->valuestring);  
					//target_param1.APModuleEnable=atoi(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWLANDevice, index), "APModuleEnable")->valuestring);  
					//target_param1.WPSKeyWord=atoi(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWLANDevice, index), "WPSKeyWord")->valuestring);  
					strcpy(target_param1.PWD,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWLANDevice, index), "PWD")->valuestring); 
                                        g_print("CtSgwGetWLANDeviceObjs=====1\n");

					if(FALSE == CheckCtSgwWLANDevice_t(&(out_param1[index]),&target_param1))
					fill_capi_result("CtSgwGetWLANDeviceObjs","failed",return_value,t_diff);  
			       		else
				        fill_capi_result("CtSgwGetWLANDeviceObjs","pass",return_value,t_diff);	      
				}
			g_free(out_param1);
			}
			break;
	case CtSgwGetWLANDevice_NUM:{
			         
				CtSgwWLANDevice_t out_param1;
				CtSgwObjPath_t path;
				CtSgwWLANDevice_t target_param1;
				cJSON *target = cJSON_GetObjectItem(testcase,"target");
				cJSON *CtSgwWLANDevice = cJSON_GetObjectItem(target,"CtSgwWLANDevice_t");
				cJSON *in = cJSON_GetObjectItem(testcase,"in");
				strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring); 

 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				return_value = CtSgwGetWLANDevice(path,&out_param1);    

			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
   
			        if(FALSE == Check_return_result(return_value,atoi(return_target)))
			        {	
					 fill_capi_result("CtSgwGetWLANDevice","failed",return_value,t_diff);
					break;
			        }

				strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgwWLANDevice, "path"),"str")->valuestring);
				strcpy(target_param1.SSID,cJSON_GetObjectItem(CtSgwWLANDevice, "SSID")->valuestring); 
				target_param1.Enable=atoi(cJSON_GetObjectItem(CtSgwWLANDevice, "Enable")->valuestring);   
				target_param1.Channel=atoi(cJSON_GetObjectItem(CtSgwWLANDevice, "Channel")->valuestring);  
				target_param1.ChannelInUse=atoi(cJSON_GetObjectItem(CtSgwWLANDevice, "ChannelInUse")->valuestring);  
				strcpy(target_param1.BeaconType,cJSON_GetObjectItem(CtSgwWLANDevice, "BeaconType")->valuestring);   
				strcpy(target_param1.Standard,cJSON_GetObjectItem(CtSgwWLANDevice, "Standard")->valuestring); 
				strcpy(target_param1.WEPEncryptionLevel,cJSON_GetObjectItem(CtSgwWLANDevice, "WEPEncryptionLevel")->valuestring);  
				strcpy(target_param1.BasicAuthenticationMode,cJSON_GetObjectItem(CtSgwWLANDevice, "BasicAuthenticationMode")->valuestring);  
				strcpy(target_param1.WPAEncryptionModes,cJSON_GetObjectItem(CtSgwWLANDevice, "WPAEncryptionModes")->valuestring);  
				target_param1.SSIDHide=atoi(cJSON_GetObjectItem(CtSgwWLANDevice, "SSIDHide")->valuestring);   

				target_param1.RFBand=atoi(cJSON_GetObjectItem(CtSgwWLANDevice, "RFBand")->valuestring); 
				target_param1.ChannelWidth=atoi(cJSON_GetObjectItem(CtSgwWLANDevice, "ChannelWidth")->valuestring);  
				target_param1.GuardInterval=atoi(cJSON_GetObjectItem(CtSgwWLANDevice, "GuardInterval")->valuestring);  
				target_param1.RetryTimeout=atoi(cJSON_GetObjectItem(CtSgwWLANDevice, "RetryTimeout")->valuestring);  
				target_param1.Powerlevel=atoi(cJSON_GetObjectItem(CtSgwWLANDevice, "Powerlevel")->valuestring);   
				//target_param1.PowerLevel_5G=atoi(cJSON_GetObjectItem(CtSgwWLANDevice, "PowerLevel_5G")->valuestring); 
				target_param1.PowerValue=atoi(cJSON_GetObjectItem(CtSgwWLANDevice, "PowerValue")->valuestring);  
				//target_param1.APModuleEnable=atoi(cJSON_GetObjectItem(CtSgwWLANDevice, "APModuleEnable")->valuestring);  
				//target_param1.WPSKeyWord=atoi(cJSON_GetObjectItem(CtSgwWLANDevice, "WPSKeyWord")->valuestring);  
				strcpy(target_param1.PWD,cJSON_GetObjectItem(CtSgwWLANDevice, "PWD")->valuestring); 

				if(FALSE == CheckCtSgwWLANDevice_t(&out_param1,&target_param1))
					 fill_capi_result("CtSgwGetWLANDevice","failed",return_value,t_diff);   
			        else
					 fill_capi_result("CtSgwGetWLANDevice","pass",return_value,t_diff);
			}
			break;
	case CtSgwGetWLANDeviceBySSID_NUM:{
			         
				CtSgwWLANDevice_t out_param1;
				char ssid[128] = "";
				CtSgwWLANDevice_t target_param1;
				cJSON *target = cJSON_GetObjectItem(testcase,"target");
				cJSON *CtSgwWLANDevice = cJSON_GetObjectItem(target,"CtSgwWLANDevice_t");
				cJSON *in = cJSON_GetObjectItem(testcase,"in");
				strcpy(ssid,cJSON_GetObjectItem(in, "ssid")->valuestring); 

 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				return_value = CtSgwGetWLANDeviceBySSID(ssid,&out_param1);  
			        if(FALSE == Check_return_result(return_value,atoi(return_target)))
			        {	
					 fill_capi_result("CtSgwGetWLANDeviceBySSID","failed",return_value,t_diff);
					break;
			        }
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;


				strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgwWLANDevice, "path"),"str")->valuestring);
				strcpy(target_param1.SSID,cJSON_GetObjectItem(CtSgwWLANDevice, "SSID")->valuestring); 
				target_param1.Enable=atoi(cJSON_GetObjectItem(CtSgwWLANDevice, "Enable")->valuestring);  
				target_param1.Channel=atoi(cJSON_GetObjectItem(CtSgwWLANDevice, "Channel")->valuestring);  
				target_param1.ChannelInUse=atoi(cJSON_GetObjectItem(CtSgwWLANDevice, "ChannelInUse")->valuestring);  
				strcpy(target_param1.BeaconType,cJSON_GetObjectItem(CtSgwWLANDevice, "BeaconType")->valuestring);   
				strcpy(target_param1.Standard,cJSON_GetObjectItem(CtSgwWLANDevice, "Standard")->valuestring); 
				strcpy(target_param1.WEPEncryptionLevel,cJSON_GetObjectItem(CtSgwWLANDevice, "WEPEncryptionLevel")->valuestring);  
				strcpy(target_param1.BasicAuthenticationMode,cJSON_GetObjectItem(CtSgwWLANDevice, "BasicAuthenticationMode")->valuestring);  
				strcpy(target_param1.WPAEncryptionModes,cJSON_GetObjectItem(CtSgwWLANDevice, "WPAEncryptionModes")->valuestring);  
				target_param1.SSIDHide=atoi(cJSON_GetObjectItem(CtSgwWLANDevice, "SSIDHide")->valuestring);   

				target_param1.RFBand=atoi(cJSON_GetObjectItem(CtSgwWLANDevice, "RFBand")->valuestring); 
				target_param1.ChannelWidth=atoi(cJSON_GetObjectItem(CtSgwWLANDevice, "ChannelWidth")->valuestring);  
				target_param1.GuardInterval=atoi(cJSON_GetObjectItem(CtSgwWLANDevice, "GuardInterval")->valuestring);  
				target_param1.RetryTimeout=atoi(cJSON_GetObjectItem(CtSgwWLANDevice, "RetryTimeout")->valuestring);  
				target_param1.Powerlevel=atoi(cJSON_GetObjectItem(CtSgwWLANDevice, "Powerlevel")->valuestring);   
				//target_param1.PowerLevel_5G=atoi(cJSON_GetObjectItem(CtSgwWLANDevice, "PowerLevel_5G")->valuestring); 
				target_param1.PowerValue=atoi(cJSON_GetObjectItem(CtSgwWLANDevice, "PowerValue")->valuestring);  
				//target_param1.APModuleEnable=atoi(cJSON_GetObjectItem(CtSgwWLANDevice, "APModuleEnable")->valuestring);  
				//target_param1.WPSKeyWord=atoi(cJSON_GetObjectItem(CtSgwWLANDevice, "WPSKeyWord")->valuestring);  
				strcpy(target_param1.PWD,cJSON_GetObjectItem(CtSgwWLANDevice, "PWD")->valuestring); 

				if(FALSE == CheckCtSgwWLANDevice_t(&out_param1,&target_param1))
					 fill_capi_result("CtSgwGetWLANDeviceBySSID","failed",return_value,t_diff);   
			        else
					 fill_capi_result("CtSgwGetWLANDeviceBySSID","pass",return_value,t_diff);
			}
			break;
	
	case CtSgwSetWLANDevice_NUM:{
			        CtSgwObjPath_t path;
				CtSgwWLANDevice_t target_param1;
				cJSON *in = cJSON_GetObjectItem(testcase,"in");
				cJSON *CtSgwWLANDevice = cJSON_GetObjectItem(in,"CtSgwWLANDevice_t");

				strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring);
				strcpy(target_param1.SSID,cJSON_GetObjectItem(CtSgwWLANDevice, "SSID")->valuestring); 
				target_param1.Enable=atoi(cJSON_GetObjectItem(CtSgwWLANDevice, "Enable")->valuestring);  
				target_param1.Channel=atoi(cJSON_GetObjectItem(CtSgwWLANDevice, "Channel")->valuestring);  
				//target_param1.ChannelInUse=atoi(cJSON_GetObjectItem(CtSgwWLANDevice, "ChannelInUse")->valuestring);  
				strcpy(target_param1.BeaconType,cJSON_GetObjectItem(CtSgwWLANDevice, "BeaconType")->valuestring);   
				strcpy(target_param1.Standard,cJSON_GetObjectItem(CtSgwWLANDevice, "Standard")->valuestring); 
				strcpy(target_param1.WEPEncryptionLevel,cJSON_GetObjectItem(CtSgwWLANDevice, "WEPEncryptionLevel")->valuestring);  
				strcpy(target_param1.BasicAuthenticationMode,cJSON_GetObjectItem(CtSgwWLANDevice, "BasicAuthenticationMode")->valuestring);  
				strcpy(target_param1.WPAEncryptionModes,cJSON_GetObjectItem(CtSgwWLANDevice, "WPAEncryptionModes")->valuestring);  
				target_param1.SSIDHide=atoi(cJSON_GetObjectItem(CtSgwWLANDevice, "SSIDHide")->valuestring);   

				target_param1.RFBand=atoi(cJSON_GetObjectItem(CtSgwWLANDevice, "RFBand")->valuestring); 
				target_param1.ChannelWidth=atoi(cJSON_GetObjectItem(CtSgwWLANDevice, "ChannelWidth")->valuestring);  
				target_param1.GuardInterval=atoi(cJSON_GetObjectItem(CtSgwWLANDevice, "GuardInterval")->valuestring);  
				target_param1.RetryTimeout=atoi(cJSON_GetObjectItem(CtSgwWLANDevice, "RetryTimeout")->valuestring);  
				target_param1.Powerlevel=atoi(cJSON_GetObjectItem(CtSgwWLANDevice, "Powerlevel")->valuestring);   
				//target_param1.PowerLevel_5G=atoi(cJSON_GetObjectItem(CtSgwWLANDevice, "PowerLevel_5G")->valuestring); 
				//target_param1.PowerValue=atoi(cJSON_GetObjectItem(CtSgwWLANDevice, "PowerValue")->valuestring);  
				//target_param1.APModuleEnable=atoi(cJSON_GetObjectItem(CtSgwWLANDevice, "APModuleEnable")->valuestring);  
				//target_param1.WPSKeyWord=atoi(cJSON_GetObjectItem(CtSgwWLANDevice, "WPSKeyWord")->valuestring);  
				strcpy(target_param1.PWD,cJSON_GetObjectItem(CtSgwWLANDevice, "PWD")->valuestring); 
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				return_value = CtSgwSetWLANDevice(path,&target_param1);     


			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
		
  
				if(FALSE == Check_return_result(return_value,atoi(return_target))) 
					 fill_capi_result("CtSgwSetWLANDevice","failed",return_value,t_diff); 
			        else
					 fill_capi_result("CtSgwSetWLANDevice","pass",return_value,t_diff); 

			}
			break;

	case CtSgwGetWiFiTimer_NUM:{
			         
				CtSgwWiFiTimer_t out_param1;
				CtSgwWiFiTimer_t target_param1;
				cJSON *target = cJSON_GetObjectItem(testcase,"target");
				cJSON *CtSgwWiFiTimer = cJSON_GetObjectItem(target,"CtSgwWiFiTimer_t");
				

 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
				return_value = CtSgwGetWiFiTimer(&out_param1);  
			
			        if(FALSE == Check_return_result(return_value,atoi(return_target)))
			        {	
					 fill_capi_result("CtSgwGetWiFiTimer","failed",return_value,t_diff);
					break;
			        }
                        gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
  


				strcpy(target_param1.StartTime,cJSON_GetObjectItem(CtSgwWiFiTimer, "StartTime")->valuestring); 
				strcpy(target_param1.EndTime,cJSON_GetObjectItem(CtSgwWiFiTimer, "EndTime")->valuestring);  
				strcpy(target_param1.ControlCycle,cJSON_GetObjectItem(CtSgwWiFiTimer, "ControlCycle")->valuestring);  
				target_param1.Enable=atoi(cJSON_GetObjectItem(CtSgwWiFiTimer, "Enable")->valuestring);  
				strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgwWiFiTimer, "path"),"str")->valuestring);
				if(FALSE == CheckCtSgwWiFiTimer_t(&out_param1,&target_param1))
					 fill_capi_result("CtSgwGetWiFiTimer","failed",return_value,t_diff);   
			        else
					 fill_capi_result("CtSgwGetWiFiTimer","pass",return_value,t_diff);
			}
			break;
	case CtSgwSetWiFiTimer_NUM:{
			         
				CtSgwWiFiTimer_t target_param1;
				cJSON *in = cJSON_GetObjectItem(testcase,"in");
				cJSON *CtSgwWiFiTimer = cJSON_GetObjectItem(in,"CtSgwWiFiTimer_t");

				strcpy(target_param1.StartTime,cJSON_GetObjectItem(CtSgwWiFiTimer, "StartTime")->valuestring); 
				strcpy(target_param1.EndTime,cJSON_GetObjectItem(CtSgwWiFiTimer, "EndTime")->valuestring);  
				strcpy(target_param1.ControlCycle,cJSON_GetObjectItem(CtSgwWiFiTimer, "ControlCycle")->valuestring);  
				target_param1.Enable=atoi(cJSON_GetObjectItem(CtSgwWiFiTimer, "Enable")->valuestring);  
				strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgwWiFiTimer, "path"),"str")->valuestring);				

                                 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
				return_value = CtSgwSetWiFiTimer(&target_param1);  
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
  
				if(FALSE == Check_return_result(return_value,atoi(return_target))) 
					 fill_capi_result("CtSgwSetWiFiTimer","failed",return_value,t_diff); 
			        else
					 fill_capi_result("CtSgwSetWiFiTimer","pass",return_value,t_diff); 	
			}
			break;
	
	case CtSgwGetWiFiExTimerObjs_NUM:{
			         
				CtSgwWiFiTimer1_t *out_param1 = NULL;
				int out_count;
				int target_count;
				CtSgwWiFiTimer1_t target_param1;
				cJSON *target = cJSON_GetObjectItem(testcase,"target");

 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				return_value = CtSgwGetWiFiExTimerObjs(&out_param1,&out_count); 

			
      
			        if(FALSE == Check_return_result(return_value,atoi(return_target)))
			        {	
					fill_capi_result("CtSgwGetWiFiExTimerObjs","failed",return_value,t_diff);
					g_free(out_param1);
					break;
			        }

                        gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;


				cJSON * CtSgwWiFiTimer1 = cJSON_GetObjectItem(target, "CtSgwWiFiTimer1_t");

				target_count=atoi(cJSON_GetObjectItem(target, "count")->valuestring);
				Check_int(out_count,target_count);
			        if(out_count > target_count)
			        {
				     out_count = target_count;
			        }
				else if(out_count == 0)
				{
					fill_capi_result("CtSgwGetWiFiExTimerObjs","pass",return_value,t_diff);
					g_free(out_param1);
					break;
				}
				int index=0;
				for (index = 0; index < out_count; index++)
				{
				   	strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWiFiTimer1, index), "path"),"str")->valuestring);
					strcpy(target_param1.WeekDay->str,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWiFiTimer1, index), "WeekDay")->valuestring); 
					strcpy(target_param1.Time,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWiFiTimer1, index), "Time")->valuestring);  
					strcpy(target_param1.Active,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWiFiTimer1, index), "Active")->valuestring);  
					target_param1.Enable = atoi(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWiFiTimer1, index), "Enable")->valuestring);   
					if(FALSE == CheckCtSgwWiFiTimer1_t(&(out_param1[index]),&target_param1))
						 fill_capi_result("CtSgwGetWiFiExTimerObjs","failed",return_value,t_diff); 
			       	        else
						 fill_capi_result("CtSgwGetWiFiExTimerObjs","pass",return_value,t_diff); 
				} 
			g_free(out_param1);
			}
			break;

	case CtSgwGetWiFiExTimer_NUM:{
			         
				CtSgwWiFiTimer1_t out_param1;
				CtSgwObjPath_t path;
				CtSgwWiFiTimer1_t target_param1;
				cJSON *target = cJSON_GetObjectItem(testcase,"target");
				cJSON *CtSgwWiFiTimer1 = cJSON_GetObjectItem(target,"CtSgwWiFiTimer1_t");
				cJSON *in = cJSON_GetObjectItem(testcase,"in");
				strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring); 

 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
				return_value = CtSgwGetWiFiExTimer(path,&out_param1);   

    
			        if(FALSE == Check_return_result(return_value,atoi(return_target)))
			        {	
					fill_capi_result("CtSgwGetWiFiExTimer","failed",return_value,t_diff);
					break;
			        }
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start; 

				strcpy(target_param1.WeekDay->str,cJSON_GetObjectItem(CtSgwWiFiTimer1, "WeekDay")->valuestring); 
				strcpy(target_param1.Time,cJSON_GetObjectItem(CtSgwWiFiTimer1, "Time")->valuestring);  
				strcpy(target_param1.Active,cJSON_GetObjectItem(CtSgwWiFiTimer1, "Active")->valuestring);  
				target_param1.Enable=atoi(cJSON_GetObjectItem(CtSgwWiFiTimer1, "Enable")->valuestring);  
				strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgwWiFiTimer1, "path"),"str")->valuestring);
				if(FALSE == CheckCtSgwWiFiTimer1_t(&out_param1,&target_param1))
					 fill_capi_result("CtSgwGetWiFiExTimer","failed",return_value,t_diff);  
			        else
					 fill_capi_result("CtSgwGetWiFiExTimer","pass",return_value,t_diff);
			}
			break;

	case CtSgwSetWiFiExTimer_NUM:{
			        CtSgwObjPath_t path;
				CtSgwWiFiTimer1_t target_param1;
				cJSON *in = cJSON_GetObjectItem(testcase,"in");
				cJSON *CtSgwWiFiTimer1 = cJSON_GetObjectItem(in,"CtSgwWiFiTimer1_t");

				strcpy(target_param1.WeekDay->str,cJSON_GetObjectItem(CtSgwWiFiTimer1, "WeekDay")->valuestring); 
				strcpy(target_param1.Time,cJSON_GetObjectItem(CtSgwWiFiTimer1, "Time")->valuestring);  
				strcpy(target_param1.Active,cJSON_GetObjectItem(CtSgwWiFiTimer1, "Active")->valuestring);  
				target_param1.Enable=atoi(cJSON_GetObjectItem(CtSgwWiFiTimer1, "Enable")->valuestring);  
				strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring);

 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
				return_value = CtSgwSetWiFiExTimer(path,&target_param1);  


			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
     
				if(FALSE == Check_return_result(return_value,atoi(return_target))) 
					 fill_capi_result("CtSgwSetWiFiExTimer","failed",return_value,t_diff); 
			        else
					 fill_capi_result("CtSgwSetWiFiExTimer","pass",return_value,t_diff); 

			}
			break;
	case CtSgwAddWiFiExTimer_NUM:{
			         
				CtSgwWiFiTimer1_t target_param1;
				cJSON *in = cJSON_GetObjectItem(testcase,"in");
				cJSON *CtSgwWiFiTimer1 = cJSON_GetObjectItem(in,"CtSgwWiFiTimer1_t");

				strcpy(target_param1.WeekDay->str,cJSON_GetObjectItem(CtSgwWiFiTimer1, "WeekDay")->valuestring); 
				strcpy(target_param1.Time,cJSON_GetObjectItem(CtSgwWiFiTimer1, "Time")->valuestring);  
				strcpy(target_param1.Active,cJSON_GetObjectItem(CtSgwWiFiTimer1, "Active")->valuestring);  
				target_param1.Enable=atoi(cJSON_GetObjectItem(CtSgwWiFiTimer1, "Enable")->valuestring);  
				strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgwWiFiTimer1, "path"),"str")->valuestring);
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				return_value = CtSgwAddWiFiExTimer(&target_param1); 
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
      
				if(FALSE == Check_return_result(return_value,atoi(return_target))) 
					 fill_capi_result("CtSgwAddWiFiExTimer","failed",return_value,t_diff); 
			        else
					 fill_capi_result("CtSgwAddWiFiExTimer","pass",return_value,t_diff);

			}
			break;
	case CtSgwDelWiFiExTimer_NUM:{
			         
				CtSgwObjPath_t path;
				cJSON *in = cJSON_GetObjectItem(testcase,"in");
				strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring);                        

 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
				return_value = CtSgwDelWiFiExTimer(path);  
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
     
				if(FALSE == Check_return_result(return_value,atoi(return_target))) 
					 fill_capi_result("CtSgwDelWiFiExTimer","failed",return_value,t_diff); 
			        else
					 fill_capi_result("CtSgwDelWiFiExTimer","pass",return_value,t_diff); 
			}
			break;
	case CtSgwGetLED_NUM:{
			         
				CtSgwLED_t out_param1;
				CtSgwLED_t target_param1;
				cJSON *target = cJSON_GetObjectItem(testcase,"target");
				cJSON *CtSgwLED = cJSON_GetObjectItem(target,"CtSgwLED_t");
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				return_value = CtSgwGetLED(&out_param1);       
			        if(FALSE == Check_return_result(return_value,atoi(return_target)))
			        {	
					 fill_capi_result("CtSgwGetLED","failed",return_value,t_diff);
					break;
			        }

			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;

				strcpy(target_param1.Status,cJSON_GetObjectItem(CtSgwLED, "Status")->valuestring); 
				strcpy(target_param1.StartTime,cJSON_GetObjectItem(CtSgwLED, "StartTime")->valuestring);  
				strcpy(target_param1.EndTime,cJSON_GetObjectItem(CtSgwLED, "EndTime")->valuestring);  
				strcpy(target_param1.ControlCycle,cJSON_GetObjectItem(CtSgwLED, "ControlCycle")->valuestring);  
				target_param1.Enable=atoi(cJSON_GetObjectItem(CtSgwLED, "Enable")->valuestring); 
				strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgwLED, "path"),"str")->valuestring);
				if(FALSE == CheckCtSgwLED_t(&out_param1,&target_param1))
					 fill_capi_result("CtSgwGetLED","failed",return_value,t_diff);  
			        else
					 fill_capi_result("CtSgwGetLED","pass",return_value,t_diff);
			}
			break;
	case CtSgwSetLED_NUM:{
			         
				CtSgwLED_t target_param1;
				cJSON *in = cJSON_GetObjectItem(testcase,"in");
				cJSON *CtSgwLED = cJSON_GetObjectItem(in,"CtSgwLED_t");

				strcpy(target_param1.Status,cJSON_GetObjectItem(CtSgwLED, "Status")->valuestring); 
				strcpy(target_param1.StartTime,cJSON_GetObjectItem(CtSgwLED, "StartTime")->valuestring);  
				strcpy(target_param1.EndTime,cJSON_GetObjectItem(CtSgwLED, "EndTime")->valuestring);  
				strcpy(target_param1.ControlCycle,cJSON_GetObjectItem(CtSgwLED, "ControlCycle")->valuestring);  
				target_param1.Enable=atoi(cJSON_GetObjectItem(CtSgwLED, "Enable")->valuestring); 
				strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgwLED, "path"),"str")->valuestring);
			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;	

                         return_value = CtSgwSetLED(&target_param1);    
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
   
				if(FALSE == Check_return_result(return_value,atoi(return_target))) 
					 fill_capi_result("CtSgwSetLED","failed",return_value,t_diff); 
			        else
					 fill_capi_result("CtSgwSetLED","pass",return_value,t_diff);
			}
			break;
	case CtSgwGetSleepTimerObjs_NUM:{
			         
				CtSgwSleepTimer_t* out_param1 = NULL;
				gint32 out_count;
				gint32 target_count;
				CtSgwSleepTimer_t target_param1;
				cJSON *target = cJSON_GetObjectItem(testcase,"target");

 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				return_value = CtSgwGetSleepTimerObjs(&out_param1,&out_count);       
			        if(FALSE == Check_return_result(return_value,atoi(return_target)))
			        {	
					 fill_capi_result("CtSgwGetSleepTimerObjs","failed",return_value,t_diff);
					g_free(out_param1);
					break;
			        }

			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;


				cJSON * CtSgwSleepTimer = cJSON_GetObjectItem(target, "CtSgwSleepTimer_t");

				target_count=atoi(cJSON_GetObjectItem(target, "count")->valuestring);
				Check_int(out_count,target_count);
			        if(out_count > target_count)
			        {
				     out_count = target_count;
			        }
				else if(out_count == 0)
				{
					fill_capi_result("CtSgwGetSleepTimerObjs","pass",return_value,t_diff);
					g_free(out_param1);
					break;
				}
				int index=0;
				for (index = 0; index < out_count; index++)
				{
				   	strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwSleepTimer, index), "path"),"str")->valuestring);
					strcpy(target_param1.Day->str,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwSleepTimer, index), "Day")->valuestring); 
					strcpy(target_param1.Time,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwSleepTimer, index), "Time")->valuestring); 
					strcpy(target_param1.Active,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwSleepTimer, index), "Active")->valuestring); 
					target_param1.Enable=atoi(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwSleepTimer, index), "Enable")->valuestring); 
					if(FALSE == CheckCtSgwSleepTimer_t(&(out_param1[index]),&target_param1))
						 fill_capi_result("CtSgwGetSleepTimerObjs","failed",return_value,t_diff);
			       		else
						 fill_capi_result("CtSgwGetSleepTimerObjs","pass",return_value,t_diff);   
				}
				g_free(out_param1);
			}
			break;
	case CtSgwGetSleepTimer_NUM:{
			         
				CtSgwSleepTimer_t out_param1;
				CtSgwObjPath_t path;
				CtSgwSleepTimer_t target_param1;
				cJSON *target = cJSON_GetObjectItem(testcase,"target");
				cJSON *CtSgwSleepTimer = cJSON_GetObjectItem(target,"CtSgwSleepTimer_t");
				cJSON *in = cJSON_GetObjectItem(testcase,"in");
				strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring);                          
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
				return_value = CtSgwGetSleepTimer(path,&out_param1);   

			        if(FALSE == Check_return_result(return_value,atoi(return_target)))
			        {	
					 fill_capi_result("CtSgwGetSleepTimer","failed",return_value,t_diff);
					break;
			        }

			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
		


				strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgwSleepTimer, "path"),"str")->valuestring);
				strcpy(target_param1.Day->str,cJSON_GetObjectItem(CtSgwSleepTimer, "Day")->valuestring); 
				strcpy(target_param1.Time,cJSON_GetObjectItem(CtSgwSleepTimer, "Time")->valuestring); 
				strcpy(target_param1.Active,cJSON_GetObjectItem(CtSgwSleepTimer, "Active")->valuestring); 
				target_param1.Enable=atoi(cJSON_GetObjectItem(CtSgwSleepTimer, "Enable")->valuestring);  

				if(FALSE == CheckCtSgwSleepTimer_t(&out_param1,&target_param1))
					 fill_capi_result("CtSgwGetSleepTimer","failed",return_value,t_diff);  
			        else
					 fill_capi_result("CtSgwGetSleepTimer","pass",return_value,t_diff);
			}
			break;
	case CtSgwSetSleepTimer_NUM:{
			        CtSgwObjPath_t path;
				CtSgwSleepTimer_t target_param1;
				cJSON *in = cJSON_GetObjectItem(testcase,"in");
				cJSON *CtSgwSleepTimer = cJSON_GetObjectItem(in,"CtSgwSleepTimer_t");

				strcpy(target_param1.Day->str,cJSON_GetObjectItem(CtSgwSleepTimer, "Day")->valuestring); 
				strcpy(target_param1.Time,cJSON_GetObjectItem(CtSgwSleepTimer, "Time")->valuestring); 
				strcpy(target_param1.Active,cJSON_GetObjectItem(CtSgwSleepTimer, "Active")->valuestring); 
				target_param1.Enable=atoi(cJSON_GetObjectItem(CtSgwSleepTimer, "Enable")->valuestring);  
				strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring);
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				return_value = CtSgwSetSleepTimer(path,&target_param1);  

			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
     
				if(FALSE == Check_return_result(return_value,atoi(return_target))) 
					 fill_capi_result("CtSgwSetSleepTimer","failed",return_value,t_diff); 
			        else
					 fill_capi_result("CtSgwSetSleepTimer","pass",return_value,t_diff);

			}
			break;
	case CtSgwAddSleepTimer_NUM:{
			         
				CtSgwSleepTimer_t target_param1;
				cJSON *in = cJSON_GetObjectItem(testcase,"in");
				cJSON *CtSgwSleepTimer = cJSON_GetObjectItem(in,"CtSgwSleepTimer_t");
				strcpy(target_param1.Day->str,cJSON_GetObjectItem(CtSgwSleepTimer, "Day")->valuestring); 
				strcpy(target_param1.Time,cJSON_GetObjectItem(CtSgwSleepTimer, "Time")->valuestring); 
				strcpy(target_param1.Active,cJSON_GetObjectItem(CtSgwSleepTimer, "Active")->valuestring); 
				target_param1.Enable=atoi(cJSON_GetObjectItem(CtSgwSleepTimer, "Enable")->valuestring); 
				strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgwSleepTimer, "path"),"str")->valuestring);
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
				return_value = CtSgwAddSleepTimer(&target_param1);   

			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
		
    
				if(FALSE == Check_return_result(return_value,atoi(return_target))) 
					 fill_capi_result("CtSgwAddSleepTimer","failed",return_value,t_diff); 
			        else
					 fill_capi_result("CtSgwAddSleepTimer","pass",return_value,t_diff); 

			}
			break;
	case CtSgwDelSleepTimer_NUM:{
			         
				CtSgwObjPath_t path;

				cJSON *in = cJSON_GetObjectItem(testcase,"in");
				strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring);                          
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				return_value = CtSgwDelSleepTimer(path);  
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
     
				if(FALSE == Check_return_result(return_value,atoi(return_target))) 
					 fill_capi_result("CtSgwDelSleepTimer","failed",return_value,t_diff); 
			        else
					 fill_capi_result("CtSgwDelSleepTimer","pass",return_value,t_diff);
			}
			break;

	case CtSgwSysCmdSetDateTime_NUM:{
			        gint32 out_result = -1;
			        //gint32 target_result;
				char datetime[MAX_TIME_LEN+1] = "";
				gchar *out_errdesc = NULL;
				//gchar *target_errdesc = NULL;

				cJSON *in = cJSON_GetObjectItem(testcase,"in");
				//cJSON *target = cJSON_GetObjectItem(testcase,"target");

				strcpy(datetime,cJSON_GetObjectItem(in,"datetime")->valuestring);  
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				return_value = CtSgwSysCmdSetDateTime(datetime,&out_result,&out_errdesc);

			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;

				if(FALSE == Check_return_result(return_value,atoi(return_target))) 
				{
					 fill_capi_result("CtSgwSysCmdSetDateTime","failed",return_value,t_diff); 
					 //strcpy(target_errdesc,cJSON_GetObjectItem(target,"errdesc")->valuestring);
					 Check_char(out_errdesc,NULL);
				}
			        else
				{
					 fill_capi_result("CtSgwSysCmdSetDateTime","pass",return_value,t_diff);
					 //target_result = atoi(cJSON_GetObjectItem(target,"result")->valuestring);
					 Check_int(out_result,0);
				}
			g_free(out_errdesc);
			}
			break;
	case CtSgwSysCmdSetDevName_NUM:{
			        guint32 out_res = -1;
			        //guint32 target_res;
				gchar *out_errdesc = NULL;
				//gchar *target_errdesc = NULL;

				char devname[MAX_DEVNAME_LEN+1] = "";
				cJSON *in = cJSON_GetObjectItem(testcase,"in");
				//cJSON *target = cJSON_GetObjectItem(testcase,"target");

				strcpy(devname,cJSON_GetObjectItem(in,"devname")->valuestring);  
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				return_value = CtSgwSysCmdSetDevName(devname,&out_res,&out_errdesc);  

			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
     
				if(FALSE == Check_return_result(return_value,atoi(return_target))) 
				{
					 fill_capi_result("CtSgwSysCmdSetDevName","failed",return_value,t_diff); 
					// strcpy(target_errdesc,cJSON_GetObjectItem(target,"errdesc")->valuestring);
					 Check_char(out_errdesc,NULL);
				}
			        else
				{
					 fill_capi_result("CtSgwSysCmdSetDevName","pass",return_value,t_diff);
					//target_res = atoi(cJSON_GetObjectItem(target,"res")->valuestring);
					Check_int(out_res,0);
				}
			g_free(out_errdesc);
			}
			break;

	case CtSgwSysCmdCheckUAPasswd_NUM:{
			         
				char pass[128] = "";
				int out_result = -1;
				//int target_result;
				gchar *out_errdesc = NULL;
				//gchar *target_errdesc = NULL;

				cJSON *in = cJSON_GetObjectItem(testcase,"in");
				//cJSON *target = cJSON_GetObjectItem(testcase,"target");

				strcpy(pass,cJSON_GetObjectItem(in,"pass")->valuestring);  
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				return_value = CtSgwSysCmdCheckUAPasswd(pass,&out_result,&out_errdesc);  

			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
     
			        if(FALSE == Check_return_result(return_value,atoi(return_target)))
				{				
					 fill_capi_result("CtSgwSysCmdCheckUAPasswd","failed",return_value,t_diff); 
					 //strcpy(target_errdesc,cJSON_GetObjectItem(target,"errdesc")->valuestring);
					 Check_char(out_errdesc,NULL);
				}
			        else
				{
					 fill_capi_result("CtSgwSysCmdCheckUAPasswd","pass",return_value,t_diff);
					 //target_result=atoi(cJSON_GetObjectItem(target,"result")->valuestring);  
					 Check_int(out_result,0);
				}
			g_free(out_errdesc);
			}
			break;
	case CtSgwSysCmdSetUAPasswd_NUM:{
			         
				char pass[128] = "";
				//int target_result;
				int out_result = -1;
				gchar *out_errdesc = NULL;
				//gchar *target_errdesc = NULL;

				cJSON *in = cJSON_GetObjectItem(testcase,"in");
				//cJSON *target = cJSON_GetObjectItem(testcase,"target");

				strcpy(pass,cJSON_GetObjectItem(in,"pass")->valuestring);  

 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				return_value = CtSgwSysCmdSetUAPasswd(pass,&out_result,&out_errdesc);  
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;

 
			        if(FALSE == Check_return_result(return_value,atoi(return_target)))
				{					 
					fill_capi_result("CtSgwSysCmdSetUAPasswd","failed",return_value,t_diff); 
					//strcpy(target_errdesc,cJSON_GetObjectItem(target,"errdesc")->valuestring);
					Check_char(out_errdesc,NULL);
				}
			        else
				{
					 fill_capi_result("CtSgwSysCmdSetUAPasswd","pass",return_value,t_diff);
					 //target_result=atoi(cJSON_GetObjectItem(target,"result")->valuestring);  
					 Check_int(out_result,0);
				}
			g_free(out_errdesc);
			}
			break;
	case CtSgwSysCmdCheckTAPasswd_NUM:{
			         
				char pass[128] = "";
				int out_result = -1;
				//int target_result;
				gchar *out_errdesc = NULL;
				//gchar *target_errdesc = NULL;

				cJSON *in = cJSON_GetObjectItem(testcase,"in");
				//cJSON *target = cJSON_GetObjectItem(testcase,"target");

				strcpy(pass,cJSON_GetObjectItem(in,"pass")->valuestring);  
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				return_value = CtSgwSysCmdCheckTAPasswd(pass,&out_result,&out_errdesc); 

			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
		
      
			        if(FALSE == Check_return_result(return_value,atoi(return_target)))
				{				
					fill_capi_result("CtSgwSysCmdCheckTAPasswd","failed",return_value,t_diff); 
					//strcpy(target_errdesc,cJSON_GetObjectItem(target,"errdesc")->valuestring);
					Check_char(out_errdesc,NULL);
				}
			        else
				{
					 fill_capi_result("CtSgwSysCmdCheckTAPasswd","pass",return_value,t_diff);
					//target_result=atoi(cJSON_GetObjectItem(target,"result")->valuestring);  
					Check_int(out_result,0);
				}
			g_free(out_errdesc);
			}
			break;

	case CtSgwGetPPPoEConfig_NUM:{
			         
				CtSgwPPPoE_t out_param1;
				CtSgwPPPoE_t target_param1;

				cJSON *target = cJSON_GetObjectItem(testcase,"target");  
				cJSON *CtSgwPPPoE = cJSON_GetObjectItem(target,"CtSgwPPPoE_t");

 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				return_value = CtSgwGetPPPoEConfig(&out_param1);

			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;

			        if(FALSE == Check_return_result(return_value,atoi(return_target)))
			        {	
					fill_capi_result("CtSgwGetPPPoEConfig","failed",return_value,t_diff);
					break;
			        }
				strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgwPPPoE, "path"),"str")->valuestring);
				strcpy(target_param1.PPPoEUserName,cJSON_GetObjectItem(CtSgwPPPoE, "PPPoEUserName")->valuestring); 

				if(FALSE == CheckCtSgwPPPoE_t(&out_param1,&target_param1))
					 fill_capi_result("CtSgwGetPPPoEConfig","failed",return_value,t_diff);   
			        else
					 fill_capi_result("CtSgwGetPPPoEConfig","pass",return_value,t_diff);
			}
			break;

	case CtSgwGetDHCPServer_NUM:{
			         
				CtSgwDHCPServer_t out_param1;
				CtSgwDHCPServer_t target_param1;

				cJSON *target = cJSON_GetObjectItem(testcase,"target");  
				cJSON *CtSgwDHCPServer = cJSON_GetObjectItem(target,"CtSgwDHCPServer_t");

 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				return_value = CtSgwGetDHCPServer(&out_param1);
			        if(FALSE == Check_return_result(return_value,atoi(return_target)))
			        {	
					 fill_capi_result("CtSgwGetDHCPServer","failed",return_value,t_diff);
					break;
			        }

			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;

				strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgwDHCPServer, "path"),"str")->valuestring);
				target_param1.Enable=atoi(cJSON_GetObjectItem(CtSgwDHCPServer, "Enable")->valuestring); 
				strcpy(target_param1.MinAddress,cJSON_GetObjectItem(CtSgwDHCPServer, "MinAddress")->valuestring); 
				strcpy(target_param1.MaxAddress,cJSON_GetObjectItem(CtSgwDHCPServer, "MaxAddress")->valuestring); 
				strcpy(target_param1.IPAddr,cJSON_GetObjectItem(CtSgwDHCPServer, "IPAddr")->valuestring); 
				strcpy(target_param1.SubnetMask,cJSON_GetObjectItem(CtSgwDHCPServer, "SubnetMask")->valuestring); 
				target_param1.LeaseTime=atoi(cJSON_GetObjectItem(CtSgwDHCPServer, "LeaseTime")->valuestring); 

				if(FALSE == CheckCtSgwDHCPServer_t(&out_param1,&target_param1))
					 fill_capi_result("CtSgwGetDHCPServer","failed",return_value,t_diff);   
			        else
					 fill_capi_result("CtSgwGetDHCPServer","pass",return_value,t_diff);
			}
			break;
	case CtSgwSetDHCPServer_NUM:{
			         
				CtSgwDHCPServer_t target_param1;

				cJSON *in = cJSON_GetObjectItem(testcase,"in");  
				cJSON *CtSgwDHCPServer = cJSON_GetObjectItem(in,"CtSgwDHCPServer_t"); 
				target_param1.Enable=atoi(cJSON_GetObjectItem(CtSgwDHCPServer, "Enable")->valuestring);
				strcpy(target_param1.IPAddr,cJSON_GetObjectItem(CtSgwDHCPServer, "IPAddr")->valuestring); 
				strcpy(target_param1.MinAddress,cJSON_GetObjectItem(CtSgwDHCPServer, "MinAddress")->valuestring); 
				strcpy(target_param1.MaxAddress,cJSON_GetObjectItem(CtSgwDHCPServer, "MaxAddress")->valuestring); 
				strcpy(target_param1.SubnetMask,cJSON_GetObjectItem(CtSgwDHCPServer, "SubnetMask")->valuestring); 
				target_param1.LeaseTime=atoi(cJSON_GetObjectItem(CtSgwDHCPServer, "LeaseTime")->valuestring); 
				strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgwDHCPServer, "path"),"str")->valuestring);

 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
				return_value = CtSgwSetDHCPServer(&target_param1);
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;

				if(FALSE == Check_return_result(return_value,atoi(return_target))) 
					 fill_capi_result("CtSgwSetDHCPServer","failed",return_value,t_diff); 
			        else
					 fill_capi_result("CtSgwSetDHCPServer","pass",return_value,t_diff); 

			}
			break;

	case CtSgwGetPortMappingObjs_NUM:{
			         
				CtSgwPortMapping_t* out_param1 = NULL;
				CtSgwPortMapping_t target_param1;
				int out_count;
				int target_count;
				cJSON *target = cJSON_GetObjectItem(testcase,"target");

 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
				return_value = CtSgwGetPortMappingObjs(&out_param1,&out_count); 

			        if(FALSE == Check_return_result(return_value,atoi(return_target)))
			        {	
					 fill_capi_result("CtSgwGetPortMappingObjs","failed",return_value,t_diff);
					g_free(out_param1);
					break;
			        }
                        gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;


				cJSON * CtSgwPortMapping = cJSON_GetObjectItem(target, "CtSgwPortMapping_t");

				target_count=atoi(cJSON_GetObjectItem(target, "count")->valuestring);
				Check_int(out_count,target_count);
			        if(out_count > target_count)
			        {
				     out_count = target_count;
			        }
			        else if(out_count == 0)
			        {
				     fill_capi_result("CtSgwGetPortMappingObjs","pass",return_value,t_diff);
				     g_free(out_param1);
				     break;
			        }
				int index=0;
				for (index = 0; index < out_count; index++)
				{
				   	strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwPortMapping, index), "path"),"str")->valuestring);
					//strcpy(target_param1.WANPath,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwPortMapping, index), "WANPath")->valuestring); 
					target_param1.Enable=atoi(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwPortMapping, index), "Enable")->valuestring); 
					target_param1.LeaseDuration=atoi(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwPortMapping, index), "LeaseDuration")->valuestring); 
					strcpy(target_param1.RemoteHost,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwPortMapping, index), "RemoteHost")->valuestring); 
					target_param1.ExternalPort=atoi(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwPortMapping, index), "ExternalPort")->valuestring); 
					target_param1.InternalPort=atoi(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwPortMapping, index), "InternalPort")->valuestring); 
					strcpy(target_param1.PortMappingProtocol,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwPortMapping, index), "PortMappingProtocol")->valuestring); 
					strcpy(target_param1.InternalClient,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwPortMapping, index), "InternalClient")->valuestring); 
					strcpy(target_param1.Description,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwPortMapping, index), "Description")->valuestring); 
					if(FALSE == CheckCtSgwPortMapping_t(&(out_param1[index]),&target_param1))
						 fill_capi_result("CtSgwGetPortMappingObjs","failed",return_value,t_diff);
			        	else
						 fill_capi_result("CtSgwGetPortMappingObjs","pass",return_value,t_diff);   
				}       
			g_free(out_param1);
			}
			break;
	case CtSgwGetPortMapping_NUM:{
			         
				CtSgwPortMapping_t out_param1;
				CtSgwPortMapping_t target_param1;
				CtSgwObjPath_t path;
				cJSON *target = cJSON_GetObjectItem(testcase,"target");
				cJSON *CtSgwPortMapping = cJSON_GetObjectItem(target,"CtSgwPortMapping_t");
				cJSON *in = cJSON_GetObjectItem(testcase,"in");
				strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring);                         
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
				return_value = CtSgwGetPortMapping(path,&out_param1); 

			        if(FALSE == Check_return_result(return_value,atoi(return_target)))
			        {	
					 fill_capi_result("CtSgwGetPortMapping","failed",return_value,t_diff);
					break;
			        }

			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;

				strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgwPortMapping, "path"),"str")->valuestring);
				//strcpy(target_param1.WANPath,cJSON_GetObjectItem(CtSgwPortMapping, "WANPath")->valuestring); 
				target_param1.Enable=atoi(cJSON_GetObjectItem(CtSgwPortMapping, "Enable")->valuestring); 
				target_param1.LeaseDuration=atoi(cJSON_GetObjectItem(CtSgwPortMapping, "LeaseDuration")->valuestring); 
				strcpy(target_param1.RemoteHost,cJSON_GetObjectItem(CtSgwPortMapping, "RemoteHost")->valuestring); 
				target_param1.ExternalPort=atoi(cJSON_GetObjectItem(CtSgwPortMapping, "ExternalPort")->valuestring); 
				target_param1.InternalPort=atoi(cJSON_GetObjectItem(CtSgwPortMapping, "InternalPort")->valuestring); 
				strcpy(target_param1.PortMappingProtocol,cJSON_GetObjectItem(CtSgwPortMapping, "PortMappingProtocol")->valuestring); 
				strcpy(target_param1.InternalClient,cJSON_GetObjectItem(CtSgwPortMapping, "InternalClient")->valuestring); 
				strcpy(target_param1.Description,cJSON_GetObjectItem(CtSgwPortMapping, "Description")->valuestring);      

				if(FALSE == CheckCtSgwPortMapping_t(&out_param1,&target_param1))
					 fill_capi_result("CtSgwGetPortMapping","failed",return_value,t_diff);  
			        else
					 fill_capi_result("CtSgwGetPortMapping","pass",return_value,t_diff);
			}
			break;
	case CtSgwAddPortMapping_NUM:{
			         
				CtSgwPortMapping_t target_param1;

				cJSON *in = cJSON_GetObjectItem(testcase,"in");
				cJSON *CtSgwPortMapping = cJSON_GetObjectItem(in,"CtSgwPortMapping_t");
				strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgwPortMapping, "path"),"str")->valuestring);
				//strcpy(target_param1.WANPath,cJSON_GetObjectItem(CtSgwPortMapping, "WANPath")->valuestring); 
				target_param1.Enable=atoi(cJSON_GetObjectItem(CtSgwPortMapping, "Enable")->valuestring); 
				target_param1.LeaseDuration=atoi(cJSON_GetObjectItem(CtSgwPortMapping, "LeaseDuration")->valuestring); 
				strcpy(target_param1.RemoteHost,cJSON_GetObjectItem(CtSgwPortMapping, "RemoteHost")->valuestring); 
				target_param1.ExternalPort=atoi(cJSON_GetObjectItem(CtSgwPortMapping, "ExternalPort")->valuestring); 
				target_param1.InternalPort=atoi(cJSON_GetObjectItem(CtSgwPortMapping, "InternalPort")->valuestring); 
				strcpy(target_param1.PortMappingProtocol,cJSON_GetObjectItem(CtSgwPortMapping, "PortMappingProtocol")->valuestring); 
				strcpy(target_param1.InternalClient,cJSON_GetObjectItem(CtSgwPortMapping, "InternalClient")->valuestring); 
				strcpy(target_param1.Description,cJSON_GetObjectItem(CtSgwPortMapping, "Description")->valuestring);        
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				return_value = CtSgwAddPortMapping(&target_param1); 
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;

				if(FALSE == Check_return_result(return_value,atoi(return_target))) 
					 fill_capi_result("CtSgwAddPortMapping","failed",return_value,t_diff); 
			        else
					 fill_capi_result("CtSgwAddPortMapping","pass",return_value,t_diff); 

			}
			break;

	case CtSgwDelPortMapping_NUM:{
			         
				CtSgwObjPath_t path;

				cJSON *in = cJSON_GetObjectItem(testcase,"in");
				strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring); 
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				return_value = CtSgwDelPortMapping(path); 
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
      
				if(FALSE == Check_return_result(return_value,atoi(return_target))) 
					 fill_capi_result("CtSgwDelPortMapping","failed",return_value,t_diff); 
			        else
					 fill_capi_result("CtSgwDelPortMapping","pass",return_value,t_diff); 
			}
			break;
	case CtSgwSetPortMapping_NUM:{
			        CtSgwObjPath_t path; 
				CtSgwPortMapping_t target_param1;

				cJSON *in = cJSON_GetObjectItem(testcase,"in");
				cJSON *CtSgwPortMapping = cJSON_GetObjectItem(in,"CtSgwPortMapping_t");
				strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring);
				//strcpy(target_param1.WANPath,cJSON_GetObjectItem(CtSgwPortMapping, "WANPath")->valuestring); 
				target_param1.Enable=atoi(cJSON_GetObjectItem(CtSgwPortMapping, "Enable")->valuestring); 
				target_param1.LeaseDuration=atoi(cJSON_GetObjectItem(CtSgwPortMapping, "LeaseDuration")->valuestring); 
				strcpy(target_param1.RemoteHost,cJSON_GetObjectItem(CtSgwPortMapping, "RemoteHost")->valuestring); 
				target_param1.ExternalPort=atoi(cJSON_GetObjectItem(CtSgwPortMapping, "ExternalPort")->valuestring); 
				target_param1.InternalPort=atoi(cJSON_GetObjectItem(CtSgwPortMapping, "InternalPort")->valuestring); 
				strcpy(target_param1.PortMappingProtocol,cJSON_GetObjectItem(CtSgwPortMapping, "PortMappingProtocol")->valuestring); 
				strcpy(target_param1.InternalClient,cJSON_GetObjectItem(CtSgwPortMapping, "InternalClient")->valuestring); 
				strcpy(target_param1.Description,cJSON_GetObjectItem(CtSgwPortMapping, "Description")->valuestring);      
                                g_print("CtSgw_USBSetLabel=====1\n");
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				return_value = CtSgwSetPortMapping(path,&target_param1); 
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;

                                g_print("CtSgw_USBSetLabel=====2\n");
				if(FALSE == Check_return_result(return_value,atoi(return_target))) 
					 fill_capi_result("CtSgwSetPortMapping","failed",return_value,t_diff); 
			        else
					 fill_capi_result("CtSgwSetPortMapping","pass",return_value,t_diff);
			}
			break;
	case CtSgw_USBMount_NUM:{
			         
				guint32 devid;
				char *out_mount_path = NULL;
				//char *target_mount_path = NULL;
				guint32 out_res = -1;
				//guint32 target_res;
				gchar *out_errdesc = NULL;
				//gchar *target_errdesc = NULL;

				cJSON *in = cJSON_GetObjectItem(testcase,"in");
				//cJSON *target = cJSON_GetObjectItem(testcase,"target");

				devid = atoi(cJSON_GetObjectItem(in, "devid")->valuestring);
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				return_value = CtSgw_USBMount(devid,&out_mount_path,&out_res,&out_errdesc); 

			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
 
			        if(FALSE == Check_return_result(return_value,atoi(return_target)))
				{	
					fill_capi_result("CtSgw_USBMount","failed",return_value,t_diff);
					//strcpy(target_errdesc,cJSON_GetObjectItem(target, "errdesc")->valuestring);
					Check_char(out_errdesc,NULL);
				}
				else
				{
					 fill_capi_result("CtSgw_USBMount","pass",return_value,t_diff);
					//strcpy(target_mount_path,cJSON_GetObjectItem(target, "mount_path")->valuestring);
					Check_char(out_mount_path,NULL);
					//target_res = atoi(cJSON_GetObjectItem(target, "res")->valuestring);
					Check_int(out_res,0);
				}
			g_free(out_errdesc);
			g_free(out_mount_path);
			}
			break;
	case CtSgw_USBUnMount_NUM:{
			        guint32 out_res = -1;
				//guint32 target_res;
				gchar *out_errdesc = NULL;
				//gchar *target_errdesc = NULL;

				gchar target_mount_path[128] = "";
				
				cJSON *in = cJSON_GetObjectItem(testcase,"in");
				//cJSON *target = cJSON_GetObjectItem(testcase,"target");
				strcpy(target_mount_path,cJSON_GetObjectItem(in, "mount_path")->valuestring);
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				return_value = CtSgw_USBUnMount(target_mount_path,&out_res,&out_errdesc);
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;

				if(FALSE == Check_return_result(return_value,atoi(return_target))) 
				{
					 fill_capi_result("CtSgw_USBUnMount","failed",return_value,t_diff); 
					//strcpy(target_errdesc,cJSON_GetObjectItem(target, "errdesc")->valuestring);
					Check_char(out_errdesc,0);
				}
			        else
				{
					 fill_capi_result("CtSgw_USBUnMount","pass",return_value,t_diff);
					//target_res = atoi(cJSON_GetObjectItem(target, "res")->valuestring);
					Check_int(out_res,0);
				}
			g_free(out_errdesc);
			}
			break;

	case CtSgw_USBSetLabel_NUM:{
			         g_print("CtSgw_USBSetLabel=====enter");
				CtSgwObjPath_t path;
				gchar label[128] = "";
				guint32 out_result = -1;
				//guint32 target_result;
				gchar *out_errdesc = NULL;
				//gchar *target_errdesc = NULL;
                                g_print("CtSgw_USBSetLabel=====1");
				cJSON *in = cJSON_GetObjectItem(testcase,"in");
				//cJSON *target = cJSON_GetObjectItem(testcase,"target");
                                  g_print("CtSgw_USBSetLabel=====2");
				strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring);
                                  g_print("CtSgw_USBSetLabel=====3");
				strcpy(label,cJSON_GetObjectItem(in, "label")->valuestring);
                                  g_print("CtSgw_USBSetLabel=====4");
                                g_print("CtSgw_USBSetLabel=====before");

 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
				return_value = CtSgw_USBSetLabel(path,label,&out_result,&out_errdesc);
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;

                                g_print("CtSgw_USBSetLabel=====after");

				if(FALSE == Check_return_result(return_value,atoi(return_target))) 
				{
					 fill_capi_result("CtSgw_USBSetLabel","failed",return_value,t_diff); 
					//strcpy(target_errdesc,cJSON_GetObjectItem(target, "target_errdesc")->valuestring);
					Check_char(out_errdesc,NULL);
				}
			        else
				{
					 fill_capi_result("CtSgw_USBSetLabel","pass",return_value,t_diff);
					//target_result = atoi(cJSON_GetObjectItem(target, "out_result")->valuestring);
					Check_int(out_result,0);
				}
			g_free(out_errdesc);
			}
			break;

	case CtSgw_GetUSBDeviceObjs_NUM:{
			         
				CtSgwUSBDeviceInfo_t* out_param1 = NULL;
				CtSgwUSBDeviceInfo_t target_param1;
				int out_count;
				int target_count;

				
				cJSON *target = cJSON_GetObjectItem(testcase,"target");

 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				return_value = CtSgw_GetUSBDeviceObjs(&out_param1,&out_count);
			        if(FALSE == Check_return_result(return_value,atoi(return_target)))
			        {	
					fill_capi_result("CtSgw_GetUSBDeviceObjs","failed",return_value,t_diff);
					g_free(out_param1);
					break;
			        }
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;


				cJSON * CtSgwUSBDeviceInfo = cJSON_GetObjectItem(target, "CtSgwUSBDeviceInfo_t");
				//cJSON * device = cJSON_GetObjectItem(CtSgwUSBDeviceInfo, "device");
				//cJSON * fsinfo = cJSON_GetObjectItem(CtSgwUSBDeviceInfo, "fsinfo");

				target_count=atoi(cJSON_GetObjectItem(target, "count")->valuestring);
				Check_int(out_count,target_count);
			        if(out_count > target_count)
			        {
				     out_count = target_count;
			        }
			        else if(out_count == 0)
			        {
				     fill_capi_result("CtSgw_GetUSBDeviceObjs","pass",return_value,t_diff);
				     g_free(out_param1);
				     break;
			        }
				int index=0;
				for (index = 0; index < out_count; index++)
				{
					target_param1.device.DeviceType=atoi(cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwUSBDeviceInfo, index), "device"),"DeviceType")->valuestring); 
					target_param1.device.DeviceId=atoi(cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwUSBDeviceInfo, index), "device"),"DeviceId")->valuestring);
					strcpy(target_param1.device.DeviceName,cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwUSBDeviceInfo, index), "device"),"DeviceName")->valuestring); 
					
					strcpy(target_param1.fsinfo.MountPoint,cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwUSBDeviceInfo, index), "fsinfo"),"MountPoint")->valuestring); 
					target_param1.fsinfo.TotalSize=atoi(cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwUSBDeviceInfo, index), "fsinfo"),"TotalSize")->valuestring); 
					target_param1.fsinfo.UsedSize=atoi(cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwUSBDeviceInfo, index), "fsinfo"),"UsedSize")->valuestring); 
					target_param1.fsinfo.FreeSize=atoi(cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwUSBDeviceInfo, index), "fsinfo"),"FreeSize")->valuestring); 
					strcpy(target_param1.fsinfo.Label,cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwUSBDeviceInfo, index), "fsinfo"),"Label")->valuestring);

					if(FALSE == CheckCtSgwUSBDeviceInfo_t(&(out_param1[index]),&target_param1))
						 fill_capi_result("CtSgw_GetUSBDeviceObjs","failed",return_value,t_diff);
			        	else
						 fill_capi_result("CtSgw_GetUSBDeviceObjs","pass",return_value,t_diff);  
				}
					g_free(out_param1);
			}
			break;
	case CtSgw_GetUSBDevice_NUM:{
			         
				CtSgwUSBDeviceInfo_t out_param1;
				CtSgwUSBDeviceInfo_t target_param1;
				CtSgwObjPath_t path;

				cJSON *target = cJSON_GetObjectItem(testcase,"target");
				cJSON *CtSgwUSBDeviceInfo_t = cJSON_GetObjectItem(target,"CtSgwUSBDeviceInfo_t");
				cJSON *in = cJSON_GetObjectItem(testcase,"in");
				cJSON *fsinfo = cJSON_GetObjectItem(CtSgwUSBDeviceInfo_t,"fsinfo");
				cJSON *device = cJSON_GetObjectItem(CtSgwUSBDeviceInfo_t,"device");

				strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring);
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				return_value = CtSgw_GetUSBDevice(path,&out_param1);      

			        if(FALSE == Check_return_result(return_value,atoi(return_target)))
			        {	
					fill_capi_result("CtSgw_GetUSBDevice","failed",return_value,t_diff);
					break;
			        }
                        gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;

				strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgwUSBDeviceInfo_t, "path"),"str")->valuestring);
				target_param1.device.DeviceType=atoi(cJSON_GetObjectItem(device, "DeviceType")->valuestring); 
				target_param1.device.DeviceId=atoi(cJSON_GetObjectItem(device, "DeviceId")->valuestring); 
				strcpy(target_param1.device.DeviceName,cJSON_GetObjectItem(device, "DeviceName")->valuestring); 

				strcpy(target_param1.fsinfo.MountPoint,cJSON_GetObjectItem(fsinfo,"MountPoint")->valuestring); 
				target_param1.fsinfo.TotalSize=atoi(cJSON_GetObjectItem(fsinfo,"TotalSize")->valuestring); 
				target_param1.fsinfo.UsedSize=atoi(cJSON_GetObjectItem(fsinfo,"UsedSize")->valuestring); 
				target_param1.fsinfo.FreeSize=atoi(cJSON_GetObjectItem(fsinfo,"FreeSize")->valuestring); 
				strcpy(target_param1.fsinfo.Label,cJSON_GetObjectItem(fsinfo,"Label")->valuestring); 

				if(FALSE == CheckCtSgwUSBDeviceInfo_t(&out_param1,&target_param1))
					 fill_capi_result("CtSgw_GetUSBDevice","failed",return_value,t_diff);  
			        else
					 fill_capi_result("CtSgw_GetUSBDevice","pass",return_value,t_diff);
			}
			break;
	case CtSgw_NAS_GetFileNum_NUM:{
			         
				gchar foldername[128] = "";
				guint32 out_num = -1;
				//guint32 target_num;
				guint32 out_result = -1;
				//guint32 target_result;
				gchar *out_errdesc = NULL;
				//gchar *target_errdesc = NULL;
				
				//cJSON *target = cJSON_GetObjectItem(testcase,"target");
				cJSON *in = cJSON_GetObjectItem(testcase,"in");
				strcpy(foldername,cJSON_GetObjectItem(in, "foldername")->valuestring); 

 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
				return_value = CtSgw_NAS_GetFileNum(foldername,&out_num,&out_result,&out_errdesc);
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
       
				if(FALSE == Check_return_result(return_value,atoi(return_target))) 
				{				
					fill_capi_result("CtSgw_NAS_GetFileNum","failed",return_value,t_diff); 
					//strcpy(target_errdesc,cJSON_GetObjectItem(target, "errdesc")->valuestring);
					Check_char(out_errdesc,NULL);
				}
			        else
				{
					fill_capi_result("CtSgw_NAS_GetFileNum","pass",return_value,t_diff);
					//target_num=atoi(cJSON_GetObjectItem(target, "num")->valuestring);
					Check_int(out_num,0);
					//target_result=atoi(cJSON_GetObjectItem(target, "result")->valuestring);
					Check_int(out_result,0);
				}
			g_free(out_errdesc);
			}
			break;
	case CtSgw_NAS_ListFolder_NUM:{
			         
				char foldername[128] = "";
				guint32 startIndex;
				guint32 endIndex;
				guint32 out_result = -1;
				//guint32 target_result;
				gchar *out_errdesc = NULL;
				//gchar *target_errdesc = NULL;

				CtSgw_FileEntry_t *out_fileList = NULL;
				//CtSgw_FileEntry_t *target_fileList = NULL;

				cJSON *in = cJSON_GetObjectItem(testcase,"in");
				//cJSON *target = cJSON_GetObjectItem(testcase,"target");


				startIndex=atoi(cJSON_GetObjectItem(in, "startIndex")->valuestring); 
				endIndex=atoi(cJSON_GetObjectItem(in, "endIndex")->valuestring); 
				strcpy(foldername,cJSON_GetObjectItem(in, "foldername")->valuestring); 		  
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

			return_value = CtSgw_NAS_ListFolder(foldername,startIndex,endIndex,&out_fileList,&out_result,&out_errdesc);

			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;

				if(FALSE == Check_return_result(return_value,atoi(return_target)))
			        {	
					 fill_capi_result("CtSgw_NAS_ListFolder","failed",return_value,t_diff);
					 //strcpy(target_errdesc,cJSON_GetObjectItem(target, "errdesc")->valuestring);
					 Check_char(out_errdesc,NULL);
			        } 
				else
				{
					//target_result=atoi(cJSON_GetObjectItem(target, "result")->valuestring);
					Check_int(out_result,0);
					if(FALSE == CheckCtSgw_FileEntry_t(out_fileList, endIndex - startIndex + 1))
					{
						 fill_capi_result("CtSgw_NAS_ListFolder","failed",return_value,t_diff);
					}
			      	 	 else
					{
					 	fill_capi_result("CtSgw_NAS_ListFolder","pass",return_value,t_diff);
					}
				}
			g_free(out_errdesc);
			}
			break;
	case CtSgw_NAS_CreateFolter_NUM:{
				gchar *out_errdesc = NULL;
				//gchar *target_errdesc = NULL;
				gchar foldername[128] = "";
				guint32 out_result = -1;
				//guint32 target_result;
				cJSON *in = cJSON_GetObjectItem(testcase,"in");
				//cJSON *target = cJSON_GetObjectItem(testcase,"target");

				strcpy(foldername,cJSON_GetObjectItem(in, "foldername")->valuestring); 		  

 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
				return_value = CtSgw_NAS_CreateFolter(foldername,&out_result,&out_errdesc);  
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
 

				if(FALSE == Check_return_result(return_value,atoi(return_target))) //wjq
				{				
					 fill_capi_result("CtSgw_NAS_CreateFolter","failed",return_value,t_diff); 
					//strcpy(target_errdesc,cJSON_GetObjectItem(target, "errdesc")->valuestring); 	
					Check_char(out_errdesc,NULL);
				}
			        else
				{
					 fill_capi_result("CtSgw_NAS_CreateFolter","pass",return_value,t_diff);
					//target_result=atoi(cJSON_GetObjectItem(target, "result")->valuestring); 
					Check_int(out_result,0);
				}
			g_free(out_errdesc);
			}
			break;
	case CtSgw_NAS_ReName_NUM:{
			         
				 gchar oldName[128] = "";
				 gchar newName[128] = "";
				gchar *out_errdesc = NULL;
				//gchar *target_errdesc = NULL;
				guint32 out_result = -1;
				//guint32 target_result;

				 cJSON *in = cJSON_GetObjectItem(testcase,"in");
				 //cJSON *target = cJSON_GetObjectItem(testcase,"target");

				 strcpy(oldName,cJSON_GetObjectItem(in, "oldName")->valuestring); 
				 strcpy(newName,cJSON_GetObjectItem(in, "newName")->valuestring); 		  
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				 return_value = CtSgw_NAS_ReName(oldName,newName,&out_result,&out_errdesc);  
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start; 

				 if(FALSE == Check_return_result(return_value,atoi(return_target))) 
				 {
					 fill_capi_result("CtSgw_NAS_ReName","failed",return_value,t_diff); 
					//strcpy(target_errdesc,cJSON_GetObjectItem(target, "errdesc")->valuestring); 
					Check_char(out_errdesc,NULL);
				 }
			         else
				{
					 fill_capi_result("CtSgw_NAS_ReName","pass",return_value,t_diff);
					//target_result=atoi(cJSON_GetObjectItem(target, "result")->valuestring); 
					Check_int(out_result,0);
				}
			 g_free(out_errdesc);
			 }
			 break;
	case CtSgw_NAS_Remove_NUM:{
			          
				gchar name[128] = "";
				gchar *out_errdesc = NULL;
				//gchar *target_errdesc = NULL;
				guint32 out_result = -1;
				//guint32 target_result;

				 cJSON *in =cJSON_GetObjectItem(testcase,"in");
				 //cJSON *target =cJSON_GetObjectItem(testcase,"target");

				 strcpy(name,cJSON_GetObjectItem(in, "name")->valuestring); 
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				 return_value = CtSgw_NAS_Remove(name,&out_result,&out_errdesc); 
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;


				 if(FALSE == Check_return_result(return_value,atoi(return_target))) 
				{
					 fill_capi_result("CtSgw_NAS_Remove","failed",return_value,t_diff); 
					//strcpy(target_errdesc,cJSON_GetObjectItem(target, "errdesc")->valuestring); 	  
					 Check_char(out_errdesc,NULL);
				}
			         else
				{
					 fill_capi_result("CtSgw_NAS_Remove","pass",return_value,t_diff);
					// target_result=atoi(cJSON_GetObjectItem(target, "result")->valuestring); 
					 Check_int(out_result,0);
				}
			 g_free(out_errdesc);
			 }
			 break;
	case CtSgw_NAS_Move_NUM:{
			          
				 gchar filename[128] = "";
				 char destFolderName[128] = "";
				gchar *out_errdesc = NULL;
				//gchar *target_errdesc = NULL;
				guint32 out_result = -1;
				//guint32 target_result;

				 cJSON *in = cJSON_GetObjectItem(testcase,"in");
 				 //cJSON *target =cJSON_GetObjectItem(testcase,"target");

				 strcpy(filename,cJSON_GetObjectItem(in, "filename")->valuestring); 
				 strcpy(destFolderName,cJSON_GetObjectItem(in, "destFolderName")->valuestring);
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				 return_value = CtSgw_NAS_Move(filename,destFolderName,&out_result,&out_errdesc);   
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;

				if(FALSE == Check_return_result(return_value,atoi(return_target))) 
				{
					 fill_capi_result("CtSgw_NAS_Move","failed",return_value,t_diff); 
					 //strcpy(target_errdesc,cJSON_GetObjectItem(target, "errdesc")->valuestring); 	
					 Check_char(out_errdesc,NULL);
				}
			         else
				{
					 fill_capi_result("CtSgw_NAS_Move","pass",return_value,t_diff);
					 //target_result=atoi(cJSON_GetObjectItem(target, "result")->valuestring); 
					Check_int(out_result,0);
				}
			 g_free(out_errdesc);
			 }
			 break;
	case CtSgw_NAS_Copy_NUM:{
			          
				 gchar name[128];
				 gchar destFolderName[128];
				 int out_transId = -1;
				 //int target_transId;
				gchar *out_errdesc = NULL;
				//gchar *target_errdesc = NULL;
				guint32 out_result = -1;
				//guint32 target_result;

				 cJSON *in = cJSON_GetObjectItem(testcase,"in");
				 cJSON *target = cJSON_GetObjectItem(testcase,"target");

				 strcpy(name,cJSON_GetObjectItem(in, "name")->valuestring); 
				 strcpy(destFolderName,cJSON_GetObjectItem(in, "destFolderName")->valuestring);
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				 return_value = CtSgw_NAS_Copy(name,destFolderName,&out_transId,&out_result,&out_errdesc);  
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
 

				 if(FALSE == Check_return_result(return_value,atoi(return_target))) 
				 {				
					 fill_capi_result("CtSgw_NAS_Copy","failed",return_value,t_diff);
					//strcpy(target_errdesc,cJSON_GetObjectItem(target, "errdesc")->valuestring); 
					Check_char(out_errdesc,NULL); 
				 }
			         else
				 {
					 fill_capi_result("CtSgw_NAS_Copy","pass",return_value,t_diff);
					 //target_transId=atoi(cJSON_GetObjectItem(target, "transId")->valuestring);
					 Check_int(out_transId,0);
					// target_result=atoi(cJSON_GetObjectItem(target, "result")->valuestring); 	
					Check_int(out_result,0);
				 }
			 g_free(out_errdesc);
			 }
			 break;
	case CtSgw_NAS_GetCopyProgress_NUM:{
			          
				 guint32 transactionId;
				 guint32 out_percentage = -1;
				 //guint32 target_percentage;
				gchar *out_errdesc = NULL;
				//gchar *target_errdesc = NULL;
				guint32 out_result = -1;
				//guint32 target_result;

				 cJSON *in = cJSON_GetObjectItem(testcase,"in");
				 //cJSON *target = cJSON_GetObjectItem(testcase,"target");

				 transactionId=atoi(cJSON_GetObjectItem(in, "transactionId")->valuestring); 
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				 return_value = CtSgw_NAS_GetCopyProgress(transactionId,&out_percentage,&out_result,&out_errdesc); 
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
  
				 if(FALSE == Check_return_result(return_value,atoi(return_target))) 
				 {				
					 fill_capi_result("CtSgw_NAS_GetCopyProgress","failed",return_value,t_diff); 
					 //strcpy(target_errdesc,cJSON_GetObjectItem(target, "errdesc")->valuestring); 	
					Check_char(out_errdesc,NULL);
				 }
			         else
				 {
					 fill_capi_result("CtSgw_NAS_GetCopyProgress","pass",return_value,t_diff);
					// target_percentage=atoi(cJSON_GetObjectItem(target, "percentage")->valuestring); 
					 Check_int(out_percentage,0);
					// target_result=atoi(cJSON_GetObjectItem(target, "result")->valuestring); 	              
					Check_int(out_result,0);
				 }
			 g_free(out_errdesc);
			 }
			 break;
	case CtSgwAddVPNConnection_NUM:{
			         CtSgwVPNConn_t obj;
				 cJSON *in = cJSON_GetObjectItem(testcase,"in");
				 cJSON *CtSgwVPNConn = cJSON_GetObjectItem(in,"CtSgwVPNConn_t");

				 strcpy(obj.vpn_type,cJSON_GetObjectItem(CtSgwVPNConn, "vpn_type")->valuestring); 
				 strcpy(obj.tunnel_name,cJSON_GetObjectItem(CtSgwVPNConn, "tunnel_name")->valuestring);
				 strcpy(obj.user_id,cJSON_GetObjectItem(CtSgwVPNConn, "user_id")->valuestring); 
				 strcpy(obj.vpn_mode,cJSON_GetObjectItem(CtSgwVPNConn, "vpn_mode")->valuestring); 
				 strcpy(obj.vpn_priority,cJSON_GetObjectItem(CtSgwVPNConn, "vpn_priority")->valuestring);
				 strcpy(obj.vpn_idletime,cJSON_GetObjectItem(CtSgwVPNConn, "vpn_idletime")->valuestring); 
				 strcpy(obj.account_proxy,cJSON_GetObjectItem(CtSgwVPNConn, "account_proxy")->valuestring); 
				 strcpy(obj.vpn_addr,cJSON_GetObjectItem(CtSgwVPNConn, "vpn_addr")->valuestring);
                                 g_print("CtSgwAddVPNConnection=====0\n");
				 strcpy(obj.vpn_account,cJSON_GetObjectItem(CtSgwVPNConn, "vpn_account")->valuestring); 
				 strcpy(obj.vpn_pwd,cJSON_GetObjectItem(CtSgwVPNConn, "vpn_pwd")->valuestring); 
				 strcpy(obj.vpn_port,cJSON_GetObjectItem(CtSgwVPNConn, "vpn_port")->valuestring);
				 strcpy(obj.attach_mode,cJSON_GetObjectItem(CtSgwVPNConn, "attach_mode")->valuestring); 
                                 g_print("CtSgwAddVPNConnection=====1\n");
				 strcpy(obj.terminal_mac->str,cJSON_GetObjectItem(CtSgwVPNConn, "terminal_mac")->valuestring); 
				 obj.domain_num = atoi(cJSON_GetObjectItem(CtSgwVPNConn, "domain_num")->valuestring); 
				 obj.ip_num = atoi(cJSON_GetObjectItem(CtSgwVPNConn, "ip_num")->valuestring); 
                                 g_print("CtSgwAddVPNConnection=====2\n");

				 obj.domains = (CtSgwStrArray_t*)malloc(2 * sizeof(CtSgwStrArray_t));
				 strcpy(obj.domains->str,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgwVPNConn, "domains"),"str")->valuestring);//wjq
                                 g_print("CtSgwAddVPNConnection=====3\n");
obj.ips = (CtSgwStrArray_t*)malloc(2 * sizeof(CtSgwStrArray_t));
				 strcpy(obj.ips->str,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgwVPNConn, "ips"),"str")->valuestring);
                                 g_print("CtSgwAddVPNConnection=====4\n");
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				 return_value = CtSgwAddVPNConnection(&obj);
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
                                 g_print("CtSgwAddVPNConnection=====5\n");


			         if(FALSE == Check_return_result(return_value,atoi(return_target)))
					 fill_capi_result("CtSgwAddVPNConnection","failed",return_value,t_diff); 
			         else
					 fill_capi_result("CtSgwAddVPNConnection","pass",return_value,t_diff);
			 }
			 break;
	case CtSgwDelVPNConnByName_NUM:{
			          
				 char tunnelName[128] = "";

				 cJSON *in = cJSON_GetObjectItem(testcase,"in");

				 strcpy(tunnelName,cJSON_GetObjectItem(in, "tunnelName")->valuestring); 
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				 return_value = CtSgwDelVPNConnByName(tunnelName);


			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
				 if(FALSE == Check_return_result(return_value,atoi(return_target))) 
					 fill_capi_result("CtSgwDelVPNConnByName","failed",return_value,t_diff); 
			         else
					 fill_capi_result("CtSgwDelVPNConnByName","pass",return_value,t_diff);

			 }
			 break;
	case CtSgwAttachVPNConnection_NUM:{
			          
				 char tunnelName[128] = "";
				 gchar ipAddrList[128] = "";
				 int ipAddrNum;

				 cJSON *in = cJSON_GetObjectItem(testcase,"in");

				 strcpy(tunnelName,cJSON_GetObjectItem(in, "tunnelName")->valuestring); 
				 strcpy(ipAddrList,cJSON_GetObjectItem(in, "ipAddrList")->valuestring); 
				 ipAddrNum=atoi(cJSON_GetObjectItem(in, "ipAddrNum")->valuestring); 
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
 		    
				 return_value = CtSgwAttachVPNConnection(tunnelName, ipAddrList, ipAddrNum);	

			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
	
				 if(FALSE == Check_return_result(return_value,atoi(return_target))) 
					 fill_capi_result("CtSgwAttachVPNConnection","failed",return_value,t_diff); 
			         else
					 fill_capi_result("CtSgwAttachVPNConnection","pass",return_value,t_diff);

			 }
			 break;
	case CtSgwDetachVPNConnection_NUM:{
			          
				 char tunnelName[128] = "";
				 char ipAddrList[128] = "";
				 int ipAddrNum;

				 cJSON *in = cJSON_GetObjectItem(testcase,"in");

				 strcpy(tunnelName,cJSON_GetObjectItem(in, "tunnelName")->valuestring); 
				 strcpy(ipAddrList,cJSON_GetObjectItem(in, "ipAddrList")->valuestring); 
				 ipAddrNum=atoi(cJSON_GetObjectItem(in, "ipAddrNum")->valuestring);  


 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
				 return_value = CtSgwDetachVPNConnection(tunnelName, ipAddrList,ipAddrNum);


			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;

				 if(FALSE == Check_return_result(return_value,atoi(return_target))) 
					 fill_capi_result("CtSgwDetachVPNConnection","failed",return_value,t_diff); 
			         else
					 fill_capi_result("CtSgwDetachVPNConnection","pass",return_value,t_diff);

			 }
			 break;
	case CtSgwGetVPNConnectionStatus_NUM:{
			         CtSgwVPNConnStats_t out_param1;
                                 CtSgwObjPath_t path;
			         CtSgwVPNConnStats_t target_param1;
                                 cJSON *in = cJSON_GetObjectItem(testcase,"in");
                                 strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring);
				 cJSON *target = cJSON_GetObjectItem(testcase,"target");
				 cJSON *CtSgwVPNConnStats = cJSON_GetObjectItem(target,"CtSgwVPNConnStats_t");
	 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
				 gettimeofday(&t_start,0);
				 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				 return_value = CtSgwGetVPNConnectionStatus(path,&out_param1);
			
			         if(FALSE == Check_return_result(return_value,atoi(return_target)))
				{	
					 fill_capi_result("CtSgwGetVPNConnectionStatus","failed",return_value,t_diff); 
					 break;
				}
		                gettimeofday(&t_end,0);
				end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
				t_diff = end - start;

				strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgwVPNConnStats, "path"),"str")->valuestring);
				target_param1.arrayLen = atoi(cJSON_GetObjectItem(CtSgwVPNConnStats, "arrayLen")->valuestring); 
				strcpy(target_param1.data->str,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgwVPNConnStats, "data"),"str")->valuestring);//wjq
				if(FALSE == CheckCtSgwVPNConnStats_t(&out_param1,&target_param1))
					 fill_capi_result("CtSgwGetVPNConnectionStatus","failed",return_value,t_diff);  
			        else
					 fill_capi_result("CtSgwGetVPNConnectionStatus","pass",return_value,t_diff);
					if(out_param1.arrayLen>0)
					{
					g_free(out_param1.data);
					}
			 }
			 break;

	case CtSgwSetDNSServerConfig_NUM:{
			         CtSgwDNSServerConfig_t target_param1;

				 cJSON *in = cJSON_GetObjectItem(testcase,"in");
				 cJSON *CtSgwDNSServerConfig = cJSON_GetObjectItem(in,"CtSgwDNSServerConfig_t");

				 strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgwDNSServerConfig, "path"),"str")->valuestring);
				 strcpy(target_param1.Server1,cJSON_GetObjectItem(CtSgwDNSServerConfig, "Server1")->valuestring); 
				 strcpy(target_param1.Server2,cJSON_GetObjectItem(CtSgwDNSServerConfig, "Server2")->valuestring); 
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				 return_value = CtSgwSetDNSServerConfig(&target_param1);
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
		

			         if(FALSE == Check_return_result(return_value,atoi(return_target)))
					 fill_capi_result("CtSgwSetDNSServerConfig","failed",return_value,t_diff); 
			        else
					 fill_capi_result("CtSgwSetDNSServerConfig","pass",return_value,t_diff);

			 }
			 break;
	case CtSgwGetDNSServerConfig_NUM:{
			         CtSgwDNSServerConfig_t target_param1;
			         CtSgwDNSServerConfig_t out_param1;

				 cJSON *target = cJSON_GetObjectItem(testcase,"target");
				 cJSON *CtSgwDNSServerConfig = cJSON_GetObjectItem(target,"CtSgwDNSServerConfig_t");
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				 return_value = CtSgwGetDNSServerConfig(&out_param1);

			
			         if(FALSE == Check_return_result(return_value,atoi(return_target)))
				 {
					 fill_capi_result("CtSgwSetDNSServerConfig","failed",return_value,t_diff); 
			        	 break;
				 }

                        gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;

				 strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgwDNSServerConfig, "path"),"str")->valuestring);
				 strcpy(target_param1.Server1,cJSON_GetObjectItem(CtSgwDNSServerConfig, "Server1")->valuestring); 
				 strcpy(target_param1.Server2,cJSON_GetObjectItem(CtSgwDNSServerConfig, "Server2")->valuestring); 

				 if(FALSE == CheckCtSgwDNSServerConfig_t(&out_param1,&target_param1))
					 fill_capi_result("CtSgwGetDNSServerConfig","failed",return_value,t_diff);  
			         else
					 fill_capi_result("CtSgwGetDNSServerConfig","pass",return_value,t_diff);
			 }
			 break;

	case CtSgwFlushDNS_NUM:{
				 guint32 out_result = -1;
				// guint32 target_result;
				 gchar *out_errdesc = NULL;
				// gchar *target_errdesc = NULL;

				 //cJSON *target = cJSON_GetObjectItem(testcase,"target");		    


 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
				 return_value = CtSgwFlushDNS(&out_result,&out_errdesc);
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;

				 if(FALSE == Check_return_result(return_value,atoi(return_target))) 
				 {
					 fill_capi_result("CtSgwFlushDNS","failed",return_value,t_diff);
					 //strcpy(target_errdesc,cJSON_GetObjectItem(target, "errdesc")->valuestring); 
					 Check_char(out_errdesc,NULL);
				 } 
			         else
				 {
					 fill_capi_result("CtSgwFlushDNS","pass",return_value,t_diff); 
					 //target_result = atoi(cJSON_GetObjectItem(target, "result")->valuestring); 
				 	 Check_int(out_result,0);
				 }
			 g_free(out_errdesc);
			 }
			 break;

	case CtSgwGetDDNSServerObjs_NUM:{
			         
				CtSgwDDNServer_t* out_param1 = NULL;
				CtSgwDDNServer_t target_param1;
				int out_count;
				int target_count;
				
				cJSON *target = cJSON_GetObjectItem(testcase,"target");

 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
				return_value = CtSgwGetDDNSServerObjs(&out_param1,&out_count);
			


			        if(FALSE == Check_return_result(return_value,atoi(return_target)))
			        {	
					fill_capi_result("CtSgwGetDDNSServerObjs","failed",return_value,t_diff);
					g_free(out_param1);
					break;
			        }
                        gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;


				cJSON * CtSgwDDNServer = cJSON_GetObjectItem(target, "CtSgwDDNServer_t");
			
				target_count=atoi(cJSON_GetObjectItem(target, "count")->valuestring);
				Check_int(out_count,target_count);
			        if(out_count > target_count)
			        {
				     out_count = target_count;
			        }
			        else if(out_count == 0)
			        {
				     fill_capi_result("CtSgwGetDDNSServerObjs","pass",return_value,t_diff);
				     g_free(out_param1);
				     break;
			        }
				int index=0;
				for (index = 0; index < out_count; index++)
				{
				   strcpy(target_param1.DDNSProvider,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwDDNServer, index), "DDNSProvider")->valuestring);  
				   strcpy(target_param1.DDNSUsername,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwDDNServer, index), "DDNSUsername")->valuestring);   
				   strcpy(target_param1.DDNSPassword,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwDDNServer, index), "DDNSPassword")->valuestring);   
				   strcpy(target_param1.DDNSDomainName,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwDDNServer, index), "DDNSDomainName")->valuestring);  
				   strcpy(target_param1.DDNSHostName,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwDDNServer, index), "DDNSHostName")->valuestring); 
				   target_param1.DDNSCfgEnabled=atoi(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwDDNServer, index), "DDNSCfgEnabled")->valuestring);   
				   target_param1.ServicePort=atoi(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwDDNServer, index), "ServicePort")->valuestring);  
					if(FALSE == CheckCtSgwDDNServer_t(&(out_param1[index]),&target_param1))
						 fill_capi_result("CtSgwGetDDNSServerObjs","failed",return_value,t_diff);
			        	else
						 fill_capi_result("CtSgwGetDDNSServerObjs","pass",return_value,t_diff);  
				}
		        g_free(out_param1);
			}
			break;

	case CtSgwGetDDNSServerInstance_NUM:{
			    
			   CtSgwDDNServer_t out_param1;
			   CtSgwDDNServer_t target_param1;
			   CtSgwObjPath_t path;
			   cJSON *target = cJSON_GetObjectItem(testcase,"target");
			   cJSON *CtSgwDDNServer = cJSON_GetObjectItem(target,"CtSgwDDNServer_t");
			   cJSON *in = cJSON_GetObjectItem(testcase,"in");
			   strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring); 
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

			   return_value = CtSgwGetDDNSServerInstance(path,&out_param1);  


     
			   if(FALSE == Check_return_result(return_value,atoi(return_target)))
			   {	
				 fill_capi_result("CtSgwGetDDNSServerInstance","failed",return_value,t_diff);
				break;
			   }
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;


			   strcpy(target_param1.DDNSProvider,cJSON_GetObjectItem(CtSgwDDNServer, "DDNSProvider")->valuestring);  
			   strcpy(target_param1.DDNSUsername,cJSON_GetObjectItem(CtSgwDDNServer, "DDNSUsername")->valuestring);   
			   strcpy(target_param1.DDNSPassword,cJSON_GetObjectItem(CtSgwDDNServer, "DDNSPassword")->valuestring);   
			   strcpy(target_param1.DDNSDomainName,cJSON_GetObjectItem(CtSgwDDNServer, "DDNSDomainName")->valuestring);  
			   target_param1.DDNSCfgEnabled=atoi(cJSON_GetObjectItem(CtSgwDDNServer, "DDNSCfgEnabled")->valuestring);   
			   target_param1.ServicePort=atoi(cJSON_GetObjectItem(CtSgwDDNServer, "ServicePort")->valuestring);  
			   strcpy(target_param1.DDNSHostName,cJSON_GetObjectItem(CtSgwDDNServer, "DDNSHostName")->valuestring);  

			   if (FALSE == CheckCtSgwDDNServer_t(&out_param1,&target_param1))
				 fill_capi_result("CtSgwGetDDNSServerInstance","failed",return_value,t_diff);
			   else
				 fill_capi_result("CtSgwGetDDNSServerInstance","pass",return_value,t_diff);
		   }
		   break;

	case CtSgwSetDDNSServerInstance_NUM:{
			    
			   CtSgwDDNServer_t target_param1;
			   CtSgwObjPath_t path;
			   cJSON *in = cJSON_GetObjectItem(testcase,"in");
			   cJSON *CtSgwDDNServer = cJSON_GetObjectItem(in,"CtSgwDDNServer_t");

			   strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring); 

			   strcpy(target_param1.DDNSProvider,cJSON_GetObjectItem(CtSgwDDNServer, "DDNSProvider")->valuestring);  
			   strcpy(target_param1.DDNSUsername,cJSON_GetObjectItem(CtSgwDDNServer, "DDNSUsername")->valuestring);   
			   strcpy(target_param1.DDNSPassword,cJSON_GetObjectItem(CtSgwDDNServer, "DDNSPassword")->valuestring);   
			   strcpy(target_param1.DDNSDomainName,cJSON_GetObjectItem(CtSgwDDNServer, "DDNSDomainName")->valuestring);  
			   target_param1.DDNSCfgEnabled=atoi(cJSON_GetObjectItem(CtSgwDDNServer, "DDNSCfgEnabled")->valuestring);   
			   target_param1.ServicePort=atoi(cJSON_GetObjectItem(CtSgwDDNServer, "ServicePort")->valuestring);  
			   strcpy(target_param1.DDNSHostName,cJSON_GetObjectItem(CtSgwDDNServer, "DDNSHostName")->valuestring);
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
  
			   return_value = CtSgwSetDDNSServerInstance(path,&target_param1);  

			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;

     
			   if(FALSE == Check_return_result(return_value,atoi(return_target)))
				 fill_capi_result("CtSgwSetDDNSServerInstance","failed",return_value,t_diff);
			   else
				 fill_capi_result("CtSgwSetDDNSServerInstance","pass",return_value,t_diff);

		   }
		   break;

	case CtSgwAddDDNSServerInstance_NUM:{
			    
			   CtSgwDDNServer_t target_param1;
			  
			   cJSON *in = cJSON_GetObjectItem(testcase,"in");
			   cJSON *CtSgwDDNServer = cJSON_GetObjectItem(in,"CtSgwDDNServer_t");

			   strcpy(target_param1.DDNSProvider,cJSON_GetObjectItem(CtSgwDDNServer, "DDNSProvider")->valuestring);  
			   strcpy(target_param1.DDNSUsername,cJSON_GetObjectItem(CtSgwDDNServer, "DDNSUsername")->valuestring);   
			   strcpy(target_param1.DDNSPassword,cJSON_GetObjectItem(CtSgwDDNServer, "DDNSPassword")->valuestring);   
			   strcpy(target_param1.DDNSDomainName,cJSON_GetObjectItem(CtSgwDDNServer, "DDNSDomainName")->valuestring);  
			   target_param1.DDNSCfgEnabled=atoi(cJSON_GetObjectItem(CtSgwDDNServer, "DDNSCfgEnabled")->valuestring);   
			   target_param1.ServicePort=atoi(cJSON_GetObjectItem(CtSgwDDNServer, "ServicePort")->valuestring);  
			   strcpy(target_param1.DDNSHostName,cJSON_GetObjectItem(CtSgwDDNServer, "DDNSHostName")->valuestring);  
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

			   return_value = CtSgwAddDDNSServerInstance(&target_param1); 
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
      
			   if(FALSE == Check_return_result(return_value,atoi(return_target)))
				 fill_capi_result("CtSgwAddDDNSServerInstance","failed",return_value,t_diff);
			   else
				 fill_capi_result("CtSgwAddDDNSServerInstance","pass",return_value,t_diff);

		   }
		   break;

	case CtSgwDelDDNSServerInstance_NUM:{
			         
				CtSgwObjPath_t path;

				cJSON *in = cJSON_GetObjectItem(testcase,"in");
				strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring); 
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				return_value = CtSgwDelDDNSServerInstance(path);    
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
   
				if(FALSE == Check_return_result(return_value,atoi(return_target))) 
					 fill_capi_result("CtSgwDelDDNSServerInstance","failed",return_value,t_diff); 
			        else
					 fill_capi_result("CtSgwDelDDNSServerInstance","pass",return_value,t_diff); 
			}
			break;

	case CtSgw_SetFtpServer_NUM:{
			          
				 CtSgw_FTPServerConfig_t target_param1;
				 cJSON *in = cJSON_GetObjectItem(testcase,"in");
				 cJSON *CtSgw_FTPServerConfig = cJSON_GetObjectItem(in,"CtSgw_FTPServerConfig_t");
			       	 strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgw_FTPServerConfig, "path"),"str")->valuestring);
				 target_param1.Enable=atoi(cJSON_GetObjectItem(CtSgw_FTPServerConfig, "Enable")->valuestring); 
				 target_param1.AllowAnonymous=atoi(cJSON_GetObjectItem(CtSgw_FTPServerConfig, "AllowAnonymous")->valuestring); 

 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				 return_value = CtSgw_SetFtpServer(&target_param1);   
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
    
				 if(FALSE == Check_return_result(return_value,atoi(return_target))) 
					 fill_capi_result("CtSgw_SetFtpServer","failed",return_value,t_diff); 
			         else
					 fill_capi_result("CtSgw_SetFtpServer","pass",return_value,t_diff);

			 }
			 break;
	case CtSgw_GetFTPServer_NUM:{
			          
				 CtSgw_FTPServerConfig_t out_param1;
				 CtSgw_FTPServerConfig_t target_param1;
				 cJSON *target = cJSON_GetObjectItem(testcase,"target");
				 cJSON *CtSgw_FTPServerConfig = cJSON_GetObjectItem(target,"CtSgw_FTPServerConfig_t");
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				 return_value = CtSgw_GetFTPServer(&out_param1);       
				 if(FALSE == Check_return_result(return_value,atoi(return_target)))
				 {					
					 fill_capi_result("CtSgw_GetFTPServer","failed",return_value,t_diff); 
					break;
				 }

			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
		

				 target_param1.Enable=atoi(cJSON_GetObjectItem(CtSgw_FTPServerConfig, "Enable")->valuestring); 
				 target_param1.AllowAnonymous=atoi(cJSON_GetObjectItem(CtSgw_FTPServerConfig, "AllowAnonymous")->valuestring); 
			       	 strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgw_FTPServerConfig, "path"),"str")->valuestring);
				 if(FALSE == CheckCtSgw_FTPServerConfig_t(&out_param1,&target_param1))
					 fill_capi_result("CtSgw_GetFTPServer","failed",return_value,t_diff);   
			         else
					 fill_capi_result("CtSgw_GetFTPServer","pass",return_value,t_diff);
			 }
			 break;
	case CtSgw_GetFTPAccountObjs_NUM:{
			          
				 CtSgw_FTPAccount_t* out_param1 = NULL;
				 CtSgw_FTPAccount_t target_param1;
				 int out_count;
				 int target_count;
				 cJSON *target = cJSON_GetObjectItem(testcase,"target");
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				 return_value = CtSgw_GetFTPAccountObjs(&out_param1,&out_count);       
				 if(FALSE == Check_return_result(return_value,atoi(return_target)))
				 {					
					 fill_capi_result("CtSgw_GetFTPAccountObjs","failed",return_value,t_diff); 
				         g_free(out_param1);
					 break;
				 } 
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;

				 cJSON * CtSgw_FTPAccount = cJSON_GetObjectItem(target, "CtSgw_FTPAccount_t");

				 target_count=atoi(cJSON_GetObjectItem(target, "count")->valuestring);
				 Check_int(out_count,target_count);
				 if(out_count > target_count)
				 {
					out_count = target_count;
				 }
			        else if(out_count == 0)
			        {
				     fill_capi_result("CtSgw_GetFTPAccountObjs","pass",return_value,t_diff);
				     g_free(out_param1);
				     break;
			        }
				 int index=0;
				 for (index = 0; index < out_count; index++)
				 {
				   	 strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgw_FTPAccount, index), "path"),"str")->valuestring);
					 strcpy(target_param1.UserName,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgw_FTPAccount, index), "UserName")->valuestring); 
					 strcpy(target_param1.Password,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgw_FTPAccount, index), "Password")->valuestring); 
					 if(FALSE == CheckCtSgw_FTPAccount_t(&(out_param1[index]),&target_param1))
						 fill_capi_result("CtSgw_GetFTPAccountObjs","failed",return_value,t_diff);
			        	 else
						 fill_capi_result("CtSgw_GetFTPAccountObjs","pass",return_value,t_diff);   
				 }
			 g_free(out_param1);
			 }
			 break;
	case CtSgw_GetFTPAccount_NUM:{
			          
				 CtSgw_FTPAccount_t out_param1;
				 CtSgw_FTPAccount_t target_param1;
				 CtSgwObjPath_t path;
				 cJSON *target = cJSON_GetObjectItem(testcase,"target");
				 cJSON *CtSgw_FTPAccount = cJSON_GetObjectItem(target,"CtSgw_FTPAccount_t");

				 cJSON *in = cJSON_GetObjectItem(testcase,"in");
				 strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring); 
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				 return_value = CtSgw_GetFTPAccount(path,&out_param1);
				 if(FALSE == Check_return_result(return_value,atoi(return_target)))
				 {					
					 fill_capi_result("CtSgw_GetFTPAccount","failed",return_value,t_diff); 
					break;
				 }
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;


				 strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgw_FTPAccount, "path"),"str")->valuestring);
				 strcpy(target_param1.UserName,cJSON_GetObjectItem(CtSgw_FTPAccount, "UserName")->valuestring); 

				 strcpy(target_param1.Password,cJSON_GetObjectItem(CtSgw_FTPAccount, "Password")->valuestring); 

				 if(FALSE == CheckCtSgw_FTPAccount_t(&out_param1,&target_param1))
					 fill_capi_result("CtSgw_GetFTPAccount","failed",return_value,t_diff);  
			         else
					 fill_capi_result("CtSgw_GetFTPAccount","pass",return_value,t_diff);
			 }
			 break;
	case CtSgw_AddFtpAccount_NUM:{
			          
				 CtSgw_FTPAccount_t target_param1;

				 cJSON *in = cJSON_GetObjectItem(testcase,"in");
				 cJSON *CtSgw_FTPAccount = cJSON_GetObjectItem(in,"CtSgw_FTPAccount_t");
				 strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgw_FTPAccount, "path"),"str")->valuestring);
				 strcpy(target_param1.UserName,cJSON_GetObjectItem(CtSgw_FTPAccount, "UserName")->valuestring); 
				 strcpy(target_param1.Password,cJSON_GetObjectItem(CtSgw_FTPAccount, "Password")->valuestring); 
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				 return_value = CtSgw_AddFtpAccount(&target_param1); 
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
      
				 if(FALSE == Check_return_result(return_value,atoi(return_target))) 
					 fill_capi_result("CtSgw_AddFtpAccount","failed",return_value,t_diff); 
			         else
					 fill_capi_result("CtSgw_AddFtpAccount","pass",return_value,t_diff);

			 }
			 break;
	case CtSgw_DelFtpAccount_NUM:{
			          
				 CtSgwObjPath_t path;

				 cJSON *in = cJSON_GetObjectItem(testcase,"in");
				 strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring);
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
 
				 return_value = CtSgw_DelFtpAccount(path);
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;

				 if(FALSE == Check_return_result(return_value,atoi(return_target))) 
					 fill_capi_result("CtSgw_DelFtpAccount","failed",return_value,t_diff ); 
			         else
					 fill_capi_result("CtSgw_DelFtpAccount","pass",return_value,t_diff );
			 }
			 break;
	case CtSgw_GetSambaServer_NUM:{

				 CtSgw_SambaServerConfig_t out_param1;
				 CtSgw_SambaServerConfig_t target_param1;
				 cJSON *target = cJSON_GetObjectItem(testcase,"target");
				 cJSON *CtSgw_SambaServerConfig = cJSON_GetObjectItem(target,"CtSgw_SambaServerConfig_t");
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				 return_value = CtSgw_GetSambaServer(&out_param1);       
				 if(FALSE == Check_return_result(return_value,atoi(return_target)))
				 {					
					 fill_capi_result("CtSgw_GetSambaServer","failed",return_value,t_diff); 
					break;
				 }
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;

				 strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgw_SambaServerConfig, "path"),"str")->valuestring);
				 target_param1.Enable=atoi(cJSON_GetObjectItem(CtSgw_SambaServerConfig, "Enable")->valuestring); 
				 target_param1.AllowAnonymous=atoi(cJSON_GetObjectItem(CtSgw_SambaServerConfig, "AllowAnonymous")->valuestring); 

				 if(FALSE == CheckCtSgw_SambaServerConfig_t(&out_param1,&target_param1))
					 fill_capi_result("CtSgw_GetSambaServer","failed",return_value,t_diff);   
			         else
					 fill_capi_result("CtSgw_GetSambaServer","pass",return_value,t_diff);
			 }
			 break;
	case CtSgw_SetSambaServer_NUM:{
			          
				 CtSgw_SambaServerConfig_t target_param1;
				 cJSON *in = cJSON_GetObjectItem(testcase,"in");
				 cJSON *CtSgw_SambaServerConfig = cJSON_GetObjectItem(in,"CtSgw_SambaServerConfig_t");

				 target_param1.Enable=atoi(cJSON_GetObjectItem(CtSgw_SambaServerConfig, "Enable")->valuestring); 
				 target_param1.AllowAnonymous=atoi(cJSON_GetObjectItem(CtSgw_SambaServerConfig, "AllowAnonymous")->valuestring); 
				 strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgw_SambaServerConfig, "path"),"str")->valuestring);
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				 return_value = CtSgw_SetSambaServer(&target_param1); 
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
      
				 if(FALSE == Check_return_result(return_value,atoi(return_target))) 
					 fill_capi_result("CtSgw_SetSambaServer","failed",return_value,t_diff); 
			         else
					 fill_capi_result("CtSgw_SetSambaServer","pass",return_value,t_diff);
			 }
			 break;
	case CtSgw_GetSambaAccountObjs_NUM:{
			          
				 CtSgw_SambaAccount_t* out_param1 = NULL;
				 CtSgw_SambaAccount_t target_param1;
				 int out_count;
				 int target_count;
				 cJSON *target = cJSON_GetObjectItem(testcase,"target");
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				 return_value = CtSgw_GetSambaAccountObjs(&out_param1, &out_count);     
			
				 if(FALSE == Check_return_result(return_value,atoi(return_target)))
				 {					
					fill_capi_result("CtSgw_GetSambaAccountObjs","failed",return_value,t_diff);
				        g_free(out_param1); 
					break;
				 }

                        gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
  

				 cJSON * CtSgw_SambaAccount = cJSON_GetObjectItem(target, "CtSgw_SambaAccount_t");

				 target_count=atoi(cJSON_GetObjectItem(target, "count")->valuestring);
				 Check_int(out_count,target_count);
				 if(out_count > target_count)
				 {
					out_count = target_count;
				 }
			        else if(out_count == 0)
			        {
				     fill_capi_result("CtSgw_GetSambaAccountObjs","pass",return_value,t_diff);
				     g_free(out_param1);
				     break;
			        }
				 int index=0;
				 for (index = 0; index < out_count; index++)
				 {
				   	 strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgw_SambaAccount, index), "path"),"str")->valuestring);
					 strcpy(target_param1.UserName,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgw_SambaAccount, index), "UserName")->valuestring); 
					 strcpy(target_param1.Password,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgw_SambaAccount, index), "Password")->valuestring); 
					 if(FALSE == CheckCtSgw_SambaAccount_t(&(out_param1[index]),&target_param1))
						 fill_capi_result("CtSgw_GetSambaAccountObjs","failed",return_value,t_diff);
			        	 else
						 fill_capi_result("CtSgw_GetSambaAccountObjs","pass",return_value,t_diff);  
				 }
			 g_free(out_param1);
			 }
			 break;
	case CtSgw_GetSambaAccount_NUM:{
			          
				 CtSgw_SambaAccount_t out_param1;
				 CtSgw_SambaAccount_t target_param1;
				 CtSgwObjPath_t path;
				 cJSON *target = cJSON_GetObjectItem(testcase,"target");
				 cJSON *CtSgw_SambaAccount = cJSON_GetObjectItem(target,"CtSgw_SambaAccount_t");
				 cJSON *in = cJSON_GetObjectItem(testcase,"in");
				 strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring);                         
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				 return_value = CtSgw_GetSambaAccount(path,&out_param1);

		                 if(FALSE == Check_return_result(return_value,atoi(return_target)))
				 {					
					 fill_capi_result("CtSgw_GetSambaAccount","failed",return_value,t_diff); 
					break;
				 }
                        gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
 

				 strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgw_SambaAccount, "path"),"str")->valuestring);
				 strcpy(target_param1.UserName,cJSON_GetObjectItem(CtSgw_SambaAccount, "UserName")->valuestring); 
				 strcpy(target_param1.Password,cJSON_GetObjectItem(CtSgw_SambaAccount, "Password")->valuestring); 

				 if(FALSE == CheckCtSgw_SambaAccount_t(&out_param1,&target_param1))
					 fill_capi_result("CtSgw_GetSambaAccount","failed",return_value,t_diff);   
			         else
					 fill_capi_result("CtSgw_GetSambaAccount","pass",return_value,t_diff);
			 }
			 break;
	case CtSgw_AddSambaAccount_NUM:{
			          
				 CtSgw_SambaAccount_t target_param1;

				 cJSON *in = cJSON_GetObjectItem(testcase,"in");
				 cJSON *CtSgw_SambaAccount = cJSON_GetObjectItem(in,"CtSgw_SambaAccount_t");
				 strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgw_SambaAccount, "path"),"str")->valuestring);
				 strcpy(target_param1.UserName,cJSON_GetObjectItem(CtSgw_SambaAccount, "UserName")->valuestring); 
				 strcpy(target_param1.Password,cJSON_GetObjectItem(CtSgw_SambaAccount, "Password")->valuestring); 
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				 return_value = CtSgw_AddSambaAccount(&target_param1); 

			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;

				 if(FALSE == Check_return_result(return_value,atoi(return_target))) 
					 fill_capi_result("CtSgw_AddSambaAccount","failed",return_value,t_diff); 
			         else
					 fill_capi_result("CtSgw_AddSambaAccount","pass",return_value,t_diff);
			 }
			 break;
	case CtSgw_DelSambaAccount_NUM:{
			          
				 CtSgwObjPath_t path;

				 cJSON *in = cJSON_GetObjectItem(testcase,"in");
				 strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring);

  			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
				 return_value = CtSgw_DelSambaAccount(path);   
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;

				 if(FALSE == Check_return_result(return_value,atoi(return_target))) 
					 fill_capi_result("CtSgw_DelSambaAccount","failed",return_value,t_diff); 
			         else
					 fill_capi_result("CtSgw_DelSambaAccount","pass",return_value,t_diff);
			 }
			 break;

	case CtSgw_GetHttpServer_NUM:{
			          
				 CtSgw_HttpServerConfig_t out_param1;
				 CtSgw_HttpServerConfig_t target_param1;
				 cJSON *target = cJSON_GetObjectItem(testcase,"target");
				 cJSON *CtSgw_HttpServerConfig = cJSON_GetObjectItem(target,"CtSgw_HttpServerConfig_t");
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				 return_value = CtSgw_GetHttpServer(&out_param1);      
				 if(FALSE == Check_return_result(return_value,atoi(return_target)))
				 {					
					 fill_capi_result("CtSgw_GetHttpServer","failed",return_value,t_diff); 
					break;
				 }
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;

				 target_param1.Enable=atoi(cJSON_GetObjectItem(CtSgw_HttpServerConfig, "Enable")->valuestring); 
				 strcpy(target_param1.AdminPassword,cJSON_GetObjectItem(CtSgw_HttpServerConfig, "AdminPassword")->valuestring); 
				 strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgw_HttpServerConfig, "path"),"str")->valuestring);
				 if(FALSE == CheckCtSgw_HttpServerConfig_t(&out_param1,&target_param1))
					 fill_capi_result("CtSgw_GetHttpServer","failed",return_value,t_diff);   
			         else
					 fill_capi_result("CtSgw_GetHttpServer","pass",return_value,t_diff);
			 }
			 break;
	case CtSgw_SetHttpServer_NUM:{
			          
				 CtSgw_HttpServerConfig_t target_param1;
				 cJSON *in = cJSON_GetObjectItem(testcase,"in");
				 cJSON *CtSgw_HttpServerConfig = cJSON_GetObjectItem(in,"CtSgw_HttpServerConfig_t");

				 target_param1.Enable=atoi(cJSON_GetObjectItem(CtSgw_HttpServerConfig, "Enable")->valuestring); 
				 strcpy(target_param1.AdminPassword,cJSON_GetObjectItem(CtSgw_HttpServerConfig, "AdminPassword")->valuestring); 
				 strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(CtSgw_HttpServerConfig, "path"),"str")->valuestring);
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				 return_value = CtSgw_SetHttpServer(&target_param1);   
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
    
				 if(FALSE == Check_return_result(return_value,atoi(return_target))) 
					 fill_capi_result("CtSgw_SetHttpServer","failed",return_value,t_diff); 
			         else
					 fill_capi_result("CtSgw_SetHttpServer","pass",return_value,t_diff);
			 }
			 break;
	case CtSgwSysCmdSetLOID_NUM:{
			         
				guint32  out_result = -1;
				//guint32  target_result;
				char loid[MAX_LOID_LEN+1] = "";
				char password[MAX_PASSWORD_LEN+1] = "";
				gchar *out_errdesc = NULL;
				//gchar *target_errdesc = NULL;

				cJSON *in = cJSON_GetObjectItem(testcase,"in");
				//cJSON *target = cJSON_GetObjectItem(testcase,"target");

				strcpy(loid,cJSON_GetObjectItem(in,"loid")->valuestring);  
				strcpy(password,cJSON_GetObjectItem(in,"password")->valuestring);    

 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				return_value = CtSgwSysCmdSetLOID(loid,password,&out_result,&out_errdesc);  

     			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
				if(FALSE == Check_return_result(return_value,atoi(return_target))) 
				{				
					 fill_capi_result("CtSgwSysCmdSetLOID","failed",return_value,t_diff); 
					// strcpy(target_errdesc,cJSON_GetObjectItem(target,"errdesc")->valuestring);  
					 Check_char(out_errdesc,NULL);
				}
			        else
				{
					 fill_capi_result("CtSgwSysCmdSetLOID","pass",return_value,t_diff);
					//target_result=atoi(cJSON_GetObjectItem(target,"result")->valuestring);  
					Check_int(out_result,0);
				}
			g_free(out_errdesc);
			}
			break;
	case CtSgwSysCmdRegisterLOID_NUM:{  
			                        
				//guint32 target_res;   
				guint32 out_res = -1;  
				gchar *out_errdesc = NULL;
				//gchar *target_errdesc = NULL;

				//cJSON *target = cJSON_GetObjectItem(testcase,"target");

 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				return_value = CtSgwSysCmdRegisterLOID(&out_res,&out_errdesc);    

			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
   
			        if(FALSE == Check_return_result(return_value,atoi(return_target)))
				{					
					 fill_capi_result("CtSgwSysCmdRegisterLOID","failed",return_value,t_diff); 
					//strcpy(target_errdesc,cJSON_GetObjectItem(target,"errdesc")->valuestring);  
					Check_char(out_errdesc,NULL);
				}
			        else
				{
					 fill_capi_result("CtSgwSysCmdRegisterLOID","pass",return_value,t_diff);
					//target_res=atoi(cJSON_GetObjectItem(target,"res")->valuestring);  
					Check_int(out_res,0);
				}
			g_free(out_errdesc);
			}
			break;
	case CtSgwSysCmdCheckLOID_NUM:{
			         
				//guint32 target_errcode;   
				guint32 out_errcode = -1;  
				gchar *out_errmsg = NULL;
				//gchar *target_errmsg = NULL;

				//cJSON *target = cJSON_GetObjectItem(testcase,"target");
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				return_value = CtSgwSysCmdCheckLOID(&out_errcode,&out_errmsg);  
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
     
			        if(FALSE == Check_return_result(return_value,atoi(return_target)))
				{
					 fill_capi_result("CtSgwSysCmdCheckLOID","failed",return_value,t_diff); 
					//strcpy(target_errmsg,cJSON_GetObjectItem(target,"errmsg")->valuestring);  
					Check_char(out_errmsg,NULL);
				}
			        else
				{
					 fill_capi_result("CtSgwSysCmdCheckLOID","pass",return_value,t_diff);
					//target_errcode=atoi(cJSON_GetObjectItem(target,"errcode")->valuestring);  
					Check_int(out_errcode,0);
				}
			g_free(out_errmsg);
			}
			break;
	case CtSgwSysCmdReboot_NUM:{  
			              
			        guint32 out_result = -1;  
			        //guint32 target_result; 
				gchar *out_errdesc = NULL;
				//gchar *target_errdesc = NULL;
 
				//cJSON *target = cJSON_GetObjectItem(testcase,"target");  
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
      
				return_value = CtSgwSysCmdReboot(&out_result,&out_errdesc); 

			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;  

				if(FALSE == Check_return_result(return_value,atoi(return_target))) 
				{
					 fill_capi_result("CtSgwSysCmdReboot","failed",return_value,t_diff); 
					//strcpy(target_errdesc,cJSON_GetObjectItem(target,"errdesc")->valuestring);  
					Check_char(out_errdesc,NULL);
				}
			        else
				{
					 fill_capi_result("CtSgwSysCmdReboot","pass",return_value,t_diff);
					//target_result=atoi(cJSON_GetObjectItem(target,"result")->valuestring); 
					Check_int(out_result,0);
				}
			g_free(out_errdesc);
			}
			break;
	case CtSgwSysCmdRestore_NUM:{  
			         
				guint32 out_result = -1;
				//guint32 target_result;  
				gchar *out_errdesc = NULL;
				//gchar *target_errdesc = NULL;

				//cJSON *target = cJSON_GetObjectItem(testcase,"target");   
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
                      
				return_value = CtSgwSysCmdRestore(&out_result,&out_errdesc); 
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
  
				if(FALSE == Check_return_result(return_value,atoi(return_target))) 
				{
					 fill_capi_result("CtSgwSysCmdRestore","failed",return_value,t_diff); 
					//strcpy(target_errdesc,cJSON_GetObjectItem(target,"errdesc")->valuestring);  
					Check_char(out_errdesc,NULL);
				}
			        else
				{
					 fill_capi_result("CtSgwSysCmdRestore","pass",return_value,t_diff);
					 // target_result=atoi(cJSON_GetObjectItem(target,"result")->valuestring); 
					 Check_int(out_result,0);
				}
			g_free(out_errdesc);
			}
			break;
	case CtSgwSysCmdUpgrade_NUM:{
   
				char url[128] = "";
				int mode;
				int method;
				guint32 out_result = -1;
				//guint32 target_result;
				gchar *out_errdesc = NULL;
				//gchar *target_errdesc = NULL;

				cJSON *in = cJSON_GetObjectItem(testcase,"in");
				//cJSON *target = cJSON_GetObjectItem(testcase,"target");

				strcpy(url,cJSON_GetObjectItem(in,"url")->valuestring);  
				mode=atoi(cJSON_GetObjectItem(in,"mode")->valuestring);  
				method=atoi(cJSON_GetObjectItem(in,"method")->valuestring);  
 			 double start,end,t_diff=0; struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;

				return_value = CtSgwSysCmdUpgrade(url,mode,method,&out_result,&out_errdesc); 
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
      
				if(FALSE == Check_return_result(return_value,atoi(return_target))) 
				{
					 fill_capi_result("CtSgwSysCmdUpgrade","failed",return_value,t_diff); 
					//strcpy(target_errdesc,cJSON_GetObjectItem(target,"errdesc")->valuestring);  
					Check_char(out_errdesc,NULL);
				}
			        else
				{
					 fill_capi_result("CtSgwSysCmdUpgrade","pass",return_value,t_diff);
					//target_result=atoi(cJSON_GetObjectItem(target,"result")->valuestring);
					Check_int(out_result,0);
				}
			g_free(out_errdesc);
			}
			break;
	case GVariant_NUM:{
				 doGVariant();
				 doGVariant2();
			 }		 
			 break;
        case CtSgwDelVPNConnection_NUM:{       
                          g_print("CtSgwDelVPNConnection=========1\n");
			 CtSgwObjPath_t path;
			 cJSON *in = cJSON_GetObjectItem(testcase,"in");
			 strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring); 
 			 double start,end,t_diff=0;
                         struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
                        g_print("CtSgwDelVPNConnection=========2\n");
                        g_print("%s\n",path.str);
				 return_value = CtSgwDelVPNConnection(path); 
                        g_print("CtSgwDelVPNConnection=========3\n");
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
  
				 if(FALSE == Check_return_result(return_value,atoi(return_target))) 
					 fill_capi_result("CtSgwDelVPNConnection","failed",return_value,t_diff); 
			         else
					 fill_capi_result("CtSgwDelVPNConnection","pass",return_value,t_diff);
			 }
			 break;
           //the following is add by 0705
                case CtSgwWiFiSetRatePriority_NUM:{
                         gboolean is5g;
                         gboolean enable;
                         char* charis5g="";
                         char* charenable="";
                         cJSON *in = cJSON_GetObjectItem(testcase,"in");
			 strcpy(charis5g,cJSON_GetObjectItem(in, "is5g")->valuestring);
                         strcpy(charenable,cJSON_GetObjectItem(in, "enable")->valuestring); 
		             if(strcmp(charis5g,"1"))
			       is5g=TRUE;
			     else
		               is5g=FALSE;
		             if(strcmp(charenable,"1"))
		              enable=TRUE;
			     else
			      enable=FALSE;
                         double start,end,t_diff=0;
                         struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
	                return_value = CtSgwWiFiSetRatePriority(is5g,enable);                 
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
			 if(FALSE == Check_return_result(return_value,atoi(return_target))) 
				 fill_capi_result("CtSgwWiFiSetRatePriority","failed",return_value,t_diff); 
		         else
				 fill_capi_result("CtSgwWiFiSetRatePriority","pass",return_value,t_diff);
			}
                break;   

               case CtSgwDelLANHost_NUM:{
                         CtSgwObjPath_t path;
                         cJSON *in = cJSON_GetObjectItem(testcase,"in");
			 strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring);
                         double start,end,t_diff=0;
                         struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
	                return_value = CtSgwDelLANHost(path);                 
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
			 if(FALSE == Check_return_result(return_value,atoi(return_target))) 
				 fill_capi_result("CtSgwDelLANHost","failed",return_value,t_diff); 
		         else
				 fill_capi_result("CtSgwDelLANHost","pass",return_value,t_diff);
			}
                break;          

  case CtSgwSysCmdUploadTroubleLocationInfo_NUM:{
                         CtSgwObjPath_t path;
                         cJSON *in = cJSON_GetObjectItem(testcase,"in");
			char *uploadurl=cJSON_GetObjectItem(in, "uploadurl")->valuestring;
			char *faultcategory=cJSON_GetObjectItem(in, "faultcategory")->valuestring;
			int result=-1;
			char *errdesc=NULL;
                         double start,end,t_diff=0;
                         struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
	                return_value = CtSgwSysCmdUploadTroubleLocationInfo(uploadurl, faultcategory, &result, &errdesc);               
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
			 if(FALSE == Check_return_result(return_value,atoi(return_target))) 
				 fill_capi_result("CtSgwSysCmdUploadTroubleLocationInfo","failed",return_value,t_diff); 
		         else
				 fill_capi_result("CtSgwSysCmdUploadTroubleLocationInfo","pass",return_value,t_diff);
                         g_free(errdesc);
			}
                break;    

 case CtSgw_USBFormat_NUM:{
                         CtSgwObjPath_t  path;
                         cJSON *in = cJSON_GetObjectItem(testcase,"in");
			 strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring);
			guint32 result=-1;
			gchar *errdesc=NULL;
                         double start,end,t_diff=0;
                         struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
	                return_value = CtSgw_USBFormat(path, &result, &errdesc);               
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
			 if(FALSE == Check_return_result(return_value,atoi(return_target))) 
				 fill_capi_result("CtSgw_USBFormat","failed",return_value,t_diff); 
		         else
				 fill_capi_result("CtSgw_USBFormat","pass",return_value,t_diff);
                       g_free(errdesc);
			}
                break;         
      
       case CtSgwGetDNSTunnelObjs_NUM:{
                         //cJSON *in = cJSON_GetObjectItem(testcase,"in");
			CtSgwDNSTunnel_t *objs;
			gint32 count=-1;
                         double start,end,t_diff=0;
                         struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
	                return_value = CtSgwGetDNSTunnelObjs(&objs, &count);               
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
			 if(FALSE == Check_return_result(return_value,atoi(return_target))) 
				 fill_capi_result("CtSgwGetDNSTunnelObjs","failed",return_value,t_diff); 
		         else
				 fill_capi_result("CtSgwGetDNSTunnelObjs","pass",return_value,t_diff);
			}
                break; 


 case CtSgwSetDNSTunnel_NUM:{
                         CtSgwObjPath_t  path;
                         cJSON *in = cJSON_GetObjectItem(testcase,"in");
			  strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring);
                        const char *server=cJSON_GetObjectItem(in, "server")->valuestring;
			const char *domain_name=cJSON_GetObjectItem(in, "domain_name")->valuestring;
                         double start,end,t_diff=0;
                         struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
	                return_value = CtSgwSetDNSTunnel(path, server,domain_name);               
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
			 if(FALSE == Check_return_result(return_value,atoi(return_target))) 
				 fill_capi_result("CtSgwSetDNSTunnel","failed",return_value,t_diff); 
		         else
				 fill_capi_result("CtSgwSetDNSTunnel","pass",return_value,t_diff);
			}
                break;         

case CtSgwDelDNSTunnel_NUM:{
                         CtSgwObjPath_t  path;
                         cJSON *in = cJSON_GetObjectItem(testcase,"in");
			 strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring);
                         double start,end,t_diff=0;
                         struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
	                return_value = CtSgwDelDNSTunnel(path);               
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
			 if(FALSE == Check_return_result(return_value,atoi(return_target))) 
				 fill_capi_result("CtSgwDelDNSTunnel","failed",return_value,t_diff); 
		         else
				 fill_capi_result("CtSgwDelDNSTunnel","pass",return_value,t_diff);
			}
                break;      

      
case CtSgwDNSTunnelDetachDomain_NUM:{
                         CtSgwObjPath_t  path;
                        cJSON *in = cJSON_GetObjectItem(testcase,"in");
			const char *serverip= cJSON_GetObjectItem(in, "serverip")->valuestring;
			const char *domain_name=cJSON_GetObjectItem(in, "domain_name")->valuestring;
                         double start,end,t_diff=0;
                         struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
	                return_value = CtSgwDNSTunnelDetachDomain(serverip,domain_name);               
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
			 if(FALSE == Check_return_result(return_value,atoi(return_target))) 
				 fill_capi_result("CtSgwDNSTunnelDetachDomain","failed",return_value,t_diff); 
		         else
				 fill_capi_result("CtSgwDNSTunnelDetachDomain","pass",return_value,t_diff);
			}
                break;     
        

case CtSgwDNSTunnelAttachDomain_NUM:{
                         CtSgwObjPath_t  path;
                         cJSON *in = cJSON_GetObjectItem(testcase,"in");
			const char *serverip= cJSON_GetObjectItem(in, "serverip")->valuestring;
			const char *domain_name=cJSON_GetObjectItem(in, "domain_name")->valuestring;
                         double start,end,t_diff=0;
                         struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
	                return_value = CtSgwDNSTunnelAttachDomain(serverip,domain_name);               
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
			 if(FALSE == Check_return_result(return_value,atoi(return_target))) 
				 fill_capi_result("CtSgwDNSTunnelAttachDomain","failed",return_value,t_diff); 
		         else
				 fill_capi_result("CtSgwDNSTunnelAttachDomain","pass",return_value,t_diff);
			}
                break;     
        
case CtSgwGetPlatformService_NUM:{
                         CtSgwPlatformService_t *obj;
                         double start,end,t_diff=0;
                         struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
	                return_value = CtSgwGetPlatformService(obj);               
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
			 if(FALSE == Check_return_result(return_value,atoi(return_target))) 
				 fill_capi_result("CtSgwGetPlatformService","failed",return_value,t_diff); 
		         else
				 fill_capi_result("CtSgwGetPlatformService","pass",return_value,t_diff);
			}
                break;     
        
case 
CtSgwSetPlatformService_NUM:{
                         CtSgwPlatformService_t  obj;
                         cJSON *in = cJSON_GetObjectItem(testcase,"in");
		        obj.Appmodel=(int)cJSON_GetObjectItem(in, "Appmodel")->valuestring;
                        strcpy(obj.InitUAPwd,cJSON_GetObjectItem(in, "InitUAPwd")->valuestring);
			strcpy(obj.InitSSID,cJSON_GetObjectItem(in, "InitSSID")->valuestring);
                        strcpy(obj.InitSSIDPwd,cJSON_GetObjectItem(in, "InitSSIDPwd")->valuestring);
			strcpy(obj.DistAddr,cJSON_GetObjectItem(in, "DistAddr")->valuestring);
                        obj.DistStatus=(int)cJSON_GetObjectItem(in, "DistStatus")->valuestring;
			strcpy(obj.OperAddr,cJSON_GetObjectItem(in, "OperAddr")->valuestring);
                        obj.OperStatus=(int)cJSON_GetObjectItem(in, "OperStatus")->valuestring;
                        strcpy(obj.OperAddr,cJSON_GetObjectItem(in, "PluginAddr")->valuestring);
                        obj.PluginStatus=(int)cJSON_GetObjectItem(in, "PluginStatus")->valuestring;
                         double start,end,t_diff=0;
                         struct timeval t_start,t_end,t_cont;
			 gettimeofday(&t_start,0);
			 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
	                return_value = CtSgwSetPlatformService(&obj);               
			gettimeofday(&t_end,0);
			end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
			t_diff = end - start;
			 if(FALSE == Check_return_result(return_value,atoi(return_target))) 
				 fill_capi_result("CtSgwSetPlatformService","failed",return_value,t_diff); 
		         else
				 fill_capi_result("CtSgwSetPlatformService","pass",return_value,t_diff);
			}
                break;  


case CtSgwAddDNSTunnel_NUM:{    
				 char domain_name[128] = "";
				 char server[128] = "";
				 cJSON *in = cJSON_GetObjectItem(testcase,"in");
				 strcpy(domain_name,cJSON_GetObjectItem(in, "domain_name")->valuestring); 
				 strcpy(server,cJSON_GetObjectItem(in, "server")->valuestring); 		    
		                 double start,end,t_diff=0;
		                 struct timeval t_start,t_end,t_cont;
				 gettimeofday(&t_start,0);
				 start = (double)t_start.tv_sec * 1000 + (double)t_start.tv_usec / 1000;
				 return_value = CtSgwAddDNSTunnel(server,domain_name);
		                gettimeofday(&t_end,0);
				end = (double)t_end.tv_sec * 1000 + (double)t_end.tv_usec / 1000;
				t_diff = end - start;
				 if(FALSE == Check_return_result(return_value,atoi(return_target))) 
					 fill_capi_result("CtSgwAddDNSTunnel","failed",return_value,t_diff); 
			         else
					 fill_capi_result("CtSgwAddDNSTunnel","pass",return_value,t_diff); 
			 }
			 break;




	}
}
gboolean  doGVariant(){
gboolean flags = TRUE;
		{
		CtSgwVariant_t *arr[2];
		int i0, i1, i2, i3;
		char *s0;
		CtSgwVariant *v0;
		arr[0] = CtSgwVariantNewDictEntry( CtSgwVariantNew("s","aaa"), CtSgwVariantNew("v", CtSgwVariantNew("i", 1)));
		arr[1] = CtSgwVariantNewDictEntry( CtSgwVariantNew("s","bbb"), CtSgwVariantNew("v", CtSgwVariantNew("s", "xx")));
		CtSgwVariant_t *v = CtSgwVariantNew("(is@a{sv}(iii))", 
		1, "hello", CtSgwVariantNewArray(arr, 2), 1, 2, 3);

CtSgwVariant_t *v1 = CtSgwVariantNew("i", 1);
g_print("CtSgwVariantNew(\"i\", 1) %s\n",CtSgwVariantPrint(v1));
if(0 != g_strcmp0(CtSgwVariantPrint(v1),"1"))
{
g_print("11111111111111111111111111\n");
	flags = FALSE;
}

CtSgwVariant_t *v2 = CtSgwVariantNew("s", "hello");
g_print("CtSgwVariantNew(\"s\", \"hello\") %s\n",CtSgwVariantPrint(v2));
if(0 != g_strcmp0(CtSgwVariantPrint(v2),"\'hello\'"))
{
g_print("22222222222222222222\n");
	flags = FALSE;
}

CtSgwVariant_t *v3 = CtSgwVariantNew("(@a{sv})", CtSgwVariantNewArray(arr, 2));

	// Ali-20160412-add to parse gvariant value
	CtSgwVariant *v55 = NULL;
	GVariantIter iter;
	gchar *key = NULL;
	gint32 num;
	gchar *str_val = NULL;
	CtSgwVariant *value = NULL;

	CtSgwVariantGet (v3, "(@a{sv})", &v55);
	g_variant_iter_init (&iter, v55);
        while (g_variant_iter_next (&iter, "{sv}", &key, &value))
        {
                if (g_strcmp0 (key, "aaa") == 0)
                {
                        g_variant_get (value, "i", &num);
                        g_print ("aaa : %d\n", num);
			if(num != 1)
				flags = FALSE;
                }
                else if (g_strcmp0 (key, "bbb") == 0)
                {
                        g_variant_get (value, "s", &str_val);
                        g_print ("bbb: %s\n", str_val);
			if(0 != g_strcmp0(str_val,"xx"))
				flags = FALSE;
                }
        }
	// Ali-20160412-add-end.

CtSgwVariant_t *v4 = CtSgwVariantNew("b", 1);
g_print("CtSgwVariantNew(\"b\", 1) %s\n",CtSgwVariantPrint(v4));
if(0 != g_strcmp0(CtSgwVariantPrint(v4),"true"))
{
g_print("44444444444444444444444\n");
	flags = FALSE;
}

CtSgwVariant_t *v5 = CtSgwVariantNew("y", 1);
g_print("CtSgwVariantNew(\"y\", 1) %s\n",CtSgwVariantPrint(v5));
if(0 != g_strcmp0(CtSgwVariantPrint(v5),"byte 0x01"))
{
g_print("55555555555555555555555555555\n");
	flags = FALSE;
}

/*
CtSgwVariant_t *v6 = CtSgwVariantNew("n", 1);
g_print("CtSgwVariantNew(\"n\", 1) %s\n",CtSgwVariantPrint(v6));

CtSgwVariant_t *v7 = CtSgwVariantNew("q", 1);
g_print("CtSgwVariantNew(\"q\", 1) %s\n",CtSgwVariantPrint(v7));

CtSgwVariant_t *v8 = CtSgwVariantNew("i", 1);
g_print("CtSgwVariantNew(\"i\", 1) %s\n",CtSgwVariantPrint(v8));

CtSgwVariant_t *v9 = CtSgwVariantNew("u", 1);
g_print("CtSgwVariantNew(\"u\", 1) %s\n",CtSgwVariantPrint(v9));

CtSgwVariant_t *v10 = CtSgwVariantNew("x", 1);
g_print("CtSgwVariantNew(\"x\", 1) %s\n",CtSgwVariantPrint(v10));

CtSgwVariant_t *v11 = CtSgwVariantNew("t", 1);
g_print("CtSgwVariantNew(\"t\", 1) %s\n",CtSgwVariantPrint(v11));

CtSgwVariant_t *v12 = CtSgwVariantNew("h", 1);
g_print("CtSgwVariantNew(\"h\", 1) %s\n",CtSgwVariantPrint(v12));

CtSgwVariant_t *v13 = CtSgwVariantNew("d", 1);
g_print("CtSgwVariantNew(\"d\", 1) %s\n",CtSgwVariantPrint(v13));
*/
CtSgwVariantGet(v, "(is@a{sv}(iii))", &i0, &s0, &v0, &i1, &i2, &i3);

		/*int num = CtSgwVariantChildNum(v0);
                int i;
		for ( i= 0 ;i < num; i++) {
		CtSgwVariant *key;
		CtSgwVariant_t *value;
		CtSgwVariantGetChild(v0, i, "{sv}", &key, &value);
		g_print("return message : %s    %s\n", key,CtSgwVariantPrint(value));
		}*/
		}
		//case2
		{
		GVariant    *pmark = NULL;
		gdouble m1 = 80;
		gdouble m2 = 70;
		const gchar * sm1 = "chinese";
		const gchar * sm2 = "english";
		const gchar *           subChin = NULL;
		gdouble                 markChin = 0;
		const gchar *           subEng = NULL;
		gdouble                 markEng = 0;
		pmark = CtSgwVariantNew("((sd)(sd))",sm1,m1,sm2,m2);
		CtSgwVariantGet(pmark, "((sd)(sd))",&subChin,&markChin,&subEng,&markEng);
		if(0 != g_strcmp0(subChin,"chinese") || (markChin != 80) || 0 != g_strcmp0(subEng,"english") || (markEng != 70))
		{
			g_print("6666666666666666666666666666666\n");
			flags = FALSE;
		}
		g_print("return message subChin:%s,markChin:%lf,        subEng:%s,markEng:%lf\n", subChin,markChin,subEng,markEng);
		}
		//case3
	{
	//GVariantBuilder *builder = NULL;

        GVariant *argin = NULL;
        CtSgwVariant_t* outarg= NULL;
        GVariantIter iter;
        gchar * str = NULL;
        CtSgwVariant_t *arr[3];
        CtSgwVariant_t* inarg= NULL;

        arr[0] = CtSgwVariantNewDictEntry( CtSgwVariantNew("s","aaa"), CtSgwVariantNew("i",0));
        arr[1] = CtSgwVariantNewDictEntry( CtSgwVariantNew("s","bbb"), CtSgwVariantNew("i",1));
        arr[2] = CtSgwVariantNewDictEntry( CtSgwVariantNew("s","ccc"), CtSgwVariantNew("i",2));
        GVariant *tmp = CtSgwVariantNewArray(arr, 3);
        g_print ("%s %s\n", g_variant_get_type_string (tmp), g_variant_print (tmp, TRUE));
        argin = CtSgwVariantNew("(@a{si})", CtSgwVariantNewArray(arr, 3));

        gint32 num = 0;
        CtSgwVariantGet(argin, "(@a{si})", &outarg);
         g_variant_iter_init (&iter, outarg);
        while (g_variant_iter_loop(&iter, "{si}", &str,&num))
        {
		if(g_strcmp0(str, "aaa") == 0)
		{
			if (num == 0)
				g_print("Pass!!!!!!\n");
			else
			{
				flags = FALSE;
				g_print("failed!!!!!\n");
			}
				
		}
		else if(g_strcmp0(str, "bbb") == 0)
		{
			if (num == 1)
				g_print("Pass!!!!!!!\n");
			else
			{
				flags = FALSE;
				g_print("failed!!!!!\n");
			}
			
		}
		else
		{
			if (num == 2)
				g_print("Pass!!!!!!\n");
			else
			{
				flags = FALSE;
				g_print("failed!!!!!\n");
			}
			
		}		
                g_print("return message : %s    %d\n", str,num);
        }
}

	//case3
	{
	//GVariantBuilder *builder = NULL;
	GVariant *argin = NULL;
	GVariant *outarg = NULL;
	CtSgwVariant_t *arr[3];
	gchar * str = NULL;
	CtSgwVariant_t* outarg_t= NULL;
	// builder = g_variant_builder_new(G_VARIANT_TYPE("a{ss}"));

	arr[0] = CtSgwVariantNewDictEntry(CtSgwVariantNew("s","lastdance.mp3"), CtSgwVariantNew("s","music/lastdance.mp3"));
	arr[1] = CtSgwVariantNewDictEntry( CtSgwVariantNew("s","Madonna.mp3"),CtSgwVariantNew("s","music/Madonna.mp3"));
	arr[2] = CtSgwVariantNewDictEntry( CtSgwVariantNew("s","DavidGarrett.mp3"),CtSgwVariantNew("s","music/David Garrett.mp3"));
	argin = CtSgwVariantNew("(@a{ss})", CtSgwVariantNewArray(arr, 3));


	// g_variant_builder_add(builder,"{ss}","lastdance.mp3","music/lastdance.mp3");
	// g_variant_builder_add(builder,"{ss}","Madonna.mp3","music/Madonna.mp3");
	// g_variant_builder_add(builder,"{ss}","DavidGarrett.mp3","music/David Garrett.mp3");
	// argin = CtSgwVariantNew("a{ss}", builder);
	// g_variant_builder_unref(builder);
	CtSgwVariantGet (argin, "(@a{ss})", &outarg);
	g_print ("%s %s\n", g_variant_get_type_string(outarg), g_variant_print (outarg, TRUE));
	outarg_t=CtSgwVariantLookupValue(outarg,"lastdance.mp3","s");
	g_print("CtSgwVariantLookupValue keyvalue:  %s  %s\n",g_variant_get_type_string(outarg_t), CtSgwVariantPrint(outarg_t));
	CtSgwVariantGet (outarg_t, "s", &str);
	if(0 != g_strcmp0(str,"music/lastdance.mp3"))
	{
		g_print("failed!!!!!!!!\n");
		flags = FALSE;
	}
 	g_print ("str = %s\n", str);
	g_free(str);

	//CtSgwVariantGet (outarg_t, "(ss)
	//inarg_t=GVar2CtSgwVar(outarg);
	
	outarg_t=GVar2CtSgwVar(CtSgwVar2GVar(outarg_t));
	g_print("CtSgwVariantLookupValue2 find keyvalue:%s\n",CtSgwVariantPrint(outarg_t));	
	
	CtSgwVariantLookup(argin,"lastdance.mp3","s",&str);
	g_print("CtSgwVariantLookup find keyvalue:%s\n",str);
	if(0 != g_strcmp0(str,"Madonna.mp3"))
	{
		g_print("failed!!!!!!!!!!!!!!!!!\n");
		flags = FALSE;
	}
}
//case4
{   
	CtSgwVariant_t *arr[2];
	arr[0] = CtSgwVariantNew( "s", "aaa");
	arr[1] = CtSgwVariantNew( "i", 1);
       //CtSgwVariant_t *tup = ;
	g_print("CtSgwVariantLookupValue3 find keyvale:%s\n",CtSgwVariantPrint(CtSgwVariantNewTuple(arr,2)));
}
	if(FALSE == flags) 
		fill_capi_result("GVariant","failed",flags,0); 
				
	else
		fill_capi_result("GVariant","pass",flags,0);
}

gboolean  doGVariant2(){
gboolean flags = TRUE;
//case1
//g_print("doGVariant2 \n");
/*		{
		CtSgwVariant_t *arr[2];
		int i0, i1, i2, i3;
		char *s0;
		CtSgwVariant *v0;
g_print("arr \n");	
		arr[0] = CtSgwVariantNewDictEntry( CtSgwVariantNew("s","aaa"), CtSgwVariantNew("i", "xxx"));
g_print("case1 \n");	
//		arr[1] = CtSgwVariantNewDictEntry( CtSgwVariantNew("i","bbb"), CtSgwVariantNew("s", 1));
g_print("CtSgwVariantNewDictEntry \n");	
	//	CtSgwVariant_t *v = CtSgwVariantNew("(si@a{iv}(sss))", 
	//	1, "hello", CtSgwVariantNewArray(arr, 1), 1, 2, 3);
g_print("CtSgwVariantNew \n");	

		CtSgwVariantGet(v, "(si@a{iv}(sss))", &i0, &s0, &v0, &i1, &i2, &i3);
g_print("CtSgwVariantGet \n");	
		int num = CtSgwVariantChildNum(v0);
g_print("CtSgwVariantChildNum  %d\n",num);	
		int i ;
		for (i= 0 ;i < num; i++) {
		char *key;
		CtSgwVariant_t *value;
g_print("CtSgwVariantGetChild \n");	
		CtSgwVariantGetChild(v0, i, "{iv}", &key, &value);
		g_print("return message : %s    %s\n", key,CtSgwVariantPrint(value));
		}
		}*/
		//case2
		{
		GVariant    *pmark = NULL;
		gdouble m1 = 80;
		gdouble m2 = 70;
		const gchar * sm1 = "chinese";
		const gchar * sm2 = "english";
		const gchar *           subChin = NULL;
		gdouble                 markChin = 0;
		const gchar *           subEng = NULL;
		gdouble                 markEng = 0;
//g_print("case2 \n");
/*
		pmark = CtSgwVariantNew("((ds)(sd))",sm1,m1,sm2,m2);
g_print("CtSgwVariantNew \n");
		CtSgwVariantGet(pmark, "((sd)(ds))",&subChin,&markChin,&subEng,&markEng);
g_print("CtSgwVariantGet \n");
		g_print("return message subChin:%s,markChin:%d,        subEng:%s,markEng:%d\n", subChin,markChin,subEng,markEng);
*/
		}
				{
		GVariant    *pmark = NULL;
		gdouble m1 = 80;
		gdouble m2 = 70;
		const gchar * sm1 = "chinese1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111";
		const gchar * sm2 = "english2222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222";
		const gchar *           subChin = NULL;
		gdouble                 markChin = 0;
		const gchar *           subEng = NULL;
		gdouble                 markEng = 0;
		pmark = CtSgwVariantNew("((sd)(sd))",sm1,m1,sm2,m2);
//g_print("CtSgwVariantGet \n");
		CtSgwVariantGet(pmark, "((sd)(sd))",&subChin,&markChin,&subEng,&markEng);
		if(0 != strcmp(subChin,"chinese1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111") || (markChin != 80) || 0 != strcmp(subEng,"english2222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222") || (markEng != 70))
		{
			g_print("7777777777777777777777777777777\n");
			flags = FALSE;
		}
		g_print("return message subChin:%s,markChin:%lf,        subEng:%s,markEng:%lf\n", subChin,markChin,subEng,markEng);
		}
		//case3
		{
	//GVariantBuilder *builder = NULL;

	GVariant *argin = NULL;
	CtSgwVariant_t* outarg_t= NULL;
	GVariantIter *iter = NULL;
	const gchar * str = NULL;
	CtSgwVariant_t *arr[3];
	CtSgwVariant_t* inarg= NULL;
	// builder = g_variant_builder_new(G_VARIANT_TYPE("a(sn)"));
	//  g_variant_builder_add(builder, "(sn)","test",1);
	//  g_variant_builder_add(builder, "(sn)","tmp",2);
//g_print("case3 \n");
	arr[0] = CtSgwVariantNewDictEntry( CtSgwVariantNew("s","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"), CtSgwVariantNew("i",0));
g_print("CtSgwVariantNewDictEntry arr value:%s\n",CtSgwVariantPrint(arr[0]));	
//g_print("CtSgwVariantNewDictEntry \n");
//	arr[1] = CtSgwVariantNewDictEntry( CtSgwVariantNew("s","bbb"), CtSgwVariantNew("s",1));
//	arr[2] = CtSgwVariantNewDictEntry( CtSgwVariantNew("s",5), CtSgwVariantNew("i",2));
//	argin = CtSgwVariantNew("(@a{si})", CtSgwVariantNewArray(arr, 1));//wjq
//g_print("CtSgwVariantNew \n");
	//g_variant_builder_unref(builder);
	gint16 num = 0;
//g_print("CtSgwVariantGet \n");
/*
	CtSgwVariantGet(argin, "(@a{si})", &iter);
g_print("CtSgwVariantGet2 \n");
	while (g_variant_iter_loop(iter, "(si)", &str,&num))
	{
	g_print("return message : %s    %d\n", str,num);
	}*///wjq
//	g_variant_iter_free(iter);
	}
	//case3
/*	{
	//GVariantBuilder *builder = NULL;
	GVariant *argin = NULL;
	GVariant *outarg = NULL;
	CtSgwVariant_t *arr[3];
	const gchar * str = NULL;
        CtSgwVariant_t* outarg_t= NULL;
	// builder = g_variant_builder_new(G_VARIANT_TYPE("a{ss}"));
	arr[0] = CtSgwVariantNewDictEntry( CtSgwVariantNew("s","lastdance.mp3"), CtSgwVariantNew("s","music/lastdance.mp3"));
	arr[1] = CtSgwVariantNewDictEntry( CtSgwVariantNew("s","Madonna.mp3"),CtSgwVariantNew("s","music/Madonna.mp3"));
	arr[2] = CtSgwVariantNewDictEntry( CtSgwVariantNew("s","DavidGarrett.mp3"),CtSgwVariantNew("s","music/David Garrett.mp3"));
	argin = CtSgwVariantNew("(@a{ss})", CtSgwVariantNewArray(arr, 3));

	// g_variant_builder_add(builder,"{ss}","lastdance.mp3","music/lastdance.mp3");
	// g_variant_builder_add(builder,"{ss}","Madonna.mp3","music/Madonna.mp3");
	// g_variant_builder_add(builder,"{ss}","DavidGarrett.mp3","music/David Garrett.mp3");
	//  argin = CtSgwVariantNew("a{ss}", builder);
	//g_variant_builder_unref(builder);
g_print("CtSgwVariantLookupValue \n");
    outarg_t=CtSgwVariantLookupValue(argin,"lastdance.mp3","s");
	//inarg_t=GVar2CtSgwVar(outarg);
	g_print("CtSgwVariantLookupValue find keyvalue:%s\n",CtSgwVariantPrint(outarg_t));
	outarg_t=GVar2CtSgwVar(CtSgwVar2GVar(outarg_t));
	g_print("CtSgwVariantLookupValue2 find keyvalue:%s\n",CtSgwVariantPrint(outarg_t));	
	
	g_print("CtSgwVariantLookupValue3 find keyvalue:%s\n",CtSgwVariantPrint(outarg_t));
	CtSgwVariantLookup(argin,"lastdance.mp3","s",&str);
	g_print("CtSgwVariantLookup find keyvalue:%s\n",str);
}*/
//case4
{   
	CtSgwVariant_t *arr[2];
//g_print("CtSgwVariantNew \n");
	arr[0] = CtSgwVariantNew( "s", "aaa1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111");
	arr[1] = CtSgwVariantNew( "i", 10000000000000);
	g_print("CtSgwVariantLookupValue3 find keyvale:%s\n",CtSgwVariantPrint(CtSgwVariantNewTuple(arr,2)));
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
	FILE *f=NULL; long len; gchar *data; cJSON *json;
	g_print("Test Running dofile %s\n",filename);
	f = fopen(filename, "rb"); 
	g_print("Test Running dofile1 %p\n",f);
	fseek(f, 0, SEEK_END); 
	g_print("Test Running dofile 2\n");
	len = ftell(f); 
	g_print("Test Running dofile3 %ld\n",len);
	fseek(f, 0, SEEK_SET);
	g_print("Test Running dofile4 \n");
	data = (gchar*)malloc(len + 1); 
	g_print("Test Running dofile5 %p\n",data);
	fread(data, 1, len, f); 
	g_print("Test Running dofile6 \n");
	fclose(f);
	//doit(data);

	json = cJSON_Parse(data);
	g_print("Test Running dofile\n");
	if (!json) { g_print("Error before: [%s]\n", cJSON_GetErrorPtr()); }
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
