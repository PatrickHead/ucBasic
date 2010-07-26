#include <stdio.h>

int main(int argc, char **argv)
{
	int i;

	i = 1;

again:
	printf("%d\n", i);
	i = i + 1;
	if (i < 100000000) goto again;

	return;
}
