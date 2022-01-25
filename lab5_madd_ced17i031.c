#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define rows 5000
#define columns 5000

#define MASTER 0
#define master 1
#define worker 2

int main(int argc, char *argv[]) {

        int i, j, rowperwroker, nextrarows, final, root;

        MPI_Status status;

        // initialise the MPI environment argc, argv
        MPI_Init(&argc, &argv);

        // Get the number of processors
        int total_proc;
        MPI_Comm_size(MPI_COMM_WORLD, &total_proc);

        // Get the rank of the process
        int rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        double time1=MPI_Wtime();

        if(rank == MASTER)
        {
                double **MA, **MB, **MC;

                // initialize matrix A
                MA = (double **)malloc(sizeof(double *)*rows);
                for(i=0; i<rows; ++i)
                {
                        *(MA + i) = (double *)malloc(sizeof(double)*columns);
                        for(j=0; j<columns; ++j)
                                *(*(MA + i)+j) = random()%100;
                }

                // initialize matrix B
                MB = (double **)malloc(sizeof(double *)*rows);
                for(i=0; i<rows; ++i)
                {
                        *(MB + i) = (double *)malloc(sizeof(double)*columns);
                        for(j=0; j<columns; ++j)
                                *(*(MB + i)+j) = random()%100;
                }

                // initialize matrix C
                MC = (double **)malloc(sizeof(double *)*rows);
                for(i=0; i<rows; ++i)
                        *(MC + i) = (double *)malloc(sizeof(double)*columns);

                // send the respective rows of MA, MB to corresponding processes
                rowperwroker = rows/(total_proc-1);
                nextrarows = rows%(total_proc-1);

                for(final=1; final<total_proc; ++final)
                {
                        for(j=0; j<rowperwroker; ++j)
                        {
                                MPI_Send(*(MA + (final-1)*rowperwroker + j), columns, MPI_DOUBLE, final, master, MPI_COMM_WORLD);
                                MPI_Send(*(MB + (final-1)*rowperwroker + j), columns, MPI_DOUBLE, final, master, MPI_COMM_WORLD);
                        }
                }

                for(i=rows-nextrarows; i<rows; ++i)
                        for(j=0; j<columns; ++j)
                                *(*(MC + i)+j) = *(*(MA + i)+j) + *(*(MB + i)+j);

                for(root=1; root<total_proc; ++root)
                {
                        for(j=0; j<rowperwroker; ++j)
                                MPI_Recv(*(MC + (root-1)*rowperwroker + j), columns, MPI_DOUBLE, root, worker, MPI_COMM_WORLD, &status);
                }
                double time2=MPI_Wtime();
                printf("%f ",time2-time1);

        }

        else if(rank > MASTER)
        {
                rowperwroker = rows/(total_proc-1);

                double **MA = (double **)malloc(sizeof(double *)*rowperwroker);
                double **MB = (double **)malloc(sizeof(double *)*rowperwroker);
                for(i=0; i<rowperwroker; ++i)
                {
                        *(MA + i) = (double *)malloc(sizeof(double)*columns);
                        MPI_Recv(*(MA + i), columns, MPI_DOUBLE, MASTER, master, MPI_COMM_WORLD, &status);
                        *(MB + i) = (double *)malloc(sizeof(double)*columns);
                        MPI_Recv(*(MB + i), columns, MPI_DOUBLE, MASTER, master, MPI_COMM_WORLD, &status);
                }

                for(i=0; i<rowperwroker; ++i)
                        for(j=0; j<columns; ++j)
                                *(*(MA + i) + j) += *(*(MB + i) + j);

                for(i=0; i<rowperwroker; ++i)
                        MPI_Send(*(MA + i), columns, MPI_DOUBLE, MASTER, worker, MPI_COMM_WORLD);
        }
        // Finalize the MPI environment
        MPI_Finalize();
        return 0;
}