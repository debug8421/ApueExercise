/*
 *exercise_14_3.h
 * */
#ifndef _EXERCISE_14_3_
#define _EXERCISE_14_3_
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
pid_t lock_test(int fd, int type, off_t offset, int whence, off_t len)
{
	struct flock lock;
	lock.type = type;  /*F_RDLCK or F_WRLCK*/
	lock.l_start = offset; /*byte offset, relative to l+_whence*/
	lock.l_whence = whence; /*SEEK_SET, SEEK_CUR, SEEK_END*/
	lock.len = len;
	if(fcntl(fd, F_GETLK, &lock) < 0)
		fprintf(stderr, "fcntl error");
	if(lock.l_type == F_UNLCK)
		return 0;
	return (lock.l_pid);   //true, return pid of lock owner

}
#define is_read_lockable(fd, offset, whence, len) \
	(lock_test((fd), F_RDLCK, (offset), (whence), (len)) == 0)
#define is_write_lockable(fd, offset,whence,len) \
	(lock_test((fd), F_WRLCK, (offset), (whence), (len)) == 0)
#endif
