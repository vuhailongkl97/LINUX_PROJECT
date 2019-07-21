#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "my_lib_process.h"
#include "my_data.h"
#include "bst.h"

int max_mem = 1;
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
node *delete_process_if_not_exist_in_proc(node * root)
{
    int n = 0, i = 0;
    int *arr = NULL;
    type_data mdata;
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
            root =  delete_node(root ,mdata , int_comp);
        }
    }
    return root;
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
int process_is_overload(type_data mdata, type_data mdata_limit)
{
    if( mdata.cpu > mdata_limit.cpu || mdata.mem > mdata_limit.mem)
        return 1;
    return 0;
}
int main(void)
{
    DIR *d;
    struct dirent *dir;
    int  pid, i, choose;
    node* root = NULL , *s;
    comparer int_comp = compare;
    callback f = display;
    type_data _data_fake, mdata_limit;
    FILE *fp = NULL; 
    mdata_limit.cpu = 0;
    mdata_limit.mem = 1;

    fp = fopen("/proc/meminfo", "r");
	fscanf(fp,"%*s%d", &max_mem);
	printf("mem_max is %d\n", max_mem);

    pid = 0;
    do 
    {
        puts("enter limit of memory in percent %%");
        scanf("%f", &mdata_limit.mem);
        root = delete_process_if_not_exist_in_proc(root);

        d = opendir("/proc");
        if (NULL != d)
        {
            while ((dir = readdir(d)) != NULL)
            {
                if(1 == check_is_pid(dir->d_name) )
                {
                        pid = atoi(dir->d_name);
                        fill_data(&_data_fake, pid);

                        if(1 == process_is_overload(_data_fake, mdata_limit))
                        {   
                     
                            s = search(root, _data_fake, int_comp);
                            if (NULL == s)
                            {
                                root = insert_node(root,int_comp,_data_fake);
                                /*update start time  */
                                s = search(root, _data_fake, int_comp);
                                update_state_start_time(&(s->data));
                                write_to_file(s->data);
                            }
                            else 
                            {
                                /*update stop time*/
                                update_state_stop_time(&(s->data));
                            }
                            
                        }
                    }	

            }
            closedir(d);
        }
        printf(" into the tree.\n\n");
    
        /* display the tree */
        display_tree(root);
        puts("please enter choose > 0 to continue");
        scanf("%d", &choose);
    } while(choose > 0);
    /* remove element */
  
    dispose(root);

    return(0);
}
