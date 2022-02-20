#include <stdio.h>
#include <sys/auxv.h>

int main(int argc, char *argv[])
{
	void *vdso = (uintptr_t) getauxval(AT_SYSINFO_EHDR);
	printf("AT_SYSINFO_EHDR %p\n", vdso);
	return 0;
}
