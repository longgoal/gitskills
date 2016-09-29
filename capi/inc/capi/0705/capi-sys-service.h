#ifndef _CAPI_SYS_SERVICE_H_
#define _CAPI_SYS_SERVICE_H_

#include <string.h>
#include <gio/gio.h>

// Max length of object path
#define MAX_OBJPATH_LEN 255

#define MAX_URL_LEN     255
#define MAX_TIME_LEN    24
#define MAX_LOID_LEN    31
#define MAX_PASSWORD_LEN 31
#define MAX_PATH_LEN    127
#define MAX_DEVNAME_LEN 64


#define STR_LEN_8       8
#define STR_LEN_16      16
#define STR_LEN_24      24
#define STR_LEN_32      32
#define STR_LEN_48      48
#define STR_LEN_64      64
#define STR_LEN_128     128
#define STR_LEN_256     256
#define STR_LEN_512     512
#define STR_LEN_1024    1024


#define FORMAT_BOOL     "b"
#define FORMAT_UINT16   "q"
#define FORMAT_UINT32   "u"
#define FORMAT_UINT64   "t"
#define FORMAT_DOUBLE   "d"
#define FORMAT_STRING   "s"
#define FORMAT_BYTE     "y"
#define FORMAT_INT16    "n"
#define FORMAT_INT32    "i"
#define FORMAT_PATH     "o"

#define IS_EMPTY_STRING(s)  ((s == NULL) || (*s == '\0'))

// Type definition of dbus object path
typedef struct
{
    char str[MAX_OBJPATH_LEN + 1];
} CtSgwObjPath_t;

// Type defination of ARRAY<STRING> entry
typedef struct
{
    gchar str[STR_LEN_64];
} CtSgwStrArray_t;

// Error code
typedef enum
{
    CTSGW_NOK = -1,
    CTSGW_OK = 0,
} CtSgwError_t;


/* ---------------------------------------- */

typedef struct
{
    CtSgwObjPath_t  path;

    guchar      BusinessStatus;
    gchar       Manufacturer[STR_LEN_32];
    gchar       MAC[STR_LEN_24];
    gchar       SWVersion[STR_LEN_32];
    gchar       HDVersion[STR_LEN_32];
    gchar       ITMSProtocolVersion[STR_LEN_32];
    gchar       ProductClass[STR_LEN_24];
    gchar       CPUClass[STR_LEN_32];
    gchar       DevType[STR_LEN_48];
    gchar       DevType1[STR_LEN_32];
    gchar       Capability[STR_LEN_48];
    guint32     FlashSize;
    guint32     RamSize;
    gchar       DevName[STR_LEN_32];
    guchar      CPUUsage;
    guchar      MEMUsage;
    guchar      FlashUsage;
    guint32     SysDuration;

} CtSgwDeviceInfo_t;

typedef struct
{
    CtSgwObjPath_t path;

    guint32     UPLink;
    guchar      IPV6;
    guchar      VLANbind;
    gchar       WiFiMode[STR_LEN_48];
    guint32     PONDuration;
    guint32     PPPoEDuration;
    guchar      LAN1Status;
    guchar      LAN2Status;
    guchar      LAN3Status;
    guchar      LAN4Status;
    gchar       WANLinkStatus[STR_LEN_8];
    gchar       WIFIModuleStatus[STR_LEN_8];
    gchar       WANConnectionStatus[STR_LEN_24];
    gchar       PPPoEDialReason[STR_LEN_16];
    gchar       IPV6_WANConnectionStatus[STR_LEN_16];
    gchar       IPV6_PPPoEDialReason[STR_LEN_24];
    gchar       LANIPAddr[STR_LEN_24];
    gchar       WANIPAddr[STR_LEN_24];
    gchar       WANIPV6Addr[STR_LEN_48];
    guint64     WiFiBytes;
    guint64     WiFiTxBytes;
    guint64     WiFiRxBytes;
    guint64     WANBytes;
    guint64     WANTxBytes;
    guint64     WANRxBytes;
    
} CtSgwNetworkInfo_t;

    
typedef struct
{
    CtSgwObjPath_t path;

    gchar       Index[STR_LEN_8];
    gchar       IfName[STR_LEN_32];
    gchar       ServiceList[STR_LEN_32];
    gchar       ConnectionType[STR_LEN_16];
    guint32     VLANID;
    guint32     VLAN8021P;
    gchar       Protocol[STR_LEN_16];
    gchar       ConnectionStatus[STR_LEN_32];
    gchar       IPAddress[STR_LEN_24];
    gchar       SubnetMask[STR_LEN_24];
    gchar       Gateway[STR_LEN_24];
    gchar       DNS1[STR_LEN_24];
    gchar       DNS2[STR_LEN_24];
    gchar       IPV6_ConnectionStatus[STR_LEN_16];
    gchar       IPV6_IPAddress[STR_LEN_48];
    gchar       IPV6_PrefixLength[STR_LEN_32];
    gchar       IPV6_Gateway[STR_LEN_48];
    gchar       IPV6_DNS1[STR_LEN_48];
    gchar       IPV6_DNS2[STR_LEN_48];
    gchar       IPV6_Prefix[STR_LEN_48];
    guint64     RxBytes;
    guint64     TxBytes;
    guint64     RxPkts;
    guint64     TxPkts;
    
} CtSgwWANConnectionInfo_t;


typedef struct
{
    CtSgwObjPath_t path;

    gboolean    Enable;     // 'rw'
    gchar       WiFiMode[STR_LEN_48]; 
    gboolean    SameSSIDStatus;
    guint64     RxBytes;
    guint64     RxPkts;
    guint64     RxErrorPkts;
    guint64     RxDropPkts;
    guint64     TxBytes;
    guint64     TxPkts;
    guint64     TxErrorPkts;
    guint64     TxDropPkts;
    gboolean    RatePriority;   // 'rw'
    gboolean    RatePriority5G; // 'rw'
    
} CtSgwWiFiInfo_t;


typedef struct
{
    CtSgwObjPath_t path;

    gchar       LOID[STR_LEN_32];
    gchar       Password[STR_LEN_32];
    gdouble     Temperature;
    gdouble     Vottage;
    gdouble     Current;
    gdouble     TXPower;
    gdouble     RXPower;
    gboolean    SupportPONStatusQuery;
    gchar       PONStatus[STR_LEN_32];
    
} CtSgwPONInfo_t;


typedef struct
{
    CtSgwObjPath_t path;

    gchar   VoIPName1[STR_LEN_64];
    gchar   VoIPName2[STR_LEN_64];
    gchar   Line1Status[STR_LEN_32];
    gchar   Line2Status[STR_LEN_32];
    
} CtSgwVoIPInfo_t;


typedef struct
{
    CtSgwObjPath_t path;

    gboolean    EnableStats;
    guint32     LANHostMaxNumber;   // 64 by default
    guint32     LANHostNumber;      // 'r'
    guint32     ControlListMaxNumber;
    guint32     ControlListNumber;  // 'r'
    
} CtSgwLANHostMgr_t;


typedef struct
{
    CtSgwObjPath_t path;

    gchar       MAC[STR_LEN_24];        //'r'
    gchar       DevName[STR_LEN_32];
    gboolean    ControlStatus;          // 'r'
    guchar      InternetAccess;         // "0"-��������룻"1"-������뵫��������"2"-������벢�ҿ�������
    gboolean    StorageAccess;
    guint32     MaxUSBandwidth;
    guint32     MaxDSBandwidth;
    gchar       DevType[STR_LEN_24];    // phone/Pad/PC/STB/ROUTER/SMTDEV/AP/PLC/OTHER
    gchar       IP[STR_LEN_24];         // 'r'
    guchar      ConnectionType;         // 'r'  '0': Wired; '1': Wireless
    guchar      Port;                   // 'r'  
    gchar       Brand[STR_LEN_32];      // 
    gchar       Model[STR_LEN_32];      // 
    gchar       OS[STR_LEN_32];         // 
    gboolean    Active;                 // 'r'
    gchar       LatestActiveTime[STR_LEN_32];   // 'r'
    gchar       LatestInactiveTime[STR_LEN_32]; // 'r'
    guint32     OnlineTime;             // 'r'
    guint64     RxBytes;                // 'r'
    guint64     TxBytes;                // 'r'
    
} CtSgwLANHost_t;


