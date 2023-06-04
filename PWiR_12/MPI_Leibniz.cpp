#include <iostream>
#include <cmath>
#include <mpi.h>

double calculatePI(int rank, int size, int numSteps) {
    double sum = 0.0;

    for (int i = rank; i < numSteps; i += size) {
        double x = (i + 0.5) / numSteps;
        double term = 4.0 / (1.0 + x * x);
        sum += term;
    }

    return sum;
}

int main(int argc, char** argv) {
    int numSteps = 1000000;  // Liczba podziałów
    double pi = 0.0;
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Obliczanie sumy lokalnej w każdym procesie
    double localSum = calculatePI(rank, size, numSteps);

    // Sumowanie częściowych wyników z wszystkich procesów
    MPI_Reduce(&localSum, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // Wyświetlanie wyniku w głównym procesie
    if (rank == 0) {
        pi /= numSteps;
        std::cout << "Liczba PI obliczona metoda Leibniza: " << pi << std::endl;
    }

    MPI_Finalize();

    return 0;
}
