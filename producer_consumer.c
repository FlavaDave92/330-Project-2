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

#define BUFFER_SIZE 10
#define CONSUMER_THREAD 3
sem_t semEmpty;
sem_t semFull;
int totalNano

task_struct *task;

int producer_consumer_init(int buffSize, int prod, int cons, int uuid)
{
    module_param(buffSize, prod, cons, uuid) #uid is user uid, buffer size, total # of producer threads, total # of consumer threads
    printk(KERN_INFO "Hello world\n");

    // Dac Le initialize

    sem_init(&semEmpty, 0, buffSize);
    sem_init(&semFull, 0, 0);

    if (kthread_run(producer_thread, NULL, "Producer-1") != 0)
    {
        printk("Failed to create producer thread");
    }

    if (kthread_run(consumer_thread, NULL, "Consumer-1") != 0)
    {
        printk("Failed to create consumer thread");
    }


    sem_destroy(&semEmpty);
    sem_destroy(&semFull);
    return 0;
}

void* producer_thread(void* args)
{
    while(!kthread_should_stop())
    {
        // Produce
        sem_wait(&semEmpty);
        
        if (down_interruptible(&semEmpty))
            break;
        // do something
        struct task_struct* p;
        for_each_process(p)
        {
            printk(KERN_INFO "[%s] Produced Item#-%d at buffer index: &d for PID:%d", p->name, p->item, p->index, p->pid);
        }
        // end of something
        pthread_mutex_unlock(&mutexBuffer);
        sem_post(&semFull);
    }
}


void* consumer_thread(void* args)
{
    while(!kthread_should_stop())
    {
        sem_wait(&semFull);
        //pthread_mutex_lock(&mutexBuffer);

        if (down_interruptible(&semFull))
            break;


        // do something
        struct task_struct* p;
        for_each_process(p)
        {
            int nanosecond = ktime_get_ns() - p->start_time;
            totalNano = totalNano + nanosecond;
            int second = nanosecond/1000000000;
            int minute = second/60;
            second %= 60;
            int hour = minute/60;
            minute %= 60;
            printk(KERN_INFO "[%s] Consumed Item#-%d on buffer index: %d PID:%d Elapsed Time-%d:%d:%d");
        }
        // end of something
        //pthread_mutex_unlock(&semEmpty);
        sem_post(&semEmpty);
    }
}
  
void producer_consumer_exit(void)
{
    down_interruptible(mutex);
    down_interruptible(semEmpty);
    down_interruptible(semFull);
    kthread_stop(struct task_struct *producer);
    kthread_stop(struct task_struct *consumer);
    int second = totalNano/1000000000;
    int minute = second/60        
    second %= 60;
    int hour = minute/60;
    minute %= 60;
    printk(KERN_INFO "The total elapsed time of all processes for UID %d is", uuid);
    printk(KERN_INFO "%d:%d:%d", hour, minute, second);
}

module_init(producer_consumer_init);
module_exit(producer_consumer_exit);
MODULE_LICENSE("GPL");
