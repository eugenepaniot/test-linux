#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h> 

char tasklet_data[] = "Using a string but it could easily be struct pointer\n";

/* Tasklet handler, just prints data held in the tasklet */
void tasklet_work(struct tasklet_struct *tasklet)
{
	printk("%s\n", (char *) tasklet->data);
}

DECLARE_TASKLET(my_tasklet, tasklet_work);

static int __init onload(void)
{
	my_tasklet.data = (unsigned long)tasklet_data;
	tasklet_schedule(&my_tasklet);
	return 0;
}

void onunload(void)
{
	tasklet_kill(&my_tasklet);
}

module_init(onload);
module_exit(onunload);
MODULE_AUTHOR("Liam Ryan <liamryandev@gmail.com>");
MODULE_LICENSE("GPL");
