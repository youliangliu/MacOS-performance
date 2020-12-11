//
// Created by 刘有亮 on 12/11/20.
//


#include "cpu.h"
using namespace std;

int main(){
    class cpu cpu;
    fstream file;

    cpu.test_read_overhead(file);
    cpu.test_loop_overhead(file);
    cpu.test_procedure_call_overhead(file);
    cpu.test_system_call_overhead(file);
}