#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

#include"czytelnia.h"


/*** Implementacja procedur interfejsu ***/

int my_read_lock_lock(cz_t* cz_p){
  pthread_mutex_lock(&cz_p->muteks);
  if (cz_p->l_p > 0 || cz_p->l_o_p != 0) { 
    cz_p->l_o_c++;
    pthread_cond_wait(&cz_p->czytelnicy, &cz_p->muteks);
    cz_p->l_o_c--;
    pthread_cond_signal(&cz_p->czytelnicy);
  }
  cz_p->l_c++;
  pthread_mutex_unlock(&cz_p->muteks);
}


int my_read_lock_unlock(cz_t* cz_p){
  pthread_mutex_lock(&cz_p->muteks);
  cz_p->l_c--;
  if(cz_p->l_c == 0) pthread_cond_signal(&cz_p->pisarze);
 
  pthread_mutex_unlock(&cz_p->muteks);
}


int my_write_lock_lock(cz_t* cz_p){
  pthread_mutex_lock(&cz_p->muteks);
  if(cz_p->l_c + cz_p->l_p > 0) {
    cz_p->l_o_p++;
    pthread_cond_wait(&cz_p->pisarze, &cz_p->muteks);
    cz_p->l_o_p--;
  }
  cz_p->l_p++;
  pthread_mutex_unlock(&cz_p->muteks);
}


int my_write_lock_unlock(cz_t* cz_p){
  pthread_mutex_lock(&cz_p->muteks);
  cz_p->l_p--;
  if(cz_p->l_o_c != 0) {
    cz_p->l_o_c--;
    pthread_cond_signal(&cz_p->czytelnicy);
  }
  else {
    cz_p->l_o_p--;
    pthread_cond_signal(&cz_p->pisarze);
  }
  pthread_mutex_unlock(&cz_p->muteks);
}

void inicjuj(cz_t* cz_p){

  cz_p->l_p = 0;
  cz_p->l_c = 0;  

  cz_p->l_o_p = 0;
  cz_p->l_o_c = 0;

  pthread_mutex_init(&cz_p->muteks, NULL);
  pthread_cond_init(&cz_p->czytelnicy, NULL);
  pthread_cond_init(&cz_p->pisarze, NULL);
}

void czytam(cz_t* cz_p){

// wypisanie wartości zmiennych kontrolujących działanie: liczby czytelników i pisarzy
  printf("\t\t\t\t\tczytam:  l_c %d, l_p %d\n", cz_p->l_c, cz_p->l_p); 
// sprawdzenie warunku poprawności i ewentualny exit
// warunek:
  if( cz_p->l_p>1 || (cz_p->l_p==1 && cz_p->l_c>0) || cz_p->l_p<0 || cz_p->l_c<0 ) {
    printf("Blad: ....\n");
    exit(0);
  }

    usleep(rand()%3000000);
}

void pisze(cz_t* cz_p){

// wypisanie wartości zmiennych kontrolujących działanie: liczby czytelników i pisarzy
  printf("\t\t\t\t\tpisze:   l_c %d, l_p %d\n", cz_p->l_c, cz_p->l_p); 
// sprawdzenie warunku poprawności i ewentualny exit
  if( cz_p->l_p>1 || (cz_p->l_p==1 && cz_p->l_c>0) || cz_p->l_p<0 || cz_p->l_c<0 ) {
    printf("Blad: ....\n");
    exit(0);
  }

    usleep(rand()%3000000);
}


