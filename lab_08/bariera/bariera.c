#include "bariera.h"

void bariera_init(int l_w) {
    liczba_watkow = l_w;
}

void bariera() {
    pthread_mutex_lock(&muteks);
    watki_na_barierze++;

    if (watki_na_barierze == liczba_watkow) {
        pthread_cond_broadcast(&warunek);
        watki_na_barierze = 0;
    }
    else {
        pthread_cond_wait(&warunek, &muteks);
    }

    pthread_mutex_unlock(&muteks);
}
