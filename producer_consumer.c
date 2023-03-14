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

int producer_consumer_init(int buffSize, int prod, int cons, int uuid)
{
    module_param(uid, buff_size, p, c) #uid is user uid, buffer size, total # of producer threads, total # of consumer threads
    printk(KERN_INFO "Hello world\n");
    return 0;
}
  
void producer_consumer_exit(void)
{
    down_interruptible(mutex);
    down_interruptible();
    down_interruptible();
    kthread_stop(struct task_struct *producer);
    kthread_stop(struct task_struct *consumer);
    printk(KERN_INFO "The total elapsed time of all processes for UID %d is", uuid);
    printk(KERN_INFO "%d:%d:%d", hours, minutes, seconds);
}

module_init(producer_consumer_init);
module_exit(producer_consumer_exit);
MODULE_LICENSE("GPL");
