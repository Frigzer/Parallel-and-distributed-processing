#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define LICZBA_W_MAX 4

void *funkcja_w( void *arg_wsk)
{
  int moj_arg;
  moj_arg = *( (int *) arg_wsk );
  pthread_t moj_id = pthread_self();
  printf("Watek otrzymal argument %d. Wartosc ID watku wynosi: %lu\n", moj_arg, (unsigned long)moj_id);
  
  return(NULL);
}

int main(int argc, char *argv[]) {
  int i;
  pthread_t watki[LICZBA_W_MAX];
  int p = LICZBA_W_MAX;
  int indeksy[LICZBA_W_MAX];
  for (i = 0; i < p; i++) indeksy[i] = i;
  for (i = 0; i < p; i++)
    pthread_create(&watki[i], NULL, funkcja_w, (void *) &indeksy[i]);
  for (i = 0; i < p; i++) pthread_join( watki[i], NULL);
  return 0;
}
