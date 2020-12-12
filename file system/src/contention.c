#include "contention.h"

const char *P1MSG = "P1";
const char *P2MSG = "P2";
const char *P3MSG = "P3";
const char *P4MSG = "P4";

void contention_read(char *file1,
                     char *file2,
                     char *file3,
                     char *file4,
                     char *msg,
                     int opt)
{
    int n1 = fork();
    int n2 = fork();

    if (opt < 2 || opt > 4)
    {
        printf("Opt can only be 2, 3, 4\n");
        return;
    }

    if (n1 > 0 && n2 > 0)
    {
        sequential_read((512 * 1024 * 1024), P1MSG, file1);
    }
    else if (n1 == 0 && n2 > 0)
    {
        if (opt > 2)
        {
            sequential_read((512 * 1024 * 1024), P2MSG, file2);
        }
        kill(getpid(), SIGKILL);
    }
    else if (n1 > 0 && n2 == 0)
    {
        if (opt > 3)
        {
            sequential_read((512 * 1024 * 1024), P3MSG, file3);
        }
        kill(getpid(), SIGKILL);
    }
    else
    {
        printf("%s - ", msg);
        printf("Process 4, pid %d\n", getpid());
        sequential_read((64 * 1024 * 1024), P4MSG, file4);
        random_read((64 * 1024 * 1024), P4MSG, file4);
        kill(getpid(), SIGKILL);
    }
    return;
}
