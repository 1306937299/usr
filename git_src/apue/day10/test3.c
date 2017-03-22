#include "../apue.h"

int num = 1;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void * thr_func(void *arg)
{
	while (1) {
		//加锁
		//num = 16
		pthread_mutex_lock(&mutex);
		if ( num > 15 ) {
			pthread_mutex_unlock(&mutex);
			break;
		}
		sched_yield();
		sched_yield();
		sched_yield();
		sched_yield();
		sched_yield();
		printf("[%d] num=%d\n", (int)arg, num);	// A 1 B 1
		sched_yield();
		sched_yield();
		num++; //A num=2  B num=3
		//解锁
		pthread_mutex_unlock(&mutex);
		sched_yield();
		sched_yield();
		sched_yield();
		sched_yield();
		sched_yield();
		sched_yield();
		sched_yield();
	}
	return NULL;
}



int main()
{
	pthread_t tid[5];
	int i;

	for ( i=0; i<5; i++) {
		pthread_create(tid+i, NULL, thr_func, (void*)i);
	}

	for ( i=0; i<5; i++) {
		pthread_join(tid[i], NULL);
	}

	return 0;
}
