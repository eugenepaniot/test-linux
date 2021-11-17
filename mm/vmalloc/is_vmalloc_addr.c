/**
 *	File is_vmalloc_addr.c
 *	Time 2021.11.17
 *	Author	Rong Tao <rongtao@cestc.cn>
 */
#include <linux/init.h>
#include <linux/module.h>
#include <asm/uaccess.h>
#include <linux/mm.h>
#include <linux/mm_types.h>
#include <linux/sched.h>


static int __init mymem_init(void)
{
	printk("mymem module is working..\n");

	return 0;
}

static void __exit mymem_exit(void)
{
	printk("mymem module is leaving..\n");
}

MODULE_LICENSE("GPL");
module_init(mymem_init);
module_exit(mymem_exit);
