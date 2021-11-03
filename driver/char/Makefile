obj-m += chardev0.o
obj-m += chardev1.o

KERNEL_DIR=/lib/modules/`uname -r`/build
MODULE_DIR := $(shell pwd)

all:
	make -C $(KERNEL_DIR) M=$(MODULE_DIR) modules
clean:
	make -C $(KERNEL_DIR) M=$(MODULE_DIR) clean
	rm -f chardev1_usertest.out
test:
	gcc ./chardev1_usertest.c -o chardev1_usertest.out