typedef struct
{
    CtSgwObjPath_t path;

    guint32     Status;             // 'r'
    gchar       Result[STR_LEN_256];    // 'r'
    gchar       URL[MAX_URL_LEN + 1];   // 'rw'
    
} CtSgwHttpDownloadTestResult_t;


typedef struct
{
    gchar   Info[STR_LEN_128];
} CtSgwWPSDevInfo_t;


typedef struct
{
    CtSgwObjPath_t path;

    gboolean            Enable;
    guchar              WPSStatus;  // 'r'
    guint32             AttdevNum;  // 'r'
    CtSgwWPSDevInfo_t  *DevInfo;   // 'r'
    
} CtSgwWPS_t;


typedef struct {
    CtSgwObjPath_t path;

    gchar       SSID[STR_LEN_32];
    gboolean    Enable;
    guint32     Channel;
    guint32     ChannelInUse;   // "r"
    gchar       BeaconType[STR_LEN_16];
    gchar       Standard[STR_LEN_24];
    gchar       WEPEncryptionLevel[STR_LEN_24];
    gchar       BasicAuthenticationMode[STR_LEN_24];
    gchar       WPAEncryptionModes[STR_LEN_24];
    gboolean    SSIDHide;
    guint32     RFBand;     // "r"
    guint32     ChannelWidth;
    guint32     GuardInterval;
    guint32     RetryTimeout;
    guint32     Powerlevel;
    guint32     PowerValue;     // "r"
    gchar       PWD[STR_LEN_64];
    
} CtSgwWLANDevice_t;

typedef struct {
    CtSgwObjPath_t path;

    gchar       StartTime[STR_LEN_32];
    gchar       EndTime[STR_LEN_32];
    gchar       ControlCycle[STR_LEN_32];
    gboolean    Enable;
    
} CtSgwWiFiTimer_t;


typedef struct {
    CtSgwObjPath_t path;

    gchar            Time[STR_LEN_32];
    gchar            Active[STR_LEN_16];
    gboolean         Enable;
    guint32          wdLen;
    CtSgwStrArray_t *WeekDay;
    
} CtSgwWiFiTimer1_t;


typedef struct {
    CtSgwObjPath_t path;

    gchar       Status[STR_LEN_16];
    gchar       StartTime[STR_LEN_32];
    gchar       EndTime[STR_LEN_32];
    gchar       ControlCycle[STR_LEN_32];
    gboolean    Enable;
    
} CtSgwLED_t;


typedef struct {
    CtSgwObjPath_t path;

    gchar            Time[STR_LEN_16];
    gchar            Active[STR_LEN_16];
    gboolean         Enable;
    int              dayArrayLen;
    CtSgwStrArray_t *Day;
    
} CtSgwSleepTimer_t;


typedef struct {
    CtSgwObjPath_t path;

    gchar   PPPoEUserName[STR_LEN_64];
    
} CtSgwPPPoE_t;

typedef struct {
    CtSgwObjPath_t path;

    gboolean    Enable;
    gchar       MinAddress[STR_LEN_24];
    gchar       MaxAddress[STR_LEN_24];
    gchar       IPAddr[STR_LEN_24];
    gchar       SubnetMask[STR_LEN_24];
    guint32     LeaseTime;
    
} CtSgwDHCPServer_t;


typedef struct {
    CtSgwObjPath_t path;

    gboolean    Enable;
    guint32     LeaseDuration;
    gchar       RemoteHost[STR_LEN_64];
    guint32     ExternalPort;
    guint32     InternalPort;
    gchar       PortMappingProtocol[STR_LEN_16];
    gchar       InternalClient[STR_LEN_24];
    gchar       Description[STR_LEN_32];
    
} CtSgwPortMapping_t;


typedef enum
{
    CT_USB_DEV_SERIAL = 0x1,
    CT_USB_DEV_CDC_ACM = 0x2,
    CT_USB_DEV_HID = 0x4,
    CT_USB_DEV_STORAGE = 0x8,
} CtUsbDevType;


typedef struct {

    gchar       MountPoint[MAX_PATH_LEN+1] ;    // "r"
    guint64     TotalSize;  // "r"
    guint64     UsedSize;   // "r"
    guint64     FreeSize;   // "r"
    gchar       Label[STR_LEN_32];  // "r"
    
} CtSgw_USBFSInfo_t ;


typedef struct {

    guint16     DeviceType;     // "r"
    gint32      DeviceId;       // "r"
    gchar       DeviceName[STR_LEN_64]; // "r"
    gchar       Vendor[STR_LEN_32];
    gchar       Model[STR_LEN_48];
    gboolean    WriteProtection;
    
} CtSgw_USBDevice_t ;

typedef struct {
    CtSgwObjPath_t path;
    
    CtSgw_USBDevice_t  device;
    CtSgw_USBFSInfo_t  fsinfo;
    
} CtSgwUSBDeviceInfo_t;


// com.ctc.igd1.VPNConnection
typedef struct
{
    CtSgwObjPath_t  path;

    gchar   vpn_type[STR_LEN_16];
    gchar   tunnel_name[STR_LEN_32];
    gchar   user_id[STR_LEN_64];
    guchar  vpn_enable;
    gchar   vpn_mode[STR_LEN_16];
    gchar   vpn_priority[STR_LEN_8];
    gchar   vpn_idletime[STR_LEN_16];
    gchar   account_proxy[STR_LEN_32];
    gchar   vpn_addr[STR_LEN_64];
    gchar   vpn_account[STR_LEN_64];
    gchar   vpn_pwd[STR_LEN_32];
    gchar   vpn_port[STR_LEN_8];
    gchar   attach_mode[STR_LEN_8];
    guint32 domain_num;
    CtSgwStrArray_t   *domains;
    guint32 ip_num;
    CtSgwStrArray_t   *ips;
    guint32 mac_num;
    CtSgwStrArray_t   *terminal_mac;
    
} CtSgwVPNConn_t;

//com.ctc.igd1.VPNConnectionStats
typedef struct
{
    CtSgwObjPath_t  path;

    guint32          arrayLen;
    CtSgwStrArray_t *data;
} CtSgwVPNConnStats_t;

typedef struct
{
    CtSgwObjPath_t  path;

    gchar   Server1[STR_LEN_24];
    gchar   Server2[STR_LEN_24];
    
} CtSgwDNSServerConfig_t;

typedef struct
{
    CtSgwObjPath_t  path;

    gchar   ServerIP[STR_LEN_24];
    guint32 DomainNum;
    CtSgwStrArray_t *DomainName;
} CtSgwDNSTunnel_t;    


typedef struct
{
    CtSgwObjPath_t  path;

    gboolean    DDNSCfgEnabled;
    gchar       DDNSProvider[STR_LEN_64];
    gchar       DDNSUsername[STR_LEN_32];
    gchar       DDNSPassword[STR_LEN_32];
    guint32     ServicePort;
    gchar       DDNSDomainName[STR_LEN_64];
    gchar       DDNSHostName[STR_LEN_64];
    
} CtSgwDDNServer_t;


typedef struct
{
    gchar       FileName[STR_LEN_256];
    gchar       PhysicalFolderName[STR_LEN_256];
    gboolean    IsFolder;
    guint32     FileSize;
    gchar       ModifiedTime[STR_LEN_24];
    
} CtSgw_FileEntry_t;

typedef struct {
    CtSgwObjPath_t path;

    guchar      Enable; //[0,3]
    gboolean    AllowAnonymous;

} CtSgw_FTPServerConfig_t;


typedef struct
{
    CtSgwObjPath_t path;

    gchar   UserName[STR_LEN_32];
    gchar   Password[STR_LEN_32];
    
} CtSgw_FTPAccount_t;


typedef struct {
    CtSgwObjPath_t path;

    guchar      Enable;     //[0, 3]
    gboolean    AllowAnonymous;
    
} CtSgw_SambaServerConfig_t;


typedef struct {
    CtSgwObjPath_t path;

    gchar   UserName[STR_LEN_32];
    gchar   Password[STR_LEN_32];
    
} CtSgw_SambaAccount_t;


typedef struct {
    CtSgwObjPath_t path;
    
    guchar      Enable; //[0,1]
    gchar       AdminPassword[STR_LEN_32];
    
} CtSgw_HttpServerConfig_t;


