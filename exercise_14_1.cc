/*
 * exrcise_14_1: 长的非阻塞write
 *
 * */
#ifndef _EXERCISE_14_1_
#define _EXERCISE_14_1_
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "exercise_3_5.h"
char buf[500000];

int main(void)
{
	int ntowrite, nwrite;
	char *ptr;
	ntowrite = read(STDIN_FILENO, buf,sizeof(buf));
	fprintf(stderr, "read %d bytes\n",ntowrite);
	set_fl(STDOUT_FILENO, O_NONBLOCK); /*set nonblocking*/
	ptr = buf;
	while(ntowrite > 0)
		{
			errno = 0;
			nwrite = write(STDOUT_FILENO, ptr, ntowrite);
			fprintf(stderr, "nwrite = %d, errno = %d\n", nwrite, errno);
			if(nwrite > 0)
			{
				ptr += nwrite;
				ntowrite -= nwrite;
			}
		}
	clr_fl(STDOUT_FILENO, O_NONBLOCK);/*clear nonblocking*/
	exit(0);
				return 0;

}
#endif
