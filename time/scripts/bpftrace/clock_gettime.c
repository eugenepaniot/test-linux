#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <sys/syscall.h>

#define MAX	(1000 * 1000 * 100)
#define longtime(ts)	((ts).tv_sec * 1000000000ULL + (ts).tv_nsec)

long sys_clock_gettime(clockid_t clockid, struct timespec *tp)
{
	return syscall(__NR_clock_gettime, clockid, tp);
}

void func(int cnt)
{
	struct timespec ts;
	int x;

	for (x = 0; x < cnt; x++)
	{
		sys_clock_gettime(CLOCK_REALTIME, &ts);
		/**
		 * Use bpftrace tracing clock_getime, need this
		 */
		usleep(1);
	}
}

int main(int argc, char *argv[])
{
	struct timespec start, end;
	unsigned long long diff_ns;

	clock_gettime(CLOCK_MONOTONIC, &start);
	func(MAX);
	clock_gettime(CLOCK_MONOTONIC, &end);
	
	diff_ns = longtime(end) - longtime(start);

	printf("diff %lld, (%llf nspc)\n", diff_ns, diff_ns*1.0L / MAX);

	return 0;
}


