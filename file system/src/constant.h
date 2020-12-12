#ifndef CONSTANT_H
#define CONSTANT_H

#include <sys/types.h>

char *LOCALMSG = "Local Read";
char *REMOTEMSG = "Remote Read";

off_t testList[] = {
    2 * 1024 * 1024,
    4 * 1024 * 1024,
    8 * 1024 * 1024,
    16 * 1024 * 1024,
    32 * 1024 * 1024,
    64 * 1024 * 1024,
    128 * 1024 * 1024};

char *file1 = "../data/1gb_bin.dat";
char *file2 = "../data/2gb_bin.dat";
char *file3 = "../data/4gb_bin.dat";
char *file4 = "../data/6gb_bin.dat";
char *remoteFile = "/Volumes/下载/1gb_bin.dat";

#endif