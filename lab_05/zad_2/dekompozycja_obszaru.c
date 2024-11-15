#include<stdio.h>
#include<pthread.h>
#include<math.h>

struct struktura {
  double id_struct;
  double a_struct;
  double b_struct;
  double dx_struct;
  double wynik_struct;
};

double funkcja ( double x );

double calka_sekw(double a, double b, double dx);

double calka_dekompozycja_obszaru(double a, double b, double dx, int l_w);

void* calka_podobszar_w(void* arg_wsk);

double calka_dekompozycja_obszaru(double a, double b, double dx, int l_w){


  //printf("a %lf, b %lf, dx %lf\n", a, b, dx);

  double calka_suma_local = 0.0;

  // tworzenie struktur danych do obsługi wielowątkowości
  pthread_t watki[l_w];
  struct struktura struktury[l_w];

  double zakres = (b-a)/l_w;

  for (int i=0; i<l_w; i++) {
    struktury[i].id_struct = i;
    struktury[i].a_struct = a + i * zakres;
    struktury[i].b_struct = a + (i + 1) * zakres;
    struktury[i].dx_struct = dx;
    struktury[i].wynik_struct = 0.0;
  }

  // tworzenie wątków
  for (int i=0; i<l_w; i++) {
    pthread_create(&watki[i], NULL, calka_podobszar_w, &struktury[i]);
  }

  // oczekiwanie na zakończenie pracy wątków
  for (int i=0; i<l_w; i++) {
    pthread_join(watki[i], NULL);
    calka_suma_local += struktury[i].wynik_struct;
  }

  return(calka_suma_local);
}



void* calka_podobszar_w(void* arg_wsk){

  double a_local, b_local, dx;
  // rozpakowanie danych przesłanych do wątku
  struct struktura struktura_loc = *((struct struktura*) arg_wsk);
  a_local = struktura_loc.a_struct;
  b_local = struktura_loc.b_struct;
  dx = struktura_loc.dx_struct;

  int my_id; // skąd pobierany?
  my_id = struktura_loc.id_struct;

  printf("\nWątek %d: a_local %lf, b_local %lf, dx %lf\n", 
	 my_id, a_local, b_local, dx);

  // wywołanie zadania do wykonania: całkowanie w zadanym przedziale 
  double calka = calka_sekw(a_local, b_local, dx);
  ((struct struktura*) arg_wsk)->wynik_struct = calka;

}
