#include <stdio.h>
#include <string.h>

char* const test()
{
	return "Hello";
}

int main(void)
{
	char p[10] = test();
	printf("%s", p);

	return 0;
}
