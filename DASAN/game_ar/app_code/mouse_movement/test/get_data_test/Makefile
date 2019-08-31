PROJDIR  := .
LIBDIR   :=~/working/linux_project/DASAN/game_ar/app_code/mouse_movement/lib
BUILD_TARGET  := t
SRCFILES := $(shell find $(LIBDIR) -type f -name "*.c" )
SRCFILES += t_get_data.c
OBJFILES := $(patsubst %.c,%.o,$(SRCFILES))
CFLAGS   := -lXtst -lX11 -lm -g -Wall
CC 	 := gcc

all: $(OBJFILES)
	$(CC)  $(OBJFILES)  $(CFLAGS) -o $(BUILD_TARGET)
clean:
	rm -f $(OBJFILES) $(BUILD_TARGET)
%.o: %.c 
	$(CC) -c -I $(LIBDIR) $< -o $@

