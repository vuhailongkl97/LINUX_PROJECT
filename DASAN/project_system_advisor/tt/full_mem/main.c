#include <stdio.h>

int main(void)
{
	int *a;
	int i = 0;
	int j = 0;
	int num = 10;	
	
	printf("pid = %d\n", getpid());

	for (j =0 ; j< 1000; j ++)	
	{
		a = (int *)malloc(sizeof(int) *1000 * 100000);
		for (i = 0; i< 1000 * 100000; i++)
			a[i] = i;
		puts("enter a number to continue");
		scanf("%d", &num);
	}
	free(a);
	
	return 0;
}
