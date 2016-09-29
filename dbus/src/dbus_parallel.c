#include <dbus_cts.h>
#include <expat.h>
#include "list.h"
#include <dbus_xml_parse.h>
#include <gio/gio.h>
#include <glib/gmessages.h>
extern dbus_bool_t sigint_received;
extern bool        check_notification;
extern bool        timeout_judgement;
extern bool        in_parallel_test;
extern char        log_path[100];
int                test_parallel_second = 300;


/*
   com.ctc.igd1.WANConnectionInfo
   Index,IfName,ServiceList,ConnectionType,VLANID,VLAN8021P,Protocol,ConnectionStatus
   com.ctc.igd1.WANConnectionDb
   l GetWANConnByName, l GetInternetConnIndex
   com.ctc.igd1.NetworkInfo
   UPLink,IPV6,VLANbind,WiFiMode,PONDuration,PPPOEDuration,WANConnectionStatus,
   com.ctc.igd1.LANHostManager
   EnableStats,LANHostMaxNumber,LANHostNumber,ControlListMaxNumber,ControlListNumber
   com.ctc.igd1.WiFiInfo
   Enable,WiFiMode,SameSSIDStatus,RxBytes,RxPkts,RxErrorPkts,RxDropPkts,TxBytes,TxPkts,TxErrorPkts,TxDropPkts
   com.ctc.igd1.WLANConfiguration
   SSID,Enable,PWD
   com.ctc.igd1.WiFiTimer
   StartTime,EndTime,ControlCycle,Enable
   com.ctc.igd1.WiFiTimer1
   WeekDay,Time,Active,Enable
   com.ctc.igd1.SambaServer
   Enable,AllowAnonymous
   com.ctc.igd1.FTPServer
   Enable,AllowAnonymous
   com.ctc.igd1.DNSServerConfig
   Server1,Server2,
   Com.ctc.igd1.usb.Device
   DeviceType,DeviceId,DeviceName
   com.ctc.igd1.HttpDownloadTest
   Status,Result,URL
   com.ctc.igd1.VPNConnection
   vpn_type,tunnel_name,user_id,vpn_mode,vpn_priority,vpn_idletime,account_proxy,vpn_addr,vpn_accout,vpn_pwd,vpn_port,attach_mode,domains,ips,terminal_mac
 */
void dbus_cts_parallel_0()
{
    struct timeval start;
    struct timeval end;

    gettimeofday(&start, NULL);
    for ( ; ; )
    {
        remote_object_method_Lookup("", "", NULL, "Set");
        if (sigint_received)
        {
            exit(0);
        }
        remote_object_method_Lookup("", "", NULL, "Set");
        if (sigint_received)
        {
            exit(0);
        }
        remote_object_method_Lookup("", "", NULL, "Set");
        if (sigint_received)
        {
            exit(0);
        }
        remote_object_method_Lookup("", "", NULL, "Get");
        if (sigint_received)
        {
            exit(0);
        }
        remote_object_method_Lookup("", "", NULL, "Get");
        if (sigint_received)
        {
            exit(0);
        }
        remote_object_method_Lookup("", "", NULL, "Get");
        if (sigint_received)
        {
            exit(0);
        }
        gettimeofday(&end, NULL);
        if (((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec)) > 300000000)      //200000==200ms
        {
            break;
        }
    }
} /* dbus_cts_parallel_0 */


