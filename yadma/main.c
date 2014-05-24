
#include <stdio.h>
#include <stdlib.h>

int show_abc(int a, int b, int c)
{
	printf("abc=%d,%d,%d", a, b, c);
}
int main(int argc, char **argv)
{	
	int i; 
	printf("step 1\n");
	i = 1;
	printf("i=%d\n", i);
	
	show_abc(1,2,3);
	i = 22;
	printf("i=%d\n", i);

	i = 3;
	printf("i=%d\n", i);
	return 0;
}

