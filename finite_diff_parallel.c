#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>

#define NX 1000
#define T_FINAL 0.1
#define PI 3.141592653589793

sem_t *semaphore;

void solve_half(double *u, double dx, double dt, int start, int end, int NT) {
    for (int t = 0; t < NT; ++t) {
        for (int i = start; i < end; ++i) {
            if (i > 0 && i < NX) {
                u[i] = 0.5 * (u[i + 1] + u[i - 1]);
            }
        }
        sem_post(&semaphore[start == 1 ? 0 : 1]);  
        sem_wait(&semaphore[start == 1 ? 1 : 0]);  
    }
}

int main() {
    const double dx = 1.0 / NX;
    const double dt = 0.5 * dx * dx;
    const int NT = (int)(T_FINAL / dt);

    double *u = mmap(NULL, (NX + 1) * sizeof(double), PROT_READ | PROT_WRITE,
                      MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    semaphore = mmap(NULL, 2 * sizeof(sem_t), PROT_READ | PROT_WRITE,
                      MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    for (int i = 0; i < 2; ++i) sem_init(&semaphore[i], 1, 0);

    for (int i = 0; i <= NX; ++i) {
        double x = i * dx;
        u[i] = sin(PI * x);
    }

    pid_t pid = fork();

    clock_t start_time = clock();

    if (pid == 0) {
        solve_half(u, dx, dt, 1, NX/2, NT);
        exit(0);
    } else if (pid > 0) {
        solve_half(u, dx, dt, NX/2, NX, NT);
        wait(NULL);
    } else {
        perror("Fork failed");
        exit(1);
    }

    clock_t end_time = clock();
    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", elapsed_time);

    FILE *file = fopen("parallel_solution.csv", "w");
    for (int i = 0; i <= NX; ++i) {
        fprintf(file, "%f,%f\n", i * dx, u[i]);
    }
    fclose(file);

    munmap(u, (NX + 1) * sizeof(double));
    munmap(semaphore, 2 * sizeof(sem_t));
    return 0;
}
