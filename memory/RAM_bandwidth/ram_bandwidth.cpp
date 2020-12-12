//
// Created by 刘有亮 on 12/12/20.
//

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

//Read the 1GB array
double read_time(int* array){
    int arrayLength = pow(10, 9) * 40;
    int sum = 0;
    //Unroll the loop
    uint64_t start, end;
    uint64_t totalTime = 0;
    start = rdtsc();
    for(int i=0; i<(arrayLength/5); i+=5){
        sum += array[i] + array[i+1] + array[i+2] + array[i+3] + array[i+4];
    }
    end = rdtsc();
    totalTime = end - start;
    return (double)totalTime;
}

double write_time(int* array){
    int arrayLength = pow(10, 9) * 40;
    int sum = 0;
    //Unroll the loop
    uint64_t start, end;
    uint64_t totalTime = 0;
    start = rdtsc();
    for(int i=0; i<(arrayLength/5); i+=5){
        //sum += array[i] + array[i+1] + array[i+2] + array[i+3] + array[i+4];
        array[i] = 1;
        array[i+1] = 1;
        array[i+2] = 1;
        array[i+3] = 1;
        array[i+4] = 1;
    }
    end = rdtsc();
    totalTime = end - start;
    return (double)totalTime;
}


int main(){

    //allocate 1GB array
    double size = pow(10, 9) * 2 * sizeof(int) * 40;
    int* array = (int*)malloc(pow(10, 9) * 2 * sizeof(int) * 40);
    //memset(array, 0, size);
    double readBandWidth = 0;
    for(int i=0; i<10; i++){
        readBandWidth += size / read_time(array);
    }
    readBandWidth /= 10;
    cout << "read bandwidth is: " << readBandWidth << endl;

    double writeBandWidth = 0;
    for(int i=0; i<10; i++){
        writeBandWidth += size / write_time(array);
    }
    writeBandWidth /= 10;
    cout << "write bandwidth is: " << writeBandWidth << endl;
    free(array);

}