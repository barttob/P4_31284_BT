#include <iostream>
#include <omp.h>
#include <cmath>

int main() {
    const int N = 2; 
    double x[N] = { 5, 8 };

    double len = 0.0;

#pragma omp parallel num_threads(4) default(shared)
    {
        double local_sum = 0.0;
#pragma omp sections nowait
        {
#pragma omp section
            {
                printf("Sections - Thread %d working...\n", omp_get_thread_num());
                local_sum += x[0] * x[0];
            }
#pragma omp section
            {
                printf("Sections - Thread %d working...\n", omp_get_thread_num());
                local_sum += x[1] * x[1];
            }
        }
#pragma omp critical
        {
            len += local_sum;
        }
    }

    len = std::sqrt(len);

    std::cout << "Vector length: " << len << std::endl;

    return 0;
}
