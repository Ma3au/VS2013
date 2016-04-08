//#include <iostream>
//#include <time.h>
//#include <vector>
////#include <mpi.h>
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
//	const int size = 200;
//
//	vector<vector<double> > matrix(size, vector<double>(size));
//	vector<double> B(size);
//
//	// Заполняем матрицу коэффициентов и B
//	for (int i = 0; i < size; i++)
//	{
//		for (int j = 0; j < size; j++)
//			matrix[i][j] = random(0, 100);
//		B[i] = random(0, 100);
//	}
//	//out_matrix(matrix, B);
//
//	double t = clock();
//
//
//
//	
//	// Вычисление обратной матрицы
//
//	// Создание и заполнение единичной матрицы
//	vector <vector<double> > E(size, vector<double>(size));
//	for (int i = 0; i < size; i++)
//	{
//		for (int j = 0; j < size; j++)
//		{
//			if (i == j) E[i][j] = 1.0;
//			else E[i][j] = 0.0;
//		}
//	}
//
//	//Трансформация исходной матрицы в верхнетреугольную
//	for (int k = 0; k < size; k++){
//		if (matrix[k][k] == 0){
//			bool changed = false;
//
//			for (int i = k + 1; i < size; i++){
//				if (matrix[i][k] != 0){
//					swap(matrix[k], matrix[i]);
//					swap(E[k], E[i]);
//					changed = true;
//					break;
//				}
//			}
//
//			if (!changed)
//				return -1;
//		}
//
//		double div = matrix[k][k];
//
//
//		for (int j = 0; j < size; j++){
//			matrix[k][j] /= div;
//			E[k][j] /= div;
//		}
//
//		for (int i = k + 1; i < size; i++){
//			double multi = matrix[i][k];
//
//			for (int j = 0; j < size; j++){
//				matrix[i][j] -= multi * matrix[k][j];
//				E[i][j] -= multi * E[k][j];
//			}
//		}
//	}
//
//
//	//Формирование единичной матрицы из исходной
//	//и обратной из единичной
//	for (int k = size - 1; k > 0; k--){
//		for (int i = k - 1; i > -1; i--){
//			double multi = matrix[i][k];
//
//			for (int j = 0; j < size; j++){
//				matrix[i][j] -= multi * matrix[k][j];
//				E[i][j] -= multi * E[k][j];
//			}
//		}
//	}
//
//
//	matrix = E;
//
//	
//	// Матрица-столбец неизвестных X и вычисление окончательного результата
//
//	vector<double> X(size);
//	for (int i = 0; i < size; i++){
//		X[i] = 0;
//		for (int j = 0; j < size; j++)
//			X[i] += matrix[i][j] * B[j];
//	}
//
//
//	// Вывод окончательного результата
//	cout << "\nThe system of equations:";
//	for (int i = 0; i < size; i++)
//		cout << "\nx" << i + 1 << " = " << X[i];
//
//	t = (clock() - t) / 1000;
//	cout << "\n\nThe time spent on computation: " << t << "s.";
//
//	cout << endl;
//	system("pause");
//	return 0;
//}
//
