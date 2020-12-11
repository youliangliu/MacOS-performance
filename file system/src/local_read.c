#include "local_read.h"

uint64_t sequential_read(off_t readSize, const char *msg, char *file)
{
    const off_t BLOCKSIZE = 8 * 1024;
    void *readBuffer = malloc(BLOCKSIZE);
    int fd;
    off_t bytesRead;
    ssize_t bytesReadPerIter;
    uint64_t start, totalTime, timePerRead;

    // Open file and disable cache
    fd = open(file, O_RDONLY | O_SYNC);
    if (fcntl(fd, F_NOCACHE, 1) == -1)
    {
        printf("Fail to disable cache.\n");
    }

    // Read block by block
    while (bytesRead < readSize)
    {
        start = rdtsc();
        bytesReadPerIter = read(fd, readBuffer, BLOCKSIZE);
        totalTime += rdtsc() - start;
        bytesRead += bytesReadPerIter;
    }

    // Clean up
    close(fd);
    free(readBuffer);
    timePerRead = totalTime / (readSize / BLOCKSIZE);
    printf("%s", msg);
    printf(" - Sequential Read: Average time per read is %llu \n", timePerRead);
    return timePerRead;
}

uint64_t random_read(off_t readSize, const char *msg, char *file)
{
    const off_t BLOCKSIZE = 8 * 1024;
    void *readBuffer = malloc(BLOCKSIZE);
    int fd, readTimes, seed;
    off_t readHere;
    uint64_t start, totalTime, timePerRead;

    // Open file and disable cache
    fd = open(file, O_RDONLY | O_SYNC);
    if (fcntl(fd, F_NOCACHE, 1) == -1)
    {
        printf("Fail to disable cache.\n");
    }

    // Read block by block
    readTimes = readSize / BLOCKSIZE;
    for (int i = 0; i < readTimes; i++)
    {
        seed = rand() % readTimes;
        start = rdtsc();
        read(fd, readBuffer, BLOCKSIZE);
        totalTime += rdtsc() - start;
        lseek(fd, seed * BLOCKSIZE, SEEK_SET);
    }

    // Clean up
    close(fd);
    free(readBuffer);
    timePerRead = totalTime / (readSize / BLOCKSIZE);
    printf("%s", msg);
    printf(" - Random Read: Average time per read is %llu \n", timePerRead);
    return timePerRead;
}