typedef struct {
    CtSgwObjPath_t path;

    guchar      Appmodel;   // 0/1, 'r'
    gchar       InitUAPwd[STR_LEN_32];  // 'r'
    gchar       InitSSID[STR_LEN_32];   // 'r'
    gchar       InitSSIDPwd[STR_LEN_64];    // 'r'
    gchar       DistAddr[STR_LEN_64];
    gint16      DistStatus;
    gchar       OperAddr[STR_LEN_64];
    gint16      OperStatus;
    gchar       PluginAddr[STR_LEN_64];
    gint16      PluginStatus;
    
} CtSgwPlatformService_t;


/****************************************************************
 *                                                              *
 * Function Declaration                                         *
 *                                                              *
 ****************************************************************/


/*
 * Function Name: CtSgwGetDeviceInfo
 *
 * Description: Get device information
 *
 * Parameter:
 *             info <OUT>:   A CtSgwDeviceInfo_t to contain the device information
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int
CtSgwGetDeviceInfo (CtSgwDeviceInfo_t *info);



/*
 * Function Name: CtSgwGetNetworkInfo
 *
 * Description: Get network information
 *
 * Parameter:
 *             info <OUT>:   A CtSgwNetworkInfo_t to contain the device information
 *
 * Return:   0 on sucess, -1 on error..
 *
 */
int
CtSgwGetNetworkInfo(CtSgwNetworkInfo_t *info);



/*
 * Function Name: CtSgwGetWANConnectionObjs
 *
 * Description  : Return all WAN connection
 *
 * Parameter:
 *             objs <OUT>:   A CtSgwWANConnectionInfo_t array to contain all
 *                           the wan information, the memory is allocated in
 *                           the function, but need to be freed by the caller.
 *
 *            count <OUT>:   The length of the array.
 *
 * Return:   0 on sucess, -1 on error..
 *
 */
int
CtSgwGetWANConnectionObjs(CtSgwWANConnectionInfo_t **objs, guint32 *count);


/*
 * Function Name: CtSgwGetWANConnection
 *
 * Description  : Return a specific WAN connection according to the object path
 *
 * Parameter:
 *             path <IN>:   The object path of the specific wan.
 *             obj <OUT>:   A CtSgwWANConnectionInfo_t struct to contain the wan information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int
CtSgwGetWANConnection(CtSgwObjPath_t path, CtSgwWANConnectionInfo_t *obj);


/*
 * Function Name: CtSgwGetWANConnectionByName
 *
 * Description  : Get wan connection according to the wan name
 *
 * Parameter:
 *             name <IN>:   The wan connection name.
 *             obj <OUT>:   A CtSgwWANConnectionInfo_t struct to contain the wan information.
 *          result <OUT>:   The operation result, 0 on success, other on failure.
 *          errmsg <OUT>:   The error message of the operation(if any). Caller
 *                          should free the memory with g_free() after using it.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int
    CtSgwGetWANConnectionByName(const char *name, CtSgwWANConnectionInfo_t *obj, int *result, char **errmsg);


/*
 * Function Name: CtSgwGetWANConnection
 *
 * Description  : Get the connected wan connection infromation
 *
 * Parameter:
 *             obj <OUT>:   A CtSgwWANConnectionInfo_t struct to contain the wan information.
 *          result <OUT>:   The operation result, 0 on success, other on failure.
 *          errmsg <OUT>:   The error message of the operation(if any). Caller
 *                          should free the memory with g_free() after using it.
 *
 * Return:   0 on sucess, -1 on error or can not find a the connected wan.
 *
 */
int
CtSgwGetInternetWANConnection(CtSgwWANConnectionInfo_t *obj, int *result, char **errmsg);


/*
 * Function Name: CtSgwGetWiFiInfo
 *
 * Description  : Get the WiFi infromation
 *
 * Parameter:
 *     info <OUT>:   A CtSgwWiFiInfo_t struct to contain the WiFi information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */


int
CtSgwGetWiFiInfo(CtSgwWiFiInfo_t *info);


/*
 * Function Name: CtSgwWiFiDiscClient
 *
 * Description  : Disconnect the wireless client whoes mac address is 'devMac' from 
 *                the network with ssid index 'ssidIdx'.
 *
 * Parameter:
 *     devMac <IN>: The MAC address of the wifi client. e.g: 00:22:33:44:55:66
 *    ssidIdx <IN>: The ssid index of the wifi network
 *    result <OUT>: The operation result, 0 on success, other on failure.
 *    errmsg <OUT>: The error message of the operation(if any). Caller
 *                  should free the memory with g_free() after using it.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int
CtSgwWiFiDiscClient(gchar *devMac, gchar *ssidIdx, guint32 *result, char **errmsg);


/*
 * Function Name: CtSgwWiFiSetSameSSID
 *
 * Description  : Set the 2.4G and 5G WiFi network the same. 
 *
 * Parameter:
 *    ssidIdx24 <IN>: The ssid index of 2.4G WIFI network
 *    ssidIdx58 <IN>: The ssid index of 5G wifi network
 *      result <OUT>: The operation result, 0 on success, other on failure.
 *      errmsg <OUT>: The error message of the operation. Caller should
 *                    free the memory with g_free() after using it.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwWiFiSetSameSSID(gchar *ssidIdx24, gchar *ssidIdx58, guint32 *result, gchar **errmsg);


/*
 * Function Name: CtSgwWiFiCancelSameSSID
 *
 * Description  : Cancel the arbitrary setting which makes 2.4G and 5G ssid the same. 
 *
 * Parameter:
 *      result <OUT>: The operation result, 0 on success, other on failure.
 *      errmsg <OUT>: The error message of the operation. Caller should
 *                    free the memory with g_free() after using it.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwWiFiCancelSameSSID(guint32 *result, gchar **errmsg);



/*
 * Function Name: CtSgwWiFiSetEnable
 *
 * Description  : enable/disable the WiFi setting. 
 *
 * Parameter:
 *    enable <IN>: The global wifi status to set
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwWiFiSetEnable (gboolean enable);


/*
 * Function Name: CtSgwWiFiSetRatePriority
 *
 * Description  : enable/disable 2.4G/5G WiFi Rate Priority. 
 *
 * Parameter:
 *    enable <IN>: The 2.4G/5G WiFi Rate Priority status to set
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwWiFiSetRatePriority (gboolean is5g, gboolean enable);


/*
 * Function Name: CtSgwGetPONInfo
 *
 * Description  : Get the PON infromation
 *
 * Parameter:
 *     info <OUT>:   A CtSgwPONInfo_t struct to contain the PON information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int
CtSgwGetPONInfo(CtSgwPONInfo_t *info);


/*
 * Function Name: CtSgwGetVoIPInfo
 *
 * Description  : Get the VoIP infromation
 *
 * Parameter:
 *     info <OUT>:   A CtSgwVoIPInfo_t struct to contain the VoIP information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGetVoIPInfo(CtSgwVoIPInfo_t *info);


/*
 * Function Name: CtSgwGetLANHostMgr
 *
 * Description  : Get the LAN Host Management configuration
 *
 * Parameter:
 *     info <OUT>:   A CtSgwLANHostMgr_t struct to contain the LAN Host Management information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGetLANHostMgr(CtSgwLANHostMgr_t *obj);


/*
 * Function Name: CtSgwSetLANHostMgr
 *
 * Description  : Set the LAN Host Management configuration
 *
 * Parameter:
 *     obj  <IN>:   A CtSgwLANHostMgr_t struct containing the LAN Host Management Setting.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSetLANHostMgr (CtSgwLANHostMgr_t *obj);


/*
 * Function Name: CtSgwGetLANHostObjs
 *
 * Description  : Return all LAN Client information
 *
 * Parameter:
 *             objs <OUT>:   A CtSgwLANHost_t array to contain all the
 *                           lan clients information, the memory is allocated in
 *                           this function, but need to be freed by the caller.
 *
 *            count <OUT>:   The length of the array.
 *
 * Return:   0 on sucess, -1 on error..
 *
 */
int CtSgwGetLANHostObjs(CtSgwLANHost_t **objs, int *count);


