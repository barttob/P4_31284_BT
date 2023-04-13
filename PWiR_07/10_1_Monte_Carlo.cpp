#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <thread>
#include <vector>
#include <atomic>

const int num_points = 1000000;
std::atomic_int num_inside_circle(0);

void compute_pi(int thread_num) {
    int thread_num_points = num_points / std::thread::hardware_concurrency();
    int thread_num_inside_circle = 0;
    std::srand(std::time(nullptr) + thread_num);

    for (int i = 0; i < thread_num_points; i++) {
        double x = ((double) std::rand() / RAND_MAX) * 2 - 1;
        double y = ((double) std::rand() / RAND_MAX) * 2 - 1;
        if (std::pow(x, 2) + std::pow(y, 2) <= 1) {
            thread_num_inside_circle++;
        }
    }

    num_inside_circle += thread_num_inside_circle;
}

int main() {
    std::vector<std::thread> threads;

    for (int i = 0; i < std::thread::hardware_concurrency(); i++) {
        threads.emplace_back(compute_pi, i);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    double pi = 4.0 * num_inside_circle / num_points;
    std::cout << "Approximate value of Pi: " << pi << std::endl;

    return 0;
}