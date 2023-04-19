#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <chrono>
#include <assert.h>
#include <time.h>

//matrix * vector

#define MATRIX_H 30000
#define MATRIX_W 30000
#define VECTOR_S 30000
#define NUM_RUNS 10

uint16_t** matrix;
uint16_t* vector;
uint16_t* result;

int32_t i;
int32_t k;

int main() {
    srand(time(NULL));

    //check if vector size == matrix width
    assert(MATRIX_W == VECTOR_S);

    //alloc matrix
    matrix = (uint16_t**)new uint16_t * [MATRIX_H];
    for (i = 0; i < MATRIX_H; i++)
        matrix[i] = new uint16_t[MATRIX_W];

    //alloc vectors
    vector = (uint16_t*)new uint16_t[VECTOR_S];
    result = (uint16_t*)new uint16_t[VECTOR_S];

    //fill matrix random data normal way
    auto start = std::chrono::high_resolution_clock::now();
    for (i = 0; i < MATRIX_H; i++) {
        for (k = 0; k < MATRIX_W; k++) {
            matrix[i][k] = (uint16_t)(rand() % 100);
        }
    }

    //fill vector random data
    for (i = 0; i < VECTOR_S; i++) {
        vector[i] = (uint16_t)(rand() % 100);
        result[i] = 0;
    }

    auto end = std::chrono::high_resolution_clock::now();

    printf("Fill in %llu miliseconds\n",
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

    //normal execution
    start = std::chrono::high_resolution_clock::now();
    for (int t = 0; t < NUM_RUNS; t++) {
        for (i = 0; i < MATRIX_H; i++) {
            for (k = 0; k < MATRIX_W; k++) {
                result[i] += matrix[i][k] * vector[k];
            }
        }
    }


    end = std::chrono::high_resolution_clock::now();

    printf("Calculated normal way in %llu miliseconds\n",
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

    start = std::chrono::high_resolution_clock::now();
#pragma omp parallel for num_threads(4)  shared(matrix) private(i, k)
    for (i = 0; i < MATRIX_H; i++) {
        for (k = 0; k < MATRIX_W; k++) {
            matrix[i][k] = (uint16_t)(rand() % 100);
        }
    }

#pragma omp parallel for num_threads(4) shared(vector) private(i) 
    for (i = 0; i < VECTOR_S; i++) {
        vector[i] = (uint16_t)(rand() % 100);
    }
    end = std::chrono::high_resolution_clock::now();

    printf("Fill parallel way in %lu miliseconds\n",
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

    start = std::chrono::high_resolution_clock::now();


#pragma omp parallel for num_threads(4) shared(matrix, vector, result) private(i, k, t)
    for (int t = 0; t < NUM_RUNS; t++) {
        for (i = 0; i < MATRIX_H; i++) {
            for (k = 0; k < MATRIX_W; k++) {
                result[i] += matrix[i][k] * vector[k];
            }
        }
    }
    


    end = std::chrono::high_resolution_clock::now();

    printf("Calculated parallel way in %lu miliseconds\n",
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());


    //free memory
    delete[] vector;
    delete[] result;

    for (i = 0; i < MATRIX_H; i++)
        delete[] matrix[i];

    delete[] matrix;

    return 0;
}