/*
 * Function Name: CtSgwGetLANHost
 *
 * Description  : Return a specific LAN hosts according to the object path
 *
 * Parameter:
 *             path <IN>:   The object path of the specific lan host.
 *                          It's something like '/com/ctc/igd1/Config/LANHosts/1'
 *
 *             obj <OUT>:   A CtSgwLANHost_t struct to contain the lan device information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGetLANHost(CtSgwObjPath_t path, CtSgwLANHost_t *obj);


/*
 * Function Name: CtSgwSetLANHost
 *
 * Description  : Set a specific LAN hosts configuration according to the object path
 *
 * Parameter:
 *            path <IN>:   The object path of the specific lan host.
 *                         It's something like '/com/ctc/igd1/Config/LANHosts/1'
 *
 *             obj <IN>:   A CtSgwLANHost_t struct to contain the lan host information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSetLANHost(CtSgwObjPath_t path, CtSgwLANHost_t *obj);


/*
 * Function Name: CtSgwDelLANHost
 *
 * Description  : Delete out-of-control lan host according to the object path
 *
 * Parameter:
 *     path <IN>: The object path of the out-of-control lan host to delete.
 *                It's something like '/com/ctc/igd1/Config/LANHosts/1'
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwDelLANHost(CtSgwObjPath_t path);


/*
 * Function Name: CtSgwSetHttpDownloadTestURL
 *
 * Description  : Set the url address for http download testing
 *
 * Parameter:
 *      url <IN>: The url address of the downloading target
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSetHttpDownloadTestURL(const char *url);


/*
 * Function Name: CtSgwGetHttpDownloadTestURL
 *
 * Description  : Get the url address for http download testing
 *
 * Parameter:
 *      url <OUT>: The url address. Caller should free the
 *                 memory with g_free() after using it.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGetHttpDownloadTestURL(char **url);


/*
 * Function Name: CtSgwStartHttpDownloadTest
 *
 * Description  : Execute the download load testing
 *
 * Parameter:
 *      time <IN>:   The last time of the testing
 *    result <OUT>:  The result of the operation, 0 on success, other on failure.
 *   errdesc <OUT>:  Error message of the operation(if any). Caller
 *                   should free the memory with g_free() after using it.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwStartHttpDownloadTest(guint32 time, guint32 *result, gchar **errdesc);


/*
 * Function Name: CtSgwGetHttpDownloadTestResult
 *
 * Description  : Get the http download load testing result
 *
 * Parameter:
 *      result <OUT>:   a struct to hold http download testing result
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGetHttpDownloadTestResult(CtSgwHttpDownloadTestResult_t *result);


/*
 * Function Name: CtSgwGetSSIDIndexBySSID
 *
 * Description  : Get SSID Index from the given SSID
 *
 * Parameter:
 *             ssid     <IN>:   The wlan ssid.
 *             ssidIdx <OUT>:   The ssid index of the given ssid.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGetSSIDIndexBySSID(char *ssid, unsigned int *ssidIdx);


/*
 * Function Name: CtSgwSetWPSConfig
 *
 * Description  : Set the WPS configuration
 *
 * Parameter:
 *       path <IN>: The object path of the specific wlan, something 
 *                  like '/com/ctc/igd1/Config/WLAN/Devices/1/WPS'
 *
 *        obj <IN>: Contain the WPS configuration
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSetWPSConfig(CtSgwObjPath_t path, CtSgwWPS_t *obj);


/*
 * Function Name: CtSgwGetWPSConfig
 *
 * Description  : Get the WPS configuration
 *
 * Parameter:
 *     path <IN>: The object path of the specific wlan, something 
 *                like '/com/ctc/igd1/Config/WLAN/Devices/{i}/WPS'
 *
 *     obj <OUT>: Contain the WPS configuration. If DevInfo is not
 *                NULL, caller should free its memory 
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGetWPSConfig(CtSgwObjPath_t path, CtSgwWPS_t *obj);


/*
 * Function Name: CtSgwSetWPS
 *
 * Description  : Switching on/off WPS functionality.
 *
 * Parameter:
 *       path <IN>: The object path of the specific wlan, something 
 *                  like '/com/ctc/igd1/Config/WLAN/Devices/1/WPS'
 *     status <IN>: 1 on or 0 off
 *       time <IN>: WPS discovery time
 *    result <OUT>: the result of the operation, 0 on success, other on failure.
 *   errdesc <OUT>: Error message of the operation(if any). Caller
 *                  should free the memory with g_free() after using it.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSetWPS (CtSgwObjPath_t path, gint32 status, guint32 time, guint32 *result, gchar **errdesc);



/*
 * Function Name: CtSgwGetWLANDeviceObjs
 *
 * Description  : Return all WLAN setting information
 *
 * Parameter:
 *             objs <OUT>:   A CtSgwWLANDevice_t array to contain all the
 *                           wlan configure information, the memory is allocated in
 *                           this function, but need to be freed by the caller.
 *
 *            count <OUT>:   The length of the array.
 *
 * Return:   0 on sucess, -1 on error..
 *
 */
int CtSgwGetWLANDeviceObjs(CtSgwWLANDevice_t **objs, guint32 *count);


/*
 * Function Name: CtSgwGetWLANDevice
 *
 * Description  : Return a specific wlan configuration according to the object path
 *
 * Parameter:
 *             path <IN>:   The object path of the specific wlan.
 *             obj <OUT>:   A CtSgwWLANDevice_t struct to contain the wlan information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGetWLANDevice(CtSgwObjPath_t path,  CtSgwWLANDevice_t *obj);


/*
 * Function Name: CtSgwGetWLANDeviceBySSID
 *
 * Description  : Get wlan configuration according to the wlan ssid
 *
 * Parameter:
 *             ssid <IN>:   The wlan ssid.
 *             obj <OUT>:   A CtSgwWLANDevice_t struct to contain the wlan information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGetWLANDeviceBySSID(const char *ssid,  CtSgwWLANDevice_t *obj);


/*
 * Function Name: CtSgwGetWLANDeviceBySSIDIndex
 *
 * Description  : Get WLAN Device by SSID Index
 *
 * Parameter:
 *                ssidIdx  <IN>:   The wlan ssid index.
 *             wlanDevice <OUT>:   The WLAN device whose ssidIdx is 'ssidIdx'.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGetWLANDeviceBySSIDIndex(int ssidIdx, CtSgwWLANDevice_t *wlanDevice);


/*
 * Function Name: CtSgwSetWLANDevice
 *
 * Description  : Set a specific wlan configuration according to the object path
 *
 * Parameter:
 *            path <IN>:   The object path of the specific WLAN device.
 *             obj <IN>:   A CtSgwWLANDevice_t struct to contain the wlan information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSetWLANDevice(CtSgwObjPath_t path, CtSgwWLANDevice_t *obj);


/*
 * Function Name: CtSgwGetWiFiTimer
 *
 * Description  : Return a specific wifi timer configuration according to the object path
 *
 * Parameter:
 *             obj <OUT>:   A CtSgwWiFiTimer_t struct to contain the wifi timer information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGetWiFiTimer(CtSgwWiFiTimer_t *obj);


/*
 * Function Name: CtSgwSetWiFiTimer
 *
 * Description  : Set a specific wifi timer configuration according to the object path
 *
 * Parameter:
 *      obj <IN>: A CtSgwWiFiTimer_t struct containing the timer information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSetWiFiTimer (CtSgwWiFiTimer_t *obj);


/*
 * Function Name: CtSgwGetWiFiExTimerObjs
 *
 * Description  : Return all WiFi Timer configuration
 *
 * Parameter:
 *             objs <OUT>:   A CtSgwWiFiTimer1_t array to contain all the
 *                           wifi timer information. the memory is allocated in
 *                           this function, but need to be freed by the caller.
 *
 *            count <OUT>:   The length of the array.
 *
 * Return:   0 on sucess, -1 on error..
 *
 */
int CtSgwGetWiFiExTimerObjs(CtSgwWiFiTimer1_t **objs, int *count);


