# RAPLwithThreads

  

## How to use?

  

1. Open the terminal in this directory and, first of all, run the following command:

	``` sudo modprobe msr ```
	
2. Now let's run the *makefile* to compile *raplServer* and *raplClient*

	```make```

We will need two terminals to run *raplServer* alonsige *raplClient*.

> **Note:** The directory chosen to run *raplServer* and *raplClient*, will be the directory where the results files will be created.

3. In this example, we chose the **results** directory, so

	``` cd results```

4. It's time to start *raplServer*:

	```sudo ../raplServer```

5. In the second terminal, we will run the *raplClient* following this command template:

    ```sudo ../raplClient timeinterval result program ```
			
	a) **timeinterval** - Interval of microseconds that RAPL will be reading and writting values to the results file;
	b) **result** - File created with name *result.rapl* containing the reading values of RAPL.
	c) **program** - Program executed to measure the energy spent.

>In this example, we will chose a time interval of 10000 micro seconds, creating the file *result.rapl* while running a *sleep* of 3 seconds:

	sudo ../raplClient 10000 result "sleep 3s"

6. Now, if we want to sum all the values containing in *result.rapl*, we just need do run the script *cleanresults.py* following this command template:

	```../cleanresults.py name```

	a) **Name** - Name of the file created by *RAPL* (without extension)
	
>In this example, the name of the file created is *result.rapl*, so we just need to run

	../cleanresults.py result

And that's it!  The file *result.sum* was created and now we have the energy spent by a *sleep* of 3 seconds.