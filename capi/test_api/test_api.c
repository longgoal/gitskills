#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "command_util.h"
#include "cJSON.h"
#include "map.h"
#include "capi-sys-service.h"
#include "test_runner.h"

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
	{ "CtSgwGetDeviceInfo", 1},
	{ "CtSgwGetNetworkInfo", 2},
	{ "CtSgwGeWANConnectionObjs", 3},
	{ "CtSgwGetWANConnection",4},
	{ "CtSgwGetWANConnectionByName",5},
	{ "CtSgwGetInternetWANConnection",6},
	{ "CtSgwGetWiFiInfo", 7},
	{ "CtSgwGetPONInfo", 8},
	{ "CtSgwGetVoIPInfo", 9},
	{ "CtSgwGetLANHostMgr", 10},
	{ "CtSgwSetLANHostMgr",11},
	{ "CtSgwGetLANHostObjs",12},
	{ "CtSgwGetLANHost",13},
	{ "CtSgwSetLANHost", 14},
	{ "CtSgwSetHttpDownloadTestURL",15},
	{ "CtSgwGetHttpDownloadTestURL",16},
	{ "CtSgwStartHttpDownloadTest", 17},
	{ "CtSgwGetHttpDownloadTestResult", 18},
    { "CtSgwStartPingTest" 19,},
    { "CtSgwGetPingTestResult", 20},
	{ "CtSgwStartTraceRouteTest", 21},
	{ "CtSgwGetTraceRouteTestResult", 22},
	{ "CtSgwStartInformTest", 23},
	{ "CtSgwGetInformTestResult", 24},
	{ "CtSgwStartMCTest", 25},
	{ "CtSgwGetMCTestResult", 26},
	{ "CtSgwSetPW", 27},
	{ "CtSgwGetPW", 28},
	{ "CtSgwSet404Redir",29},
	{ "CtSgwGet404Redir",30},
	{ "CtSgwSetWPS",31},
	{ "CtSgwGetWPS", 32},
	{ "CtSgwGetWLANDeviceObjs",33},
	{ "CtSgwGetWLANDevice",34},
	{ "CtSgwGetWLANDeviceBySSID",35},
	{ "CtSgwSetWLANDevice", 36},
	{ "CtSgwGetWiFiTimerObjs", 37},
	{ "CtSgwGetWiFiTimer", 38},
	{ "CtSgwSetWiFiTimer", 39},
	{ "CtSgwAddWiFiTimer", 40},
	{ "CtSgwDelWiFiTimer", 41},
	{ "CtSgwGetLEDObjs", 42},
	{ "CtSgwGetLED", 43},
	{ "CtSgwSetLED", 44},
	{ "CtSgwSetNFC", 45},
	{ "CtSgwGetNFC", 46},
	{ "CtSgwGetSleepTimerObjs", 47},
	{ "CtSgwGetSleepTimer", 48},
	{ "CtSgwSetSleepTimer", 49},
	{ "CtSgwAddSleepTimer", 50},
	{ "CtSgwDelSleepTimer", 51},
	{ "CtSgwSysCmdSetLOID", 52},
	{ "CtSgwSysCmdRegisterLOID", 53},
	{ "CtSgwSysCmdCheckLOID", 54},
	{ "CtSgwSysCmdSetDateTime", 55},
	{ "CtSgwSysCmdSetDevName",56},
	{ "CtSgwSysCmdReboot", 57},
	{ "CtSgwSysCmdRestore", 58},
	{ "CtSgwSysCmdUpgrade", 59},
	{ "CtSgwSysCmdCheckUAPasswd", 60},
	{ "CtSgwSysCmdCheckTAPasswd", 61},
	{ "CtSgwSysCmdSubscribe", 62},
	{ "CtSgwGetWANPPPConnObjs", 63},
	{ "CtSgwGetWANPPPConn", 64},
	{ "CtSgwSetWANPPPConn", 65},
	{ "CtSgwGetWANIPConnObjs", 66},
	{ "CtSgwGetWANIPConn", 67},
	{ "CtSgwSetWANIPConn", 68},
	{ "CtSgwGetDHCPServerObjs", 69},
	{ "CtSgwGetDHCPServer", 70},
	{ "CtSgwSetDHCPServer", 71},
	{ "CtSgwSetUplinkQos", 72},
	{ "CtSgwGetUplinkQoS", 73},
	{ "CtSgwGetUplinkQoSAppRuleObjs", 74},
	{ "CtSgwGetUplinkQoSAppRule", 75},
	{ "CtSgwSetUplinkQoSAppRule", 76},
	{ "CtSgwAddUplinkQoSAppRule", 77},
	{ "CtSgwDelUplinkQoSAppRule",78},
	{ "CtSgwGetUplinkQoSClsRuleObjs", 79},
	{ "CtSgwGetUplinkQoSClsRule", 80},
	{ "CtSgwAddUplinkQoSClsRule", 81},
	{ "CtSgwDelUplinkQoSClsRule", 82},
	{ "CtSgwSetUplinkQoSClsRule", 83},
	{ "CtSgwGetUplinkQoSClsMatch", 84},
	{ "CtSgwAddUplinkQoSClsMatch", 85},
	{ "CtSgwDelUplinkQoSClsMatch", 86},
	{ "CtSgwSetUplinkQoSClsMatch",87},
	{ "CtSgwGetPortMappingObjs", 88},
	{ "CtSgwGetPortMapping", 89},
	{ "CtSgwAddPortMapping", 90},
	{ "CtSgwDelPortMapping", 91},
	{ "CtSgwSetPortMapping", 92},
	{ "CtSgw_GetUSBDeviceObjs", 93},
	{ "CtSgw_GetUSBDevice", 94},
	{ "CtSgw_SetNASConfig", 95},
	{ "CtSgw_GetNASConfig", 96},
	{ "CtSgw_NAS_GetFileNum", 97},
	{ "CtSgw_NAS_ListFolder", 98},
	{ "CtSgw_NAS_CreateFolter", 99},
	{ "CtSgw_NAS_ReName", 100},
	{ "CtSgw_NAS_Remove", 101},
	{ "CtSgw_NAS_Move", 102},
	{ "CtSgw_NAS_Copy", 103},
	{ "CtSgw_NAS_GetCopyProgress", 104},
	{ "ctSgw_wanCreateL2tpTunnel", 105},
	{ "ctSgw_wanRemoveL2tpTunnel", 106},
	{ "ctSgw_wanAttachL2tpTunnel", 107},
	{ "ctSgw_wanDetachL2tpTunnel", 108},
	{ "ctSgw_wanGetL2tpTunnelStatus", 109},
	{ "CtSgw_AddDNSTunnel",110},
	{ "CtSgw_DelDNSTunnel", 111},
	{ "CtSgw_SetFtpServer", 112},
	{ "CtSgw_GetFTPServer", 113},
	{ "CtSgw_GetFTPAccountObjs", 114},
	{ "CtSgw_GetFTPAccount", 115},

	{ "CtSgw_AddFtpAccount", 116},
	{ "CtSgw_DelFtpAccount", 117},
	{ "CtSgw_GetSambaServer",118},
	{ "CtSgw_SetSambaServer", 119},
	{ "CtSgw_GetSambaAccountObjs", 120},
	{ "CtSgw_GetSambaAccount", 121},
	{ "CtSgw_AddSambaAccount", 122},
	{ "CtSgw_DelSambaAccount", 123},
	{ "CtSgw_GetHttpServer", 124},
	{ "CtSgw_SetHttpServer", 125}


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
   mode = Get_mode(command, extral);
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
	cJSON * case_index_root= dofile("../case/caseindex");
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
	gchar* path = "../case/";
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
	gchar * function_name = cJSON_GetObjectItem(testcase, "function_value")->valuestring;
	//cJSON *inlist = cJSON_GetObjectItem(testcase, "in");
	//cJSON *outlist = cJSON_GetObjectItem(testcase, "out");
	//cJSON *in = NULL;
	//cJSON *out = NULL;
	gchar * type_value = NULL;
	gchar * value_value = NULL;
	int function_index=-1;
	int param_index = -1;
	int return_value;
	function_index = map_find(&fuction_map, function_value, NULL);
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
   case 1:
   {        
			 CtSgwDeviceInfo_t out_param1;
			 CtSgwDeviceInfo_t target_param1;
             cJSON *target = cJSON_GetObjectItem(testcase, "target");
            
			 return_value = CtSgwGetDeviceInfo(&out_param1);
			 Check_return_result(return_value,atoi(return_target));
			 cJSON  *info = cJSON_GetObjectItem(target, "CtSgwDeviceInfo_t");
			 strcpy(target_param1.BusinessStatus,cJSON_GetObjectItem(info, "BusinessStatus")->valuestring);
			 strcpy(target_param1.MAC,cJSON_GetObjectItem(info, "MAC")->valuestring);
			 strcpy(target_param1.SWVersion,cJSON_GetObjectItem(info, "SWVersion")->valuestring);
			 strcpy(target_param1.HDVersion,cJSON_GetObjectItem(info, "HDVersion")->valuestring);
			 strcpy(target_param1.ProductClass,cJSON_GetObjectItem(info, "ProductClass")->valuestring);
			 strcpy(target_param1.CPUClass,cJSON_GetObjectItem(info, "CPUClass")->valuestring);
			 strcpy(target_param1.DevType,cJSON_GetObjectItem(info, "DevType")->valuestring);
			 strcpy(target_param1.DevType1,cJSON_GetObjectItem(info, "DevType1")->valuestring);
			 strcpy(target_param1.Capability,cJSON_GetObjectItem(info, "Capability")->valuestring);
			 strcpy(target_param1.FlashSize,cJSON_GetObjectItem(info, "FlashSize")->valuestring);
			 strcpy(target_param1.RamSize,cJSON_GetObjectItem(info, "RamSize")->valuestring);
			 strcpy(target_param1.DevName,cJSON_GetObjectItem(info, "DevName")->valuestring);
			 strcpy(target_param1.NFC,cJSON_GetObjectItem(info, "NFC")->valuestring);
			 strcpy(target_param1.LED,cJSON_GetObjectItem(info, "LED")->valuestring);
			 strcpy(target_param1.CPUUsage,cJSON_GetObjectItem(info, "CPUUsage")->valuestring);
			 strcpy(target_param1.MEMUsage,cJSON_GetObjectItem(info, "MEMUsage")->valuestring);
			 strcpy(target_param1.FlashUsage,cJSON_GetObjectItem(info, "FlashUsage")->valuestring);
			 strcpy(target_param1.SysDuration,cJSON_GetObjectItem(info, "SysDuration")->valuestring);
			 strcpy(target_param1.Card,cJSON_GetObjectItem(info, "Card")->valuestring);
			 strcpy(target_param1.Cardno,cJSON_GetObjectItem(info, "Cardno")->valuestring);
			 strcpy(target_param1.CardStatus,cJSON_GetObjectItem(info, "CardStatus")->valuestring);
			 strcpy(target_param1.RegisterStatus,cJSON_GetObjectItem(info, "RegisterStatus")->valuestring);
			 strcpy(target_param1.RegisterResult,cJSON_GetObjectItem(info, "RegisterResult")->valuestring);
			 strcpy(target_param1.RegisterProgressResult,cJSON_GetObjectItem(info, "RegisterProgressResult")->valuestring);
			 strcpy(target_param1.RegisterBussNameResult,cJSON_GetObjectItem(info, "RegisterBussNameResult")->valuestring);
			 strcpy(target_param1.RegisterServiceResult,cJSON_GetObjectItem(info, "RegisterServiceResult")->valuestring);
			 strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(info, "path"),"str")->valuestring);

			 CheckCtSgwDeviceInfo_t(&out_param1,&target_param1);
   }

	   break;
   case 2:{
                         CtSgwNetworkInfo_t out_param1;// define out_param
                         CtSgwNetworkInfo_t target_param1;
                         cJSON *target = cJSON_GetObjectItem(testcase,"target");//get the target of the testcae
                         
                         return_value = CtSgwGetNetworkInfo(&out_param1);       //get the return's value of the networkinfo
                         cJSON  *info = cJSON_GetObjectItem(target, "CtSgwNetworkInfo_t");
						 Check_return_result(return_value,atoi(return_target)); //check the return_value and the target
                         strcpy(target_param1.UPLink,cJSON_GetObjectItem(info, "UPLink")->valuestring);  
                         strcpy(target_param1.IPV6,cJSON_GetObjectItem(info, "IPV6")->valuestring);   
                         strcpy(target_param1.VLANbind,cJSON_GetObjectItem(info, "VLANbind")->valuestring);   
                         strcpy(target_param1.WiFiMode,cJSON_GetObjectItem(info, "WiFiMode[STR_LEN_48]")->valuestring);   
                         strcpy(target_param1.PONDuration,cJSON_GetObjectItem(info, "PONDuration")->valuestring);   
                         strcpy(target_param1.PPPOEDuration,cJSON_GetObjectItem(info, "PPPOEDuration")->valuestring);  
                         strcpy(target_param1.LAN1Status,cJSON_GetObjectItem(info, "LAN1Status")->valuestring);  
                         strcpy(target_param1.LAN2Status,cJSON_GetObjectItem(info, "LAN2Status")->valuestring);  
                         strcpy(target_param1.LAN3Status,cJSON_GetObjectItem(info, "LAN3Status")->valuestring);  
                         strcpy(target_param1.LAN4Status,cJSON_GetObjectItem(info, "LAN4Status")->valuestring);   

			 strcpy(target_param1.WANLinkStatus,cJSON_GetObjectItem(info, "WANLinkStatus")->valuestring);   
                         strcpy(target_param1.WIFIModuleStatus,cJSON_GetObjectItem(info, "WIFIModuleStatus")>valuestring);  
                         strcpy(target_param1.WANConnectionStatus,cJSON_GetObjectItem(info, "WANConnectionStatus")->valuestring);  
                         strcpy(target_param1.PPPoEDialReason,cJSON_GetObjectItem(info, "PPPoEDialReason")->valuestring);  
                         strcpy(target_param1.IPV6_WANConnectionStatus,cJSON_GetObjectItem(info, "IPV6_WANConnectionStatus")->valuestring);  
                         strcpy(target_param1.IPV6_PPPoEDialReason,cJSON_GetObjectItem(info, "IPV6_PPPoEDialReason")->valuestring);   
			 strcpy(target_param1.LANIPAddr,cJSON_GetObjectItem(info, "LANIPAddr")->valuestring);   
                         strcpy(target_param1.WANIPAddr,cJSON_GetObjectItem(info, "WANIPAddr")->valuestring);  
                         strcpy(target_param1.WANIPV6Addr,cJSON_GetObjectItem(info, "WANIPV6Addr")->valuestring);  
                         strcpy(target_param1.WiFiRate,cJSON_GetObjectItem(info, "WiFiRate")->valuestring);  
                         strcpy(target_param1.WiFiUSRate,cJSON_GetObjectItem(info, "WiFiUSRate")->valuestring);  
                         strcpy(target_param1.WiFiDSRate,cJSON_GetObjectItem(info, "WiFiDSRate")->valuestring);   

			 strcpy(target_param1.WANRate,cJSON_GetObjectItem(info, "WANRate")->valuestring);  
                         strcpy(target_param1.WANUSRate,cJSON_GetObjectItem(info, "WANUSRate")->valuestring);  
                         strcpy(target_param1.WANDSRate,cJSON_GetObjectItem(info, "WANDSRate")->valuestring);   
    			 strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(info, "path"),"str")->valuestring);

                         CheckCtSgwNetworkInfo_t(&out_param1,&target_param1);         

   }

	   break;
   case 3:{
                         CtSgwWANConnectionInfo_t* out_param1;
						 guint32 out_count;
			             guint32 target_count;
                         CtSgwWANConnectionInfo_t target_param1;
                         cJSON *target = cJSON_GetObjectItem(testcase,"target");

                         return_value = CtSgwGeWANConnectionObjs(&out_param1，&out_count);       
                         Check_return_result(return_value,atoi(return_target)); 
	                     cJSON * CtSgwWANConnectionInfo = cJSON_GetObjectItem(target, "CtSgwWANConnectionInfo_t");

			 strcpy(target_count,cJSON_GetObjectItem(target, "count")->valuestring);
			 Check_int(out_count,atoi(target_count));
        	 int index=0;
			 for (index = 0; index < cJSON_GetArraySize(CtSgwWANConnectionInfo); index++)
			 {
		
 			 strcpy(target_param1.Index,cJSON_GetObjectItem( cJSON_GetArrayItem(CtSgwWANConnectionInfo, index), "Index")->valuestring);  
                         strcpy(target_param1.IfName,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANConnectionInfo, index), "IfName")->valuestring);   
                         strcpy(target_param1.ServiceList,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANConnectionInfo, index), "ServiceList")->valuestring);   
			 strcpy(target_param1.ConnectionType,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANConnectionInfo, index), "ConnectionType")->valuestring);  

                         strcpy(target_param1.VLANID,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANConnectionInfo, index), "VLANID")->valuestring);   
                         strcpy(target_param1.VLAN8021P,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANConnectionInfo, index), "VLAN8021P")->valuestring);  
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
                         strcpy(target_param1.RxBytes,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANConnectionInfo, index), "RxBytes")->valuestring);   
			 strcpy(target_param1.TxBytes,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANConnectionInfo, index), "TxBytes")->valuestring);  
                         strcpy(target_param1.RxPkts,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANConnectionInfo, index), "RxPkts")->valuestring);   
                         strcpy(target_param1.TxPkts,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANConnectionInfo, index), "TxPkts")->valuestring);   
			 strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANConnectionInfo, index), "path"),"str")->valuestring);
             CheckCtSgwWANConnectionInfo_t(out_param1[index],&target_param1);
	}
                        
                         

     
   }
	   break;

   case 4:{
                         CtSgwWANConnectionInfo_t out_param1;
                         CtSgwWANConnectionInfo_t target_param1;
			 CtSgwObjPath_t path;
                         cJSON *target = cJSON_GetObjectItem(testcase,"target");
		         cJSON *in = cJSON_GetObjectItem(testcase,"in");
                         strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring); 

                         return_value = CtSgwGetWANConnection(path,&out_param1);       
                         Check_return_result(return_value,atoi(return_target)); 
                         strcpy(target_param1.Index,cJSON_GetObjectItem(target, "Index")->valuestring);  
                         strcpy(target_param1.IfName,cJSON_GetObjectItem(target, "IfName")->valuestring);   
                         strcpy(target_param1.ServiceList,cJSON_GetObjectItem(target, "ServiceList")->valuestring);   
			 strcpy(target_param1.ConnectionType,cJSON_GetObjectItem(target, "ConnectionType")->valuestring);  
                         strcpy(target_param1.VLANID,cJSON_GetObjectItem(target, "VLANID")->valuestring);   
                         strcpy(target_param1.VLAN8021P,cJSON_GetObjectItem(target, "VLAN8021P")->valuestring);  
			 strcpy(target_param1.Protocol,cJSON_GetObjectItem(target, "Protocol")->valuestring);  
                         strcpy(target_param1.ConnectionStatus,cJSON_GetObjectItem(target, "ConnectionStatus")->valuestring);   
                         strcpy(target_param1.IPAddress,cJSON_GetObjectItem(target, "IPAddress")->valuestring);   
			 strcpy(target_param1.SubnetMask,cJSON_GetObjectItem(target, "SubnetMask")->valuestring);  
                         strcpy(target_param1.Gateway,cJSON_GetObjectItem(target, "Gateway")->valuestring);   
                         strcpy(target_param1.DNS1,cJSON_GetObjectItem(target, "DNS1")->valuestring);    
			 strcpy(target_param1.DNS2,cJSON_GetObjectItem(target, "DNS2")->valuestring);  
                         strcpy(target_param1.IPV6_ConnectionStatus,cJSON_GetObjectItem(target, "IPV6_ConnectionStatus")->valuestring);   
                         strcpy(target_param1.IPV6_IPAddress,cJSON_GetObjectItem(target, "IPV6_IPAddress")->valuestring);   
			 strcpy(target_param1.IPV6_PrefixLength,cJSON_GetObjectItem(target, "IPV6_PrefixLength")->valuestring);  
                         strcpy(target_param1.IPV6_Gateway,cJSON_GetObjectItem(target, "IPV6_Gateway")->valuestring);   
                         strcpy(target_param1.IPV6_DNS1,cJSON_GetObjectItem(target, "IPV6_DNS1")->valuestring);  
			 strcpy(target_param1.IPV6_DNS2,cJSON_GetObjectItem(target, "IPV6_DNS2")->valuestring);  
                         strcpy(target_param1.IPV6_Prefix,cJSON_GetObjectItem(target, "IPV6_Prefix")->valuestring);   
                         strcpy(target_param1.RxBytes,cJSON_GetObjectItem(target, "RxBytes")->valuestring);   
			 strcpy(target_param1.TxBytes,cJSON_GetObjectItem(target, "TxBytes")->valuestring);  
                         strcpy(target_param1.RxPkts,cJSON_GetObjectItem(target, "RxPkts")->valuestring);   
                         strcpy(target_param1.TxPkts,cJSON_GetObjectItem(target, "TxPkts")->valuestring);  
              		 strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(target, "path"),"str")->valuestring);

                         CheckCtSgwWANConnectionInfo_t(&out_param1,&target_param1);

   }
	   break;
   
   case 5:{
                         CtSgwWANConnectionInfo_t out_param1;
                         CtSgwWANConnectionInfo_t target_param1;
			 char name;

                         cJSON *target = cJSON_GetObjectItem(testcase,"target");
			 cJSON *in = cJSON_GetObjectItem(testcase,"in");
                         strcpy(name,cJSON_GetObjectItem(in, "name")->valuestring);  
                         
                         return_value = CtSgwGetWANConnectionByName(&name,&out_param1);       
                         Check_return_result(return_value,atoi(return_target)); 
                         strcpy(target_param1.Index,cJSON_GetObjectItem(target, "Index")->valuestring);  
                         strcpy(target_param1.IfName,cJSON_GetObjectItem(target, "IfName")->valuestring);   
                         strcpy(target_param1.ServiceList,cJSON_GetObjectItem(target, "ServiceList")->valuestring);   
			 strcpy(target_param1.ConnectionType,cJSON_GetObjectItem(target, "ConnectionType")->valuestring);  
                         strcpy(target_param1.VLANID,cJSON_GetObjectItem(target, "VLANID")->valuestring);   
                         strcpy(target_param1.VLAN8021P,cJSON_GetObjectItem(target, "VLAN8021P")->valuestring);  
			 strcpy(target_param1.Protocol,cJSON_GetObjectItem(target, "Protocol")->valuestring);  
                         strcpy(target_param1.ConnectionStatus,cJSON_GetObjectItem(target, "ConnectionStatus")->valuestring);   
                         strcpy(target_param1.IPAddress,cJSON_GetObjectItem(target, "IPAddress")->valuestring);   
			 strcpy(target_param1.SubnetMask,cJSON_GetObjectItem(target, "SubnetMask")->valuestring);  
                         strcpy(target_param1.Gateway,cJSON_GetObjectItem(target, "Gateway")->valuestring);   
                         strcpy(target_param1.DNS1,cJSON_GetObjectItem(target, "DNS1")->valuestring);    
			 strcpy(target_param1.DNS2,cJSON_GetObjectItem(target, "DNS2")->valuestring);  
                         strcpy(target_param1.IPV6_ConnectionStatus,cJSON_GetObjectItem(target, "IPV6_ConnectionStatus")->valuestring);   
                         strcpy(target_param1.IPV6_IPAddress,cJSON_GetObjectItem(target, "IPV6_IPAddress")->valuestring);   
			 strcpy(target_param1.IPV6_PrefixLength,cJSON_GetObjectItem(target, "IPV6_PrefixLength")->valuestring);  
                         strcpy(target_param1.IPV6_Gateway,cJSON_GetObjectItem(target, "IPV6_Gateway")->valuestring);   
                         strcpy(target_param1.IPV6_DNS1,cJSON_GetObjectItem(target, "IPV6_DNS1")->valuestring);  
			 strcpy(target_param1.IPV6_DNS2,cJSON_GetObjectItem(target, "IPV6_DNS2")->valuestring);  
                         strcpy(target_param1.IPV6_Prefix,cJSON_GetObjectItem(target, "IPV6_Prefix")->valuestring);   
                         strcpy(target_param1.RxBytes,cJSON_GetObjectItem(target, "RxBytes")->valuestring);   
			 strcpy(target_param1.TxBytes,cJSON_GetObjectItem(target, "TxBytes")->valuestring);  
                         strcpy(target_param1.RxPkts,cJSON_GetObjectItem(target, "RxPkts")->valuestring);   
                         strcpy(target_param1.TxPkts,cJSON_GetObjectItem(target, "TxPkts")->valuestring);  
              		 strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(target, "path"),"str")->valuestring);

                         CheckCtSgwWANConnectionInfo_t(&out_param1,&target_param1);

   }
	   break;

   case 6:{
                         CtSgwWANConnectionInfo_t out_param1;
                         CtSgwWANConnectionInfo_t target_param1;
                         cJSON *target = cJSON_GetObjectItem(testcase,"target");
                         
                         return_value = CtSgwGetInternetWANConnection(&out_param1);       
                         Check_return_result(return_value,atoi(return_target)); 
                         strcpy(target_param1.Index,cJSON_GetObjectItem(target, "Index")->valuestring);  
                         strcpy(target_param1.IfName,cJSON_GetObjectItem(target, "IfName")->valuestring);   
                         strcpy(target_param1.ServiceList,cJSON_GetObjectItem(target, "ServiceList")->valuestring);   
			 strcpy(target_param1.ConnectionType,cJSON_GetObjectItem(target, "ConnectionType")->valuestring);  
                         strcpy(target_param1.VLANID,cJSON_GetObjectItem(target, "VLANID")->valuestring);   
                         strcpy(target_param1.VLAN8021P,cJSON_GetObjectItem(target, "VLAN8021P")->valuestring);  
			 strcpy(target_param1.Protocol,cJSON_GetObjectItem(target, "Protocol")->valuestring);  
                         strcpy(target_param1.ConnectionStatus,cJSON_GetObjectItem(target, "ConnectionStatus")->valuestring);   
                         strcpy(target_param1.IPAddress,cJSON_GetObjectItem(target, "IPAddress")->valuestring);   
			 strcpy(target_param1.SubnetMask,cJSON_GetObjectItem(target, "SubnetMask")->valuestring);  
                         strcpy(target_param1.Gateway,cJSON_GetObjectItem(target, "Gateway")->valuestring);   
                         strcpy(target_param1.DNS1,cJSON_GetObjectItem(target, "DNS1")->valuestring);    
			 strcpy(target_param1.DNS2,cJSON_GetObjectItem(target, "DNS2")->valuestring);  
                         strcpy(target_param1.IPV6_ConnectionStatus,cJSON_GetObjectItem(target, "IPV6_ConnectionStatus")->valuestring);   
                         strcpy(target_param1.IPV6_IPAddress,cJSON_GetObjectItem(target, "IPV6_IPAddress")->valuestring);   
			 strcpy(target_param1.IPV6_PrefixLength,cJSON_GetObjectItem(target, "IPV6_PrefixLength")->valuestring);  
                         strcpy(target_param1.IPV6_Gateway,cJSON_GetObjectItem(target, "IPV6_Gateway")->valuestring);   
                         strcpy(target_param1.IPV6_DNS1,cJSON_GetObjectItem(target, "IPV6_DNS1")->valuestring);  
			 strcpy(target_param1.IPV6_DNS2,cJSON_GetObjectItem(target, "IPV6_DNS2")->valuestring);  
                         strcpy(target_param1.IPV6_Prefix,cJSON_GetObjectItem(target, "IPV6_Prefix")->valuestring);   
                         strcpy(target_param1.RxBytes,cJSON_GetObjectItem(target, "RxBytes")->valuestring);   
			 strcpy(target_param1.TxBytes,cJSON_GetObjectItem(target, "TxBytes")->valuestring);  
                         strcpy(target_param1.RxPkts,cJSON_GetObjectItem(target, "RxPkts")->valuestring);   
                         strcpy(target_param1.TxPkts,cJSON_GetObjectItem(target, "TxPkts")->valuestring);  
              		 strcpy(target_param1.path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(target, "path"),"str")->valuestring);

                         CheckCtSgwWANConnectionInfo_t(&out_param1,&target_param1);

   }
	   break;

   case 7:{
                         CtSgwWiFiInfo_t out_param1;   
                         CtSgwWiFiInfo_t target_param1;
                         cJSON *target = cJSON_GetObjectItem(testcase,"target");
                         
                         return_value = CtSgwGetWiFiInfo(&out_param4);       
                         Check_return_result(return_value,atoi(return_target)); 
                         strcpy(target_param1.SSID,cJSON_GetObjectItem(target, "SSID")->valuestring);  
                         strcpy(target_param1.Enable,cJSON_GetObjectItem(target, "Enable")->valuestring);   
                         strcpy(target_param1.Channel,cJSON_GetObjectItem(target, "Channel")->valuestring);   
			 strcpy(target_param1.PowerLevel,cJSON_GetObjectItem(target, "PowerLevel")->valuestring);  
                         strcpy(target_param1.PowerLevel_5G,cJSON_GetObjectItem(target, "PowerLevel_5G")->valuestring);   
                         strcpy(target_param1.PWD,cJSON_GetObjectItem(target, "PWD")->valuestring); 
	
			 strcpy(target_param1.Encrypt,cJSON_GetObjectItem(target, "Encrypt")->valuestring);  
                         strcpy(target_param1.RxBytes,cJSON_GetObjectItem(target, "RxBytes")->valuestring);   
                         strcpy(target_param1.RxPkts,cJSON_GetObjectItem(target, "RxPkts")->valuestring);   
			 strcpy(target_param1.RxErrorPkts,cJSON_GetObjectItem(target, "RxErrorPkts")->valuestring);  
                         strcpy(target_param1.RxDropPkts,cJSON_GetObjectItem(target, "RxDropPkts")->valuestring);   
                         strcpy(target_param1.TxBytes,cJSON_GetObjectItem(target, "TxBytes")->valuestring);   

			 strcpy(target_param1.TxPkts,cJSON_GetObjectItem(target, "TxPkts")->valuestring);  
                         strcpy(target_param1.TxErrorPkts,cJSON_GetObjectItem(target, "TxErrorPkts")->valuestring);   
                         strcpy(target_param1.TxDropPkts,cJSON_GetObjectItem(target, "TxDropPkts")->valuestring);   
                 
                         CheckCtSgwWiFiInfo_t(&out_param1,&target_param1);
   }
           break;
   case 8:{
                         CtSgwPONInfo_t out_param1;
                         CtSgwPONInfo_t target_param1;
                         cJSON *target = cJSON_GetObjectItem(testcase,"target");
                         
                         return_value = CtSgwGetPONInfo(&out_param5);       
                         Check_return_result(return_value,atoi(return_target)); 
                         strcpy(target_param1.LOID,cJSON_GetObjectItem(target, "LOID")->valuestring);  
                         strcpy(target_param1.Password,cJSON_GetObjectItem(target, "Password")->valuestring);   
                         strcpy(target_param1.Temperature,cJSON_GetObjectItem(target, "Temperature")->valuestring);   
			 strcpy(target_param1.Vottage,cJSON_GetObjectItem(target, "Vottage")->valuestring);  
                         strcpy(target_param1.Current,cJSON_GetObjectItem(target, "Current")->valuestring);   
                         strcpy(target_param1.TxPower,cJSON_GetObjectItem(target, "TxPower")->valuestring);  
			 strcpy(target_param1.RxPower,cJSON_GetObjectItem(target, "RxPower")->valuestring);  
                         strcpy(target_param1.SupportPONStatusQuery,cJSON_GetObjectItem(target, "SupportPONStatusQuery")->valuestring);   
                         strcpy(target_param1.PONStatus,cJSON_GetObjectItem(target, "PONStatus")->valuestring);   
                 
                         CheckCtSgwPONInfo_t(&out_param1,&target_param1);



   } 
           break;
   case 9:{
                         CtSgwVoIPInfo_t out_param1;
                         CtSgwVoIPInfo_t target_param1;
                         cJSON *target = cJSON_GetObjectItem(testcase,"target");
                         
                         return_value = CtSgwGetVoIPInfo(&out_param1);       
                         Check_return_result(return_value,atoi(return_target)); 
                         strcpy(target_param1.VoIPName1,cJSON_GetObjectItem(target, "VoIPName1")->valuestring);  
                         strcpy(target_param1.VoIPName2,cJSON_GetObjectItem(target, "VoIPName2")->valuestring);   
                         strcpy(target_param1.Line1Status,cJSON_GetObjectItem(target, "Line1Status")->valuestring);  
			 strcpy(target_param1.Line2Status,cJSON_GetObjectItem(target, "Line2Status")->valuestring);  
              
    
                         CheckCtSgwVoIPInfo_t(&out_param1,&target_param1);



   }
           break;   
   case 10:{

                        CtSgwLANHostMgr_t out_param1;
                        CtSgwLANHostMgr_t target_param1
                        cJSON *target = cJSON_GetObjectItem(testcase,"target");
                         
                        return_value = CtSgwGetLANHostMgr(&out_param1);       
                        Check_return_result(return_value,atoi(return_target)); 
                        strcpy(target_param1.EnableStats,cJSON_GetObjectItem(target, "EnableStats")->valuestring);  
                       
                        CheckCtSgwLANHostMgr_t(&out_param1,&target_param1);   


   }
           break;
   case 11:{
                        CtSgwLANHostMgr_t target_param1;
                        cJSON *in = cJSON_GetObjectItem(testcase,"in");
                        strcpy(target_param1.EnableStats,cJSON_GetObjectItem(in, "EnableStats")->valuestring);

                        return_value = CtSgwSetLANHostMgr(&target_param1);       
                        Check_return_result(return_value,atoi(return_target));                       

   }
           break;
  
  
   case 12:{
                       CtSgwLANHost_t* out_param1;
		       int out_count;
		       int target_count;
                       CtSgwLANHost_t target_param1;    
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
                         
                       return_value = CtSgwGetLANHostObjs(&out_param1,&out_count);       
                       Check_return_result(return_value,atoi(return_target)); 

		       cJSON * CtSgwLANHost = cJSON_GetObjectItem(target, "CtSgwLANHost_t");

		       strcpy(target_count,cJSON_GetObjectItem(target, "count")->valuestring);
		       Check_int(out_count,atoi(target_count));

        	       int index=0;
		       for (index = 0; index < cJSON_GetArraySize(CtSgwLANHost); index++)
		       {
			strcpy(target_param1.MAC,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwLANHost, index), "MAC")->valuestring);  
		        strcpy(target_param1.DevName,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwLANHost, index), "DevName")->valuestring);  
			strcpy(target_param1.DenyInternetAccess,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwLANHost, index), "DenyInternetAccess")->valuestring);  
			strcpy(target_param1.DenyStorageAccess,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwLANHost, index), "DenyStorageAccess")->valuestring);  
			strcpy(target_param1.MaxUSBandwidth,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwLANHost, index), "MaxUSBandwidth")->valuestring);  
			strcpy(target_param1.MaxDSBandwidth,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwLANHost, index), "MaxDSBandwidth")->valuestring);  
			strcpy(target_param1.USBandwidth,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwLANHost, index), "USBandwidth")->valuestring);  
			
			strcpy(target_param1.DSBandwidth,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwLANHost, index), "DSBandwidth")->valuestring);  
			strcpy(target_param1.DevType,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwLANHost, index), "DevType")->valuestring);  
			strcpy(target_param1.IP,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwLANHost, index), "IP")->valuestring);  
			strcpy(target_param1.ConnectionType,cJSON_GetObjectItem(target, "ConnectionType")->valuestring);  
			strcpy(target_param1.Port,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwLANHost, index), "Port")->valuestring);  
                       
			strcpy(target_param1.Brand,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwLANHost, index), "Brand")->valuestring);  
			strcpy(target_param1.OS,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwLANHost, index), "OS")->valuestring);  
			strcpy(target_param1.OnlineTime,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwLANHost, index), "OnlineTime")->valuestring);  
		       }
  
                       CheckCtSgwLANHost_t(&out_param1,&target_param1);   

   }
         break;

  
   case 13:{
                       CtSgwLANHost_t out_param1;
		       CtSgwObjPath_t path;
                       CtSgwLANHost_t target_param1;    
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
		       cJSON *in = cJSON_GetObjectItem(testcase,"in");
                       strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring); 

                       return_value = CtSgwGetLANHost(path,&out_param1);       
                       Check_return_result(return_value,atoi(return_target)); 
                       strcpy(target_param1.MAC,cJSON_GetObjectItem(target, "MAC")->valuestring);  
		       strcpy(target_param1.DevName,cJSON_GetObjectItem(target, "DevName")->valuestring);  
			strcpy(target_param1.DenyInternetAccess,cJSON_GetObjectItem(target, "DenyInternetAccess")->valuestring);  
			strcpy(target_param1.DenyStorageAccess,cJSON_GetObjectItem(target, "DenyStorageAccess")->valuestring);  
			strcpy(target_param1.MaxUSBandwidth,cJSON_GetObjectItem(target, "MaxUSBandwidth")->valuestring);  
			strcpy(target_param1.MaxDSBandwidth,cJSON_GetObjectItem(target, "MaxDSBandwidth")->valuestring);  
			strcpy(target_param1.USBandwidth,cJSON_GetObjectItem(target, "USBandwidth")->valuestring);  
			
			strcpy(target_param1.DSBandwidth,cJSON_GetObjectItem(target, "DSBandwidth")->valuestring);  
			strcpy(target_param1.DevType,cJSON_GetObjectItem(target, "DevType")->valuestring);  
			strcpy(target_param1.IP,cJSON_GetObjectItem(target, "IP")->valuestring);  
			strcpy(target_param1.ConnectionType,cJSON_GetObjectItem(target, "ConnectionType")->valuestring);  
			strcpy(target_param1.Port,cJSON_GetObjectItem(target, "Port")->valuestring);  
                       
			strcpy(target_param1.Brand,cJSON_GetObjectItem(target, "Brand")->valuestring);  
			strcpy(target_param1.OS,cJSON_GetObjectItem(target, "OS")->valuestring);  
			strcpy(target_param1.OnlineTime,cJSON_GetObjectItem(target, "OnlineTime")->valuestring);  
			
    
                       CheckCtSgwLANHost_t(&out_param1,&target_param1);   

   }
         break;

   case 14:{
                       CtSgwLANHost_t out_param1;
                       CtSgwLANHost_t target_param1;    
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
                         
                       return_value = CtSgwSetLANHost(&out_param1);       
                       Check_return_result(return_value,atoi(return_target)); 
                       strcpy(target_param1.MAC,cJSON_GetObjectItem(target, "MAC")->valuestring);  
		       strcpy(target_param1.DevName,cJSON_GetObjectItem(target, "DevName")->valuestring);  
			strcpy(target_param1.DenyInternetAccess,cJSON_GetObjectItem(target, "DenyInternetAccess")->valuestring);  
			strcpy(target_param1.DenyStorageAccess,cJSON_GetObjectItem(target, "DenyStorageAccess")->valuestring);  
			strcpy(target_param1.MaxUSBandwidth,cJSON_GetObjectItem(target, "MaxUSBandwidth")->valuestring);  
			strcpy(target_param1.MaxDSBandwidth,cJSON_GetObjectItem(target, "MaxDSBandwidth")->valuestring);  
			strcpy(target_param1.USBandwidth,cJSON_GetObjectItem(target, "USBandwidth")->valuestring);  
			
			strcpy(target_param1.DSBandwidth,cJSON_GetObjectItem(target, "DSBandwidth")->valuestring);  
			strcpy(target_param1.DevType,cJSON_GetObjectItem(target, "DevType")->valuestring);  
			strcpy(target_param1.IP,cJSON_GetObjectItem(target, "IP")->valuestring);  
			strcpy(target_param1.ConnectionType,cJSON_GetObjectItem(target, "ConnectionType")->valuestring);  
			strcpy(target_param1.Port,cJSON_GetObjectItem(target, "Port")->valuestring);  
                       
			strcpy(target_param1.Brand,cJSON_GetObjectItem(target, "Brand")->valuestring);  
			strcpy(target_param1.OS,cJSON_GetObjectItem(target, "OS")->valuestring);  
			strcpy(target_param1.OnlineTime,cJSON_GetObjectItem(target, "OnlineTime")->valuestring);  
			
    
                       CheckCtSgwLANHost_t(&out_param1,&target_param1);   

   }
         break;

    case 15:{
                       char url[MAX_URL_LEN+1];
                       cJSON *in = cJSON_GetObjectItem(testcase,"in");
                       
		       strcpy(url,cJSON_GetObjectItem(in, "url")->valuestring); 
                       return_value = CtSgwSetHttpDownloadTestURL(url);       
                       Check_return_result(return_value,atoi(return_target)); 
  
   }
         break;

     case 16:{
                       char out_url[MAX_URL_LEN+1];
		       char target_url[MAX_URL_LEN+1];
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
                       
                       return_value = CtSgwGetHttpDownloadTestURL(out_url);       
                       Check_return_result(return_value,atoi(return_target)); 

		       strcpy(target_url,cJSON_GetObjectItem(target, "url")->valuestring); 
		       Check_char(out_url,target_url);
  
   }
         break;
   
    case 17:{                   
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
                       
                       return_value = CtSgwStartHttpDownloadTest(void);       
                       Check_return_result(return_value,atoi(return_target)); 
  
   }
         break;
   
   case 18:{
                       CtSgwHttpDownloadTestResult_t out_param1;
                       CtSgwHttpDownloadTestResult_t target_param1;
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
                         
                       return_value = CtSgwGetHttpDownloadTestResult(&out_param1);       
                       Check_return_result(return_value,atoi(return_target)); 
                       strcpy(target_param1.Status,cJSON_GetObjectItem(target, "Status")->valuestring);  
		       strcpy(target_param1.Result,cJSON_GetObjectItem(target, "Result")->valuestring);  
		       strcpy(target_param1.URL,cJSON_GetObjectItem(target, "URL")->valuestring);  
   
                       CheckCtSgwHttpDownloadTestResult_t(&out_param1,&target_param1);   



   }
         break;

   case 19:{         
		       CtSgwObjPath_t wanconn;
		       gchar dest;
		       guint32 len;
		       guint32 time;
		       
                       cJSON *in = cJSON_GetObjectItem(testcase,"in");
                       strcpy(wanconn,cJSON_GetObjectItem(in, "wanconn")->valuestring); 
			strcpy(dest,cJSON_GetObjectItem(in, "dest")->valuestring); 
			strcpy(len,cJSON_GetObjectItem(in, "len")->valuestring); 
			strcpy(time,cJSON_GetObjectItem(in, "time")->valuestring); 
                       return_value = CtSgwStartPingTest(&wanconn,&dest,len,time);  
     
                       Check_return_result(return_value,atoi(return_target)); 
  
   }
         break;
   
   case 20:{
                       CtSgwPingTestResult_t out_param1;
                       CtSgwPingTestResult_t target_param1;
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
                         
                       return_value = CtSgwGetPingTestResult(&out_param1);       
                       Check_return_result(return_value,atoi(return_target)); 
                       strcpy(target_param1.PingStatus,cJSON_GetObjectItem(target, "PingStatus")->valuestring);  
                       strcpy(target_param1.PingResult,cJSON_GetObjectItem(target, "PingResult")->valuestring);  
                       
                       CheckCtSgwPingTestResult_t(&out_param1,&target_param1);   

   }
         break;
   case 21:{
                       CtSgwObjPath_t wanconn;
		       char dest;
                       cJSON *in = cJSON_GetObjectItem(testcase,"in");

			strcpy(wanconn.PingResult,cJSON_GetObjectItem(in, "wanconn")->valuestring); 
			strcpy(dest.PingResult,cJSON_GetObjectItem(in, "dest")->valuestring);  
                         
                       return_value = CtSgwStartTraceRouteTest(&wanconn, &dest);       
                       Check_return_result(return_value,atoi(return_target)); 
                       
   }
         break;
   case 22:{
                       CtSgwTraceRouteTestResult_t out_param1;
                       CtSgwTraceRouteTestResult_t target_param1;
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
                         
                       return_value = CtSgwGetTraceRouteTestResult(&out_param1);       
                       Check_return_result(return_value,atoi(return_target)); 
                       strcpy(target_param1.TraceStatus,cJSON_GetObjectItem(target, "TraceStatus")->valuestring);  
                       strcpy(target_param1.TraceResult,cJSON_GetObjectItem(target, "TraceResult")->valuestring);  
     
                       CheckCtSgwTraceRouteTestResult_t(&out_param1,&target_param1);   

   }
         break;
   case 23:{                      
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
                         
                       return_value = CtSgwStartInformTest(void);       
                       Check_return_result(return_value,atoi(return_target)); 

   }
         break;

   case 24:{
                       CtSgwInformTestResult_t out_param1;
                       CtSgwInformTestResult_t target_param1;
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
                         
                       return_value = CtSgwGetInformTestResult(&out_param1);       
                       Check_return_result(return_value,atoi(return_target)); 
                       strcpy(target_param1.result,cJSON_GetObjectItem(target, "result")->valuestring);  
                     
    
                       CheckCtSgwInformTestResult_t(&out_param1,&target_param1);   

   }
         break;
    case 25:{                      
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
                         
                       return_value = CtSgwStartMCTest(void);       
                       Check_return_result(return_value,atoi(return_target)); 

   }
         break;

   case 26:{
                       CtSgwMCTestResult_t out_param1;
                       CtSgwMCTestResult_t target_param1;
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
                         
                       return_value = CtSgwGetMCTestResult(&out_param1);       
                       Check_return_result(return_value,atoi(return_target)); 
                       strcpy(target_param1.DialStatus,cJSON_GetObjectItem(target, "DialStatus")->valuestring);  
                       strcpy(target_param1.DialResult,cJSON_GetObjectItem(target, "DialResult")->valuestring);  
    
                       CheckCtSgwMCTestResult_t(&out_param1,&target_param1);   

   }
         break;

   case 27:{
                       CtSgwPWConfig_t target_param1;
                       cJSON *in = cJSON_GetObjectItem(testcase,"in");

		       strcpy(target_param1.Enable,cJSON_GetObjectItem(in, "Enable")->valuestring);  
                       strcpy(target_param1.Width,cJSON_GetObjectItem(in, "Width")->valuestring);  
		       strcpy(target_param1.Height,cJSON_GetObjectItem(in, "Height")->valuestring);
		       strcpy(target_param1.Place,cJSON_GetObjectItem(in, "Place")->valuestring);
		       strcpy(target_param1.URL,cJSON_GetObjectItem(in, "URL")->valuestring);  
                       strcpy(target_param1.Time,cJSON_GetObjectItem(in, "Time")->valuestring);  
		       strcpy(target_param1.Status,cJSON_GetObjectItem(in, "Status")->valuestring);
                         
                       return_value = CtSgwSetPW(&target_param1);       
                       Check_return_result(return_value,atoi(return_target));  

   }
         break;

   case 28:{
                       CtSgwPWConfig_t out_param1;
                       CtSgwPWConfig_t target_param1;
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
                         
                       return_value = CtSgwGetPW(&out_param1);       
                       Check_return_result(return_value,atoi(return_target)); 
                       strcpy(target_param1.Enable,cJSON_GetObjectItem(target, "Enable")->valuestring);  
                       strcpy(target_param1.Width,cJSON_GetObjectItem(target, "Width")->valuestring);  
		       strcpy(target_param1.Height,cJSON_GetObjectItem(target, "Height")->valuestring);
		       strcpy(target_param1.Place,cJSON_GetObjectItem(target, "Place")->valuestring);
		       strcpy(target_param1.URL,cJSON_GetObjectItem(target, "URL")->valuestring);  
                       strcpy(target_param1.Time,cJSON_GetObjectItem(target, "Time")->valuestring);  
		       strcpy(target_param1.Status,cJSON_GetObjectItem(target, "Status")->valuestring);
    
                       CheckCtSgwPWConfig_t(&out_param1,&target_param1);   

   }
         break;

   case 29:{
                       CtSgw404Redir_t target_param1;
                       cJSON *in = cJSON_GetObjectItem(testcase,"in");

                       strcpy(target_param1.DownURL,cJSON_GetObjectItem(in, "DownURL")->valuestring);     
                       return_value = CtSgwSet404Redir(&target_param1);    
   
                       Check_return_result(return_value,atoi(return_target)); 

   }
         break;
   case 30:{
                       CtSgw404Redir_t out_param1;
                       CtSgw404Redir_t target_param1;
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
                         
                       return_value = CtSgwGet404Redir(&out_param1);       
                       Check_return_result(return_value,atoi(return_target)); 
                       strcpy(target_param1.DownURL,cJSON_GetObjectItem(target, "DownURL")->valuestring);  
    
                       CheckCtSgw404Redir_t(&out_param1,&target_param1);   

   }
         break;
   case 31:{
                       CtSgwWPS_t target_param1;
                       cJSON *in = cJSON_GetObjectItem(testcase,"in");

                       strcpy(target_param1.Enable,cJSON_GetObjectItem(in, "Enable")->valuestring); 
		       strcpy(target_param1.SSID,cJSON_GetObjectItem(in, "SSID")->valuestring);  
		       strcpy(target_param1.TimeOut,cJSON_GetObjectItem(in, "TimeOut")->valuestring);  
		       strcpy(target_param1.WPSStatus,cJSON_GetObjectItem(in, "WPSStatus")->valuestring);  
		       strcpy(target_param1.DevInfo,cJSON_GetObjectItem(in, "DevInfo")->valuestring);   
                        
                       return_value = CtSgwSetWPS(&target_param1);       
                       Check_return_result(return_value,atoi(return_target)); 

   }
         break;

   case 32:{
                       CtSgwWPS_t out_param1;
                       CtSgwWPS_t target_param1;
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
                         
                       return_value = CtSgwGetWPS(&out_param1);       
                       Check_return_result(return_value,atoi(return_target)); 
                       strcpy(target_param1.Enable,cJSON_GetObjectItem(target, "Enable")->valuestring); 
		       strcpy(target_param1.SSID,cJSON_GetObjectItem(target, "SSID")->valuestring);  
		       strcpy(target_param1.TimeOut,cJSON_GetObjectItem(target, "TimeOut")->valuestring);  
		       strcpy(target_param1.WPSStatus,cJSON_GetObjectItem(target, "WPSStatus")->valuestring);  
		       strcpy(target_param1.DevInfo,cJSON_GetObjectItem(target, "DevInfo")->valuestring);   
    
                       CheckCtSgwWPS_t(&out_param1,&target_param1);   


   }
         break;


     case 33:{
                       CtSgwWLANDevice_t* out_param1;
		       guint32 out_count;
		       guint32 target_count;
                       CtSgwWLANDevice_t target_param1;
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
                         
                       return_value = CtSgwGetWLANDeviceObjs(&out_param1,&out_count);       
                       Check_return_result(return_value,atoi(return_target)); 

		       cJSON * CtSgwWLANDevice = cJSON_GetObjectItem(target, "CtSgwWLANDevice_t");
		       strcpy(target_count,cJSON_GetObjectItem(target, "count")->valuestring);
		       Check_int(out_count,atoi(target_count));

		       int index=0;
		       for (index = 0; index < cJSON_GetArraySize(CtSgwWLANDevice); index++)
		       {
                       strcpy(target_param1.SSID,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWLANDevice, index), "SSID")->valuestring); 
		       strcpy(target_param1.Enable,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWLANDevice, index), "Enable")->valuestring);  
		       strcpy(target_param1.Channel,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWLANDevice, index), "Channel")->valuestring);  
		       strcpy(target_param1.ChannelInUse,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWLANDevice, index), "ChannelInUse")->valuestring);  
		       strcpy(target_param1.BeaconType,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWLANDevice, index), "BeaconType")->valuestring);   
		       strcpy(target_param1.Standard,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWLANDevice, index), "Standard")->valuestring); 
		       strcpy(target_param1.WEPEncryptionLevel,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWLANDevice, index), "WEPEncryptionLevel")->valuestring);  
		       strcpy(target_param1.BasicAuthenticationMode,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWLANDevice, index), "BasicAuthenticationMode")->valuestring);  
		       strcpy(target_param1.WPAEncryptionModes,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWLANDevice, index), "WPAEncryptionModes")->valuestring);  
		       strcpy(target_param1.SSIDHide,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWLANDevice, index), "SSIDHide")->valuestring);   

		       strcpy(target_param1.RFBand,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWLANDevice, index), "RFBand")->valuestring); 
		       strcpy(target_param1.ChannelWidth,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWLANDevice, index), "ChannelWidth")->valuestring);  
		       strcpy(target_param1.GuardInterval,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWLANDevice, index), "GuardInterval")->valuestring);  
		       strcpy(target_param1.RetryTimeout,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWLANDevice, index), "RetryTimeout")->valuestring);  
		       strcpy(target_param1.Powerlevel,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWLANDevice, index), "Powerlevel")->valuestring);   
		       strcpy(target_param1.PowerLevel_5G,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWLANDevice, index), "PowerLevel_5G")->valuestring); 
		       strcpy(target_param1.WEPEncryptionLevel,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWLANDevice, index), "PowerValue")->valuestring);  
		       strcpy(target_param1.APModuleEnable,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWLANDevice, index), "APModuleEnable")->valuestring);  
		       strcpy(target_param1.WPSKeyWord,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWLANDevice, index), "WPSKeyWord")->valuestring);  
		       strcpy(target_param1.PWD,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWLANDevice, index), "PWD")->valuestring); 
		       }
   
                       CheckCtSgwWLANDevice_t(&out_param1,&target_param1);   

   }
         break;
     case 34:{
                       CtSgwWLANDevice_t out_param1;
		       CtSgwObjPath_t path;
                       CtSgwWLANDevice_t target_param1;
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
		       cJSON *in = cJSON_GetObjectItem(testcase,"in");
                       strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring); 
                         
                       return_value = CtSgwGetWLANDevice(path,&out_param1);       
                       Check_return_result(return_value,atoi(return_target)); 
                       strcpy(target_param1.SSID,cJSON_GetObjectItem(target, "SSID")->valuestring); 
		       strcpy(target_param1.Enable,cJSON_GetObjectItem(target, "Enable")->valuestring);  
		       strcpy(target_param1.Channel,cJSON_GetObjectItem(target, "Channel")->valuestring);  
		       strcpy(target_param1.ChannelInUse,cJSON_GetObjectItem(target, "ChannelInUse")->valuestring);  
		       strcpy(target_param1.BeaconType,cJSON_GetObjectItem(target, "BeaconType")->valuestring);   
		       strcpy(target_param1.Standard,cJSON_GetObjectItem(target, "Standard")->valuestring); 
		       strcpy(target_param1.WEPEncryptionLevel,cJSON_GetObjectItem(target, "WEPEncryptionLevel")->valuestring);  
		       strcpy(target_param1.BasicAuthenticationMode,cJSON_GetObjectItem(target, "BasicAuthenticationMode")->valuestring);  
		       strcpy(target_param1.WPAEncryptionModes,cJSON_GetObjectItem(target, "WPAEncryptionModes")->valuestring);  
		       strcpy(target_param1.SSIDHide,cJSON_GetObjectItem(target, "SSIDHide")->valuestring);   

		       strcpy(target_param1.RFBand,cJSON_GetObjectItem(target, "RFBand")->valuestring); 
		       strcpy(target_param1.ChannelWidth,cJSON_GetObjectItem(target, "ChannelWidth")->valuestring);  
		       strcpy(target_param1.GuardInterval,cJSON_GetObjectItem(target, "GuardInterval")->valuestring);  
		       strcpy(target_param1.RetryTimeout,cJSON_GetObjectItem(target, "RetryTimeout")->valuestring);  
		       strcpy(target_param1.Powerlevel,cJSON_GetObjectItem(target, "Powerlevel")->valuestring);   
		       strcpy(target_param1.PowerLevel_5G,cJSON_GetObjectItem(target, "PowerLevel_5G")->valuestring); 
		       strcpy(target_param1.WEPEncryptionLevel,cJSON_GetObjectItem(target, "PowerValue")->valuestring);  
		       strcpy(target_param1.APModuleEnable,cJSON_GetObjectItem(target, "APModuleEnable")->valuestring);  
		       strcpy(target_param1.WPSKeyWord,cJSON_GetObjectItem(target, "WPSKeyWord")->valuestring);  
		       strcpy(target_param1.PWD,cJSON_GetObjectItem(target, "PWD")->valuestring); 
    
                       CheckCtSgwWLANDevice_t(&out_param1,&target_param1);   

   }
         break;
     case 35:{
                       CtSgwWLANDevice_t out_param1;
		       char ssid;
                       CtSgwWLANDevice_t target_param1;
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
                       cJSON *in = cJSON_GetObjectItem(testcase,"in");
		       strcpy(ssid,cJSON_GetObjectItem(in, "ssid")->valuestring); 
                         
                       return_value = CtSgwGetWLANDeviceBySSID(&ssid,&out_param1);       
                       Check_return_result(return_value,atoi(return_target)); 
                       strcpy(target_param1.SSID,cJSON_GetObjectItem(target, "SSID")->valuestring); 
		       strcpy(target_param1.Enable,cJSON_GetObjectItem(target, "Enable")->valuestring);  
		       strcpy(target_param1.Channel,cJSON_GetObjectItem(target, "Channel")->valuestring);  
		       strcpy(target_param1.ChannelInUse,cJSON_GetObjectItem(target, "ChannelInUse")->valuestring);  
		       strcpy(target_param1.BeaconType,cJSON_GetObjectItem(target, "BeaconType")->valuestring);   
		       strcpy(target_param1.Standard,cJSON_GetObjectItem(target, "Standard")->valuestring); 
		       strcpy(target_param1.WEPEncryptionLevel,cJSON_GetObjectItem(target, "WEPEncryptionLevel")->valuestring);  
		       strcpy(target_param1.BasicAuthenticationMode,cJSON_GetObjectItem(target, "BasicAuthenticationMode")->valuestring);  
		       strcpy(target_param1.WPAEncryptionModes,cJSON_GetObjectItem(target, "WPAEncryptionModes")->valuestring);  
		       strcpy(target_param1.SSIDHide,cJSON_GetObjectItem(target, "SSIDHide")->valuestring);   

		       strcpy(target_param1.RFBand,cJSON_GetObjectItem(target, "RFBand")->valuestring); 
		       strcpy(target_param1.ChannelWidth,cJSON_GetObjectItem(target, "ChannelWidth")->valuestring);  
		       strcpy(target_param1.GuardInterval,cJSON_GetObjectItem(target, "GuardInterval")->valuestring);  
		       strcpy(target_param1.RetryTimeout,cJSON_GetObjectItem(target, "RetryTimeout")->valuestring);  
		       strcpy(target_param1.Powerlevel,cJSON_GetObjectItem(target, "Powerlevel")->valuestring);   
		       strcpy(target_param1.PowerLevel_5G,cJSON_GetObjectItem(target, "PowerLevel_5G")->valuestring); 
		       strcpy(target_param1.WEPEncryptionLevel,cJSON_GetObjectItem(target, "PowerValue")->valuestring);  
		       strcpy(target_param1.APModuleEnable,cJSON_GetObjectItem(target, "APModuleEnable")->valuestring);  
		       strcpy(target_param1.WPSKeyWord,cJSON_GetObjectItem(target, "WPSKeyWord")->valuestring);  
		       strcpy(target_param1.PWD,cJSON_GetObjectItem(target, "PWD")->valuestring); 
    
                       CheckCtSgwWLANDevice_t(&out_param1,&target_param1);   

   }
         break;
     case 36:{
                       CtSgwWLANDevice_t out_param1;
                       CtSgwWLANDevice_t target_param1;
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
                         
                       return_value = CtSgwSetWLANDevice(&out_param1);       
                       Check_return_result(return_value,atoi(return_target)); 
                       strcpy(target_param1.SSID,cJSON_GetObjectItem(target, "SSID")->valuestring); 
		       strcpy(target_param1.Enable,cJSON_GetObjectItem(target, "Enable")->valuestring);  
		       strcpy(target_param1.Channel,cJSON_GetObjectItem(target, "Channel")->valuestring);  
		       strcpy(target_param1.ChannelInUse,cJSON_GetObjectItem(target, "ChannelInUse")->valuestring);  
		       strcpy(target_param1.BeaconType,cJSON_GetObjectItem(target, "BeaconType")->valuestring);   
		       strcpy(target_param1.Standard,cJSON_GetObjectItem(target, "Standard")->valuestring); 
		       strcpy(target_param1.WEPEncryptionLevel,cJSON_GetObjectItem(target, "WEPEncryptionLevel")->valuestring);  
		       strcpy(target_param1.BasicAuthenticationMode,cJSON_GetObjectItem(target, "BasicAuthenticationMode")->valuestring);  
		       strcpy(target_param1.WPAEncryptionModes,cJSON_GetObjectItem(target, "WPAEncryptionModes")->valuestring);  
		       strcpy(target_param1.SSIDHide,cJSON_GetObjectItem(target, "SSIDHide")->valuestring);   

		       strcpy(target_param1.RFBand,cJSON_GetObjectItem(target, "RFBand")->valuestring); 
		       strcpy(target_param1.ChannelWidth,cJSON_GetObjectItem(target, "ChannelWidth")->valuestring);  
		       strcpy(target_param1.GuardInterval,cJSON_GetObjectItem(target, "GuardInterval")->valuestring);  
		       strcpy(target_param1.RetryTimeout,cJSON_GetObjectItem(target, "RetryTimeout")->valuestring);  
		       strcpy(target_param1.Powerlevel,cJSON_GetObjectItem(target, "Powerlevel")->valuestring);   
		       strcpy(target_param1.PowerLevel_5G,cJSON_GetObjectItem(target, "PowerLevel_5G")->valuestring); 
		       strcpy(target_param1.WEPEncryptionLevel,cJSON_GetObjectItem(target, "PowerValue")->valuestring);  
		       strcpy(target_param1.APModuleEnable,cJSON_GetObjectItem(target, "APModuleEnable")->valuestring);  
		       strcpy(target_param1.WPSKeyWord,cJSON_GetObjectItem(target, "WPSKeyWord")->valuestring);  
		       strcpy(target_param1.PWD,cJSON_GetObjectItem(target, "PWD")->valuestring); 
    
                       CheckCtSgwWLANDevice_t(&out_param1,&target_param1);   

   }
         break;
   case 37:{
                       CtSgwWiFiTimer1_t* out_param1;
		       int out_count;
 		       int target_count;
                       CtSgwWiFiTimer1_t target_param1;
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
                         
                       return_value = CtSgwGetWiFiTimerObjs(&out_param1,&out_count);       
                       Check_return_result(return_value,atoi(return_target)); 
		       cJSON * CtSgwWiFiTimer1 = cJSON_GetObjectItem(target, "CtSgwWiFiTimer1_t");

		       strcpy(target_count,cJSON_GetObjectItem(target, "count")->valuestring);
		       Check_int(out_count,atoi(target_count));

		       int index=0;
		       for (index = 0; index < cJSON_GetArraySize(CtSgwWiFiTimer1); index++)
		       {
                       strcpy(target_param1.WeekDay,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWiFiTimer1, index), "WeekDay")->valuestring); 
		       strcpy(target_param1.Time,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWiFiTimer1, index), "Time")->valuestring);  
		       strcpy(target_param1.Active,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWiFiTimer1, index), "Active")->valuestring);  
		       strcpy(target_param1.Enable,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWiFiTimer1, index), "Enable")->valuestring);  
		       } 
		      
                       CheckCtSgwWiFiTimer1_t(&out_param1,&target_param1);   

   }
         break;

   case 38:{
                       CtSgwWiFiTimer1_t out_param1;
		       CtSgwObjPath_t path;
                       CtSgwWiFiTimer1_t target_param1;
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
		       cJSON *in = cJSON_GetObjectItem(testcase,"in");
                       strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring); 
                         
                       return_value = CtSgwGetWiFiTimer(path,&out_param1);       
                       Check_return_result(return_value,atoi(return_target)); 
                       strcpy(target_param1.WeekDay,cJSON_GetObjectItem(target, "WeekDay")->valuestring); 
		       strcpy(target_param1.Time,cJSON_GetObjectItem(target, "Time")->valuestring);  
		       strcpy(target_param1.Active,cJSON_GetObjectItem(target, "Active")->valuestring);  
		       strcpy(target_param1.Enable,cJSON_GetObjectItem(target, "Enable")->valuestring);  
		      
                       CheckCtSgwWiFiTimer1_t(&out_param1,&target_param1);   

   }
         break;

   case 39:{
                       CtSgwWiFiTimer1_t target_param1;
                       cJSON *in = cJSON_GetObjectItem(testcase,"in");

                       strcpy(target_param1.WeekDay,cJSON_GetObjectItem(in, "WeekDay")->valuestring); 
		       strcpy(target_param1.Time,cJSON_GetObjectItem(in, "Time")->valuestring);  
		       strcpy(target_param1.Active,cJSON_GetObjectItem(in, "Active")->valuestring);  
		       strcpy(target_param1.Enable,cJSON_GetObjectItem(in, "Enable")->valuestring);  
                         
                       return_value = CtSgwSetWiFiTimer(&target_param1);       
                       Check_return_result(return_value,atoi(return_target)); 

   }
         break;
   case 40:{
                       CtSgwWiFiTimer1_t target_param1;
                       cJSON *in = cJSON_GetObjectItem(testcase,"in");

                       strcpy(target_param1.WeekDay,cJSON_GetObjectItem(in, "WeekDay")->valuestring); 
		       strcpy(target_param1.Time,cJSON_GetObjectItem(in, "Time")->valuestring);  
		       strcpy(target_param1.Active,cJSON_GetObjectItem(in, "Active")->valuestring);  
		       strcpy(target_param1.Enable,cJSON_GetObjectItem(in, "Enable")->valuestring);  
                         
                       return_value = CtSgwAddWiFiTimer(&target_param1);       
                       Check_return_result(return_value,atoi(return_target)); 

   }
         break;
   case 41:{
                       CtSgwObjPath_t path;
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
		       cJSON *in = cJSON_GetObjectItem(testcase,"in");
                       strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring);                        
                       return_value = CtSgwDelWiFiTimer(path);       
                       Check_return_result(return_value,atoi(return_target)); 

   }
         break;


    case 42:{
                       CtSgwLED_t* out_param1;
		       int out_count;
		       int target_count;
                       CtSgwLED_t target_param1;
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
                         
                       return_value = CtSgwGetLEDObjs(&out_param1,&out_count);       
                       Check_return_result(return_value,atoi(return_target)); 

		       cJSON * CtSgwLED = cJSON_GetObjectItem(target, "CtSgwLED_t");

		       strcpy(target_count,cJSON_GetObjectItem(target, "count")->valuestring);
		       Check_int(out_count,atoi(target_count));

        	       int index=0;
		       for (index = 0; index < cJSON_GetArraySize(CtSgwLED); index++)
		       {
                       strcpy(target_param1.Status,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwLED, index), "Status")->valuestring); 
		       strcpy(target_param1.StartTime,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwLED, index), "StartTime")->valuestring);  
		       strcpy(target_param1.EndTime,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwLED, index), "EndTime")->valuestring);  
		       strcpy(target_param1.ControlCycle,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwLED, index), "ControlCycle")->valuestring);  
		       strcpy(target_param1.Enable,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwLED, index), "Enable")->valuestring); 
		       }
		      
                       CheckCtSgwLED_t(&out_param1,&target_param1);   

   }
         break;
    case 43:{
                       CtSgwLED_t out_param1;
		       CtSgwObjPath_t path;
                       CtSgwLED_t target_param1;
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
		       cJSON *in = cJSON_GetObjectItem(testcase,"in");
                       strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring); 
                         
                       return_value = CtSgwGetLED(path,&out_param1);       
                       Check_return_result(return_value,atoi(return_target)); 
                       strcpy(target_param1.Status,cJSON_GetObjectItem(target, "Status")->valuestring); 
		       strcpy(target_param1.StartTime,cJSON_GetObjectItem(target, "StartTime")->valuestring);  
		       strcpy(target_param1.EndTime,cJSON_GetObjectItem(target, "EndTime")->valuestring);  
		       strcpy(target_param1.ControlCycle,cJSON_GetObjectItem(target, "ControlCycle")->valuestring);  
		       strcpy(target_param1.Enable,cJSON_GetObjectItem(target, "Enable")->valuestring);  
		      
                       CheckCtSgwLED_t(&out_param1,&target_param1);   

   }
         break;
    case 44:{
                       CtSgwLED_t target_param1;
                       cJSON *in = cJSON_GetObjectItem(testcase,"in");

                       strcpy(target_param1.Status,cJSON_GetObjectItem(in, "Status")->valuestring); 
		       strcpy(target_param1.StartTime,cJSON_GetObjectItem(in, "StartTime")->valuestring);  
		       strcpy(target_param1.EndTime,cJSON_GetObjectItem(in, "EndTime")->valuestring);  
		       strcpy(target_param1.ControlCycle,cJSON_GetObjectItem(in, "ControlCycle")->valuestring);  
		       strcpy(target_param1.Enable,cJSON_GetObjectItem(in, "Enable")->valuestring);  
                       
                       return_value = CtSgwSetLED(&target_param1);       
                       Check_return_result(return_value,atoi(return_target)); 


   }
         break;


   case 45:{
                       CtSgwNFC_t target_param1;
                       cJSON *in = cJSON_GetObjectItem(testcase,"in");
                       strcpy(target_param1.Enable,cJSON_GetObjectItem(in, "Enable")->valuestring); 
                         
                       return_value = CtSgwSetNFC(&target_param1);       
                       Check_return_result(return_value,atoi(return_target)); 

   }
         break;
   case 46:{
                       CtSgwNFC_t out_param1;
                       CtSgwNFC_t target_param1;
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
                         
                       return_value = CtSgwGetNFC(&out_param1);       
                       Check_return_result(return_value,atoi(return_target)); 
                       strcpy(target_param1.Enable,cJSON_GetObjectItem(target, "Enable")->valuestring); 
		      
                       CheckCtSgwNFC_t(&out_param1,&target_param1);   

   }
         break;
   case 47:{
                       CtSgwSleepTimer_t* out_param1;
		       gint32 out_count;
		       gint32 target_count;
                       CtSgwSleepTimer_t target_param1;
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
                         
                       return_value = CtSgwGetSleepTimerObjs(&out_param1,&out_count);       
                       Check_return_result(return_value,atoi(return_target)); 
		       cJSON * CtSgwSleepTimer = cJSON_GetObjectItem(target, "CtSgwSleepTimer_t");

		       strcpy(target_count,cJSON_GetObjectItem(target, "count")->valuestring);
		       Check_int(out_count,atoi(target_count));
        	       int index=0;
		       for (index = 0; index < cJSON_GetArraySize(CtSgwSleepTimer); index++)
		       {
                       strcpy(target_param1.Day,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwSleepTimer, index), "Day")->valuestring); 
		       strcpy(target_param1.Time,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwSleepTimer, index), "Time")->valuestring); 
                       strcpy(target_param1.Active,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwSleepTimer, index), "Active")->valuestring); 
                       strcpy(target_param1.Enable,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwSleepTimer, index), "Enable")->valuestring); 
		       }
		       CheckCtSgwSleepTimer_t(&out_param1,&target_param1);   

   }
         break;
   case 48:{
                       CtSgwSleepTimer_t out_param1;
		       CtSgwObjPath_t path;
                       CtSgwSleepTimer_t target_param1;
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
		       cJSON *in = cJSON_GetObjectItem(testcase,"in");
                       strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring);                          
                       return_value = CtSgwGetSleepTimer(path,&out_param1);       
                       Check_return_result(return_value,atoi(return_target)); 
                       strcpy(target_param1.Day,cJSON_GetObjectItem(target, "Day")->valuestring); 
		       strcpy(target_param1.Time,cJSON_GetObjectItem(target, "Time")->valuestring); 
                       strcpy(target_param1.Active,cJSON_GetObjectItem(target, "Active")->valuestring); 
                       strcpy(target_param1.Enable,cJSON_GetObjectItem(target, "Enable")->valuestring); 

		       CheckCtSgwSleepTimer_t(&out_param1,&target_param1);   

   }
         break;
   case 49:{
                       CtSgwSleepTimer_t target_param1;
                       cJSON *in = cJSON_GetObjectItem(testcase,"in");

                       strcpy(target_param1.Day,cJSON_GetObjectItem(in, "Day")->valuestring); 
		       strcpy(target_param1.Time,cJSON_GetObjectItem(in, "Time")->valuestring); 
                       strcpy(target_param1.Active,cJSON_GetObjectItem(in, "Active")->valuestring); 
                       strcpy(target_param1.Enable,cJSON_GetObjectItem(in, "Enable")->valuestring); 
                         
                       return_value = CtSgwSetSleepTimer(&target_param1);       
                       Check_return_result(return_value,atoi(return_target)); 


   }
         break;
   case 50:{
                       CtSgwSleepTimer_t target_param1;
                       cJSON *in = cJSON_GetObjectItem(testcase,"in");
                       strcpy(target_param1.Day,cJSON_GetObjectItem(in, "Day")->valuestring); 
		       strcpy(target_param1.Time,cJSON_GetObjectItem(in, "Time")->valuestring); 
                       strcpy(target_param1.Active,cJSON_GetObjectItem(in, "Active")->valuestring); 
                       strcpy(target_param1.Enable,cJSON_GetObjectItem(in, "Enable")->valuestring); 
                         
                       return_value = CtSgwAddSleepTimer(&target_param1);       
                       Check_return_result(return_value,atoi(return_target)); 

   }
         break;
   case 51:{
                       CtSgwObjPath_t path;

		       cJSON *in = cJSON_GetObjectItem(testcase,"in");
                       strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring);                          
                       return_value = CtSgwDelSleepTimer(path);       
                       Check_return_result(return_value,atoi(return_target));
   }
         break;
   case 52:{
                       char loid[MAX_LOID_LEN+1];
                       char password[MAX_PASSWORD_LEN+1];
		       cJSON *in = cJSON_GetObjectItem(testcase,"in");

                       strcpy(loid,cJSON_GetObjectItem(in,"loid")->valuestring);  
                       strcpy(password,cJSON_GetObjectItem(in,"password")->valuestring);    
                        
                       return_value = CtSgwSysCmdSetLOID(loid,password);       
                       Check_return_result(return_value,atoi(return_target));
   }
         break;
   case 53:{                         
                       return_value = CtSgwSysCmdRegisterLOID(void);       
                       Check_return_result(return_value,atoi(return_target));
   }
         break;
   case 54:{
                       return_value = CtSgwSysCmdCheckLOID(void);       
                       Check_return_result(return_value,atoi(return_target));
   }
         break;

   case 55:{
                       char datetime[MAX_TIME_LEN+1];
		       cJSON *in = cJSON_GetObjectItem(testcase,"in");

                       strcpy(datetime,cJSON_GetObjectItem(in,"datetime")->valuestring);  
                        
                       return_value = CtSgwSysCmdSetDateTime(datetime);       
                       Check_return_result(return_value,atoi(return_target));
   }
         break;
   case 56:{
                       char devname[MAX_DEVNAME_LEN+1];
		       cJSON *in = cJSON_GetObjectItem(testcase,"in");

                       strcpy(devname,cJSON_GetObjectItem(in,"devname")->valuestring);  
                        
                       return_value = CtSgwSysCmdSetDevName(devname);       
                       Check_return_result(return_value,atoi(return_target));
   }
         break;
   case 57:{                         
                       return_value = CtSgwSysCmdReboot(void);   
                       Check_return_result(return_value,atoi(return_target));
   }
         break;
   case 58:{                         
                       return_value = CtSgwSysCmdRestore(void);   
                       Check_return_result(return_value,atoi(return_target));
   }
         break;
   case 59:{
                       char url[MAX_URL_LEN+1];
		       int mode;
		       int method;
		       cJSON *in = cJSON_GetObjectItem(testcase,"in");

                       strcpy(url,cJSON_GetObjectItem(in,"url")->valuestring);  
                       strcpy(mode,cJSON_GetObjectItem(in,"mode")->valuestring);  
                       strcpy(method,cJSON_GetObjectItem(in,"method")->valuestring);  
                        
                       return_value = CtSgwSysCmdUpgrade(url,mode,method);       
                       Check_return_result(return_value,atoi(return_target));
   }
         break;
   case 60:{
                       char pass;
		       int result;
		       cJSON *in = cJSON_GetObjectItem(testcase,"in");

                       strcpy(pass,cJSON_GetObjectItem(in,"pass")->valuestring);  
                       strcpy(result,cJSON_GetObjectItem(in,"result")->valuestring);  
                      
                       return_value = CtSgwSysCmdCheckUAPasswd(&pass,&result);       
                       Check_return_result(return_value,atoi(return_target));
   }
         break;
   case 61:{
                       char pass;
		       int result;
		       cJSON *in = cJSON_GetObjectItem(testcase,"in");

                       strcpy(pass,cJSON_GetObjectItem(in,"pass")->valuestring);  
                       strcpy(result,cJSON_GetObjectItem(in,"result")->valuestring);  
                      
                       return_value = CtSgwSysCmdCheckTAPasswd(&pass,&result);       
                       Check_return_result(return_value,atoi(return_target));
   }
         break;
   case 62:{                         
                       return_value = CtSgwSysCmdSubscribe(void);
                       Check_return_result(return_value,atoi(return_target));
   }
         break;
   case 63:{
                       CtSgwWANPPPConn_t* out_param1;
		       int out_count;
		       int target_count;
                       CtSgwWANPPPConn_t target_param1;
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
                         
                       return_value = CtSgwGetWANPPPConnObjs(&out_param1,&out_count);       
                       Check_return_result(return_value,atoi(return_target)); 

		       cJSON * CtSgwWANPPPConn = cJSON_GetObjectItem(target, "CtSgwWANPPPConn_t");
		       strcpy(target_count,cJSON_GetObjectItem(target, "count")->valuestring);
		       Check_int(out_count,atoi(target_count));

		       int index=0;
		       for (index = 0; index < cJSON_GetArraySize(CtSgwWANPPPConn); index++)
		       {
                       strcpy(target_param1.LANInterface,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANPPPConn, index), "LANInterface")->valuestring); 
		       strcpy(target_param1.ServiceList,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANPPPConn, index), "ServiceList")->valuestring);  
		       strcpy(target_param1.DHCPEnable,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANPPPConn, index), "DHCPEnable")->valuestring);  
		       strcpy(target_param1.IPMode,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANPPPConn, index), "IPMode")->valuestring);  
		       strcpy(target_param1.IPV6ConnectionStatus,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANPPPConn, index), "IPV6ConnectionStatus")->valuestring);   
		       strcpy(target_param1.ProxyEnable,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANPPPConn, index), "ProxyEnable")->valuestring); 
		       strcpy(target_param1.ProxyMaxUser,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANPPPConn, index), "ProxyMaxUser")->valuestring);  
		       strcpy(target_param1.DDNSCfgEnabled,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANPPPConn, index), "DDNSCfgEnabled")->valuestring);  
		       strcpy(target_param1.DDNSProvider,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANPPPConn, index), "DDNSProvider")->valuestring);  
		       strcpy(target_param1.DDNSUsername,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANPPPConn, index), "DDNSUsername")->valuestring);   

		       strcpy(target_param1.DDNSPassword,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANPPPConn, index), "DDNSPassword")->valuestring); 
		       strcpy(target_param1.ServicePort,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANPPPConn, index), "ServicePort")->valuestring);  
		       strcpy(target_param1.DDNSDomainName,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANPPPConn, index), "DDNSDomainName")->valuestring);  
		       strcpy(target_param1.DDNSHostName,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANPPPConn, index), "DDNSHostName")->valuestring);  
		     
		       }
   
                       CheckCtSgwWANPPPConn_t(&out_param1,&target_param1);   

   }
         break;
   case 64:{
                       CtSgwWANPPPConn_t out_param1;
		       CtSgwObjPath_t path;

                       CtSgwWANPPPConn_t target_param1;
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
		       cJSON *in = cJSON_GetObjectItem(testcase,"in");
                       strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring);                          
                       return_value = CtSgwGetWANPPPConn(path,&out_param1);       
                       Check_return_result(return_value,atoi(return_target)); 
		       strcpy(target_count,cJSON_GetObjectItem(target, "count")->valuestring);
		       Check_int(out_count,atoi(target_count));

                       strcpy(target_param1.LANInterface,cJSON_GetObjectItem(target, "LANInterface")->valuestring); 
		       strcpy(target_param1.ServiceList,cJSON_GetObjectItem(target, "ServiceList")->valuestring);  
		       strcpy(target_param1.DHCPEnable,cJSON_GetObjectItem(target, "DHCPEnable")->valuestring);  
		       strcpy(target_param1.IPMode,cJSON_GetObjectItem(target, "IPMode")->valuestring);  
		       strcpy(target_param1.IPV6ConnectionStatus,cJSON_GetObjectItem(target, "IPV6ConnectionStatus")->valuestring);   
		       strcpy(target_param1.ProxyEnable,cJSON_GetObjectItem(target, "ProxyEnable")->valuestring); 
		       strcpy(target_param1.ProxyMaxUser,cJSON_GetObjectItem(target, "ProxyMaxUser")->valuestring);  
		       strcpy(target_param1.DDNSCfgEnabled,cJSON_GetObjectItem(target, "DDNSCfgEnabled")->valuestring);  
		       strcpy(target_param1.DDNSProvider,cJSON_GetObjectItem(target, "DDNSProvider")->valuestring);  
		       strcpy(target_param1.DDNSUsername,cJSON_GetObjectItem(target, "DDNSUsername")->valuestring);   

		       strcpy(target_param1.DDNSPassword,cJSON_GetObjectItem(target, "DDNSPassword")->valuestring); 
		       strcpy(target_param1.ServicePort,cJSON_GetObjectItem(target, "ServicePort")->valuestring);  
		       strcpy(target_param1.DDNSDomainName,cJSON_GetObjectItem(target, "DDNSDomainName")->valuestring);  
		       strcpy(target_param1.DDNSHostName,cJSON_GetObjectItem(target, "DDNSHostName")->valuestring);  

                       CheckCtSgwWANPPPConn_t(&out_param1,&target_param1);   
   }
         break;
   case 65:{

                       CtSgwWANPPPConn_t target_param1;
 
		       cJSON *in = cJSON_GetObjectItem(testcase,"in");
		     
                       strcpy(target_param1.LANInterface,cJSON_GetObjectItem(in, "LANInterface")->valuestring); 
		       strcpy(target_param1.ServiceList,cJSON_GetObjectItem(in, "ServiceList")->valuestring);  
		       strcpy(target_param1.DHCPEnable,cJSON_GetObjectItem(in, "DHCPEnable")->valuestring);  
		       strcpy(target_param1.IPMode,cJSON_GetObjectItem(in, "IPMode")->valuestring);  
		       strcpy(target_param1.IPV6ConnectionStatus,cJSON_GetObjectItem(in, "IPV6ConnectionStatus")->valuestring);   
		       strcpy(target_param1.ProxyEnable,cJSON_GetObjectItem(in, "ProxyEnable")->valuestring); 
		       strcpy(target_param1.ProxyMaxUser,cJSON_GetObjectItem(in, "ProxyMaxUser")->valuestring);  
		       strcpy(target_param1.DDNSCfgEnabled,cJSON_GetObjectItem(in, "DDNSCfgEnabled")->valuestring);  
		       strcpy(target_param1.DDNSProvider,cJSON_GetObjectItem(in, "DDNSProvider")->valuestring);  
		       strcpy(target_param1.DDNSUsername,cJSON_GetObjectItem(in, "DDNSUsername")->valuestring);   
		       strcpy(target_param1.DDNSPassword,cJSON_GetObjectItem(in, "DDNSPassword")->valuestring); 
		       strcpy(target_param1.ServicePort,cJSON_GetObjectItem(in, "ServicePort")->valuestring);  
		       strcpy(target_param1.DDNSDomainName,cJSON_GetObjectItem(in, "DDNSDomainName")->valuestring);  
		       strcpy(target_param1.DDNSHostName,cJSON_GetObjectItem(in, "DDNSHostName")->valuestring);                              
                       return_value = CtSgwGetWANPPPConn(&target_param1);       
                       Check_return_result(return_value,atoi(return_target)); 

   }
         break;

    case 66:{
                       CtSgwWANIPConn_t* out_param1;
		       int out_count;
		       int target_count;
                       CtSgwWANIPConn_t target_param1;
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");      
                       return_value = CtSgwGetWANIPConnObjs(&out_param1,&out_count);
                       Check_return_result(return_value,atoi(return_target)); 

		       cJSON * CtSgwWANIPConn = cJSON_GetObjectItem(target, "CtSgwWANIPConn_t");

		       strcpy(target_count,cJSON_GetObjectItem(target, "count")->valuestring);
		       Check_int(out_count,atoi(target_count));

        	       int index=0;
		       for (index = 0; index < cJSON_GetArraySize(CtSgwWANIPConn); index++)
		       {
                       strcpy(target_param1.LANInterface,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANIPConn, index), "LANInterface")->valuestring); 
		       strcpy(target_param1.ServiceList,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANIPConn, index), "ServiceList")->valuestring); 
                       strcpy(target_param1.DHCPEnable,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANIPConn, index), "DHCPEnable")->valuestring); 
                       strcpy(target_param1.IPMode,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANIPConn, index), "IPMode")->valuestring); 
		       strcpy(target_param1.IPV6ConnectionStatus,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANIPConn, index), "IPV6ConnectionStatus[STR_LEN_32]")->valuestring); 
                       strcpy(target_param1.DDNSCfgEnabled,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANIPConn, index), "DDNSCfgEnabled")->valuestring); 
		       strcpy(target_param1.DDNSProvider,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANIPConn, index), "DDNSProvider")->valuestring); 
		       strcpy(target_param1.DDNSUsername,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANIPConn, index), "DDNSUsername")->valuestring); 
                       strcpy(target_param1.DDNSPassword,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANIPConn, index), "DDNSPassword")->valuestring); 
                       strcpy(target_param1.ServicePort,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANIPConn, index), "ServicePort")->valuestring); 
		       strcpy(target_param1.DDNSDomainName,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANIPConn, index), "DDNSDomainName")->valuestring); 
                       strcpy(target_param1.DDNSHostName,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwWANIPConn, index), "DDNSHostName")->valuestring); 
		       }

		       CheckCtSgwWANIPConn_t(&out_param1,&target_param1);   

   }
         break;
    case 67:{
                       CtSgwWANIPConn_t out_param1;
		       CtSgwObjPath_t path;
                       CtSgwWANIPConn_t target_param1;

                       cJSON *target = cJSON_GetObjectItem(testcase,"target");  
		       cJSON *in = cJSON_GetObjectItem(testcase,"in");
                       strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring); 
    
                       return_value = CtSgwGetWANIPConnObjs(path,&out_count);
                       Check_return_result(return_value,atoi(return_target)); 

                       strcpy(target_param1.LANInterface,cJSON_GetObjectItem(target, "LANInterface")->valuestring); 
		       strcpy(target_param1.ServiceList,cJSON_GetObjectItem(target, "ServiceList")->valuestring); 
                       strcpy(target_param1.DHCPEnable,cJSON_GetObjectItem(target, "DHCPEnable")->valuestring); 
                       strcpy(target_param1.IPMode,cJSON_GetObjectItem(target, "IPMode")->valuestring); 
		       strcpy(target_param1.IPV6ConnectionStatus,cJSON_GetObjectItem(target, "IPV6ConnectionStatus[STR_LEN_32]")->valuestring); 
                       strcpy(target_param1.DDNSCfgEnabled,cJSON_GetObjectItem(target, "DDNSCfgEnabled")->valuestring); 
		       strcpy(target_param1.DDNSProvider,cJSON_GetObjectItem(target, "DDNSProvider")->valuestring); 
		       strcpy(target_param1.DDNSUsername,cJSON_GetObjectItem(target, "DDNSUsername")->valuestring); 
                       strcpy(target_param1.DDNSPassword,cJSON_GetObjectItem(target, "DDNSPassword")->valuestring); 
                       strcpy(target_param1.ServicePort,cJSON_GetObjectItem(target, "ServicePort")->valuestring); 
		       strcpy(target_param1.DDNSDomainName,cJSON_GetObjectItem(target, "DDNSDomainName")->valuestring); 
                       strcpy(target_param1.DDNSHostName,cJSON_GetObjectItem(target, "DDNSHostName")->valuestring); 
		      
		       CheckCtSgwWANIPConn_t(&out_param1,&target_param1);   

   }
         break;
    case 68:{	   
                       CtSgwWANIPConn_t target_param1;

                       cJSON *in = cJSON_GetObjectItem(testcase,"in");  
                       strcpy(target_param1.LANInterface,cJSON_GetObjectItem(in, "LANInterface")->valuestring); 
		       strcpy(target_param1.ServiceList,cJSON_GetObjectItem(in, "ServiceList")->valuestring); 
                       strcpy(target_param1.DHCPEnable,cJSON_GetObjectItem(in, "DHCPEnable")->valuestring); 
                       strcpy(target_param1.IPMode,cJSON_GetObjectItem(in, "IPMode")->valuestring); 
		       strcpy(target_param1.IPV6ConnectionStatus,cJSON_GetObjectItem(in, "IPV6ConnectionStatus[STR_LEN_32]")->valuestring); 
                       strcpy(target_param1.DDNSCfgEnabled,cJSON_GetObjectItem(in, "DDNSCfgEnabled")->valuestring); 
		       strcpy(target_param1.DDNSProvider,cJSON_GetObjectItem(in, "DDNSProvider")->valuestring); 
		       strcpy(target_param1.DDNSUsername,cJSON_GetObjectItem(in, "DDNSUsername")->valuestring); 
                       strcpy(target_param1.DDNSPassword,cJSON_GetObjectItem(in, "DDNSPassword")->valuestring); 
                       strcpy(target_param1.ServicePort,cJSON_GetObjectItem(in, "ServicePort")->valuestring); 
		       strcpy(target_param1.DDNSDomainName,cJSON_GetObjectItem(in, "DDNSDomainName")->valuestring); 
                       strcpy(target_param1.DDNSHostName,cJSON_GetObjectItem(in, "DDNSHostName")->valuestring); 
	
                       return_value = CtSgwSetWANIPConn(&target_count);
                       Check_return_result(return_value,atoi(return_target)); 


   }
         break;

    case 69:{
                       CtSgwDHCPServer_t* out_param1;
		       int out_count;
		       int target_count;
                       CtSgwDHCPServer_t target_param1;
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
                         
                       return_value = CtSgwGetDHCPServerObjs(&out_param1,&out_count);       
                       Check_return_result(return_value,atoi(return_target)); 
		       cJSON * CtSgwDHCPServer = cJSON_GetObjectItem(target, "CtSgwDHCPServer_t");

		       strcpy(target_count,cJSON_GetObjectItem(target, "count")->valuestring);
		       Check_int(out_count,atoi(target_count));
        	       int index=0;
		       for (index = 0; index < cJSON_GetArraySize(CtSgwDHCPServer); index++)
		       {
                       strcpy(target_param1.MinAddress,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwDHCPServer, index), "MinAddress")->valuestring); 
		       strcpy(target_param1.MaxAddress,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwDHCPServer, index), "MaxAddress")->valuestring); 
                       strcpy(target_param1.SubnetMask,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwDHCPServer, index), "SubnetMask")->valuestring); 
                       strcpy(target_param1.LeaseTime,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwDHCPServer, index), "LeaseTime")->valuestring); 
		       }
		       
		       CheckCtSgwDHCPServer_t(&out_param1,&target_param1);   

   }
         break;
    case 70:{
                       CtSgwDHCPServer_t out_param1;
		       CtSgwObjPath_t path;
                       CtSgwDHCPServer_t target_param1;

                       cJSON *target = cJSON_GetObjectItem(testcase,"target");  
		       cJSON *in = cJSON_GetObjectItem(testcase,"in");
                       strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring); 
    
                       return_value = CtSgwGetDHCPServer(path,&out_count);
                       Check_return_result(return_value,atoi(return_target)); 

                       strcpy(target_param1.MinAddress,cJSON_GetObjectItem(target, "MinAddress")->valuestring); 
		       strcpy(target_param1.MaxAddress,cJSON_GetObjectItem(target, "MaxAddress")->valuestring); 
                       strcpy(target_param1.SubnetMask,cJSON_GetObjectItem(target, "SubnetMask")->valuestring); 
                       strcpy(target_param1.LeaseTime,cJSON_GetObjectItem(target, "LeaseTime")->valuestring); 
		      
		       CheckCtSgwDHCPServer_t(&out_param1,&target_param1);   

   }
         break;
    case 71:{
                       CtSgwDHCPServer_t target_param1;

                       cJSON *in = cJSON_GetObjectItem(testcase,"in");  
                       strcpy(target_param1.MinAddress,cJSON_GetObjectItem(in, "MinAddress")->valuestring); 
		       strcpy(target_param1.MaxAddress,cJSON_GetObjectItem(in, "MaxAddress")->valuestring); 
                       strcpy(target_param1.SubnetMask,cJSON_GetObjectItem(in, "SubnetMask")->valuestring); 
                       strcpy(target_param1.LeaseTime,cJSON_GetObjectItem(in, "LeaseTime")->valuestring); 
	
                       return_value = CtSgwSetDHCPServer(&target_count);
                       Check_return_result(return_value,atoi(return_target)); 

   }
         break;
    case 72:{
                       CtSgwUplinkQoS_t target_param1;
                       cJSON *in = cJSON_GetObjectItem(testcase,"in");

                       strcpy(target_param1.Mode,cJSON_GetObjectItem(in, "Mode")->valuestring); 
		       strcpy(target_param1.Enable,cJSON_GetObjectItem(in, "Enable")->valuestring); 
                       strcpy(target_param1.Bandwidth,cJSON_GetObjectItem(in, "Bandwidth")->valuestring); 
                       strcpy(target_param1.Plan,cJSON_GetObjectItem(in, "Plan")->valuestring); 
                       strcpy(target_param1.EnableForceWeight,cJSON_GetObjectItem(in, "EnableForceWeight")->valuestring); 
                       strcpy(target_param1.EnableDSCPMark,cJSON_GetObjectItem(in, "EnableDSCPMark")->valuestring); 
                       strcpy(target_param1.Enable802_1_P,cJSON_GetObjectItem(in, "Enable802_1_P")->valuestring); 
                        
                       return_value = CtSgwSetUplinkQos(&target_param1);       
                       Check_return_result(return_value,atoi(return_target));    

   }
         break;
    case 73:{
                       CtSgwUplinkQoS_t out_param1;
		       CtSgwUplinkQoS_t target_param1;
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
                        
                       return_value = CtSgwGetUplinkQoS(&out_param1);       
                       Check_return_result(return_value,atoi(return_target));
                       strcpy(target_param1.Mode,cJSON_GetObjectItem(target, "Mode")->valuestring); 
		       strcpy(target_param1.Enable,cJSON_GetObjectItem(target, "Enable")->valuestring); 
                       strcpy(target_param1.Bandwidth,cJSON_GetObjectItem(target, "Bandwidth")->valuestring); 
                       strcpy(target_param1.Plan,cJSON_GetObjectItem(target, "Plan")->valuestring); 
                       strcpy(target_param1.EnableForceWeight,cJSON_GetObjectItem(target, "EnableForceWeight")->valuestring); 
                       strcpy(target_param1.EnableDSCPMark,cJSON_GetObjectItem(target, "EnableDSCPMark")->valuestring); 
                       strcpy(target_param1.Enable802_1_P,cJSON_GetObjectItem(target, "Enable802_1_P")->valuestring);    
 
		       CheckCtSgwUplinkQoS_t(&out_param1,&target_param1); 
   }
         break;

    case 74:{
                       CtSgwUplinkQoSAppRule_t* out_param1;
                       CtSgwUplinkQoSAppRule_t target_param1;
		       int out_count;
		       int target_count;
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
                         
                       return_value = CtSgwGetUplinkQoSAppRuleObjs(&out_param1,&out_count);       
                       Check_return_result(return_value,atoi(return_target)); 

		       cJSON * CtSgwUplinkQoSAppRule = cJSON_GetObjectItem(target, "CtSgwUplinkQoSAppRule_t");

		       strcpy(target_count,cJSON_GetObjectItem(target, "count")->valuestring);
		       Check_int(out_count,atoi(target_count));
        	       int index=0;
		       for (index = 0; index < cJSON_GetArraySize(CtSgwUplinkQoSAppRule); index++)
		       {
                       strcpy(target_param1.AppName,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwUplinkQoSAppRule, index), "AppName")->valuestring); 
		       strcpy(target_param1.ClassQueue,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwUplinkQoSAppRule, index), "ClassQueue")->valuestring); 
		       }
		       CheckCtSgwUplinkQoSAppRule_t(&out_param1,&target_param1);   

   }
         break;
    case 75:{
                       CtSgwUplinkQoSAppRule_t* out_param1;
                       CtSgwUplinkQoSAppRule_t target_param1;
		       CtSgwObjPath_t path;
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
		       cJSON *in = cJSON_GetObjectItem(testcase,"in");
                       strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring); 
                         
                       return_value = CtSgwGetUplinkQoSAppRuleObjs(path,&out_param1);       
                       Check_return_result(return_value,atoi(return_target)); 
        	     
                       strcpy(target_param1.AppName,cJSON_GetObjectItem(target, "AppName")->valuestring); 
		       strcpy(target_param1.ClassQueue,cJSON_GetObjectItem(target, "ClassQueue")->valuestring); 
		       
		       CheckCtSgwUplinkQoSAppRule_t(&out_param1,&target_param1);   

   }
         break;
    case 76:{
                       CtSgwUplinkQoSAppRule_t target_param1;

                       cJSON *in = cJSON_GetObjectItem(testcase,"in");
                       strcpy(target_param1.AppName,cJSON_GetObjectItem(in, "AppName")->valuestring); 
		       strcpy(target_param1.ClassQueue,cJSON_GetObjectItem(in, "ClassQueue")->valuestring); 
	
                       return_value = CtSgwSetUplinkQoSAppRule(&target_param1);       
                       Check_return_result(return_value,atoi(return_target)); 
        	    
   }
         break;
    case 77:{
                       CtSgwUplinkQoSAppRule_t target_param1;

                       cJSON *in = cJSON_GetObjectItem(testcase,"in");
                       strcpy(target_param1.AppName,cJSON_GetObjectItem(in, "AppName")->valuestring); 
		       strcpy(target_param1.ClassQueue,cJSON_GetObjectItem(in, "ClassQueue")->valuestring); 
	
                       return_value = CtSgwAddUplinkQoSAppRule(&target_param1);       
                       Check_return_result(return_value,atoi(return_target)); 
        	    
   }
         break;
    case 78:{
                       CtSgwObjPath_t path;

		       cJSON *in = cJSON_GetObjectItem(testcase,"in");
                       strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring); 
                   
                       return_value = CtSgwDelUplinkQoSAppRule(path);       
                       Check_return_result(return_value,atoi(return_target)); 
        	    
   }
         break;

    case 79:{
                       CtSgwUplinkQoSClsRule_t* out_param1;
                       CtSgwUplinkQoSClsRule_t target_param1;
		       int out_count;
		       int target_count;
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
                         
                       return_value = CtSgwGetUplinkQoSClsRuleObjs(&out_param1,&out_count);       
                       Check_return_result(return_value,atoi(return_target)); 

		       cJSON * CtSgwUplinkQoSClsRule = cJSON_GetObjectItem(target, "CtSgwUplinkQoSClsRule_t");

		       strcpy(target_count,cJSON_GetObjectItem(target, "count")->valuestring);
		       Check_int(out_count,atoi(target_count));

        	       int index=0;
		       for (index = 0; index < cJSON_GetArraySize(CtSgwUplinkQoSClsRule); index++)
		       {
                       strcpy(target_param1.path_count,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwUplinkQoSClsRule, index), "path_count")->valuestring); 
		       strcpy(target_param1.ClassQueue,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwUplinkQoSClsRule, index), "ClassQueue")->valuestring); 
		       strcpy(target_param1.DSCPMarkValue,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwUplinkQoSClsRule, index), "DSCPMarkValue")->valuestring); 
		       strcpy(target_param1._802_1P_Value,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwUplinkQoSClsRule, index), "_802_1P_Value")->valuestring); 
		       strcpy(target_param1.action,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwUplinkQoSClsRule, index), "action")->valuestring); 
		       }
		       CheckCtSgwUplinkQoSClsRule_t(&out_param1,&target_param1);   

   }
         break;
    case 80:{
                       CtSgwUplinkQoSClsRule_t out_param1;
                       CtSgwUplinkQoSClsRule_t target_param1;
		       CtSgwObjPath_t path;
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
		       cJSON *in = cJSON_GetObjectItem(testcase,"in");
                       strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring); 
                         
                       return_value = CtSgwGetUplinkQoSClsRule(path,&out_param1);       
                       Check_return_result(return_value,atoi(return_target)); 

                       strcpy(target_param1.path_count,cJSON_GetObjectItem(target, "path_count")->valuestring); 
		       strcpy(target_param1.ClassQueue,cJSON_GetObjectItem(target, "ClassQueue")->valuestring); 
		       strcpy(target_param1.DSCPMarkValue,cJSON_GetObjectItem(target, "DSCPMarkValue")->valuestring); 
		       strcpy(target_param1._802_1P_Value,cJSON_GetObjectItem(target, "_802_1P_Value")->valuestring); 
		       strcpy(target_param1.action,cJSON_GetObjectItem(target, "action")->valuestring); 		       
		       CheckCtSgwUplinkQoSClsRule_t(&out_param1,&target_param1);   

   }
         break;
    case 81:{
                       CtSgwUplinkQoSClsRule_t target_param1;

                       cJSON *in = cJSON_GetObjectItem(testcase,"in");
                       strcpy(target_param1.path_count,cJSON_GetObjectItem(in, "path_count")->valuestring); 
		       strcpy(target_param1.ClassQueue,cJSON_GetObjectItem(in, "ClassQueue")->valuestring); 
		       strcpy(target_param1.DSCPMarkValue,cJSON_GetObjectItem(in, "DSCPMarkValue")->valuestring); 
		       strcpy(target_param1._802_1P_Value,cJSON_GetObjectItem(in, "_802_1P_Value")->valuestring); 
		       strcpy(target_param1.action,cJSON_GetObjectItem(target, "action")->valuestring); 
                       return_value = CtSgwAddUplinkQoSClsRule(&target_param1);       
                       Check_return_result(return_value,atoi(return_target)); 
		       

   }
         break;
    case 82:{
                       CtSgwObjPath_t path;

		       cJSON *in = cJSON_GetObjectItem(testcase,"in");
                       strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring); 

                       return_value = CtSgwDelUplinkQoSClsRule(path);       
                       Check_return_result(return_value,atoi(return_target)); 
		       

   }
         break;
    case 83:{
                       CtSgwUplinkQoSClsRule_t target_param1;

                       cJSON *in = cJSON_GetObjectItem(testcase,"in");
                       strcpy(target_param1.path_count,cJSON_GetObjectItem(in, "path_count")->valuestring); 
		       strcpy(target_param1.ClassQueue,cJSON_GetObjectItem(in, "ClassQueue")->valuestring); 
		       strcpy(target_param1.DSCPMarkValue,cJSON_GetObjectItem(in, "DSCPMarkValue")->valuestring); 
		       strcpy(target_param1._802_1P_Value,cJSON_GetObjectItem(in, "_802_1P_Value")->valuestring); 
		       strcpy(target_param1.action,cJSON_GetObjectItem(target, "action")->valuestring); 
                       return_value = CtSgwSetUplinkQoSClsRule(&target_param1);       
                       Check_return_result(return_value,atoi(return_target)); 
		       

   }
         break;
    case 84:{
                       CtSgwUplinkQoSClsMatch_t out_param1;
                       CtSgwUplinkQoSClsMatch_t target_param1;
		       CtSgwObjPath_t path;
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
		       cJSON *in = cJSON_GetObjectItem(testcase,"in");
                       strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring); 
                         
                       return_value = CtSgwGetUplinkQoSClsMatch(path,&out_param1);       
                       Check_return_result(return_value,atoi(return_target)); 

                       strcpy(target_param1.Type,cJSON_GetObjectItem(target, "Type")->valuestring); 
		       strcpy(target_param1.Max,cJSON_GetObjectItem(target, "Max")->valuestring); 
		       strcpy(target_param1.Min,cJSON_GetObjectItem(target, "Min")->valuestring); 
  		       strcpy(target_param1.ProtocolList,cJSON_GetObjectItem(target, "ProtocolList")->valuestring); 
		       
		       CheckCtSgwUplinkQoSClsMatch_t(&out_param1,&target_param1);   

   }
         break;
    case 85:{
                       CtSgwUplinkQoSClsMatch_t target_param1;

                       cJSON *in = cJSON_GetObjectItem(testcase,"in");
                       strcpy(target_param1.Type,cJSON_GetObjectItem(in, "Type")->valuestring); 
		       strcpy(target_param1.Max,cJSON_GetObjectItem(in, "Max")->valuestring); 
		       strcpy(target_param1.Min,cJSON_GetObjectItem(in, "Min")->valuestring); 
  		       strcpy(target_param1.ProtocolList,cJSON_GetObjectItem(in, "ProtocolList")->valuestring); 
		    
                       return_value = CtSgwAddUplinkQoSClsMatch(&target_param1);       
                       Check_return_result(return_value,atoi(return_target)); 


		       CheckCtSgwUplinkQoSClsMatch_t(&out_param1,&target_param1);   

   }
         break;
    case 86:{

		       CtSgwObjPath_t path;

		       cJSON *in = cJSON_GetObjectItem(testcase,"in");
                       strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring); 
                         
                       return_value = CtSgwDelUplinkQoSClsMatch(path);       
                       Check_return_result(return_value,atoi(return_target)); 
   }
         break;
    case 87:{
                       CtSgwUplinkQoSClsMatch_t target_param1;

                       cJSON *in = cJSON_GetObjectItem(testcase,"in");
                       strcpy(target_param1.Type,cJSON_GetObjectItem(in, "Type")->valuestring); 
		       strcpy(target_param1.Max,cJSON_GetObjectItem(in, "Max")->valuestring); 
		       strcpy(target_param1.Min,cJSON_GetObjectItem(in, "Min")->valuestring); 
  		       strcpy(target_param1.ProtocolList,cJSON_GetObjectItem(in, "ProtocolList")->valuestring); 
		    
                       return_value = CtSgwSetUplinkQoSClsMatch(&target_param1);       
                       Check_return_result(return_value,atoi(return_target)); 


		       CheckCtSgwUplinkQoSClsMatch_t(&out_param1,&target_param1);   

   }
         break;

    case 88:{
                       CtSgwPortMapping_t* out_param1;
                       CtSgwPortMapping_t target_param1;
		       int out_count;
		       int target_count;
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
                         
                       return_value = CtSgwGetPortMappingObjs(&out_param1,&out_count); 
      
                       Check_return_result(return_value,atoi(return_target)); 

		       cJSON * CtSgwPortMapping = cJSON_GetObjectItem(target, "CtSgwPortMapping_t");

		       strcpy(target_count,cJSON_GetObjectItem(target, "count")->valuestring);
		       Check_int(out_count,atoi(target_count));

        	       int index=0;
		       for (index = 0; index < cJSON_GetArraySize(CtSgwPortMapping); index++)
		       {
                       strcpy(target_param1.Enable,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwPortMapping, index), "Enable")->valuestring); 
		       strcpy(target_param1.LeaseDuration,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwPortMapping, index), "LeaseDuration")->valuestring); 
		       strcpy(target_param1.RemoteHost,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwPortMapping, index), "RemoteHost")->valuestring); 
  		       strcpy(target_param1.ExternalPort,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwPortMapping, index), "ExternalPort")->valuestring); 
		       strcpy(target_param1.InternalPort,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwPortMapping, index), "InternalPort")->valuestring); 
		       strcpy(target_param1.PortMappingProtocol,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwPortMapping, index), "PortMappingProtocol")->valuestring); 
		       strcpy(target_param1.InternalClient,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwPortMapping, index), "InternalClient")->valuestring); 
		       strcpy(target_param1.Description,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgwPortMapping, index), "Description")->valuestring); 
			}       

		       CheckCtSgwPortMapping_t(&out_param1,&target_param1);   

   }
         break;
    case 89:{
                       CtSgwPortMapping_t out_param1;
                       CtSgwPortMapping_t target_param1;
		       CtSgwObjPath_t path;
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
		       cJSON *in = cJSON_GetObjectItem(testcase,"in");
                       strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring);                         
                       return_value = CtSgwGetPortMappingObjs(path,&out_param1); 
      
                       Check_return_result(return_value,atoi(return_target)); 

                       strcpy(target_param1.Enable,cJSON_GetObjectItem(target, "Enable")->valuestring); 
		       strcpy(target_param1.LeaseDuration,cJSON_GetObjectItem(target, "LeaseDuration")->valuestring); 
		       strcpy(target_param1.RemoteHost,cJSON_GetObjectItem(target, "RemoteHost")->valuestring); 
  		       strcpy(target_param1.ExternalPort,cJSON_GetObjectItem(target, "ExternalPort")->valuestring); 
		       strcpy(target_param1.InternalPort,cJSON_GetObjectItem(target, "InternalPort")->valuestring); 
		       strcpy(target_param1.PortMappingProtocol,cJSON_GetObjectItem(target, "PortMappingProtocol")->valuestring); 
		       strcpy(target_param1.InternalClient,cJSON_GetObjectItem(target, "InternalClient")->valuestring); 
		       strcpy(target_param1.Description,cJSON_GetObjectItem(target, "Description")->valuestring);      

		       CheckCtSgwPortMapping_t(&out_param1,&target_param1);   

   }
         break;
    case 90:{
                       CtSgwPortMapping_t target_param1;
		     
                       cJSON *in = cJSON_GetObjectItem(testcase,"in");
                       strcpy(target_param1.Enable,cJSON_GetObjectItem(in, "Enable")->valuestring); 
		       strcpy(target_param1.LeaseDuration,cJSON_GetObjectItem(in, "LeaseDuration")->valuestring); 
		       strcpy(target_param1.RemoteHost,cJSON_GetObjectItem(in, "RemoteHost")->valuestring); 
  		       strcpy(target_param1.ExternalPort,cJSON_GetObjectItem(in, "ExternalPort")->valuestring); 
		       strcpy(target_param1.InternalPort,cJSON_GetObjectItem(in, "InternalPort")->valuestring); 
		       strcpy(target_param1.PortMappingProtocol,cJSON_GetObjectItem(in, "PortMappingProtocol")->valuestring); 
		       strcpy(target_param1.InternalClient,cJSON_GetObjectItem(in, "InternalClient")->valuestring); 
		       strcpy(target_param1.Description,cJSON_GetObjectItem(in, "Description")->valuestring);      
		                
                       return_value = CtSgwAddPortMapping(&target_param1); 
      
                       Check_return_result(return_value,atoi(return_target)); 

   }
         break;

    case 91:{

		       CtSgwObjPath_t path;

		       cJSON *in = cJSON_GetObjectItem(testcase,"in");
                       strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring); 
                         
                       return_value = CtSgwDelPortMapping(path);       
                       Check_return_result(return_value,atoi(return_target)); 
   }
         break;
    case 92:{
                       CtSgwPortMapping_t target_param1;
		     
                       cJSON *in = cJSON_GetObjectItem(testcase,"in");
                       strcpy(target_param1.Enable,cJSON_GetObjectItem(in, "Enable")->valuestring); 
		       strcpy(target_param1.LeaseDuration,cJSON_GetObjectItem(in, "LeaseDuration")->valuestring); 
		       strcpy(target_param1.RemoteHost,cJSON_GetObjectItem(in, "RemoteHost")->valuestring); 
  		       strcpy(target_param1.ExternalPort,cJSON_GetObjectItem(in, "ExternalPort")->valuestring); 
		       strcpy(target_param1.InternalPort,cJSON_GetObjectItem(in, "InternalPort")->valuestring); 
		       strcpy(target_param1.PortMappingProtocol,cJSON_GetObjectItem(in, "PortMappingProtocol")->valuestring); 
		       strcpy(target_param1.InternalClient,cJSON_GetObjectItem(in, "InternalClient")->valuestring); 
		       strcpy(target_param1.Description,cJSON_GetObjectItem(in, "Description")->valuestring);      
		                
                       return_value = CtSgwSetPortMapping(&target_param1); 
      
                       Check_return_result(return_value,atoi(return_target)); 

   }
         break;

     case 93:{
                       CtSgw_USBDevice_t* out_param1;
                       CtSgw_USBDevice_t target_param1;
		       int out_count;
		       int target_count;
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
                         
                       return_value = CtSgw_GetUSBDeviceObjs(&out_param1,&out_count);       
                       Check_return_result(return_value,atoi(return_target)); 

		       cJSON * CtSgw_USBDevice_t = cJSON_GetObjectItem(target, "CtSgw_USBDevice_t_t");

		       strcpy(target_count,cJSON_GetObjectItem(target, "count")->valuestring);
		       Check_int(out_count,atoi(target_count));

        	       int index=0;
		       for (index = 0; index < cJSON_GetArraySize(CtSgw_USBDevice_t); index++)
		       {
		       strcpy(target_param1.DeviceType,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgw_USBDevice_t, index), "DeviceType")->valuestring); 
		       strcpy(target_param1.DeviceId,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgw_USBDevice_t, index), "DeviceId")->valuestring); 
		       strcpy(target_param1.DeviceName[STR_LEN_32],cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgw_USBDevice_t, index), "DeviceName[STR_LEN_32]")->valuestring); 
  		       strcpy(target_param1.fsinfo,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgw_USBDevice_t, index), "fsinfo")->valuestring); 
		       }

		     
		       CheckCtSgw_USBDevice_t(&out_param1,&target_param1);   

   }
         break;
     case 94:{
                       CtSgw_USBDevice_t out_param1;
                       CtSgw_USBDevice_t target_param1;
		       CtSgwObjPath_t path;
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
		       cJSON *in = cJSON_GetObjectItem(testcase,"in");
                       strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring);                         
                       return_value = CtSgw_GetUSBDevice(path,&out_param1);       
                       Check_return_result(return_value,atoi(return_target)); 
		     
		       strcpy(target_param1.DeviceType,cJSON_GetObjectItem(target, "DeviceType")->valuestring); 
		       strcpy(target_param1.DeviceId,cJSON_GetObjectItem(target, "DeviceId")->valuestring); 
		       strcpy(target_param1.DeviceName,cJSON_GetObjectItem(target, "DeviceName")->valuestring); 
  		       strcpy(target_param1.fsinfo,cJSON_GetObjectItem(target, "fsinfo")->valuestring); 
		     
		       CheckCtSgw_USBDevice_t(&out_param1,&target_param1);   

   }
         break;


    case 95:{
                       CtSgw_NASConfig_t target_param1;
                       cJSON *in = cJSON_GetObjectItem(testcase,"in");
                       strcpy(target_param1.ACLMode,cJSON_GetObjectItem(in, "ACLMode")->valuestring); 
		       strcpy(target_param1.MACList,cJSON_GetObjectItem(in, "MACList")->valuestring); 
		                       
                       return_value = CtSgw_SetNASConfig(&target_param1);       
                       Check_return_result(return_value,atoi(return_target)); 
   }
         break;
    case 96:{
                       CtSgw_NASConfig_t out_param1;
                       CtSgw_NASConfig_t target_param1;
                       cJSON *target = CtSgw_GetNASConfig(testcase,"target");

                       return_value = CtSgw_GetNASConfig(&out_param1);       
                       Check_return_result(return_value,atoi(return_target)); 
                       strcpy(target_param1.ACLMode,cJSON_GetObjectItem(target, "ACLMode")->valuestring); 
		       strcpy(target_param1.MACList,cJSON_GetObjectItem(target, "MACList")->valuestring); 

		       CheckCtSgw_NASConfig_t(&out_param1,&target_param1);   
		                       
   }
         break;
    case 97:{
                       char foldername[MAX_PATH_LEN+1];
                       cJSON *in = CtSgw_GetNASConfig(testcase,"in");
		       strcpy(foldername,cJSON_GetObjectItem(in, "foldername")->valuestring); 

                       return_value = CtSgw_NAS_GetFileNum(foldername);       
                       Check_return_result(return_value,atoi(return_target)); 
                      		                       
   }
         break;
    case 98:{
                       char folderName;
		       guint32 startIndex;
		       guint32 endIndex;
	               CtSgw_FileEntry_t *out_fileList;
	               CtSgw_FileEntry_t *target_fileList;

                       cJSON *in = CtSgw_GetNASConfig(testcase,"in");
		       cJSON *target = CtSgw_GetNASConfig(testcase,"target");

		       strcpy(startIndex,cJSON_GetObjectItem(in, "startIndex")->valuestring); 
		       strcpy(endIndex,cJSON_GetObjectItem(in, "endIndex")->valuestring); 
		       strcpy(foldername,cJSON_GetObjectItem(in, "foldername")->valuestring); 		  

                       return_value = CtSgw_NAS_ListFolder(&foldername,startIndex,endIndex,&out_fileList); 
                       Check_return_result(return_value,atoi(return_target));   
			strcpy(target_fileList,cJSON_GetObjectItem(target, "fileList")->valuestring);
                       Check_return_result(target_fileList,atoi(out_fileList)); 
			     
		                       
   }
         break;
    case 99:{
                       gchar folderName;

                       cJSON *in = CtSgw_GetNASConfig(testcase,"in");

		       strcpy(foldername,cJSON_GetObjectItem(in, "foldername")->valuestring); 		  

                       return_value = CtSgw_NAS_ListFolder(&foldername);   
			
                       Check_return_result(return_value,atoi(return_target)); 
	                       
   }
         break;
    case 100:{
                       gchar oldName;
		       gchar newName;

                       cJSON *in = CtSgw_GetNASConfig(testcase,"in");

		       strcpy(oldName,cJSON_GetObjectItem(in, "oldName")->valuestring); 
		       strcpy(newName,cJSON_GetObjectItem(in, "newName")->valuestring); 		  

                       return_value = CtSgw_NAS_ReName(&oldName,&newName);   
			
                       Check_return_result(return_value,atoi(return_target)); 
	                       
   }
         break;
    case 101:{
                       gchar name;

                       cJSON *in = CtSgw_GetNASConfig(testcase,"in");

		       strcpy(name,cJSON_GetObjectItem(in, "name")->valuestring); 
		     
                       return_value = CtSgw_NAS_Remove(&Name);   
			
                       Check_return_result(return_value,atoi(return_target)); 
	                       
   }
         break;
    case 102:{
                       gchar filename;
		       char destFolderName;

                       cJSON *in = CtSgw_GetNASConfig(testcase,"in");

		       strcpy(filename,cJSON_GetObjectItem(in, "filename")->valuestring); 
		       strcpy(destFolderName,cJSON_GetObjectItem(in, "destFolderName")->valuestring);
		     
                       return_value = CtSgw_NAS_Move(&filename,&destFolderName);   
			
                       Check_return_result(return_value,atoi(return_target)); 
	                       
   }
         break;
    case 103:{
                       gchar name;
			gchar destFolderName;

                       cJSON *in = CtSgw_GetNASConfig(testcase,"in");

		       strcpy(name,cJSON_GetObjectItem(in, "name")->valuestring); 
		       strcpy(destFolderName,cJSON_GetObjectItem(in, "destFolderName")->valuestring);
		     
                       return_value = CtSgw_NAS_Copy(&name,&destFolderName);   
			
                       Check_return_result(return_value,atoi(return_target)); 
	                       
   }
         break;
    case 104:{
                       guint32 transactionId;

                       cJSON *in = CtSgw_GetNASConfig(testcase,"in");

		       strcpy(transactionId,cJSON_GetObjectItem(in, "transactionId")->valuestring); 
		    
                       return_value = CtSgw_NAS_GetCopyProgress(transactionId);   
			
                       Check_return_result(return_value,atoi(return_target)); 
	                       
   }
         break;
    case 105:{
                       const char serverIpAddr;
 			const char username;
			const char password;
 			char out_tunnelName;
			char target_tunnelName;
 			int len;

                       cJSON *in = CtSgw_GetNASConfig(testcase,"in");
                       cJSON *target = CtSgw_GetNASConfig(testcase,"target");

		       strcpy(serverIpAddr,cJSON_GetObjectItem(in, "serverIpAddr")->valuestring); 
		       strcpy(username,cJSON_GetObjectItem(in, "username")->valuestring); 
		       strcpy(password,cJSON_GetObjectItem(in, "password")->valuestring); 
		       strcpy(len,cJSON_GetObjectItem(in, "len")->valuestring); 
		    
                       return_value = ctSgw_wanCreateL2tpTunnel(&serverIpAddr,&username,&password,&out_tunnelName,len);   
			
                       Check_return_result(return_value,atoi(return_target));
		       strcpy(target_tunnelName,cJSON_GetObjectItem(target, "tunnelName")->valuestring); 
			Check_return_result(out_tunnelName,atoi(target_tunnelName));
 
	                       
   }
         break;
    case 106:{
                       char tunnelName;

                       cJSON *in = CtSgw_GetNASConfig(testcase,"in");

		       strcpy(tunnelName,cJSON_GetObjectItem(in, "tunnelName")->valuestring); 
		    
                       return_value = ctSgw_wanRemoveL2tpTunnel(&tunnelName);
			
                       Check_return_result(return_value,atoi(return_target)); 
	                       
   }
         break;
    case 107:{
                       const char tunnelName;
			const gchar ipAddrList;
			int ipAddrNum;

                       cJSON *in = CtSgw_GetNASConfig(testcase,"in");
 
		       strcpy(tunnelName,cJSON_GetObjectItem(in, "tunnelName")->valuestring); 
		       strcpy(ipAddrList,cJSON_GetObjectItem(in, "ipAddrList")->valuestring); 
		       strcpy(ipAddrNum,cJSON_GetObjectItem(in, "ipAddrNum")->valuestring);  
		    
                       return_value = ctSgw_wanAttachL2tpTunnel(&tunnelName, &ipAddrList, ipAddrNum);
			
                       Check_return_result(return_value,atoi(return_target));
		         
   }
         break;
    case 108:{
                       const char tunnelName;
			const char ipAddrList;
			int ipAddrNum;

                       cJSON *in = CtSgw_GetNASConfig(testcase,"in");
 
		       strcpy(tunnelName,cJSON_GetObjectItem(in, "tunnelName")->valuestring); 
		       strcpy(ipAddrList,cJSON_GetObjectItem(in, "ipAddrList")->valuestring); 
		       strcpy(ipAddrNum,cJSON_GetObjectItem(in, "ipAddrNum")->valuestring);  
		    
                       return_value = ctSgw_wanDetachL2tpTunnel(&tunnelName, &ipAddrList,ipAddrNum);
			
                       Check_return_result(return_value,atoi(return_target));
		         
   }
         break;
    case 109:{
                       const char tunnelName;
			int out_tunnelStatus;
			int target_tunnelStatus;

                       cJSON *in = CtSgw_GetNASConfig(testcase,"in");
                       cJSON *target = CtSgw_GetNASConfig(testcase,"target");
 
		       strcpy(tunnelName,cJSON_GetObjectItem(in, "tunnelName")->valuestring); 
		    
		    
                       return_value = ctSgw_wanDetachL2tpTunnel(&tunnelName, &tunnelStatus);
			
                       Check_return_result(return_value,atoi(return_target));
		       strcpy(target_tunnelStatus,cJSON_GetObjectItem(target, "tunnelStatus")->valuestring);
                      Check_return_result(out_tunnelStatus,atoi(target_tunnelStatus)); 
		         
   }
         break;
    case 110:{
                       const char domain_name;
			const char server;

                       cJSON *in = CtSgw_GetNASConfig(testcase,"in");
                     
		       strcpy(domain_name,cJSON_GetObjectItem(in, "domain_name")->valuestring); 
		       strcpy(server,cJSON_GetObjectItem(in, "server")->valuestring); 
		    
		    
                       return_value = CtSgw_AddDNSTunnel(&domain_name,&server);
			
                       Check_return_result(return_value,atoi(return_target));  
   }
         break;
    case 111:{
                       const char domain_name;

                       cJSON *in = CtSgw_GetNASConfig(testcase,"in");
                     
		       strcpy(domain_name,cJSON_GetObjectItem(in, "domain_name")->valuestring); 
		   
                       return_value = CtSgw_DelDNSTunnel(&domain_name);
			
                       Check_return_result(return_value,atoi(return_target));  
   }
         break;
    case 112:{
 
                       CtSgw_FTPServerConfig_t target_param1;
                       cJSON *in = cJSON_GetObjectItem(testcase,"in");
                       strcpy(target_param1.Enable,cJSON_GetObjectItem(in, "Enable")->valuestring); 
		       strcpy(target_param1.AllowAnonymous,cJSON_GetObjectItem(in, "AllowAnonymous")->valuestring); 

                         
                       return_value = CtSgw_SetFtpServer(&target_param1);       
                       Check_return_result(return_value,atoi(return_target)); 

   }
         break;
    case 113:{
                       CtSgw_FTPServerConfig_t out_param1;
                       CtSgw_FTPServerConfig_t target_param1;
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
                         
                       return_value = CtSgw_GetFTPServer(&out_param1);       
                       Check_return_result(return_value,atoi(return_target)); 
                       strcpy(target_param1.Enable,cJSON_GetObjectItem(target, "Enable")->valuestring); 
		       strcpy(target_param1.AllowAnonymous,cJSON_GetObjectItem(target, "AllowAnonymous")->valuestring); 

		       CheckCtSgwPingTestResult_t(&out_param1,&target_param1);   

   }
	break;
     case 114:{
                       CtSgw_FTPAccount_t out_param1;
                       CtSgw_FTPAccount_t target_param1;
		       int out_count;
		       int target_count;
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
                         
                       return_value = CtSgw_GetFTPAccountObjs(&out_param1);       
                       Check_return_result(return_value,atoi(return_target)); 
		       cJSON * CtSgw_FTPAccount = cJSON_GetObjectItem(target, "CtSgw_FTPAccount_t");

		       strcpy(target_count,cJSON_GetObjectItem(target, "count")->valuestring);
		       Check_int(out_count,atoi(target_count));

        	       int index=0;
		       for (index = 0; index < cJSON_GetArraySize(CtSgw_FTPAccount); index++)
		       {
                       strcpy(target_param1.UserName,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgw_FTPAccount, index), "UserName[")->valuestring); 
		       strcpy(target_param1.Password,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgw_FTPAccount, index), "Password")->valuestring); 
			}
		       CheckCtSgw_FTPAccount_t(&out_param1,&target_param1);   

   }
         break;
     case 115:{
                       CtSgw_FTPAccount_t out_param1;
                       CtSgw_FTPAccount_t target_param1;
		       CtSgwObjPath_t path;
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
		       cJSON *in = cJSON_GetObjectItem(testcase,"in");
                       strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring); 
                         
                       return_value = CtSgw_GetFTPAccount(&out_param1);       
                       Check_return_result(return_value,atoi(return_target)); 
            		strcpy(target_param1.UserName,cJSON_GetObjectItem(target, "UserName")->valuestring); 
		       strcpy(target_param1.Password,cJSON_GetObjectItem(target, "Password")->valuestring); 
			
		       CheckCtSgw_FTPAccount_t(&out_param1,&target_param1);   

   }
         break;
     case 116:{

                       CtSgw_FTPAccount_t target_param1;

                       cJSON *in = cJSON_GetObjectItem(testcase,"in");
            		strcpy(target_param1.UserName,cJSON_GetObjectItem(in, "UserName")->valuestring); 
		       strcpy(target_param1.Password,cJSON_GetObjectItem(in, "Password")->valuestring); 
                   
                       return_value = CtSgw_AddFtpAccount(&target_param1);       
                       Check_return_result(return_value,atoi(return_target));  

   }
         break;
     case 117:{

                       CtSgwObjPath_t path;

		       cJSON *in = cJSON_GetObjectItem(testcase,"in");
                       strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring); 
                      return_value = CtSgw_DelFtpAccount(path);       
                       Check_return_result(return_value,atoi(return_target));  

   }
         break;
     case 118:{
                       CtSgw_SambaServerConfig_t out_param1;
                       CtSgw_SambaServerConfig_t target_param1;
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
                         
                       return_value = CtSgw_GetSambaServer(&out_param1);       
                       Check_return_result(return_value,atoi(return_target)); 
                       strcpy(target_param1.Enable,cJSON_GetObjectItem(target, "Enable")->valuestring); 
		       strcpy(target_param1.AllowAnonymous,cJSON_GetObjectItem(target, "AllowAnonymous")->valuestring); 

		       CheckCtSgw_SambaServerConfig_t(&out_param1,&target_param1);   

   }
         break;
    case 119:{
                       CtSgw_SambaServerConfig_t target_param1;
                       cJSON *in = cJSON_GetObjectItem(testcase,"in");
                       strcpy(target_param1.Enable,cJSON_GetObjectItem(in, "Enable")->valuestring); 
		       strcpy(target_param1.AllowAnonymous,cJSON_GetObjectItem(in, "AllowAnonymous")->valuestring); 
                    
                       return_value = CtSgw_SetSambaServer(&target_param1);       
                       Check_return_result(return_value,atoi(return_target)); 


   }
         break;
    case 120:{
                       CtSgw_SambaAccount_t* out_param1;
                       CtSgw_SambaAccount_t target_param1;
		       int out_count;
		       int target_count;
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
                         
                       return_value = CtSgw_GetSambaAccountObjs(&out_param1, &out_count);       
                       Check_return_result(return_value,atoi(return_target)); 

		       cJSON * CtSgw_SambaAccount = cJSON_GetObjectItem(target, "CtSgw_SambaAccount_t");

		       strcpy(target_count,cJSON_GetObjectItem(target, "count")->valuestring);
		       Check_int(out_count,atoi(target_count));

        	       int index=0;
		       for (index = 0; index < cJSON_GetArraySize(CtSgw_SambaAccount); index++)
		       {
	
                       strcpy(target_param1.UserName,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgw_SambaAccount, index), "UserName")->valuestring); 
		       strcpy(target_param1.Password,cJSON_GetObjectItem(cJSON_GetArrayItem(CtSgw_SambaAccount, index), "Password")->valuestring); 
		       }
		       CheckCtSgw_SambaAccount_t(&out_param1,&target_param1);   

   }
         break;
    case 121:{
                      CtSgw_SambaAccount_t* out_param1;
                       CtSgw_SambaAccount_t target_param1;
		       CtSgwObjPath_t path;
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
		       cJSON *in = cJSON_GetObjectItem(testcase,"in");
                       strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring);                         
                       return_value = CtSgw_GetSambaAccount(path,&out_param1); 
      
                       Check_return_result(return_value,atoi(return_target)); 

                      strcpy(target_param1.UserName,cJSON_GetObjectItem(target, "UserName")->valuestring); 
		       strcpy(target_param1.Password,cJSON_GetObjectItem(target, "Password")->valuestring); 

		       CheckCtSgw_SambaAccount_t(&out_param1,&target_param1);   

   }
         break;
    case 122:{

                       CtSgw_SambaAccount_t target_param1;
  
		       cJSON *in = cJSON_GetObjectItem(testcase,"in");
                      strcpy(target_param1.UserName,cJSON_GetObjectItem(in, "UserName")->valuestring); 
		       strcpy(target_param1.Password,cJSON_GetObjectItem(in, "Password")->valuestring); 
                     return_value = CtSgw_AddSambaAccount(&target_param1); 
      
                       Check_return_result(return_value,atoi(return_target)); 


   }
         break;
     case 123:{

                       CtSgwObjPath_t path;

		       cJSON *in = cJSON_GetObjectItem(testcase,"in");
                       strcpy(path.str,cJSON_GetObjectItem(cJSON_GetObjectItem(in, "path"),"str")->valuestring); 
                      return_value = CtSgw_DelSambaAccount( path);       
                       Check_return_result(return_value,atoi(return_target));  

   }
         break;

    case 124:{
                       CtSgw_HttpServerConfig_t out_param1;
                       CtSgw_HttpServerConfig_t target_param1;
                       cJSON *target = cJSON_GetObjectItem(testcase,"target");
                         
                       return_value = CtSgw_GetHttpServer(&out_param1);       
                       Check_return_result(return_value,atoi(return_target)); 
                       strcpy(target_param1.Enable,cJSON_GetObjectItem(target, "Enable")->valuestring); 
		       strcpy(target_param1.AdminPasswd,cJSON_GetObjectItem(target, "AdminPasswd")->valuestring); 

		       CheckCtSgw_HttpServerConfig_t(&out_param1,&target_param1);   

   }
         break;
   case 125:{
 
                       CtSgw_HttpServerConfig_t target_param1;
                       cJSON *in = cJSON_GetObjectItem(testcase,"in");
                       strcpy(target_param1.Enable,cJSON_GetObjectItem(in, "Enable")->valuestring); 
		               strcpy(target_param1.AdminPasswd,cJSON_GetObjectItem(in, "AdminPasswd")->valuestring); 
                        
                       return_value = CtSgw_SetHttpServer(&target_param1);       
                       Check_return_result(return_value,atoi(return_target)); 

   }
         break;









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
