#include <stdlib.h>
#include <pthread.h>

#define NHASH 29
#define NASH(fp) (((unsigned long)fp) %NHASH)
struct foo1 *fh[NHASH];

pthread_mutex_t hashlock = PTHREAD_MUTEX_INITIALIZER;

struct foo1{
	int f_count;
	pthread_mutex_t f_lock;
	struct foo1	*f_next; /*protexted by hashlock*/
	int f_id;
	/* ... more stuff here ...*/
};

struct foo1 *
foo1_alloc(void) /*allocate the object */
{
	struct foo1 *fp;
	int idx;

	if((fp = (foo1*)malloc(sizeof(struct foo1))) != NULL )
	{
		fp->f_count = 1;
		if(pthread_mutex_init(&fp->f_lock, NULL) != 0)
		{
			free(fp);
			return NULL;
		}
		idx = NASH(fp);
		pthread_mutex_lock(&hashlock);
		fp->f_next = fh[idx];
		fh[idx] = fp->f_next;
		pthread_mutex_lock(&fp->f_lock);
		pthread_mutex_unlock(&hashlock);
		/* ... continue initialization ....*/
		pthread_mutex_unlock(&fp->f_lock);

	}
	return fp;
}

void foo1_hold(struct foo1 *fp)
{
	pthread_mutex_lock(&fp->f_lock);
	fp->f_count++;
	pthread_mutex_unlock(&fp->f_lock);

}

struct foo1 *
foo1_find(int id) /*find an existing object */
{
	struct foo1 *fp;
	int idx;

	idx = NASH(fp);
	pthread_mutex_lock(&hashlock);
	for(fp = fh[idx]; fp != NULL; fp = fp->f_next)
	{
		if(fp->f_id == id)
		{
			foo1_hold(fp);
			break;
		}
	}
	pthread_mutex_unlock(&hashlock);
	return(fp);
}
void foo1_release(struct foo1 *fp)
{
	struct foo1 *tfp;
	int idx;

	pthread_mutex_lock(&fp->f_lock);
	if(fp->f_count == 1)
	{
		pthread_mutex_unlock(&fp->f_lock);
		pthread_mutex_lock(&hashlock);
		pthread_mutex_lock(&fp->f_lock);
		/* recheck the condition */
		if(fp->f_count != 1)
		{
			fp->f_count --;
			pthread_mutex_unlock(&fp->f_lock);
			pthread_mutex_unlock(&hashlock);
			return;
		}
		/*remove from list */
		idx = NASH(fp);
		tfp = fh[idx];
		if(tfp == fp)
		{ 
			fh[idx] = fp->f_next;
		}
		else
		{
			while(tfp->f_next != fp)
			{
				tfp = tfp->f_next;
			}
			tfp->f_next = fp->f_next;
		}

		pthread_mutex_unlock(&hashlock);
		pthread_mutex_unlock(&fp->f_lock);
		pthread_mutex_destroy(&fp->f_lock);
		free(fp);
	}
	else
	{
		fp->f_count--;
		pthread_mutex_unlock(&fp->f_lock);
	}
}
