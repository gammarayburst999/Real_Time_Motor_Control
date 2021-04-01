
Description

Two Linux programs (clients) will be responsible for “communicating” with a real-time device driver
through a third Linux task (server). The first Linux program will request and display motor position
data periodically from the server. The second will provide setpoint data to the server to be used in simple
proportional feedback control of the motor position. The real-time device driver will exist as one or more
real-time tasks, responsible for sampling motor position periodically at approximately 10Hz, and also
providing a calculated control actuation at the same rate. Communication between the real-time task(s)
and the Linux server will be through either RT-FIFO’s or shared memory.
Compilation is carried out using the gcc compiler.

real_time_device_driver.c - sampling motor position periodically at approximately 10Hz, and also
providing a calculated control actuation at the same rate.

client.c - the client will be a Linux program which requires sampled data from the server, and then displays it.


For more info check RTAI Programming Guide and RTAI Manual
online for further reference.
