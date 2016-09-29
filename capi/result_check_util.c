#include "result_check_util.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "log_util.h"

gboolean Check_bool(gboolean ret, gboolean tar){
    gboolean check_result=TRUE;
	LOGI(Check_bool,ret,tar);
	if (ret == tar)
		return check_result;
	else
	{
		check_result = FALSE;
	}
	return check_result;
}
gboolean Check_int(int ret, int tar){
    gboolean check_result=TRUE;
	LOGI(Check_int,ret,tar);
	if (ret == tar)
		return check_result;
	else
	{
		check_result = FALSE;
	}
	return check_result;
}
gboolean Check_char(char *ret, char *tar){
    gboolean check_result=TRUE;
	LOGS(Check_char,ret,tar); /* if (strcmp(ret, tar)){
		check_result = FALSE;
	}*/
	return check_result;
}
gboolean Check_return_result(int ret,int tar){
    gboolean check_result=TRUE;
    LOGI(Check_return_result,ret,tar);
	if (ret == tar)
		return check_result;
	else
	{
		check_result = FALSE;
	}
	return check_result;
}
//BEGIN~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int data_int_one[] = {0,1};
int data_int_two[] = {0,1,2};
int data_int_three[] = {0,1,2,3};
int data_int_four[] = {0,1,2,3,4};
int data_int_five[] = {0,1,2,3,4,5};
int data_int_six[] = {0,1,2,3,4,5,100};
int data_int_seven[] = {1,2,3,4,5,6,7,8};
int data_int_eight[] = {1,2,3,4,5};
int data_int_nine[] = {1,2,3};

//char *regMac = "[A-F0-9]{2}(:[A-F0-9]{2}){5}";
char *regMac = "^([0-9a-fA-F]{2})(([0-9a-fA-F]{2}){5})$";
char *regIp = "[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}";
char *regDevInfo = "IP:[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3};MAC:[A-F0-9]{2}(:[A-F0-9]{2}){5},?";
char *regMACList = "MAC:[A-F0-9]{2}(:[A-F0-9]{2}){5},?";
char *regTime = "\\d+:\\d+";
char *regStr = "[0-1]{1}";
char *regDay = "[0-7]{1}";
char *regActive = "(ON)?(OFF)?";
char *regString = "(REGISTER_DEFAULT)?(REGISTER_REGISTED)?(REGISTER_TIMEOUT)?(REGISTER_NOMATCH_NOLIMITED)?(REGISTER_NOMATCH_LIMITED)\
?(REGISTER_NOACCOUNT_NOLIMITED)?(REGISTER_NOACCOUNT_LIMITED)?(REGISTER_NOUSER_NOLIMITED)?(REGISTER_NOUSER_LIMITED,REGISTER_OLT)\
?(REGISTER_OLT_FAIL)?(REGISTER_OK_DOWN_BUSINESS)?(REGISTER_OK)?(REGISTER_OK_NOW_REBOOT)?(REGISTER_GETSTAT)?(REGISTER_POK)?";
char *regPONStatus = "(PON_STATUS_NO_REG_NO_AUTH)?(PON_STATUS_REG_NO_AUTH)?(PON_STATUS_REG_AUTH)?";
char *regPingStatus = "(Request)?(Unreach)?(Complete)?";
char *regResult = "(INFORM_OK)?(INFORM_IAD_RUNNING)?(INFORM_NO_WAN)?(INFORM_INVALID_WAN)?(INFORM_NO_DNS_INFORM)?(INFORM_NO_ACS_CONFIGURATION)?(INFORM_ACSDNS_RESOLVE_FAILURE)?(INFORM_NO_RESPONSE)?(INFORM_REPORT_INTERRUPT)?(INFORM_CFE_NO_REPORT)?";
char *regDialResult = "(NO_IPTV_CONNECTION)?(IPTV_DISCONNECT)?(INVALID_MULTIVLAN)?(IPTV_BUSSINESS_NOK)?(IPTV_BUSSINESS_OK)?";
char *regPercentage = "[2-4]{1}0%";
char *regPercentage2 = "[5-9]{1}[0-9]{1}%";
char *regIpv6 = "\\s*((([0-9A-Fa-f]{1,4}:){7}(([0-9A-Fa-f]{1,4})|:))|(([0-9A-Fa-f]{1,4}:){6}(:|((25[0-5]|2[0-4]\\d|[01]?\\d{1,2})(\\.(25[0-5]|2[0-4]\\d|[01]?\\d{1,2})){3})|(:[0-9A-Fa-f]{1,4})))|(([0-9A-Fa-f]{1,4}:){5}((:((25[0-5]|2[0-4]\\d|[01]?\\d{1,2})(\\.(25[0-5]|2[0-4]\\d|[01]?\\d{1,2})){3})?)|((:[0-9A-Fa-f]{1,4}){1,2})))|(([0-9A-Fa-f]{1,4}:){4}(:[0-9A-Fa-f]{1,4}){0,1}((:((25[0-5]|2[0-4]\\d|[01]?\\d{1,2})(\\.(25[0-5]|2[0-4]\\d|[01]?\\d{1,2})){3})?)|((:[0-9A-Fa-f]{1,4}){1,2})))|(([0-9A-Fa-f]{1,4}:){3}(:[0-9A-Fa-f]{1,4}){0,2}((:((25[0-5]|2[0-4]\\d|[01]?\\d{1,2})(\\.(25[0-5]|2[0-4]\\d|[01]?\\d{1,2})){3})?)|((:[0-9A-Fa-f]{1,4}){1,2})))|(([0-9A-Fa-f]{1,4}:){2}(:[0-9A-Fa-f]{1,4}){0,3}((:((25[0-5]|2[0-4]\\d|[01]?\\d{1,2})(\\.(25[0-5]|2[0-4]\\d|[01]?\\d{1,2})){3})?)|((:[0-9A-Fa-f]{1,4}){1,2})))|(([0-9A-Fa-f]{1,4}:)(:[0-9A-Fa-f]{1,4}){0,4}((:((25[0-5]|2[0-4]\\d|[01]?\\d{1,2})(\\.(25[0-5]|2[0-4]\\d|[01]?\\d{1,2})){3})?)|((:[0-9A-Fa-f]{1,4}){1,2})))|(:(:[0-9A-Fa-f]{1,4}){0,5}((:((25[0-5]|2[0-4]\\d|[01]?\\d{1,2})(\\.(25[0-5]|2[0-4]\\d|[01]?\\d{1,2})){3})?)|((:[0-9A-Fa-f]{1,4}){1,2})))|(((25[0-5]|2[0-4]\\d|[01]?\\d{1,2})(\\.(25[0-5]|2[0-4]\\d|[01]?\\d{1,2})){3})))(%.+)?\\s*";

char *regBeaconType = "(None)?(Basic)?(WPA)?(WPA2)?(WPA/ WPA2)?(11i)?";
char *regWEPEncryptionLevel = "(40-bit)?(104-bit)?";
char *regBasicAuthenticationMode = "(OpenSystem)?(SharedKey)?(Both)?";
char *regWPAEncryptionModes = "(TKIPEncryption)?(AESEncryption)?(TKIPandAESEncryption)?";
char *regConnectionStatus = "(Unconfigured)?(Connecting)?(Authenticating)?(Connected)?(PendingDisconnect)?(Disconnecting)?(Disconnected)?";
char *regPlan = "(weight)?(priority)?";
char *regAppName = "(VOIP)?(TR069)?";
char *regProtocolList = "(TCP)?,?(UDP)?,?(ICMP)?,?(RTP)?";
char *regType = "(SMAC)?(8021P)?(SIP)?(DIP)?(SPORT)?(DPORT)?(TOS)?(DSCP)?(WANInterface)?(LANInterface)?(TC)?(FL)?";

typedef struct data_format_entry{
	char * data_format_name;
	int index;
}data_format_entry_t;
#define NUMBER 30

const data_format_entry_t DATA_FORMAT_MAP[NUMBER] = {
  	{ "DATA_MAC", 0},
	{ "DATA_STRING", 1},
	{ "DATA_IP", 2},
	{ "DATA_TIME", 3},
	{ "DATA_DEVINFO", 4},
	{ "DATA_PERCENTAGE", 5},
	{ "DATA_PERCENTAGE2", 6},
	{ "DATA_IPV6", 7},
	{ "STR", 8},
	{ "DATA_PONSTATUS", 9},
	{ "DATA_PINGSTATUS", 10},
	{ "DATA_DIALRESULT", 11},
	{ "DATA_DAY", 12},
	{ "DATA_ACTIVE", 13},
	{ "DATA_MACLIST", 14},
	{ "DATA_RESULT", 15},
	{ "DATA_BeaTyp", 16},
	{ "DATA_WEPEnLevel", 17},
	{ "DATA_BasicAuthMode", 18},
	{ "DATA_WPAEnModes", 19},
	{ "DATA_Status", 20},
	{ "DATA_PLAN", 21},
	{ "DATA_AppName", 22},
	{ "DATA_ProList", 23},
	{ "DATA_Type", 24},
};


