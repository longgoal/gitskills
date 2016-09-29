/*#include<stdio.h>
 #include <string.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <fcntl.h> */
#include "dbus_log.h"
#include <dbus/dbus.h>
#include <stdio.h>
#include <dbus_xml_parse.h>
#include <gio/gio.h>

//#include <gnu/libc-version.h>


/*int main()
   {
   Checkoverlayfs();
   checkOSversion();
   return 0;
   }
 */
int comparestring(char source[])
{
    char str[] = "overlayfs";
    char *pdest;
    int  result;

    pdest  = strstr(source, str);
    result = pdest - source + 1;

    if (pdest != NULL)
    {
        return(0);
    }
    else
    {
        return(-1);
    }
}


extern char mountcontent[100];
extern char mount_cmd[100];
extern char linuxkernelversion[100];
extern char uname_cmd[100];


int Checkoverlayfs()
{
    char *filename = mountcontent;  //????????????
    FILE *fp;
    char StrLine[1024];             //????????б┴????ио????????????б┴??????????

    fp = fopen(filename, "r");
    if (fp)
    {
        fclose(fp);
        remove(filename);
    }

    {
        system(mount_cmd);
    }

    if ((fp = fopen(filename, "r")) == NULL) //??????????????????????????????????бу????????
    {
        dbus_printf("Error, can't generate %s\n", filename);
        return(-1);
    }
    while (!feof(fp))
    {
        fgets(StrLine, 1024, fp); //????????????????
        int i = comparestring(StrLine);
        if (i == 0)
        {
            //dbus_printf("find the result");
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Current system", "", "", "", "", "", "OK", "support overlayfs", "checkoverlayfs", "");
            fclose(fp);
            remove(filename);
            return(0);
        }
    }
    fclose(fp);
    remove(filename);
    dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Current system", "", "", "", "", "", "Failed", "Don't support overlayfs", "checkoverlayfs", "");
    return(-1);
}


char *substring(char *ch, int pos, int length)
{
    char *pch   = ch;
    char *subch = (char *)calloc(sizeof(char), length + 1);
    int  i;

    pch = pch + pos;
    for (i = 0; i < length; i++)
    {
        subch[i] = *(pch++);
    }
    subch[length] = '\0';
    return(subch);
}


int checkOSversion()
{
    FILE *fp;
    char str[100];

    fp = fopen(linuxkernelversion, "r");
    if (fp)
    {
        fclose(fp);
        remove(linuxkernelversion);
    }

    system(uname_cmd);
    fp = fopen(linuxkernelversion, "rb");
    if (fp != NULL)
    {
        fgets(str, 100, fp);
        fclose(fp);
        remove(linuxkernelversion);
    }
    else
    {
        return(dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Current system", "", "", "", "", "", "Failed", "Can't get kernel info", __func__, ""));
    }
    //printf("%s\n",str);
    char delims[] = ".";
    char *result  = NULL;
    int  v1       = 0;
    int  v2       = 0;
    int  v3       = 0;
    int  v        = 0;

    char *p = str;
    int  n;
    for (n = 0; n < (strlen(str) - 2); n++)
    {
        if (v == 0)
        {
            if ((*p) >= '0' && (*p) <= '9')
            {
                v1 *= 10;
                v1  = (*p) - '0';
            }
            else if ((*p) = '.')
            {
                v = 1;
            }
        }
        else if (v == 1)
        {
            if ((*p) >= '0' && (*p) <= '9')
            {
                v2 *= 10;
                v2  = (*p) - '0';
            }
            else if ((*p) = '.')
            {
                v = 2;
            }
        }
        else if (v == 2)
        {
            if ((*p) >= '0' && (*p) <= '9')
            {
                v3 *= 10;
                v3  = (*p) - '0';
            }
            else
            {
                v = 3;
            }
        }
        //else
        //break;
        p++;
    }
    (*p) = '\0';
//dbus_printf("version= %d.%d.%d\n",v1,v2,v3);
    if (v1 > 3)
    {
        //printf("%s\n","version >=3.18");
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Current system", "", "", "", "", "", "OK", "kernel version > 3.0", "checkosversion", str);
        return(0);
    }
    else
    {
        if (v2 >= 0)
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Current system", "", "", "", "", "", "OK", "kernel version > 3.0", "checkosversion", str);
        }
        else
        {
            //printf("%s\n","version <=3.18");
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Current system", "", "", "", "", "", "Failed", "kernel version < 3.0", "checkosversion", str);
        }
        return(-1);
    }
} /* checkOSversion */

extern char overlayfs[100];
extern char overlayfs_cmd[100];


