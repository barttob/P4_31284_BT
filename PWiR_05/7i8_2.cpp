#include <thread>
#include <cstdio>
#include <windows.h>
#include <mutex>
#include <chrono>

std::mutex counter_mutex;
unsigned int counter = 0;

void increment(){
    for(;;){
        counter_mutex.lock();
        counter++;
        counter_mutex.unlock();
        Sleep(2000);
        if (counter == 10)
            break;
    }
}

void parity(){
    for(;;){
        counter_mutex.lock();
        if (counter % 2){
            printf("%u jest nieparzyste\r\n", counter);
        }
        else{
            printf("%u jest parzyste\r\n", counter);
        }
        counter_mutex.unlock();
        Sleep(2000);
        if (counter == 10)
            break;
    }
}

int main(){
    auto start = std::chrono::steady_clock::now();
    std::thread inc(increment);
    std::thread par(parity);

    inc.join();
    par.join();

    auto end = std::chrono::steady_clock::now();
    printf("Czas trwania: %llu\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
    printf("Done\r\n");

    return 0;
}