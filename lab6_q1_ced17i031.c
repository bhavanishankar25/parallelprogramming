#include <mpi.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 

#define n 400000000
int main(int argc, char* argv[]) 
{ 

double start;
double end;
double maxend = 0;
double minstart = 10000;
double sum;

int processid;
int np;
int elements_per_process;
int n_elements_recieved;
int SIZE; 

MPI_Status status; 
MPI_Init(&argc, &argv); 
MPI_Comm_rank(MPI_COMM_WORLD, &processid); 
MPI_Comm_size(MPI_COMM_WORLD, &np);

elements_per_process = n / np;  
int count = 0;

SIZE = elements_per_process*np;
MPI_Barrier(MPI_COMM_WORLD);

start = MPI_Wtime();

if (processid == 0) 
{
int index, i; 
double* a = (double*) malloc(SIZE*sizeof(double));
double partial_sum;

for( i=0; i<n; i++)
	a[i] = (double) rand() + 0.00001534784187571354923459*(double) rand();

partial_sum=0;
sum=0; 
count=0;
int t;
t = (int) n%np;
if(np>1)
{
                printf("\nremaining elements %d\n",n%np);
			if(n%np != 0)
			{
			    
			    	for(i=np*t;i<n;i++)
			    	{ 
					partial_sum+=a[i];
			    	}
			}  


for ( i = 1; i < np; i++) 
{ 
				index = i * elements_per_process; 

				MPI_Send(&elements_per_process, 1, MPI_INT, i, 0,MPI_COMM_WORLD); 
				MPI_Send(&a[index],elements_per_process,MPI_DOUBLE, i, 1,MPI_COMM_WORLD);

} 


}
for (i = 0; i < elements_per_process; i++) 
	partial_sum+= a[i];

printf("\nMASTER RANK PROCESSED\n");
            
double csum;
 
  MPI_Reduce(&partial_sum, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
int k;

}
else { 
double p_sum;
double* a2 = (double*) malloc(SIZE*sizeof(double));
p_sum=0.0;
		MPI_Recv(&n_elements_recieved, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status); 
		MPI_Recv(a2, n_elements_recieved, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, &status);
		int i; 
		for ( i = 0; i < n_elements_recieved; i++) 
			p_sum+= a2[i];

  MPI_Reduce(&p_sum, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD); 
                printf("\nDATA SENT -%d\n",processid);
	}
MPI_Barrier(MPI_COMM_WORLD);
end = MPI_Wtime();
MPI_Finalize(); 

   if(minstart > start){
        minstart = start;
    }
    if(maxend < end){
        maxend = end;
    }
    if(processid == 0){
        printf("\nExec time %lf\n",end-start);
    }
	return 0; 
} 