/*
 * Function Name: CtSgwGetWiFiExTimer
 *
 * Description  : Return a specific wifi timer configuration according to the object path
 *
 * Parameter:
 *             path <IN>:   The object path of the specific timer.
 *             obj <OUT>:   A CtSgwWiFiTimer1_t struct to contain the wifi timer information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGetWiFiExTimer(CtSgwObjPath_t path, CtSgwWiFiTimer1_t *obj);


/*
 * Function Name: CtSgwSetWiFiExTimer
 *
 * Description  : Set a specific wifi timer configuration according to the object path
 *
 * Parameter:
 *     path <IN>:   The object path of the specific WiFi external Timer.
 *      obj <IN>:   A CtSgwWiFiTimer1_t struct containing the timer information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSetWiFiExTimer (CtSgwObjPath_t path, CtSgwWiFiTimer1_t *obj);


/*
 * Function Name: CtSgwAddWiFiExTimer
 *
 * Description  : add a new wifi timer configuration according to the object path
 *
 * Parameter:
 *      obj <IN>: A CtSgwWiFiTimer1_t struct containing the wifi timer information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwAddWiFiExTimer(CtSgwWiFiTimer1_t *obj);


/*
 * Function Name: CtSgwDelWiFiExTimer
 *
 * Description  : Delete a specific wifi timer configuration according to the object path
 *
 * Parameter:
 *     path <IN>: The object path of the wifi timer to delete.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwDelWiFiExTimer(CtSgwObjPath_t path);


/*
 * Function Name: CtSgwGetLED
 *
 * Description  : Get the power led configuration
 *
 * Parameter:
 *             obj <OUT>:   A CtSgwLED_t struct to contain the led information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGetLED(CtSgwLED_t *obj);


/*
 * Function Name: CtSgwSetLED
 *
 * Description  : Set the power led configuration
 *
 * Parameter:
 *      obj <IN>: CtSgwLED_t struct containing the led information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSetLED(CtSgwLED_t *obj);


/*
 * Function Name: CtSgwGetSleepTimerObjs
 *
 * Description  : Return all sleep Timer configuration
 *
 * Parameter:
 *             objs <OUT>:   A CtSgwSleepTimer_t array to contain all the
 *                           sleep timer information. the memory is allocated in
 *                           this function, but need to be freed by the caller.
 *
 *            count <OUT>:   The length of the array.
 *
 * Return:   0 on sucess, -1 on error..
 *
 */
int CtSgwGetSleepTimerObjs(CtSgwSleepTimer_t **objs, gint32 *count);


/*
 * Function Name: CtSgwGetSleepTimer
 *
 * Description  : Return a specific sleep timer configuration according to the object path
 *
 * Parameter:
 *             path <IN>:   The object path of the specific timer.
 *             obj <OUT>:   A CtSgwSleepTimer_t struct to contain the sleep timer information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGetSleepTimer(CtSgwObjPath_t path, CtSgwSleepTimer_t *obj);


/*
 * Function Name: CtSgwSetSleepTimer
 *
 * Description  : Set a specific sleep timer configuration according to the object path
 *
 * Parameter:
 *     path <IN>:   The object path of the specific Sleep Timer.
 *      obj <IN>:   A CtSgwSleepTimer_t struct containing the timer information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSetSleepTimer(CtSgwObjPath_t path, CtSgwSleepTimer_t *obj);



/*
 * Function Name: CtSgwAddSleepTimer
 *
 * Description  : add a new sleep timer
 *
 * Parameter:
 *      obj <IN>: A CtSgwSleepTimer_t struct containing the sleep timer information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwAddSleepTimer(CtSgwSleepTimer_t *obj);


/*
 * Function Name: CtSgwDelSleepTimer
 *
 * Description  : Delete a specific sleep timer configuration according to the object path
 *
 * Parameter:
 *     path <IN>: The object path of the sleep timer to delete.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwDelSleepTimer(CtSgwObjPath_t path);
    

/*
 * Function Name: CtSgwSysCmdSetLOID
 *
 * Description  : Set the network register code and password
 *
 * Parameter:
 *          loid <IN>: Network register code.
 *      password <IN>: password of the broadband network
 *       result <OUT>: Operation result, 0 on success, other on failure.
 *      errdesc <OUT>: Error message of the operation(if any). Caller
 *                     should free the memory with g_free() after using it.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSysCmdSetLOID(char *loid, char *password, guint32 *result, gchar   **errdesc);




/*
 * Function Name: CtSgwSysCmdRegisterLOID
 *
 * Description  : Start the loid registeration
 *
 * Parameter:
 *       res <OUT>:  The result code, 0 on success, other on fail.
 *   errdesc <OUT>:  The error description of the RegisterLOID operation(if any).
 *                   Caller should free the memory with g_free() after using it.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSysCmdRegisterLOID(guint32 *res, gchar **errdesc);



/*
 * Function Name: CtSgwSysCmdCheckLOID
 *
 * Description  : check whether the broadband identification code is correct or not.
 *
 * Parameter:
 *       errcode <OUT>:  The error code (if any). 
 *        errmsg <OUT>:  The error description (if any). Caller should
 *                       free the memory with g_free() after using it.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSysCmdCheckLOID(guint32 *errcode, gchar **errmsg);




/*
 * Function Name: CtSgwSysCmdSetDateTime
 *
 * Description  : Set device time.
 *
 * Parameter:
 *      datetime <IN>: the time to set.
 *       result <OUT>: The result of set operation, 0 on success, other on fail
 *      errdesc <OUT>: Error description of the operation(if any).
 *                     Caller should free the memory with g_free() after using it.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSysCmdSetDateTime(char *datetime, gint32 *result, gchar **errdesc);




/*
 * Function Name: CtSgwSysCmdSetDevName
 *
 * Description  : Set device name.
 *
 * Parameter:
 *      devname  <IN>: the device name to set
 *          res <OUT>: The result of the operation
 *      errdesc <OUT>: Error description of the operation(if any), caller
 *                     should free the memory with g_free() after using it.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSysCmdSetDevName(char *devname, guint32 *res, gchar **errdesc);



/*
 * Function Name: CtSgwSysCmdReboot
 *
 * Description  : reboot the device.
 *
 * Parameter:
 *      result  <OUT>:  feedback of reboot request. 0 on success, other on failure.
 *     errdesc  <OUT>:  Error description of the operation(if any). caller should
 *                      free the memory with g_free() after using it.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSysCmdReboot(guint32 *result, gchar **errdesc);



/*
 * Function Name: CtSgwSysCmdRestore
 *
 * Description  : reset the device configuration to default setting.
 *
 * Parameter:
 *      result  <OUT>:  feedback of restore default request. 0 on success, other on failure.
 *     errdesc  <OUT>:  Error description of the operation(if any). Caller
 *                      should free the memory with g_free() after using it.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSysCmdRestore(guint32 *result, gchar **errdesc);



/*
 * Function Name: CtSgwSysCmdUpgrade
 *
 * Description  : upgrade the device image.
 *
 * Parameter:
 *       url <IN>: The firmware location.
 *      mode <IN>: The firmware type, the value could be:
 *                  0:  HomeGateway firmware
 *                  1:  OSGI Framework
 *                  2:  Java machine
 *                  3:  NOS
 *                  4:  Andriod
 *                  5:  Gateway DBUS module
 *                  6:  CTC_OPENWRT
 *
 *    method <IN>: Firmware upgrade mode, the value could be:
 *                  0:  Recommand to upgrade
 *                  1:  Mandatory upgrading
 *
 *   result <OUT>:  The feedback of upgrade operation.
 *
 *  errdesc <OUT>:  error description of the operation(if any). Caller
 *                  should free the memory with g_free() after using it.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSysCmdUpgrade(char *url, int mode, int method, guint32 *result, gchar **errdesc);



/*
 * Function Name: CtSgwSysCmdCheckUAPasswd
 *
 * Description  : Check whether the user admin password is correct or not.
 *
 * Parameter:
 *       pass <IN>: The password of the Useradmin account to check.
 *    result <OUT>: The checking result, 0 on success, other on fail.
 *   errdesc <OUT>: Error description of the operation(if any). Caller
 *                  should free the memory with g_free() after using it.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSysCmdCheckUAPasswd(const char *pass, int *result, char **errdesc);


/*
 * Function Name: CtSgwSysCmdSetUAPasswd
 *
 * Description  : Set new password of Useradmin account.
 *
 * Parameter:
 *      pass <IN>: The password of the Useradmin account to set.
 *   result <OUT>: The setting result.
 *  errdesc <OUT>: Error description of the operation(if any). Caller
 *                 should free the memory with g_free() after using it.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSysCmdSetUAPasswd(const char *pass, int *result, char **errdesc);


/*
 * Function Name: CtSgwSysCmdCheckTAPasswd
 *
 * Description  : Check whether the telecomadmin password is correct or not.
 *
 * Parameter:
 *       pass <IN>: The password of the Telecom account to check.
 *    result <OUT>: The checking result.
 *   errdesc <OUT>: Error description of the operation(if any). Caller
 *                  should free the memory with g_free() after using it.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSysCmdCheckTAPasswd(const char *pass, int *result, char **errdesc);


/*
 * Function Name: CtSgwSysCmdUploadTroubleLocationInfo
 *
 * Description  : When DUT is in trouble, call this information 
 *                to collect all the debug inforamtion.
 *
 * Parameter:
 *        uploadurl <IN>: A URL address to where the message file should be uploaded.
 *    faultcategory <IN>: ALL��ȫ����Ϣ
 *                        INTERNET����������
 *                        VOICE����������
 *                        IPTV��IPTV����
 *                        WIFI��WIFI����
 *                        SYSTEM��ϵͳά������
 *
 *          result <OUT>: The checking result.
 *         errdesc <OUT>: Error description of the operation(if any). Caller
 *                        should free the memory with g_free() after using it.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSysCmdUploadTroubleLocationInfo(const char *uploadurl, const char *faultcategory, int *result, char **errdesc);


/*
 * Function Name: CtSgwGetPPPoEConfig
 *
 * Description  : Return the PPPoE configuration
 *
 * Parameter:
 *      obj <OUT>: A CtSgwPPPoE_t struct containing the pppoe configuration.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGetPPPoEConfig(CtSgwPPPoE_t *obj);


/*
 * Function Name: CtSgwGetDHCPServer
 *
 * Description  : Return the dhcp server configuration
 *
 * Parameter:
 *      obj <OUT>: A CtSgwDHCPServer_t struct containing the dhcp server configuration.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGetDHCPServer(CtSgwDHCPServer_t *obj);


/*
 * Function Name: CtSgwSetDHCPServer
 *
 * Description  : Set the dhcp server configuration
 *
 * Parameter:
 *      obj <IN>: A CtSgwDHCPServer_t struct containing the dhcp server configuration.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSetDHCPServer(CtSgwDHCPServer_t *obj);



/*
 * Function Name: CtSgwGetPortMappingObjs
 *
 * Description  : Return port mapping rules
 *
 * Parameter:
 *    objs <OUT>:   A CtSgwPortMapping_t array to contain all the
 *                  port mapping object. The memory is allocated in
 *                  this function, but need to be freed by the caller.
 *
 *   count <OUT>:   The length of the array.
 *
 * Return:   0 on sucess, -1 on error..
 *
 */
