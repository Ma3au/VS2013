#include <iostream>
#include <time.h>
#include <vector>

using namespace std;

double random(const int min, const int max)
{
	if (min == max)
		return min;
	return min + rand() % (max - min);
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "RUS");
	const int size = 10000;

	vector<vector<double> > matrix(size, vector<double>(size));
	vector<double> B(size);
	vector<vector<double> > segment(50, vector<double>(size));

	// Заполняем матрицу коэффициентов и B

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			matrix[i][j] = random(0, 100);
		B[i] = random(0, 100);
	}
	copy(matrix.begin(), matrix.begin() + 50, segment.begin());


	// Матрица-столбец неизвестных X и вычисление окончательного результата

	cout << endl;
	system("pause");
	return 0;

}

