#include "result_check_util.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "capi.h"


int CheckCtSgwtest_one(int out,int target)
 {
   int a=-1;
   if(out==target){
      a=1;
   }
   else{
     a=0;
   }
   return a;    

 }

int CheckCtSgwInstallApp_t(int out,int target)
 {
   static int pass=0,fail=0;
   if(out==target)
    {
      pass++;
      printf("Pass\n");
    }
   else
    {
      fail++;
      printf("Fail\n");
    }
   return pass;
 }


int CheckCtSgwStatus(CtSgwAppStatus_t app_status,char *p)
{
   int a=-1;
   if(strcmp(p,app_status.state)==0){
    a=1; 
   }
   else{
    a=0;   
   }

return a;

}



