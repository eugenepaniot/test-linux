obj-m = red_tasklet.o

KERNEL_VER = $(shell uname -r)

all:
	make -C /lib/modules/$(KERNEL_VER)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(KERNEL_VER)/build M=$(PWD) clean
