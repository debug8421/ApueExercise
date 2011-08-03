#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

extern int makethread(void *(*) (void *), void *);

struct to_info{
	void (*to_fn)(void *); /*function */
	void *to_arg; /*argument */
	struct timespec to_wait; /*time to wait*/

}
#define SECTONSEC 1000000000
#define USECTONSEC 1000
void * timeout_helper(void *args)
{
	struct to_info *tip;
	tip = (struct to_info* )arg;
	nanosleep(&tip->to_wait, NULL);
	(*tip->to_fn)(tip->to_arg);
	return (0);
}
void timeout(const struct timespec *when, void (*func)(void *), void *arg)
{
	struct timespec now;
	struct timeval tv;
	struct to_info *tip;
	int err;
	gettimeofday(&tv, NULL);
	now.tv_sec = tv.tv_sec;
	now.tv_nsec = tv.tv_usec * USECTONSEC;
	if((when->tv_sec > now.tv_sec) || (when->tv_sec == now.tv_sec && when->tv_nsec > now.tv_nsec))
	{
		tip = (to_info*)malloc(sizeof(struct to_info));
		if(tip != NULL)
		{
			tip
		}
	}

}
