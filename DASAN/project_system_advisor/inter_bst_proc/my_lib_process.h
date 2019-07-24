#ifndef _MY_LIB_PROCESS_H
#define _MY_LIB_PROCESS_H
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <dirent.h>
#include "my_data.h"
#include <signal.h>

int check_is_pid(const char *name);
float read_cpu(int pid);
char* read_name(int pid, char *const name);
float read_mem(int pid);
int pid_is_not_in_proc(int pid);
int process_alert_overload();
void write_tree_handler(int signo);

#endif
