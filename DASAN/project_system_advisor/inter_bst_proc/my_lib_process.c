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

    int ret = 0;
    float user_use_cpu_percent = 0;
    float kernel_use_cpu_percent = 0;

	sprintf(tmp,"/proc/%d/stat", pid);
	
	fp = fopen(tmp, "r");
	if(NULL == fp)
	{
		printf("fail open stat for read cpu (pid %d)\n", pid);
		return 0;
	}
	fclose(fp);

    if( cpu>= 100.0)
    {
        cpu = 100.0;
    }
    else if( cpu<= 0.0)
    {
        cpu= 0.0;
    }

	return cpu;	
}
char* read_name(int pid,char *const name)
{
	char tmp[100];
	FILE *fp;

	sprintf(tmp,"/proc/%d/cmdline", pid);
	
	fp = fopen(tmp, "r");
	strcpy(name, "");
	
	if(NULL == fp)
	{
		printf("fail open stat for read name (pid %d)\n", pid);
		return name;
	}
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
		printf("fail open stat for read mem (pid %d)\n", pid);
		return 0;
	}

	fscanf(fp, "%*f%f", &mem);

	mem *= sysconf(_SC_PAGE_SIZE) / 1024;

	mem = (mem * 100.0/max_mem);

	fclose(fp);
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

	closedir(d);
    return 0;
}
int process_alert_overload(type_data mdata)
{
	/*double fork at here */
	int tmp_pid = 0;

	
	tmp_pid = fork();
	if( tmp_pid < 0 )
	{
		perror("fork fail in process alert overload ");
		return -1;
	}
	else if (tmp_pid == 0)
	{
		
		int tmp_pid2 = fork();
		if( tmp_pid2 > 0 )
		{
			//usleep(10);
			exit(0);
		}
		else if( tmp_pid2 == 0)
		{
			//system("ogg123 alert.ogg");
			usleep(100000);
			printf("\nalert %s is overload ( mem = %f%%)\n", mdata.name, mdata.mem );
			exit(0);
		}
		else 
		{
			perror("fork twice fail");
			return -1;
		}
		
	}
	
	wait(NULL);
	//printf("\nalert %s is overload ( mem = %f%%)\n", mdata.name, mdata.mem );
	
	return 0;
}
void write_tree_handler(int signo)
{
	puts("write tree to file ");
	if (SIGUSR1 == signo)
	{
		
	}
}