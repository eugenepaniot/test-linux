obj-m += workqueue-template.o
obj-m += workqueue1.o
obj-m += workqueue2.o
obj-m += workqueue3-hd.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD	:= $(shell pwd)

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
