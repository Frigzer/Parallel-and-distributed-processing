#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define WYMIAR 10

int main ()
{
  double a[WYMIAR][WYMIAR];

  for(int i=0;i<WYMIAR;i++) for(int j=0;j<WYMIAR;j++) a[i][j]=1.02*i+1.01*j;

  // podwójna pętla - sekwencyjnie
  double suma=0.0;
  for(int i=0;i<WYMIAR;i++) {
    for(int j=0;j<WYMIAR;j++) {
      suma += a[i][j];
    }
  }
  
  printf("Suma wyrazów tablicy: %lf\n", suma);

  omp_set_nested(1);
  /*
  // podwójna pętla - docelowo równolegle
  double suma_parallel=0.0; int i,j;
//#pragma omp parallel for default(none) schedule(static, 2) reduction(+:suma_parallel) shared(a) private(j) ordered
  for(i=0;i<WYMIAR;i++) {
    int id_w = omp_get_thread_num();
    // #pragma omp ordered
#pragma omp parallel for default(none) schedule(dynamic) reduction(+:suma_parallel) shared(a, i) ordered// private(i)
    for(j=0;j<WYMIAR;j++) {
      suma_parallel += a[i][j];
      #pragma omp ordered
      // dla dekompozycji 1D
      printf("(%1d,%1d)-W_%1d ",i,j,omp_get_thread_num()); 
      // dla dekompozycji 2D
      //printf("(%1d,%1d)-W_%1d,%1d ",i,j,id_w,omp_get_thread_num()); 
    }
     #pragma omp ordered
    printf("\n");
  }
  */

// podwójna pętla - docelowo równolegle
  double suma_parallel=0.0; int i,j;
#pragma omp parallel for default(none) schedule(static) shared(a, suma_parallel) ordered private(i)
  for(j=0;j<WYMIAR;j++) {
    int id_w = omp_get_thread_num();
    double suma_lokalna = 0.0;
    // #pragma omp ordered
//#pragma omp parallel for default(none) schedule(dynamic) reduction(+:suma_parallel) shared(a>
    for(i=0;i<WYMIAR;i++) {
      suma_lokalna += a[i][j];
      #pragma omp ordered
      // dla dekompozycji 1D
      printf("(%1d,%1d)-W_%1d ",i,j,omp_get_thread_num()); 
      // dla dekompozycji 2D
      //printf("(%1d,%1d)-W_%1d,%1d ",i,j,id_w,omp_get_thread_num()); 
    }
    #pragma omp atomic
    suma_parallel += suma_lokalna;
    #pragma omp ordered
    printf("\n");
  }

  printf("Suma wyrazów tablicy równolegle: %lf\n", suma_parallel);

}
