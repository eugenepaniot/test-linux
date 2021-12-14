/**
 *	File ./kprobe_icmp_echo.c 
 *	Time 2021.12.14
 *	Author Rong Tao
 *
 *	Discription
 *	  sudo bpftrace -e 'kprobe:icmp_echo {printf("ICMP ECHO.\n");}'
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kprobes.h>

#define MAX_SYMBOL_LEN	64
static char symbol[MAX_SYMBOL_LEN] = "icmp_echo";
module_param_string(symbol, symbol, sizeof(symbol), 0644);

static unsigned long int count_icmp_echo = 0;

static struct kprobe kp = {
	.symbol_name	= symbol,
};

static int __kprobes handler_pre(struct kprobe *p, struct pt_regs *regs)
{
	printk("ICMP ECHO <%s> %ld\n", p->symbol_name, count_icmp_echo++);

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
