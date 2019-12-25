#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

long long mili_second()
{
	struct timeval start, end;
 	gettimeofday(&start, NULL);	
	long long delta_us = (start.tv_sec) * 1000LL + start.tv_usec / 1000;
	return delta_us;

}
//int main(void)
//{
//	printf("mili 1 %lld\n", milis());
//	usleep(1000);
//	printf("mili 1 %lld\n", milis());
//	printf("mili 1 %lld\n", milis());
//	sleep(1);
//	printf("mili 1 %lld\n", milis());
//	return 0;
//}
