#include <iostream>
#include <cstdio>
#include <thread>
#include <windows.h>

void action(int id){
    printf("Uruchamiam watek %d\n", id);
    Sleep(5*1000); //5 sekund
    printf("Koncze watek %d\n", id);
}

int main(){
    int thread_count = 0;
    std::cout << "Podaj ilosc watkow: ";
    std::cin >> thread_count;

    //alokacja tablicy, która będzie przechowywać wskaźniki na wątki
    std::thread** threads = new std::thread*[thread_count];

    //otwieranie wątków
    for(int i = 0;i<thread_count;i++){
        threads[i] = new std::thread(action, i); //wykorzystuje i jako id danego wątku
    }

    //watki pracują, ale trzeba je zsynchronizować
    for(int i = 0;i<thread_count;i++){
        threads[i]->join();
    }

    //alokowaliśmy pamięć więc pasuje ją zwolnić
    for(int i = 0;i<thread_count;i++){
        delete threads[i];
    }
    delete[] threads;

    printf("Koniec programu \r\n");

    return 0;
}
