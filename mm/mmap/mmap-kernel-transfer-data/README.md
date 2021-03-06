GitHub: [Repo](https://github.com/paraka/mmap-kernel-transfer-data)

= Transfer data from user space to kernel using char device and mmap =

* Compile:

    $ make
    make -C /lib/modules/3.16.0-38-generic/build M=/home/sergio/devel/mmap-kernel-transfer-data modules
    make[1]: se ingresa al directorio «/usr/src/linux-headers-3.16.0-38-generic»
      CC [M]  /home/sergio/devel/mmap-kernel-transfer-data/mmap-example.o
      Building modules, stage 2.
      MODPOST 1 modules
      CC      /home/sergio/devel/mmap-kernel-transfer-data/mmap-example.mod.o
      LD [M]  /home/sergio/devel/mmap-kernel-transfer-data/mmap-example.ko
    make[1]: se sale del directorio «/usr/src/linux-headers-3.16.0-38-generic»
    $ 

* Insert module into the kernel:

    $ sudo insmod ./mmap-example.ko

* Check kernel log:
 
    $ dmesg | tail -2 
    [176134.953100] sample char device init
    [176134.956291] mmap-example: mmap-test registered with major 250

* Exec test program:

    $ ./test
    Initial message: Hello from kernel this is file: mmap-test
    Changed message: Hello from *user* this is file: mmap-test

* Remove module from the kernel:

    $ sudo rmmod mmap-example

* Check kernel log:

    $ dmesg | tail -1
    [176272.596109] mmap-example: Module exit correctly
