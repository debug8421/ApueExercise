/*
 * apue.cc
 *
 *  Created on: Feb 26, 2011
 *      Author: Tiandao
 */
#include <sys/stat.h>
#include <stdio.h>
int main()
{
   struct stat statbuf;
   //turn on set-group-ID and turn off group-execute
   if(stat("foo",&statbuf)< 0)
	   printf("stat error for foo");
   if(chmod("foo", (statbuf.st_mode & ~S_IXGRP)| S_ISGID) < 0)
	   printf("chmod error for foo");
   if(chmod("bar", S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)<0)
	   printf("chmod error for bar");
  return 0;

}
