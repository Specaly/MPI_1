#include "mpi.h"
#include <stdio.h>
#include <string.h>
#include<math.h>
#include<time.h>
//--------------------------------------------------------------------
//此段为题一
#define N 1000
int main(int argc, char** argv)
{
	int data[N];
	int myid, numprocs;
	double local=0.0;
	double total,bg,ed;
	for (int i = 0; i < N; i++)
	{
		data[i] = i * (i + 1);
	}
	float sum = 0;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	bg = clock();
	for (int i = myid; i < N; i = i + numprocs)
	{
		local += sqrt(data[i]);
	}
	MPI_Reduce(&local, &total, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	if (myid == 0)
	{
		ed = clock();
		printf("The result is %f\n Runtime is %f ms\n", total,ed-bg);
	}
	MPI_Finalize();
}
//------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
//此段为题二
/*int main(int argc, char** argv)
{
	double bg, ed;
	int myid, numprocs,i;
	float temp=0.0,sum=0.0,x,dx,part;
	MPI_Status Status;
	dx = 90.0 / N;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs); --numprocs;
	bg = clock();
	if (myid != 0)
	{
		for (i = myid-1; i < N; i=i+numprocs)
		{
			x = 10 + i * dx + dx / 2;
			temp += x * x * x * dx;
		}
		MPI_Send(&temp, 1, MPI_FLOAT, 0, 1, MPI_COMM_WORLD);
	}
	else
	{
		for (int source = 1; source < numprocs+1; source++)
		{
			MPI_Recv(&part, 1, MPI_FLOAT, source, 1, MPI_COMM_WORLD, &Status);
			sum = sum + part;
		}
		ed = clock();
		printf("Runtime is %f ms\n", ed - bg);
		printf("The result is %f \n", sum);
	}
	MPI_Finalize();
}
*/
//------------------------------------------------------------------------