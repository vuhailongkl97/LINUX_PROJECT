#include "lib_game_obj.h"
#include <assert.h>

void g_change_dev(void *_g_obj,int option)
{
	game_obj *g_obj = (game_obj *)_g_obj;
	static int current_dev = KEY_1;	

	switch(option)	
	{
		case g_DEV_NEXT :
			current_dev ++;
			break;
		case g_DEV_BACK:
			current_dev --;
			break;
		default:
			printf("error option %s %d", __FUNCTION__, __LINE__);
	}
	if (current_dev > KEY_4 ) 
		current_dev = KEY_4;
	else if (current_dev < KEY_1)
		current_dev = KEY_1;
	press_key(g_obj, current_dev, 1);
	press_key(g_obj, current_dev, 0);

}

void g_movement(void *_g_obj, int option)
{
	game_obj *g_obj = (game_obj *)_g_obj;
	switch(option)	
	{
		case g_MOVE_UP:
			break;
		case g_MOVE_BACK:
			break;
		case g_MOVE_LEFT:
			break;
		case g_MOVE_RIGHT:
			break;
		default:
			printf("error option %s %d", __FUNCTION__, __LINE__);
	}
	
}

void g_attach(void *g_obj)
{

}

void press_key(void *_g_obj, int key, int cmd)
{
	struct input_event event, event_end;
	
	char path[40] = {0};
	int fd = 0;
	game_obj* self = (game_obj*)_g_obj;
	
	sprintf(path, "/dev/input/event%d", self->fd_keyboard);
	fd = open(path, O_RDWR);
	if (fd < 0)
	{
	        perror("press_key can't open device file");
	        exit(0);
	}
	
	memset(&event, 0, sizeof(event));
	memset(&event_end, 0, sizeof(event_end));
	
	gettimeofday(&event.time, NULL);
	event.type = EV_KEY;
	event.code = key;
	event.value = cmd;
	/*stop move signal*/
	gettimeofday(&event_end.time, NULL);
	event_end.type = EV_SYN;
	event_end.code = SYN_REPORT;
	event_end.value = 0;
	
	write(fd, &event, sizeof(event));// Move the mouse
	write(fd, &event_end, sizeof(event_end));// Show move
	close(fd);
	
	usleep(10000);
}

void * gameobj_init(void (*change_dev)(void*, int ), \
 void (*movement)(void *, int ), void (*attach)(void *), int fd_keyboard)
{
	game_obj* g_obj = NULL;

	g_obj = (game_obj*)malloc(sizeof(game_obj));
	assert(g_obj);

	g_obj->change_dev = change_dev;
	g_obj->movement = movement;
	g_obj->attach = attach;
	g_obj->fd_keyboard = fd_keyboard;

	return g_obj;

}
void gameobj_des(void *_g_obj)
{
	game_obj* g_obj = (game_obj*)_g_obj;
	close (g_obj->fd_keyboard);
	free(g_obj);
}

