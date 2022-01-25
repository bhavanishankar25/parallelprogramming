#include<bits/stdc++.h>
#include<mpi.h>
#define MAX 1000000
#define N 1000
#define MASTER 0
using namespace std;
double v1[N][N],v2[N][N],v3[N][N],t1[N][N],t3[N][N];
int main()
{
  //clock_t tStart = clock();
  int rank,total,n_per_pro,i;
  double start;
  MPI_Init(NULL,NULL);
  MPI_Comm_size(MPI_COMM_WORLD,&total);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  if(rank==MASTER)
  {
    for(int i=0;i<N;i++)
      for(int j=0;j<N;j++)
        v1[i][j]=(double)rand()/(double)RAND_MAX*MAX;
    for(int i=0;i<N;i++)
      for(int j=0;j<N;j++)
        v2[i][j]=(double)rand()/(double)RAND_MAX*MAX;
    start=MPI_Wtime();
  }

  int begrow=rank*N/total;
  int lastrow=(rank+1)*N/total;
  lastrow=(lastrow>N)?N:lastrow;
  //printf("%d %d\n",begrow,lastrow);
  MPI_Scatter(v1, N*N/total, MPI_DOUBLE, t1[begrow], N*N/total,MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Bcast(v2,N*N,MPI_DOUBLE,MASTER,MPI_COMM_WORLD);
  MPI_Barrier(MPI_COMM_WORLD);
  for(int i=begrow;i<lastrow;i++)
  {
    for(int j=0;j<N;j++)
    {
      t3[i][j]=0;
      for(int k=0;k<N;k++)
        t3[i][j]+=t1[i][k]*v2[k][j];
    }
  }
  MPI_Gather (t3[begrow], N*N/total, MPI_DOUBLE, v3, N*N/total, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  if(rank==MASTER)
  {
    printf("%.6f\n", (double)(MPI_Wtime() - start));
  }
  MPI_Finalize();
  return 0;
}
