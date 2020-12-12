# How to find the code with desired functionality
Codes have already been divided based on their functinality. You can refer to the directory name to find desired code easily. All detail about codes are illustrated in "methodology" part of the report.

# How to compile and run the code:
For measuments in CPU, Memory and Network parts, go into corresponding directory, run "make". The Makefile will generate a "test" executable file. Run "test" will give the results. In Network part, some measurements require server and client. For these tests, start the "test" executable file of server first, and then run the client.

For measurements in File System,go into "file system.src". First, run "python3 random_bin_file.py". Then, run "make". Finally, run "./cache"
