vDSO - Virtual Dynamic Shared Object
===============

VDSO就是`Virtual Dynamic Shared Object`，就是内核提供的虚拟的.so,这个.so文件不在磁盘上，而是在内核里头。内核把包含某.so的内存页在程序启动的时候映射入其内存空间，对应的程序就可以当普通的.so来使用里头的函数。比如syscall()这个函数就是在`linux-vdso.so.1`里头的，但是磁盘上并没有对应的文件.可以通过ldd/bin/bash看看。

Linux下传统的系统调用是通过软中断(0x80)实现的,采用传统的int 0x80的系统调用浪费了很多时间,而sysenter/sysexit可以弥补这个缺点，所以才最终决定在linux内核中用后替换前者（最终在2.6版本的内核中才加入了此功能，即采用sysenter/sysexit）。

如何用替换sysenter/sysexit替换以前的int 0x80呢？

linux kenerl 需要考虑到这点：有的机器并不支持sysenter/sysexit，于是它跟glibc说好了，“你以后调用系统调用的时候就从我给你的这个地址调用，这个地址指向的内容要么是int 0x80调用方式，要么是sysenter/sysexit调用方式，我会根据机器来选择其中一个”（kernel与glibc的配合是如此的默契），这个地址便是vsyscall的首地址。

可以将`vdso`看成一个shared objdect file（这个文件实际上不存在）,内核将其映射到某个地址空间，被所有程序所共享。（我觉得这里用到了一个技术：多个虚拟页面映射到同一个物理页面。即内核把vdso映射到某个物理页面上，然后所有程序都会有一个页表项指向它，以此来共享，这样每个程序的vdso地址就可以不相同了）


