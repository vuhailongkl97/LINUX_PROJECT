#include"stdio.h"
#include <pthread.h>

void *myThreadFun(void *vargp)
{
        sleep(1);
        printf("Printing GeeksQuiz from Thread \n");
        return NULL;
}

void handler(int signo)
{
	puts("ok");
}

int main()
{
	int x = 10;

	signal(SIGINT, handler);

	return 0;
}

