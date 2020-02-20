#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

int fd;

int main()
{
	printf("Hello, World!\n");
	fd = open("/dev/mygpio",O_RDWR);
	if (fd < 0)
	{
	    printf("can't open device\n");
	    return 0;
	}
	sleep(5);
	close(fd);
	return 0;
}
