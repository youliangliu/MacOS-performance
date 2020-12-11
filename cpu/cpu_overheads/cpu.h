//
// Created by 刘有亮 on 12/11/20.
//

#ifndef MACOS_PERFORMANCE_CPU_H
#define MACOS_PERFORMANCE_CPU_H

#define ITERATIONS 100000

#include <sys/types.h>
#include <mach/mach_time.h>
#include <mach/mach.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <unistd.h>
//#include "util.h"
using namespace std;

static __inline__ unsigned long long rdtsc(void)
{
    unsigned hi, lo;
    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
    return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}

class cpu {
private:
    double get_read_overhead();
    double get_loop_overhead();
    void call_0();
    void call_1(int a);
    void call_2(int a, int b);
    void call_3(int a, int b, int c);
    void call_4(int a, int b, int c, int d);
    void call_5(int a, int b, int c, int d, int e);
    void call_6(int a, int b, int c, int d, int e, int f);
    void call_7(int a, int b, int c, int d, int e, int f, int g);
    vector<double> procedure_call_overhead();
    double system_call_overhead();
public:
    void test_read_overhead(fstream &);
    void test_loop_overhead(fstream &);
    void test_procedure_call_overhead(fstream &);
    void test_system_call_overhead(fstream &);
};


#endif //MACOS_PERFORMANCE_CPU_H
