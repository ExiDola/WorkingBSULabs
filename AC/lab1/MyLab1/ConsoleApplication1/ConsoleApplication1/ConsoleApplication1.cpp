//#include <stdio.h>
//#include "mpi.h"
//#include <sys\timeb.h>
//#include<random>
//#include <ctime>
//#include <iostream>
//using namespace std;
//
//void main(int argc, char** argv)
//{
//	int myrank;
//	MPI_Status status;
//	int L = 0;
//	int N = 0;
//	double testSize;
//	double* arrA = nullptr;
//	double* arrB = nullptr;
//	double* arrA1 = nullptr;
//	double* arrB1 = nullptr;
//	srand(time(NULL));
//
//	MPI_Init(&argc, &argv);    
//	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);   
//	MPI_Comm_size(MPI_COMM_WORLD, &N);
//	
//	if (myrank == 0)             
//	{
//		printf("Number of L: ");
//		scanf_s("%ld", &L);
//	}
//
//	MPI_Bcast(&L, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
//
//	testSize = L / N;
//	arrA = new double[L];
//	arrB = new double[L];
//	arrA1 = new double[L];
//	arrB1 = new double[L];
//
//	for (int i = 0; i < L; i++)
//	{
//		arrA[i] = (rand() % 20)/10 - 1;
//		arrB[i] = (rand() % 20)/10 - 1;
//	}
//
//	int* sendcounts = new int[N];
//	int* displs = new int[N];
//	int remainder = L % N;
//	int base = L / N;
//	int ost = L % N;
//
//	for (int i = 0; i < L; i++) {
//		sendcounts[i] = testSize;
//		if (ost!=0) {
//			sendcounts[i]++;
//			ost--;
//		}
//	}
//	displs[0] = 0;
//	for (int i = 1; i < L; i++) {
//		displs[i] = displs[i - 1] + sendcounts[i - 1];
//	}
//
//	MPI_Scatterv(&arrA[0], sendcounts, displs, MPI_DOUBLE, &arrA1[0], testSize, MPI_DOUBLE, 0, MPI_COMM_WORLD);
//	MPI_Scatterv(&arrB[0], sendcounts, displs, MPI_DOUBLE, &arrB1[0], testSize, MPI_DOUBLE, 0, MPI_COMM_WORLD);
//
//	double subMult = 0; 
//
//	for (int i = 0; i < testSize; i++) 
//	{
//		subMult += arrA1[i] * arrB1[i];
//	}
//
//	double ScalarSum = 0;
//
//	MPI_Reduce(&subMult, &ScalarSum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
//
//	if (myrank == 0)              
//	{
//		for (int i = 0; i < L; i++)
//		{
//			cout << arrA[i] << "  " << arrB[i] << endl;
//		}
//		cout << endl;
//		cout <<"Scalar Multiply: " << ScalarSum << endl;
//	}
//
//	MPI_Finalize();
//	delete[] arrA;
//	delete[] arrB;
//	return;
//}

	





//#include <iostream>
//#include <ctime>
//#include<iostream>
//#include <mpi.h>
//#include<random>
//using namespace std;
// 
//
//int main(int argc, char** argv) {
//    MPI_Status status;
//    MPI_Init(&argc, &argv);
//    setlocale(LC_ALL, "rus");
//    int myrank, size;
//    int testSize;
//    int N;
//    int L = 4;
//    int M = 5;
//    double* arrA = nullptr;
//    double* arrA1 = nullptr;
//    double* arrB = nullptr;
//    double* arrB1 = nullptr;
//    double* arrC = nullptr;
//    double* arrC1 = nullptr;
//    srand(time(NULL));
//    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
//    MPI_Comm_size(MPI_COMM_WORLD, &N);
//    
//    MPI_Bcast(&L, 1, MPI_INT, 0, MPI_COMM_WORLD);
//    MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);
//    testSize = L * M / N;
//    arrA = new double[L*M];
//    arrA1 = new double[L * M];
//    arrB = new double[L * M];
//    arrB1 = new double[L * M];
//    arrC = new double[L * M];
//    arrC1 = new double[L * M];
//
//    if (myrank == 0)
//    {
//        for (int i = 0; i < L * M;i++)
//        {
//            arrA[i] = rand() % 10;
//            arrB[i] = rand() % 10;
//        }
//        for (int i = 0; i < M; ++i)
//        {
//            for (int j = 0; j < L; ++j)
//                std::cout << arrA[i * L + j] << " ";
//            std::cout << endl;
//        }
//        cout << endl;
//        for (int i = 0; i < M; ++i)
//        {
//            for (int j = 0; j < L; ++j)
//                std::cout << arrB[i * L + j] << " ";
//            std::cout << endl;
//        }
//        cout << endl;
//    }
//
//    int* sendcounts = new int[N];
//    int* displs = new int[N];
//    int ost = L % N;
//    
//   	for (int i = 0; i < L; i++) {
//    	sendcounts[i] = testSize;
//    	if (ost!=0) {
//    		sendcounts[i]++;
//    		ost--;
//    	}
//   	}
//   	displs[0] = 0;
//   	for (int i = 1; i < L; i++) {
//   		displs[i] = displs[i - 1] + sendcounts[i - 1];
//   	}
//
//    MPI_Scatterv(&arrA[0], sendcounts, displs, MPI_DOUBLE, &arrA1[0], testSize, MPI_DOUBLE, 0, MPI_COMM_WORLD);
//    MPI_Scatterv(&arrB[0], sendcounts, displs, MPI_DOUBLE, &arrB1[0], testSize, MPI_DOUBLE, 0, MPI_COMM_WORLD);
//
//    for (int i = 0; i < L * M; i++)
//    {
//        arrC1[i] = arrA1[i] - arrB[i];
//    }
//
//    MPI_Gatherv(&arrC1[0], sendcounts[myrank], MPI_DOUBLE,&arrC[0],sendcounts,displs,MPI_DOUBLE,0, MPI_COMM_WORLD);
//
//    if (myrank == 0)
//    {
//        cout << endl;
//        cout << "A-B = " <<endl;
//        for (int i = 0; i < M; ++i)
//        {
//            for (int j = 0; j < L; ++j)
//                std::cout << arrC[i * L + j]<<" ";
//            std::cout << endl;
//        }
//    }
//    
//
//    MPI_Finalize();
//    delete[]arrA;
//    delete[]arrB;
//    delete[]arrC;
//    delete[]arrA1;
//    delete[]arrB1;
//    delete[]arrC1;
//    return 0;
//}




