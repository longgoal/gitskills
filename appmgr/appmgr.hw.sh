#!/bin/sh
pwd
test_path="/tmp"
#test_path="/"

demoappmgr_path=${test_path}"/appmgr/demoappmgr"
applist_path=${test_path}"/appmgr/applist"
applist_install_path=${applist_path}"/app_install"
applist_upgrade_path=${applis_path}"/app_upgrade"
app_URL="http://192.168.1.111:280/appmgr/"  
result_URL="192.168.1.111"

if [ ! -d ${applist_path} ]
then
     mkdir -p ${applist_path}
     cd ${test_path}/appmgr
else
     cd ${applist_path}
fi

echo "Please select one vendor:
      1.Realtek
      2.Broadcom
      3.MTK
      4.Huawei
      5.Zhongxing
     "
#    read vendor
vendor=4
    case $vendor in
       1)        
        
        rm -rf ${applist_path}
	mkdir -p "${applist_path}"
	cd ${applist_path}
	mkdir "app_install"
        cd "app_install" 
        mkdir "normal"
        mkdir "abnormal" 

        cd "normal"      
	`wget ${app_URL}/applist_rtl/app_install/normal/testapp_1_rtl9600.ipk`      
	`wget ${app_URL}/applist_rtl/app_install/normal/tsappb_1_rtl9600.ipk`
	`wget ${app_URL}/applist_rtl/app_install/normal/tsappc_1_rtl9600.ipk`
	`wget ${app_URL}/applist_rtl/app_install/normal/tsappd_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappe_1_rtl9600.ipk`
	`wget ${app_URL}/applist_rtl/app_install/normal/tsappf_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappdependf_1_rtl9600.ipk`
	`wget ${app_URL}/applist_rtl/app_install/normal/tsappg_1_rtl9600.ipk`
	`wget ${app_URL}/applist_rtl/app_install/normal/tsapph_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappj_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappk_1_rtl9600.ipk`       
        `wget ${app_URL}/applist_rtl/app_install/normal/appmemory_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/appcpus_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/appcpul_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/approot_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/approotn_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsroot_1_rtl9600.ipk`
        
        
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappaa_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappab_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappac_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappad_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappae_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappaf_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappag_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappah_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappai_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappaj_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappak_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappal_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappam_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappan_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappao_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappap_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappaq_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappar_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappas_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappat_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappau_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappav_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappaw_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappax_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappay_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappaz_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappba_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappbb_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappbc_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappbd_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappbe_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappbf_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappbg_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappbh_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappbi_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappbj_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappbk_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappbl_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappbm_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappbn_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappbo_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappbp_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappbq_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappbr_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappbs_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappbt_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappbu_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappbv_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappbw_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappbx_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappby_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappbz_1_rtl9600.ipk`

         
	
         mkdir "install_1"
         mkdir "install_2"      

         cd "install_1"
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappa_1_rtl9600.ipk`
         cd ../
         cd "install_2"
        `wget ${app_URL}/applist_rtl/app_install/normal/tsappa_1_rtl9600.ipk`
        
	 cd ../../
         cd "abnormal"
	`wget ${app_URL}/applist_rtl/app_install/abnormal/tsappapk_1_rtl9600.apk`	
	`wget ${app_URL}/applist_rtl/app_install/abnormal/tsappinterface_1_rtl9600.ipk`
	`wget ${app_URL}/applist_rtl/app_install/abnormal/tsapplarge_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_install/abnormal/tsappcrack_1_rtl9600.ipk`	
        `wget ${app_URL}/applist_rtl/app_install/abnormal/tsappwrong_1_rtl9600.ipk`

	 cd ../../
         mkdir "app_upgrade"         
         cd "app_upgrade"	
        `wget ${app_URL}/applist_rtl/app_upgrade/testapp_1_rtl9600.ipk`    
   	`wget ${app_URL}/applist_rtl/app_upgrade/tsappcinterface_1_rtl9600.ipk`
	`wget ${app_URL}/applist_rtl/app_upgrade/tsappclarge_1_rtl9600.ipk`  
        `wget ${app_URL}/applist_rtl/app_upgrade/tsappcwrong_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_upgrade/tsappccrack_1_rtl9600.ipk`  
        `wget ${app_URL}/applist_rtl/app_upgrade/tsappcup_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_upgrade/tsappjup_1_rtl9600.ipk`
        `wget ${app_URL}/applist_rtl/app_upgrade/tsappkup_1_rtl9600.ipk`
    
         mkdir "grade_1"
         mkdir "grade_2"      
         cd "grade_1"       
         `wget ${app_URL}/applist_rtl/app_upgrade/tsappc_1_rtl9600.ipk`
         cd ../
         cd "grade_2"       
         `wget ${app_URL}/applist_rtl/app_upgrade/tsappc_1_rtl9600.ipk`
         cd /
 
         cd ${test_path}/appmgr
        `rm -f "demoappmgr" "appmgr.log" "appmgr.xls"`    										
        `wget ${app_URL}/applist_rtl/demoappmgr`
	 chmod 777 ${demoappmgr_path} 
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
         `tftp -p -l appmgr.log ${result_URL}`
         `tftp -p -l appmgr.xls ${result_URL}`        
