// A program which creates two real-time tasks, each of which performs different things.
#include <linux/module.h>
#include <linux/init.h>

#include <rtai.h>
#include <rtai_sched.h>

#define ARG 0
#define STACK_SIZE 1024
#define PRIORITY RT_SCHED_HIGHEST_PRIORITY
#define USE_FPU 1
#define NOW rt_get_time()
#define PERIOD_01 nano2count(1e9)
#define PERIOD_02 nano2count(2e9)

/* Store data needed for the thread */
RT_TASK thread_data_01;
RT_TASK thread_data_02;
int counter=0;

/* The code that is run */
/*Task 01 */
void thread_code_01(long arg)
{
 printk("\n ****** Code of Task 01 started 01  *******\n");
  while (1)
  {
 counter++;  
           /*printk("RT count = %d \n", counter);*/
   /*rt_sleep(nano2count(2e9));*/
    rt_task_wait_period();
  }
}
/*Task 02 */
void thread_code_02(long arg)
{
 printk("\n ****** Code of Task 01 started 02  *******\n");
  while (1)
  {
      printk("RT count = %d \n", counter);
   /*rt_sleep(nano2count(1e9));*/
    rt_task_wait_period();
  }
}

/* Called when "insmod" is used */
static int __init template_init(void)
{
  /* Start the RT timer, NB only needs to be done once */
  rt_set_periodic_mode();
  start_rt_timer(PERIOD_01);
   start_rt_timer(PERIOD_02);

  /* Initialise the data associated with a thread and make it periodic */
  rt_task_init(&thread_data_01, thread_code_01,
	       ARG, STACK_SIZE, PRIORITY, USE_FPU, NULL);
	       rt_task_init(&thread_data_02, thread_code_02,
	       ARG, STACK_SIZE, PRIORITY, USE_FPU, NULL);
  rt_task_make_periodic(&thread_data_01, NOW, PERIOD_01);
    rt_task_make_periodic(&thread_data_02, NOW, PERIOD_02);

  /* Return success */
  return 0;
}

/* Called when "rmmod" is used */
static void __exit template_exit(void)
{
  rt_task_delete(&thread_data_01);
  rt_task_delete(&thread_data_02);
}

module_init(template_init);
module_exit(template_exit);
