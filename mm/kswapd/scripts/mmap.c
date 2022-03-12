/**
 * 编写一个能够唤醒 kswapd 进程的用户代码
 * TODO: 目前不成功
 */
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/resource.h>

unsigned long Nsuccess = 0, Nfailed = 0;

void sig_handler(int signum)
{
	switch (signum) {
	case SIGALRM:
		printf("Success: %ld\n", Nsuccess);
		printf("Failed: %ld\n", Nfailed);
		alarm(1);
		break;
	default:
		break;
	}
}

int main()
{
	int i;
	char *p;
	int pagesize = getpagesize();
	struct rlimit limit;

	signal(SIGALRM, sig_handler);

	limit.rlim_cur = 1024*1024*1024;
	limit.rlim_max = 1024*1024*1024;
	prlimit(getpid(), RLIMIT_MEMLOCK, &limit, NULL);
	mlockall(0);
	alarm(1);

	for (;;) {
#if 1
		p = mmap(NULL, pagesize*1024, PROT_READ|PROT_WRITE,
				MAP_ANON|MAP_SHARED, -1, 0);
		if (p == MAP_FAILED) {
			//perror("mmap");
			Nfailed++;
			continue;
		}
		Nsuccess++;
		for (i = 0; i < 1024; i += pagesize) {
			p[i] = 'A';
		}
#endif
	}
	return 0;
}
