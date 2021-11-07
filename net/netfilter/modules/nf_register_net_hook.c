/**
 *	File	nf_register_net_hook
 *	Time	2021.11.07
 *	Author	Rong Tao <rongtao@cestc.cn>
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>

static struct nf_hook_ops netfilter_ops;

unsigned int main_hook(void *priv,
		       struct sk_buff *skb,
		       const struct nf_hook_state *state)
{
    printk(KERN_INFO "PF_INET netfilter hook called.\n");
    return NF_ACCEPT;
}

static int kernel_init(void)
{
    printk(KERN_INFO "my init.\n");
    
    netfilter_ops.hook = main_hook;
    netfilter_ops.pf = PF_INET;
    netfilter_ops.hooknum = 0;
    netfilter_ops.priority = NF_IP_PRI_FIRST;
    
    nf_register_net_hook(&init_net, &netfilter_ops);
    
    return 0;
}

static void kernel_exit(void)
{
    printk(KERN_INFO "my exit.\n");
    nf_unregister_net_hook(&init_net, &netfilter_ops);
}

module_init(kernel_init);
module_exit(kernel_exit);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