int CtSgwGetPortMappingObjs(CtSgwPortMapping_t **objs, int *count);



/*
 * Function Name: CtSgwGetPortMapping
 *
 * Description  : Return a specific port mapping rules according to the object path
 *
 * Parameter:
 *             path <IN>:   The object path of the specific port mapping rule.
 *             obj <OUT>:   A CtSgwPortMapping_t struct to contain the port mapping rule.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGetPortMapping(CtSgwObjPath_t path, CtSgwPortMapping_t *obj);



/*
 * Function Name: CtSgwAddPortMapping
 *
 * Description  : add a new port mapping rule
 *
 * Parameter:
 *      obj <IN>: A CtSgwPortMapping_t struct containing the port mapping rule.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwAddPortMapping(CtSgwPortMapping_t *obj);


/*
 * Function Name: CtSgwDelPortMapping
 *
 * Description  : Delete a specific port mapping rule according to the object path
 *
 * Parameter:
 *     path <IN>: The object path of the port mapping rule to delete.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwDelPortMapping(CtSgwObjPath_t path);


/*
 * Function Name: CtSgwSetPortMapping
 *
 * Description  : Set a specific port mapping rule according to the object path
 *
 * Parameter:
 *     path <IN>: The object path of the specific PortMapping rule. 
 *                It's something like '/com/ctc/igd1/Config/PortMapping/1'
 *
 *      obj <IN>: A CtSgwPortMapping_t struct containing the rule.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSetPortMapping(CtSgwObjPath_t path, CtSgwPortMapping_t *obj);


/*
 * Function Name: CtSgw_USBMount
 *
 * Description  : mount a usb device whose device id is devid, return the mount point
 *
 * Parameter:
 *        devid  <IN>: device id to identify a USB device.
 *
 *   mount_path <OUT>: the mount point of the USB device. Caller
 *                     should free the memory with g_free() after using it.
 *
 *          res <OUT>: The result of the mount operation
 *
 *      errdesc <OUT>: Error description of the operation(if any). Caller
 *                     should free the memory with g_free() after using it.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_USBMount(guint32 devid, char **mount_path, guint32 *res, gchar **errdesc);


/*
 * Function Name: CtSgw_USBUnMount
 *
 * Description  : unmount a usb device who was mounted to mount_path.
 *
 * Parameter:
 *    mount_path <IN>: the mount point of the USB device
 *          res <OUT>: The result of the mount operation
 *      errdesc <OUT>: Error description of the operation(if any). Caller
 *                     should free the memory with g_free() after using it.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_USBUnMount(gchar *mount_path, guint32 *res, gchar **errdesc);



/*
 * Function Name: CtSgw_USBSetLabel
 *
 * Description  : Set the label of a usb file system.
 *
 * Parameter:
 *         path <IN>: The path of the usb device. something like '/com/ctc/igd1/usb/devices/1'
 *        label <IN>: The label to set.
 *     result  <OUT>: The operation result.
 *    errdesc  <OUT>: The error message of the operation if any. Caller
 *                    should free the memory with g_free() after using it. 
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_USBSetLabel(CtSgwObjPath_t path, gchar *label, guint32 *result, gchar **errdesc);


/*
 * Function Name: CtSgw_USBFormat
 *
 * Description  : Set the label of a usb file system.
 *
 * Parameter:
 *         path <IN>: The path of the usb device. something like '/com/ctc/igd1/usb/devices/1'
 *     result  <OUT>: The operation result.
 *    errdesc  <OUT>: The error message of the operation if any. Caller
 *                    should free the memory with g_free() after using it. 
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_USBFormat(CtSgwObjPath_t path, guint32 *result, gchar **errdesc);


/*
 * Function Name: CtSgw_GetUSBDeviceObjs
 *
 * Description  : Return all the usb device
 *
 * Parameter:
 *    objs <OUT>:   A CtSgwUSBDeviceInfo_t array to contain all the
 *                  usb device object. The memory is allocated in
 *                  this function, but need to be freed by the caller.
 *
 *   count <OUT>:   The length of the array.
 *
 * Return:   0 on sucess, -1 on error..
 *
 */
int CtSgw_GetUSBDeviceObjs(CtSgwUSBDeviceInfo_t **objs, int *count);


/*
 * Function Name: CtSgw_GetUSBDevice
 *
 * Description  : Return a specific usb device according to the object path
 *
 * Parameter:
 *             path <IN>:   The object path of the specific usb device.
 *             obj <OUT>:   A CtSgwUSBDeviceInfo_t struct to contain the usb device.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_GetUSBDevice(CtSgwObjPath_t path, CtSgwUSBDeviceInfo_t *obj);

/*
 * Function Name: CtSgw_NAS_GetFileNum
 *
 * Description  : Return the file number of a specified folder.
 *
 * Parameter:
 *     foldername <IN>:   The folder name.
 *           num <OUT>:   The file Number
 *        result <OUT>:   The result of the operation. 0 on success, other on failure.
 *      errdesc  <OUT>:   Error description of the operation(if any). User should free
 *                        the memory with g_free() after using it.
 *
 * Return:   0 on success, -1 on fail.
 *
 */
int CtSgw_NAS_GetFileNum(gchar *foldername, guint32 *num, guint32 *result, gchar **errdesc);