done    
       ;;

       2)         
        rm -rf ${applist_path}
	mkdir -p "${applist_path}"
	cd ${applist_path}
	mkdir "app_install"
        cd "app_install" 
        mkdir "normal"
        mkdir "abnormal" 
         
        cd "normal"      
	`wget ${app_URL}/applist_bcm/app_install/normal/testapp_1_bcm6838.ipk`      
	`wget ${app_URL}/applist_bcm/app_install/normal/tsappb_1_bcm6838.ipk`
	`wget ${app_URL}/applist_bcm/app_install/normal/tsappc_1_bcm6838.ipk`
	`wget ${app_URL}/applist_bcm/app_install/normal/tsappd_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappe_1_bcm6838.ipk`
	`wget ${app_URL}/applist_bcm/app_install/normal/tsappf_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappdependf_1_bcm6838.ipk`
	`wget ${app_URL}/applist_bcm/app_install/normal/tsappg_1_bcm6838.ipk`
	`wget ${app_URL}/applist_bcm/app_install/normal/tsapph_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappj_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappk_1_bcm6838.ipk`        
        `wget ${app_URL}/applist_bcm/app_install/normal/appmemory_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/appcpus_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/appcpul_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/approot_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/approotn_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsroot_1_bcm6838.ipk`

        `wget ${app_URL}/applist_bcm/app_install/normal/tsappaa_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappab_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappac_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappad_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappae_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappaf_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappag_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappah_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappai_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappaj_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappak_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappal_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappam_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappan_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappao_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappap_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappaq_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappar_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappas_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappat_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappau_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappav_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappaw_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappax_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappay_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappaz_1_bcm6838.ipk`
        
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappba_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappbb_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappbc_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappbd_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappbe_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappbf_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappbg_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappbh_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappbi_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappbj_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappbk_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappbl_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappbm_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappbn_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappbo_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappbp_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappbq_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappbr_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappbs_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappbt_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappbu_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappbv_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappbw_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappbx_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappby_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappbz_1_bcm6838.ipk`

       	
        mkdir "install_1"
        mkdir "install_2"      

        cd "install_1"
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappa_1_bcm6838.ipk`
        cd ../
        cd "install_2"
        `wget ${app_URL}/applist_bcm/app_install/normal/tsappa_1_bcm6838.ipk`
        
	cd ../../
        cd "abnormal"
	`wget ${app_URL}/applist_bcm/app_install/abnormal/tsappapk_1_bcm6838.apk`	
	`wget ${app_URL}/applist_bcm/app_install/abnormal/tsappinterface_1_bcm6838.ipk`
	`wget ${app_URL}/applist_bcm/app_install/abnormal/tsapplarge_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_install/abnormal/tsappcrack_1_bcm6838.ipk`	
        `wget ${app_URL}/applist_bcm/app_install/abnormal/tsappwrong_1_bcm6838.ipk`

	cd ../../
        mkdir "app_upgrade"         
        cd "app_upgrade"	
        `wget ${app_URL}/applist_bcm/app_upgrade/testapp_1_bcm6838.ipk`    
   	`wget ${app_URL}/applist_bcm/app_upgrade/tsappcinterface_1_bcm6838.ipk`
	`wget ${app_URL}/applist_bcm/app_upgrade/tsappclarge_1_bcm6838.ipk`  
        `wget ${app_URL}/applist_bcm/app_upgrade/tsappcwrong_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_upgrade/tsappccrack_1_bcm6838.ipk`  
        `wget ${app_URL}/applist_bcm/app_upgrade/tsappcup_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_upgrade/tsappjup_1_bcm6838.ipk`
        `wget ${app_URL}/applist_bcm/app_upgrade/tsappkup_1_bcm6838.ipk`
    
        mkdir "grade_1"
        mkdir "grade_2"      
        cd "grade_1"       
        `wget ${app_URL}/applist_bcm/app_upgrade/tsappc_1_bcm6838.ipk`
        cd ../
        cd "grade_2"       
        `wget ${app_URL}/applist_bcm/app_upgrade/tsappc_1_bcm6838.ipk`
         cd / 
     
         cd ${test_path}/appmgr
        `rm -f "demoappmgr" "appmgr.log" "appmgr.xls"`    										
        `wget ${app_URL}/applist_bcm/demoappmgr`
	 chmod 777 ${demoappmgr_path} 
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
           `tftp -p -l appmgr.log ${result_URL}`
           `tftp -p -l appmgr.xls ${result_URL}`
