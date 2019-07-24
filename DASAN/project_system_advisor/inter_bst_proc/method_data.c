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
		if(NULL == mdata->name)
			strcpy(mdata->name , "");
		else 
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
    
	if (NULL == name)
		strcpy(name, "");

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
    sigset_t block_mask,old_set;
    
    sigfillset(&block_mask);

    /*protect */
    /*lock */
    sigprocmask(SIG_BLOCK, &block_mask, &old_set);

    name = (char*)malloc(sizeof(char)*MAX_LENGTH_OF_NAME);
    fill_raw_data(mdata, pid, read_cpu(pid), read_mem(pid), \
        read_name(pid, name));

    sigprocmask(SIG_SETMASK, &old_set, NULL);
    /*unlock */
    free(name);
    
    return 0;
}
int update_state_start_time(type_data *mdata)
{
    time_t t;
    time(&t);
    
    snprintf(mdata->start_time, MAX_LENGTH_OF_NAME, "%s", ctime(&t));
    mdata->start_time[strlen(mdata->start_time) -1 ]= '\0'; 
    strcpy(mdata->stop_time , "None");
    strcpy(mdata->status, "Running");
    mdata->alert = 0;


    return 0;
}

int update_state_stop_time(type_data *mdata)
{
    time_t t;
    time(&t);
    
    //printf("limit.mem , limit.timeout %f   %d\n",mdata_limit.mem, limit_time);
    snprintf(mdata->stop_time, MAX_LENGTH_OF_NAME, "%s", ctime(&t));
    mdata->stop_time[strlen(mdata->stop_time)- 1] = '\0';

    return 0;
}

int enough_time_overload(type_data mdata)
{
    type_data tmp;
    int time_overload = 0;

    /*get time at now */
    update_state_stop_time(&tmp);
    if(strcmp("None", mdata.stop_time) == 0)
    {
        time_overload = get_duration_time(mdata.start_time, tmp.stop_time);    
    }
    else 
    {
        time_overload = get_duration_time(mdata.start_time, mdata.stop_time);
    }
    return (time_overload > limit_time);
    
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
    fp = fopen(path, "a");
    
    if(NULL == fp)
    {
        perror("open file in write to file is fail");
        return -1;
    }
    puts("write log to file ... ");
    fprintf(fp, "%-30s %-2.2f %-2.2f %-20s - %-20s %-10s\n", 
            mdata.name, mdata.cpu, mdata.mem, mdata.start_time, mdata.stop_time,
            mdata.status);
            
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

            strcpy((s->data).status, "Stoped");
            update_state_stop_time(&(s->data));
            if ((FEATURE_1 == feature) || (1 == enough_time_overload(s->data)))
            {
                write_to_file(s->data);
            }
            root =  delete_node(root ,mdata , int_comp);
        }
    }
    return root;
}
int get_second_from_time(const char *mtime)
{
	int n = 0, i;	
	int hs = 1, hsx = 1;
	int ret = 0;

	n = strlen(mtime);

	for (i = n-1; i >= 0 ; i--)
	{
		if( mtime[i] != ':')
		{
			ret += hs*(mtime[i] - '0') *hsx;	
			hsx *= 10;
		}
		else 
		{
			hsx = 1;
			hs *= 60;
		}
	}
	return ret;
}
int get_duration_time(const char *start_time, const char *stop_time)
{
	char mtime1[20],mtime2[20];

	sscanf(start_time, "%*s%*s%*d%s%*d", mtime1);
    sscanf(stop_time, "%*s%*s%*d%s%*d", mtime2);

	return abs(get_second_from_time(mtime1) - get_second_from_time(mtime2));	
}
int write_tree_to_file(node *root)
{
    if (NULL != root)
    {
        write_to_file(root->data);
        write_tree_to_file(root->left);
        write_tree_to_file(root->right);
    }
}
