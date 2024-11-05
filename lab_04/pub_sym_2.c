#include<stdlib.h>
#include<stdio.h>
#include <time.h>
#include<pthread.h>
#include <unistd.h>

#define ILE_MUSZE_WYPIC 3

struct struktura_t { 
  int l_wkf;
  pthread_mutex_t *tab_kuf; 
  int l_kr;
  pthread_mutex_t *tab_kran;  
};
struct struktura_t pub_wsk;

char *piwa[] = {"Guinness", "Żywiec", "Heineken", "Okocim", "Karlsberg", "Perła", "Łomża"};

void * watek_klient (void * arg);

int main( void ){
  pthread_t *tab_klient;
  int *tab_klient_id;

  int l_kl, l_kf, l_kr, i;

  printf("\nLiczba klientow: "); scanf("%d", &l_kl);

  printf("\nLiczba kufli: "); scanf("%d", &l_kf);
  pub_wsk.l_wkf = l_kf;

  //printf("\nLiczba kranow: "); scanf("%d", &l_kr);
  pub_wsk.l_kr = sizeof(*piwa) - 1;

  tab_klient = (pthread_t *) malloc(l_kl*sizeof(pthread_t));
  tab_klient_id = (int *) malloc(l_kl*sizeof(int));
  for(i=0;i<l_kl;i++) tab_klient_id[i]=i;

  pub_wsk.tab_kuf = (pthread_mutex_t *) malloc(l_kf*sizeof(pthread_mutex_t));
  for(i=0;i<l_kf;i++) pthread_mutex_init(&pub_wsk.tab_kuf[i], NULL);

  pub_wsk.tab_kran = (pthread_mutex_t *) malloc(l_kr*sizeof(pthread_mutex_t));
  for(i=0;i<l_kr;i++) pthread_mutex_init(&pub_wsk.tab_kran[i], NULL);

  printf("\nOtwieramy pub (simple)!\n");
  printf("\nLiczba wolnych kufli %d\n", l_kf); 

  for(i=0;i<l_kl;i++){
    pthread_create(&tab_klient[i], NULL, watek_klient, &tab_klient_id[i]); 
  }
  for(i=0;i<l_kl;i++){
    pthread_join( tab_klient[i], NULL);
  }
  printf("\nZamykamy pub!\n");

}


void * watek_klient (void * arg_wsk){

  int moj_id = * ((int *)arg_wsk);

  int i, i_wypite, kran, kufel, result;

  int ile_musze_wypic = ILE_MUSZE_WYPIC;

  long int wykonana_praca = 0;
  
  printf("\nKlient %d, wchodzę do pubu\n", moj_id); 
    
  for(i_wypite=0; i_wypite<ile_musze_wypic; i_wypite++){

    printf("\nKlient %d, wybieram kufel\n", moj_id);
    int success = 0;
    do {
      for (kufel = 0; kufel < pub_wsk.l_wkf; kufel++) {
        if (pthread_mutex_trylock(&pub_wsk.tab_kuf[kufel]) == 0) {
          success = 1;
          break;
        }
        else {
          wykonana_praca++;
        }
      }
    } while (success == 0);

    printf("\nKlient %d, wybrałem kufel %d\n", moj_id, kufel);
    

    printf("\nKlient %d, wybieram kran\n", moj_id); 

    success = 0;
    do {
      for (kran = 0; kran < pub_wsk.l_kr; kran++) {
        if (pthread_mutex_trylock(&pub_wsk.tab_kran[kran]) == 0) {
          success = 1;
          break;
        } 
        else {
          wykonana_praca++;
        }
      }
    } while (success == 0);

    printf("\nKlient %d, nalewam z kranu %d (%s)\n", moj_id, kran, piwa[kran]);
    usleep(1000);
    pthread_mutex_unlock(&pub_wsk.tab_kran[kran]);

    printf("\nKlient %d, pije piwo %s z kufla %d\n", moj_id, piwa[kran], kufel);

    usleep(1000);

    pthread_mutex_unlock(&pub_wsk.tab_kuf[kufel]);

    printf("\nKlient %d, odkladam kufel %d\n", moj_id, kufel); 
  }

  return(NULL);
} 
