#include <stdio.h>

char arr[10][10] = {0};

void print()
{
	int i, j;
	for ( i=0; i<10; i++) {
		for (j=0; j<10; j++) {
			write(1, &arr[i][j], 1);
		}
		write(1, "\n", 1);
	}
}

int main()
{
	memset(arr, ' ', 100);
	arr[4][4] = '*';
	arr[4][5] = '*';
	arr[5][4] = '*';
	arr[5][5] = '*';


	while (1) {
		system("clear");
		print();		
		getchar();
	}

	return 0;
}

