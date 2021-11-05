obj-m += chardev0.o
obj-m += chardev1.o
obj-m += chardev2.o
obj-m += chardev3.o
obj-m += chardev4.o

KERNEL_DIR=/lib/modules/`uname -r`/build
MODULE_DIR := $(shell pwd)

all:
	make -C $(KERNEL_DIR) M=$(MODULE_DIR) modules
clean:
	make -C $(KERNEL_DIR) M=$(MODULE_DIR) clean
	rm -f chardev1_usertest.out \
		chardev2_usertest.out \
		chardev3_usertest.out \
		chardev4_usertest.out
test:
	gcc ./chardev1_usertest.c -o chardev1_usertest.out
	gcc ./chardev2_usertest.c -o chardev2_usertest.out
	gcc ./chardev3_usertest.c -o chardev3_usertest.out
	gcc ./chardev4_usertest.c -o chardev4_usertest.out
