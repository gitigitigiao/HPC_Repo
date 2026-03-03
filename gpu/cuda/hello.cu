#include <iostream>
#include <cuda_runtime.h>

// __global__ 关键字告诉编译器：这个函数是在 GPU 上运行的
// 它可以从 CPU（主机端）通过 <<< >>> 语法调用
__global__ void helloFromGPU() {
    // 获取当前线程的 ID
    int threadId = threadIdx.x;
    printf("Hello World from GPU thread %d!\n", threadId);
}

int main() {
    // 1. 在主机端（CPU）输出
    std::cout << "Hello World from CPU!" << std::endl;

    // 2. 启动 GPU 核函数（Kernel）
    // <<<网格大小, 线程块大小>>> 
    // 这里我们启动 1 个线程块，里面包含 10 个线程
    helloFromGPU<<<10000, 64>>>();

    // 3. 重点：由于 GPU 核函数是异步执行的，
    // CPU 不会等它运行完就继续往下走了，所以我们需要同步等待
    cudaDeviceSynchronize();

    std::cout << "GPU execution finished." << std::endl;

    return 0;
}