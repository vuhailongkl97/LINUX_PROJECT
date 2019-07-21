#ifndef _MY_DATA_H
#define _MY_DATA_H

#define MAX_LENGTH_OF_NAME 70
#define MAX_LENGTH_OF_TIME 40
#define MAX_LENGTH_OF_STATUS 10

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "my_lib_process.h"

extern int feature;
extern int limit_time;

enum feature {FEATURE_1 = 1, FEATURE_2 = 2 };

typedef struct _data{
	int pid;
	float cpu;
	float mem;
	char name[MAX_LENGTH_OF_NAME + 1];
	char start_time[MAX_LENGTH_OF_TIME + 1];
	char stop_time[MAX_LENGTH_OF_TIME + 1];
	char status[MAX_LENGTH_OF_STATUS + 1];
}m_data;

typedef m_data type_data;

typedef struct node
{
    type_data data;
    struct node* left;
    struct node* right;
} node;
typedef void (*callback)(node*);

typedef int (*comparer)(type_data, type_data);
extern void enter_data(type_data *, type_data );
extern int compare(type_data left,type_data right);
extern void display(node* nd);
int fill_raw_data(type_data *mdata,int pid, float cpu, float mem, char *name) ;
int fill_data(type_data *mdata, int pid);
int update_state_start_time(type_data *mdata);
int update_state_stop_time(type_data *mdata);
int enough_time_overload(type_data mdata);
int process_is_overload(type_data mdata, type_data mdata_limit);
int write_to_file(type_data mdata);
node *delete_process_if_not_exist_in_proc(node * root);
extern void traverse_tree(node *root, int *n, int *arr);
extern node* delete_node(node* , type_data ,comparer );
extern node* search(node *, type_data ,comparer );

#endif


