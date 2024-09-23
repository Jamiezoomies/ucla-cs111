# You Spin Me Round Robin
This project implements a Round Robin scheduling algorithm in C.

## Building
To build the project, the following command will compile the source code and create the rr executable.
```shell
make
```

## Running
To run the Round Robin scheduler, use the following command. Replace processes.txt with the path to your input file and quantum with your desired quantum length.
```shell
./rr processes.txt 3
```

## Result
When you run the command, the output will display the average waiting time and average response time. An example with quantum length 3:
```shell
./rr processes.txt 3

Average waiting time: 7.00
Average response time: 2.75
```

## Cleaning up
To clean up the compiled files, use the following command, which will remove the rr executable and any other generated files.
```shell
make clean
```
