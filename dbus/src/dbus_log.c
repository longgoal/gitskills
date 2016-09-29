/************************************************
*  Dbus test suite
*  Author: Thundersoft
*  2016, all rights reserved.
************************************************/

#include "dbus_log.h"

#include "time.h"
int dbus_printf_logfile(const char *fmt, ...);

int  hms           = 0;
bool open_log      = true;
char log_path[100] = { 0 };
char *root_path = NULL;
//char default_root_path[6]={'/','t','m','p',0,0};
char default_root_path[6] = "/tmp";


char instance_sh_path[100] = { 0 };
char exec_param[200] = { 0 };
char noinstance_xml_path[100] = { 0 };
char xml_path[100] = { 0 };
char xml_case_path[100] = { 0 };
char xml_case_bak_path[100] = { 0 };
char mountcontent[100] = { 0 };
char mount_cmd[100] = { 0 };
char linuxkernelversion[100] = { 0 };
char uname_cmd[100] = { 0 };
char overlayfs[100] = { 0 };
char overlayfs_cmd[100] = { 0 };
char check_lxc[100] = { 0 };
char checklxc_cmd[100] = { 0 };
char check_uClibc[100] = { 0 };
char checkuClibc_cmd[100] = { 0 };
char result_file[100] = { 0 };


void check_root_path(guint32 param)
{
//param is for parallel log
    time_t    rawtime;
    struct tm *timeinfo;
    char      *p = log_path;
    int       n;

    if (root_path == NULL)
    {
        root_path = default_root_path;
    }
    /*else{

       }*/
    if (strlen(root_path) > 30)
    {
        dbus_printf("Path %s is too long\n", root_path);
        exit(0);
    }

    if (access(root_path, 0) != 0)
    {
        dbus_printf("Program can't run by %s\n", root_path);
        exit(0);
    }


    for (n = 0; n < 100; n++)
    {
        *p = '0';
    }
    p = log_path;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    sprintf(log_path, "%s/%s", root_path, asctime(timeinfo));
    for (n = 0; n < (strlen(log_path) - 1); n++)
    {
        if (*p == ' ')
        {
            if (hms == 2)
            {
                *p = 's';
                hms++;
            }
            else
            {
                *p = '_';
            }
        }
        if (*p == ':')
        {
            if (hms == 0)
            {
                *p = 'h';
            }
            else if (hms == 1)
            {
                *p = 'm';
            }
            hms++;
        }

        p++;
    }
    if (param != 0)
    {
        *p = '_';
        p++;
        switch (param)
        {
        case 1: *p = '1';
            break;

        case 2: *p = '2';
            break;

        case 3: *p = '3';
            break;

        case 4: *p = '4';
            break;

        case 5: *p = '5';
            break;

        case 6: *p = '6';
            break;

        case 7: *p = '7';
            break;

        case 8: *p = '8';
            break;

        case 9: *p = '9';
            break;
        }
        p++;
    }
    *p = '.';
    p++;
    *p = 'c';
    p++;
    *p = 's';
    p++;
    *p = 'v';
    p++;
    *p = '\0';
    dbus_printf_logfile("Object,Interface,Property,Method,Signal,Time,Result,Reason,Action, Value\n");
    dbus_printf("\n\n   Generate the log file: %s \n   Please don't remove it untill test end\n\n", log_path);


    sprintf(instance_sh_path, "%s/.instance.sh", root_path);
    sprintf(noinstance_xml_path, "%s/dbus_cts.xml", root_path);
    sprintf(xml_path, "%s/dbus_cts.xml.bak", root_path);
    sprintf(xml_case_path, "%s/dbus_cts.case.xml", root_path);
    sprintf(xml_case_bak_path, "%s/dbus_cts.case.xml.bak", root_path);
    sprintf(exec_param, "%s  %s  %s  %s", instance_sh_path, noinstance_xml_path, log_path, xml_case_path);
    sprintf(mountcontent, "%s/.mountcontent.txt", root_path);
    sprintf(mount_cmd, "mount >> %s", mountcontent);
    sprintf(linuxkernelversion, "%s/.linuxkernelversion.txt", root_path);
    sprintf(uname_cmd, "busybox uname -r > %s", linuxkernelversion);
    sprintf(overlayfs, "%s/.overlayfs.txt", root_path);
    sprintf(overlayfs_cmd, "cat /proc/filesystems |grep overlay -ic > %s", overlayfs);
    sprintf(check_lxc, "%s/.checklxc.txt", root_path);
    sprintf(checklxc_cmd, "zcat /proc/config.gz >  %s", check_lxc);
    sprintf(check_uClibc, "%s/.checkuClibc.txt", root_path);
    sprintf(checkuClibc_cmd, "ls /lib/libuClibc* >  %s", check_uClibc);
    sprintf(result_file, "%s/dbus_cts_test_result.txt", root_path);
} /* check_root_path */


