#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define dev_file "/dev/ttyACM0"

int main(void)
{
	int choice = 1;
	char rely[1000];
	char tmp[1000];
	int fd = open(dev_file, O_RDWR );	

	if (0 >  fd)
	{
		perror("open file failed");
		return -1;
	}
	
	sleep(2);
	read(fd, rely, 1000);
	puts(rely);
	choice = 0;
	int time_change=0;
	float pitch, yaw;
	do 
	{
		memset(rely ,'\0', 100);
		//printf("write %d to device uart ... ", choice);	
		sprintf(tmp,"%d", choice);
		write(fd, tmp, 1);
		usleep(10000);
		read(fd, rely, 100);
		sscanf(rely,"%f%f",&pitch, &yaw);

		printf("%f  %f\n", pitch, yaw);
		

		//printf("enter choice > 0 to continue  ");
		//scanf("%d", &choice);
		//sau 200ms lai check 1 lan  
		//time_change++;
		//if ( 0 == time_change )
		//{
		//	value1 = man   
		//}
			
	}
	while( 0 <= choice );

	close(fd);
	return 0;
}
