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
__global__ void sumMatrixOnGPU(float *A, float *B, float *C, int Nx, int Ny) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    int j = blockIdx.y * blockDim.y + threadIdx.y;

    if (i < Nx && j < Ny) {
        int idx = j * Nx + i; // 计算矩阵元素的线性索引
        C[idx] = A[idx] + B[idx]; // 执行矩阵加法
    }
}

int main(int argc, char** argv){
    printf("%s Starting...", argv[0]);
    int nx = 1<<14;
    int ny = 1<<14;
    int nxy = nx*ny;
    int nBytes = nxy*sizeof(float);

    float *h_A, *h_B;
    h_A = (float*)malloc(nBytes);
    h_B = (float*)malloc(nBytes);

    float *d_A, *d_B, *d_C;
    return 0;
}