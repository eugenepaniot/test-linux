
obj-m += kprobe_icmp_echo.o
obj-m += kprobe___handle_sysrq.o
#obj-m += kprobe_read_tsc.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
