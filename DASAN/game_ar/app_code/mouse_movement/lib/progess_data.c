#include "progess_data.h"
#define DEBUGs
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
FILE* device_init(const char *path)
{
	FILE *fp = NULL ;
	char rely[100] = {0};

	fp = fopen(path, "r+" );	

	if (fp == NULL)
	{
		perror("open file failed");
		return NULL;
	}
	return fp;
	
}
int device_release(FILE *fp)
{
	return (0 == fclose(fp));
}
int get_target(int x1, int y1, float vx, float vy, int *dx, int *dy)
{
	int x2,y3;
	
	//reset postion 
	x1 = y1 = 0;
	
	//x2 = x1 + VELOCITY_TO_PIXEL(vx);		
	//y3 = y1 + VELOCITY_TO_PIXEL(vy);
	x2 = x1 + (int)(vx *RATIO);
	y3 = y1 + (int)(vy *RATIO);

	*dx =  x2;
	*dy =  y3;

	#ifdef DEBUG
		printf("x1 , vx = %d %d  ", *dx, (int)(vx *RATIO));
		printf("y1 , vy = %d %d\n", *dy, (int)(vy *RATIO));
	#endif 

	return 0;	
}
int get_data(FILE *fp,pdata *p)
{
	char rely[200];
	
	memset(rely ,0, 100);
	fprintf(fp, "%d", COMMAND_REQUEST_PITCH_YAW);
	usleep(20000);
	fgets(rely, 200, fp);
	sscanf(rely,"%f  %f %f %d %d",&(p->pitch),&(p->roll),&(p->yaw), &(p->mouse_state), \
			&(p->movement_state));
	#if 0
		printf("string rely :  %s\n", rely);
		printf("%f  %f %f\n", *pitch, *yaw, *roll);
	#endif

	return 0;
}
void caculator_velocity(FILE *fp, mouse *self)
{
	int ret = 0;
	float pitch1, yaw1,roll1, pitch2, yaw2, roll2;
	pdata p1, p2;


	get_data(fp, &p1);

	usleep(20000);
	get_data(fp, &p2);

	self->current_vx = p2.pitch -p1.pitch;

	self->current_vy = p2.yaw - p1.yaw;

        //printf("detail : pitch1 %f pitch2 %f yaw1 %f yaw2 %f", \
			 p1.pitch, p2.pitch, p1.yaw, p2.yaw);
	//printf("detail roll %f %f\n", p1.roll, p2.roll);
	#if 0
			 printf("detail : pitch1 %f pitch2 %f\n", pitch1, pitch2);
			 printf("detail : yaw1 %f yaw2 %f\n", yaw1, yaw2);
		 printf("vx , vy  vz: %f %f \n", *vx , *vy);
		 if ( abs((int)*vx) > 30 || abs((int)*vy) > 30)
		 {
			 printf("detail : pitch1 %f pitch2 %f\n", pitch1, pitch2);
			 printf("detail : yaw1 %f yaw2 %f\n", yaw1, yaw2);
			 sleep(2);
		 }
	#endif
	
}
