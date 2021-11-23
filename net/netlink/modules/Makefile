obj-m += netlink_kernel.o
obj-m += netlink_kernel2.o
CURRENT_PATH:=$(shell pwd)
LINUX_KERNEL:=$(shell uname -r)
LINUX_KERNEL_PATH:=/lib/modules/`uname -r`/build

all:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules

client:
	gcc netlink_client2.c -o netlink_client2 -g
	gcc netlink_client3.c -o netlink_client3 -g
	gcc netlink_client.c -o netlink_client -g

clean:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean
	rm  -rf netlink_client netlink_client2 netlink_client3
