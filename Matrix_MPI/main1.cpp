#include <iostream>
#include <time.h>
#include <vector>
#include <mpi.h>

using namespace std;

void out_matrix(vector <vector<double> > matrix, vector<double> B)
{
	// Вывод системы уравнений
	cout << "\nСистема уравнений:\n";
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
		{
			if (j != 0 && matrix[i][j] >= 0)
				cout << " +";
			cout << " " << matrix[i][j] << 'x' << j + 1;
		}
		cout << " = " << B[i] << endl;
	}
}


double random(const int min, const int max)
{
	if (min == max)
		return min;
	return min + rand() % (max - min);
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "RUS");
	const int size = 10;

	int size_proc, rank;
	MPI_Status status;
	MPI_Request request;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size_proc);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	const int num_iter = 2;
	int	first_iter = rank * num_iter;
	int	last_iter = first_iter + num_iter;

	double t = clock();

	double matrix[size][size];
	double B[size];
	double E[size][size];
	double segment[num_iter][size];
	double mini_segmentM[num_iter];
	double mini_segmentE[num_iter];

	double div;
	//	 Заполняем матрицу коэффициентов и B
	if (rank == 0){
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++){
				matrix[i][j] = random(0, 100);
				if (i == j) E[i][j] = 1.0;
				else E[i][j] = 0.0;
			}
			B[i] = random(0, 100);
		}
		cout << "MY MATRIX!!!!\n";
		for (int i = 0; i < size; i++){
			for (int j = 0; j < size; j++){
				cout << matrix[i][j] << ' ';
			}
			cout << endl;
		}
	}
	/*
	MPI_Scatter(matrix, num_iter * size, MPI_DOUBLE, segment, num_iter*size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	for (int i = 1; i < size_proc; i++){
	if (rank == i){
	cout << "Proc num:" << rank << '\n';
	for (int i = 0; i < num_iter; i++){
	for (int j = 0; j < size; j++){
	cout << segment[i][j] << ' ';
	}
	cout << '\n';
	}
	}
	MPI_Barrier(MPI_COMM_WORLD);

	}
	*/
	MPI_Barrier(MPI_COMM_WORLD);

	for (int i = 0; i < size; i++){
		MPI_Scatter(matrix[i], num_iter, MPI_DOUBLE, mini_segmentM, num_iter, MPI_DOUBLE, 0, MPI_COMM_WORLD);
		//if (rank != 0){
		for (int k = 0; k < size_proc; k++){
			if (rank == k){
				for (int j = 0; j < num_iter; j++){
					cout << mini_segmentM[j] << "   ";
				}
			}
		}
		cout << endl;
		MPI_Barrier(MPI_COMM_WORLD);
	}

	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();
	return 0;
}

//
//	MPI_Barrier(MPI_COMM_WORLD);
//
//	out_matrix(matrix, B);
//
//	double t = clock();
//
//
//
//
//	 Вычисление обратной матрицы
//
//	Трансформация исходной матрицы в верхнетреугольную
//int k = 0;
//	for (int k = 0; k < size; k++)
//	{
//		if (rank == 0)
//		{
//			if (matrix[k][k] == 0){
//				bool changed = false;
//				for (int i = k + 1; i < size; i++){
//					if (matrix[i][k] != 0){
//						swap(matrix[k], matrix[i]);
//						swap(E[k], E[i]);
//						changed = true;
//						break;
//					}
//				}
//				if (!changed)
//					return -1;
//			}
//			double div = matrix[k][k];
//		}
//		MPI_Barrier(MPI_COMM_WORLD);
//		MPI_Scatter(matrix[k], num_iter, MPI_DOUBLE, mini_segmentM, num_iter, MPI_DOUBLE, 0, MPI_COMM_WORLD);
//		MPI_Scatter(E[k], num_iter, MPI_DOUBLE, mini_segmentE, num_iter, MPI_DOUBLE, 0, MPI_COMM_WORLD);
//		MPI_Bcast(&div, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
//
//		if (rank != 0){
//			for (int j = 0; j < num_iter; j++){
//				mini_segmentM[j] /= div;
//				mini_segmentE[j] /= div;
//			}
//		}
//		MPI_Barrier(MPI_COMM_WORLD);
//		MPI_Gather(mini_segmentM, num_iter, MPI_DOUBLE, matrix, num_iter, MPI_DOUBLE, 0, MPI_COMM_WORLD);
//		MPI_Gather(mini_segmentE, num_iter, MPI_DOUBLE, E, num_iter, MPI_DOUBLE, 0, MPI_COMM_WORLD);
//
//	}
//	MPI_Barrier(MPI_COMM_WORLD);
//	cout << endl << endl << endl;
//	if (rank == 0){
//		for (int i = 0; i < size; i++){
//			for (int j = 0; j < size; j++){
//				cout << matrix[i][j] << ' ';
//			}
//			cout << '\n';
//		}
//	}
//		MPI_Bcast(&matrix, size * size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
//		MPI_Bcast(&E, size * size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
//		MPI_Barrier(MPI_COMM_WORLD);
//		for (int i = k + 1; i < size; i++){
//			double multi = matrix[i][k];
//			if (first_iter <= i && i < last_iter){
//				for (int j = 0; j < size; j++){
//					matrix[i][j] -= multi * matrix[k][j];
//					E[i][j] -= multi * E[k][j];
//				}
//			}
//		}
//		for (int i = 1; i < size_proc; i++){
//			MPI_Bcast(&matrix[first_iter], size * num_iter, MPI_DOUBLE, i, MPI_COMM_WORLD);
//		}
//		/*
//		MPI_Gather(matrix[first_iter], num_iter, MPI_DOUBLE,
//		matrix[last_iter], size * size, MPI_Datatype rtype,
//		int root, MPI_Comm comm);
//		*/
//	}
//	
//	MPI_Finalize();
//		
//		Формирование единичной матрицы из исходной
//		и обратной из единичной
//		for (int k = size - 1; k > 0; k--){
//			for (int i = k - 1; i > -1; i--){
//				double multi = matrix[i][k];
//	
//				for (int j = 0; j < size; j++){
//					matrix[i][j] -= multi * matrix[k][j];
//					E[i][j] -= multi * E[k][j];
//				}
//			}
//		}
//	
//	
//	
//		 Матрица-столбец неизвестных X и вычисление окончательного результата
//	
//		vector<double> X(size);
//		for (int i = 0; i < size; i++){
//			X[i] = 0;
//			for (int j = 0; j < size; j++)
//				X[i] += matrix[i][j] * B[j];
//		}
//	
//	
//		 Вывод окончательного результата
//		cout << "\nThe system of equations:";
//		for (int i = 0; i < size; i++)
//			cout << "\nx" << i + 1 << " = " << X[i];
//	
//		t = (clock() - t) / 1000;
//		cout << "\n\nThe time spent on computation: " << t << "s.";
//	
//	
//			MPI_Finalize();
//	
//		cout << endl;
//		system("pause");*/
//	
//		return 0;
//}