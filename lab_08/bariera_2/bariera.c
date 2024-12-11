#include "bariera.h"

void bariera_init(bariera_t *bariera, int liczba_watkow) {

    bariera->liczba_watkow = liczba_watkow;
    bariera->watki_na_barierze = 0;
    pthread_mutex_init(&bariera->muteks, NULL);
    pthread_cond_init(&bariera->warunek, NULL);

}

void bariera(bariera_t *bariera) {

    pthread_mutex_lock(&bariera->muteks);

    bariera->watki_na_barierze++;

    if (bariera->watki_na_barierze == bariera->liczba_watkow) {

        bariera->watki_na_barierze = 0;
        pthread_cond_broadcast(&bariera->warunek);

    } else {
        
        pthread_cond_wait(&bariera->warunek, &bariera->muteks);

    }

    pthread_mutex_unlock(&bariera->muteks);
}
