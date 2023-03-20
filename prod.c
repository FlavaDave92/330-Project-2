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
#include <linux/vmalloc.h>

static uid_t uuid;
static int buffSize;
static int prod;
static int cons;

module_param(buffSize, int, 0644);
module_param(prod, int, 0644);
module_param(cons, int, 0644);
module_param(uuid, int, 0644);

struct semaphore empty;
struct semaphore full;
struct semaphore mutex;
struct task_struct* producerThread;
struct task_struct* consumerThread;
struct task_struct* p;
struct task_struct* processArray;
struct task_struct* task;
struct task_struct timeProc;

int second = 0;
int hour = 0;
int minute = 0;
int prodInd = 0;
int prodCount = 0;
int pCount = 0;
int cCount = 0;
int conInd = 0;

long long int nanosecond = 0;
long long int totalNano = 0;

static int producer_thread(void* args)
{
    for_each_process(p)
    {
   	if(uuid != p->cred->uid.val) {
	       continue;
   	}
        else{
        
        	if (down_interruptible(&empty) || down_interruptible(&mutex)) {
        		break;
		}
		if(cons == 0 && buffSize == prodInd) {
			break;
		}
        	pCount++;
        	processArray[prodInd] = *p;
       		prodInd = (prodInd+1) % buffSize; 
        	printk("[%s] Produced Item#-%d at buffer index: %d for PID:%d",p->comm, pCount, prodInd, p->pid);
        
        // end of something
        	up(&mutex);
        	up(&full);
    	}
    }

       return 0;

}


static int consumer_thread(void* args)
{

  
    while(!kthread_should_stop())
    {

        if (down_interruptible(&full) || down_interruptible(&mutex)) {
            break;
	}


        // do something
        timeProc = processArray[conInd];
        nanosecond = ktime_get_ns() - timeProc.start_time;
        totalNano = totalNano + nanosecond;
        second = nanosecond / 1000000000;
        minute = second / 60;
        second = second % 60;
        hour = minute / 60;
        minute = minute % 60;
        cCount++;
        printk("[%s] Consumed Item#-%d on buffer index: %d PID:%d Elapsed Time-%d:%d:%d", timeProc.comm cCount, conInd, timeProc.pid, hour, minute,second);
        conInd = (conInd+1)%buffSize;

        

        // end of something
        up(&mutex);
        up(&empty);
    }

     return 0;

}

int producer_consumer_init(void)
{
  

    // Dac Le initialize

    sema_init(&empty, buffSize);
    sema_init(&full, 0);
    sema_init(&mutex, 1);

    processArray= vmalloc(buffSize*sizeof(struct task_struct));
    if(prod > 0)
    {
      producerThread = kthread_run(producer_thread, NULL, "producer-1");
      if(cons > 0)
	{
	   consumerThread = kthread_run(consumer_thread, NULL, "consumer-1");
	}
    }
	
    return 0;
}
  
void producer_consumer_exit(void)
{   
    second = totalNano/ 1000000000;
    minute = second / 60;
    second = second % 60;
    hour = minute / 60;
    minute = minute % 60;
    printk(KERN_INFO "The total elapsed time of all processes for UID %d is %d:%d:%d\n", uuid, hour, minute, second);
    vfree(processArray);
}

module_init(producer_consumer_init);
module_exit(producer_consumer_exit);
MODULE_LICENSE("GPL");
