#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <thread>
#include <chrono>

#define SIZE 40

void add(int id, int* a, int* b, int* c) {
    for (int i = id; i < id + 10; i++) {
        c[i] = a[i] + b[i];
    }
}

int main() {
    srand(time(NULL));
    int a[SIZE];
    int b[SIZE];
    int c[SIZE];

    for (int i = 0; i < SIZE; i++) {
        a[i] = rand() % 100 + 1; //1 do 100
        b[i] = rand() % 100 + 1;
    }

    //wypisanie na ekranie A
    for (int i = 0; i < SIZE; i++) {
        printf("%u ", a[i]);
    }
    printf("\n");

    //wypisanie na ekranie B
    for (int i = 0; i < SIZE; i++) {
        printf("%u ", b[i]);
    }
    printf("\n");


    std::thread** threads = new std::thread * [SIZE/10];
    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < SIZE / 10; i++) {
        threads[i] = new std::thread(add, (i * 10), a, b, c); //wykorzystuje i jako id danego wątku
    }

    for (int i = 0; i < SIZE / 10; i++) {
        threads[i]->join();
    }
    auto end = std::chrono::steady_clock::now();

    for (int i = 0; i < SIZE / 10; i++) {
        delete threads[i];
    }
    delete[] threads;

    //wypisanie na ekranie C
    for (int i = 0; i < SIZE; i++) {
        printf("%u ", c[i]);
    }

    printf("\n");
    printf("Czas trwania: %llu\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());


    return 0;
}
