#ifndef LOCAL_READ_H
#define LOCAL_READ_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "rdtsc.h"

uint64_t sequential_read(off_t readSize, const char *msg, char *file);

uint64_t random_read(off_t readSize, const char *msg, char *file);

#endif
