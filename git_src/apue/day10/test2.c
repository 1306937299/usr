#include "../apue.h"
#define LEFT	3000000
#define RIGHT	3000200

int compute(int num)
{
	int i, j, flag=0;
	for (i=2; i<num/2; i++) {
		if ( num%i == 0 ) {
			flag = -1;
			break;
		}
	}
	return flag;
}


void * thr_func(void*arg)
{//(int)arg
	int i;
	int count= 0;
	//3000000 3000005  3000010 ...
	//3000001 3000006  3000011 ...
	//3000004 3000009  3000014 ...
	for ( i=LEFT+(int)arg; i<=RIGHT; i+=5) {
		if ( compute(i) == 0 ) {
			printf("[%d] %d is a primer.\n", (int)arg, i);
			count++;
		}
	}
	return (void*)count;
}

int main()
{
	pthread_t tid[5];
	int i;
	int sum = 0, ret;

	for ( i=0; i<5; i++) {
		pthread_create(tid+i, NULL, thr_func, (void*)i);
	}

	for ( i=0; i<5; i++) {
		pthread_join(tid[i], (void**)&ret);
		sum+=ret;
	}
	
	printf("sum=%d\n", sum);

	return 0;
}

