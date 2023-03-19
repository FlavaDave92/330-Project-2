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

static uid_t uuid;
static int buffSize;
static int prod;
static int cons;

module_param(buffSize, int, 0644);
module_param(prod, int, 0644);
module_param(cons, int, 0644);
module_param(uuid, int, 0644);


sem_t semEmpty;
sem_t semFull;
pthread_mutex_t mutex;


struct task_struct* p;
int prodind = 0;
int prodcount = 0;
struct task_struct* processArray;
int pcount = 0;
int ccount = 0;

int conind = 0;

struct task_struct* task;


int totalNano = 0;



int producer_consumer_init(void)
{
  

    // Dac Le initialize

    sem_init(&semEmpty, 0, buffSize);
    sem_init(&semFull, 0);

    processArray= vmalloc(buffSize*sizeof(struct task_struct));

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

static int producer_thread(void* args)
{

  
    for_each_process(p)
    {
        pthread_mutex_lock(&mutex);
       if(uuid != p->cred->uid.val)
	      {
	       continue;
  	    }
        else{
        
        if (down_interruptible(&semEmpty))
            break;

         if(cons == 0 && buffSize == prodind)  
	          break;
        
        
            pcount++;
            processArray[prodind] = *p;
            prodind = (prodind+1) % buffSize; 
            printk(KERN_INFO "[%s] Produced Item#-%d at buffer index: &d for PID:%d", p->name, count, prodind, p->pid);
        
        // end of something
        pthread_mutex_unlock(&mutex);
        up(&semFull);
    }
    }

       return 0;

}


static int consumer_thread(void* args)
{

  
    while(!kthread_should_stop())
    {
        sem_wait(&semFull);
        pthread_mutex_lock(&mutex);

        if (down_interruptible(&semFull))
            break;


        // do something
            struct task_struct timeproc = processArray[conind];
           long long int nanosecond = ktime_get_ns() - timeproc->start_time;
            totalNano = totalNano + nanosecond;
            int second = nanosecond/1000000000;
            int minute = second/60;
            second %= 60;
            int hour = minute/60;
            minute %= 60;
            ccount++;
            printk(KERN_INFO "[consumer-1] Consumed Item#-%d on buffer index: %d PID:%d Elapsed Time-%d:%d:%d", ccount, conind, timeproc.pid, hours, minutes,seconds );
            conind = (conind+1)%buffSize;

        

        // end of something
        pthread_mutex_unlock(&mutex);
        sem_post(&semEmpty);
    }

     return 0;

}
  
void producer_consumer_exit(void)
{
    down_interruptible(mutex);
    down_interruptible(semEmpty);
    down_interruptible(semFull);
    kthread_stop(struct task_struct *producer);
    kthread_stop(struct task_struct *consumer);
    pthread_mutex_destroy(&mutex);
    sem_destroy(&semEmpty);
    sem_destroy(&semFull);
    int second = totalNano/1000000000;
    int minute = second/60        
    second %= 60;
    int hour = minute/60;
    minute %= 60;
    printk(KERN_INFO "The total elapsed time of all processes for UID %d is", uuid);
    printk(KERN_INFO "%d:%d:%d", hour, minute, second);
    vfree(processArray);
}

module_init(producer_consumer_init);
module_exit(producer_consumer_exit);
MODULE_LICENSE("GPL");