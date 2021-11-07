/**
 *	File	nf_register_net_hook
 *	Time	2021.11.07
 *	Author	Rong Tao <rongtao@cestc.cn>
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>

static int kernel_init(void)
{
    printk(KERN_INFO "mykthread init.\n");
    return 0;
}

static void kernel_exit(void)
{

}

module_init(kernel_init);
module_exit(kernel_exit);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
