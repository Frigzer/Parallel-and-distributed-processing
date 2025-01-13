#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "mpi.h"

#define NAME_LEN 50

typedef struct {
  int id;
  float value;
  char name[NAME_LEN];

} CustomStruct;

void process_data(CustomStruct *data, int rank) {
    switch (rank) {
        case 0:
            data->value *= 2.0;
            break;
        case 1:
            data->id += 10;
            break;
        case 2:
            for (int i = 0; i < strlen(data->name); i++) {
                if (data->name[i] >= 'a' && data->name[i] <= 'z') {
                    data->name[i] = data->name[i] - 'a' + 'A';
                }
            }
            break;
        case 3:
            data->value -= 1.0;
            break;
        default:
            data->id += 1;
            break;
    }
}

int main(int argc, char **argv){

  srand((unsigned int)time(NULL));

  int rank, size, source, dest, position, buffer_size = 0, temp_size = 0;
  char *buffer;

  MPI_Status status;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  dest = rank + 1;
  source = rank - 1;

  if( size > 1 ){

    CustomStruct data;

    if( rank == 0 ){

      CustomStruct dataset[] =
      {
        {0, (float)(rand() % 100) / 10.0, "Anastazja"},
        {1, (float)(rand() % 100) / 10.0, "Alojzy"},
        {2, (float)(rand() % 100) / 10.0, "Klementyna"},
        {3, (float)(rand() % 100) / 10.0, "Sebastian"},
        {4, (float)(rand() % 100) / 10.0, "Gerbert"}
      };

      int num_structs = sizeof(dataset) / sizeof(CustomStruct);

      for(int i=0; i<num_structs; i++){

        MPI_Pack_size(1, MPI_INT, MPI_COMM_WORLD, &temp_size);
        buffer_size += temp_size;
        MPI_Pack_size(1, MPI_FLOAT, MPI_COMM_WORLD, &temp_size);
        buffer_size += temp_size;
        MPI_Pack_size(NAME_LEN, MPI_CHAR, MPI_COMM_WORLD, &temp_size);
        buffer_size += temp_size;

        buffer = malloc(buffer_size);
        position = 0;

        MPI_Pack(&dataset[i].id, 1, MPI_INT, buffer, buffer_size, &position, MPI_COMM_WORLD);
        MPI_Pack(&dataset[i].value, 1, MPI_FLOAT, buffer, buffer_size, &position, MPI_COMM_WORLD);
        MPI_Pack(dataset[i].name, NAME_LEN, MPI_CHAR, buffer, buffer_size, &position, MPI_COMM_WORLD);

        MPI_Send(buffer, position, MPI_PACKED, dest, 0, MPI_COMM_WORLD);
        printf("Proces 0 wysłał dane: id: %d, liczba: %.2f, imie: %s\n", dataset[i].id, dataset[i].value, dataset[i].name);

        free(buffer);

      }

      data.id = -1;
      MPI_Pack_size(1, MPI_INT, MPI_COMM_WORLD, &temp_size);
      buffer_size = temp_size;
      buffer = malloc(buffer_size);
      position = 0;

      MPI_Pack(&data.id, 1, MPI_INT, buffer, buffer_size, &position, MPI_COMM_WORLD);
      MPI_Send(buffer, position, MPI_PACKED, dest, 0, MPI_COMM_WORLD);

      free(buffer);

    }

    else if(rank < size){

      while(true){

        MPI_Probe(source, 0, MPI_COMM_WORLD, &status);

        MPI_Get_count(&status, MPI_PACKED, &buffer_size);

        buffer = malloc(buffer_size);

        MPI_Recv(buffer, buffer_size, MPI_PACKED, source, 0, MPI_COMM_WORLD, &status);

        position = 0;

        MPI_Unpack(buffer, buffer_size, &position, &data.id, 1, MPI_INT, MPI_COMM_WORLD);

        if (data.id == -1) {

          free(buffer);

          if (rank != size - 1) {
            MPI_Pack_size(1, MPI_INT, MPI_COMM_WORLD, &temp_size);
            buffer_size = temp_size;
            buffer = malloc(buffer_size);
            position = 0;
            MPI_Pack(&data.id, 1, MPI_INT, buffer, buffer_size, &position, MPI_COMM_WORLD);
            MPI_Send(buffer, position, MPI_PACKED, dest, 0, MPI_COMM_WORLD);
            free(buffer);
          }
          break;
        }


        MPI_Unpack(buffer, buffer_size, &position, &data.value, 1, MPI_FLOAT, MPI_COMM_WORLD);
        MPI_Unpack(buffer, buffer_size, &position, data.name, NAME_LEN, MPI_CHAR, MPI_COMM_WORLD);

        printf("Proces %d odebrał dane od procesu %d - id: %d, liczba: %.2f, imie: %s\n", rank, source, data.id, data.value, data.name);

        process_data(&data, rank);

        printf("Proces %d zmodyfikował dane - id: %d, liczba: %.2f, imie: %s\n", rank, data.id, data.value, data.name);

        if(rank != size-1){

          position = 0;
          MPI_Pack(&data.id, 1, MPI_INT, buffer, buffer_size, &position, MPI_COMM_WORLD);
          MPI_Pack(&data.value, 1, MPI_FLOAT, buffer, buffer_size, &position, MPI_COMM_WORLD);
          MPI_Pack(data.name, NAME_LEN, MPI_CHAR, buffer, buffer_size, &position, MPI_COMM_WORLD);

          MPI_Send(buffer, position, MPI_PACKED, dest, 0, MPI_COMM_WORLD);

          free(buffer);
        }

      }

    }

  }

  MPI_Finalize();
  return (0);

}