void dbus_cts_parallel_1()
{
    struct timeval start;
    struct timeval end;
    guint32 test_count = 0;

    //check_root_path(1);
    dbus_printf("   Parallel process 1 begin\n");

    gettimeofday(&start, NULL);
    for ( ; ; )
    {
        test_count++;
        remote_object_method_Lookup("/com/ctc/igd1/Info/Network/WANConnectionDb/{i}", "com.ctc.igd1.WANConnectionInfo", NULL, "SCC");
        if (sigint_received)
        {
            exit(0);
        }
        test_count++;
        remote_object_method_Lookup("/com/ctc/igd1/Info/Network/WANConnectionDb", "com.ctc.igd1.WANConnectionDb", NULL, "SCC");
        if (sigint_received)
        {
            exit(0);
        }
        test_count++;
        remote_object_method_Lookup("/com/ctc/igd1/Info/Network", "com.ctc.igd1.NetworkInfo", NULL, "SCC");
        if (sigint_received)
        {
            exit(0);
        }

        test_count++;
        remote_object_method_Lookup("/com/ctc/igd1/Info/Network/WANConnectionDb/{i}", "com.ctc.igd1.WANConnectionInfo", NULL, "Get");
        if (sigint_received)
        {
            exit(0);
        }
        test_count++;
        remote_object_method_Lookup("/com/ctc/igd1/Info/Network/WANConnectionDb", "com.ctc.igd1.WANConnectionDb", NULL, "Get");
        if (sigint_received)
        {
            exit(0);
        }
        test_count++;
        remote_object_method_Lookup("/com/ctc/igd1/Info/Network", "com.ctc.igd1.NetworkInfo", NULL, "Get");
        if (sigint_received)
        {
            exit(0);
        }
        gettimeofday(&end, NULL);
        dbus_printf("   Parallel process 1 test_count=%d,time=%d\n",test_count,(end.tv_sec - start.tv_sec));
        //if(((end.tv_sec - start.tv_sec)*1000000 + (end.tv_usec - start.tv_usec)) > 300000000) //200000==200ms
        if ((end.tv_sec - start.tv_sec) > test_parallel_second)        //200000==200ms
        {
            break;
        }
    }
    dbus_printf("   Parallel process 1 end\n");
} /* dbus_cts_parallel_1 */


void dbus_cts_parallel_2()
{
    struct timeval start;
    struct timeval end;
    guint32 test_count = 0;

    //check_root_path(2);
    dbus_printf("   Parallel process 2 begin\n");

    gettimeofday(&start, NULL);
    for ( ; ; )
    {
        test_count++;
        remote_object_method_Lookup("/com/ctc/igd1/Config/LANHosts", "com.ctc.igd1.LANHostManager", NULL, "SCC");
        if (sigint_received)
        {
            exit(0);
        }
        test_count++;
        remote_object_method_Lookup("/com/ctc/igd1/Info/WiFi", "com.ctc.igd1.WiFiInfo", NULL, "SCC");
        if (sigint_received)
        {
            exit(0);
        }
        test_count++;
        remote_object_method_Lookup("/com/ctc/igd1/Config/WLAN/Devices/{i}", "com.ctc.igd1.WLANConfiguration", NULL, "SCC");
        if (sigint_received)
        {
            exit(0);
        }
        test_count++;
        remote_object_method_Lookup("/com/ctc/igd1/Config/LANHosts", "com.ctc.igd1.LANHostManager", NULL, "Get");
        if (sigint_received)
        {
            exit(0);
        }
        test_count++;
        remote_object_method_Lookup("/com/ctc/igd1/Info/WiFi", "com.ctc.igd1.WiFiInfo", NULL, "Get");
        if (sigint_received)
        {
            exit(0);
        }
        test_count++;
        remote_object_method_Lookup("/com/ctc/igd1/Config/WLAN/Devices/{i}", "com.ctc.igd1.WLANConfiguration", NULL, "Get");
        if (sigint_received)
        {
            exit(0);
        }
        gettimeofday(&end, NULL);
        //if(((end.tv_sec - start.tv_sec)*1000000 + (end.tv_usec - start.tv_usec)) > 300000000) //200000==200ms
         dbus_printf("   Parallel process 2 test_count=%d,time=%d\n",test_count,(end.tv_sec - start.tv_sec));
        if ((end.tv_sec - start.tv_sec) > test_parallel_second)        //200000==200ms
        {
            break;
        }
    }
    dbus_printf("   Parallel process 2 end\n");
} /* dbus_cts_parallel_2 */


