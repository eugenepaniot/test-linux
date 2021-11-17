/**
 *	File register_sysctl.c
 *	Time 2021.11.12
 *	Author	Rong Tao <rongtao@cestc.cn>
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/sysctl.h>

int my_proc_handler(struct ctl_table *tab, int write, void *buffer, 
					size_t *lenp, loff_t *ppos);

#define SYSCTL_ENTRY(name)				\
		{						\
			.procname	= name,			\
			.maxlen		= sizeof(int),		\
			.mode		= 0644,			\
			.proc_handler	= my_proc_handler,	\
			.extra1		= SYSCTL_ZERO,		\
			.extra2		= SYSCTL_INT_MAX,	\
		}

struct ctl_table_header *rongtao_header;
struct ctl_table rongtao = SYSCTL_ENTRY("rongtao");

int my_proc_handler(struct ctl_table *tab, int write, void *buffer, 
					size_t *lenp, loff_t *ppos)
{
	printk("write=%d, buffer=%p\n", write, buffer);

	/**
	 *	TODO 不成功
	 */
	*lenp = sizeof(int);
	*ppos = 0;

	return 0;
}

static int __init my_init(void)
{
	printk("my module is working..\n");

	rongtao_header = register_sysctl("rongtao", &rongtao);

	return 0;
}

static void __exit my_exit(void)
{
	printk("my module is leaving..\n");

	if(rongtao_header) {
		unregister_sysctl_table(rongtao_header);
	}
}

MODULE_LICENSE("GPL");
module_init(my_init);
module_exit(my_exit);
