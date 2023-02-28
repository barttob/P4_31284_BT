#include <cstdio>
#include <thread>
#include <windows.h>
#include <vector>

void action(int id){
    printf("Uruchamiam watek %d\n", id);
    Sleep(5*1000); //5 sekund
    printf("Koncze watek %d\n", id);
}

int main(){
    int thread_count = 8;

    //alokacja tablicy, która będzie przechowywać wskaźniki na wątki
    std::vector<std::thread*> threads;
    //std::thread** threads = new std::thread*[thread_count];

    //otwieranie wątków
    for(int i = 0;i<thread_count;i++){
        threads.push_back(new std::thread(action, i)); //wykorzystuje i jako id danego wątku
    }

    //watki pracują, ale trzeba je zsynchronizować
    for(std::thread* n : threads){
        n->join();
    }

    //alokowaliśmy pamięć więc pasuje ją zwolnić
    threads.clear();

    printf("Koniec programu \r\n");

    return 0;
}
