/**
 *	File tasklet-bh.c 
 *	Time 2021.11.03
 *	Author Rong Tao <rongtao@cestc.cn>
 */
#include <linux/module.h>    // included for all kernel modules
#include <linux/kernel.h>    // included for KERN_INFO
#include <linux/init.h>      // included for __init and __exit macros
#include <linux/interrupt.h> // included for request_irq and free_irq macros
#include <linux/preempt.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rong Tao");
MODULE_DESCRIPTION("A Simple request irq module");
MODULE_VERSION("0.1");

static int irqnum = 2;
module_param(irqnum, int, 0644);
MODULE_PARM_DESC(irqnum, "irq number, acpi is OK");

static char *name = "tasklet-bh";
module_param( name, charp, S_IRUGO);
MODULE_PARM_DESC(name, "irq name");	

struct myirq {
	int devid;
};
struct myirq mydev = {1119};
static struct tasklet_struct mytasklet;

static void print_irq_status(char *prefix)
{
	printk(KERN_INFO "%20s in_task       = %d\n", prefix, in_task());
	printk(KERN_INFO "%20s in_irq        = %ld\n", prefix, in_irq());
	printk(KERN_INFO "%20s in_hardirq    = %ld\n", prefix, in_hardirq());
	printk(KERN_INFO "%20s in_softirq    = %ld\n", prefix, in_softirq());
	printk(KERN_INFO "%20s in_interrupt  = %ld\n", prefix, in_interrupt());
	printk(KERN_INFO "%20s softirq_count = %ld\n", prefix, softirq_count());
	printk(KERN_INFO "%20s hardirq_count = %ld\n", prefix, hardirq_count());
	printk(KERN_INFO "%20s irq_count     = %ld\n", prefix, irq_count());
}

static void mytasklet_handler(unsigned long data)
{
	print_irq_status("tasklet handler: ");
}

irqreturn_t no_action(int cpl, void *dev_id)
{
    printk(KERN_INFO "irq line number is %d!\n", cpl);
	print_irq_status("irq top half: ");

	tasklet_init(&mytasklet, mytasklet_handler, 0);
	tasklet_schedule(&mytasklet);
	return IRQ_HANDLED;
}

static int __init rtoax_irq_init(void)
{
    
	printk(KERN_INFO "request irq %s!\n", name);
    if (request_irq(irqnum, no_action, IRQF_SHARED, name, &mydev) != 0) {
	    printk(KERN_ERR "%s: request_irq() failed\n", name);
		return -1;
	}
	return 0;
}

static void __exit rtoax_irq_cleanup(void)
{
	printk(KERN_INFO "free irq.\n");
    free_irq(irqnum, &mydev);
	tasklet_kill(&mytasklet);
}

module_init(rtoax_irq_init);
module_exit(rtoax_irq_cleanup);
