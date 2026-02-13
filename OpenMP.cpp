#include <iostream>
#include <vector>
#include <omp.h>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // 用途: 将循环的迭代分配给多个线程并行执行。
    #pragma omp parallel
    {
        std::cout << "Thread " << omp_get_thread_num() << " is processing the vector." << std::endl;
    }

    // 用途：指定代码块只由第一个到达线程执行，其他线程跳过该代码块。
    #pragma omp parallel for
    for (size_t i = 0; i < numbers.size(); ++i) {
        numbers[i] *= 2; // Doubling each number in the vector
    }
    std::cout << "Numbers in the vector: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
