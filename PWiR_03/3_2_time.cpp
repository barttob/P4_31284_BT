#include <iostream>
#include <chrono>
#include <cstdio>

int fib(int n)
{
    if (n <= 1)
        return n;
    return fib(n - 1) + fib(n - 2);
}

int main(){
    auto start = std::chrono::steady_clock::now();

    std::cout << fib(40) << std::endl;

    auto end = std::chrono::steady_clock::now();

    printf("Czas trwania: %llu\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

    return 0;
}