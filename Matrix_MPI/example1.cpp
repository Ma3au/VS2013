//#include "mpi.h"
//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <math.h>
//#include <iostream>
//
//using namespace std;
//
////-----------функции вывода вспомогательные
//void printmatrix(double** a, int n, int count)
//{
//	for (int i = 0; i < count; i++){
//		for (int j = 0; j < n; j++){
//			cout << a[i][j] << ' ';
//		}
//		cout << '\n';
//	}
//}
//
//
//void printvector(double *l, int count)
//{
//	for (int i = 0; i < count; i++)
//		printf("l[%d] = %5.2f\n", i, l[i]);
//	printf("\n");
//}
//
//
////---------------------------
//int main(int argv, char* argc[]){
//	int rank, size;
//	int count = 10;
//	double t1, t2;
//	mpi_status status;
//	mpi_init(&argv, &argc);
//
//	mpi_comm_size(mpi_comm_world, &size);
//	mpi_comm_rank(mpi_comm_world, &rank);
//
//	mpi_bcast(&count, 1, mpi_int, 0, mpi_comm_world);
//	double temp;
//	int maxcol;
//	double maxvalue;
//	double *trx = new double[count];
//	int numb;
//	int* ind = new int[count];
//	for (int i = 0; i < count; i++)
//		ind[i] = i;
//	int n = count / size;
//	double** a = new double*[count];
//	for (int i = 0; i < count; i++)
//		a[i] = new double[n];
//
//	double*b = new double[count];
//	for (int i = 0; i < count; i++) b[i] = rand() % 100 + 1;
//	srand(time(null) + rank);
//	for (int i = 0; i < count; i++)
//		for (int j = 0; j < n; j++)
//			a[i][j] = rand() % 400 + 1;
//	int recv = 0;
//	double* l = new double[count];
//	double* cfs = new double[count];
//	double orb = b[0];
//	//if(rank == 0) printf("%f",orb);
//
//
//	//mpi_bcast(b,count,mpi_double,size - 1,mpi_comm_world);
//	//printvector(count,b);
//	if(rank == 0)printmatrix(a, count, n);
//	mpi_barrier(mpi_comm_world);
//	if (rank == 1)printmatrix(a, count, n);
//	mpi_barrier(mpi_comm_world);
//
//	//-------------------------
//	t1 = mpi_wtime();
//	for (int p = 0; p < size; p++)
//	{
//		if (p == rank)
//		{
//
//			for (int k = 0; k<n; k++)
//			{
//				maxvalue = a[n*p + k][k];
//				maxcol = n*p + k;
//				//поиск главного элемента
//				for (int i = n*p + k + 1; i < count; i++)
//					if (abs(a[i][k]) > abs(maxvalue)) { maxvalue = a[i][k]; maxcol = i; }
//				for (int i = 0; i < n; i++)
//				{
//					temp = a[n*p + k][i];
//					a[n*p + k][i] = a[maxcol][i];
//					a[maxcol][i] = temp;
//				}
//
//				if (maxcol != n*p + k){
//					temp = ind[n*p + k];
//					ind[n*p + k] = ind[maxcol];
//					ind[maxcol] = temp;
//					temp = b[n*p + k];
//					b[n*p + k] = b[maxcol];
//					b[maxcol] = temp;
//				}
//
//				//
//				for (int j = n*p + k; j < count - 1; j++){
//					l[j] = a[j + 1][k] / a[p*n + k][k];
//				}
//				for (int proc = p + 1; proc < size; proc++)
//				{
//					mpi_send(l, count, mpi_double, proc, 1, mpi_comm_world);
//					mpi_send(&k, 1, mpi_double, proc, 2, mpi_comm_world);
//					mpi_send(&maxcol, 1, mpi_int, proc, 22, mpi_comm_world);
//					mpi_send(ind, count, mpi_int, proc, 33, mpi_comm_world);
//
//				}
//				for (int i = n*p + k + 1; i < count; i++)
//				{
//					for (int j = k; j < n; j++){
//						a[i][j] = a[i][j] - a[n*p + k][j] * l[i - 1];
//						if (abs(a[i][j]) < 0.00001) a[i][j] = 0;
//					}
//					b[i] = b[i] - b[n*p + k] * l[i - 1];
//				}
//
//				if (p != size - 1){
//					for (int proc = p + 1; proc < size; proc++)
//						mpi_send(b, count, mpi_double, proc, 3, mpi_comm_world);
//				}
//
//
//			}
//		}
//		if (rank > p)
//		{
//			for (int k = 0; k<n; k++) {
//				mpi_recv(&numb, 1, mpi_double, p, 2, mpi_comm_world, &status);
//				mpi_recv(l, count, mpi_double, p, 1, mpi_comm_world, &status);
//				mpi_recv(b, count, mpi_double, p, 3, mpi_comm_world, &status);
//				mpi_recv(ind, count, mpi_int, p, 33, mpi_comm_world, &status);
//				mpi_recv(&maxcol, 1, mpi_int, p, 22, mpi_comm_world, &status);
//				for (int i = 0; i < n; i++){
//					temp = a[maxcol][i];
//					a[maxcol][i] = a[n*p + numb][i];
//					a[n*p + numb][i] = temp;
//				}
//				for (int i = numb + 1; i < count; i++)
//				{
//					for (int j = numb; j < n; j++)
//						a[i][j] = a[i][j] - a[k][j] * l[i - 1];//к потому что по диагонали
//					//b[i] = b[i] - b[k]*l[i - 1];
//				}
//			}
//
//		}
//
//	}
//
//	//-------так как последний свободный вектор, верный
//	mpi_bcast(b, count, mpi_double, size - 1, mpi_comm_world);
//
//	mpi_bcast(ind, count, mpi_int, size - 1, mpi_comm_world);
//	double* x = new double[count];
//	orb = b[0];
//	//-----обратный ход
//	for (int p = size - 1; p >= 0; p--)
//	{
//		if (p == rank)
//		{
//
//			x[n*p + n - 1] = b[n*p + n - 1] / a[n*p + n - 1][n - 1];
//
//			for (int i = n - 2; i >= 0; i--){
//				for (int j = i + 1; j < n; j++)
//					b[n*p + i] = b[n*p + i] - a[n*p + i][j] * x[n*p + j];
//
//				x[n*p + i] = b[n*p + i] / a[n*p + i][i];
//			}
//			for (int i = 0; i < n*p; i++)
//				for (int j = 0; j < n; j++)
//					b[i] = b[i] - a[i][j] * x[n*p + j];
//			if (p>0){
//				mpi_send(b, count, mpi_double, p - 1, 4, mpi_comm_world);
//				mpi_send(x, count, mpi_double, p - 1, 5, mpi_comm_world);
//			}
//
//		}
//		if (rank == p - 1)
//		{
//			mpi_recv(b, count, mpi_double, p, 4, mpi_comm_world, &status);
//			mpi_recv(x, count, mpi_double, p, 5, mpi_comm_world, &status);
//
//		}
//	}
//	t2 = mpi_wtime();
//	printf("time = %f\n", t2 - t1);
//	double ch = 0;
//
//	mpi_bcast(x, count, mpi_double, 0, mpi_comm_world);
//
//	//printvector(count,x);
//	for (int p = 0; p < size; p++){
//		if (rank == p) {
//			for (int i = 0; i < n; i++)
//				ch = ch + a[0][i] * x[n*p + i];
//			if (p != size - 1) mpi_send(&ch, 1, mpi_double, p + 1, 223, mpi_comm_world);
//			if (p == size - 1) printf("pogreshnost = %2.16f\n", orb - ch);
//		}
//		if (rank == p + 1)
//			mpi_recv(&ch, 1, mpi_double, p, 223, mpi_comm_world, &status);
//
//	}
//
//	//проверка 
//
//	//if(rank == 0)vyvod1(a, count, n);
//	//if(rank == 1)vyvod2(a, count, n);
//	//if(rank == 2)vyvod3(a, count, n);
//	//if(rank == 3)vyvod4(a, count, n);
//	mpi_finalize();
//}