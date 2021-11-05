obj-m:=myfs.o                          #产生first模块的目标文件
CURRENT_PATH:=$(shell pwd)             #模块所在的当前路径
LINUX_KERNEL_PATH:=/lib/modules/`uname -r`/build

all:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules

clean:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean
