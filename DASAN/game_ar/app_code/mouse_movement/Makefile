PROJDIR  := .
BUILD_TARGET  := t
SRCFILES := $(shell find $(PROJDIR) -type f -name "*.c" )
OBJFILES := $(patsubst %.c,%.o,$(SRCFILES))
CFLAGS   := -lXtst -lX11 -lm -g
CC 	 := gcc

all: $(OBJFILES)
	$(CC) $(OBJFILES) $(CFLAGS) -o $(BUILD_TARGET)
clean:
	rm -f $(OBJFILES) $(BUILD_TARGET)
%.o: %.c 
	$(CC) -c $< -o $@

