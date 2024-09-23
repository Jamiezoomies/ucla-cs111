# A Kernel Seedling
The proc_count.ko is a kernel module designed to print the number of processes running on the machine. Upon loading, this module creates a proc entry. By accessing this proc entry, users can see an integer value representing the number of active processes. This documentation also includes commands for cleanup to ensure proper functionality and maintenance. The module has been successfully unit tested with Python.

## Building
cmd for build:
```shell
make
sudo insmod proc_count.ko
```

## Running
cmd for running binary:
```shell
cat /proc/count
```

This command returns an integer indicating the number of processes running on the machine.
In my case:
```
cat /proc/count
157
```


## Cleaning Up
cmd for cleaning the built binary
```shell
sudo rmmod proc_count
make clean
```

## Testing
```python
python -m unittest
```

The command performs the unit test and returns whether the result is successful or a failure. In my case,
```
python -m unittest
ran 3 tests in 2.588s
OK
```

Tested version:
```shell
uname -r -s -v
```
This module was tested on Kernel release Linux version 5.14.8-arch1-1.
(Linux 5.14.8-arch1-1 #1 SMP PREEMPT Sun, 26 Sep 2021 19:36:15 +0000)
