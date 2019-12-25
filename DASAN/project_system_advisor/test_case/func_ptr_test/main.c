#include <stdio.h>

typedef void* (*compare)(char *) ;

void *hello(const char *a)
{

	return NULL;
}
int main(void)
{
	compare a ;
	a = hello;

	a("kk");
	return 0;
}
