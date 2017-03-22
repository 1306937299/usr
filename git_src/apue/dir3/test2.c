#include "../apue.h"

int main()
{
	char *p = "192.168.2.254";
	char *pret;
	struct in_addr addr;

	addr.s_addr = inet_addr(p);

	printf("%u\n", addr.s_addr);

	addr.s_addr++;
	pret = inet_ntoa(addr);

	printf("pret=%s\n", pret);
	return 0;
}
