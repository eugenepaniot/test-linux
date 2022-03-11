/**
 * 编写一个能够唤醒 kswapd 进程的用户代码
 * TODO: 目前不成功
 */
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

int main()
{
	int i;
	char *p;
	int pagesize = getpagesize();

	mlockall(0);
	
	for (;;) {
		p = mmap(NULL, pagesize*10, PROT_READ|PROT_WRITE,
				MAP_ANON|MAP_SHARED, -1, 0);
		if (p == MAP_FAILED) {
			perror("mmap");
			continue;
		}
		for (i = 0; i < 10; i += pagesize) {
			p[i] = 'A';
		}
	}
	return 0;
}
