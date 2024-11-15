#include<stdio.h>
#include<pthread.h>
#include<math.h>
#include<stdlib.h>

pthread_mutex_t mx = PTHREAD_MUTEX_INITIALIZER;

double funkcja ( double x );

double calka_sekw(double a, double b, double dx);

double calka_zrownoleglenie_petli(double a, double b, double dx, int l_w);

static int l_w_global=0;

static double a_global;
static double b_global;
static double dx_global;
static int N_global;

void* calka_fragment_petli_w(void* arg_wsk);

double calka_zrownoleglenie_petli(double a, double b, double dx, int l_w){

  int N = ceil((b-a)/dx);
  double dx_adjust = (b-a)/N;

  a_global = a;
  b_global = b;
  dx_global = dx;
  l_w_global = l_w;
  N_global = N;

  printf("Obliczona liczba trapezów: N = %d, dx_adjust = %lf\n", N, dx_adjust);
  //printf("a %lf, b %lf, n %d, dx %.12lf (dx_adjust %.12lf)\n", a, b, N, dx, dx_adjust);


  // tworzenie struktur danych do obsługi wielowątkowości
  pthread_t *watki = malloc(l_w * sizeof(pthread_t));
  int indeksy[l_w];

  for (int i=0; i<l_w; i++) {
    indeksy[i] = i;
  }

  // tworzenie wątków
  for (int i=0; i<l_w; i++) {
    pthread_create(&watki[i], NULL, calka_fragment_petli_w, &indeksy[i]);
  }

  // oczekiwanie na zakończenie pracy wątków
  double calka_local = 0.0;
  void* bufor;
  for (int i=0; i<l_w; i++) {
    pthread_join(watki[i], &bufor);
    calka_local += *((double*)bufor);
    free(bufor);
  }

  free(watki);

  return(calka_local);
}

void* calka_fragment_petli_w(void* arg_wsk){

  int my_id = *((int*) arg_wsk);

  double a, b, dx; // skąd pobrać dane a, b, dx, N, l_w ? 
  int N, l_w;      // wariant 1 - globalne

  a = a_global;
  b = b_global;
  dx = dx_global;
  N = N_global;
  l_w = l_w_global;

  // a = a_global; // itd. itp. - wartości globalne nadaje calka_zrownoleglenie_petli

  // dekompozycja cykliczna
  int my_start = my_id;
  int my_end = N;
  int my_stride = l_w;

  // dekompozycja blokowa
  //int my_start = my_id * ceil((double) N/l_w);
  //int my_end = (my_id+1) * ceil((double) N/l_w);
  //int my_stride = 1;

  if (my_end > N) my_end=N;

  // something else ? (dekompozycja blokowo-cykliczna)

  printf("\nWątek %d: my_start %d, my_end %d, my_stride %d\n", 
	 my_id, my_start, my_end, my_stride);


  int i;
  double *calka = malloc(sizeof(double));
  for(i=my_start; i<my_end; i+=my_stride){

    double x1 = a + i*dx;
    *calka += 0.5*dx*(funkcja(x1)+funkcja(x1+dx));
    //printf("i %d, x1 %lf, funkcja(x1) %lf, całka = %.15lf\n", 
    //	   i, x1, funkcja(x1), calka);

  }
 
 pthread_exit(calka);
}

