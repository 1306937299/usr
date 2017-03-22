#include "queue.h"
#include <stdlib.h>
#include <string.h>

pQueue init_queue()
{
	pQueue p = malloc(sizeof(sQueue));	//队列结构体
	p->phead = malloc(sizeof(struct node));	//头结点
	bzero(&p->phead->data, sizeof(ElemType));
	p->phead->next = p->phead->prev = p->phead;

	pthread_mutex_init(&p->mutex, NULL);
	pthread_cond_init(&p->cond, NULL);
	return p;
}

void destroy_queue(pQueue pq)
{
	struct node *pdel;
	if ( pq != NULL ) {
		while (  pq->phead->next != pq->phead ) {
			pdel = pq->phead->next;
			pdel->next->prev = pdel->prev;
			pdel->prev->next = pdel->next;
			free(pdel);
		}
		free(pq->phead);
		pthread_mutex_destroy(&pq->mutex);
		pthread_cond_destroy(&pq->cond);
		free(pq);
		pq = NULL;
	}
}

int en_queue(pQueue pq, ElemType data)
{
	struct node *pnew = malloc(sizeof(struct node));
	pnew->data = data;
	
	pthread_mutex_lock(&pq->mutex);
	pnew->next = pq->phead->next;
	pnew->prev = pq->phead;
	pq->phead->next->prev = pnew;
	pq->phead->next = pnew;
	pthread_mutex_unlock(&pq->mutex);
	pthread_cond_broadcast(&pq->cond);
	return 0;
}

int de_queue(pQueue pq, ElemType *data)
{
	pthread_mutex_lock(&pq->mutex);
	while ( pq->phead->next == pq->phead ) {
		pthread_cond_wait(&pq->cond, &pq->mutex);
	}
	struct node *pdel = pq->phead->prev;
	*data = pdel->data;
	pdel->next->prev = pdel->prev;
	pdel->prev->next = pdel->next;
	pthread_mutex_unlock(&pq->mutex);
	free(pdel);
	return 0;
}
int empty_queue(pQueue pq)
{
	pthread_mutex_lock(&pq->mutex);
	int ret = pq->phead->next == pq->phead;
	pthread_mutex_unlock(&pq->mutex);
	return ret;
}


