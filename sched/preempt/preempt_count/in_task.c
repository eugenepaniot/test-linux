#include <linux/module.h>
#include <linux/preempt.h>
#include <linux/kernel.h>

static int test_init(void)
{
	printk(KERN_INFO "in_task = %d\n", in_task());
	return 0;
}

static void test_exit(void)
{
	printk(KERN_INFO "bye.\n");
}

module_init(test_init);
module_exit(test_exit);

MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
