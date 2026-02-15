#include <iostream>
#include <vector>
#include <omp.h>
#include <signal.h>
#include <csignal>    // 用于 signal() 函数
#include <cstdlib>    // 用于 malloc() 函数
#include <unistd.h>   // 用于 sleep() 函数

typedef struct Data_t {
    int value;
    char *p;
} Data;
static bool stop = false; // 用途: 定义一个全局变量stop，初始值为false，用于控制程序的停止状态。
int main() {
    signal(SIGINT, [](int signum) {
        std::cerr << "Segmentation fault (signal " << signum << ") occurred." << std::endl;
        stop = true; // 设置全局变量stop为true，表示程序应该停止执行。
    });
    // omp_set_num_threads(6); // 用途: 设置OpenMP使用的线程数为4，通常用于控制并行执行的线程数量。
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    std::cout << "numbers size: " << numbers.size() << std::endl;

    void* ptr = nullptr; // 用途: 声明一个空指针，通常用于指向未知类型的数据或作为函数参数。
    ptr = malloc(20*sizeof(struct Data_t)); // 用途: 分配100字节的内存，并将其地址赋值给ptr指针。

    // 用途: 将循环的迭代分配给多个线程并行执行。
    #pragma omp parallel
    {
        // void* ptr_thread = nullptr; // 用途: 声明一个空指针，通常用于指向未知类型的数据或作为函数参数。
        // ptr_thread = malloc(20*sizeof(struct Data_t)); // 用途: 分配100字节的内存，并将其地址赋值给ptr指针。
        int thread_id = omp_get_thread_num(); // 用途: 获取当前线程的ID，通常用于区分不同线程的执行。
        std::cout << "Thread " << thread_id << " is processing the vector." << std::endl;
    }

    // 用途：指定代码块只由第一个到达线程执行，其他线程跳过该代码块。
    #pragma omp parallel for
    for (size_t i = 0; i < 50; ++i) {
        int tmp = ((Data*)ptr)[i].value;
        numbers[i] *= tmp; // Doubling each number in the vector
        printf("[for] i: %d, Thread %d processing\n", i, omp_get_thread_num());
    }
    std::cout << "Numbers in the vector: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    while(!stop) {
        // 用途: 无限循环，通常用于持续执行某些任务，直到满足特定条件或手动终止。
        std::cout << "This is an infinite loop. Press Ctrl+C to stop." << std::endl;
        sleep(2); // 用途: 使程序暂停执行1秒钟，通常用于控制循环的执行频率。
    }
    // free(ptr); // 用途: 释放之前分配的内存，防止内存泄漏。
    return 0;
}