/*
 *      dest <IN>:  The destination address of the wan ping testing
 * Function Name: CtSgw_NAS_ListFolder
 *
 * Description  : List all the files and folders in a specified folder.
 *
 * Parameter:
 *     foldername  <IN>:   The folder name.
 *     startIndex  <IN>:   The start index of folder file.
 *       endIndex  <IN>:   The end index of folder file.
 *       fileList <OUT>:   The entries represent the files and folders.
 *         result <OUT>:   The result of the operation. 0 on success, other on failure.
 *       errdesc  <OUT>:   Error description of the operation(if any). User should free
 *                         the memory with g_free() after using it.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_NAS_ListFolder(char *folderName, guint32 startIndex, guint32 endIndex, CtSgw_FileEntry_t **fileList, guint32 *result, gchar **errdesc);



/*
 * Function Name: CtSgw_NAS_CreateFolter
 *
 * Description  : Create a folder with the specified name.
 *
 * Parameter:
 *     foldername  <IN>:   The folder name.
 *        result  <OUT>:   The result of the operation.
 *       errdesc  <OUT>:   Error description of the operation(if any). User should free
 *                         the memory with g_free() after using it.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_NAS_CreateFolter(gchar *folderName, guint32 *result, gchar **errdesc);


/*
 * Function Name: CtSgw_NAS_ReName
 *
 * Description  : Change the name of a file/folder.
 *
 * Parameter:
 *        oldName  <IN>:   The old name.
 *        newName  <IN>:   The new name.
 *        result  <OUT>:   The result of the operation.
 *       errdesc  <OUT>:   Error description of the operation(if any). User should free
 *                         the memory with g_free() after using it.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_NAS_ReName(gchar *oldName, gchar *newName, guint32 *result, gchar **errdesc);


/*
 * Function Name: CtSgw_NAS_Remove
 *
 * Description  : Remove a file/folder.
 *
 * Parameter:
 *      name  <IN>:   The file/folder name.
 *    result <OUT>:   The result of the operation.
 *   errdesc <OUT>:   Error description of the operation(if any). User should free
 *                    the memory with g_free() after using it.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_NAS_Remove(gchar *name, guint32 *result, gchar **errdesc);


/*
 * Function Name: CtSgw_NAS_Move
 *
 * Description  : Move a file/folder to another location.
 *
 * Parameter:
 *        filename  <IN>:   The source location.
 *  destFolderName  <IN>:   The destination location.
 *          result <OUT>:   The result of the operation.
 *         errdesc <OUT>:   Error description of the operation(if any). User should free
 *                          the memory with g_free() after using it.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_NAS_Move(gchar *filename, char *destFolderName, guint32 *result, gchar **errdesc);


/*
 * Function Name: CtSgw_NAS_Copy
 *
 * Description  : Copy a file/folder to another location.
 *
 * Parameter:
 *            name  <IN>:   The source file name.
 *  destFolderName  <IN>:   The destination file name.
 *        transId  <OUT>:   The copying transaction id
 *          result <OUT>:   The result of the operation.
 *         errdesc <OUT>:   Error description of the operation(if any). User should free
 *                          the memory with g_free() after using it.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_NAS_Copy(gchar *name, gchar *destFolderName, int *transId, guint32 *result, gchar **errdesc);


/*
 * Function Name: CtSgw_NAS_GetCopyProgress
 *
 * Description  : Get the copy progress.
 *
 * Parameter:
 *      transactionId  <IN>:   The transactionId of the copy progress.
 *         percentage <OUT>:   Percentage of the copying progress
 *             result <OUT>:   The result of the operation
 *            errdesc <OUT>:   Error description of the operation(if any). Caller
 *                             should free the memory with g_free() after using it.
 *
 * Return:   0 on success, -1 on failure.
 *
 */
int CtSgw_NAS_GetCopyProgress(guint32 transactionId, guint32 *percentage, gint32 *result, gchar **errdesc);


/*
 * Function Name: CtSgwGetVPNConnObjs
 *
 * Description  : Return all the VPN Connections.
 *
 * Parameter:
 *    objs <OUT>:   A pointer to CtSgwVPNConn_t array to contain all
 *                  the VPN connection object. The memory is allocated in
 *                  this function, but need to be freed by the caller.
 *
 *   count <OUT>:   The length of the array.
 *
 * Return:   0 on sucess, -1 on error..
 *
 */
gint32 CtSgwGetVPNConnObjs(CtSgwVPNConn_t **objs, gint32 *count);


/*
 * Function Name: CtSgwAddVPNConnection
 *
 * Description  : Create WAN VPN tunnel.
 *
 * Parameter:
 *      obj  <IN>:   VPN configure of the new connection to add.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwAddVPNConnection(CtSgwVPNConn_t *obj);


/*
 * Function Name: CtSgwDelVPNConnection
 *
 * Description  : Delete a specific VPN Connection according to the object path
 *
 * Parameter:
 *     path <IN>: The object path of the VPN Connection to delete.
 *                It's something like '/com/ctc/igd1/Network/VPN /Connection/1'
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwDelVPNConnection(CtSgwObjPath_t path);



/*
 * Function Name: CtSgwDelVPNConnByName
 *
 * Description  : Remove the tunnel of the given name
 *
 * Parameter:
 *      tunnelName  <IN>:   The tunnel name.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwDelVPNConnByName(const char *tunnelName);



/*
 * Function Name: CtSgwAttachVPNConnection
 *
 * Description  : Attach the data flow to VPN connection
 *
 * Parameter:
 *    tunnelName  <IN>:   The tunnel name.
 *    ipAddrList  <IN>:   List of the IP addresses need to be attached to the VPN connection whose name is tunnelName 
 *     ipAddrNum  <IN>:   Number of IP addresses in the ipAddrList
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwAttachVPNConnection(const char *tunnelName, const gchar *ipAddrList, int ipAddrNum);



/*
 * Function Name: CtSgwDetachVPNConnection
 *
 * Description  : Detach the data flow from L2TP VPN tunnel
 *
 * Parameter:
 *    tunnelName  <IN>:   The tunnel name.
 *    ipAddrList  <IN>:   List of the IP addresses need to be detached from the L2TP tunnel whose name is tunnelName 
 *     ipAddrNum  <IN>:   Number of IP addresses in the ipAddrList
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwDetachVPNConnection(const char *tunnelName, const char *ipAddrList, int ipAddrNum);



/*
 * Function Name: CtSgwGetVPNConnectionStatus
 *
 * Description  : Query the status of all vpn connection
 *
 * Parameter:
 *      path <IN>:  The object path of the VPN Connection to delete.
 *                  It's something like '/com/ctc/igd1/Network/VPN /Connection/1/Stats'
 *
 *      obj <OUT>:  The object containning the VPN connection status.
 *                  If obj->arrayLen > 0, user should free obj->data after using this object.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGetVPNConnectionStatus(CtSgwObjPath_t path, CtSgwVPNConnStats_t *obj);


/*
 * Function Name: CtSgwSetDNSServerConfig
 *
 * Description  : Set the dns server configuration.
 *
 * Parameter:
 *     obj  <IN>: A CtSgwDNSServerConfig_t struct with dns server configuration.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSetDNSServerConfig(CtSgwDNSServerConfig_t *dnsServer);


/*
 * Function Name: CtSgwGetDNSServerConfig
 *
 * Description  : Get the dns server configuration.
 *
 * Parameter:
 *     obj <OUT>: A CtSgwDNSServerConfig_t struct to contain dns server configuration.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGetDNSServerConfig(CtSgwDNSServerConfig_t *dnsServer);


/*
 * Function Name: CtSgwFlushDNS
 *
 * Description  : Flush the system DNS cache.
 *
 * Parameter:
 *     result  <OUT>:   The operation result.
 *     errmsg  <OUT>:   The error message of the operation if any. Caller
 *                      should free the memory with g_free() after using it.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwFlushDNS(guint32 *result, gchar **errdesc);


/*
 * Function Name: CtSgwGetDNSTunnelObjs
 *
 * Description  : Return all the DNS Tunnel.
 *
 * Parameter:
 *    objs <OUT>:   A pointer to CtSgwDNSTunnel_t array to contain all
 *                  the DNS Tunnel objects. The memory is allocated in
 *                  this function, but need to be freed by the caller.
 *                  Caller should also free the 'DomainName' member in
 *                  'objs' this function returned.
 *
 *   count <OUT>:   The length of the array.
 *
 * Return:   0 on sucess, -1 on error..
 *
 */
gint32 CtSgwGetDNSTunnelObjs(CtSgwDNSTunnel_t **objs, gint32 *count);


