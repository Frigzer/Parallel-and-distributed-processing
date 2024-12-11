#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

#include "bariera.h"

//extern void bariera_init(int);
//extern void bariera(void);

#define LICZBA_W 4
//#define LICZBA_W 44

pthread_t watki[LICZBA_W];

typedef struct {

  int id;
  bariera_t *bariera1;
  bariera_t *bariera2;

} watek_data_t;

void *cokolwiek( void *arg);

int main( int argc, char *argv[] ){

  int i;
  watek_data_t dane_watkow[LICZBA_W];
  bariera_t bariera1, bariera2;

  // Inicjalizacja barier
  bariera_init(&bariera1, LICZBA_W);
  bariera_init(&bariera2, LICZBA_W);

  for(i=0; i<LICZBA_W; i++ ) {
    dane_watkow[i].id = i;
    dane_watkow[i].bariera1 = &bariera1;
    dane_watkow[i].bariera2 = &bariera2;
    pthread_create(&watki[i], NULL, cokolwiek, (void *)&dane_watkow[i]);
  }

  for(i=0; i<LICZBA_W; i++ ) pthread_join( watki[i], NULL );

  pthread_exit( NULL);  
}


void *cokolwiek( void *arg){

  watek_data_t *dane = (watek_data_t *)arg;
  int moj_id = dane->id;

  printf("przed bariera 1 - watek %d\n", moj_id);
  bariera(dane->bariera1);

  printf("przed bariera 2 - watek %d\n", moj_id);
  bariera(dane->bariera2);
  printf("po ostatniej barierze - watek %d\n", moj_id);

  pthread_exit( (void *)0);
}
