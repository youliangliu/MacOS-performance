#ifndef CONTENTION_H
#define CONTENTION_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

#include "local_read.h"

void contention_read(char *file1,
                     char *file2,
                     char *file3,
                     char *file4,
                     char *msg,
                     int opt);

#endif