/*
 * Function Name: CtSgwSetDNSTunnel
 *
 * Description  : Set DNS tunnel object with the given domain name and server
 *
 * Parameter:
 *            path <IN>:   The object path of the specific ddns server configuration.
 *                         It's something like '/com/ctc/igd1/Network/dns/1'
 *
 *     domain_name <IN>:   The dns domain name. Multiple domain name should be separated by ';'
 *
 *          server <IN>:   Server address.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSetDNSTunnel(CtSgwObjPath_t path, const char *server, const char *domain_name);


/*
 * Function Name: CtSgwDelDNSTunnel
 *
 * Description  : Delete a specific DNS Tunnel according to the object path
 *
 * Parameter:
 *     path <IN>: The object path of the DNS Tunnel to delete.
 *                It's something like '/com/ctc/igd1/Network/dns/1'
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwDelDNSTunnel(CtSgwObjPath_t path);


/*
 * Function Name: CtSgwAddDNSTunnel
 *
 * Description  : Add DNS tunnel with the domain name and server
 *
 * Parameter:
 *    domain_name  <IN>:   The dns domain name.
 *          server <IN>:   Server address.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwAddDNSTunnel(const char *server, const char *domain_name);


/*
 * Function Name: CtSgwDNSTunnelDetachDomain
 *
 * Description  : Detach domain name from the DNS Tunnel with the specified server ip.
 *
 * Parameter:
 *       serverip  <IN>:   The server ip of a DNS Tunnel object.
 *    domain_name  <IN>:   The dns domain name.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwDNSTunnelDetachDomain(const char *serverip, const char *domain_name);


/*
 * Function Name: CtSgwDNSTunnelAttachDomain
 *
 * Description  : Attach domain name to the DNS Tunnel with the specified server ip.
 *
 * Parameter:
 *       serverip  <IN>:   The server ip of a DNS Tunnel object.
 *    domain_name  <IN>:   The dns domain name.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwDNSTunnelAttachDomain(const char *serverip, const char *domain_name);


/*
 * Function Name: CtSgwGetDDNSServerObjs
 *
 * Description  : Return all the DDNS server account
 *
 * Parameter:
 *    objs <OUT>:   A pointer to CtSgwDDNServer_t array to contain all
 *                  the DDNS server account object. The memory is allocated in
 *                  this function, but need to be freed by the caller.
 *
 *   count <OUT>:   The length of the array.
 *
 * Return:   0 on sucess, -1 on error..
 *
 */
int CtSgwGetDDNSServerObjs(CtSgwDDNServer_t **objs, int *count);


/*
 * Function Name: CtSgwGetDDNSServerInstance
 *
 * Description  : Return a specific DDNS server instance according to the object path
 *
 * Parameter:
 *             path <IN>:   The object path of the specific ddns server account.
 *             obj <OUT>:   A CtSgwDDNServer_t struct to contain the ddns server account rule.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGetDDNSServerInstance(CtSgwObjPath_t path, CtSgwDDNServer_t *obj);


/*
 * Function Name: CtSgwSetDDNServerInstance
 *
 * Description  : Set a specific ddns server configuration according to the object path
 *
 * Parameter:
 *     path <IN>:   The object path of the specific ddns server configuration.
 *      obj <IN>:   A CtSgwDDNServer_t struct containing the timer information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSetDDNSServerInstance (CtSgwObjPath_t path, CtSgwDDNServer_t *obj);



/*
 * Function Name: CtSgwAddDDNSServerInstance
 *
 * Description  : add a DDNS server account
 *
 * Parameter:
 *      obj <IN>: A CtSgwDDNServer_t struct containing the ddns server account.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwAddDDNSServerInstance(CtSgwDDNServer_t *obj);



/*
 * Function Name: CtSgwDelDDNSServerInstance
 *
 * Description  : Delete a specific ddns server account according to the object path
 *
 * Parameter:
 *     path <IN>: The object path of the ddns server account to delete.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwDelDDNSServerInstance(CtSgwObjPath_t path);


/*
 * Function Name: CtSgw_SetFtpServer
 *
 * Description  : Set the ftp server configuration.
 *
 * Parameter:
 *     obj  <IN>: A CtSgw_FTPServerConfig_t struct with ftp server configuration.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_SetFtpServer(CtSgw_FTPServerConfig_t *obj);


/*
 * Function Name: CtSgw_SetFtpServer
 *
 * Description  : Get the ftp server configuration.
 *
 * Parameter:
 *     obj <OUT>: A CtSgw_FTPServerConfig_t struct to contain ftp server configuration.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_GetFTPServer(CtSgw_FTPServerConfig_t *obj);


/*
 * Function Name: CtSgw_GetFTPAccountObjs
 *
 * Description  : Return all the ftp account
 *
 * Parameter:
 *    objs <OUT>:   A pointer to CtSgw_FTPAccount_t array to contain all
 *                  the ftp account object. The memory is allocated in
 *                  this function, but need to be freed by the caller.
 *
 *   count <OUT>:   The length of the array.
 *
 * Return:   0 on sucess, -1 on error..
 *
 */
int CtSgw_GetFTPAccountObjs(CtSgw_FTPAccount_t **objs, int *count);


/*
 * Function Name: CtSgw_GetFTPAccount
 *
 * Description  : Return a specific ftp account according to the object path
 *
 * Parameter:
 *             path <IN>:   The object path of the specific ftp account.
 *             obj <OUT>:   A CtSgw_FTPAccount_t struct to contain the ftp account rule.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_GetFTPAccount(CtSgwObjPath_t path, CtSgw_FTPAccount_t *obj);


/*
 * Function Name: CtSgw_AddFtpAccount
 *
 * Description  : add a ftp account
 *
 * Parameter:
 *      obj <IN>: A CtSgw_FTPAccount_t struct containing the ftp account.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_AddFtpAccount(CtSgw_FTPAccount_t *obj);


/*
 * Function Name: CtSgw_DelFtpAccount
 *
 * Description  : Delete a specific ftp account according to the object path
 *
 * Parameter:
 *     path <IN>: The object path of the ftp account to delete.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_DelFtpAccount(CtSgwObjPath_t path);


/*
 * Function Name: CtSgw_GetSambaServer
 *
 * Description  : Get the samba server configuration.
 *
 * Parameter:
 *     obj <OUT>: A CtSgw_SambaServerConfig_t struct to contain samba server configuration.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_GetSambaServer(CtSgw_SambaServerConfig_t *obj);


/*
 * Function Name: CtSgw_SetSambaServer
 *
 * Description  : Set the samba server configuration.
 *
 * Parameter:
 *     obj  <IN>: A CtSgw_SambaServerConfig_t struct with samba server configuration.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_SetSambaServer(CtSgw_SambaServerConfig_t *obj);


/*
 * Function Name: CtSgw_GetSambaAccountObjs
 *
 * Description  : Return all the samba account
 *
 * Parameter:
 *    objs <OUT>:   A pointer to CtSgw_SambaAccount_t array to contain all
 *                  the samba account object. The memory is allocated in
 *                  this function, but need to be freed by the caller.
 *
 *   count <OUT>:   The length of the array.
 *
 * Return:   0 on sucess, -1 on error..
 *
 */
int CtSgw_GetSambaAccountObjs(CtSgw_SambaAccount_t **objs, int *count);


/*
 * Function Name: CtSgw_GetSambaAccount
 *
 * Description  : Return a specific samba account according to the object path
 *
 * Parameter:
 *             path <IN>:   The object path of the specific samba account.
 *             obj <OUT>:   A CtSgw_SambaAccount_t struct to contain the samba account rule.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_GetSambaAccount(CtSgwObjPath_t path, CtSgw_SambaAccount_t *obj);


/*
 * Function Name: CtSgw_AddSambaAccount
 *
 * Description  : add a samba account
 *
 * Parameter:
 *      obj <IN>: A CtSgw_SambaAccount_t struct containing the samba account.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_AddSambaAccount(CtSgw_SambaAccount_t *obj);


/*
 * Function Name: CtSgw_DelSambaAccount
 *
 * Description  : Delete a specific samba account according to the object path
 *
 * Parameter:
 *     path <IN>: The object path of the samba account to delete.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_DelSambaAccount(CtSgwObjPath_t path);


/*
 * Function Name: CtSgw_GetHttpServer
 *
 * Description  : Get the http server configuration.
 *
 * Parameter:
 *     obj <OUT>: A CtSgw_HttpServerConfig_t struct to contain http server configuration.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_GetHttpServer(CtSgw_HttpServerConfig_t *obj);


/*
 * Function Name: CtSgw_SetHttpServer
 *
 * Description  : Set the http server configuration.
 *
 * Parameter:
 *     obj  <IN>: A CtSgw_HttpServerConfig_t struct with http server configuration.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_SetHttpServer(CtSgw_HttpServerConfig_t *obj);


/*
 * Function Name: CtSgwGetPlatformService
 *
 * Description  : Get the Platform Service configuration.
 *
 * Parameter:
 *     obj <OUT>: A CtSgwPlatformService_t struct to contain Platform Service configuration.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGetPlatformService(CtSgwPlatformService_t *obj);


/*
 * Function Name: CtSgwSetPlatformService
 *
 * Description  : Set the platform service configuration.
 *
 * Parameter:
 *     obj  <IN>: A CtSgwPlatformService_t struct with platform service configuration.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSetPlatformService(CtSgwPlatformService_t *obj);



#endif
