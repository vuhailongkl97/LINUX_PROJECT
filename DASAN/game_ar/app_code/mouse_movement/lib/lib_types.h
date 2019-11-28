#ifndef _LIB_TYPES_H
#define _LIB_TYPES_H

#define RATIO  (10)

typedef struct {
	int x_current, y_current;	
	int fd_mouse, fd_keyboard;	
	float current_vx, current_vy;	

	void (*cstor)(void *self, int x_c, int y_c);
	void (*dstor)(void *self);

	void (*move)(void *self,int x_des, int y_des,int jump_size, int speed);
	void (*click)(void *self);
	void (*btn_press)(void* self,int btn, int cmd);

}mouse;

typedef struct {
	int fd_keyboard;
	/*change device is up or down*/
	void (*change_dev)(void *self, int option);

	/*movement character is go ahead , back , left , right*/
	void (*movement)(void *self, int option);

	/*game obj attach*/
	void (*attach)(void *self);

}game_obj;



#endif
