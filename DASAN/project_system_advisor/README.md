Project : system tracking 

Description: 
> Use knowleage about Process , Signal to create a APP tracking CPU, MEMORY, ... and save 
    log file

Feature : 
> Tracking all process in a linux system about Cpu , Mem

> Tracking one or more process with specific PID which is set 

> Alert to User when system is overload

> Kill process which is overload 

> Log file for tracking in long time 

Skill :
> C programming
> Linux File System (/proc)
> Process 
> Signal 
> Binary Search Tree
> Function Pointer

Note:
> Log file certain name, cpu, mem, start/stop time of processes when they is overload

Organization 

	project locate "inter_bst_proc" directory

How to run ?

	go to "cd inter_bst_proc"
	
	run "make"

Test 2 feature:
	Feature 1 : tracking specific PIDs
	
		1.run : "./m 1"
		
		2.enter number pids tracking 
		
		3.enter each PID sequence 
		
		4.enter RAM limit ( percent)
		
		5.enter time out ( for alert, update node to tree)

	
	Feature 2 : tracking all processes on System
		1.run : "./m 2"
		2.enter RAM limit ( percent)
		3.enter time out ( for alert, update node to tree)











