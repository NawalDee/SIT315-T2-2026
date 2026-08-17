# Parallel Matrix Multiplication

## Overview
This project was developed for **SIT315 – Concurrent and Distributed Programming**.

The project implements matrix multiplication using three different approaches:

- Sequential implementation
- Parallel implementation using C++ `std::thread`
- OpenMP implementation

The purpose of this project is to compare the performance of sequential and parallel programming by measuring execution time using different matrix sizes and thread counts.

## Files

- `sequential.cpp` – Sequential matrix multiplication
- `parallel.cpp` – Parallel matrix multiplication using `std::thread`
- `openmp.cpp` – OpenMP implementation
- `TaskM2.T1P.pdf` – Project report

## Compilation

### Sequential

```bash
g++ sequential.cpp -o sequential
./sequential
```

### Parallel

```bash
g++ -std=c++11 parallel.cpp -o parallel
./parallel
```

### OpenMP (macOS)

```bash
clang++ -Xpreprocessor -fopenmp openmp.cpp \
-I/usr/local/opt/libomp/include \
-L/usr/local/opt/libomp/lib \
-lomp \
-o openmp

./openmp
```

## Features

- Matrix multiplication using three nested loops
- Parallel execution using `std::thread`
- Parallel execution using OpenMP
- Execution time measurement using `chrono`
- Correctness verification by comparing output files
- Performance evaluation with different matrix sizes and thread counts

## Author

**Nawal Bin Dawood**  
Student ID: **s223737376**
