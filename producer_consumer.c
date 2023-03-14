#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/semaphore.h>
#include <linux/kthread.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/ktime.h>
#include <linux/time.h>
#include <linux/timer.h>
#include <linux/slab.h>

static int __init producer_consumer(int buffSize, int prod, int cons, int uuid)
{

    printk(KERN_INFO "Hello world\n");
    return 0;
}
  
static void __exit hello_end(void)
{
    printk(KERN_INFO "Goodbye Mr.\n");
}
