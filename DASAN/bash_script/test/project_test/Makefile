override FLAGS +=-Wall
FILE_IN=main.c lib.c
OBJFILES := $(patsubst %.c,%.o,$(FILE_IN))

all: $(OBJFILES)
	gcc -o t $(FLAGS) $(OBJFILES)

clean_trash:
	rm -f output2.txt  *.o

%.o: %.c
	gcc -c -Wall $< -o $@

