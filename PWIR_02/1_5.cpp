#include <cstdio>
#include <thread>
#include <windows.h>

int action(int id, int sec){
    printf("Uruchamiam watek %d\n", id);
    Sleep(sec*1000); //10 sekund
    printf("Koncze watek %d\n", id);
    return 0;
}

int main(){
    int sec1 = 8, sec2 = 12, sec3 = 5;
    //tworzenie wątku
    std::thread t1(action, 1, sec1); //konstruktor klasy t1 przyjmuje minimum wskaźnik na funckje do wykonania
    std::thread t2(action, 2, sec2); //funckja ta może coś zwracać, ale może zwaracać też void
    std::thread t3(action, 3, sec3); //dalsze parametry zostaną przekazane do podanej funckji

    t1.join();  //synchronizacja
    t2.join();  //wątek główny ma tu poczekać na te 3 wątki
    t3.join();  //inaczej program by się zakończył wcześniej bo wątki trwają minimum 10 sekund

    printf("Koniec programu \r\n");

    return 0;
}
