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
pthread_mutex_t mutexBuffer;

task_struct *task;

int producer_consumer_init(int buffSize, int prod, int cons, int uuid)
{
    module_param(uid, buff_size, p, c) #uid is user uid, buffer size, total # of producer threads, total # of consumer threads
    printk(KERN_INFO "Hello world\n");

    // Dac Le initialize
    pthread_t thread[prod + cons];
    pthread_mutex_init(&mutexBuffer, NULL);
    sem_init(&semEmpty, 0, buffSize);
    sem_init(&semFull, 0, 0);

    if (kthread_run(&thread[0], NULL, &producer_thread, NULL) != 0)
    {
        printk("Failed to create producer thread");
    }

    for (int i = 0; i < cons; ++i)
        if (kthread_run(&thread[0], NULL, &consumer_thread, NULL) != 0)
        {
            printk("Failed to create consumer thread");
        }


    sem_destroy(&semEmpty);
    sem_destroy(&semFull);
    //pthread_mutex_destroy(&mutexBuffer);
    kthread_stop(&mutexBuffer);

    return 0;
}

void* producer_thread(void* args)
{
    while(1)
    {
        // Produce
        sem_wait(&semEmpty);
        pthread_mutex_lock(&mutexBuffer);
        // do something

        // end of something
        pthread_mutex_unlock(&mutexBuffer);
        sem_post(&semFull);
    }
}


void* consumer_thread(void* args)
{
    while(1)
    {
        sem_wait(&semFull);
        pthread_mutex_lock(&mutexBuffer);
        // do something

        // end of something
        pthread_mutex_unlock(&semEmpty);
        sem_post(&semEmpty);
    }
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