int checkoverlayfs()
{
    FILE *fp;
    char str[100];

    fp = fopen(overlayfs, "r");
    if (fp)
    {
        fclose(fp);
        remove(overlayfs);
    }

    system(overlayfs_cmd);
    fp = fopen(overlayfs, "rb");
    if (fp != NULL)
    {
        fgets(str, 100, fp);
        fclose(fp);
        remove(overlayfs);
    }
    else
    {
        return(dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Current system", "", "", "", "", "", "Failed", "Can't get overlayfs info", __func__, ""));
    }
    //printf("%s\n",str);
    char delims[] = ".";
    char *result  = NULL;
    int  v1       = 0;
    int  v2       = 0;
    int  v3       = 0;
    int  v        = 0;

    char *p = str;
    int  n;
    for (n = 0; n < 5; n++)
    {
        if ((*p) >= '0' && (*p) <= '9')
        {
            v1 *= 10;
            v1  = (*p) - '0';
        }
    }

    if (v1 == 0)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Current system", "", "", "", "", "", "Failed", "No support overlayfs", __func__, "");
        return(-1);
    }
    else
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Current system", "", "", "", "", "", "OK", "Support overlayfs", __func__, "");
    }
    return(0);
} /* checkoverlayfs */


void checkcgroup()
{
}


struct lxc
{
    char *config;
    char *explain;
    int  has_config;
};


struct lxc lxcs[16] =
{
    { "CONFIG_NAMESPACES=y",                "Namespaces cgroup subsystem",                   false },
    { "CONFIG_CGROUP_FREEZER=y",            "Freezer cgroup subsystem",                      false },
    { "CONFIG_CPUSETS=y",                   "Cpuset support",                                false },
    { "CONFIG_CGROUP_CPUACCT=y",            "Simple CPU accounting cgroup subsystem",        false },
    { "CONFIG_RESOURCE_COUNTERS=y",         "Resource counters",                             false },
    { "CONFIG_MEMCG=y",                     "Memory Resource Controller for Control Groups", false },
    { "CONFIG_CGROUP_SCHED=y",              "Group CPU scheduler",                           false },
    { "CONFIG_UTS_NS=y",                    "UTS namespace",                                 false },
    { "CONFIG_IPC_NS=y",                    "IPC namespace",                                 false },
    { "CONFIG_USER_NS=y",                   "User namespace",                                false },
    { "CONFIG_PID_NS=y",                    "Pid Namespaces",                                false },
    { "CONFIG_NET_NS=y",                    "Network namespace",                             false },
    { "CONFIG_DEVPTS_MULTIPLE_INSTANCES=y", "Support multiple instances of devpts",          false },
    { "CONFIG_MACVLAN=y",                   "MAC-VLAN support",                              false },
    { "CONFIG_VETH=y",                      "Virtual ethernet pair device",                  false },
    { "CONFIG_BRIDGE=y",                    "802.1d Ethernet Bridging",                      false },
};


extern char check_lxc[100];
extern char checklxc_cmd[100];
char        checklxc_parse_cmd[100][30] = { 0 };
char        checklxc_parse_cmd2[100] = { 0 };


