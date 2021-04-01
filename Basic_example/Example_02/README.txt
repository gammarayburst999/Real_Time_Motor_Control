
Description -Real-Time Task Communication
By the use of the global memory variable a sufficient means of communication between two
real-time processes is confirmed.
• File: example_02_02_RT -
the two real-time tasks separated by constructing two independent modules, however using the
same global counter variable.

• File: example_02_03_nonRT -the first real-time task,  the second task (which displays the
counter) is a non real-time Linux task (containing main).(Global Variable)

• File: example_02_03_RT - the first real-time task,  the second task (which displays the
counter) is a real-time Linux task (containing main).(Global Variable)

• File: example_02_04_nonRT - shared memory

• File: example_02_04_RT - FIFO 


Compilation is carried out using the gcc compiler.

For more info check RTAI Programming Guide and RTAI Manual
online for further reference.
