
obj-m += nr_softirqs.o
obj-m += show_softirqs.o
obj-m += softirq_count.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
