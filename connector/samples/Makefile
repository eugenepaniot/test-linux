
obj-m += cn_test.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	gcc ./ucon.c -o ucon.out

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -f ucon.out
