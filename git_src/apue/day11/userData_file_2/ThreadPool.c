#include "ThreadPool.h"

static ThreadPool_t *pool = NULL;

int threadpool_init(int num, void *(*pfunc)(void*), void *arg)
{//num:线程池中线程的个数
 //pfunc:线程池中线程的入口函数
 //arg:pfunc的参数
	if ( pool != NULL ) {
		return -1;//表示线程池已经被创建
	}
	pool = malloc(sizeof(ThreadPool_t));
	pool->thread_num = num;
	pool->tid_arr = malloc(num*sizeof(pthread_t));
	pool->services_pq = init_queue();

	int i;
	for ( i=0; i<num; i++) {
		pthread_create(&pool->tid_arr[i], NULL, pfunc, arg);	
	}

	return 0;
}

int threadpool_destroy()	//销毁线程池
{
	int i;
	if ( pool == NULL ) {
		return -1;
	}

	for ( i=0; i<pool->thread_num; i++) {
		pthread_cancel(pool->tid_arr[i]);
	}
	destroy_queue(pool->services_pq);
	free(pool->tid_arr);
	free(pool);
	pool = NULL;
	return 0;
}

int threadpool_add_services(struct s_t *msg)	//向服务请求队列中添加服务请求
{
	if ( pool == NULL ) {
		return -1;
	}
	en_queue(pool->services_pq, *msg);
	return 0;
}

int threadpool_get_services(struct s_t *msg)	//从服务请求队列中取出服务请求
{
	if ( pool == NULL ) {
		return -1;
	}
	de_queue(pool->services_pq, msg);
	return 0;
}

