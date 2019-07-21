#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include "my_lib_process.h"
#include "my_data.h"
#include "bst.h"

int max_mem = 1;
int feature = 0 ;
int limit_time = 0;

int in_array_pid_tracking(int pid, int arr[], int n)
{
    int i = 0;

    for(i = 0; i< n; i++)
    {
        if(pid == arr[i])
            return 1;
    }
    return 0;
}
int main(int argc, char *argv[])
{
    DIR *d;
    struct dirent *dir;
    int  pid, i, choose;
    node* root = NULL , *s;
    comparer int_comp = compare;
    callback f = display;
    type_data _data_fake, mdata_limit;
    FILE *fp = NULL; 
    
    int *arr_p_tracking = NULL;
    int number_p_tracking = 0;

    pid = 0;
    mdata_limit.cpu = 0;
    mdata_limit.mem = 1;
    fp = fopen("/proc/meminfo", "r");
	fscanf(fp,"%*s%d", &max_mem);
	printf("mem_max is %d\n", max_mem);

    if( argc < 2 )
    {
        puts("incorrect argument, please follow : ./m <number_feature>");
        return -1;
    }
    feature = atoi(argv[1]);

    if (FEATURE_1 == feature )
    {
        printf("Tracking some processes on this system\n");
        printf("Enter number process tracking (PID) : ");
        scanf("%d", &number_p_tracking);
        arr_p_tracking = (int *)malloc(sizeof(int) * number_p_tracking);
        for (i = 0; i< number_p_tracking; i++)
        {
            scanf("%d", arr_p_tracking + i);
        }
    }
    else if(FEATURE_2 == feature)
    {
        printf("Tracking all processes on this system\n");
    }

    puts("Enter limit of memory in percent %");
    scanf("%f", &mdata_limit.mem);
    puts("Enter x time which is limit time overload");
    scanf("%d", &limit_time);

    /* fork  */
    do 
    {

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
                    if (FEATURE_2 == feature )
                    {
                        if( 1 == process_is_overload(_data_fake, mdata_limit))
                        {   
                        
                            s = search(root, _data_fake, int_comp);
                            if (NULL == s)
                            {
                                root = insert_node(root,int_comp,_data_fake);
                                /*update start time  */
                                s = search(root, _data_fake, int_comp);
                                update_state_start_time(&(s->data));
                                //write_to_file(s->data);
                            }
                            else 
                            {
                                /*update stop time*/
                                update_state_stop_time(&(s->data));
                                
                            }
                        }
                        else 
                        { 
                                /* this process escape from overload */
                                s = search(root, _data_fake, int_comp);
                                /*feature 2  tracking system*/
                                if(NULL != s )
                                {
                                    if(enough_time_overload(s->data))
                                    {
                                        write_to_file(s->data);
                                    }
                                }
                        }
                    }
                    else if(FEATURE_1 == feature)
                    {
                            if (1 == in_array_pid_tracking(pid, arr_p_tracking, number_p_tracking))
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
                    else 
                    {
                        puts("error argument ");
                        exit (-1);
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
