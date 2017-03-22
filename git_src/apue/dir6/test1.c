#include <stdio.h>

union A {
	char ch;
	int a;
};

int main()
{
	union A a1;

	a1.a = 1124;	//1024+100
	//  100 0000 0000
	//       110 0100

	printf("ch=%c\n", a1.ch);


	return 0;
}
