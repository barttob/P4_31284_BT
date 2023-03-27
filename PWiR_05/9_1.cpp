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

    //ten blok wykona się tylko raz mimo, że wątków jest więcej
    if(id == 1){
        for(int i = 0;i<100;i++){
            printf("%d ", arr[i]);
        }
    }
}

int main(){
    srand(time(NULL));
    const int size = 100;
    int* arr = new int[size];

    std::thread t1(increment,1, arr);
    std::thread t2(increment,2, arr);

    t1.join();
    t2.join();

    return 0;
}