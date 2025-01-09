#include <stdlib.h>
#include<stdio.h>
#include<math.h>

#include "mpi.h"

int main( int argc, char** argv ){ 
  
  int rank, ranksent, size, source, dest, tag, i; 
  char hostname[256], hostname_recv[256];
  MPI_Status status;
  
  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank ); 
  MPI_Comm_size( MPI_COMM_WORLD, &size );
  
  

  if(size>1){
    gethostname( hostname, 256 );
    
    if( rank != 0 ){ dest=0; tag=0; 
      
      MPI_Send( &rank, 1, MPI_INT, dest, 0, MPI_COMM_WORLD );
      MPI_Send( hostname, 256, MPI_CHAR, dest, 1, MPI_COMM_WORLD );

    } else {
      
      for( i=1; i<size; i++ ) { 
	
	MPI_Recv( &ranksent, 1, MPI_INT, MPI_ANY_SOURCE, 
		  0, MPI_COMM_WORLD, &status );
        MPI_Recv( hostname_recv, 256, MPI_CHAR, status.MPI_SOURCE,
                  1, MPI_COMM_WORLD, &status );
	printf("Dane od procesu o randze (status.MPI_SOURCE ->) %d: %d (i=%d), nazwa hosta: %s\n", 
	       status.MPI_SOURCE, ranksent, i, hostname_recv );
      }
      
    }

  }
  else{
        gethostname( hostname, 256 );
	printf("Pojedynczy proces o randze: %d, nazwa hosta: %s (brak komunikatów)\n", rank, hostname);
  }

  
  MPI_Finalize(); 
  
  return(0);

}

