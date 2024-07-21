#include <iostream>
#include <fstream>
#include <chrono>
#include<random>
#include <ctime>
#include <omp.h>
using namespace std;

void remove(int* arr, int i, int length)
{
    arr[i] = arr[length - 1];
}

int* randomCyclicPermutuation(int length)
{
    int* result = new int[length]();
    int* unusedIndexes = new int[length - 1];

    for (int i = 0; i < length - 1; i++)
    {
        unusedIndexes[i] = i + 1;
    }
    int currentIndex = 0;
    std::random_device rd;
    std::mt19937_64 eng(rd());
#pragma omp parallel for
    for (int i = 0; i < length - 1; i++)
    {
        std::uniform_int_distribution<int> distr(0, length - 1-i);
        int r = distr(eng);
        //int r = rand() % (length - 1 - i);
        int nextInd = unusedIndexes[r];
#pragma omp critical
        {
            remove(unusedIndexes, r, length - 1 - i);
            result[currentIndex] = nextInd;
            currentIndex = nextInd;
        }
    }

    delete[] unusedIndexes;

    return result;
}

float benchmarkLatency(int sizeBytes, int iterations)
{
    int* array = randomCyclicPermutuation(sizeBytes / 4);
    int pointer = 0;

    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < iterations; i++)
    {
        pointer = array[pointer];
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);

    delete[] array;

    return static_cast<float>(duration.count()) / iterations;
}

int main()
{
    srand(time(0));
    ofstream fout("data.txt");
    //ofstream fout2("tinedata.txt");
    for (float i = 5000.0; i <= 20000000.0; i *= 1.2)
    {
        fout<< int(i)<<" "<< benchmarkLatency(int(i), 100000000) << endl;
    }

    return 0;
}