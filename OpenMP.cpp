#include <iostream>
#include <vector>
#include <omp.h>

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
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    void* ptr = nullptr; // 用途: 声明一个空指针，通常用于指向未知类型的数据或作为函数参数。
    ptr = malloc(100*sizeof(struct Data_t)); // 用途: 分配100字节的内存，并将其地址赋值给ptr指针。

    
    // 用途: 将循环的迭代分配给多个线程并行执行。
    #pragma omp parallel
    {
        std::cout << "Thread " << omp_get_thread_num() << " is processing the vector." << std::endl;
    }

    // 用途：指定代码块只由第一个到达线程执行，其他线程跳过该代码块。
    #pragma omp parallel for
    for (size_t i = 0; i < numbers.size(); ++i) {
        numbers[i] *= (int)ptr[i]; // Doubling each number in the vector
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

    return 0;
}
