obj-m += netlink_kernel.o
obj-m += netlink_kernel2.o
CURRENT_PATH:=$(shell pwd)
LINUX_KERNEL:=$(shell uname -r)
LINUX_KERNEL_PATH:=/lib/modules/`uname -r`/build

all:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules

user:
	gcc netlink_user2.c -o netlink_user2 -g
	gcc netlink_user3.c -o netlink_user3 -g
	gcc netlink_user.c -o netlink_user -g

clean:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean
	rm  -rf netlink_user netlink_user2 netlink_user3
