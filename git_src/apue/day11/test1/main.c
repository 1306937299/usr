/*
 三个线程
 1. 负责输入字符串，将每一个字符入读列
 2. 每隔0.5s入队列一个's'字符
 3. 每隔0.3s出队列一个字符并写入到一个文件中
 */
#include "../../apue.h"
#include "queue.h"

pQueue pq;
pthread_mutex_t mutex;
pthread_cond_t  cond;

void * thr_loop(void *arg)
{
	while (1) {
		usleep(500000);
		pthread_mutex_lock(&mutex);
		en_queue(pq, 's');
		pthread_mutex_unlock(&mutex);
		pthread_cond_broadcast(&cond);
	}
	return NULL;
}

void * thr_file(void *arg)
{
	int fd;
	fd = open("log", O_WRONLY|O_CREAT|O_TRUNC, 0666);
	char ch;
	while (1) {
		usleep(300000);
		pthread_mutex_lock(&mutex);
		while ( empty_queue(pq) ) { 
			//pthread_mutex_unlock(&mutex);
			//sched_yield();
			//pthread_mutex_lock(&mutex);
			pthread_cond_wait(&cond, &mutex);//阻塞
		}
		de_queue(pq, &ch);
		pthread_mutex_unlock(&mutex);
		write(fd, &ch, 1);	
	}

	close(fd);
	return NULL;
}

int main()
{
	pthread_t tid_loop, tid_file;

	pq = init_queue();

	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond, NULL);

	pthread_create(&tid_loop, NULL, thr_loop, NULL);
	pthread_create(&tid_file, NULL, thr_file, NULL);

	char buf[32];
	int i;
	while (1) {
		bzero(buf, 32);
		read(0, buf, 32);
		if ( strcmp(buf, "quit\n") == 0 )
			break;
		for ( i=0; buf[i]!='\0'; i++) {
			pthread_mutex_lock(&mutex);
			en_queue(pq, buf[i]);
			pthread_mutex_unlock(&mutex);
			pthread_cond_broadcast(&cond);
		}
	}

	pthread_cancel(tid_loop);
	pthread_cancel(tid_file);
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
	destroy_queue(pq);
	return 0;
}