void dbus_cts_parallel_3()
{
    struct timeval start;
    struct timeval end;
    guint32 test_count = 0;

    //check_root_path(3);
    dbus_printf("   Parallel process 3 begin\n");

    gettimeofday(&start, NULL);
    for ( ; ; )
    {
        test_count++;
        remote_object_method_Lookup("/com/ctc/igd1/Config/WLAN/Timer", "com.ctc.igd1.WiFiTimer", NULL, "SCC");
        if (sigint_received)
        {
            exit(0);
        }
        test_count++;
        remote_object_method_Lookup("/com/ctc/igd1/Config/WLAN/ExTimers/{i}", "com.ctc.igd1.WiFiTimer1", NULL, "SCC");
        if (sigint_received)
        {
            exit(0);
        }
        test_count++;
        remote_object_method_Lookup("/com/ctc/igd1/Storage/SambaServer", "com.ctc.igd1.SambaServer", NULL, "SCC");
        if (sigint_received)
        {
            exit(0);
        }
        test_count++;
        remote_object_method_Lookup("/com/ctc/igd1/Config/WLAN/Timer", "com.ctc.igd1.WiFiTimer", NULL, "Get");
        if (sigint_received)
        {
            exit(0);
        }
        test_count++;
        remote_object_method_Lookup("/com/ctc/igd1/Config/WLAN/ExTimers/{i}", "com.ctc.igd1.WiFiTimer1", NULL, "Get");
        if (sigint_received)
        {
            exit(0);
        }
        test_count++;
        remote_object_method_Lookup("/com/ctc/igd1/Storage/SambaServer", "com.ctc.igd1.SambaServer", NULL, "Get");
        if (sigint_received)
        {
            exit(0);
        }
        gettimeofday(&end, NULL);
        //if(((end.tv_sec - start.tv_sec)*1000000 + (end.tv_usec - start.tv_usec)) > 300000000) //200000==200ms
         dbus_printf("   Parallel process 3 test_count=%d,time=%d\n",test_count,(end.tv_sec - start.tv_sec));
        if ((end.tv_sec - start.tv_sec) > test_parallel_second)        //200000==200ms
        {
            break;
        }
    }
    dbus_printf("   Parallel process 3 end\n");
} /* dbus_cts_parallel_3 */


void dbus_cts_parallel_4()
{
    struct timeval start;
    struct timeval end;
    guint32 test_count = 0;

    //check_root_path(4);
    dbus_printf("   Parallel process 4 begin\n");

    gettimeofday(&start, NULL);
    for ( ; ; )
    {
        test_count++;
        remote_object_method_Lookup("/com/ctc/igd1/Storage/ftpserver", "com.ctc.igd1.FTPServer", NULL, "SCC");
        if (sigint_received)
        {
            exit(0);
        }
        test_count++;
        remote_object_method_Lookup("/com/ctc/igd1/Network/dns", "com.ctc.igd1.DNSServerConfig", NULL, "SCC");
        if (sigint_received)
        {
            exit(0);
        }
        test_count++;
        remote_object_method_Lookup("/com/ctc/igd1/Storage/usb/devices/{i}", "com.ctc.igd1.usb.Device", NULL, "SCC");
        if (sigint_received)
        {
            exit(0);
        }
        test_count++;
        remote_object_method_Lookup("/com/ctc/igd1/Storage/ftpserver", "com.ctc.igd1.FTPServer", NULL, "Get");
        if (sigint_received)
        {
            exit(0);
        }
        test_count++;
        remote_object_method_Lookup("/com/ctc/igd1/Network/dns", "com.ctc.igd1.DNSServerConfig", NULL, "Get");
        if (sigint_received)
        {
            exit(0);
        }
        test_count++;
        remote_object_method_Lookup("/com/ctc/igd1/Storage/usb/devices/{i}", "com.ctc.igd1.usb.Device", NULL, "Get");
        if (sigint_received)
        {
            exit(0);
        }
        gettimeofday(&end, NULL);
        //if(((end.tv_sec - start.tv_sec)*1000000 + (end.tv_usec - start.tv_usec)) > 300000000) //200000==200ms
         dbus_printf("   Parallel process 4 test_count=%d,time=%d\n",test_count,(end.tv_sec - start.tv_sec));
        if ((end.tv_sec - start.tv_sec) > test_parallel_second)        //200000==200ms
        {
            break;
        }
    }
    dbus_printf("   Parallel process 4 end\n");
} /* dbus_cts_parallel_4 */


