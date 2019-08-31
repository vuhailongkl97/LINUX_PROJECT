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
int device_init(const char *path)
{
	int fd = 0;
	char rely[100];

	fd = open(path, O_RDWR );	

	if (0 >  fd)
	{
		perror("open file failed");
		return -1;
	}
	sleep(2);
	read(fd, rely, 100);

	return fd;
	
}
int device_release(int fd)
{
	return (0 == close(fd));
}
int get_target(int x1, int y1, float vx, float vy, int *dx, int *dy)
{
	int x2,y3;
	
	
	//x2 = x1 + VELOCITY_TO_PIXEL(vx);		
	//y3 = y1 + VELOCITY_TO_PIXEL(vy);
	x2 = x1 + (int)(vx *RATIO);
	y3 = y1 + (int)(vy *RATIO);

	#ifdef DEBUG
		printf("x1 , vx = %d %f", x1, (int)(vx *RATIO));
		printf("y1 , vy = %d %f", y1, (int)(vy *RATIO));
	#endif 
	*dx =  x2;
	*dy =  y3;

	return 0;	
}
int get_data(const int fd, float *pitch, float *yaw)
{
	char rely[100], tmp[100];
	
	memset(rely ,'\0', 100);
	sprintf(tmp,"%d", COMMAND_REQUEST_PITCH_YAW);
	write(fd, tmp, 1);
	usleep(10000);
	read(fd, rely, 100);
	sscanf(rely,"%f%f",pitch, yaw);
	#ifdef DEBUG
		printf("%f  %f\n", *pitch, *yaw);
	#endif

	return 0;
}
void caculator_velocity(const int fd, float *vx , float *vy)
{
	int ret = 0;
	float pitch1, yaw1, pitch2, yaw2;


	get_data(fd, &pitch1, &yaw1);

	usleep(100);
	get_data(fd, &pitch2, &yaw2);

	*vx = pitch1 -pitch2;

	*vy = yaw1 - yaw2;

	#ifdef DEBUG
			 printf("vx , vy : %f %f \n", *vx , *vy);
	#endif
	
}
