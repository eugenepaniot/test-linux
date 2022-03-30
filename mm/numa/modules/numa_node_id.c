/**
 *	File	numa_node_id.c
 *	Time	2022-03-30
 *	Author	Rong Tao <rongtao@cestc.cn>
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/mmzone.h>

static int kernel_init(void)
{
	printk(KERN_INFO "numa_node_id %d\n", numa_node_id());

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
