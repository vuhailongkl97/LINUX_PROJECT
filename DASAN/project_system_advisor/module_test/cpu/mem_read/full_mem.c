#include <stdio.h>

int main(void)
{
	int i = 0;
	char *pi = NULL;
	char a[1000] = {111};

	while(1)
	{
		pi = (char *)calloc(10000000, sizeof(char));
		for(i = 0 ; i< 10000000; i++)
			*(pi + i ) = i;
		sleep(2);
	}

	return 0 ;
}
