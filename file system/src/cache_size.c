#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

const int TESTSIZE = 7;
const off_t BLOCKSIZE = 8 * 1024;
const off_t FILESIZES[] = {
    (double)0.5 * (double)1073741824,
    (double)4 * (double)1073741824,
    (double)6 * (double)1073741824,
    (double)8 * (double)1073741824,
    (double)10 * (double)1073741824,
    (double)12 * (double)1073741824,
    (double)14 * (double)1073741824,
    (double)16 * (double)1073741824};
const char *TESTFILES[] = {
    "../data/0.5gb_bin.dat",
    "../data/4gb_bin.dat",
    "../data/6gb_bin.dat",
    "../data/8gb_bin.dat",
    "../data/10gb_bin.dat",
    "../data/12gb_bin.dat",
    "../data/14gb_bin.dat",
    "../data/16gb_bin.dat"};

static inline uint64_t rdtsc()
{
    uint32_t lo, hi;
    __asm__ __volatile__("rdtsc"
                         : "=a"(lo), "=d"(hi));
    return ((uint64_t)hi << 32) | lo;
}

int main(int argc, const char *argv[])
{
    void *readBuffer = malloc(BLOCKSIZE);
    int fd;
    off_t bytesRead;
    ssize_t bytesReadPerIter;
    uint64_t start, totalTime, readTimes, timePerRead;

    for (int i = 0; i < TESTSIZE; i++)
    {

        // Read in data for the 1st time
        fd = open(TESTFILES[i], O_RDONLY | O_SYNC);
        lseek(fd, (FILESIZES[i] - BLOCKSIZE - 1), SEEK_SET);
        bytesRead = 0;
        bytesReadPerIter = 0;
        if (fd != -1)
        {
            printf("1st round reading: Reading from file %d, with size %lld",
                   i, FILESIZES[i]);
        }
        else
        {
            printf(" - Error reading file %d\n", i);
            return -1;
        }
        while (bytesRead < FILESIZES[i])
        {
            bytesReadPerIter = read(fd, readBuffer, BLOCKSIZE);
            bytesRead += bytesReadPerIter;
            lseek(fd, -2 * BLOCKSIZE, SEEK_CUR);
        }
        printf(" - Finished!\n");
        close(fd);

        // Read in data again and get time
        fd = open(TESTFILES[i], O_RDONLY | O_SYNC);
        bytesRead = 0;
        totalTime = 0;
        lseek(fd, (FILESIZES[i] - BLOCKSIZE - 1), SEEK_SET);
        if (fd != -1)
        {
            printf("2nd round reading: Reading from file %d, with size %lld",
                   i, FILESIZES[i]);
        }
        else
        {
            printf(" - Error reading file %d\n", i);
            return -1;
        }
        while (bytesRead < FILESIZES[i])
        {
            start = rdtsc();
            bytesReadPerIter = read(fd, readBuffer, BLOCKSIZE);
            totalTime += rdtsc() - start;
            bytesRead += bytesReadPerIter;
            lseek(fd, -2 * BLOCKSIZE, SEEK_CUR);
        }
        printf(" - Finished!\n");
        close(fd);

        // Printout results
        timePerRead = totalTime / (FILESIZES[i] / BLOCKSIZE);
        printf(
            "Average time per read is %llu \n\n", timePerRead);
    }
}
