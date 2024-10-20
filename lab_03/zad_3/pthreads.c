#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define LICZBA_W_MAX 2

typedef struct {
  int a;
  double b;
  double suma;
}struktura;

int zmienna_wspolna=0;

void *funkcja_w( void *arg_wsk)
{
  struktura s_lok = *((struktura *)arg_wsk);
  s_lok.b += s_lok.a;
  printf("watek: s_lok.a = %d, s_lok.b = %lf\n", s_lok.a, s_lok.b);
  struktura * s_wsk = (struktura *) arg_wsk;
  printf("zewn.: s_zewn.a = %d, s_zewn.b = %lf\n", s_wsk->a, s_wsk->b);
  s_wsk->suma = s_lok.a + s_lok.b;
  printf("Suma lokalna: %lf\n", s_wsk->suma);
  return(NULL);
}

int main(int argc, char *argv[]) {
  int i;
  pthread_t watki[LICZBA_W_MAX];
  int p = LICZBA_W_MAX;
  struktura struktury[LICZBA_W_MAX];
  for (i = 0; i < p; i++) 
  {
    (struktury[i]).a = i;
    (struktury[i]).b = i + 2.0;
    (struktury[i]).suma = 0.0;
  }
  double suma_calkowita = 0.0;
  for (i = 0; i < p; i++) {
    pthread_create(&watki[i], NULL, funkcja_w, (void *) &struktury[i]);
    
  }
  for (i = 0; i < p; i++) {
    pthread_join( watki[i], NULL);
    suma_calkowita += (struktury[i]).suma;
  }
  printf("Suma calkowita wyniosla: %lf\n", suma_calkowita);
  return 0;
}
