#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mpi.h"

#define NAME_LEN 50

typedef struct {
  int id;
  float value;
  char name[NAME_LEN];

} CustomStruct;

int main(int argc, char **argv){

  srand((unsigned int)time(NULL));
  float random_value = ((float)rand() / RAND_MAX) * (1.0 - 0.1) + 0.1;

  int rank, size, source, dest, position, buffer_size = 0, temp_size = 0;
  char *buffer;

  MPI_Status status;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  dest = (rank + 1) % size;
  source = (rank - 1 + size) % size;

  if( size > 1 ){

    CustomStruct data;

    if( rank == 0 ){

      data.id = 0;
      data.value = 3.14;
      strcpy(data.name, "Adam");
      //data.name = "Adam";

      MPI_Pack_size(1, MPI_INT, MPI_COMM_WORLD, &temp_size);
      buffer_size += temp_size;
      MPI_Pack_size(1, MPI_FLOAT, MPI_COMM_WORLD, &temp_size);
      buffer_size += temp_size;
      MPI_Pack_size(NAME_LEN, MPI_CHAR, MPI_COMM_WORLD, &temp_size);
      buffer_size += temp_size;

      buffer = malloc(buffer_size);

    }

    else{

      MPI_Probe(source, 0, MPI_COMM_WORLD, &status);

      MPI_Get_count(&status, MPI_PACKED, &buffer_size);

      buffer = malloc(buffer_size);

      MPI_Recv(buffer, buffer_size, MPI_PACKED, source, 0, MPI_COMM_WORLD, &status);

      position = 0;

      MPI_Unpack(buffer, buffer_size, &position, &data.id, 1, MPI_INT, MPI_COMM_WORLD);
      MPI_Unpack(buffer, buffer_size, &position, &data.value, 1, MPI_FLOAT, MPI_COMM_WORLD);
      MPI_Unpack(buffer, buffer_size, &position, data.name, NAME_LEN, MPI_CHAR, MPI_COMM_WORLD);

      printf("Proces %d odebrał dane od procesu %d - id: %d, liczba: %f, imie: %s\n", rank, source, data.id, data.value, data.name);

      data.id += 1;
      data.value += random_value;

    }
    if( rank < size-1 ){

      position = 0;
      MPI_Pack(&data.id, 1, MPI_INT, buffer, buffer_size, &position, MPI_COMM_WORLD);
      MPI_Pack(&data.value, 1, MPI_FLOAT, buffer, buffer_size, &position, MPI_COMM_WORLD);
      MPI_Pack(data.name, NAME_LEN, MPI_CHAR, buffer, buffer_size, &position, MPI_COMM_WORLD);

      MPI_Send(buffer, position, MPI_PACKED, dest, 0, MPI_COMM_WORLD);

      printf("Proces %d wysłał dane do procesu %d - id: %d, liczba: %f, imie: %s\n", rank, dest, data.id, data.value, data.name);

      free(buffer);
    }
  }

  MPI_Finalize();
  return (0);

}
