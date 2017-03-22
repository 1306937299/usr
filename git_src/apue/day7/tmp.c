#include <stdio.h>

void func()
{
	static int a = 10;
	a++;
	printf("a=%d\n", a);
}

int main()
{

	func();
	func();
	func();
	func();
	func();




	return 0;
}
