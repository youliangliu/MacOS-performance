#include "cache_size.h"
#include "local_read.h"
#include "contention.h"
#include "constant.h"

int main(int argc, const char *argv[])
{
    // Test cache size
    cache_size_test();

    // Test local read speed
    for (int i = 0; i < 7; i++)
    {
        printf("Testing local read, iteration %d:\n", i);
        sequential_read((off_t)testList[i], LOCALMSG, file1);
        random_read((off_t)testList[i], LOCALMSG, file1);
    }

    // Test contention
    printf("\nTring 2 processes:\n");
    contention_read(file1, file2, file3, file4, "2 processes", 2);
    sleep(5);
    printf("\nTring 3 processes:\n");
    contention_read(file1, file2, file3, file4, "3 processes", 3);
    sleep(5);
    printf("\nTring 4 processes:\n");
    contention_read(file1, file2, file3, file4, "4 processes", 4);
}
