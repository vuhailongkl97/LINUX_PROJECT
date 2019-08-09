#include"stdio.h"
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
        exit(0);
}

