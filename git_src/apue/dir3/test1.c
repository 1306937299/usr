#include <stdio.h>
#include <stdint.h>


int main()
{
	uint32_t a = 0x12345678;

	printf("0x%x\n", *(uint8_t*)&a);

	uint32_t b;
	b = htonl(a);

	printf("0x%x\n", *(uint8_t*)&b);

	return 0;
}
