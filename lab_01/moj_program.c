#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#include"pomiar_czasu.h"

const int liczba = 1;

int main(){

  double a, b, c;
  int i,j,k,l;

  k = -50000;
  inicjuj_czas();
  for(i=0;i<liczba;i++){

    printf("%d ",k+i);

  }
  printf("\n");

  printf("Czas wykonania %d operacji wejscia/wyjscia: \n",liczba);
  drukuj_czas();

  a = 1.000001;
  double t1 = czas_zegara();
  double t2 = czas_CPU();
  for(i=0;i<liczba;i++){

    a = 1.000001*a+0.000001; 

  }
  t1 = czas_zegara() - t1;
  t2 = czas_CPU() - t2;
  printf("Wynik operacji arytmetycznych: %lf\n", a);
  printf("Czas wykonania %d operacji arytmetycznych: \n",liczba);
  printf("czas CPU \t= %lf",t2);
  printf("\nczas zegarowy \t= %lf",t1);
  printf("\n");

}
