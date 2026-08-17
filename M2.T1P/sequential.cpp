#include <iostream>
#include <ctime>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <chrono>

using namespace std;

int main()
{
    int N;

    cout << "Enter matrix size: ";
    cin >> N;

    // Create matrices
    vector<vector<int>> A(N, vector<int>(N));
    vector<vector<int>> B(N, vector<int>(N));
    vector<vector<int>> C(N, vector<int>(N, 0));

    // Fill A and B with random numbers
    srand(1);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }

    // Start timer
    auto start = chrono::high_resolution_clock::now();

    // Matrix multiplication
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

    // Stop timer
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> time = end - start;

    cout << "Execution Time: " << time.count() << " seconds" << endl;

    // Save result to file
    ofstream file("sequential_output.txt");

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            file << C[i][j] << " ";
        }

        file << endl;
    }

    file.close();

    cout << "Matrix saved to sequential_output.txt" << endl;

    return 0;
}