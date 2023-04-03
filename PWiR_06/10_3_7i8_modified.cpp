#include <thread>
#include <cstdio>
#include <windows.h>
#include <atomic>

std::atomic<unsigned int> counter(0);

void increment(){
    for(;;){
        counter++;
        Sleep(2000);
    }
}

void parity(){
    for(;;){
        if (counter % 2){
            printf("%u jest nieparzyste\r\n", counter.load());
        }
        else{
            printf("%u jest parzyste\r\n", counter.load());
        }
        Sleep(2000);
    }
}

int main(){
    std::thread inc(increment);
    std::thread par(parity);

    inc.join();
    par.join();

    printf("Done\r\n");

    return 0;
}