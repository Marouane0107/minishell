

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int	main(void)
{
	int i = open("test.txt", O_RDWR | O_CREAT | O_TRUNC , 0666);
	printf("%d\n", i);
	close(i);
}