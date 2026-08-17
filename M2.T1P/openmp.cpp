#include <iostream>
#include <ctime>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <chrono>
#include <omp.h>

using namespace std;

int main()
{
    int N;
    int numThreads;

    cout << "Enter matrix size: ";
    cin >> N;

    cout << "Enter number of threads: ";
    cin >> numThreads;

    vector<vector<int>> A(N, vector<int>(N));
    vector<vector<int>> B(N, vector<int>(N));
    vector<vector<int>> C(N, vector<int>(N, 0));

    srand(1);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }

    omp_set_num_threads(numThreads);

    auto start = chrono::high_resolution_clock::now();

    #pragma omp parallel for
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < N; k++)
            {
                C[i][j] = C[i][j] + (A[i][k] * B[k][j]);
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> time = end - start;

    cout << "Execution Time: " << time.count() << " seconds" << endl;

    ofstream file("openmp_output.txt");

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            file << C[i][j] << " ";
        }

        file << endl;
    }

    file.close();

    cout << "Matrix saved to openmp_output.txt" << endl;

    return 0;
}