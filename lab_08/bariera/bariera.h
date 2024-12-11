#include <pthread.h>
#include <stdio.h>

static int liczba_watkow;
static int watki_na_barierze;
static pthread_mutex_t muteks = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t warunek = PTHREAD_COND_INITIALIZER;

void bariera_init(int);
void bariera();
