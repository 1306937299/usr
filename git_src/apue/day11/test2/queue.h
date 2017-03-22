#ifndef QUEUE_H
#define QUEUE_H
#include <pthread.h>

typedef char ElemType;//队列中数据元素的类型
struct node {//链表结点
	ElemType data;
	struct node * next, *prev;
};

typedef struct {//队列
	struct node *phead;
	pthread_mutex_t mutex;
	pthread_cond_t  cond;
}sQueue, *pQueue;

pQueue init_queue();

void destroy_queue(pQueue);

int en_queue(pQueue pq, ElemType data);

int de_queue(pQueue pq, ElemType *data);

int empty_equeue(pQueue pq);

#endif
