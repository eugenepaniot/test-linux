/**
 *	test page walk
 *	
 *	Author	Rong Tao <rongtao@cestc.cn>
 *	Time	2021.11.05
 */

#include <linux/pagewalk.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init.h>

static int pte_hole(unsigned long start, unsigned long end,
		    __always_unused int depth, struct mm_walk *walk)
{
	printk("PTE: %lx-%lx.\n", start, end);
	return 0;
}

static const struct mm_walk_ops pagewalktest_ops = {
//	.pmd_entry	= pmd_range,
	.pte_hole	= pte_hole,
};

static int __init pagewalktest_init(void)
{
	printk("pagewalktest_init.\n");

	struct task_struct *this_task = current;

	/**
	 *	Undefined, can't use in module/driver
	 */
	walk_page_range(this_task->mm, 0, 0, &pagewalktest_ops, NULL);

	return 0;
}

static void __exit pagewalktest_exit(void)
{
	printk("pagewalktest_exit.\n");
}

module_init(pagewalktest_init);
module_exit(pagewalktest_exit);

MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
