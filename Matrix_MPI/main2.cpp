//#include <iostream>
//#include <time.h>
//#include <vector>
//
//#include "mpi.h"
//
//using namespace std;
//
//void out_matrix(vector <vector<double> > matrix, vector<double> B)
//{
//	// Вывод системы уравнений
//	cout << "\nСистема уравнений:\n";
//	for (int i = 0; i < matrix.size(); i++)
//	{
//		for (int j = 0; j < matrix[i].size(); j++)
//		{
//			if (j != 0 && matrix[i][j] >= 0)
//				cout << " +";
//			cout << " " << matrix[i][j] << 'x' << j + 1;
//		}
//		cout << " = " << B[i] << endl;
//	}
//}
//
//double random(const int min, const int max)
//{
//	if (min == max)
//		return min;
//	return min + rand() % (max - min);
//}
//
//int main(int argc, char* argv[])
//{
//	setlocale(LC_ALL, "RUS");
//	
//	const int size = 1000;
//
//	int size_proc, rank;
//	MPI_Status status;
//	MPI_Request request;
//
//	MPI_Init(&argc, &argv);
//	MPI_Comm_size(MPI_COMM_WORLD, &size_proc);
//	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//	double t = clock();
//
//	int num_iter = size / size_proc ;
//	int	first_iter = rank * num_iter;
//	int	last_iter = first_iter + num_iter;
//	
//	vector<vector<double> > matrix(size, vector<double>(size));
//	vector<double> B(size);
//	vector<vector<double> > segment(num_iter, vector<double>(size));
//
//	// Заполняем матрицу коэффициентов и B
//	if (rank == 0){
//		for (int i = 0; i < size; i++)
//		{
//			for (int j = 0; j < size; j++)
//				matrix[i][j] = random(0, 100);
//			B[i] = random(0, 100);
//		}
//		copy(matrix.begin(), matrix.begin() + num_iter, segment.begin());
//		for (int i = 1; i < size_proc; i++){
//			//MPI_Send(&matrix[i*num_iter], num_iter, MPI_VECTOR, i, 1, MPI_COMM_WORLD);// , &request);
//			MPI_Send(&B[0], size, MPI_DOUBLE, i, 2, MPI_COMM_WORLD);//, &request);
//		}
//	}
//	else {
//		//MPI_Recv(&segment[0], num_iter, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, &status);
//		MPI_Recv(&B[0], size, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD, &status);
//	}
//
//	//MPI_Barrier(MPI_COMM_WORLD);
//	///*
//
//
//
//	//// Вычисление обратной матрицы
//
//	//// Создание и заполнение единичной матрицы
//	//vector <vector<double> > E(size, vector<double>(size));
//	//for (int i = 0; i < size; i++)
//	//{
//	//for (int j = 0; j < size; j++)
//	//{
//	//if (i == j) E[i][j] = 1.0;
//	//else E[i][j] = 0.0;
//	//}
//	//}
//
//	////Трансформация исходной матрицы в верхнетреугольную
//	//for (int k = 0; k < size; k++){
//	//if (matrix[k][k] == 0){
//	//bool changed = false;
//
//	//for (int i = k + 1; i < size; i++){
//	//if (matrix[i][k] != 0){
//	//swap(matrix[k], matrix[i]);
//	//swap(E[k], E[i]);
//	//changed = true;
//	//break;
//	//}
//	//}
//
//	//if (!changed)
//	//return -1;
//	//}
//
//	//double div = matrix[k][k];
//
//
//	//for (int j = 0; j < size; j++){
//	//matrix[k][j] /= div;
//	//E[k][j] /= div;
//	//}
//
//	//for (int i = k + 1; i < size; i++){
//	//double multi = matrix[i][k];
//
//	//for (int j = 0; j < size; j++){
//	//matrix[i][j] -= multi * matrix[k][j];
//	//E[i][j] -= multi * E[k][j];
//	//}
//	//}
//	//}
//
//
//	////Формирование единичной матрицы из исходной
//	////и обратной из единичной
//	//for (int k = size - 1; k > 0; k--){
//	//for (int i = k - 1; i > -1; i--){
//	//double multi = matrix[i][k];
//
//	//for (int j = 0; j < size; j++){
//	//matrix[i][j] -= multi * matrix[k][j];
//	//E[i][j] -= multi * E[k][j];
//	//}
//	//}
//	//}
//
//
//	//matrix = E;
//	//*/
//
//
//	//// Матрица-столбец неизвестных X и вычисление окончательного результата
//	//
//	//vector<double> X(num_iter);
//	//for (int i = 0; i < num_iter; i++){
//	//	X[i] = 0;
//	//	for (int j = 0; j < size; j++)
//	//		X[i] += segment[i][j] * B[j];
//	//}
//
//	//if (rank == 0)
//	//	cout << "\nThe system of equations:";
//
//	for (int i = 0; i < size_proc; i++){
//		if (rank == i){
//			for (int i = 0; i < num_iter; i++)
//				cout << "\nx" << i + 1 << " = " << B[i];
//		}
//		//MPI_Barrier(MPI_COMM_WORLD);
//	}
//
//	//MPI_Barrier(MPI_COMM_WORLD);
//	MPI_Finalize();
//
//	//// Вывод окончательного результата
//	if (rank == 0){
//		cout << "\n\nThe time spent on computation: " << t << "s.";
//
//		cout << endl;
//		system("pause");
//	}
//	return 0;
//
//}
//