#include <iostream>
#include <ctime>
#include <cstdlib>
#include <mpi.h>
#include <stdio.h>

using namespace std;

int main(int argc, char** argv) {
    MPI_Status status;
    MPI_Init(&argc, &argv);
    setlocale(LC_ALL, "rus");
    int myrank, size;
    int testSize;
    int N;
    double* arrA = nullptr;
    double* arrB = nullptr;
    double* arrC = nullptr;
    const int k =1000;
    const int l = 1000 ;
    const int m = 1000;;
    double begnTime = 0;
    double endTime = 0;
    double firstCulc = 0;
    double endculc = 0;
    srand(time(NULL));
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &N);
    
    
    arrA = new double[k * l];
    arrC = new double[k * m];
    arrB = new double[l * m];

    if (myrank == 0)
    {
        begnTime = MPI_Wtime();
        for (int i = 0; i < k * l; i++)
        {
            arrA[i] = rand() % 10;
        }

        for (int i = 0; i < l * m; i++)
        {
            arrB[i] = rand() % 10;
        }

        /*cout << "Matrix A:" << endl;
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < l; j++) {
                cout << arrA[i * l + j] << " ";
            }
            cout << endl;
        }

        cout << "Matrix B:" << endl;
        for (int i = 0; i < l; i++) {
            for (int j = 0; j < m; j++) {
                cout << arrB[i * m + j] << " ";
            }
            cout << endl;
        }*/
    }

    MPI_Bcast(&arrB[0], l * m, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    int k1 = k / N;
    int ost = k % N;

    int* NumOfSend = new int[N];
    int* distance = new int[N];

    for (int i = 0; i < N; i++)
    {
        NumOfSend[i] = k1;
        if (ost != 0)
        {
            NumOfSend[i]++;
            ost--;
        }
        NumOfSend[i] *= l;
    }

    distance[0] = 0;
    for (int i = 1; i < N; i++)
    {
        distance[i] = distance[i - 1] + NumOfSend[i - 1];
    }

    double* C = new double[k * m];

    int* senderNum = new int[N];
    int* disples = new int[N];

    for (int i = 0; i < N; i++)
    {
        senderNum[i] = (NumOfSend[i] / l) * m;
    }
    disples[0] = 0;
    for (int i = 1; i < N; i++)
    {
        disples[i] = disples[i - 1] + senderNum[i - 1];
    }

    double* partA = new double[NumOfSend[myrank]];

    MPI_Scatterv(&arrA[0], NumOfSend, distance, MPI_DOUBLE, &partA[0], NumOfSend[myrank], MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double* partC = new double[NumOfSend[myrank] / l * m];

    MPI_Barrier(MPI_COMM_WORLD);
    firstCulc = MPI_Wtime();
    for (int i = 0; i < NumOfSend[myrank] / l; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            partC[i * m + j] = 0;
            for (int p = 0; p < l; ++p)
                partC[i * m + j] += partA[i * l + p] * arrB[p * m + j];
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);
    endculc = MPI_Wtime();

    MPI_Gatherv(&partC[0], senderNum[myrank], MPI_DOUBLE, &C[0], senderNum, disples, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (myrank == 0) 
    {
        endTime = MPI_Wtime();
        /*cout << "The result of multiply:" << endl;
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < m; j++) {
                cout << C[i * m + j] << " ";
            }
            cout << endl;
        }*/

        cout << "All programm working: " << endTime - begnTime<< "  seconds"<< endl;
        cout << "The multiply lasts:  " << endculc - firstCulc <<" seconds" << endl;

        delete[] arrA;
        delete[] arrB;
        delete[] arrC;
        delete[] C;
    }



    MPI_Finalize();
    return 0;
}

