#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "mpi.h"

#define SCALAR double
//#define SCALAR float

#ifndef M_PI // standardy C99 i C11 nie wymagają definiowania stałej M_PI
#define M_PI (3.14159265358979323846)
#endif

int main( int argc, char** argv ){ // program obliczania przybliżenia PI za pomocą wzoru Leibniza
                  // PI = 4 * ( 1 - 1/3 + 1/5 - 1/7 + 1/9 - 1/11 + itd. )
  
  int rank, size;
  MPI_Status status;

  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank ); 
  MPI_Comm_size( MPI_COMM_WORLD, &size );
  
  int max_liczba_wyrazow=0;

  if(rank == 0){
    printf("Podaj maksymalną liczbę wyrazów do obliczenia przybliżenia PI\n");
    scanf("%d", &max_liczba_wyrazow);
  }

  MPI_Bcast(&max_liczba_wyrazow, 1, MPI_INT, 0, MPI_COMM_WORLD);

  //  double t = MPI_Wtime();

 // wzór: PI/4 = 1 - 1/3 + 1/5 - 1/7 + 1/9 itd. itp.  

  int glob_rozm_bloku = ceil((double)max_liczba_wyrazow / (double)size);

  int moj_poczatek = rank * glob_rozm_bloku;
  int moj_skok = 1;
  int moj_koniec = (rank == -1) ? max_liczba_wyrazow : moj_poczatek + glob_rozm_bloku;

  SCALAR suma_plus=0.0;
  SCALAR suma_minus=0.0;
  int i=0;
  for(i=moj_poczatek; i<moj_koniec; i+=moj_skok){  
    int j = 1 + 4*i; 
    suma_plus += 1.0/j;
    suma_minus += 1.0/(j+2.0);
    //printf("PI obliczone: %20.15lf, aktualna poprawka: %20.15lf\n",
    //  	 4*(suma_plus-suma_minus), 4.0/j-4.0/(j+2.0));
  }
  double pi_lokalne = suma_plus-suma_minus;
  double pi_suma = 0.f;
  MPI_Reduce(&pi_lokalne, &pi_suma, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

  //  t = MPI_Wtime() - t;
  if(rank == 0){
    double pi_approx = pi_suma * 4.f;
    printf("PI obliczone: \t\t\t%20.15lf\n", pi_approx);
    printf("PI z biblioteki matematycznej: \t%20.15lf\n", M_PI);
  }
  //  printf("Czas obliczeń: %lf\n", t);
  MPI_Finalize();
}


