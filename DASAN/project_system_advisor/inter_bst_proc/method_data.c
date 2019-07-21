#include "my_data.h"

int compare(type_data left,type_data right)
{
    if(left.pid > right.pid)
        return 1;
    if(left.pid < right.pid)
        return -1;
    return 0;
}

void enter_data(type_data *mdata, type_data sdata)
{
	if(NULL != mdata)	
	{
		mdata->pid = sdata.pid;
		mdata->cpu = sdata.cpu;
		mdata->mem = sdata.mem;
		strncpy(mdata->name, sdata.name, MAX_LENGTH_OF_NAME);
	}
}

void display(node* nd)
{
    int pid;
    float cpu, mem ;
    char *name = NULL;

    pid = (nd->data).pid;
    cpu = (nd->data).cpu;
    mem = (nd->data).mem;
    name = (nd->data).name;
    
    if(nd != NULL)
 	 printf("pid = %-6d cpu = %-2.2f mem = %-2.2f name = %s\n"\
			, pid, cpu, mem, name);      
}

