#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define NX 4000
#define T_FINAL 0.2
#define PI 3.141592653589793

int main() {
    const double dx = 1.0 / NX;
    const double dt = 0.5 * dx * dx;
    const int NT = (int)(T_FINAL / dt);

    double *u_old = malloc((NX + 1) * sizeof(double));
    double *u_new = malloc((NX + 1) * sizeof(double));

    if (u_old == NULL || u_new == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initial conditions
    for (int i = 0; i <= NX; ++i) {
        double x = i * dx;
        u_old[i] = sin(PI * x);
    }

    // Boundary conditions
    u_old[0] = u_old[NX] = 0.0;

    clock_t start = clock();

    // Time-stepping loop
    for (int t = 0; t < NT; ++t) {
        for (int i = 1; i < NX; ++i) {
            u_new[i] = 0.5 * (u_old[i + 1] + u_old[i - 1]);
        }

        // Boundary conditions
        u_new[0] = u_new[NX] = 0.0;

        // Swap pointers
        double *temp = u_old;
        u_old = u_new;
        u_new = temp;
    }

    clock_t end = clock();
    double elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", elapsed_time);

    // Output for visualization
    FILE *file = fopen("solution.csv", "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }

    for (int i = 0; i <= NX; ++i) {
        fprintf(file, "%f,%f\n", i * dx, u_old[i]);
    }
    fclose(file);

    // Cleanup
    free(u_old);
    free(u_new);

    return 0;
}
