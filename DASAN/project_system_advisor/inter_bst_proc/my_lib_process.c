#include "my_lib_process.h"
#include <unistd.h>

extern int max_mem;
int check_is_pid(const char *name)
{
	int len = strlen(name);
	int i = 0;

	for (i = 0; i< len; i++)
	{
		if(0 == isdigit(*(name +i))) 
			return 0;
	}
	return 1;
}
float read_cpu(int pid)
{
	char tmp[100];
	float cpu = 0;
	FILE *fp;

	sprintf(tmp,"/proc/%d/stat", pid);
	
	fp = fopen(tmp, "r");
	if(NULL == fp)
	{
		perror("fail open stat for read cpu");
		return -1;
	}

	/*
		read stat and update variable cpu
	*/
	fclose(fp);

	return cpu;	
}
char* read_name(int pid,char *const name)
{
	char tmp[100];
	FILE *fp;

	sprintf(tmp,"/proc/%d/cmdline", pid);
	
	fp = fopen(tmp, "r");
	if(NULL == fp)
	{
		perror("fail open stat for read cpu");
		return NULL;
	}
	strcpy(name, "");
	fgets(name, MAX_LENGTH_OF_NAME-1, fp);

	name[MAX_LENGTH_OF_NAME -1 ] = '\0';

	fclose(fp);
	
	return name;	
}
float read_mem(int pid)
{
	char tmp[100];
	float mem = 0;
	FILE *fp;

	sprintf(tmp,"/proc/%d/statm", pid);
	fp = fopen(tmp, "r");
	if(NULL == fp)
	{
		perror("fail open stat for read cpu");
		return -1;
	}

	fscanf(fp, "%*f%f", &mem);
	fclose(fp);

	mem *= sysconf(_SC_PAGE_SIZE) / 1024;

	mem = (mem * 100.0/max_mem);

	return mem;	
}
int pid_is_not_in_proc(int pid)
{
    DIR *d;
    char tmp[30];
    
    sprintf(tmp, "/proc/%d", pid);
    d = opendir(tmp);
    if (NULL == d)
    {
        return 1;
    }
    return 0;
}
int process_alert_overload()
{
	/*double fork at here */
	puts("\n\n\nalert\n\n\n");
	return 0;
}