static boolean regint(const int data,const int *reg,int index)
{
	gboolean ret = FALSE;
	int i = 0;
	for(i = 0;i < index;i ++)
	{
		if(NULL != reg && data == *(reg + i))
		{
			ret = TRUE;
			g_print( "pass!!!!!!!!!!!!!!!!\n" );
			return ret;
		}
	}
	g_print("failed!!!!!!!!!!!!!\n");
	return ret;
}

gboolean  Check_data_int(int out_param,int index,int num){

  gboolean ret=FALSE;
  int *reg = NULL;
  switch(index){
    case 0:
	 reg=data_int_one;
	 break;
    case 1:
	 reg=data_int_two;
	 break;
    case 2:
	 reg=data_int_three;
	 break;
    case 3:
	 reg=data_int_four;
	 break;
    case 4:
	 reg=data_int_five;
	 break;
    case 5:
	 reg=data_int_six;
	 break;
    case 6:
	 reg=data_int_seven;
	 break;
    case 7:
	 reg=data_int_eight;
	 break;
    case 8:
	 reg=data_int_nine;
	 break;
    default:
	 break;
  }
  return regint(out_param,reg,num);
}

static boolean regex(const gchar *string,const gchar *reg)
{   gboolean ret = FALSE;
    GRegex* regex;   
    GMatchInfo *match_info;   
    GError *error = NULL;
    regex = g_regex_new(reg, 0, 0, &error);  
    g_regex_match(regex, string, 0, &match_info);   
    while (g_match_info_matches(match_info)) {   
        gint count = g_match_info_get_match_count( match_info );
        //g_print( "match count:%d\n", count );
		if(count>=1) ret = TRUE;
        /*
        int i;
        for ( i = 0; i < count; i++ )
        {
            gchar* word = g_match_info_fetch(match_info, i);
            g_print("%d: %s\n",i,word);
            g_free(word);
        }
	*/	
        g_match_info_next(match_info, NULL);
    }
    g_match_info_free(match_info); 
    g_regex_unref(regex);
    return ret;
}

gboolean  Check_data_format(gchar *out_param,gchar *data_format_name){
  gboolean ret=FALSE;
  int index =0;
  char *reg;
  if('\0' == *out_param)
	return FALSE;
  index=find_data_format_index(data_format_name);
  switch(index){
    case 0:
	 reg=regMac;
	 break;
    case 1:
	 reg=regString;
	 break;	
    case 2:
	 reg=regIp;
	 break;	 
    case 3:
	 reg=regTime;
	 break;
    case 4:
	 reg=regDevInfo;
	 break;
    case 5:
	 reg=regPercentage;
	 break;	
    case 6:
	 reg=regPercentage2;
	 break;
    case 7:
	 reg=regIpv6;
	 break;
    case 8:
	 reg=regStr;
	 break;
    case 9:
	 reg=regPONStatus;
	 break;
    case 10:
	 reg=regPingStatus;
	 break;
    case 11:
	 reg=regDialResult;
	 break;
    case 12:
	 reg=regDay;
	 break;
    case 13:
	 reg=regActive;
	 break;
    case 14:
	 reg=regMACList;
	 break;
    case 15:
	 reg=regResult;
	 break;
    case 16:
	 reg=regBeaconType;
	 break;
    case 17:
	 reg=regWEPEncryptionLevel;
	 break;
    case 18:
	 reg=regBasicAuthenticationMode;
	 break;
    case 19:
	 reg=regWPAEncryptionModes;
	 break;
    case 20:
	 reg=regConnectionStatus;
	 break;
    case 21:
	 reg=regPlan;
	 break;
    case 22:
	 reg=regAppName;
	 break;
    case 23:
	 reg=regProtocolList;
	 break;
    case 24:
	 reg=regType;
	 break;
    default:
	 return ret;
  }
  return regex(out_param,reg);
}

int find_data_format_index(char* data_format_name){
	int index=0;
	for(index=0;index<NUMBER;index++){
               // g_print("Test Running find %d, %s,%s\n",index,FUCTION_MAP[index].fun_name,function_name);
		if(!strcmp(DATA_FORMAT_MAP[index].data_format_name,data_format_name))
		{
			//g_print("Test Running find %d\n",index);
			return DATA_FORMAT_MAP[index].index;
		}
	}
	return -1;
}
//END~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
gboolean    CheckCtSgwObjPath_t(CtSgwObjPath_t *result, CtSgwObjPath_t *target){
    gboolean check_result=TRUE;
	LOGS(CheckCtSgwObjPath_t, result->str,target->str);  if (strcmp(result->str, target->str)){
		check_result = FALSE;
	}
	return check_result;
}

