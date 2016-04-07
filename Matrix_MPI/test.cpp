//#include <iostream>
//#include <time.h>
//#include <vector>
//
//#include "mpi.h"
//
//using namespace std;
//
//int main(int argc, char* argv[])
//{
//	setlocale(LC_ALL, "RUS");
//
//	int size_proc, rank;
//	MPI_Status status;
//	MPI_Request request;
//
//	MPI_Init(&argc, &argv);
//	MPI_Comm_size(MPI_COMM_WORLD, &size_proc);
//	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//	int k = 0;
//	if (rank == 0){
//		k = 2;
//		
//	}
//	MPI_Bcast(&k, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
//	cout << k;
//
//	MPI_Finalize();
//	return 0;
//}