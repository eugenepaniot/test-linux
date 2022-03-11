# Rong Tao, 2022-03-11

all: clock_gettime.sec.out clock_gettime.nsec.out

clock_gettime.sec.out:
	make -C dpdk
	gcc clock_gettime.c -DHAVE_DPDK_TSC_FREQ ./dpdk/tsc_freq.o -o $@ -DACCURATE_TO_SEC
clock_gettime.nsec.out:
	make -C dpdk
	gcc clock_gettime.c -DHAVE_DPDK_TSC_FREQ ./dpdk/tsc_freq.o -o $@

clean:
	make -C dpdk clean
	rm -f *.out
