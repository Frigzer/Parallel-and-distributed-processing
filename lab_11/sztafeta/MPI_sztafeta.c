#include <stdlib.h>
#include<stdio.h>
#include<math.h>

#include "mpi.h"

int main( int argc, char** argv ){

  int rank, size, source, dest, data = 0;
  MPI_Status status;

  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank );
  MPI_Comm_size( MPI_COMM_WORLD, &size );

  dest = (rank + 1) % size;
  source = (rank - 1 + size) % size;

  if(size>1){
    
    if( rank > 0){
      
      MPI_Recv( &data, 1, MPI_INT, source, 0, MPI_COMM_WORLD, &status );
      printf("Proces %d odebrał liczbę %d od procesu %d\n", rank, data, source);

    }

    data += 1;

    if( rank < size ){
      
      MPI_Send( &data, 1, MPI_INT, dest, 0, MPI_COMM_WORLD );
      printf("Proces %d wysłał liczbę %d do procesu %d\n", rank, data, dest);
    }

    if ( rank == 0 ){
      
      MPI_Recv( &data, 1, MPI_INT, source, 0, MPI_COMM_WORLD, &status );
      printf("Proces %d odebrał liczbę %d od procesu %d\n", rank, data, source);
    }
  }
  MPI_Finalize();
  return(0);
}
