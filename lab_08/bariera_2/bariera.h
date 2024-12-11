#include <pthread.h>
#include <stdio.h>

typedef struct {
    int liczba_watkow;     // Liczba wątków wymaganych do przejścia bariery
    int watki_na_barierze; // Licznik wątków, które dotarły do bariery
    pthread_mutex_t muteks; // Mutex do ochrony sekcji krytycznych
    pthread_cond_t warunek; // Zmienna warunku
} bariera_t;

void bariera_init(bariera_t*, int);
void bariera(bariera_t*);
