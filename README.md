# Linux-Scheduling
Using linux scheduling policies for 3 threads/processes

This contains 2 parts:- 1) Thread Scheduling   2) Process Scheduling

## Thread Scheduling

This program uses linux scheduling policies on 3 threads A, B & C to time the process of counting from 1 to 2^32 by using different scheduling disciplines. The 3 threads run on 3 identical functions countA(), countB() & countC(); each of which count from 1 to 2^32.

The scheduling classes used by threads A, B & C are SCHED_OTHER, SCHED_FIFO & SCHED_RR respectively. Initially, the threads run on their default priorities.

clock_gettime() is used to time the counting process.

## Process Scheduling

This program creates 3 processes; each of which compiles a copy of the linux kernel source(linux 5.19.9). The processes are created using fork() and the 3 child processes use exec() family of system calls to run a different bash scripting, containing the commands for compiling the kernel.
The 3 programs are run on default priority, hence, 3 seperate copies of the kernel must be created so that, each process simultaneosly compiles a seperate copy of the kernel.

clock_gettime() is used to time the processes.

## How to run the program?
1) Clone the entire repository
2) Go to the respective folders
3) Run make

