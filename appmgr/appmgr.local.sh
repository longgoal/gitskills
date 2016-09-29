#!/bin/sh
pwd
test_path="/tmp"
#test_path="/"


if [ ! -d ${test_path}/appmgr ]
then
    tar zxvf ${test_path}/appmgr.tar.gz
fi

cd ${test_path}/appmgr
rm -f "appmgr.log" "appmgr.xls"    										
rm ${test_path}/appmgr/applist -rf
rm ${test_path}/appmgr/demoappmgr


echo "Please select one vendor:
      1.Realtek
      2.Broadcom
      3.MTK
      4.Huawei
      5.Zhongxing
     "
    read vendor
    case $vendor in
       1)        
         ln -s ${test_path}/appmgr/applist_rtl ${test_path}/appmgr/applist
         chmod 777 ${test_path}/appmgr/applist_rtl/demoappmgr 
         ln -s ${test_path}/appmgr/applist_rtl/demoappmgr ${test_path}/appmgr/demoappmgr
       ;;

       2)         
         ln -s ${test_path}/appmgr/applist_bcm ${test_path}/appmgr/applist
         chmod 777 ${test_path}/appmgr/applist_bcm/demoappmgr 
         ln -s ${test_path}/appmgr/applist_bcm/demoappmgr ${test_path}/appmgr/demoappmgr
       ;;
       3)
         ln -s ${test_path}/appmgr/applist_mtk ${test_path}/appmgr/applist
         chmod 777 ${test_path}/appmgr/applist_mtk/demoappmgr 
         ln -s ${test_path}/appmgr/applist_mtk/demoappmgr ${test_path}/appmgr/demoappmgr
       ;;
     
       4)
         ln -s ${test_path}/appmgr/applist_hw ${test_path}/appmgr/applist
         chmod 777 ${test_path}/appmgr/applist_hw/demoappmgr 
         ln -s ${test_path}/appmgr/applist_hw/demoappmgr ${test_path}/appmgr/demoappmgr
       ;;
       5)
         ln -s ${test_path}/appmgr/applist_zte ${test_path}/appmgr/applist
         chmod 777 ${test_path}/appmgr/applist_zte/demoappmgr 
         ln -s ${test_path}/appmgr/applist_zte/demoappmgr ${test_path}/appmgr/demoappmgr
       ;;       
    esac


while true
do   
        echo "Please select on test mode:
             1.APP_ALL
             2.APP_ONE
             3.APP_INSTALL
             4.APP_UPGRADE
             5.APP_START
             6.APP_STOP
             7.APP_RELOAD
             8.APP_UNINSTALL      
             9.UCI_CAPI
             10.TEST_LOG
             11.SAFE_TEST
             12.PRESSURE_TEST
             13.APPNUM_TEST
             14.Quit
            "
        read mode 
        case $mode in
                1)
                  ./demoappmgr APP_ALL >> /tmp/appmgr/appmgr.log                                   
                  ;;                
                2)
                  ./demoappmgr APP_ONE >> /tmp/appmgr/appmgr.log                  
                  ;; 
                3)
                  ./demoappmgr APP_INSTALL >> /tmp/appmgr/appmgr.log
                  ;;
                4)
                  ./demoappmgr APP_UPGRADE >> /tmp/appmgr/appmgr.log
                  ;;
                5)
                  ./demoappmgr APP_START >> /tmp/appmgr/appmgr.log
                  ;;
                6)
                  ./demoappmgr APP_STOP >> /tmp/appmgr/appmgr.log
                  ;;
                7)
                  ./demoappmgr APP_RELOAD >> /tmp/appmgr/appmgr.log
                  ;;
                8)
                  ./demoappmgr APP_UNINSTALL >> /tmp/appmgr/appmgr.log
                  ;;
                9)
                  ./demoappmgr UCI_CAPI >> /tmp/appmgr/appmgr.log
                  ;;
                10)
                  ./demoappmgr TEST_LOG >> /tmp/appmgr/appmg.log
                  ;;
                11)
                  ./demoappmgr SAFE_TEST >> /tmp/appmgr/appmgr.log
                  ;;
                12)echo "Please input the loop times:"
                   read times
                   for i in `seq ${times}`
                   do
                   ./demoappmgr PRESSURE_TEST >> /tmp/appmgr/appmgr.log
                   done 
                   ;;
                 13)
                  ./demoappmgr APPNUM_TEST >> /tmp/appmgr/appmgr.log
                  ;; 
                 14) echo "Quit!"
                   break
                   ;;              
          
            esac           
           #`tftp -p -l appmgr.log ${result_URL}`
           #`tftp -p -l appmgr.xls ${result_URL}`
done  
