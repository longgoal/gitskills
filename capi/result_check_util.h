#include <string.h>
#include <gio/gio.h>
#include "capi.h"
gboolean    Checkbool();
gboolean    Check_return_result(int,int);
gboolean    Check_int(int,int);
gboolean    CheckCtSgwObjPath_t(CtSgwObjPath_t *result ,CtSgwObjPath_t *target );
gboolean    CheckCtSgwError_t(CtSgwError_t *result ,CtSgwError_t *target );
gboolean    CheckCtSgwDeviceInfo_t(CtSgwDeviceInfo_t *result ,CtSgwDeviceInfo_t *target );
gboolean 	CheckCtSgwNetworkInfo_t(CtSgwNetworkInfo_t *result ,CtSgwNetworkInfo_t *target );
gboolean 	CheckCtSgwWANConnectionInfo_t(CtSgwWANConnectionInfo_t *result ,CtSgwWANConnectionInfo_t *target );
gboolean 	CheckCtSgwWiFiInfo_t(CtSgwWiFiInfo_t *result ,CtSgwWiFiInfo_t *target );
gboolean 	CheckCtSgwPONInfo_t(CtSgwPONInfo_t *result ,CtSgwPONInfo_t *target );
gboolean 	CheckCtSgwVoIPInfo_t(CtSgwVoIPInfo_t *result ,CtSgwVoIPInfo_t *target );
gboolean 	CheckCtSgwLANHostMgr_t(CtSgwLANHostMgr_t *result ,CtSgwLANHostMgr_t *target );
gboolean 	CheckCtSgwLANHost_t(CtSgwLANHost_t *result ,CtSgwLANHost_t *target );
gboolean	CheckCtSgwHttpDownloadTestResult_t(CtSgwHttpDownloadTestResult_t *result ,CtSgwHttpDownloadTestResult_t *target );
gboolean	CheckCtSgwWPSDevInfo_t(CtSgwWPSDevInfo_t *result ,CtSgwWPSDevInfo_t *target );
gboolean	CheckCtSgwWPS_t(CtSgwWPS_t *result ,CtSgwWPS_t *target );
gboolean	CheckCtSgwWLANDevice_t(CtSgwWLANDevice_t *result ,CtSgwWLANDevice_t *target );
gboolean	CheckCtSgwWiFiTimer_t(CtSgwWiFiTimer_t *result ,CtSgwWiFiTimer_t *target );
gboolean	CheckCtSgwWiFiTimer_t(CtSgwWiFiTimer_t *result ,CtSgwWiFiTimer_t *target );
gboolean	CheckCtSgwWiFiTimer1_t(CtSgwWiFiTimer1_t *result ,CtSgwWiFiTimer1_t *target );
gboolean	CheckCtSgwLED_t(CtSgwLED_t *result ,CtSgwLED_t *target );
gboolean	CheckCtSgwSleepTimer_t(CtSgwSleepTimer_t *result ,CtSgwSleepTimer_t *target );
gboolean	CheckCtSgwPPPoE_t(CtSgwPPPoE_t *result ,CtSgwPPPoE_t *target );
gboolean	CheckCtSgwDHCPServer_t(CtSgwDHCPServer_t *result ,CtSgwDHCPServer_t *target );
gboolean	CheckCtSgwPortMapping_t(CtSgwPortMapping_t *result ,CtSgwPortMapping_t *target );
gboolean	CheckCtSgw_USBFSInfo_t(CtSgw_USBFSInfo_t *result ,CtSgw_USBFSInfo_t *target );
gboolean	CheckCtSgw_USBDevice_t(CtSgw_USBDevice_t *result ,CtSgw_USBDevice_t *target );
gboolean	CheckCtSgwUSBDeviceInfo_t(CtSgwUSBDeviceInfo_t *result ,CtSgwUSBDeviceInfo_t *target );
gboolean	CheckCtSgwVPNConnStats_t(CtSgwVPNConnStats_t *result ,CtSgwVPNConnStats_t *target );
gboolean	CheckCtSgwStrArray_t(CtSgwStrArray_t *result ,CtSgwStrArray_t *target );
gboolean	CheckCtSgwDNSServerConfig_t(CtSgwDNSServerConfig_t *result ,CtSgwDNSServerConfig_t *target );
gboolean	CheckCtSgwDNSServerConfig_t(CtSgwDNSServerConfig_t *result ,CtSgwDNSServerConfig_t *target );
gboolean	CheckCtSgwDNSTunnel_t(CtSgwDNSTunnel_t *result ,CtSgwDNSTunnel_t *target );
gboolean	CheckCtSgwDDNServer_t(CtSgwDDNServer_t *result ,CtSgwDDNServer_t *target );
gboolean	CheckCtSgw_FileEntry_t(CtSgw_FileEntry_t *result ,int num );
gboolean	CheckCtSgw_FTPServerConfig_t(CtSgw_FTPServerConfig_t *result ,CtSgw_FTPServerConfig_t *target );
gboolean	CheckCtSgw_FTPAccount_t(CtSgw_FTPAccount_t *result ,CtSgw_FTPAccount_t *target );
gboolean	CheckCtSgw_SambaServerConfig_t(CtSgw_SambaServerConfig_t *result ,CtSgw_SambaServerConfig_t *target );
gboolean	CheckCtSgw_SambaAccount_t(CtSgw_SambaAccount_t *result ,CtSgw_SambaAccount_t *target );
gboolean	CheckCtSgw_HttpServerConfig_t(CtSgw_HttpServerConfig_t *result ,CtSgw_HttpServerConfig_t *target );
