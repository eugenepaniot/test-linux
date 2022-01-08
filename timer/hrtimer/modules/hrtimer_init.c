/**
 *	File: hrtimer_init.c
 *	Author: Rong Tao <rongtao@cestc.cn>
 *	Create at: 2022-01-08
 *
 *	Refs:
 *	1. https://stackoverflow.com/questions/13214197/hrtimer-repeating-task-in-the-linux-kernel
 *
 */
#include <linux/module.h>
#include <linux/hrtimer.h>
#include <linux/kernel.h>
#include <linux/ktime.h>

static struct hrtimer timer;
s64 i64TimeInNsec = 500 * NSEC_PER_MSEC;
enum hrtimer_restart enHRTimer=HRTIMER_NORESTART;

/**
 *	
 */
static enum hrtimer_restart timer_callback(struct hrtimer *timer)
{
    printk(KERN_ERR "Callback\n");
    //I know something needs to go here to reset the timer
	hrtimer_forward(timer, hrtimer_cb_get_time(timer),
				ktime_set(0, i64TimeInNsec));
    return enHRTimer;
}

static int init_timer(void)
{   
    ktime_t ktime;

	enHRTimer = HRTIMER_RESTART;
    printk(KERN_ERR "Timer being set up\n");

    ktime = ktime_set(0, i64TimeInNsec);
    hrtimer_init(&timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	hrtimer_set_expires(&timer, ktime);
    timer.function = &timer_callback;
    printk(KERN_ERR "Timer starting to fire\n");
    printk(KERN_ERR "in %lldms %ld\n", i64TimeInNsec/NSEC_PER_MSEC,  jiffies);

    hrtimer_start(&timer, ktime, HRTIMER_MODE_REL);
    return 0;
}

static void clean_load_balancing_timer(void)
{
    int cancelled = hrtimer_cancel(&timer);
	enHRTimer = HRTIMER_NORESTART;
    if (cancelled)
        printk(KERN_ERR "Timer still running\n");
    else
        printk(KERN_ERR "Timer cancelled\n");
}

module_init(init_timer);
module_exit(clean_load_balancing_timer);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
