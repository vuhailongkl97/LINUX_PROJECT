#include "progess_data.h"

/*
    (x3,y3)             (dx,dy)
	-------------------
	|		  |
	^		  |
	|		  |
	vy		  |
	|		  |
	-------vx ->-------
    (x1,y1)        (x2,y2)

	(dx,dy) = (x2,y3);
*/
int get_target(int x1, int y1, float vx, float vy, int *dx, int *dy)
{
	int x2,y3;
	
	x2 = x1 + VELOCITY_TO_PIXEL(vx);		
	y3 = y1 + VELOCITY_TO_PIXEL(vy);

	*dx =  x2;
	*dy =  y3;

	return 0;	
}
int get_data(char *dev_path, float *pitch, float *yaw)
{
	char rely[100], tmp[100];
	int fd = 0;
	
	
	fd = open(dev_path, O_RDWR );	

	if (0 >  fd)
	{
		perror("open file failed");
		return -1;
	}
	memset(rely ,'\0', 100);
	sprintf(tmp,"%d", COMMAND_REQUEST_PITCH_YAW);
	write(fd, tmp, 1);
	usleep(10000);
	read(fd, rely, 100);
	sscanf(rely,"%f%f",pitch, yaw);
	printf("%f  %f\n", *pitch, *yaw);

	close(fd);
	return 0;
}
void caculator_velociry(float *vx , float *vy)
{
	int ret = 0;
	get_data()	
}
