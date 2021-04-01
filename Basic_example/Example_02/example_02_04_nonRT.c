#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

 
static int end;
static void endme(int dummy) { end=1; }

int main (void)
{

    int fifo, counter;
    
    if ((fifo = open("/dev/rtf0", O_RDONLY)) < 0) 
    {
        fprintf(stderr, "Error opening /dev/rtf0\n");
       // exit(1);
    }

    signal(SIGINT, endme);
    while (!end) 
    {
        read(fifo, &counter, sizeof(counter));
        printf(" Counter : %d \n", counter);
        sleep(2);
    }
    return 0;
}

