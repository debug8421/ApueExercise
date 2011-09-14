#ifndef _EXERCISE_14_2_
#define _EXERCISE_14_2_
#include <fcntl.h>
int lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len){
	struct flock lock;
	lock.l_type = type; //F_RDLCK, F_WRLCK,F_UNLCK
	lock.l_start = offset;//byte offset , relative to l_whence
	lock.l_whence = whence; //SEEK_SET, SEEK_CUR, SEEK_END
	lock.l_len = len;
	return (fcntl(fd, cmd, &lock));
}
#define read_lock(fd, offset, whence, len) \
	lock_reg((fd),F_SETLK, F_RDLCK, (offset), (whence), (len))
#define write_lock(fd, offset, whence,len) \
	lock_reg((fd),F_SETLK,F_WRLCK,(offset),(whence),(len));
#define writew_lock(fd,offset, whence,len) \
	lock_reg((fd),F_SETLKW,F_WRLCK,(offset),(whence),(len));
#define un_lock(fd,offset, whence,len) \
	lock_reg((fd), F_SETLK,F_UNLCK,(offset), (whence),(len));
#endif
