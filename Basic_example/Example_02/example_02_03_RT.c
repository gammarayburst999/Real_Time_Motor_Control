//shared memory
/*First MODULE*/
#include <linux/module.h>
#include <linux/init.h>
#include <rtai_nam2num.h>
#include <rtai_shm.h>
#include <rtai.h>
#include <rtai_sched.h>

#define ARG 0
#define STACK_SIZE 1024
#define PRIORITY RT_SCHED_HIGHEST_PRIORITY
#define USE_FPU 1
#define NOW rt_get_time()
#define PERIOD_01 nano2count(1e9)
/* Store data needed for the thread */
RT_TASK thread_data_01;

int counter=100;
int *mem =NULL;
/* The code that is run */
/*Task 01 */
void thread_code_01(long arg)
{
 printk("\n ****** Code of Task 01 started 01  *******\n");
  while (1)
  {
 counter++;  
           printk("RT count = %d \n", counter);
   /*rt_sleep(nano2count(2e9));*/
    rt_task_wait_period();
    *mem =counter;
  }
}
/* Called when "insmod" is used */
static int __init template_init(void)
{
 mem = rtai_kmalloc(nam2num("shmem"), sizeof(int));
  /* Start the RT timer, NB only needs to be done once */
  rt_set_periodic_mode();
  start_rt_timer(PERIOD_01);

  /* Initialise the data associated with a thread and make it periodic */
  rt_task_init(&thread_data_01, thread_code_01,
	       ARG, STACK_SIZE, PRIORITY, USE_FPU, NULL);
	  
  rt_task_make_periodic(&thread_data_01, NOW, PERIOD_01);
    
  /* Return success */
  return 0;
}
/* Called when "rmmod" is used */
static void __exit template_exit(void)
{
  rt_task_delete(&thread_data_01);
  rtai_kfree(nam2num("shmem"));
}
module_init(template_init);
module_exit(template_exit);
