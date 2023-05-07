#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <omp.h>

double length(const std::vector<int>& v) {
    double sum = 0;
    for (int i = 0; i < v.size(); i++) {
        sum += v[i] * v[i];
    }
    return std::sqrt(sum);
}

void fill_vector(std::vector<int>& v) {
    std::srand(std::time(nullptr));
    for (int i = 0; i < v.size(); i++) {
        v[i] = std::rand() % 11;
    }
}

void sequential() {
    std::vector<int> v(10000);
    fill_vector(v);
    auto start = std::chrono::steady_clock::now();
    double len = length(v);
    auto end = std::chrono::steady_clock::now();
    std::cout << "Sequential time: " << std::chrono::duration<double>(end - start).count() << " s\n";
}

void parallel() {
    std::vector<int> v(10000);
    fill_vector(v);
    auto start = std::chrono::steady_clock::now();
    double len = 0;
#pragma omp parallel for reduction(+:len)
    for (int i = 0; i < v.size(); i++) {
        len += v[i] * v[i];
    }
    len = std::sqrt(len);
    auto end = std::chrono::steady_clock::now();
    std::cout << "Parallel time: " << std::chrono::duration<double>(end - start).count() << " s\n";
}

int main() {
    sequential();
    parallel();
    return 0;
}