done  
       ;;
       3)

        rm -rf ${applist_path}
	mkdir -p "${applist_path}"
	cd ${applist_path}
	mkdir "app_install"
        cd "app_install" 
        mkdir "normal"
        mkdir "abnormal" 

        cd "normal"      
	`wget ${app_URL}/applist_mtk/app_install/normal/testapp_1_mt7525.ipk`      
	`wget ${app_URL}/applist_mtk/app_install/normal/tsappb_1_mt7525.ipk`
	`wget ${app_URL}/applist_mtk/app_install/normal/tsappc_1_mt7525.ipk`
	`wget ${app_URL}/applist_mtk/app_install/normal/tsappd_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappe_1_mt7525.ipk`
	`wget ${app_URL}/applist_mtk/app_install/normal/tsappf_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappdependf_1_mt7525.ipk`
	`wget ${app_URL}/applist_mtk/app_install/normal/tsappg_1_mt7525.ipk`
	`wget ${app_URL}/applist_mtk/app_install/normal/tsapph_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappj_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappk_1_mt7525.ipk`       
        `wget ${app_URL}/applist_mtk/app_install/normal/appmemory_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/appcpus_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/appcpul_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/approot_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/approotn_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsroot_1_mt7525.ipk`
        
        
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappaa_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappab_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappac_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappad_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappae_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappaf_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappag_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappah_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappai_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappaj_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappak_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappal_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappam_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappan_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappao_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappap_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappaq_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappar_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappas_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappat_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappau_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappav_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappaw_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappax_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappay_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappaz_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappba_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappbb_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappbc_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappbd_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappbe_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappbf_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappbg_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappbh_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappbi_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappbj_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappbk_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappbl_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappbm_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappbn_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappbo_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappbp_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappbq_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappbr_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappbs_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappbt_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappbu_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappbv_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappbw_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappbx_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappby_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappbz_1_mt7525.ipk`

         
	
         mkdir "install_1"
         mkdir "install_2"      

         cd "install_1"
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappa_1_mt7525.ipk`
         cd ../
         cd "install_2"
        `wget ${app_URL}/applist_mtk/app_install/normal/tsappa_1_mt7525.ipk`
        
	 cd ../../
         cd "abnormal"
	`wget ${app_URL}/applist_mtk/app_install/abnormal/tsappapk_1_mt7525.apk`	
	`wget ${app_URL}/applist_mtk/app_install/abnormal/tsappinterface_1_mt7525.ipk`
	`wget ${app_URL}/applist_mtk/app_install/abnormal/tsapplarge_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_install/abnormal/tsappcrack_1_mt7525.ipk`	
        `wget ${app_URL}/applist_mtk/app_install/abnormal/tsappwrong_1_mt7525.ipk`

	 cd ../../
         mkdir "app_upgrade"         
         cd "app_upgrade"	
        `wget ${app_URL}/applist_mtk/app_upgrade/testapp_1_mt7525.ipk`    
   	`wget ${app_URL}/applist_mtk/app_upgrade/tsappcinterface_1_mt7525.ipk`
	`wget ${app_URL}/applist_mtk/app_upgrade/tsappclarge_1_mt7525.ipk`  
        `wget ${app_URL}/applist_mtk/app_upgrade/tsappcwrong_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_upgrade/tsappccrack_1_mt7525.ipk`  
        `wget ${app_URL}/applist_mtk/app_upgrade/tsappcup_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_upgrade/tsappjup_1_mt7525.ipk`
        `wget ${app_URL}/applist_mtk/app_upgrade/tsappkup_1_mt7525.ipk`
    
         mkdir "grade_1"
         mkdir "grade_2"      
         cd "grade_1"       
         `wget ${app_URL}/applist_mtk/app_upgrade/tsappc_1_mt7525.ipk`
         cd ../
         cd "grade_2"       
         `wget ${app_URL}/applist_mtk/app_upgrade/tsappc_1_mt7525.ipk`
         cd /
 
         cd ${test_path}/appmgr
        `rm -f "demoappmgr" "appmgr.log" "appmgr.xls"`    										
        `wget ${app_URL}/applist_mtk/demoappmgr`
	 chmod 777 ${demoappmgr_path} 
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
         `tftp -p -l appmgr.log ${result_URL}`
         `tftp -p -l appmgr.xls ${result_URL}`        
