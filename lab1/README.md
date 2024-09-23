## UID: 506043010

## Pipe Up

A program that executes a series of commands in a pipeline, allowing users to pass executable names as command line arguments. This program will execute each one in a new process and enable the output of one command to be passed as input to the next.

## Building

To build the program, compile it using gcc:
```bash
gcc -o pipe pipe.c
```

## Running

For necessary permission to execute the program:
```bash
chmod +x pipe
```

To run the program, provide a series of commands as arguments. The program will set up a pipeline where the output of each command is passed as input to the next. Note that this program is not implemented to handle passing additional command line arguments to each individual process.

Examples:
```bash
./pipe ls cat wc

echo -e "banana\napple\norange" | ./pipe sort wc
```

## Cleaning up

To clean up all binary files, remove the compiled program using the command:
```bash
rm pipe
```
