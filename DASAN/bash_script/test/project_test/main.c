#include"stdio.h"

void *func(void *vargp)
{
        sleep(1);
        printf("Printing GeeksQuiz from Thread \n");
        return NULL;
}

int main()
{
		pthread_t t;

		pthread_create(&t, NULL, func, NULL);
		pthread_join(t, NULL);

		puts("hello");
        exit(0);
}

