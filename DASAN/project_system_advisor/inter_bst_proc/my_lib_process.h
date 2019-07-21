#ifndef _MY_LIB_PROCESS_H
#define _MY_LIB_PROCESS_H
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int check_is_pid(const char *name);
float read_cpu(int pid);
char* read_name(int pid, char *const name);
float read_mem(int pid);

#endif
