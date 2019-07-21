#include <stdio.h>
#include <stdlib.h>
#include "my_data.h"
#include "bst.h"
 
#define SIZE 19
void create_fake_data(type_data mdata[SIZE])
{
	int i = 1;	
	char name_fake[MAX_LENGTH_OF_NAME];

	for(i = 1; i< SIZE/2; i++)
	{
		mdata[i].pid = SIZE/2 - i;
	 	mdata[i].cpu = SIZE/2 - i;
		mdata[i].mem = SIZE/2 - i;
		sprintf(mdata[i].name,"process%d", SIZE/2- i);
	}
	for(i = SIZE/2; i< SIZE; i++)
	{
		mdata[i].pid = i;
		mdata[i].cpu = i;
		mdata[i].mem = i;
		sprintf(mdata[i].name,"process%d", i);
	}
}

int main()
{
    node* root = NULL;
    int i;
    comparer int_comp = compare;
    callback f = display;
    type_data data_fake[SIZE];
    type_data _data_fake;

    /*
	 create fake data
	 read from proc
    */
    create_fake_data(data_fake);

    /* insert data into the tree */

    printf("--- C Binary Search Tree ---- \n\n");
    printf("Insert: ");
    for(i = 1; i < SIZE; i++)
    {
        printf("%d ",data_fake[i].pid);
        root = insert_node(root,int_comp,data_fake[i]);
    }
    printf(" into the tree.\n\n");
 
    /* display the tree */
    display_tree(root);
 
    /* remove element */
    int r;
    do
    {
        printf("Enter data to remove, (-1 to exit):");
        scanf("%d",&r);
	_data_fake.pid = r;
	
        if(r == -1)
            break;
        root = delete_node(root, _data_fake, int_comp);
        /* display the tree */
        if(root != NULL)
            display_tree(root);
        else
            break;
    }
    while(root != NULL);
 
    /* search for a node */
    int key = 0;
    node *s;
    while(key != -1)
    {
        printf("Enter data to search (-1 to exit):");
        scanf("%d",&key);
	_data_fake.pid = key;
 
        s = search(root, _data_fake, int_comp);
        if(s != NULL)
        {
		display(s);
		puts("\n");
        }
        else
        {
            printf("node %d not found\n",key);
        }
    }
 
    /* remove the whole tree */
    dispose(root);
    return 0;
}
