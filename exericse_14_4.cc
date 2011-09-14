/*
 * exercise_14_4
 * detect lock
 **/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "exercise_14_2.h"
#include "exercise_14_3.h"
static void lockabyte(const char *name, int fd, off_t offset)
{
	if(write_lock(fd, offset, SEEK_SET,1) < 0 )
	  fprintf(stderr, "%s: writew_lock error", name);
	printf("%s: got the lock, byte %ld\n", name, offset);
}
int main(void)
{
	int fd;
	pid_t pid;
	/*
	 * create a file and write two bytes to it
	 * */
	if((fd =create("templock",FILE_MODE)) < 0 )
	  fprintf(stderr, "create error");
	if(write(fd, "ab", 2)!=2)
	  fprintf(stderr, "write error");
	TELL_WAIT();
	if((pid = fork()) < 0)
	{
		fprintf(stderr, "fork error");
	}
	else if(pid == 0)
	{
		lockabyte("child", fd, 0);
		TELL_PARENT(getpid());
			WAIT_PARENT();
	}
	else
	{
		lockabyte("parent", fd, 1);
		TELL_CHILD(pid);
		WAIT_CHILD();
		lockabyte("parent", fd, 0);
	}
	exit(0);


}
