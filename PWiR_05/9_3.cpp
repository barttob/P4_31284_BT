#include <thread>
#include <cstdio>
#include <windows.h>
#include <ctime>

thread_local unsigned int counter = 0;

void increment(int id, int* arr){
    for(int i = 0;i<100;i++){
        arr[i] = rand() % 10 + 1;
//        Sleep(300);
    }
    int sum = 0;

    for(int i = id*10; i < (id+1)*10; i++) {
        sum += arr[i];
    }

    thread_local int thread_sum = sum;

    printf("%d -> %d \n", id, thread_sum);
}

int main(){
    srand(time(NULL));
    const int size = 100;
    int* arr = new int[size];

    std::thread threads[10];

    for(int i = 0; i < 10; i++) {
        threads[i] = std::thread(increment, i, arr);
    }

    for(int i = 0; i < 10; i++) {
        threads[i].join();
    }

    return 0;
}