void check_persent_char(char *begin)
{
#if 0
    int  n;
    char *p            = begin;
    int  need_change   = 0;
    int  has_changed   = 0;
    int  chor[512 / 2] = { 0 };
    int  end;
    for (n = 0; n < 512; n++)
    {
        if (*p == '%')
        {
            char *b_p = p;
            b_p--;
            if (*b_p != '\\')
            {
                chor[need_change] = n;
                need_change      += 1;
            }
        }

        if (*p == '\0')
        {
            end = n;
            break;
        }
        p++;
        end = n;
    }

    if (need_change > 0)
    {
        for (n = end; n > 0; n--)
        {
            char *a_p = p;
            a_p += need_change;
            *a_p = *p;
            if (*p == '%')
            {
                *p = '\\';
                need_change--;
            }
            p--;
            if (need_change == 0)
            {
                break;
            }
        }
    }
#endif
#if 1
    int  n;
    char *p            = begin;
    int  need_change   = 0;
    int  has_changed   = 0;
    int  chor[512 / 2] = { 0 };
    int  end;
    dbus_printf("begin %s,%d\n", begin, strlen(begin));
    for (n = 0; n < 512; n++)
    {
        if (*p == '%')
        {
            char *b_p = p;
            b_p--;
            if (*b_p != '\\')
            {
                chor[need_change] = n;
                need_change      += 1;
            }
            *p = 'A';
        }

        if (*p == '\0')
        {
            end = n;
            break;
        }
        p++;
        end = n;
    }
    dbus_printf("end %s,%d\n", begin, strlen(begin));
#endif
} /* check_persent_char */


int dbus_printf_logfile(const char *fmt, ...)
{
    char    buf[256];
    FILE    *fp;
    va_list arg;
    int     rc = 0;

    if (!open_log)
    {
        return(0);
    }

    va_start(arg, fmt);
    rc = vsnprintf(buf, 512, fmt, arg);
    va_end(arg);

    fp = fopen(log_path, "a+");
    if (fp)
    {
        rc = fputs(buf, fp);
        fclose(fp);
    }

    return(rc);
}


void dbus_printf_twice(const char *fmt, ...)
{
#if 0
    char    buf[256];
    va_list arg;
    int     rc;

    va_start(arg, fmt);
    rc = vsnprintf(buf, 256, fmt, arg);
    va_end(arg);

    dbus_printf_logfile(buf);
#endif


    char    buf[512];
    FILE    *fp;
    va_list arg;
    int     rc = 0;
    va_start(arg, fmt);
    rc = vsnprintf(buf, 512, fmt, arg);
    va_end(arg);

    if (open_log)
    {
        fp = fopen(log_path, "a+");
        if (fp)
        {
            rc = fputs(buf, fp);
            fclose(fp);
        }
    }
 
   char* p = buf;
   char* pend = buf;
   int start = strlen(fmt);
   int end = strlen(buf);
   int n = 0;
   int count = 0;
   if(!(end < (start+1)))
   {
    
       for(n=0;n<end;n++)
       {
           if(*p == '%')
           {
               count++;
           }
           p++;
       }
    
       if(!((count == 0) || ((end + count) > 511)))
       {
        
           p = buf + end;
           pend = buf + end + count;
           for(n=end; n>0; n--)
           {
               if(*p != '%')
               {
                    *pend = *p;
                    pend--;
                    p--;
               }
               else
               {
                   *pend = '%';
                   pend--;
                   *pend = '%';
                   pend--;
                   p--;
                   count--;
               }
               if(count == 0)
                   break;
           }
       }
   }
   //check_persent_char(buf);
    g_print(buf);
}


//#define dbus_printf_twice(a) {g_print(a);dbus_printf_twice2(a);}
void dbus_cts_error_print(GError *error)
{
    GString *gstring;

    gstring = g_string_new("Test Failed");
    g_string_append_printf(gstring, "%s", error->message);
    dbus_printf("%s\n", gstring->str);
    g_string_free(gstring, TRUE);
}


void dbus_cts_ok_print()
{
    GString *gstring;

    gstring = g_string_new("Test OK");
    dbus_printf("%s\n", gstring->str);
    g_string_free(gstring, TRUE);
}


#if 0

#ifdef DBUS_LOGFILE_PATH


int dbus_printf(const char *fmt, ...)
{
    char    buf[512];
    FILE    *fp;
    va_list arg;
    int     rc = 0;

    va_start(arg, fmt);
    rc = vsnprintf(buf, 512, fmt, arg);
    va_end(arg);

    fp = fopen(DBUS_LOGFILE_PATH, "a+");
    if (fp)
    {
        rc = fputs(buf, fp);
        fclose(fp);
    }

    return(rc);
}

#else


int dbus_printf(const char *fmt, ...)
{
    char    buf[512];
    FILE    *fp;
    va_list arg;
    int     rc = 0;

    va_start(arg, fmt);
    rc = vsnprintf(buf, 512, fmt, arg);
    va_end(arg);

    printf(buf);

    return(rc);
}
#endif
#endif
