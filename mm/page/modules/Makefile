obj-m += alloc_page.o
obj-m += dump_page.o
obj-m += my_zero_pfn.o
obj-m += test_free_pages.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
