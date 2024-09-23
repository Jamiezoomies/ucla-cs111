# Hash Hash Hash
This project explores different possible implementations for managing concurrent access to a hash table. Using two different locking strategies, we compare them with the base implementation. By changing the number of threads and the number of elements, we evaluate and analyze their correctness and performance.

## Building
To build the program, run the following command:
```shell
make
```

## Running
To test performance and correctness of the hash table, run the program with two command link arguments:
The `-t` flag changes the number of threads to use (default 4) and `-s` flag changes the number of hash table entries to add per thread.
```shell
./hash-table-tester -t 8 -s 50000

Generation: 76,047 usec
Hash table base: 1,034,674 usec
  - 0 missing
Hash table v1: 1,352,645 usec
  - 0 missing
Hash table v2: 357,049 usec
  - 0 missing
```

## First Implementation
In the `hash_table_v1_add_entry` function, I added a single global mutex lock and unlock for the entire hash table to make sure thread safety. Before any update to the hash table, a pthread_mutex_lock is used to prevent other threads from accessing the hash table so that only one thread can modify it at a time. After the update, a pthread_mutex_unlock allows other threads to access the hash table.

### Performance
Test the program's performance with the following command:
```shell
./hash-table-tester -t 8 -s 150000

Generation: 216,785 usec
Hash table base: 17,319,416 usec
  - 0 missing
Hash table v1: 20,226,595 usec
  - 0 missing

```
Version 1 is a little slower than the base version (~0.86x). As the number of threads increases, the performance of version 1 is likely to decrease further. Creating and starting a new thread takes time and resources because the process includes allocating memory, initializing the thread, and integrating it into the scheduler. For this reason, starting and destroying a large number of threads can lead to significant amount of overhead and slow down the performance. 
For the implementation-wise, only one thread is able to modify the hash table at a time even though multiple threads are running. When one thread holds the mutex, all other threads must wait until the mutex is released before they access to the hash table. Since all threads need to obtain the same global mutex before they can work, the high contention occurs and overall performance is reduced.

## Second Implementation
In the `hash_table_v2_add_entry` function, I added a mutex to each bucket in the hash table instead of using a single global mutex. This allows multiple threads to work on different parts of the hash table concurrently without blocking each other.
Before modifying a bucket, the mutex is locked so only one thread can modify that particular bucket at a time. After the modification, the mutex is unlocked so that other threads can access to it.

### Performance
```shell
./hash-table-tester -t 1 -s 50000

Generation: 9,062 usec
Hash table base: 13,762 usec
  - 0 missing
Hash table v2: 15,134 usec
  - 0 missing

./hash-table-tester -t 4 -s 50000

Generation: 36,959 usec
Hash table base: 201,095 usec
  - 0 missing
Hash table v2: 61,494 usec
  - 0 missing

./hash-table-tester -t 8 -s 150000

Generation: 216,785 usec
Hash table base: 17,319,416 usec
  - 0 missing
Hash table v2: 5,431,528 usec
  - 0 missing

```
With only 1 thread, version 2 is slightly slower than the base implementation because the mutex locking may introduce some overhead without any paralleism (~0.91x). However, as the number of threads increases, version 2 shows a significant performance improvement (~3.27x). This is because multiple threads can work on different parts of the hash table concurrently, reducing contention and making better use of CPU. In version 2, by increasing the number of threads, we can expect overall better performance, on average.



## Cleaning up
To clean up, run the following command:
```shell
make clean
```