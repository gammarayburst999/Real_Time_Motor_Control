// display the shared memory 

#include <stdio.h>

#include <rtai.h>
#include <rtai_nam2num.h>
#include <rtai_shm.h>
int counter;
int *mem=NULL;int main(void)
{
  mem = rtai_malloc(nam2num("shmem"), sizeof(int));
  // code over here 
  while (1)
  {
     counter=*mem;
      printf("non  	RT count = %d \n", counter);
   sleep(1);
   
  }
  rtai_free(nam2num("shmem"),mem);

  return 0;
}

