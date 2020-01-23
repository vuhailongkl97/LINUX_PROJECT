#include <stdio.h>
#include <unistd.h>

int main(void)
{
	char buff[100];

	memset(buff, '\0', 100);
	readlink("/proc/self/exe",buff, 100);

	puts(buff);

	return 0;
}
