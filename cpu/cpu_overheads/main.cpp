//
// Created by 刘有亮 on 12/11/20.
//

#define ITERATIONS 1000000

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <unistd.h>
using namespace std;


static __inline__ unsigned long long rdtsc(void)
{
    unsigned hi, lo;
    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
    return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}



double get_read_overhead(){
    double sum = 0;
    uint64_t startTime, endTime;
    for(int i=0; i<ITERATIONS; i++){
        startTime = rdtsc();
        endTime = rdtsc();
        sum += (endTime - startTime);
    }
    return ((double)sum / (double){ITERATIONS});
}

double get_loop_overhead(){
    uint64_t start, end;
    uint64_t sum = 0;
    start = rdtsc();
    for(int i=0; i<ITERATIONS; i++){
    }
    end = rdtsc();
    sum += (end - start);
    return ((double)sum / ITERATIONS);
}

void test_read_overhead(fstream &file){
    cout << "Testing read overhead..." << endl;
    file.open("read_overhead.txt", ios::out);
    for(int i=0; i<10; i++){
        file << setiosflags(ios::fixed) << get_read_overhead() << "\n";
    }
    file.close();
}

void test_loop_overhead(fstream &file){
    cout << "Testing loop overhead..." << endl;
    file.open("loop_overhead.txt", ios::out);
    for(int i=0; i<10; i++){
        file << setiosflags(ios::fixed) << get_loop_overhead() << "\n";
    }
    file.close();
}

void call_0(){}
void call_1(int a){}
void call_2(int a, int b){}
void call_3(int a, int b, int c){}
void call_4(int a, int b, int c, int d){}
void call_5(int a, int b, int c, int d, int e){}
void call_6(int a, int b, int c, int d, int e, int f){}
void call_7(int a, int b, int c, int d, int e, int f, int g){}

vector<double> procedure_call_overhead(){
    vector<double> result;
    double sum = 0;
    uint64_t start, end;
    for(int i=0; i<ITERATIONS; i++){
        start = rdtsc();
        call_0();
        end = rdtsc();
        sum += (end - start);
    }
    sum /= ITERATIONS;
    result.push_back(sum);

    sum = 0;
    for(int i=0; i<ITERATIONS; i++){
        start = rdtsc();
        call_1(1);
        end = rdtsc();
        sum += (end - start);
    }
    sum /= ITERATIONS;
    result.push_back(sum);

    sum = 0;
    for(int i=0; i<ITERATIONS; i++){
        start = rdtsc();
        call_2(1, 2);
        end = rdtsc();
        sum += (end - start);
    }
    sum /= ITERATIONS;
    result.push_back(sum);

    sum = 0;
    for(int i=0; i<ITERATIONS; i++){
        start = rdtsc();
        call_3(1, 2, 3);
        end = rdtsc();
        sum += (end - start);
    }
    sum /= ITERATIONS;
    result.push_back(sum);

    sum = 0;
    for(int i=0; i<ITERATIONS; i++){
        start = rdtsc();
        call_4(1, 2, 3, 4);
        end = rdtsc();
        sum += (end - start);
    }
    sum /= ITERATIONS;
    result.push_back(sum);

    sum = 0;
    for(int i=0; i<ITERATIONS; i++){
        start = rdtsc();
        call_5(1, 2, 3, 4, 5);
        end = rdtsc();
        sum += (end - start);
    }
    sum /= ITERATIONS;
    result.push_back(sum);

    sum = 0;
    for(int i=0; i<ITERATIONS; i++){
        start = rdtsc();
        call_6(1, 2, 3, 4, 5, 6);
        end = rdtsc();
        sum += (end - start);
    }
    sum /= ITERATIONS;
    result.push_back(sum);

    sum = 0;
    for(int i=0; i<ITERATIONS; i++){
        start = rdtsc();
        call_7(1, 2, 3, 4, 5, 6, 7);
        end = rdtsc();
        sum += (end - start);
    }
    sum /= ITERATIONS;
    result.push_back(sum);

    return result;
}


void test_procedure_call_overhead(fstream &file){
    cout << "Testing procedure call overhead..." << endl;
    file.open("procedure_call_overhead.txt", ios::out);
    vector<double> result;
    vector< vector<double> > finalResult;
    vector<double> average;
    for(int i=0; i<10; i++){
        result = procedure_call_overhead();
        finalResult.push_back(result);
    }

    for(int i=0; i<8; i++){
        double total = 0;
        for(int j=0; j<10; j++){
            total += finalResult.at(j).at(i);
        }
        total /= 10;
        average.push_back(total);
    }

    for(auto i = average.begin(); i != average.end(); ++i){
        file << setiosflags(ios::fixed) << *i << "\n";
    }
    file.close();
}

double system_call_overhead(fstream &file){
    uint64_t start, end;
    uint64_t sum = 0;
    for(int i=0; i<ITERATIONS; i++){
        start = rdtsc();
        file.open("test.txt");
        end = rdtsc();
        sum += (end - start);
    }
    return double(sum) / ITERATIONS;
}

void test_system_call_overhead(fstream &file){
    cout << "Testing system call overhead..." << endl;
    file.open("system_call_overhead.txt", ios::out);
    for(int i=0; i<10; i++){
        fstream fileTest;
        file << setiosflags(ios::fixed) << system_call_overhead(fileTest) << "\n";
    }
    file.close();
}

int main(){

    fstream file;

    test_read_overhead(file);
    test_loop_overhead(file);
    test_procedure_call_overhead(file);
    test_system_call_overhead(file);
}