void checklxc()
{
    FILE *fp;
    //FILE *fp_sub;
    //char str[100]={0};
    //char* p=str+50;
    int ret;

    fp = fopen(check_lxc, "r");
    if (fp)
    {
        fclose(fp);
        system(check_lxc);
    }

    system(checklxc_cmd);
    fp = fopen(check_lxc, "rb");
    if (fp != NULL)
    {
        sprintf(checklxc_parse_cmd[0], "grep CONFIG_NAMESPACES= %s -icq", check_lxc);
        ret = system(checklxc_parse_cmd[0]);
        if (ret == 0)
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Current system", "", "", "", "", "", "OK", "Namespaces cgroup subsystem", __func__, "CONFIG_NAMESPACES");
        }
        else
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Current system", "", "", "", "", "", "Failed", "Namespaces cgroup subsystem", __func__, "no CONFIG_NAMESPACES");
        }


        sprintf(checklxc_parse_cmd[1], "grep CONFIG_CGROUP_FREEZER= %s -icq", check_lxc);
        ret = system(checklxc_parse_cmd[1]);
        if (ret == 0)
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Current system", "", "", "", "", "", "OK", "Freezer cgroup subsystem", __func__, "CONFIG_CGROUP_FREEZER");
        }
        else
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Current system", "", "", "", "", "", "Failed", "Freezer cgroup subsystem", __func__, "no CONFIG_CGROUP_FREEZER");
        }

        sprintf(checklxc_parse_cmd[2], "grep CONFIG_CPUSETS= %s -icq", check_lxc);
        ret = system(checklxc_parse_cmd[2]);
        if (ret == 0)
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Current system", "", "", "", "", "", "OK", "Cpuset support", __func__, "CONFIG_CPUSETS");
        }
        else
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Current system", "", "", "", "", "", "Failed", "Cpuset support", __func__, "no CONFIG_CPUSETS");
        }

        sprintf(checklxc_parse_cmd[3], "grep CONFIG_CGROUP_CPUACCT= %s -icq", check_lxc);
        ret = system(checklxc_parse_cmd[3]);
        if (ret == 0)
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Current system", "", "", "", "", "", "OK", "Simple CPU accounting cgroup subsystem", __func__, "CONFIG_CGROUP_CPUACCT");
        }
        else
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Current system", "", "", "", "", "", "Failed", "Simple CPU accounting cgroup subsystem", __func__, "no CONFIG_CGROUP_CPUACCT");
        }


        sprintf(checklxc_parse_cmd[4], "grep CONFIG_RESOURCE_COUNTERS= %s -icq", check_lxc);
        ret = system(checklxc_parse_cmd[4]);
        if (ret == 0)
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Current system", "", "", "", "", "", "OK", "Resource counters", __func__, "CONFIG_RESOURCE_COUNTERS");
        }
        else
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Current system", "", "", "", "", "", "Failed", "Resource counters", __func__, "no CONFIG_RESOURCE_COUNTERS");
        }

        sprintf(checklxc_parse_cmd[5], "grep CONFIG_MEMCG= %s -icq", check_lxc);
        ret = system(checklxc_parse_cmd[5]);
        if (ret == 0)
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Current system", "", "", "", "", "", "OK", "Memory Resource Controller for Control Groups", __func__, "CONFIG_MEMCG");
        }
        else
        {
            sprintf(checklxc_parse_cmd2, "grep CONFIG_CGROUP_MEM_RES_CTLR= %s -icq", check_lxc);
            ret = system(checklxc_parse_cmd2);
            if (ret == 0)
            {
                dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Current system", "", "", "", "", "", "OK", "Memory Resource Controller for Control Groups", __func__, "CONFIG_CGROUP_MEM_RES_CTLR");
            }
            else
            {
                dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Current system", "", "", "", "", "", "Failed", "Memory Resource Controller for Control Groups", __func__, "no CONFIG_MEMCG or CONFIG_CGROUP_MEM_RES_CTLR");
            }
        }

        sprintf(checklxc_parse_cmd[6], "grep CONFIG_CGROUP_SCHED= %s -icq", check_lxc);
        ret = system(checklxc_parse_cmd[6]);
        if (ret == 0)
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Current system", "", "", "", "", "", "OK", "Group CPU scheduler", __func__, "CONFIG_CGROUP_SCHED");
        }
        else
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Current system", "", "", "", "", "", "Failed", "Group CPU scheduler", __func__, "no CONFIG_CGROUP_SCHED");
        }


        sprintf(checklxc_parse_cmd[7], "grep CONFIG_UTS_NS= %s -icq", check_lxc);
        ret = system(checklxc_parse_cmd[7]);
        if (ret == 0)
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Current system", "", "", "", "", "", "OK", "UTS namespace", __func__, "CONFIG_UTS_NS");
        }
        else
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Current system", "", "", "", "", "", "Failed", "UTS namespace", __func__, "no CONFIG_UTS_NS");
        }

        sprintf(checklxc_parse_cmd[8], "grep CONFIG_IPC_NS= %s -icq", check_lxc);
        ret = system(checklxc_parse_cmd[8]);
        if (ret == 0)
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Current system", "", "", "", "", "", "OK", "IPC namespace", __func__, "CONFIG_IPC_NS");
        }
        else
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Current system", "", "", "", "", "", "Failed", "IPC namespace", __func__, "no CONFIG_IPC_NS");
        }

        sprintf(checklxc_parse_cmd[9], "grep CONFIG_USER_NS= %s -icq", check_lxc);
        ret = system(checklxc_parse_cmd[9]);
        if (ret == 0)
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Current system", "", "", "", "", "", "OK", "USER namespace", __func__, "CONFIG_USER_NS");
        }
        else
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Current system", "", "", "", "", "", "Failed", "USER namespace", __func__, "no CONFIG_USER_NS");
        }

        sprintf(checklxc_parse_cmd[10], "grep CONFIG_PID_NS= %s -icq", check_lxc);
        ret = system(checklxc_parse_cmd[10]);
        if (ret == 0)
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Current system", "", "", "", "", "", "OK", "PID namespace", __func__, "CONFIG_PID_NS");
        }
        else
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Current system", "", "", "", "", "", "Failed", "PID namespace", __func__, "no CONFIG_PID_NS");
        }


        sprintf(checklxc_parse_cmd[11], "grep CONFIG_NET_NS= %s -icq", check_lxc);
        ret = system(checklxc_parse_cmd[11]);
        if (ret == 0)
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Current system", "", "", "", "", "", "OK", "Network namespace", __func__, "CONFIG_NET_NS");
        }
        else
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Current system", "", "", "", "", "", "Failed", "Network namespace", __func__, "no CONFIG_NET_NS");
        }


        sprintf(checklxc_parse_cmd[12], "grep CONFIG_DEVPTS_MULTIPLE_INSTANCES= %s -icq", check_lxc);
        ret = system(checklxc_parse_cmd[12]);
        if (ret == 0)
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Current system", "", "", "", "", "", "OK", "Support multiple instances of devpts", __func__, "CONFIG_DEVPTS_MULTIPLE_INSTANCES");
        }
        else
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Current system", "", "", "", "", "", "Failed", "Support multiple instances of devpts", __func__, "no CONFIG_DEVPTS_MULTIPLE_INSTANCES");
        }


        /*sprintf(checklxc_parse_cmd[13], "grep CONFIG_MACVLAN= %s -icq", check_lxc);
        ret = system(checklxc_parse_cmd[13]);
        if (ret == 0)
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Current system", "", "", "", "", "", "OK", "MAC-VLAN support", __func__, "CONFIG_MACVLAN");
        }
        else
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Current system", "", "", "", "", "", "Failed", "MAC-VLAN support", __func__, "no CONFIG_MACVLAN");
        }

        sprintf(checklxc_parse_cmd[14], "grep CONFIG_VETH= %s -icq", check_lxc);
        ret = system(checklxc_parse_cmd[14]);
        if (ret == 0)
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Current system", "", "", "", "", "", "OK", "Virtual ethernet pair device", __func__, "CONFIG_VETH");
        }
        else
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Current system", "", "", "", "", "", "Failed", "Virtual ethernet pair device", __func__, "no CONFIG_VETH");
        }*/


        sprintf(checklxc_parse_cmd[15], "grep CONFIG_BRIDGE= %s -icq", check_lxc);
        ret = system(checklxc_parse_cmd[15]);
        if (ret == 0)
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Current system", "", "", "", "", "", "OK", "802.1d Ethernet Bridging", __func__, "CONFIG_BRIDGE");
        }
        else
        {
            dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Current system", "", "", "", "", "", "Failed", "802.1d Ethernet Bridging", __func__, "no CONFIG_BRIDGE");
        }


        fclose(fp);
        //sprintf(checklxc_parse_cmd[],"rm %s");
        remove(check_lxc);
    }
} /* checklxc */


