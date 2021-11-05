/**
 *	File ./get_unmapped_area.c 
 *	Time 2021.11.05
 *	Author	Rong Tao <rongtao@cestc.cn>
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/mm.h>
#include <linux/mm_types.h>

static void test__get_unmapped_area(void)
{
	unsigned long addr;
	addr = get_unmapped_area(NULL, 0, PAGE_SIZE, 0, 0);
	if(!addr) {
		printk(KERN_ERR "can't get unmapped area.\n");
	}
	printk(KERN_INFO "get_unmapped_area = 0x%lx\n", addr);
}

static int __init mymem_init(void)
{
	printk("mymem module is working..\n");

	test__get_unmapped_area();

	return 0;
}

static void __exit mymem_exit(void)
{
	printk("mymem module is leaving..\n");
}

MODULE_LICENSE("GPL");
module_init(mymem_init);
module_exit(mymem_exit);
