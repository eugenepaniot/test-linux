/**
 *	File listtasks.c
 *	Time 2021.11.03
 *	Author	Rong Tao <rongtao@cestc.cn> modify from Slava Imameev
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/rcupdate.h>
#include <linux/init_task.h>
#include <linux/version.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rong Tao");

const char* state_to_string(long state)
{
	switch (state)
	{
		case TASK_RUNNING: return "rinning";
		case TASK_INTERRUPTIBLE: return "irqable";
		case TASK_UNINTERRUPTIBLE: return "unirqable";
		case __TASK_STOPPED: return "stoped";
		case __TASK_TRACED: return "traced";
		case TASK_DEAD: return "dead";
		case TASK_WAKEKILL: return "wakekill";
		case TASK_WAKING: return "waking";
		case TASK_PARKED: return "parked";
		case TASK_NOLOAD: return "noload";
		default: return "UNKNOWN";
	}
}

void list_from_task(struct task_struct *task)
{
	/**
	 * tasklist_lock is not exported anymore, use RCU as p->tasks 
	 * is updated wth list_add_tail_rcu(), see copy_process(),
	 * you can use list_for_each_entry_rcu() instead the explicit 
	 * RCU list traversing code below
	 */
	rcu_read_lock();
	{
		struct task_struct* p = task;
        
        printk(KERN_INFO "%-17s %-6s %-6s %-3s %-4s %-4s %-20s\n", 
                        "Name", "PID", "TGID", "Pri","PriS","PriN", "State");
		do
		{
			struct list_head*  next;
#if LINUX_VERSION_CODE < KERNEL_VERSION(5, 14, 0)
			long               state = p->state;
#else
			long               state = p->__state;
#endif
			printk(KERN_INFO "%-17s %-6d %-6d %-3d %-4d %-4d %-2ld(-%9s)\n", 
                                p->comm, p->pid, p->tgid,
                                p->prio, p->static_prio, p->normal_prio, 
                                state, state_to_string(state));

			next = rcu_dereference(p->tasks.next);
			p = list_entry(next, struct task_struct, tasks);
		} while (p != task);
	}
	rcu_read_unlock();
}

void list_tasks(void)
{
	list_from_task(&init_task);
}

static int __init listtask_init(void)
{
	printk(KERN_INFO "Hi from init\n");

	list_tasks();

	return 0;
}

static void __exit listtask_exit(void)
{
	printk(KERN_INFO "Bye!\n");
}

module_init(listtask_init)
module_exit(listtask_exit)
