#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include "my_lib_process.h"
#include "my_data.h"
#include "bst.h"

int max_mem = 1;

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
    int feature = 0 ;

    pid = 0;
    mdata_limit.cpu = 0;
    mdata_limit.mem = 1;
    fp = fopen("/proc/meminfo", "r");
	fscanf(fp,"%*s%d", &max_mem);
	printf("mem_max is %d\n", max_mem);

    if( argc < 2 )
    {
        puts("incorrect argument, please follow : ./m <number_feature>");
        feature = atoi(argv[1]);
        return -1;
    }
    
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
                                s = search(root, _data_fake, int_comp);
                                /*feature 2  tracking system*/
                                 if(s && (FEATURE_2 == feature) )
                                {
                                    if(enough_time_overload(s->data))
                                    {
                                        write_to_file(s->data);
                                    }
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
