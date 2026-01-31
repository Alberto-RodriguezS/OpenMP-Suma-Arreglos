#include <iostream>
#include <vector>
#include <omp.h>

#define N 100000000
#define chunk 10000
#define mostrar 10

void imprimeArreglo(float* d);

int main()
{
    bool debug_hilos = true;   // true para mostrar evidencia; false para sólo medir
    std::cout << "Sumando Arreglos en Paralelo!\n";

    std::vector<float> a(N), b(N), c_serial(N), c_par(N);
    int i;

    for (i = 0; i < N; i++)
    {
        a[i] = i * 10;
        b[i] = (i + 3) * 3;
    }

    int pedazos = chunk;

    std::cout << "Max threads (omp_get_max_threads): " << omp_get_max_threads() << std::endl;

        int hilos = 4;
    omp_set_num_threads(hilos);
    std::cout << "Threads fijados a: " << hilos << std::endl;

    // Serial
    double t0 = omp_get_wtime();
    for (i = 0; i < N; i++)
        c_serial[i] = a[i] + b[i];
    double t1 = omp_get_wtime();

    // Paralelo (sin prints dentro del loop para medir bien)
    double t2 = omp_get_wtime();
#pragma omp parallel for shared(a, b, c_par, pedazos) private(i) schedule(static, pedazos)
    for (i = 0; i < N; i++)
        c_par[i] = a[i] + b[i];
    double t3 = omp_get_wtime();

    std::cout << "Tiempo serial (s):   " << (t1 - t0) << std::endl;
    std::cout << "Tiempo paralelo (s): " << (t3 - t2) << std::endl;
    std::cout << "Speedup (serial/paralelo): " << (t1 - t0) / (t3 - t2) << std::endl;

    int N_demo = 1000;           // demo corta
    int pedazos_demo = 100;      // chunks visibles

    if (debug_hilos)
    {
        std::cout << "\n--- Evidencia de asignacion de chunks (demo) ---\n";

#pragma omp parallel for shared(pedazos_demo) schedule(static, pedazos_demo)
        for (int j = 0; j < N_demo; j++)
        {
            if (j % pedazos_demo == 0)
            {
                int tid = omp_get_thread_num();
#pragma omp critical
                std::cout << "Thread " << tid << " inicia en j=" << j << std::endl;
            }
        }
    }


    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo c (paralelo): " << std::endl;
    imprimeArreglo(c_par.data());

    return 0;
}

void imprimeArreglo(float* d)
{
    for (int x = 0; x < mostrar; x++)
        std::cout << d[x] << " - ";
    std::cout << std::endl;
}
