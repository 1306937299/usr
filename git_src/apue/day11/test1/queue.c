#include "queue.h"
#include <stdlib.h>
#include <string.h>

pQueue init_queue()
{
	pQueue p = malloc(sizeof(sQueue));	//队列结构体
	p->phead = malloc(sizeof(struct node));	//头结点
	bzero(&p->phead->data, sizeof(ElemType));
	p->phead->next = p->phead->prev = p->phead;
	return p;
}

void destroy_queue(pQueue pq)
{
	ElemType tmp;
	if ( pq != NULL ) {
		while ( de_queue(pq, &tmp) == 0 ) {
			;
		}
		free(pq->phead);
		free(pq);
		pq = NULL;
	}
}

int en_queue(pQueue pq, ElemType data)
{
	struct node *pnew = malloc(sizeof(struct node));
	pnew->data = data;
	
	pnew->next = pq->phead->next;
	pnew->prev = pq->phead;
	pq->phead->next->prev = pnew;
	pq->phead->next = pnew;
	return 0;
}

int de_queue(pQueue pq, ElemType *data)
{
	if ( pq->phead->next == pq->phead ) {
		return -1;
	}
	struct node *pdel = pq->phead->prev;
	*data = pdel->data;
	pdel->next->prev = pdel->prev;
	pdel->prev->next = pdel->next;
	free(pdel);
	return 0;
}
int empty_queue(pQueue pq)
{
	return pq->phead->next == pq->phead;
}


