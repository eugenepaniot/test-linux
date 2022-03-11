/**
 * File: clock_gettime.c
 * Discription: Compare the latency of vDSO, syscall, etc.
 *
 * Author:	Ge Changzhong (gechangzhong@cestc.cn)
 *			Rong Tao (rongtao@cestc.cn)
 * Time: 2022-03-11
 *
 * syscall, vDSO, rdtsc compare.
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <sys/syscall.h>

#define MAX	(1000 * 1000 * 100)
#define longtime(ts)	((ts).tv_sec * 1000000000ULL + (ts).tv_nsec)

typedef enum {
	TEST_SYSCALL,
	TEST_VSYSCALL,
	TEST_VDSO,
#if defined(__x86_64__)
	TEST_RDTSC,
#endif
} test_enum;

#if defined(__x86_64__)
static inline uint64_t __rdtsc(void)
{
   unsigned int a, d;
   asm volatile ("rdtsc" : "=a" (a), "=d"(d));
   return ((unsigned long) a) | (((unsigned long) d) << 32);
}

int rdtsc_clock_gettime(clockid_t clockid, struct timespec *tp)
{
	uint64_t tsc = __rdtsc();

	/**
	 * TODO: 注意，这里需要进一步计算才能获取 timespec
	 */

	return tsc;
}
#endif

/* 使用系统调用 */
int sys_clock_gettime(clockid_t clockid, struct timespec *tp)
{
	return syscall(__NR_clock_gettime, clockid, tp);
}

/* 系统默认使用 vDSO, 无需单独实现 clock_gettime() 接口 */

void func(int cnt, test_enum te)
{
	struct timespec ts;
	int x;

	int (*test_clock_gettime)(clockid_t, struct timespec *) = NULL;

	switch (te) {
	case TEST_VDSO:
		test_clock_gettime = clock_gettime;
		break;
	case TEST_SYSCALL:
		test_clock_gettime = sys_clock_gettime;
		break;
#if defined(__x86_64__)
	case TEST_RDTSC:
		test_clock_gettime = rdtsc_clock_gettime;
		break;
#endif
	case TEST_VSYSCALL:
	default:
		assert(0 && "Not support.");
		break;
	}

	for (x = 0; x < cnt; x++) {
		/**
		 * See vsyscall/vdso relate content
		 */
		test_clock_gettime(CLOCK_REALTIME, &ts);
		/**
		 * Use bpftrace tracing clock_getime, need this
		 */
		//usleep(1);
	}
}

void usage(int argc, char **argv)
{
	printf("Usage: %s [syscall|vdso"
#if defined(__x86_64__)
		"|rdtsc"
#endif
		"]\n", argv[0]);
}

int main(int argc, char *argv[])
{
	struct timespec start, end;
	unsigned long long diff_ns;
	test_enum te = TEST_SYSCALL;

	if (argc < 2) {
		usage(argc, argv);
		exit(1);
	}

	if (!strcmp(argv[1], "vdso")) {
		te = TEST_VDSO;
	} else if (!strcmp(argv[1], "syscall")) {
		te = TEST_SYSCALL;
#if defined(__x86_64__)
	} else if (!strcmp(argv[1], "rdtsc")) {
		te = TEST_RDTSC;
#endif
	} else {
		usage(argc, argv);
		exit(1);
	}

	clock_gettime(CLOCK_MONOTONIC, &start);
	func(MAX, te);
	clock_gettime(CLOCK_MONOTONIC, &end);
	
	diff_ns = longtime(end) - longtime(start);

	printf("diff %lld, (%llf nspc)\n", diff_ns, diff_ns*1.0L / MAX);

	return 0;
}


