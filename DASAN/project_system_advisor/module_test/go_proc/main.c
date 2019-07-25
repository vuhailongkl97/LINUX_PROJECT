#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include "my_lib_process.h"
 
int main(void)

{

    DIR *d;
    struct dirent *dir;
    int cpu, mem, pid;
    char *name;

    cpu = mem = pid = 0;
    name = (char *)malloc(sizeof(char) *200);
    d = opendir("/proc");

    if (NULL != d)
    {
        while ((dir = readdir(d)) != NULL)
        {
	    if(1 == check_is_pid(dir->d_name) )
            	{
			pid = atoi(dir->d_name);
			cpu = read_cpu(pid);
			mem = read_mem(pid);
			name = read_name(pid, name);
			if (name == NULL)
			{
				puts("error");
				break;
			}
			printf("pid = %6d cpu = %5.2d mem = %10d name = \
				%20s\n", pid, cpu, mem, name);
		}	
        }
	free(name);
        closedir(d);
    }

    return(0);

}
