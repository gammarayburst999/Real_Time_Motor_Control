#include <linux/module.h>
#include <asm/io.h>
#include <linux/init.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
//#include <math.h>
#include <rtai.h>

#include <rtai_sched.h>

#include <rtai_fifos.h> 


#define ARG 0
#define USE_FPU 1
#define NOW rt_get_time()
#define PERIOD nano2count(1e9)
#define SIZE 1000

#define TICK_PERIOD 1000000000
#define TASK_PRIORITY 1
#define STACK_SIZE 10000
#define FIFO 0
 

static RT_TASK rt_task;


static void task(int t)
{
    int counter = 0;
	printk("\n CODE START \n");
    while (1) 
    {
        rtf_put(FIFO, &counter, sizeof(counter));    
        counter++;         
        printk("RT count = %d \n", counter);
        //rt_sleep(1);
        rt_task_wait_period();
        
    }
}

int init_module(void)
{
    RTIME tick_period;
    rt_set_periodic_mode();

    rt_task_init(&rt_task, task, ARG, STACK_SIZE, TASK_PRIORITY, USE_FPU, 0);
    rtf_create(FIFO, 8000);

    tick_period = start_rt_timer(nano2count(TICK_PERIOD));
    rt_task_make_periodic(&rt_task, rt_get_time() + tick_period, tick_period);
    printk("RT count = %d......%d \n", rt_get_time() + tick_period, tick_period);

    return 0;

}

void cleanup_module(void)
{
    stop_rt_timer();
    rtf_destroy(FIFO);
    rt_task_delete(&rt_task);

    return;
}

 