done 

       ;;
     
       4)

        rm -rf ${applist_path}
	mkdir -p "${applist_path}"
	cd ${applist_path}
	mkdir "app_install"
        cd "app_install" 
        mkdir "normal"
        mkdir "abnormal" 
         
        cd "normal"      
	`wget ${app_URL}/applist_hw/app_install/normal/testapp_1_sd5115.ipk`      
	`wget ${app_URL}/applist_hw/app_install/normal/tsappb_1_sd5115.ipk`
	`wget ${app_URL}/applist_hw/app_install/normal/tsappc_1_sd5115.ipk`
	`wget ${app_URL}/applist_hw/app_install/normal/tsappd_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappe_1_sd5115.ipk`
	`wget ${app_URL}/applist_hw/app_install/normal/tsappf_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappdependf_1_sd5115.ipk`
	`wget ${app_URL}/applist_hw/app_install/normal/tsappg_1_sd5115.ipk`
	`wget ${app_URL}/applist_hw/app_install/normal/tsapph_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappj_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappk_1_sd5115.ipk`        
        `wget ${app_URL}/applist_hw/app_install/normal/appmemory_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/appcpus_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/appcpul_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/approot_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/approotn_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsroot_1_sd5115.ipk`

        `wget ${app_URL}/applist_hw/app_install/normal/tsappaa_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappab_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappac_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappad_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappae_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappaf_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappag_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappah_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappai_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappaj_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappak_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappal_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappam_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappan_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappao_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappap_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappaq_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappar_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappas_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappat_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappau_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappav_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappaw_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappax_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappay_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappaz_1_sd5115.ipk`
        
        `wget ${app_URL}/applist_hw/app_install/normal/tsappba_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappbb_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappbc_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappbd_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappbe_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappbf_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappbg_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappbh_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappbi_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappbj_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappbk_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappbl_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappbm_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappbn_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappbo_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappbp_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappbq_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappbr_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappbs_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappbt_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappbu_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappbv_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappbw_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappbx_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappby_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/normal/tsappbz_1_sd5115.ipk`

       	
        mkdir "install_1"
        mkdir "install_2"      

        cd "install_1"
        `wget ${app_URL}/applist_hw/app_install/normal/tsappa_1_sd5115.ipk`
        cd ../
        cd "install_2"
        `wget ${app_URL}/applist_hw/app_install/normal/tsappa_1_sd5115.ipk`
        
	cd ../../
        cd "abnormal"
	`wget ${app_URL}/applist_hw/app_install/abnormal/tsappapk_1_sd5115.apk`	
	`wget ${app_URL}/applist_hw/app_install/abnormal/tsappinterface_1_sd5115.ipk`
	`wget ${app_URL}/applist_hw/app_install/abnormal/tsapplarge_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_install/abnormal/tsappcrack_1_sd5115.ipk`	
        `wget ${app_URL}/applist_hw/app_install/abnormal/tsappwrong_1_sd5115.ipk`

	cd ../../
        mkdir "app_upgrade"         
        cd "app_upgrade"	
        `wget ${app_URL}/applist_hw/app_upgrade/testapp_1_sd5115.ipk`    
   	`wget ${app_URL}/applist_hw/app_upgrade/tsappcinterface_1_sd5115.ipk`
	`wget ${app_URL}/applist_hw/app_upgrade/tsappclarge_1_sd5115.ipk`  
        `wget ${app_URL}/applist_hw/app_upgrade/tsappcwrong_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_upgrade/tsappccrack_1_sd5115.ipk`  
        `wget ${app_URL}/applist_hw/app_upgrade/tsappcup_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_upgrade/tsappjup_1_sd5115.ipk`
        `wget ${app_URL}/applist_hw/app_upgrade/tsappkup_1_sd5115.ipk`
    
        mkdir "grade_1"
        mkdir "grade_2"      
        cd "grade_1"       
        `wget ${app_URL}/applist_hw/app_upgrade/tsappc_1_sd5115.ipk`
        cd ../
        cd "grade_2"       
        `wget ${app_URL}/applist_hw/app_upgrade/tsappc_1_sd5115.ipk`
         cd / 
     
         cd ${test_path}/appmgr
        `rm -f "demoappmgr" "appmgr.log" "appmgr.xls"`    										
        `wget ${app_URL}/applist_hw/demoappmgr`
	 chmod 777 ${demoappmgr_path} 

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
           `tftp -p -l appmgr.log ${result_URL}`
           `tftp -p -l appmgr.xls ${result_URL}`
