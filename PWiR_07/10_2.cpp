#include <iostream>
#include <vector>
#include <thread>
#include <atomic>

const int num_threads = std::thread::hardware_concurrency();

void sum_partial(const std::vector<int>& arr, int start, int end, std::atomic_int& result) {
    int partial_sum = 0;
    for (int i = start; i < end; i++) {
        partial_sum += arr[i];
    }
    result += partial_sum;
}

int sum(const std::vector<int>& arr) {
    std::vector<std::thread> threads;
    std::atomic_int result(0);
    int chunk_size = arr.size() / num_threads;

    for (int i = 0; i < num_threads; i++) {
        int start = i * chunk_size;
        int end = (i == num_threads - 1) ? arr.size() : start + chunk_size;
        threads.emplace_back(sum_partial, std::ref(arr), start, end, std::ref(result));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return result;
}

int main() {
    std::vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int s = sum(arr);
    std::cout << "Sum of array elements: " << s << std::endl;
    return 0;
}
