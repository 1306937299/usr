#include "../apue.h"

void func()
{
	pthread_exit(NULL);
}
int x = 111;
struct A {
	int l;
	int h;
};
void * thr_func(void *arg)
{
	printf("[%s] tid=%d arg=%d\n", __func__, pthread_self(), (int)arg);
/*
	while (1) {
		usleep(500000);
		write(1, "x", 1);
	}
*/
	//func();
	
	struct A *s1 = malloc(sizeof(struct A));
	s1->l = 1;
	s1->h = 2;

	return (void*)s1;

	//return (void*)&x;
	//return (void*)x;
	//pthread_exit(NULL);
}

int main()
{
	pthread_t tid;
	int a = 10;

	pthread_create(&tid, NULL, thr_func, (void*)a);

	printf("[%s] tid=%d\n", __func__, tid);

	//int *p;
	//pthread_join(tid, (void**)&p);
	//int p;
	//pthread_join(tid, (void**)&p);
	//printf("*p=%d\n", p);
	struct A *p;
	pthread_join(tid, (void**)&p);
	printf("%d %d\n", p->l, p->h);

	/*
	while (1) {
		usleep(1000000);
		write(1, "X", 1);
	}
	*/

	return 0;
	//exit(0);
}
