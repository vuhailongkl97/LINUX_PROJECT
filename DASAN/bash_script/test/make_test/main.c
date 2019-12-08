#include"stdio.h"
//#include <stdlib.h>
//#include <unistd.h> //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>

// A normal C function that is executed as a thread
// when its name is specified in pthread_create()
void *myThreadFun(void *vargp)
{
        sleep(1);
        printf("Printing GeeksQuiz from Thread \n");
        return NULL;
}

int main()
{
		int a = 10;
        pthread_t thread_id;
        printf("Before Thread\n");
        printf("After Thread\n");
        exit(0);
}