void dbus_cts_parallel_5()
{
    struct timeval start;
    struct timeval end;
    guint32 test_count = 0;

    //check_root_path(5);
    dbus_printf("   Parallel process 5 begin\n");

    gettimeofday(&start, NULL);
    for ( ; ; )
    {
        test_count++;
        //sleep(5);
        remote_object_method_Lookup("/com/ctc/igd1/Diagnostics/HttpDownload", "com.ctc.igd1.HttpDownloadTest", NULL, "SCC");
        if (sigint_received)
        {
            exit(0);
        }
        //liuxy 0908-002 begin : change "/com/ctc/igd1/Network/VPN/Connection/Stats" to "/com/ctc/igd1/Network/VPN/Connection/{i}"
        test_count++;
        //remote_object_method_Lookup("/com/ctc/igd1/Network/VPN/Connection/{i}", "com.ctc.igd1.VPNConnection", NULL, "SCC");
        if (sigint_received)
        {
            exit(0);
        }
        test_count++;
        //remote_object_method_Lookup("/com/ctc/igd1/Diagnostics/HttpDownload", "com.ctc.igd1.HttpDownloadTest", NULL, "Get");
        if (sigint_received)
        {
            exit(0);
        }
        //liuxy 0908-002 begin : change "/com/ctc/igd1/Network/VPN/Connection/Stats" to "/com/ctc/igd1/Network/VPN/Connection/{i}"
        test_count++;
        //remote_object_method_Lookup("/com/ctc/igd1/Network/VPN/Connection/{i}", "com.ctc.igd1.VPNConnection", NULL, "Get");
        if (sigint_received)
        {
            exit(0);
        }
        gettimeofday(&end, NULL);
        //if(((end.tv_sec - start.tv_sec)*1000000 + (end.tv_usec - start.tv_usec)) > 300000000) //200000==200ms
         dbus_printf("   Parallel process 5 test_count=%d,time=%d\n",test_count,(end.tv_sec - start.tv_sec));
        if ((end.tv_sec - start.tv_sec) > test_parallel_second)        //200000==200ms
        {
            break;
        }
    }
    dbus_printf("   Parallel process 5 end\n");
}


void dbus_cts_parallel()
{
    in_parallel_test   = true;
    check_notification = false;
    if (fork() != 0)
    {
        if (fork() != 0)
        {
            if (fork() != 0)
            {
                if (fork() != 0)
                {
                    /*//check_root_path(5);
                       //dbus_printf("   Parallel process 5 begin\n");
                       dbus_cts_parallel_5();
                       //dbus_printf("   Parallel process 5 End\n");
                     */
                }
                else
                {
                    /*//check_root_path(4);
                       sleep(7);
                       //dbus_printf("   Parallel process 4 begin\n");
                       dbus_cts_parallel_4();
                       //dbus_printf("   Parallel process 4 end\n");*/
                }
            }
            else
            {
                /*//check_root_path(3);
                   sleep(5);
                   //dbus_printf("   Parallel process 3 begin\n");
                   dbus_cts_parallel_3();
                   //dbus_printf("   Parallel process 3 end\n");*/
            }
        }
        else
        {
            //check_root_path(2);
            sleep(3);
            //dbus_printf("   Parallel process 2 begin\n");
            dbus_cts_parallel_2();
            //dbus_printf("   Parallel process 2 end\n");
        }
    }
    else
    {
        //check_root_path(1);
        //dbus_printf("   Parallel process 1 begin\n");
        //dbus_cts_parallel_1();
        //dbus_printf("   Parallel process 1 end\n");
    }
}
