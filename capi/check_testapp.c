#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>

long check_file_size(char*);

int check_log_exist(char * info){
	char cmd_string[128];
	char tmpfile[] = "/tmp/tmp_file.XXXXXX";
	mkstemp(tmpfile);
	unlink(tmpfile);
	sprintf(cmd_string, "grep -F \"%s\" /opt/apps/ctsgw.log > %s", info, tmpfile);
	printf("check_log_exist %s\n",cmd_string);
	printf("check_log_exist tmpfile %s\n",tmpfile);
	system(cmd_string);
	if(check_file_size(tmpfile)>0){
		printf("log \"%s\" exist\n",info);
		return 0;
	}
	else {
		printf("log \"%s\" not exist\n",info);
		return -1;
	}
}

long check_file_size(char* filename){
	unsigned long filesize = -1;      
	struct stat statbuff;  
	if(stat(filename, &statbuff) < 0){  
		return filesize;  
	}
	else{  
		filesize = statbuff.st_size;  
	}  
	printf("check_file_size %ld \n",filesize);
	return filesize;  
}

int xls_write(const char* name,const char* result)
{
	FILE* fp = NULL; 

	fp = fopen("/tmp/capi.xls","a+");
	if(NULL == fp)
	{
		printf("fopen error!\n");
		return -1;
	}

	fprintf(fp,"%s \t %s\n",name,result);
	
	fclose(fp);
	return 0;
}

int main(int argc, const char *argv[])
{
	int i = 0;
	char *str[] = {"CtSgwDBusSetProperty",
			"testCtSgwDBusPropSetFunction testapp1Title",
			"CtSgwDBusGetProperty",
			"testCtSgwDBusPropGetFunction testapp1Title",
			"CtSgwDBusSetMultiProperty",
			"testCtSgwDBusPropSetMultiFunction",
			"CtSgwDBusGetAllProperty",
			"testCtSgwDBusPropGetAllFunction",
			"CtSgwDBusSubscribeSignal",
			"callback My_CtSgwDBusSignalFunction"};
	for(i = 0;i < 10;i ++)
	{
		if(check_log_exist(str[i]) < 0)
		{
			printf("failed!!!!!\n");
			xls_write("signal_capi_function","failed");
			break;
		}
	}
	if(i == 10)
	{
		printf("pass!!!\n");
		xls_write("signal_capi_function","pass");
	}

	return 0;
}
