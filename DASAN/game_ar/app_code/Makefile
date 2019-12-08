PROJDIR  := .
LIBDIR   :=./lib
BUILD_TARGET  := t
SRCFILES := $(shell find $(LIBDIR) -type f -name "*.c" )
SRCFILES +=main.c
OBJFILES := $(patsubst %.c,%.o,$(SRCFILES))
CFLAGS   := -lm -g -lpaho-mqtt3c
CC 	 := gcc
DEFAULT_FLAG=SERIAL

ifneq ($(FLAG),)
DFLAG=-D$(FLAG)
else
DFLAG:=-D$(DEFAULT_FLAG)
endif


all: $(OBJFILES)
	$(CC)  $(OBJFILES)  $(CFLAGS) -o $(BUILD_TARGET)
clean:
	rm -f $(OBJFILES) $(BUILD_TARGET)
%.o: %.c 
	$(CC) -c -I $(LIBDIR) $< -o $@ $(DFLAG)

