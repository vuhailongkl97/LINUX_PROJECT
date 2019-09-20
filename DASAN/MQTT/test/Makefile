.PHONY : all
PUB_SRC := $(wildcard pub.c)
SUB_SRC := $(wildcard sub.c)
PUB_OBJ := $(patsubst %.c, %.o, $(PUB_SRC)) 
SUB_OBJ := $(patsubst %.c, %.o, $(SUB_SRC)) 
#LIB_DIR := /home/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/src
LIB_DIR := /usr/local/lib
FLAGS   := -lpaho-mqtt3c

all: sub pub

sub: $(SUB_OBJ)
	$(CC) $^ -o $@ -L$(LIB_DIR) $(FLAGS)

pub: $(PUB_OBJ)
	$(CC) $^ -o $@ -L$(LIB_DIR) $(FLAGS)

clean:
	rm -rf sub pub  $(SUB_OBJ) $(PUB_OBJ)
