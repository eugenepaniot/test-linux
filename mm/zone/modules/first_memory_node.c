/**
 *	File	first_memory_node.c
 *	Time	2021.11.10
 *	Author	Rong Tao <rongtao@cestc.cn>
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/mmzone.h>

static int kernel_init(void)
{
    printk(KERN_INFO "my init.\n");

	printk(KERN_INFO "First memory node %d\n", first_memory_node);

    return 0;
}

static void kernel_exit(void)
{
	printk(KERN_INFO "my exit.\n");
}

module_init(kernel_init);
module_exit(kernel_exit);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
