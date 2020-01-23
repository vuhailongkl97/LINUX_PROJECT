#include <stdio.h>
int main(void)
{

	FILE *fp = fopen("/proc/meminfo", "r");
	int mem_max;

	fscanf(fp,"%*s%d", &mem_max);
	printf("mem_max is %d", mem_max);

	return 0;
}
