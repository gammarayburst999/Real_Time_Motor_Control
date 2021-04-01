
Description
A three real-time tasks which are synchronised to be executed one after the other. That is,
the first task will be set up to run periodically. When this task is finished its code, it wakes
up the next task, which in turn wakes up the last task when it has finished.
 Note :The second and third task not to be set up periodically. To do this I have used the functions:
rt task resume, and rt task suspend.

Compilation is carried out using the gcc compiler.

For more info check RTAI Programming Guide and RTAI Manual
online for further reference.
