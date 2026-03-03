#include <iostream>
#include <vector>
#include <openacc.h>
#include <signal.h>

int main() {
    signal(SIGINT, [](int signum) {
        std::cerr << "Segmentation fault (signal " << signum << ") occurred." << std::endl;
        exit(signum); // 直接退出程序，返回信号编号作为退出状态。
    });

    std::vector<int> numbers = {1, 2, 3, 4, 5};

    std::cout << "numbers size: " << numbers.size() << std::endl;

    // 用途: 将循环的迭代分配给多个线程并行执行。
    #pragma acc parallel loop
    for (size_t i = 0; i < numbers.size(); ++i) {
        numbers[i] *= 2; // Doubling each number in the vector
        printf("[for] i: %d, processing\n", i);
    }

    std::cout << "Numbers in the vector: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    while(true) {
        // 用途: 无限循环，通常用于持续执行某些任务，直到满足特定条件或手动终止。
        std::cout << "This is an infinite loop. Press Ctrl+C to stop." << std::endl;
        sleep(2); // 用途: 使程序暂停执行1秒钟，通常用于控制循环的执行频率。
    }

    return 0;
}