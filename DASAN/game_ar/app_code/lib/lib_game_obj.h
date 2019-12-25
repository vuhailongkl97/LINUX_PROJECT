#ifndef _LIB_GAME_OBJ_
#define _LIB_GAME_OBJ_
#include "lib_types.h"
#include "lib_mouse.h"

enum option_game
{
	g_MOVE_UP,
	g_MOVE_BACK,
	g_MOVE_LEFT,
	g_MOVE_RIGHT,
	g_DEV_NEXT,
	g_DEV_BACK
} ;
enum mouse_ev { mIDLE = 0, LEFT_CLICK  = 1, RIGHT_CLICK = 2 , STOP_MOVE = 4};
enum orientation_character {oIDLE = 0, LEFT = 1 , GO_AHEAD = 2 , RIGHT = 4, BACK = 8};

void g_change_dev(void *g_obj,int );

void g_movement(void *g_obj, int);

void g_attach(void *g_obj);

void *gameobj_init( void (*change_dev)(void*,int ), \
	void (*g_movement)(void *, int ), \
	void (*g_attach)(void *), int );

void press_key(void *, int ,int cmd);
void gameobj_des(void *);

#endif 