extern char check_uClibc[100];
extern char checkuClibc_cmd[100];


void checkulibc()
{
    FILE *fp;
    char str[100] = { 0 };

    fp = fopen(check_uClibc, "r");
    if (fp)
    {
        fclose(fp);
        remove(check_uClibc);
    }
    system(checkuClibc_cmd);
    fp = fopen(check_uClibc, "rb");
    if (fp != NULL)
    {
        char *p = str;

        fgets(str, 100, fp);
        /*p+=30;
         * p='\0';*/
        dbus_printf("uClib version=%s\n", str);
        int n;
        for (n = 0; n < strlen(str); n++)
        {
            if (!((*p >= '0') && (*p <= '9') || (*p >= 'a') && (*p <= 'z') || (*p >= 'A') && (*p <= 'Z') || (*p == '-') || (*p == '/') || (*p == '.')))
            {
                *p = '\0';
                break;
            }
            p++;
        }

        fclose(fp);
        remove(check_uClibc);
    }
    else
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Current system", "", "", "", "", "", "Failed", "Can't get uClibc info", __func__, "");
        return;
    }

    /*fp = fopen("/lib/libuClibc-0.9.33.2.so", "r");
       if (fp) {
         fclose(fp);
         dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n","Current system", "", "","","","","OK","Support ulibc-0.9.33.2",__func__, "0.9.33.2");
         return;
       }

       dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n","Current system", "", "","","","","Failed","Not support ulibc-0.9.33.2",__func__, "");*/
    if (strstr(str, "/lib/libuClibc-0.9.33.2.so") != NULL)
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Current system", "", "", "", "", "", "OK", "Support uClibc-0.9.33.2", __func__, "0.9.33.2");
    }
    else
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "Current system", "", "", "", "", "", "Failed", "Not support uClibc-0.9.33.2", __func__, str);
    }
} /* checkulibc */
