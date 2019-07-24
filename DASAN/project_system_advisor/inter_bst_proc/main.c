#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "my_lib_process.h"
#include "my_data.h"
#include "bst.h"

int max_mem = 1;
int feature = 0 ;
int limit_time = 0;
type_data mdata_limit;
node* root = NULL;

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
    int  pid, i, choose =1, pid_f = 0;
    node *s;
    comparer int_comp = compare;
    callback f = display;
    type_data _data_fake;
    FILE *fp = NULL; 
    
    int *arr_p_tracking = NULL;
    int number_p_tracking = 0;

    pid = 0;
    mdata_limit.cpu = 0;
    mdata_limit.mem = 0.1f;
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
    
    pid_f = fork();
    if( pid_f < 0){
        perror("fork fail");
        exit(-1);
    } 
    else if( pid_f > 0)
    {
            /*parent */
            int time_out_f = 10;

            if (FEATURE_1 == feature )
            {
                while(1)
                {
                    sleep(time_out_f);
                    kill(pid_f, SIGUSR1);
                }
            }
            else 
                while (1)
                {
                    /* code */
                    sleep(1000);
                }

    }
    else 
    {
        /*child */
        /*update handler for write tree to file  */
        signal(SIGUSR1, write_tree_handler);
        
    do 
    {

        // block all signal to this process after read all information about process 
        // unblock to receive signal ( write to file from other process )
        
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
                                /*update memory , cpu  */
                            s->data.mem = _data_fake.mem;
                            s->data.cpu = _data_fake.cpu;
                            update_state_stop_time(&(s->data));
                            if((0 == s->data.alert ) && (1 == enough_time_overload(_data_fake)))
                            {
                                process_alert_overload(s->data);
                                //mdata->alert = 1;
                                s->data.alert = 1;
                            }
     
                            }
                        }
                        else 
                        {
                                /* 
                                    this process escape from overload state
                                        1. update stop time 
                                        2. delete this node from Binary Search Tree 
                                */
                                s = search(root, _data_fake, int_comp);
                                /*feature 2  tracking system*/
                                if(NULL != s )
                                {
                                    s->data.mem = _data_fake.mem;
                                    s->data.cpu = _data_fake.cpu;
                                    update_state_stop_time(&(s->data));
                                    if(enough_time_overload(s->data))
                                    {
                                        write_to_file(s->data);
                                    }
                                    root = delete_node(root, _data_fake, int_comp);
                                }
                                
                        }
                    }
                    else if(FEATURE_1 == feature)
                    {
                            if (1 == in_array_pid_tracking(pid, arr_p_tracking, number_p_tracking))
                            {
                                /* 
                                    alert
                                    if process enought overload time 
                                */
                                
                                s = search(root, _data_fake, int_comp);
                                if (NULL == s)
                                {
                                    root = insert_node(root,int_comp,_data_fake);
                                    /*update start time  */
                                    s = search(root, _data_fake, int_comp);
                                    update_state_start_time(&(s->data));

                                
                                }
                                else 
                                {
                                    /*update stop time*/
                                    /*update cpu , mem */
                                    
                                    s->data.mem = read_mem(pid);
                                    s->data.cpu = read_cpu(pid);
                                    update_state_stop_time(&(s->data));

                                    if((0 == s->data.alert ) && (1 == process_is_overload(s->data,mdata_limit)))
                                    {
                                        process_alert_overload(s->data);
                                        //mdata->alert = 1;
                                        s->data.alert = 1;
                                    }
                                    
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
    
        /* display the tree */
        //display_tree(root);
     //  puts("please enter choose > 0 to continue");
        //scanf("%d", &choose);
       sleep(1);
    } while(choose > 0);
    /* remove element */
  
    dispose(root);
    }

    return(0);
}
