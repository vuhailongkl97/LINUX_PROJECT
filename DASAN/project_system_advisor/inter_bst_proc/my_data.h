#ifndef _MY_DATA_H
#define _MY_DATA_H

#define MAX_LENGTH_OF_NAME 70
#define MAX_LENGTH_OF_TIME 40
#define MAX_LENGTH_OF_STATUS 10
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
 
#endif


