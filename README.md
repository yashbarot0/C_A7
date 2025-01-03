# Finite Difference Heat Equation Solver (Single and Parallel Implementation)

## Overview
This project solves the heat equation using the finite difference method in C. Two versions are implemented:
- **Single Process Implementation:** Solves the heat equation using a single process.
- **Parallel Process Implementation:** Solves the heat equation using two parallel processes with shared memory and semaphores.

## Files Included
- `finite_diff_single.c`: C code for the single process implementation.
- `finite_diff_parallel.c`: C code for the parallel process implementation.
- `Makefile`: Build instructions for compiling and running both versions.
- `solution.csv`: Output file for the single process version.
- `parallel_solution.csv`: Output file for the parallel version.

## Compilation and Execution
### Using Makefile (Recommended)
```bash
make
make run_single   # To run the single process version
make run_parallel # To run the parallel process version
```

### Manual Compilation (If Needed)
```bash
gcc -o finite_diff_single finite_diff_single.c -lm
gcc -o finite_diff_parallel finite_diff_parallel.c -lm -lpthread
```

### Running Manually
```bash
./finite_diff_single
./finite_diff_parallel
```

## Output
- The console will display the execution time for both versions.
- Results will be saved in `solution.csv` (single) and `parallel_solution.csv` (parallel).

## How It Works
- **Single Process:** Iteratively solves the heat equation using the finite difference method.
- **Parallel Process:** The grid is split between two processes using `fork()` and shared memory (`mmap`). Synchronization is achieved using semaphores.

## Troubleshooting
- If you experience a **segmentation fault**, verify the grid size (`NX`) and time step (`T_FINAL`).
- Reduce the grid size for faster testing.

## Cleaning Up
```bash
make clean
```
This removes the compiled binaries and CSV output files.

