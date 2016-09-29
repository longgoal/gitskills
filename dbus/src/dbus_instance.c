#include <dbus_cts.h>
#include <expat.h>
#include "list.h"
#include <dbus_xml_parse.h>
#include <gio/gio.h>  
#include <sys/types.h>
#include <sys/stat.h>

char array[8000]={"\n\
#!/bin/sh\n\
oldpwd=`pwd`\n\
\n\
\n\
\n\
input1=\"\"\n\
input2=\"\"\n\
node_=\"\"\n\
form_node_=\"\"\n\
\n\
#introspect_object=\"/com/ctc/igd1/Info/Network/WANConnectionDb\"\n\
dbus_read_introspect()\n\
{\n\
   output=\"\"\n\
   if test \"$1\" != \"\"; then\n\
   dbus-send --system --print-reply --dest=com.ctc.igd1 $1 org.freedesktop.DBus.Introspectable.Introspect | while read line\n\
   do\n\
       node_=$(echo $line| grep node -w |grep name -w |awk -F '\\\"' '{ print $2;}')\n\
       if test \"$node_\" != \"\" ; then\n\
          #output=$node_\" \"\n\
          echo $node_\n\
       fi\n\
   done\n\
   fi\n\
}\n\
\n\
#input1=`dbus_read_introspect $introspect_object`\n\
#echo @@@@$input1\n\
\n\
\n\
bak_file=\"$1.bak\"\n\
bak_file2=\"$1.bak2\"\n\
input_file=\"$1\"\n\
log_file=$2\n\
if test \"$log_file\" = \"\" ; then\n\
   log_file=\"/dev/null\"\n\
else\n\
   if test ! -f $log_file ; then\n\
      log_file=\"/dev/null\"\n\
   fi\n\
fi\n\
\n\
case_bak_file=\"$3.bak\"\n\
normal_print=true \n\
\n\
begin=0; \n\
end=0; \n\
print_process=0; \n\
quickline=1600; \n\
\n\
var=0 #file lines\n\
\n\
stag=false \n\
mtag=false \n\
dtag=false \n\
\n\
object_for_introspect=\"\" #for dbus introspect\n\
stringA=\" \" \n\
stringB=\" \" \n\
if test -f $bak_file; then\n\
rm $bak_file\n\
fi\n\
if test -f $bak_file2; then\n\
rm $bak_file2\n\
fi\n\
if test -f $0; then\n\
rm $0 \n\
fi\n\
if test -f $case_bak_file; then\n\
rm $case_bak_file\n\
fi\n\
ts_default_mount=`mount |grep mnt/ -i | grep usb -i -m 1| awk '{print $3}'`\n\
echo \"command= mount |grep mnt/ -i | grep usb -i -m 1\" \n\
default_mount2=`echo $ts_default_mount | sed -e 's/\\\\//\\\\\\\\\\\//g'`\n\
#echo Get $default_mount2\n\
echo Update case xml, from Default_Mount_Path to $ts_default_mount, in $case_bak_file\n\
sed -e \"s/Default_Mount_Path/$default_mount2/g\" $3 > $case_bak_file \n\ 
ts_default_usbdev=`mount |grep mnt/ -i| awk '{print $1}'`\n\
default_usbdev2=`echo $ts_default_usbdev | sed -e 's/\\\\//\\\\\\\\\\\//g'`\n\
#echo $default_usbdev2\n\
echo Update case xml, from Default_Usbdev_Path to $ts_default_usbdev, in $case_bak_file\n\
#sed -e \"s/Default_Usbdev_Path/$default_usbdev2/g\" $3 > $case_bak_file \n\ 
sed -i \"s/Default_Usbdev_Path/$default_usbdev2/g\" $case_bak_file \n\ 
#cat $3 | while read caseline\n\
#do\n\
#echo $caseline | sed \"s/Default_Mount_Path/$default_mount/g\" >>$case_bak_file\n\
#done\n\
\n\
#sed -n -e \"1,1100\"p $input_file >> $bak_file\n\
#sed -n -e \"1101,$\"p $input_file >> $bak_file2\n\
copy_begin=`grep \\\{i\\\} $1 -m 1 -in | awk -F ':' '{print $1}'`\n\
copy_begin2=0\n\
#echo copy_begin at $copy_begin\n\
if test \"$copy_begin\" != \"0\" ; then\n\
let \"copy_begin2=copy_begin-1\"\n\
sed -n -e \"1,$copy_begin2\"p $input_file >> $bak_file\n\
sed -n -e \"$copy_begin,$\"p $input_file >> $bak_file2\n\
else\n\
cp $input_file $bak_file2\n\
fi\n\
cat $bak_file2 | while read line\n\
do\n\
   let \"print_process+=1\"\n\
   if test \"$print_process\" = \"120\" ; then\n\
       echo \"  +\"\n\
       print_process=0 \n\
   fi\n\
   #echo $var\n\
   #Tag=`echo $line | grep node -i | grep \\\{ -ic`\n\
   Tag=`echo $line | grep {i} -ic`\n\
   if test \"$Tag\" = \"1\" ; then\n\
\n\
      begin=$var\n\
      let \"begin+=2\"\n\
      form_node_=`echo $line| awk -F '\\\"' '{ print $2;}'`\n\
\n\
      normal_print=false\n\
      Middle_tag=`echo $line | grep \"[0-9a-zA-Z\\/]{i}\\/\" -ic`\n\
      if test \"$Middle_tag\" = \"0\" ; then\n\
         stag=true\n\
         object_for_introspect=`echo $line|sed -e 's/\\/{i}//g'| sed -e 's/{i}//g' |awk -F '\\\"' '{ print $2;}'`\n\
	\n\
         #echo $var@$line\n\
         input1=$(dbus_read_introspect $object_for_introspect )\n\
      fi\n\
\n\
      if test \"$Middle_tag\" = \"1\" ; then\n\
         \n\
         Double_tag=`echo $line | grep \"{i}\\\">$\" -ic`\n\
\n\
         if test \"$Double_tag\" = \"0\" ; then\n\
            mtag=true\n\
            stringA=`echo $line| awk -F '\\{' '{ print $1;}'| sed -e 's/\\/$//g'`\n\
            stringB=`echo $line| awk -F '\\}' '{ print $2;}'`\n\
            \n\
            #echo $var@@$line\n\
         fi\n\
\n\
         if test \"$Double_tag\" = \"1\" ; then\n\
            dtag=true\n\
            stringA=`echo $line| awk -F '\\{' '{ print $1;}'| sed -e 's/\\/$//g'`\n\
            stringB=`echo $line| awk -F '\\{' '{ print $2;}'| sed -e 's/^i\\}//g'`\n\
            #echo $var@@@$line\n\
         fi \n\
\n\
      fi          \n\
\n\
   fi \n\
\n\
\n\
\n\
\n\
   if test \"$begin\" != \"0\" ; then\n\
      Tag=`echo $line | grep \"</node>\" -wc`\n\
      if test \"$Tag\" = \"1\" ; then\n\
         end=$var\n\
         let \"end+=1\"\n\
         #echo \"--end in line$end\"\n\
\n\
         if test \"$stag\" = \"true\" ; then\n\
            if test \"$input1\" = \"\"; then\n\
               echo $object_for_introspect\"/{i} NO instance!!\"\n\
               #echo $object_for_introspect\"/{i}, , , , , ,Failed ,No instance , Check instance,\" >> $log_file\n\
            fi\n\
            for p in $input1; do\n\
               exist_obj=`grep \\\"$object_for_introspect/$p\\\" $input_file -wc`\n\
               if test \"$exist_obj\" = \"0\" ; then\n\
               echo \"<node name=\\\"$object_for_introspect/$p\\\">\" >> $bak_file\n\
               echo \"<form_node formname=\\\"$form_node_\\\"/>\" >> $bak_file\n\
               #sed -n \"$begin,$end\"p $input_file >> $bak_file\n\
               sed -n \"$begin,$end\"p $bak_file2 >> $bak_file\n\
               #else\n\
               #echo $object_for_introspect/$p is exist $exist_obj\n\
               fi\n\
            done \n\
         fi\n\
         stag=false\n\
\n\
\n\
         if test \"$mtag\" = \"true\" ; then\n\
            object_for_introspect=`echo $stringA | awk -F '\\\"' '{ print $2;}'`\n\
            object_for_introspect2=`echo $stringB | awk -F '\\\"' '{ print $1;}'`\n\
\n\
            #input1=$(dbus_read_introspect $object_for_introspect$object_for_introspect2)\n\
            input1=$(dbus_read_introspect $object_for_introspect)\n\
            #echo $object_for_introspect######$object_for_introspect2\n\
            #echo #$input1\n\
            if test \"$input1\" = \"\"; then\n\
               echo $object_for_introspect\"/{i}\"$object_for_introspect2\" NO instance!!\"\n\
               #echo $object_for_introspect\"/{i}\"$object_for_introspect2\", , , , , ,Failed ,No instance , Check instance,\" >> $log_file\n\
            fi\n\
            \n\
            for p in $input1; do\n\
               echo \"<node name=\\\"$object_for_introspect/$p$object_for_introspect2\\\">\" >> $bak_file\n\
               echo \"<form_node formname=\\\"$form_node_\\\"/>\" >> $bak_file\n\
               #sed -n \"$begin,$end\"p $input_file >> $bak_file\n\
               sed -n \"$begin,$end\"p $bak_file2 >> $bak_file\n\
            done \n\
         fi\n\
\n\
\n\
         if test \"$dtag\" = \"true\" ; then\n\
            object_for_introspect=`echo $stringA | awk -F '\\\"' '{ print $2;}'`  \n\
            object_for_introspect2=`echo $stringB | awk -F '\\\"' '{ print $1;}' | sed -e 's/\\/$//g' ` \n\
            input1=$(dbus_read_introspect $object_for_introspect)\n\
\n\
            for p in $input1; do\n\
               if test \"$p\" != \"\"; then\n\
                  #echo @@@@@@$object_for_introspect\"/\"$p$object_for_introspect2\n\
                  input2=$(dbus_read_introspect $object_for_introspect\"/\"$p$object_for_introspect2)\n\
                  if test \"$input2\" = \"\"; then\n\
                     echo $object_for_introspect\"/\"$p$object_for_introspect2\"/{i} NO instance!!\"\n\
                     #echo $object_for_introspect\"/\"$p$object_for_introspect2\"/{i}, , , , , ,Failed ,No instance , Check instance,\" >> $log_file\n\
                  fi\n\
                  for q in $input2; do\n\
                     echo \"<node name=\\\"$object_for_introspect/$p$object_for_introspect2/$q\\\">\" >> $bak_file\n\
                     echo \"<form_node formname=\\\"$form_node_\\\"/>\" >> $bak_file\n\
                     #sed -n \"$begin,$end\"p $input_file >> $bak_file\n\
                     sed -n \"$begin,$end\"p $bak_file2 >> $bak_file\n\
                  done\n\
               fi\n\
            done \n\
         fi\n\
\n\
         stag=false\n\
         mtag=false\n\
         dtag=false\n\
         stringA=\" \"\n\
         stringB=\" \"\n\
\n\
         begin=0\n\
         end=0\n\
         normal_print=true\n\
\n\
         input1=\"\"\n\
         input2=\"\"\n\
\n\
\n\
         if test -f $bak_file; then\n\
         sed -i '$d' $bak_file\n\
         #sed '$d' $bak_file > $bak_file2\n\
         #mv $bak_file2 $bak_file\n\
         fi\n\
      fi\n\
      \n\
   fi\n\
\n\
\n\
\n\
\n\
   if test \"$normal_print\" = \"true\" ; then\n\
      echo $line >> $bak_file \n\
   fi\n\
let \"var+=1\"\n\
done\n\
if test -f $bak_file2; then\n\
rm $bak_file2\n\
fi\n\
cd $oldpwd\n\
"};





extern char instance_sh_path[100];
extern char log_path[100];
extern char exec_param[200];
extern char noinstance_xml_path[100];

static void instance_delete()
{
	if(access(instance_sh_path,0)==0)
		remove(instance_sh_path);
}

static void instance_generate()
{

        FILE *fp;
        int rc = 0;
        fp = fopen(instance_sh_path, "a+");
        if (fp) {
                rc = fputs(array, fp);
                fclose(fp);
        }
	chmod(instance_sh_path,S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IXGRP|S_IROTH|S_IWOTH|S_IXOTH);

}

int instance_run()
{
        FILE *fp;
        int rc = 0;

	if(access(noinstance_xml_path,0)<0)
	{
		dbus_printf("can't find %s\n",noinstance_xml_path);
		return -1;
	}
   instance_generate();
   system(exec_param);
   instance_delete();
   return 0;
}
