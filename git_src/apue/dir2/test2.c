#include "../apue.h"

int main()
{
	time_t t ;
	struct tm *ptm;

	t = time(NULL);
	printf("t=%d\n", t);

	
	ptm = localtime(&t);

	printf("%d-%d-%d %d:%d:%d\n", 
			ptm->tm_year+1900, ptm->tm_mon+1, ptm->tm_mday, 
			ptm->tm_hour, ptm->tm_min, ptm->tm_sec);


	return 0;
}
