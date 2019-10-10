#include<stdio.h>
#include<mpi.h>
int mpi_iittp_barrier_linear(){
  int rank;
  int num_proc;
  int i,dummy=-1;
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&num_proc);
  if(rank == 0){
    for(i=1;i<num_proc;i++){
      MPI_Recv(&dummy, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    for(i=0;i<num_proc;i++){
      MPI_Send(&dummy, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
    }
  }
  MPI_Send(&dummy, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
  MPI_Recv(&dummy, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  return 0;
}
int main(){
  MPI_Init(NULL, NULL);
  int rank;
  int num_proc;
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&num_proc);
  printf("Process %d hits the Barrier\n",rank);
	mpi_iittp_barrier_linear();
  printf("Process %d after Barrier\n",rank);
	MPI_Finalize();

}
