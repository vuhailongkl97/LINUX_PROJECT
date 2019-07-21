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

int fill_raw_data(type_data *mdata,int pid, float cpu, float mem, char *name) 
{
	mdata->pid = pid;
	mdata->cpu = cpu;
	mdata->mem = mem;

	strncpy(mdata->name, name, MAX_LENGTH_OF_NAME );
	return 0;
}

int fill_data(type_data *mdata, int pid)
{
    char *name = NULL;
    float mem, cpu;

    name = (char*)malloc(sizeof(char)*MAX_LENGTH_OF_NAME);
    fill_raw_data(mdata, pid, read_cpu(pid), read_mem(pid), \
        read_name(pid, name));

    free(name);
    
    return 0;
}
int update_state_start_time(type_data *mdata)
{
    time_t t;
    time(&t);
    
    snprintf(mdata->start_time, MAX_LENGTH_OF_NAME, "%s", ctime(&t));
    strcpy(mdata->stop_time , "None");
    strcpy(mdata->status, "Running");

    return 0;
}

int update_state_stop_time(type_data *mdata)
{
    time_t t;
    time(&t);
    
    snprintf(mdata->stop_time, MAX_LENGTH_OF_NAME, "%s", ctime(&t));
    strcpy(mdata->status, "Stoped");

    return 0;
}

int enough_time_overload(type_data mdata)
{
    
    return 0;
}

int process_is_overload(type_data mdata, type_data mdata_limit)
{
    if( mdata.cpu > mdata_limit.cpu || mdata.mem > mdata_limit.mem)
        return 1;
    return 0;
}

int write_to_file(type_data mdata)
{
    int pid = mdata.pid;
    char path[50];
    FILE *fp = NULL;

    snprintf(path, MAX_LENGTH_OF_NAME, "./log/%d.txt", pid);
    fp = fopen(path, "w+");
    
    if(NULL == fp)
    {
        perror("open file in write to file is fail");
        return -1;
    }
    printf("%-5d %-2.2f %-2.2f %-20s %-20s %-7s %-30s\n", 
            mdata.pid, mdata.cpu, mdata.mem, mdata.start_time, mdata.stop_time,
            mdata.name, mdata.status);
            
    fclose(fp);
}
node *delete_process_if_not_exist_in_proc(node * root)
{
    int n = 0, i = 0;
    int *arr = NULL;
    type_data mdata;
    node *s =  NULL;
    comparer int_comp = compare;
    
    if( NULL == root)
        return NULL;

    traverse_tree(root, &n, NULL);
    arr = (int*)malloc(sizeof(int)* n);
    n = 0;
    traverse_tree(root, &n, arr );

    for (i = 0; i< n ; i++)
    {
        if (1 == pid_is_not_in_proc(arr[i]))
        {
            mdata.pid = arr[i];
            s = search(root, mdata, int_comp);
            /*
                check if enought time overload ( feature 2)
                or feature 1
                then call write to file 
            */
            if ((FEATURE_1 == feature) || (1 == enough_time_overload(s->data)))
            {
                write_to_file(s->data);
            }
            root =  delete_node(root ,mdata , int_comp);
        }
    }
    return root;
}