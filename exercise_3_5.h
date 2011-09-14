#ifndef _EXERCISE_3_5_
#define _EXERCISE_3_5_
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
void set_fl(int fd, int flags)
{
	int val;
	if(val = fcntl(fd,  F_GETFL, 0) < 0)
	  fprintf(stderr, "fcntl F_GETFL error");
	val |= flags; /*turn on flags*/
	if(fcntl(fd, F_SETFL, val) < 0)
	  fprintf(stderr,"fcntl F_SETFL error");
}
void clr_fl(int fd, int flags)
{
	int val;
	if(val = fcntl(fd, F_GETFL,0) < 0)
	  fprintf(stderr, "fcntl F_GETFL error");
	val &= ~flags; //turn flags off
	if(fcntl(fd, F_SETFL, 0) == -1)
	fprintf(stderr, "fcntl F_SETFL error");

}
#endif
