#include <stdio.h>
#include <cuda_runtime.h>

// 错误检查宏：用于检查 CUDA API 调用的返回值
#define check(call) { \
    cudaError_t err = call; \
    if (err != cudaSuccess) { \
        fprintf(stderr, "CUDA error at %s:%d: %s\n", __FILE__, __LINE__, cudaGetErrorString(err)); \
        exit(EXIT_FAILURE); \
    } \
}

// cuda 核函数：在 GPU 上执行矩阵加法
__global__ void sumMatrixOnGPU(float *A, float *B, float *C, int N) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    int j = blockIdx.y * blockDim.y + threadIdx.y;

    if (i < N && j < N) {
        int idx = j * N + i; // 计算矩阵元素的线性索引
        C[idx] = A[idx] + B[idx]; // 执行矩阵加法
    }
}