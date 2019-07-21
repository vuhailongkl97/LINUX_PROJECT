#include <stdio.h>

int main(void)
{
	int *a;
	int i = 0;
	
	a = (int *)malloc(sizeof(int) *1000 * 10000);
	for (i = 0; i< 1000 * 10000; i++)
		a[i] = i;
	
	sleep(10000);
	free(a);
	
	return 0;
}
