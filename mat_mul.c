#include<mpi.h>
#include<stdio.h>
#include <omp.h>
#include <stdlib.h>


int main()
{
    int p, q, r;
    printf("Enter the Order of Matrices p X r and r X p\n");
    scanf("%d %d %d",&p,&q,&r);
    int A[p][r];
    int B[r][q];
    int AB[p][q];
    int i,j,k;
    for(i=0;i<p;i++)
      for(j=0;j<r;j++)
        A[i][j] = rand()%1000;
    for(i=0;i<r;i++)
      for(j=0;j<q;j++)
        B[i][j] = rand()%1000;
    printf("Matrix A\n");
    for(i=0;i<p;i++){
      for(j=0;j<r;j++){
        printf("%d ",A[i][j]);
      }
      printf("\n");
    }
    printf("Matrix B\n");
    for(i=0;i<r;i++){
      for(j=0;j<q;j++){
        printf("%d ",B[i][j]);
      }
      printf("\n");
    }
#pragma omp parallel shared(p,q,r) private(i,j,k)
   {
#pragma omp for  schedule(static)
   for (i=0; i<p; i++){
      for (j=0; j<q; j++){
         AB[i][j]=0.;
         for (k=0; k<r; k++){
            AB[i][j] += ((A[i][k])*(B[k][j]));
         }
      }
   }
   }
   printf("Product Matrix AB\n");
   for(i=0;i<p;i++){
     for(j=0;j<q;j++){
       printf("%d ",AB[i][j]);
     }
     printf("\n");
   }
   return 0;
}
/*
   Number of processes (world_size) should evenly divide both p,q and r.
*/
/*#define ORDER 100*/
/*Maximum Order of Matrix*/
/*int main(int argc, char** argv){
    MPI_Init(NULL, NULL);
    int world_size;
    int rank;
    int A[ORDER][ORDER];
    int B[ORDER][ORDER];
    int AB[ORDER][ORDER];
    int temp_A[ORDER][ORDER];
    int temp_B[ORDER][ORDER];
    int p,q,r;/* p,q,r are dimensions of matrices, implies order p*q and q*r */
  /*  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, rank);
    int num_rows_per_process = p/world_size;
    if(rank == 0){
      printf("Enter the dimensions of matrices P, Q and R\n");
      scanf("%d %d %d",&p,&q,&r);
    }
    MPI_Bcast(&p, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&q, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&r, 1, MPI_INT, 0, MPI_COMM_WORLD);
    /* Initialize all matrix with zeroes*/
    /*int i,j;
    for(i=0;i<ORDER;i++){
      for(j=0;j<ORDER;j++){
        A[i][j] = 0;
        B[i][j] = 0;
        AB[i][j] = 0;
        temp_A[i][j] = 0;
        temp_B[i][j] = 0;
      }
    }
    /*Read Matrices and scatter to processes*/
    /*if(rank == 0){
      printf("Enter Matrix A\n");
      int i,j;
      for(i=0;i<p;i++){
        for(j=0;j<q;j++){
          printf("Enter element %d, %d\n",i,j);
          scanf("%d",&temp[i][j]);
        }
      }
    }
    /* Each Process Receives the chunk of mat A which is to be multiplied
      MPI_Scatter copies respective chunks in 'A' of each Process
    */
/*    MPI_Scatter(temp,num_rows_per_process*ORDER,MPI_INT,A,num_rows_per_process*ORDER,MPI_INT,0,MPI_COMM_WORLD);

    /*Read Matrice B and Broadcast to processes*/
  /*  if(rank == 0){
      printf("Enter Matrix B\n");
      int i,j;
      for(i=0;i<q;i++){
        for(j=0;j<r;j++){
          printf("Enter element %d, %d\n",i,j);
          scanf("%d",&temp_B[i][j]);
        }
      }
    }
}*/
