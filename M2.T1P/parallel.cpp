#include <iostream>
#include <ctime>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <chrono>
#include <thread>

using namespace std;

void multiplyRows(
    const vector<vector<int>>& A,
    const vector<vector<int>>& B,
    vector<vector<int>>& C,
    int startRow,
    int endRow,
    int N)
{
    for (int i = startRow; i < endRow; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < N; k++)
            {
                C[i][j] = C[i][j] + (A[i][k] * B[k][j]);
            }
        }
    }
}

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

    vector<thread> threads;

    int rowsPerThread = N / numThreads;
    int startRow = 0;

    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < numThreads; i++)
    {
        int endRow;

        if (i == numThreads - 1)
        {
            endRow = N;
        }
        else
        {
            endRow = startRow + rowsPerThread;
        }

        threads.emplace_back(
    multiplyRows,
    cref(A),
    cref(B),
    ref(C),
    startRow,
    endRow,
    N
);

        startRow = endRow;
    }

    for (int i = 0; i < numThreads; i++)
    {
        threads[i].join();
    }

    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> time = end - start;

    cout << "Execution Time: " << time.count() << " seconds" << endl;

    ofstream file("parallel_output.txt");

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            file << C[i][j] << " ";
        }

        file << endl;
    }

    file.close();

    cout << "Matrix saved to parallel_output.txt" << endl;

    return 0;
}