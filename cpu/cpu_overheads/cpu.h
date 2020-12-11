//
// Created by 刘有亮 on 12/11/20.
//

#ifndef MACOS_PERFORMANCE_CPU_H
#define MACOS_PERFORMANCE_CPU_H

#include <sys/types.h>
#include <mach/mach_time.h>
#include <mach/mach.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include "util.h"
using namespace std;

class cpu {
private:
    double get_read_overhead();
    double get_loop_overhead();
public:
    void test_read_overhead(fstream &);
    void test_loop_overhead(fstream &);
};


#endif //MACOS_PERFORMANCE_CPU_H
