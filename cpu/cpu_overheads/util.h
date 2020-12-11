//
// Created by 刘有亮 on 12/11/20.
//

#ifndef MACOS_PERFORMANCE_UTIL_H
#define MACOS_PERFORMANCE_UTIL_H

#define ITERATIONS 100000

static inline uint64_t rdtsc(void) {
    uint32_t lo, hi;
    __asm__ __volatile__("xor %%eax, %%eax;" "cpuid;" "rdtsc;": "=a" (lo), "=d" (hi));
    return (((uint64_t)hi << 32) | lo);
}


#endif //MACOS_PERFORMANCE_UTIL_H