done       

         ;;       


       5)

        rm -rf ${applist_path}
	mkdir -p "${applist_path}"
	cd ${applist_path}
	mkdir "app_install"
        cd "app_install" 
        mkdir "normal"
        mkdir "abnormal" 
         
        cd "normal"      
	`wget ${app_URL}/applist_zte/app_install/normal/testapp_1_zx279100.ipk`      
	`wget ${app_URL}/applist_zte/app_install/normal/tsappb_1_zx279100.ipk`
	`wget ${app_URL}/applist_zte/app_install/normal/tsappc_1_zx279100.ipk`
	`wget ${app_URL}/applist_zte/app_install/normal/tsappd_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappe_1_zx279100.ipk`
	`wget ${app_URL}/applist_zte/app_install/normal/tsappf_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappdependf_1_zx279100.ipk`
	`wget ${app_URL}/applist_zte/app_install/normal/tsappg_1_zx279100.ipk`
	`wget ${app_URL}/applist_zte/app_install/normal/tsapph_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappj_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappk_1_zx279100.ipk`        
        `wget ${app_URL}/applist_zte/app_install/normal/appmemory_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/appcpus_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/appcpul_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/approot_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/approotn_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsroot_1_zx279100.ipk`

        `wget ${app_URL}/applist_zte/app_install/normal/tsappaa_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappab_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappac_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappad_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappae_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappaf_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappag_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappah_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappai_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappaj_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappak_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappal_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappam_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappan_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappao_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappap_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappaq_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappar_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappas_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappat_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappau_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappav_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappaw_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappax_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappay_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappaz_1_zx279100.ipk`
        
        `wget ${app_URL}/applist_zte/app_install/normal/tsappba_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappbb_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappbc_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappbd_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappbe_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappbf_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappbg_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappbh_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappbi_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappbj_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappbk_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappbl_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappbm_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappbn_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappbo_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappbp_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappbq_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappbr_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappbs_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappbt_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappbu_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappbv_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappbw_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappbx_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappby_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/normal/tsappbz_1_zx279100.ipk`

       	
        mkdir "install_1"
        mkdir "install_2"      

        cd "install_1"
        `wget ${app_URL}/applist_zte/app_install/normal/tsappa_1_zx279100.ipk`
        cd ../
        cd "install_2"
        `wget ${app_URL}/applist_zte/app_install/normal/tsappa_1_zx279100.ipk`
        
	cd ../../
        cd "abnormal"
	`wget ${app_URL}/applist_zte/app_install/abnormal/tsappapk_1_zx279100.apk`	
	`wget ${app_URL}/applist_zte/app_install/abnormal/tsappinterface_1_zx279100.ipk`
	`wget ${app_URL}/applist_zte/app_install/abnormal/tsapplarge_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_install/abnormal/tsappcrack_1_zx279100.ipk`	
        `wget ${app_URL}/applist_zte/app_install/abnormal/tsappwrong_1_zx279100.ipk`

	cd ../../
        mkdir "app_upgrade"         
        cd "app_upgrade"	
        `wget ${app_URL}/applist_zte/app_upgrade/testapp_1_zx279100.ipk`    
   	`wget ${app_URL}/applist_zte/app_upgrade/tsappcinterface_1_zx279100.ipk`
	`wget ${app_URL}/applist_zte/app_upgrade/tsappclarge_1_zx279100.ipk`  
        `wget ${app_URL}/applist_zte/app_upgrade/tsappcwrong_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_upgrade/tsappccrack_1_zx279100.ipk`  
        `wget ${app_URL}/applist_zte/app_upgrade/tsappcup_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_upgrade/tsappjup_1_zx279100.ipk`
        `wget ${app_URL}/applist_zte/app_upgrade/tsappkup_1_zx279100.ipk`
    
        mkdir "grade_1"
        mkdir "grade_2"      
        cd "grade_1"       
        `wget ${app_URL}/applist_zte/app_upgrade/tsappc_1_zx279100.ipk`
        cd ../
        cd "grade_2"       
        `wget ${app_URL}/applist_zte/app_upgrade/tsappc_1_zx279100.ipk`
         cd / 
     
         cd ${test_path}/appmgr
        `rm -f "demoappmgr" "appmgr.log" "appmgr.xls"`    										
        `wget ${app_URL}/applist_zte/demoappmgr`
	 chmod 777 ${demoappmgr_path} 

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
           `tftp -p -l appmgr.log ${result_URL}`
           `tftp -p -l appmgr.xls ${result_URL}`
done       

         ;;       

   
esac