/*gboolean    CheckCtSgwError_t(CtSgwError_t *result, CtSgwError_t *target){
    gboolean check_result=TRUE;
	LOGS(CheckCtSgwError_t,result,target);
	if (result != target){
		check_result = FALSE;
	}
	return check_result;
}
*/
gboolean    CheckCtSgwDeviceInfo_t(CtSgwDeviceInfo_t *result, CtSgwDeviceInfo_t *target){
    gboolean check_result=TRUE;
	LOGI(CheckCtSgwDeviceInfo_t, result->BusinessStatus,target->BusinessStatus);  if (!Check_data_int(result->BusinessStatus,target->BusinessStatus,2)){
		check_result = FALSE;
	}	
	LOGS(CheckCtSgwDeviceInfo_t, result->MAC,target->MAC);  
       if (!Check_data_format(result->MAC,target->MAC)){
		g_print("MAC failed!!!!!!!!!\n");
		check_result = FALSE;
	}
	LOGS(CheckCtSgwDeviceInfo_t, result->ITMSProtocolVersion,target->ITMSProtocolVersion);  
	LOGI(CheckCtSgwDeviceInfo_t, result->CPUUsage,target->CPUUsage); 
	LOGI(CheckCtSgwDeviceInfo_t, result->MEMUsage,target->MEMUsage); 
	LOGI(CheckCtSgwDeviceInfo_t, result->FlashUsage,target->FlashUsage); 
	LOGS(CheckCtSgwDeviceInfo_t, result->Capability,target->Capability);  
	LOGS(CheckCtSgwDeviceInfo_t, result->CPUClass,target->CPUClass); 
	LOGS(CheckCtSgwDeviceInfo_t, result->DevName,target->DevName);  
	LOGS(CheckCtSgwDeviceInfo_t, result->DevType,target->DevType); 
	LOGS(CheckCtSgwDeviceInfo_t, result->DevType1,target->DevType1); 
	LOGS(CheckCtSgwDeviceInfo_t, result->HDVersion,target->HDVersion); 
	LOGS(CheckCtSgwDeviceInfo_t, result->ProductClass,target->ProductClass); 
	LOGS(CheckCtSgwDeviceInfo_t, result->SWVersion,target->SWVersion);  
	LOGI(CheckCtSgwDeviceInfo_t, result->FlashSize,target->FlashSize); 
	LOGI(CheckCtSgwDeviceInfo_t, result->RamSize,target->RamSize); 
	LOGI(CheckCtSgwDeviceInfo_t, result->SysDuration,target->SysDuration); 
/*	LOGI(CheckCtSgwDeviceInfo_t, result->Card,target->Card);  if (!Check_data_int(result->Card,target->Card,2)){
		check_result = FALSE;
	}
	if (CheckCtSgwObjPath_t(&(result->path), &(target->path))){
		check_result = FALSE;
	}*/
	return check_result;
}
gboolean    CheckCtSgwNetworkInfo_t(CtSgwNetworkInfo_t *result, CtSgwNetworkInfo_t *target){
    gboolean check_result=TRUE;
	LOGI(CheckCtSgwNetworkInfo_t, result->IPV6,target->IPV6);  if (!Check_data_int(result->IPV6,target->IPV6,3)){
		g_print("IPV6 failed!!!!!!!!!!!!!!!!!!!!\n");		
		check_result = FALSE;
	}
	LOGI(CheckCtSgwNetworkInfo_t, result->VLANbind,target->VLANbind);  if (!Check_data_int(result->VLANbind,target->VLANbind,2)){
		check_result = FALSE;
	}
	LOGI(CheckCtSgwNetworkInfo_t, result->LAN1Status,target->LAN1Status);  if (!Check_data_int(result->LAN1Status,target->LAN1Status,2)){
		check_result = FALSE;
	}
	LOGI(CheckCtSgwNetworkInfo_t, result->LAN2Status,target->LAN2Status);  if (!Check_data_int(result->LAN2Status,target->LAN2Status,2)){
		check_result = FALSE;
	}
	LOGI(CheckCtSgwNetworkInfo_t, result->LAN3Status,target->LAN3Status);  if (!Check_data_int(result->LAN3Status,target->LAN3Status,2)){
		check_result = FALSE;
	}
	LOGI(CheckCtSgwNetworkInfo_t, result->LAN4Status,target->LAN4Status);  if (!Check_data_int(result->LAN4Status,target->LAN4Status,2)){
		check_result = FALSE;
	}	
	LOGS(CheckCtSgwNetworkInfo_t, result->IPV6_PPPoEDialReason,target->IPV6_PPPoEDialReason); 
	LOGS(CheckCtSgwNetworkInfo_t, result->IPV6_WANConnectionStatus,target->IPV6_WANConnectionStatus); if (!Check_data_format(result->IPV6_WANConnectionStatus, target->IPV6_WANConnectionStatus)){
		g_print("IPV6_WANConnectionStatus failed!!!!!!!!!!\n");
		check_result = FALSE;
	}
	LOGS(CheckCtSgwNetworkInfo_t, result->LANIPAddr,target->LANIPAddr);  if (!Check_data_format(result->LANIPAddr, target->LANIPAddr)){
		g_print("LANIPAddr failed!!!!!!!!!!!!!!\n");
		check_result = FALSE;
	}
	LOGS(CheckCtSgwNetworkInfo_t, result->PPPoEDialReason,target->PPPoEDialReason);
	LOGS(CheckCtSgwNetworkInfo_t, result->WANConnectionStatus,target->WANConnectionStatus);  if (!Check_data_format(result->WANConnectionStatus, target->WANConnectionStatus)){
		g_print("WANConnectionStatus failed!!!!!!!!!!\n");
		check_result = FALSE;
	}
	if(0 != strcmp(result->WANConnectionStatus,"Connected"))
	{
		LOGS(CheckCtSgwNetworkInfo_t, result->WANIPAddr,target->WANIPAddr);
	}
	else
	{
		LOGS(CheckCtSgwNetworkInfo_t, result->WANIPAddr,target->WANIPAddr);  if (!Check_data_format(result->WANIPAddr, target->WANIPAddr)){
		g_print("WANIPAddr failed!!!!!!!!!!!!\n");
		check_result = FALSE;
	    }
	}
	if(0 != strcmp(result->IPV6_WANConnectionStatus,"Connected"))
	{
		LOGS(CheckCtSgwNetworkInfo_t, result->WANIPV6Addr,target->WANIPV6Addr);
	}
	else
	{
		LOGS(CheckCtSgwNetworkInfo_t, result->WANIPV6Addr,target->WANIPV6Addr);if (!Check_data_format(result->WANIPV6Addr, target->WANIPV6Addr)){
		g_print("WANIPV6Addr failed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		check_result = FALSE;
		}
	}
	LOGS(CheckCtSgwNetworkInfo_t, result->WANLinkStatus,target->WANLinkStatus);  if (!Check_data_format(result->WANLinkStatus, target->WANLinkStatus)){
		g_print("WANLinkStatus failed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		check_result = FALSE;//wjq
	}
	LOGS(CheckCtSgwNetworkInfo_t, result->WiFiMode,target->WiFiMode); /* if (strcmp(result->WiFiMode, target->WiFiMode)){
		check_result = FALSE;//wjq
	}*/
	LOGS(CheckCtSgwNetworkInfo_t, result->WIFIModuleStatus,target->WIFIModuleStatus);  if (!Check_data_format(result->WIFIModuleStatus, target->WIFIModuleStatus)){
		g_print("WIFIModuleStatus failed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		check_result = FALSE;
	}
	LOGI(CheckCtSgwNetworkInfo_t, result->UPLink,target->UPLink);
	LOGI(CheckCtSgwNetworkInfo_t, result->PONDuration,target->PONDuration); 
	LOGI(CheckCtSgwNetworkInfo_t, result->PPPOEDuration,target->PPPOEDuration);
	LOGI(CheckCtSgwNetworkInfo_t, result->WiFiBytes,target->WiFiBytes); 
	LOGI(CheckCtSgwNetworkInfo_t, result->WiFiTxBytes,target->WiFiTxBytes);  
	LOGI(CheckCtSgwNetworkInfo_t, result->WiFiRxBytes,target->WiFiRxBytes);  
	LOGI(CheckCtSgwNetworkInfo_t, result->WANBytes,target->WANBytes);  
	LOGI(CheckCtSgwNetworkInfo_t, result->WANTxBytes,target->WANTxBytes);  
	LOGI(CheckCtSgwNetworkInfo_t, result->WANRxBytes,target->WANRxBytes);  
/*	if (CheckCtSgwObjPath_t(&(result->path), &(target->path))){
		check_result = FALSE;
	}*/
	return check_result;
}
gboolean    CheckCtSgwWANConnectionInfo_t(CtSgwWANConnectionInfo_t *result, CtSgwWANConnectionInfo_t *target){
    gboolean check_result=TRUE;
	LOGS(CheckCtSgwWANConnectionInfo_t, result->ConnectionStatus,target->ConnectionStatus); if (!Check_data_format(result->ConnectionStatus, target->ConnectionStatus)){
		g_print("ConnectionStatus failed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		check_result = FALSE;
	}
	LOGS(CheckCtSgwWANConnectionInfo_t, result->ConnectionType,target->ConnectionType); 
	if(0 == strcmp(result->ConnectionStatus,"Connected"))
{
	LOGS(CheckCtSgwWANConnectionInfo_t, result->DNS1,target->DNS1);  if (!Check_data_format(result->DNS1, target->DNS1)){
		g_print("DNS1 failed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		check_result = FALSE;
	}
	LOGS(CheckCtSgwWANConnectionInfo_t, result->DNS2,target->DNS2);  if (!Check_data_format(result->DNS2, target->DNS2)){
		g_print("DNS2 failed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		check_result = FALSE;
	}
	LOGS(CheckCtSgwWANConnectionInfo_t, result->Gateway,target->Gateway);  if (!Check_data_format(result->Gateway, target->Gateway)){
		g_print("Gateway failed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		check_result = FALSE;
	}
	LOGS(CheckCtSgwWANConnectionInfo_t, result->IPAddress,target->IPAddress);  if (!Check_data_format(result->IPAddress, target->IPAddress)){
		g_print("IPAddress failed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		check_result = FALSE;
	}
	LOGS(CheckCtSgwWANConnectionInfo_t, result->SubnetMask,target->SubnetMask);  if (!Check_data_format(result->SubnetMask, target->SubnetMask)){
		g_print("SubnetMask failed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		check_result = FALSE;
	}

}
	else
{
	LOGS(CheckCtSgwWANConnectionInfo_t, result->DNS1,target->DNS1);
	LOGS(CheckCtSgwWANConnectionInfo_t, result->DNS2,target->DNS2);
	LOGS(CheckCtSgwWANConnectionInfo_t, result->Gateway,target->Gateway);
	LOGS(CheckCtSgwWANConnectionInfo_t, result->IPAddress,target->IPAddress);
	LOGS(CheckCtSgwWANConnectionInfo_t, result->SubnetMask,target->SubnetMask);
}
	LOGS(CheckCtSgwWANConnectionInfo_t, result->IfName,target->IfName); 
	LOGS(CheckCtSgwWANConnectionInfo_t, result->Index,target->Index); 
	LOGS(CheckCtSgwWANConnectionInfo_t, result->IPV6_ConnectionStatus,target->IPV6_ConnectionStatus);  if (!Check_data_format(result->IPV6_ConnectionStatus, target->IPV6_ConnectionStatus)){
		g_print("IPV6_ConnectionStatus failed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		check_result = FALSE;
	}
	if(0 == strcmp(result->IPV6_ConnectionStatus,"Connected")) 
{
	LOGS(CheckCtSgwWANConnectionInfo_t, result->IPV6_IPAddress,target->IPV6_IPAddress);  if (!Check_data_format(result->IPV6_IPAddress, target->IPV6_IPAddress)){
		g_print("IPV6_IPAddress failed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		check_result = FALSE;
	}
	LOGS(CheckCtSgwWANConnectionInfo_t, result->IPV6_DNS1,target->IPV6_DNS1);  if (!Check_data_format(result->IPV6_DNS1, target->IPV6_DNS1)){
		g_print("IPV6_DNS1 failed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		check_result = FALSE;
	}
	LOGS(CheckCtSgwWANConnectionInfo_t, result->IPV6_DNS2,target->IPV6_DNS2);  if (!Check_data_format(result->IPV6_DNS2, target->IPV6_DNS2)){
		g_print("IPV6_DNS2 failed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		check_result = FALSE;
	}
	LOGS(CheckCtSgwWANConnectionInfo_t, result->IPV6_Gateway,target->IPV6_Gateway);  if (!Check_data_format(result->IPV6_Gateway, target->IPV6_Gateway)){
		g_print("IPV6_Gateway failed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		check_result = FALSE;
	}
}
else
{
	LOGS(CheckCtSgwWANConnectionInfo_t, result->IPV6_IPAddress,target->IPV6_IPAddress);
	LOGS(CheckCtSgwWANConnectionInfo_t, result->IPV6_DNS1,target->IPV6_DNS1); 
	LOGS(CheckCtSgwWANConnectionInfo_t, result->IPV6_DNS2,target->IPV6_DNS2);
	LOGS(CheckCtSgwWANConnectionInfo_t, result->IPV6_Gateway,target->IPV6_Gateway);
}
	LOGS(CheckCtSgwWANConnectionInfo_t, result->IPV6_Prefix,target->IPV6_Prefix); /* if (strcmp(result->IPV6_Prefix, target->IPV6_Prefix)){
		check_result = FALSE;
	}*/
	LOGS(CheckCtSgwWANConnectionInfo_t, result->IPV6_PrefixLength,target->IPV6_PrefixLength); 
	LOGS(CheckCtSgwWANConnectionInfo_t, result->Protocol,target->Protocol); /* if (strcmp(result->Protocol, target->Protocol)){
		check_result = FALSE;
	}*/
	LOGS(CheckCtSgwWANConnectionInfo_t, result->ServiceList,target->ServiceList); /* if (strcmp(result->ServiceList, target->ServiceList)){
		check_result = FALSE;
	}*/

	LOGI(CheckCtSgwWANConnectionInfo_t, result->VLANID,target->VLANID); /* if (result->VLANID != target->VLANID){
		check_result = FALSE;
	}*/
	LOGI(CheckCtSgwWANConnectionInfo_t, result->VLAN8021P,target->VLAN8021P);  /*if (result->VLAN8021P != target->VLAN8021P){
		check_result = FALSE;
	}*/
	LOGI(CheckCtSgwWANConnectionInfo_t, result->RxBytes,target->RxBytes); /* if (result->RxBytes != target->RxBytes){
		check_result = FALSE;
	}*/
	LOGI(CheckCtSgwWANConnectionInfo_t, result->TxBytes,target->TxBytes); /* if (result->TxBytes != target->TxBytes){
		check_result = FALSE;
	}*/
	LOGI(CheckCtSgwWANConnectionInfo_t, result->RxPkts,target->RxPkts);  /*if (result->RxPkts != target->RxPkts){
		check_result = FALSE;
	}*/
	LOGI(CheckCtSgwWANConnectionInfo_t, result->TxPkts,target->TxPkts); /* if (result->TxPkts != target->TxPkts){
		check_result = FALSE;
	}*/
/*	if (CheckCtSgwObjPath_t(&(result->path), &(target->path))){
		check_result = FALSE;
	}*/
	return check_result;
}
gboolean    CheckCtSgwWiFiInfo_t(CtSgwWiFiInfo_t *result, CtSgwWiFiInfo_t *target){
    gboolean check_result=TRUE;
	/*LOGS(CheckCtSgwWiFiInfo_t, result->PWD,target->PWD);  if (strcmp(result->PWD, target->PWD)){
		check_result = FALSE;
	}
	LOGS(CheckCtSgwWiFiInfo_t, result->SSID,target->SSID); if (strcmp(result->SSID, target->SSID)){
		check_result = FALSE;
	}*/
	LOGI(CheckCtSgwWiFiInfo_t, result->SameSSIDStatus,target->SameSSIDStatus);  if (!Check_data_int(result->SameSSIDStatus,target->SameSSIDStatus,2)){
		check_result = FALSE;
	}
	LOGI(CheckCtSgwWiFiInfo_t, result->Enable,target->Enable);  if (!Check_data_int(result->Enable,target->Enable,2)){
		check_result = FALSE;
	}
	LOGS(CheckCtSgwWiFiInfo_t, result->WiFiMode,target->WiFiMode); 
       /* if (strcmp(result->WiFiMode, target->WiFiMode)){
		check_result = FALSE;
        }*/
	/*LOGI(CheckCtSgwWiFiInfo_t, result->Channel,target->Channel);  if (result->Channel != target->Channel){
		check_result = FALSE;
	}
	LOGI(CheckCtSgwWiFiInfo_t, result->PowerLevel,target->PowerLevel);  if (result->PowerLevel != target->PowerLevel){
		check_result = FALSE;
	}
	LOGI(CheckCtSgwWiFiInfo_t, result->PowerLevel_5G,target->PowerLevel_5G);  if (result->PowerLevel_5G != target->PowerLevel_5G){
		check_result = FALSE;
	}
	LOGI(CheckCtSgwWiFiInfo_t, result->Encrypt,target->Encrypt); if (!Check_data_int(result->Encrypt,target->Encrypt,5)){
		check_result = FALSE;
	}*/
	LOGI(CheckCtSgwWiFiInfo_t, result->RxBytes,target->RxBytes); /* if (result->RxBytes != target->RxBytes){
		check_result = FALSE;
	}*/
	LOGI(CheckCtSgwWiFiInfo_t, result->RxPkts,target->RxPkts); /* if (result->RxPkts != target->RxPkts){
		check_result = FALSE;
	}*/
	LOGI(CheckCtSgwWiFiInfo_t, result->RxErrorPkts,target->RxErrorPkts); /* if (result->RxErrorPkts != target->RxErrorPkts){
		check_result = FALSE;
	}*/
	LOGI(CheckCtSgwWiFiInfo_t, result->RxDropPkts,target->RxDropPkts); /* if (result->RxDropPkts != target->RxDropPkts){
		check_result = FALSE;
	}*/
	LOGI(CheckCtSgwWiFiInfo_t, result->TxBytes,target->TxBytes);  /*if (result->TxBytes != target->TxBytes){
		check_result = FALSE;
	}*/
	LOGI(CheckCtSgwWiFiInfo_t, result->TxPkts,target->TxPkts); /* if (result->TxPkts != target->TxPkts){
		check_result = FALSE;
	}*/
	LOGI(CheckCtSgwWiFiInfo_t, result->TxErrorPkts,target->TxErrorPkts);/*  if (result->TxErrorPkts != target->TxErrorPkts){
		check_result = FALSE;
	}*/
	LOGI(CheckCtSgwWiFiInfo_t, result->TxDropPkts,target->TxDropPkts);/*  if (result->TxDropPkts != target->TxDropPkts){
		check_result = FALSE;
	}*/
/*	if (CheckCtSgwObjPath_t(&(result->path), &(target->path))){
		check_result = FALSE;
	}*/
	return check_result;
}
gboolean    CheckCtSgwPONInfo_t(CtSgwPONInfo_t *result, CtSgwPONInfo_t *target){
    gboolean check_result=TRUE;
	LOGS(CheckCtSgwPONInfo_t, result->LOID,target->LOID); /* if (strcmp(result->LOID, target->LOID)){
		check_result = FALSE;
	}*/
	LOGS(CheckCtSgwPONInfo_t, result->Password,target->Password); /* if (strcmp(result->Password, target->Password)){
		check_result = FALSE;
	}*/
	LOGS(CheckCtSgwPONInfo_t, result->PONStatus,target->PONStatus);  if (!Check_data_format(result->PONStatus, target->PONStatus)){
		g_print("PONStatus failed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		check_result = FALSE;
	}

	LOGF(CheckCtSgwPONInfo_t, result->Temperature,target->Temperature); /* if (result->Temperature != target->Temperature){
		check_result = FALSE;
	}*/
	LOGF(CheckCtSgwPONInfo_t, result->Voltage,target->Voltage); /* if (result->Vottage != target->Vottage){
		check_result = FALSE;
	}*/
	LOGF(CheckCtSgwPONInfo_t, result->Current,target->Current); /* if (result->Current != target->Current){
		check_result = FALSE;
	}*/
	LOGF(CheckCtSgwPONInfo_t, result->TXPower,target->TXPower); /* if (result->TXPower != target->TXPower){
		check_result = FALSE;
	}*/
	LOGF(CheckCtSgwPONInfo_t, result->RXPower,target->RXPower); /* if (result->RXPower != target->RXPower){
		check_result = FALSE;
	}*/
	LOGI(CheckCtSgwPONInfo_t, result->SupportPONStatusQuery,target->SupportPONStatusQuery);  if (!Check_data_int(result->SupportPONStatusQuery,target->SupportPONStatusQuery,2)){
		check_result = FALSE;
	}
/*	if (CheckCtSgwObjPath_t(&(result->path), &(target->path))){
		check_result = FALSE;
	}*/
	return check_result;
}
gboolean    CheckCtSgwVoIPInfo_t(CtSgwVoIPInfo_t *result, CtSgwVoIPInfo_t *target){
    gboolean check_result=TRUE;
	LOGS(CheckCtSgwVoIPInfo_t, result->Line1Status,target->Line1Status); /* if (strcmp(result->Line1Status, target->Line1Status)){
		check_result = FALSE;
	}*/
	LOGS(CheckCtSgwVoIPInfo_t, result->Line2Status,target->Line2Status);  /*if (strcmp(result->Line2Status, target->Line2Status)){
		check_result = FALSE;
	}*/
	LOGS(CheckCtSgwVoIPInfo_t, result->VoIPName1,target->VoIPName1);  /*if (strcmp(result->VoIPName1, target->VoIPName1)){
		check_result = FALSE;
	}*/
	LOGS(CheckCtSgwVoIPInfo_t, result->VoIPName2,target->VoIPName2); /* if (strcmp(result->VoIPName2, target->VoIPName2)){
		check_result = FALSE;
	}*/

/*	if (CheckCtSgwObjPath_t(&(result->path), &(target->path))){
		check_result = FALSE;
	}*/
	return check_result;
}
gboolean    CheckCtSgwLANHostMgr_t(CtSgwLANHostMgr_t *result, CtSgwLANHostMgr_t *target){
    gboolean check_result=TRUE;
	LOGI(CheckCtSgwLANHostMgr_t, result->EnableStats,target->EnableStats);  if (!Check_data_int(result->EnableStats,target->EnableStats,2)){
		check_result = FALSE;
	}
	LOGI(CheckCtSgwLANHostMgr_t, result->LANHostMaxNumber,target->LANHostMaxNumber); 
	LOGI(CheckCtSgwLANHostMgr_t, result->LANHostNumber,target->LANHostNumber);  
	LOGI(CheckCtSgwLANHostMgr_t, result->ControlListMaxNumber,target->ControlListMaxNumber); 
	LOGI(CheckCtSgwLANHostMgr_t, result->ControlListNumber,target->ControlListNumber);  
/*	if (CheckCtSgwObjPath_t(&(result->path), &(target->path))){
		check_result = FALSE;
	}*/
	return check_result;

}
gboolean    CheckCtSgwLANHost_t(CtSgwLANHost_t *result, CtSgwLANHost_t *target){
    gboolean check_result=TRUE;
	LOGI(CheckCtSgwLANHost_t, result->ConnectionType,target->ConnectionType);  if (!Check_data_int(result->ConnectionType,target->ConnectionType,2)){
		check_result = FALSE;
	}
	LOGI(CheckCtSgwLANHost_t, result->Port,target->Port);  if (!Check_data_int(result->Port,target->Port,5)){
		check_result = FALSE;
	}
	LOGS(CheckCtSgwLANHost_t, result->Brand,target->Brand);  /*if (strcmp(result->Brand, target->Brand)){
		check_result = FALSE;
	}*/
	LOGS(CheckCtSgwLANHost_t, result->Model,target->Model);  /*if (strcmp(result->Model, target->Model)){
		check_result = FALSE;
	}*/
	LOGS(CheckCtSgwLANHost_t, result->LatestActiveTime,target->LatestActiveTime);  /*if (strcmp(result->LatestActiveTime, target->LatestActiveTime)){
		check_result = FALSE;
	}*/
	LOGS(CheckCtSgwLANHost_t, result->LatestInactiveTime,target->LatestInactiveTime);  /*if (strcmp(result->LatestInactiveTime, target->LatestInactiveTime)){
		check_result = FALSE;
	}*/
	LOGS(CheckCtSgwLANHost_t, result->DevName,target->DevName);  /*if (strcmp(result->DevName, target->DevName)){
		check_result = FALSE;
	}*/
	LOGS(CheckCtSgwLANHost_t, result->DevType,target->DevType); /* if (strcmp(result->DevType, target->DevType)){
		check_result = FALSE;
	}*/
	LOGS(CheckCtSgwLANHost_t, result->IP,target->IP);  if (!Check_data_format(result->IP, target->IP)){
		g_print("IP failed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		check_result = FALSE;
	}
	LOGS(CheckCtSgwLANHost_t, result->MAC,target->MAC); /* if (!Check_data_format(result->MAC, target->MAC)){
		g_print("MAC failed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		check_result = FALSE;
	}*/
	LOGS(CheckCtSgwLANHost_t, result->OS,target->OS);  /*if (strcmp(result->OS, target->OS)){
		check_result = FALSE;
	}*/
	LOGI(CheckCtSgwLANHost_t, result->InternetAccess,target->InternetAccess);  if (!Check_data_int(result->InternetAccess,target->InternetAccess,3)){
		check_result = FALSE;
	}
	LOGI(CheckCtSgwLANHost_t, result->StorageAccess,target->StorageAccess);  if (!Check_data_int(result->StorageAccess,target->StorageAccess,2)){
		check_result = FALSE;
	}
	LOGI(CheckCtSgwLANHost_t, result->ControlStatus,target->ControlStatus);  if (!Check_data_int(result->ControlStatus,target->ControlStatus,2)){
		check_result = FALSE;
	}
	LOGI(CheckCtSgwLANHost_t, result->Active,target->Active);  if (!Check_data_int(result->Active,target->Active,2)){
		check_result = FALSE;
	}
	LOGI(CheckCtSgwLANHost_t, result->MaxUSBandwidth,target->MaxUSBandwidth); /* if (result->MaxUSBandwidth != target->MaxUSBandwidth){
		check_result = FALSE;
	}*/
	LOGI(CheckCtSgwLANHost_t, result->MaxDSBandwidth,target->MaxDSBandwidth); /* if (result->MaxDSBandwidth != target->MaxDSBandwidth){
		check_result = FALSE;
	}*/
	/*LOGI(CheckCtSgwLANHost_t, result->USBandwidth,target->USBandwidth);  if (result->USBandwidth != target->USBandwidth){
		check_result = FALSE;
	}
	LOGI(CheckCtSgwLANHost_t, result->DSBandwidth,target->DSBandwidth);  if (result->DSBandwidth != target->DSBandwidth){
		check_result = FALSE;
	}*/
	LOGI(CheckCtSgwLANHost_t, result->OnlineTime,target->OnlineTime); /* if (result->OnlineTime != target->OnlineTime){
		check_result = FALSE;
	}*/
	LOGI(CheckCtSgwLANHost_t, result->RxBytes,target->RxBytes); /* if (result->RxBytes != target->RxBytes){
		check_result = FALSE;
	}*/
	LOGI(CheckCtSgwLANHost_t, result->TxBytes,target->TxBytes); /* if (result->TxBytes != target->TxBytes){
		check_result = FALSE;
	}*/
/*	if (CheckCtSgwObjPath_t(&(result->path), &(target->path))){
		check_result = FALSE;
	}*/
	return check_result;
}

gboolean    CheckCtSgwHttpDownloadTestResult_t(CtSgwHttpDownloadTestResult_t *result, CtSgwHttpDownloadTestResult_t *target){
    gboolean check_result=TRUE;
	LOGS(CheckCtSgwHttpDownloadTestResult_t, result->Result,target->Result); /* if (strcmp(result->Result, target->Result)){
		check_result = FALSE;
	}*/
	LOGS(CheckCtSgwHttpDownloadTestResult_t, result->URL,target->URL); /* if (strcmp(result->URL, target->URL)){
		check_result = FALSE;
	}*/
	LOGI(CheckCtSgwHttpDownloadTestResult_t, result->Status,target->Status);  if (!Check_data_int(result->Status,target->Status,2)){
		check_result = FALSE;
	}
/*	if (CheckCtSgwObjPath_t(&(result->path), &(target->path))){
		check_result = FALSE;
	}*/
	return check_result;
}

gboolean    CheckCtSgwWPSDevInfo_t(CtSgwWPSDevInfo_t *result, CtSgwWPSDevInfo_t *target){
    gboolean check_result=TRUE;
	LOGS(CheckCtSgwWPSDevInfo_t, result->Info,target->Info);  if (!Check_data_format(result->Info, target->Info)){
		g_print("Info failed!!!!!\n");
		check_result = FALSE;
	}

	return check_result;
}

gboolean    CheckCtSgwWPS_t(CtSgwWPS_t *result, CtSgwWPS_t *target){
    gboolean check_result=TRUE;
	LOGI(CheckCtSgwWPS_t, result->WPSStatus,target->WPSStatus);  if (!Check_data_int(result->WPSStatus,target->WPSStatus,4)){
		check_result = FALSE;
	}
	if (CheckCtSgwWPSDevInfo_t(result->DevInfo, target->DevInfo)){
		check_result = FALSE;
	}
/*	int index=0;
	for (index = 0; index < WPS_ATT_DEV_NUM; index++)
	{	
		LOGS(CheckCtSgwWPS_t, result->DevInfo[index].Info,target->DevInfo[index].Info);  if (!Check_data_format(result->DevInfo[index].Info, target->DevInfo[index].Info)){
			check_result = FALSE;//wu
		}
	}
*/

	LOGI(CheckCtSgwWPS_t, result->Enable,target->Enable);  if (!Check_data_int(result->Enable,target->Enable,2)){
		check_result = FALSE;
	}
	//LOGI(CheckCtSgwWPS_t, result->TimeOut,target->TimeOut);  
/*if (result->TimeOut != target->TimeOut){
		check_result = FALSE;
	}*/
/*	if (CheckCtSgwObjPath_t(&(result->path), &(target->path))){
		check_result = FALSE;
	}*/
	return check_result;
}
gboolean    CheckCtSgwWLANDevice_t(CtSgwWLANDevice_t *result, CtSgwWLANDevice_t *target){
    gboolean check_result=TRUE;
	LOGS(CheckCtSgwWLANDevice_t, result->BasicAuthenticationMode,target->BasicAuthenticationMode);  if (!Check_data_format(result->BasicAuthenticationMode, target->BasicAuthenticationMode)){
		g_print("BasicAuthenticationMode failed!!!!!\n");
		check_result = FALSE;
	}

	LOGS(CheckCtSgwWLANDevice_t, result->BeaconType,target->BeaconType);  if (!Check_data_format(result->BeaconType, target->BeaconType)){
		g_print("BeaconType failed!!!!!\n");
		check_result = FALSE;
	}

	LOGS(CheckCtSgwWLANDevice_t, result->PWD,target->PWD); /* if (strcmp(result->PWD, target->PWD)){
		check_result = FALSE;
	}*/

	LOGS(CheckCtSgwWLANDevice_t, result->SSID,target->SSID); /* if (strcmp(result->SSID, target->SSID)){
		check_result = FALSE;
	}*/
	LOGS(CheckCtSgwWLANDevice_t, result->Standard,target->Standard); /* if (strcmp(result->Standard, target->Standard)){
		check_result = FALSE;
	}*/
	LOGS(CheckCtSgwWLANDevice_t, result->WEPEncryptionLevel,target->WEPEncryptionLevel);  if (!Check_data_format(result->WEPEncryptionLevel, target->WEPEncryptionLevel)){
		g_print("WEPEncryptionLevel failed!!!!!\n");
		check_result = FALSE;
	}
	LOGS(CheckCtSgwWLANDevice_t, result->WPAEncryptionModes,target->WPAEncryptionModes);  if (!Check_data_format(result->WPAEncryptionModes, target->WPAEncryptionModes)){
		g_print("WPAEncryptionModes failed!!!!!\n");
		check_result = FALSE;
	}
	LOGI(CheckCtSgwWLANDevice_t, result->Enable,target->Enable);  if (!Check_data_int(result->Enable,target->Enable,2)){
		check_result = FALSE;
	}
	LOGI(CheckCtSgwWLANDevice_t, result->Channel,target->Channel); /* if (result->Channel != target->Channel){
		check_result = FALSE;
	}*/
	LOGI(CheckCtSgwWLANDevice_t, result->ChannelInUse,target->ChannelInUse); /* if (result->ChannelInUse != target->ChannelInUse){
		check_result = FALSE;
	}*/
	LOGI(CheckCtSgwWLANDevice_t, result->SSIDHide,target->SSIDHide);  if (!Check_data_int(result->SSIDHide,target->SSIDHide,2)){
		check_result = FALSE;
	}
	LOGI(CheckCtSgwWLANDevice_t, result->RFBand,target->RFBand);  if (!Check_data_int(result->RFBand,target->RFBand,2)){
		check_result = FALSE;
	}
	LOGI(CheckCtSgwWLANDevice_t, result->ChannelWidth,target->ChannelWidth);  if (!Check_data_int(result->ChannelWidth,target->ChannelWidth,6)){
		check_result = FALSE;
	}
	LOGI(CheckCtSgwWLANDevice_t, result->GuardInterval,target->GuardInterval);  if (!Check_data_int(result->GuardInterval , target->GuardInterval,2)){
		check_result = FALSE;
	}
	LOGI(CheckCtSgwWLANDevice_t, result->RetryTimeout,target->RetryTimeout); /* if (result->RetryTimeout != target->RetryTimeout){
		check_result = FALSE;
	}*/
	LOGI(CheckCtSgwWLANDevice_t, result->Powerlevel,target->Powerlevel);  /*if (result->Powerlevel != target->Powerlevel){
		check_result = FALSE;
	}*/
	//LOGI(CheckCtSgwWLANDevice_t, result->PowerLevel_5G,target->PowerLevel_5G); 
/* if (result->PowerLevel_5G != target->PowerLevel_5G){
		check_result = FALSE;
	}*/
	LOGI(CheckCtSgwWLANDevice_t, result->PowerValue,target->PowerValue); /* if (result->PowerValue != target->PowerValue){
		check_result = FALSE;
	}*/
      /*LOGI(CheckCtSgwWLANDevice_t, result->APModuleEnable,target->APModuleEnable); 
 if (!Check_data_int(result->APModuleEnable, target->APModuleEnable,2)){
		check_result = FALSE;
	}*/
	//LOGI(CheckCtSgwWLANDevice_t, result->WPSKeyWord,target->WPSKeyWord); 
/* if (result->WPSKeyWord != target->WPSKeyWord){
		check_result = FALSE;
	}*/
/*	if (CheckCtSgwObjPath_t(&(result->path), &(target->path))){
		check_result = FALSE;
	}*/
	return check_result;
}
gboolean    CheckCtSgwWiFiTimer_t(CtSgwWiFiTimer_t *result, CtSgwWiFiTimer_t *target){
    gboolean check_result=TRUE;
	LOGS(CheckCtSgwWiFiTimer_t, result->ControlCycle,target->ControlCycle);  if (strcmp(result->ControlCycle, target->ControlCycle)){
              g_print("ControlCycle failed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");		
              check_result = FALSE;
	}
	LOGS(CheckCtSgwWiFiTimer_t, result->EndTime,target->EndTime);  if (!Check_data_format(result->EndTime, target->EndTime)){
		g_print("EndTime failed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		check_result = FALSE;
	}
	LOGS(CheckCtSgwWiFiTimer_t, result->StartTime,target->StartTime);  if (!Check_data_format(result->StartTime, target->StartTime)){
		g_print("StartTime failed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");	
                check_result = FALSE;
	}
	LOGI(CheckCtSgwWiFiTimer_t, result->Enable,target->Enable);  if (!Check_data_int(result->Enable,target->Enable,2)){
            g_print("result->Enable&target->Enable failed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");			
            check_result = FALSE;
	}
/*	if (CheckCtSgwObjPath_t(&(result->path), &(target->path))){
		check_result = FALSE;
	}*/
	return check_result;
}
gboolean    CheckCtSgwWiFiTimer1_t(CtSgwWiFiTimer1_t *result, CtSgwWiFiTimer1_t *target){
    gboolean check_result=TRUE;
	LOGS(CheckCtSgwWiFiTimer1_t, result->Active,target->Active);  if (!Check_data_format(result->Active, target->Active)){
		g_print("Active failed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		check_result = FALSE;
	}
	LOGI(CheckCtSgwWiFiTimer1_t, result->Enable,target->Enable);  if (!Check_data_int(result->Enable,target->Enable,2)){
                g_print("result->Enable&target->Enable)!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");		
                check_result = FALSE;
	}
	LOGS(CheckCtSgwWiFiTimer1_t, result->Time,target->Time);  if (!Check_data_format(result->Time, target->Time)){
		g_print("Time failed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		check_result = FALSE;
	}
	LOGS(CheckCtSgwWiFiTimer1_t, result->WeekDay->str,target->WeekDay->str);  if (!Check_data_format(result->WeekDay->str, target->WeekDay->str)){
		g_print("WeekDay failed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		check_result = FALSE;
	}

/*	if (CheckCtSgwObjPath_t(&(result->path), &(target->path))){
		check_result = FALSE;
	}*/
	return check_result;
}
gboolean    CheckCtSgwLED_t(CtSgwLED_t *result, CtSgwLED_t *target){
    gboolean check_result=TRUE;
	LOGS(CheckCtSgwLED_t, result->ControlCycle,target->ControlCycle);  if (strcmp(result->ControlCycle, target->ControlCycle)){
            g_print("ControlCycle failed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");		
            check_result = FALSE;
	}
	LOGI(CheckCtSgwLED_t, result->Enable,target->Enable);  if (!Check_data_int(result->Enable,target->Enable,2)){
	    g_print("result->Enable&target->Enable!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");		
	    check_result = FALSE;
	}
	LOGS(CheckCtSgwLED_t, result->EndTime,target->EndTime);  if (!Check_data_format(result->EndTime, target->EndTime)){
		g_print("EndTime failed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		check_result = FALSE;
	}
	LOGS(CheckCtSgwLED_t, result->StartTime,target->StartTime);  if (!Check_data_format(result->StartTime, target->StartTime)){
		g_print("StartTime failed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		check_result = FALSE;
	}
	LOGS(CheckCtSgwLED_t, result->Status,target->Status);  if (!Check_data_format(result->Status, target->Status)){
		g_print("Status failed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		check_result = FALSE;
	}

/*	if (CheckCtSgwObjPath_t(&(result->path), &(target->path))){
		check_result = FALSE;
	}*/
	return check_result;
}
gboolean    CheckCtSgwSleepTimer_t(CtSgwSleepTimer_t *result, CtSgwSleepTimer_t *target){
    gboolean check_result=TRUE;
	LOGS(CheckCtSgwSleepTimer_t, result->Active,target->Active);  if (!Check_data_format(result->Active, target->Active)){
		g_print("Active failed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		check_result = FALSE;
	}
	LOGS(CheckCtSgwSleepTimer_t, result->Day->str,target->Day->str);  if (!Check_data_format(result->Day->str, target->Day->str)){
		g_print("Day failed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		check_result = FALSE;
	}
	LOGI(CheckCtSgwSleepTimer_t, result->Enable,target->Enable);  if (!Check_data_int(result->Enable,target->Enable,2)){
                 g_print("result->Enable&target->Enable!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");		
                 check_result = FALSE;
	}
	LOGS(CheckCtSgwSleepTimer_t, result->Time,target->Time);  if (!Check_data_format(result->Time,target->Time)){
		g_print("Time failed!!!!\n");
		check_result = FALSE;
	}

/*	if (CheckCtSgwObjPath_t(&(result->path), &(target->path))){
		check_result = FALSE;
	}*/
	return check_result;
}

gboolean    CheckCtSgwPPPoE_t(CtSgwPPPoE_t *result, CtSgwPPPoE_t *target){
    gboolean check_result=TRUE;

	LOGS(CheckCtSgwPPPoE_t, result->PPPoEUserName,target->PPPoEUserName);

/*	if (CheckCtSgwObjPath_t(&(result->path), &(target->path))){
		check_result = FALSE;
	}*/
	return check_result;
}

gboolean    CheckCtSgwDHCPServer_t(CtSgwDHCPServer_t *result, CtSgwDHCPServer_t *target){
    gboolean check_result=TRUE;
	LOGI(CheckCtSgwDHCPServer_t, result->Enable,target->Enable);  if (!Check_data_int(result->Enable,target->Enable,2)){
		check_result = FALSE;
	}
	LOGS(CheckCtSgwDHCPServer_t, result->MaxAddress,target->MaxAddress);  if (!Check_data_format(result->MaxAddress, target->MaxAddress)){
		g_print("MaxAddress failed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		check_result = FALSE;
	}
	LOGS(CheckCtSgwDHCPServer_t, result->MinAddress,target->MinAddress);  if (!Check_data_format(result->MinAddress, target->MinAddress)){
		g_print("MinAddress failed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		check_result = FALSE;
	}
	LOGS(CheckCtSgwDHCPServer_t, result->IPAddr,target->IPAddr);  if (!Check_data_format(result->IPAddr, target->IPAddr)){
		g_print("IPAddr failed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		check_result = FALSE;
	}
	LOGS(CheckCtSgwDHCPServer_t,result->SubnetMask,target->SubnetMask);  if (!Check_data_format(result->SubnetMask, target->SubnetMask)){
		g_printf("SubnetMask failed!!!!!!!!!!!!\n");		
		check_result = FALSE;
	}
	LOGI(CheckCtSgwDHCPServer_t, result->LeaseTime,target->LeaseTime); /* if (result->LeaseTime != target->LeaseTime){
		check_result = FALSE;
	}*/
/*	if (CheckCtSgwObjPath_t(&(result->path), &(target->path))){
		check_result = FALSE;
	}*/
	return check_result;
}

gboolean    CheckCtSgwPortMapping_t(CtSgwPortMapping_t *result, CtSgwPortMapping_t *target){
    gboolean check_result=TRUE;
	LOGS(CheckCtSgwPortMapping_t, result->Description,target->Description); /* if (strcmp(result->Description, target->Description)){
		check_result = FALSE;
	}*/
	LOGS(CheckCtSgwPortMapping_t, result->InternalClient,target->InternalClient);  if (!Check_data_format(result->InternalClient, target->InternalClient)){
		g_print("InternalClient failed!!!!!!!!\n");
		check_result = FALSE;
	}
	LOGS(CheckCtSgwPortMapping_t, result->PortMappingProtocol,target->PortMappingProtocol);/*  if (strcmp(result->PortMappingProtocol, target->PortMappingProtocol)){
		check_result = FALSE;
	}*/
	LOGS(CheckCtSgwPortMapping_t, result->RemoteHost,target->RemoteHost);  if (!Check_data_format(result->RemoteHost, target->RemoteHost)){
		g_print("RemoteHost failed!!!!!!!!\n");
		check_result = FALSE;
	}
//	LOGS(CheckCtSgwPortMapping_t, result->WANPath,target->WANPath);  if (strcmp(result->WANPath, target->WANPath)){
//		check_result = FALSE;
//	}
	LOGI(CheckCtSgwPortMapping_t, result->Enable,target->Enable);  if (!Check_data_int(result->Enable,target->Enable,2)){
		check_result = FALSE;
	}
	LOGI(CheckCtSgwPortMapping_t, result->LeaseDuration,target->LeaseDuration); /* if (result->LeaseDuration != target->LeaseDuration){
		check_result = FALSE;
	}*/
	LOGI(CheckCtSgwPortMapping_t, result->ExternalPort,target->ExternalPort);/*  if (result->ExternalPort != target->ExternalPort){
		check_result = FALSE;
	}*/
	LOGI(CheckCtSgwPortMapping_t, result->InternalPort,target->InternalPort); /* if (result->InternalPort != target->InternalPort){
		check_result = FALSE;
	}*/
/*	if (CheckCtSgwObjPath_t(&(result->path), &(target->path))){
		check_result = FALSE;
	}*/
	return check_result;
}

gboolean    CheckCtSgw_USBFSInfo_t(CtSgw_USBFSInfo_t *result, CtSgw_USBFSInfo_t *target){
    gboolean check_result=TRUE;
	LOGS(CheckCtSgw_USBFSInfo_t, result->Label,target->Label);  /*if (strcmp(result->Label, target->Label)){
		check_result = FALSE;
	}*/
	LOGS(CheckCtSgw_USBFSInfo_t, result->MountPoint,target->MountPoint); /* if (strcmp(result->MountPoint, target->MountPoint)){
		check_result = FALSE;
	}*/
	LOGI(CheckCtSgw_USBFSInfo_t, result->TotalSize,target->TotalSize); /* if (result->TotalSize != target->TotalSize){
		check_result = FALSE;
	}*/
	LOGI(CheckCtSgw_USBFSInfo_t, result->UsedSize,target->UsedSize); /* if (result->UsedSize != target->UsedSize){
		check_result = FALSE;
	}*/
	LOGI(CheckCtSgw_USBFSInfo_t, result->FreeSize,target->FreeSize);  /*if (result->FreeSize != target->FreeSize){
		check_result = FALSE;
	}*/
	return check_result;
}

gboolean    CheckCtSgw_USBDevice_t(CtSgw_USBDevice_t *result, CtSgw_USBDevice_t *target){
    gboolean check_result=TRUE;
	LOGS(CheckCtSgw_USBDevice_t, result->DeviceName,target->DeviceName); /* if (strcmp(result->DeviceName, target->DeviceName)){
		check_result = FALSE;
	}*/
	LOGI(CheckCtSgw_USBDevice_t, result->DeviceType,target->DeviceType); /* if (result->DeviceType != target->DeviceType){
		check_result = FALSE;
	}*/
	LOGI(CheckCtSgw_USBDevice_t, result->DeviceId,target->DeviceId);/*  if (result->DeviceId != target->DeviceId){
		check_result = FALSE;
	}*/

/*	if (CheckCtSgwObjPath_t(&(result->path), &(target->path))){
		check_result = FALSE;
	}*/
	return check_result;
}

gboolean    CheckCtSgwUSBDeviceInfo_t(CtSgwUSBDeviceInfo_t *result, CtSgwUSBDeviceInfo_t *target){
    gboolean check_result=TRUE;
	if (!CheckCtSgw_USBDevice_t(&(result->device), &(target->device))){
		check_result = FALSE;
	}
	if (!CheckCtSgw_USBFSInfo_t(&(result->fsinfo), &(target->fsinfo))){
		check_result = FALSE;
	}
/*	if (CheckCtSgwObjPath_t(&(result->path), &(target->path))){
		check_result = FALSE;
	}*/
	return check_result;
}

gboolean    CheckCtSgwStrArray_t(CtSgwStrArray_t *result, CtSgwStrArray_t *target){
	gboolean check_result=TRUE;

	LOGS(CheckCtSgwStrArray_t, result->str,target->str);  if (strcmp(result->str, target->str)){
		check_result = FALSE;
	}

	return check_result;
}


gboolean    CheckCtSgwVPNConnStats_t(CtSgwVPNConnStats_t *result, CtSgwVPNConnStats_t *target){
	gboolean check_result=TRUE;

	LOGI(CheckCtSgwVPNConnStats_t, result->arrayLen,target->arrayLen);  if (result->arrayLen != target->arrayLen){
		check_result = FALSE;
	}
	if(!CheckCtSgwStrArray_t(result->data,target->data))
	{
		check_result = FALSE;
	}

/*	if (CheckCtSgwObjPath_t(&(result->path), &(target->path))){
		check_result = FALSE;
	}*/
	return check_result;
}
gboolean    CheckCtSgwDNSServerConfig_t(CtSgwDNSServerConfig_t *result, CtSgwDNSServerConfig_t *target){
    gboolean check_result=TRUE;
	LOGS(CheckCtSgwDNSServerConfig_t, result->Server1,target->Server1);  if (strcmp(result->Server1, target->Server1)){
		check_result = FALSE;
	}
	LOGS(CheckCtSgwDNSServerConfig_t, result->Server2,target->Server2);  if (strcmp(result->Server2, target->Server2)){
		check_result = FALSE;
	}

/*	if (CheckCtSgwObjPath_t(&(result->path), &(target->path))){
		check_result = FALSE;
	}*/
	return check_result;
}
gboolean    CheckCtSgwDNSTunnel_t(CtSgwDNSTunnel_t *result, CtSgwDNSTunnel_t *target){
    gboolean check_result=TRUE;
	if(!CheckCtSgwStrArray_t(result->DomainName,target->DomainName))
	{
		check_result = FALSE;
	}
	LOGS(CheckCtSgwDNSTunnel_t, result->ServerIP,target->ServerIP);  if (strcmp(result->ServerIP, target->ServerIP)){
		check_result = FALSE;
	}
	LOGI(CheckCtSgwDNSTunnel_t, result->DomainNum,target->DomainNum); /* if (result->DomainNum != target->DomainNum)){
		check_result = FALSE;
	}*/
	
/*	if (CheckCtSgwObjPath_t(&(result->path), &(target->path))){
		check_result = FALSE;
	}*/
	return check_result;
}
gboolean    CheckCtSgw_FileEntry_t(CtSgw_FileEntry_t *result, int num){
    gboolean check_result=TRUE;
	CtSgw_FileEntry_t *pEntry = result;
	int i = 0;

	for (i = 0; i < num; ++i)
	{ 
		LOGS(CheckCtSgw_FileEntry_t, pEntry->FileName,NULL);
		LOGS(CheckCtSgw_FileEntry_t, pEntry->ModifiedTime,NULL); 
		LOGS(CheckCtSgw_FileEntry_t, pEntry->PhysicalFolderName,NULL); 
		LOGI(CheckCtSgw_FileEntry_t, pEntry->IsFolder,NULL);  
		LOGI(CheckCtSgw_FileEntry_t, pEntry->FileSize,NULL); 
		++pEntry;
	}

	return check_result;
}
gboolean    CheckCtSgw_FTPServerConfig_t(CtSgw_FTPServerConfig_t *result, CtSgw_FTPServerConfig_t *target){
    gboolean check_result=TRUE;
	LOGI(CheckCtSgw_FTPServerConfig_t, result->Enable,target->Enable);  if (!Check_data_int(result->Enable,target->Enable,4)){
		check_result = FALSE;
	}
	LOGI(CheckCtSgw_FTPServerConfig_t, result->AllowAnonymous,target->AllowAnonymous);  if (!Check_data_int(result->AllowAnonymous,target->AllowAnonymous,2)){
		check_result = FALSE;
	}
/*	if (CheckCtSgwObjPath_t(&(result->path), &(target->path))){
		check_result = FALSE;
	}*/
	return check_result;
}
gboolean    CheckCtSgw_FTPAccount_t(CtSgw_FTPAccount_t *result, CtSgw_FTPAccount_t *target){
    gboolean check_result=TRUE;
	LOGS(CheckCtSgw_FTPAccount_t, result->Password,target->Password);/*  if (strcmp(result->Password, target->Password)){
		check_result = FALSE;
	}*/
	LOGS(CheckCtSgw_FTPAccount_t, result->UserName,target->UserName); /* if (strcmp(result->UserName, target->UserName)){
		check_result = FALSE;
	}*/

/*	if (CheckCtSgwObjPath_t(&(result->path), &(target->path))){
		check_result = FALSE;
	}*/
	return check_result;
}
gboolean    CheckCtSgw_SambaServerConfig_t(CtSgw_SambaServerConfig_t *result, CtSgw_SambaServerConfig_t *target){
    gboolean check_result=TRUE;
	LOGI(CheckCtSgw_SambaServerConfig_t, result->Enable,target->Enable);  if (!Check_data_int(result->Enable,target->Enable,4)){
		check_result = FALSE;
	}
	LOGI(CheckCtSgw_SambaServerConfig_t, result->AllowAnonymous,target->AllowAnonymous);  if (!Check_data_int(result->AllowAnonymous,target->AllowAnonymous,2)){
		check_result = FALSE;
	}
/*	if (CheckCtSgwObjPath_t(&(result->path), &(target->path))){
		check_result = FALSE;
	}*/
	return check_result;
}
gboolean    CheckCtSgw_SambaAccount_t(CtSgw_SambaAccount_t *result, CtSgw_SambaAccount_t *target){
    gboolean check_result=TRUE;
	LOGS(CheckCtSgw_SambaAccount_t, result->Password,target->Password); /* if (strcmp(result->Password, target->Password)){
		check_result = FALSE;
	}*/
	LOGS(CheckCtSgw_SambaAccount_t, result->UserName,target->UserName); /* if (strcmp(result->UserName, target->UserName)){
		check_result = FALSE;
	}*/
	
/*	if (CheckCtSgwObjPath_t(&(result->path), &(target->path))){
		check_result = FALSE;
	}*/
	return check_result;
}

gboolean    CheckCtSgwDDNServer_t(CtSgwDDNServer_t *result, CtSgwDDNServer_t *target){
    gboolean check_result=TRUE;
	LOGI(CheckCtSgwDDNServer_t, result->DDNSCfgEnabled,target->DDNSCfgEnabled);if (!Check_data_int(result->DDNSCfgEnabled,target->DDNSCfgEnabled,2)){
		check_result = FALSE;
	}
	LOGS(CheckCtSgwDDNServer_t, result->DDNSProvider,target->DDNSProvider); /* if (strcmp(result->DDNSProvider, target->DDNSProvider)){
		check_result = FALSE;

	}*/
	LOGS(CheckCtSgwDDNServer_t, result->DDNSUsername,target->DDNSUsername); /* if (strcmp(result->DDNSUsername, target->DDNSUsername)){
		check_result = FALSE;
	}*/
	
	LOGS(CheckCtSgwDDNServer_t, result->DDNSPassword,target->DDNSPassword); /* if (strcmp(result->DDNSPassword, target->DDNSPassword)){
		check_result = FALSE;
	}*/
	
	LOGI(CheckCtSgwDDNServer_t, result->ServicePort,target->ServicePort); /* if (strcmp(result->ServicePort, target->ServicePort)){
		check_result = FALSE;
	}*/
	LOGS(CheckCtSgwDDNServer_t, result->DDNSDomainName,target->DDNSDomainName); /* if (strcmp(result->DDNSDomainName, target->DDNSDomainName)){
		check_result = FALSE;
	}*/	
	LOGS(CheckCtSgwDDNServer_t, result->DDNSHostName,target->DDNSHostName); /* if (strcmp(result->DDNSHostName, target->DDNSHostName)){
		check_result = FALSE;
	}*/
	
/*	if (CheckCtSgwObjPath_t(&(result->path), &(target->path))){
		check_result = FALSE;

	}*/
	return check_result;
}

gboolean    CheckCtSgw_HttpServerConfig_t(CtSgw_HttpServerConfig_t *result, CtSgw_HttpServerConfig_t *target){
    gboolean check_result=TRUE;
	LOGS(CheckCtSgw_HttpServerConfig_t, result->AdminPassword,target->AdminPassword); /* if (strcmp(result->AdminPassword, target->AdminPassword)){
		check_result = FALSE;
	}*/
	LOGI(CheckCtSgw_HttpServerConfig_t, result->Enable,target->Enable);  if (!Check_data_int(result->Enable,target->Enable,2)){
		check_result = FALSE;
	}
/*	if (CheckCtSgwObjPath_t(&(result->path), &(target->path))){
		check_result = FALSE;
	}*/
	return check_result;
}
