#include <chrono>
#include <cstdio>
#include <fstream>

int main(){
    auto start = std::chrono::steady_clock::now();

    std::fstream fs ("test.txt", std::fstream::in | std::fstream::out);
    fs.close();

    auto end = std::chrono::steady_clock::now();

    printf("Czas trwania: %llu\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

    return 0;
}