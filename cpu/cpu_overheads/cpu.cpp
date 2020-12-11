//
// Created by 刘有亮 on 12/11/20.
//

#include "cpu.h"
#include "util.h"
using namespace std;

double cpu::get_read_overhead(){
    double sum = 0;
    uint64_t startTime, endTime;
    //rdtsc();
    for(int i=0; i<ITERATIONS; i++){
        startTime = rdtsc();
        endTime = rdtsc();
        sum += (endTime - startTime);
    }
    return ((double)sum / (double){ITERATIONS});
}

double cpu::get_loop_overhead(){
    uint64_t start, end;
    uint64_t sum = 0;
    start = rdtsc();
    for(int i=0; i<ITERATIONS; i++){
    }
    end = rdtsc();
    sum += (end - start);
    return ((double)sum / ITERATIONS);
}

void cpu::test_read_overhead(fstream &file){
    cout << "Testing read overhead..." << endl;
    file.open("read_overhead.txt", ios::out);
    for(int i=0; i<10; i++){
        file << setiosflags(ios::fixed) << get_read_overhead() << "\n";
    }
    file.close();
}

void cpu::test_loop_overhead(fstream &file){
    cout << "Testing loop overhead..." << endl;
    file.open("loop_overhead.txt", ios::out);
    for(int i=0; i<10; i++){
        file << setiosflags(ios::fixed) << get_loop_overhead() << "\n";
    }
    file.close();
}
