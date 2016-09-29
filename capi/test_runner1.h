#include <gio/gio.h>

#include "capi.h"

#define CtSgwGetDeviceInfo_NUM 1
#define CtSgwGetNetworkInfo_NUM 2
#define CtSgwGetWANConnectionObjs_NUM 3
#define CtSgwGetWANConnection_NUM 4
#define CtSgwGetWANConnectionByName_NUM 5
#define CtSgwGetInternetWANConnection_NUM 6
#define CtSgwGetWiFiInfo_NUM 7
#define CtSgwWiFiDiscClient_NUM 8
#define CtSgwWiFiSetSameSSID_NUM 9
#define CtSgwWiFiCancelSameSSID_NUM 10
#define CtSgwWiFiSetEnable_NUM 11
#define CtSgwGetPONInfo_NUM 12
#define CtSgwGetVoIPInfo_NUM 13
#define CtSgwGetLANHostMgr_NUM 14
#define CtSgwSetLANHostMgr_NUM 15
#define CtSgwGetLANHostObjs_NUM 16
#define CtSgwGetLANHost_NUM 17
#define CtSgwSetLANHost_NUM 18
#define CtSgw_USBSetLabel_NUM 19
#define CtSgwGetDDNSServerObjs_NUM 20
#define CtSgwGetDDNSServerInstance_NUM 21
#define CtSgwSetHttpDownloadTestURL_NUM 22
#define CtSgwGetHttpDownloadTestURL_NUM 23
#define CtSgwStartHttpDownloadTest_NUM 24
#define CtSgwGetHttpDownloadTestResult_NUM 25
#define CtSgwSetDDNSServerInstance_NUM 26
#define CtSgwAddDDNSServerInstance_NUM 27
#define CtSgwDelDDNSServerInstance_NUM 28
#define CtSgwGetPPPoEConfig_NUM 29
#define CtSgwSetWPSConfig_NUM 36
#define CtSgwGetWPSConfig_NUM 37
#define CtSgwSetWPS_NUM 38
#define CtSgwGetWLANDeviceObjs_NUM 39
#define CtSgwGetWLANDevice_NUM 40
#define CtSgwGetWLANDeviceBySSID_NUM 41
#define CtSgwSetWLANDevice_NUM 42
#define CtSgwGetWiFiTimer_NUM 43
#define CtSgwSetWiFiTimer_NUM 44
#define CtSgwGetWiFiExTimerObjs_NUM 45
#define CtSgwGetWiFiExTimer_NUM 46
#define CtSgwSetWiFiExTimer_NUM 47
#define CtSgwAddWiFiExTimer_NUM 48
#define CtSgwDelWiFiExTimer_NUM 49
#define CtSgwGetLED_NUM 50
#define CtSgwSetLED_NUM 51
#define CtSgwGetSleepTimerObjs_NUM 52
#define CtSgwGetSleepTimer_NUM 53
#define CtSgwSetSleepTimer_NUM 54
#define CtSgwAddSleepTimer_NUM 55
#define CtSgwDelSleepTimer_NUM 56
#define CtSgwSysCmdSetDateTime_NUM 57
#define CtSgwSysCmdSetDevName_NUM 58
#define CtSgwSysCmdCheckUAPasswd_NUM 59
#define CtSgwSysCmdSetUAPasswd_NUM 60
#define CtSgwSysCmdCheckTAPasswd_NUM 61
#define CtSgwGetDHCPServer_NUM 71
#define CtSgwSetDHCPServer_NUM 72
#define CtSgwGetPortMappingObjs_NUM 89
#define CtSgwGetPortMapping_NUM 90
#define CtSgwAddPortMapping_NUM 91
#define CtSgwDelPortMapping_NUM 92
#define CtSgwSetPortMapping_NUM 93
#define CtSgw_USBMount_NUM 94
#define CtSgw_USBUnMount_NUM 95
#define CtSgw_GetUSBDeviceObjs_NUM 96
#define CtSgw_GetUSBDevice_NUM 97
#define CtSgw_NAS_GetFileNum_NUM 100
#define CtSgw_NAS_ListFolder_NUM 101
#define CtSgw_NAS_CreateFolter_NUM 102
#define CtSgw_NAS_ReName_NUM 103
#define CtSgw_NAS_Remove_NUM 104
#define CtSgw_NAS_Move_NUM 105
#define CtSgw_NAS_Copy_NUM 106
#define CtSgw_NAS_GetCopyProgress_NUM 107
#define CtSgwAddVPNConnection_NUM 108
#define CtSgwDelVPNConnByName_NUM 109
#define CtSgwAttachVPNConnection_NUM 110
#define CtSgwDetachVPNConnection_NUM 111
#define CtSgwGetVPNConnectionStatus_NUM 112
#define CtSgwSetDNSServerConfig_NUM 113
#define CtSgwGetDNSServerConfig_NUM 114
#define CtSgwFlushDNS_NUM 115
#define CtSgw_SetFtpServer_NUM 118
#define CtSgw_GetFTPServer_NUM 119
#define CtSgw_GetFTPAccountObjs_NUM 120
#define CtSgw_GetFTPAccount_NUM 121
#define CtSgw_AddFtpAccount_NUM 122
#define CtSgw_DelFtpAccount_NUM 123
#define CtSgw_GetSambaServer_NUM 124
#define CtSgw_SetSambaServer_NUM 125
#define CtSgw_GetSambaAccountObjs_NUM 126
#define CtSgw_GetSambaAccount_NUM 127
#define	CtSgw_AddSambaAccount_NUM 128
#define	CtSgw_DelSambaAccount_NUM 129
#define	CtSgw_GetHttpServer_NUM 130
#define	CtSgw_SetHttpServer_NUM 131
#define CtSgwSysCmdSetLOID_NUM 137
#define CtSgwSysCmdRegisterLOID_NUM 138
#define CtSgwSysCmdCheckLOID_NUM 139
#define CtSgwSysCmdReboot_NUM 140
#define CtSgwSysCmdRestore_NUM 141
#define CtSgwSysCmdUpgrade_NUM 142
#define	GVariant_NUM 143
#define CtSgwDelVPNConnection_NUM 180

#define CtSgwWiFiSetRatePriority_NUM 181
#define CtSgwDelLANHost_NUM 182
#define CtSgwSysCmdUploadTroubleLocationInfo_NUM 183
#define CtSgw_USBFormat_NUM 184
#define CtSgwGetDNSTunnelObjs_NUM 185
#define CtSgwSetDNSTunnel_NUM 186
#define CtSgwDelDNSTunnel_NUM 187
#define CtSgwDNSTunnelDetachDomain_NUM 188
#define CtSgwDNSTunnelAttachDomain_NUM 189
#define CtSgwGetPlatformService_NUM 190
#define CtSgwSetPlatformService_NUM 191
#define CtSgwAddDNSTunnel_NUM 192












int start(gchar *command,gchar* extral);
int Process_test_single(gchar* extral);
int Process_test_module(gchar* extral,gchar* extral2);
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


