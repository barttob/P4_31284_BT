#include "mpi.h"
#include <cstdio>
#include <iostream>
#include <time.h>

void mainProcess(int size, int vectorSize) {
    srand(time(NULL));

    // alokujemy wektory o rozmiarze (vectorSize * (size - 1))
    unsigned int* va = new unsigned int[vectorSize * (size - 1)];
    unsigned int* vb = new unsigned int[vectorSize * (size - 1)];
    unsigned int* vc = new unsigned int[vectorSize * (size - 1)];

    // wypełniamy a i b losowymi danymi, a vc zerujemy
    for (int i = 0; i < vectorSize * (size - 1); i++) {
        va[i] = rand() % 10;
        vb[i] = rand() % 10;
        vc[i] = 0;
    }

    // broadcastujemy rozmiar wektorów do pozostałych procesów
    MPI_Bcast(&vectorSize, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // broadcastujemy wektor a do pozostałych procesów
    MPI_Bcast(va, vectorSize * (size - 1), MPI_UNSIGNED, 0, MPI_COMM_WORLD);

    // broadcastujemy wektor b do pozostałych procesów
    MPI_Bcast(vb, vectorSize * (size - 1), MPI_UNSIGNED, 0, MPI_COMM_WORLD);

    // odpalamy nasłuch
    MPI_Request* requests = new MPI_Request[size - 1];
    MPI_Status* statuses = new MPI_Status[size - 1];
    for (int i = 0; i < size - 1; i++) {
        MPI_Irecv(vc + i * vectorSize, vectorSize, MPI_UNSIGNED, i + 1, 0, MPI_COMM_WORLD, &requests[i]);
    }
    MPI_Waitall(size - 1, requests, statuses);

    // wypisujemy wyniki
    for (int i = 0; i < (vectorSize * (size - 1)); i++) printf("%d\t", va[i]);
    printf("\r\n");
    for (int i = 0; i < (vectorSize * (size - 1)); i++) printf("%d\t", vb[i]);
    printf("\r\n");
    for (int i = 0; i < (vectorSize * (size - 1)); i++) printf("%d\t", vc[i]);
    printf("\r\n");

    // zwalniamy pamięć
    delete[] va;
    delete[] vb;
    delete[] vc;
    delete[] requests;
    delete[] statuses;
}

void workerProcess(int id, int size) {
    // odbieramy rozmiar wektorów
    int vectorSize;
    MPI_Bcast(&vectorSize, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // alokujemy bufor na moją część zadania
    unsigned int* v = new unsigned int[vectorSize];

    // alokujemy miejsce na wektor a oraz b
    unsigned int* va = new unsigned int[vectorSize * (size - 1)];
    unsigned int* vb = new unsigned int[vectorSize * (size - 1)];

    // nasłuchujemy broadcasta wektora a
    MPI_Bcast(va, vectorSize * (size - 1), MPI_UNSIGNED, 0, MPI_COMM_WORLD);

    // nasłuchujemy broadcasta wektora b
    MPI_Bcast(vb, vectorSize * (size - 1), MPI_UNSIGNED, 0, MPI_COMM_WORLD);

    // liczymy sumę
    for (int i = 0; i < vectorSize; i++) {
        v[i] = va[(id - 1) * vectorSize + i] + vb[(id - 1) * vectorSize + i];
    }

    // odsyłamy wynik
    MPI_Send(v, vectorSize, MPI_UNSIGNED, 0, 0, MPI_COMM_WORLD);

    // zwalniamy pamięć
    delete[] v;
    delete[] va;
    delete[] vb;
}

int main()
{
    int PID, PCOUNT;

    MPI_Init(NULL, NULL);

    MPI_Comm_rank(MPI_COMM_WORLD, &PID);
    MPI_Comm_size(MPI_COMM_WORLD, &PCOUNT);

    if (PID == 0) { // jestem procesem głównym
        int vectorSize;
        std::cout << "Podaj rozmiar wektorow: ";
        std::cin >> vectorSize;
        mainProcess(PCOUNT, vectorSize);
    }
    else { // jestem procesem roboczym
        workerProcess(PID, PCOUNT);
    }

    MPI_Finalize();

    return 0;
}
