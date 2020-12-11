#include "cache_size.h"
#include "local_read.h"

int main(int argc, const char *argv[])
{
    // cache_size_test();

    //Test read speed
    off_t testList[] = {
        2 * 1024 * 1024,
        4 * 1024 * 1024,
        8 * 1024 * 1024,
        16 * 1024 * 1024,
        32 * 1024 * 1024,
        64 * 1024 * 1024,
        128 * 1024 * 1024};

    for (int i = 0; i < 7; i++)
    {
        sequential_read((off_t)testList[i]);
        random_read((off_t)testList[i]);
    }
}
