/**
 *	File ./kprobe_read_tsc.c 
 *	Time 2022.01.10
 *	Author Rong Tao
 *
 *	Discription
 *	  sudo bpftrace -e 'kprobe:read_tsc {printf("read_tsc.\n");}'
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kprobes.h>

#define MAX_SYMBOL_LEN	64
static char symbol[MAX_SYMBOL_LEN] = "read_tsc";
module_param_string(symbol, symbol, sizeof(symbol), 0644);

static unsigned long int count_read_tsc = 0;

static struct kprobe kp = {
	.symbol_name	= symbol,
};

static int __kprobes handler_pre(struct kprobe *p, struct pt_regs *regs)
{
	printk("ICMP ECHO <%s> %ld\n", p->symbol_name, count_read_tsc++);

	return 0;
}

/* kprobe post_handler: called after the probed instruction is executed */
static void __kprobes handler_post(struct kprobe *p, struct pt_regs *regs,
				unsigned long flags)
{
}

static int __init kprobe_init(void)
{
	int ret;
	kp.pre_handler = handler_pre;
	kp.post_handler = handler_post;

	ret = register_kprobe(&kp);
	if (ret < 0) {
		printk("register_kprobe failed, returned %d\n", ret);
		return ret;
	}
	printk("Planted kprobe at %p\n", kp.addr);
	return 0;
}

static void __exit kprobe_exit(void)
{
	unregister_kprobe(&kp);
	printk("kprobe at %p unregistered\n", kp.addr);
}

module_init(kprobe_init)
module_exit(kprobe_exit)
MODULE_LICENSE("GPL");
