# How to find the code with desired functionality
Codes have already been divided based on their functinality. You can refer to the directory name to find desired code easily. All detail about codes are illustrated in "methodology" part of the report.

## Quick find:
### CPU, Scheduling, and OS Servicestest:
#### Measurement, procedure call and sytem call overhead test: In "cpu/cpu_overheads" folder
#### Task creation time test: In "cpu/task_creation" folder
#### Process contex switch test: in "cpu/process_switch" folder
#### Thread contex switch test: in "cpu/thread_switch" folder

### Memory test:
#### RAM access time test: In "memory/RAM_access" folder
#### RAM bandwidth test: In "memory/RAM_bandwidth" folder
#### Page fault service time test:  In "memory/page fault" folder

### Network test (Compile and run servers first. When server is running, compile and run clients):
#### Round trip time test: In "network/rtt" folder
#### Peak bandwidth: In "network/bandwidth" folder
#### Connection overhead: In "network/connection" folder

### File system test:
#### All in "file system/src" folder.

# How to compile and run the code:
 For measuments in CPU, Memory and Network parts, go into corresponding directory, run "make". The Makefile will generate a "test" executable file. Run "test" will give the results. In Network part, some measurements require server and client. For these tests, start the "test" executable file of server first, and then run the client.

For measurements in File System,go into "file system/src". First, run "python3 random_bin_file.py". Then, run "make". Finally, run "./cache"
