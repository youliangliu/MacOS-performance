//
// Created by 刘有亮 on 12/11/20.
//

#define LOADS 1000000

#include <math.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
using namespace std;

static __inline__ unsigned long long rdtsc(void)
{
    unsigned hi, lo;
    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
    return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}


int arraySize[11] = {pow(2,12), pow(2, 14), pow(2, 15), pow(2, 16),
                     pow(2, 17), pow(2, 18), pow(2, 19), pow(2, 21),
                     pow(2, 24), pow(2, 28), pow(2, 30)};
int strideSize[7] = {pow(2,2), pow(2,5), pow(2,7), pow(2,10), pow(2,20), pow(2, 22), pow(2, 24)};



double cache_access_time(int arraySize, int strideSize){

    int* array = (int*)malloc(arraySize * sizeof(int));
    memset(array, 0, arraySize * sizeof(int));
    for (int i = 0; i < arraySize; i++) {
        int nextAddress = i + strideSize;
        if (nextAddress >= arraySize) {
            nextAddress = nextAddress % arraySize;
        }
        array[i] = nextAddress;
    }

    uint64_t start, end;
    uint64_t sum;
    int index = array[0];
    start = rdtsc();
    for(int i=0; i<LOADS; i++){
        index = array[index];
    }
    end = rdtsc();
    sum = (end - start);

    //free(array);
    return ((double) sum / LOADS);
}

/*
void test_ram_access_time(fstream &file, int arraySize, int strideSize){
    cout << "Running with array size: " << arraySize << endl;
    cout << "Running with stride size: " << strideSize << endl;
    file.open("ram_access_time.txt", ios::out);
    file << setiosflags(ios::fixed) << cache_access_time(arraySize, strideSize) << "\n";
    file.close();
}

void seperate_data(fstream &file){
    file.open("ram_access_time.txt", ios::out);
    file << setiosflags(ios::fixed) << "--------------------------------------------" << "\n";
    file.close();
}
*/
int main(){


    fstream file;
    file.open("ram_access_time.txt", ios::out);
    for(int i=0; i<7; i++){
        for(int j=0; j<11; j++){
            file << setiosflags(ios::fixed) << "Array size is: " << log2(arraySize[j]) << "\n";
            file << setiosflags(ios::fixed) << cache_access_time(arraySize[j], strideSize[i]) << "\n";
            //test_ram_access_time(file, arraySize[i], strideSize[j]);
        }
        file << setiosflags(ios::fixed) << "\n";
        file << setiosflags(ios::fixed) << "\n";
    }
    file.close();

/*
    for(int i=0; i<7; i++){
        for(int j=0; j<10; j++){
            file << setiosflags(ios::fixed) << cache_access_time(arraySize[j], strideSize[i]) << "\n";
            //test_ram_access_time(file, arraySize[i], strideSize[j]);
        }
        cout << endl;
        cout << endl;
        //seperate_data(file);
    }
*/


}