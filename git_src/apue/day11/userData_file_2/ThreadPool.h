#ifndef THREADPOOL_H
#define THREADPOOL_H

#include "queue.h"

//线程池结构
typedef struct {
	int thread_num;			//线程池中线程的数量
	pthread_t *tid_arr;		//线程池中线程id的数组
	pQueue services_pq;		//线程池的服务请求队列
}ThreadPool_t;

int threadpool_init(int num, void *(*pfunc)(void*), void *arg);
int threadpool_destroy();	//销毁线程池

int threadpool_add_services(struct s_t *msg);	//向服务请求队列中添加服务请求

int threadpool_get_services(struct s_t *msg);	//从服务请求队列中取出服务请求



#endif
