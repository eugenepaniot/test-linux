obj-m += test_klp_atomic_replace.o
obj-m += test_klp_callbacks_busy.o
obj-m += test_klp_callbacks_demo2.o
obj-m += test_klp_callbacks_demo.o
obj-m += test_klp_callbacks_mod.o
obj-m += test_klp_livepatch.o
obj-m += test_klp_shadow_vars.o
obj-m += test_klp_state2.o
obj-m += test_klp_state3.o
obj-m += test_klp_state.o

all:
		make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
		make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
