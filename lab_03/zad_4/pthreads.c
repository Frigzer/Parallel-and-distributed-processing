#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>

#define LICZBA_W_MAX 2

typedef struct {
  int id;
  int a;
  double b;
  double suma;
}struktura;

int zmienna_wspolna = 0;

void *funkcja_w( void *arg_wsk)
{
  int tab[10000000] = {0};

  struktura s_lok = *((struktura *)arg_wsk);
  printf("ID watku: %d\n", s_lok.id);
  s_lok.b += s_lok.a;
  printf("watek: s_lok.a = %d, s_lok.b = %lf\n", s_lok.a, s_lok.b);
  struktura * s_wsk = (struktura *) arg_wsk;
  printf("zewn.: s_zewn.a = %d, s_zewn.b = %lf\n", s_wsk->a, s_wsk->b);
  s_wsk->suma = s_lok.a + s_lok.b;
  printf("Suma lokalna: %lf\n", s_wsk->suma);

  // Sprawdzenie atrybutów wątku
  pthread_attr_t attr;
  size_t stack_size;
  void *stack_addr;
  pthread_getattr_np(pthread_self(), &attr); // Pobieranie atrybutów wątku
  pthread_attr_getstack(&attr, &stack_addr, &stack_size);
  printf("Rozmiar stosu: %zu, Adres stosu: %p\n", stack_size, stack_addr);
  
  // Pobieranie polityki planowania
  int policy;
  pthread_attr_getschedpolicy(&attr, &policy);
  const char *policy_name = (policy == SCHED_FIFO) ? "SCHED_FIFO" :
                      (policy == SCHED_RR) ? "SCHED_RR" :
                      (policy == SCHED_OTHER) ? "SCHED_OTHER" : "UNKNOWN";
  printf("Polityka planowania: %s\n", policy_name);

  // Pobieranie priorytetu
  struct sched_param param;
  pthread_attr_getschedparam(&attr, &param);
  printf("Priorytet wątku: %d\n", param.sched_priority);

  // Pobieranie afiniczności
  cpu_set_t cpuset;
  CPU_ZERO(&cpuset);
  pthread_getaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);
  printf("Afiniczność wątku: ");
  for (int j = 0; j < CPU_SETSIZE; j++) {
    if (CPU_ISSET(j, &cpuset)) {
      printf("CPU %d ", j);
    }
  }
  printf("\n\n");

  return(NULL);
}

int main(int argc, char *argv[]) {
  int i;
  pthread_t watki[LICZBA_W_MAX];
  pthread_attr_t attr;
  struct sched_param param;
  cpu_set_t cpuset;
  int p = LICZBA_W_MAX;
  struktura struktury[LICZBA_W_MAX];
  for (i = 0; i < p; i++) 
  {
    (struktury[i]).id = i;
    (struktury[i]).a = i;
    (struktury[i]).b = i + 2.0;
    (struktury[i]).suma = 0.0;
  }
  double suma_calkowita = 0.0;

  for (i = 0; i < p; i++) {
    pthread_attr_init(&attr);

    // Ustawianie rozmiaru stosu
    size_t rozmiar_stosu = 64 * 1024 * 1024; // 64MB
    pthread_attr_setstacksize(&attr, rozmiar_stosu);

     // Ustawianie priorytetu
     pthread_attr_setschedpolicy(&attr, SCHED_RR);
     param.sched_priority = 10 + i;
     pthread_attr_setschedparam(&attr, &param);

     // Ustawianie afiniczności - przypisywanie wątku do określonego rdzenia
     CPU_ZERO(&cpuset);
     CPU_SET(i % 2, &cpuset);
     pthread_attr_setaffinity_np(&attr, sizeof(cpu_set_t), &cpuset);

     // Tworzenie wątków z atrybutami
     pthread_create(&watki[i], &attr, funkcja_w, (void *)&struktury[i]);
     pthread_attr_destroy(&attr);
  }

  for (i = 0; i < p; i++) {
    pthread_join( watki[i], NULL);
    suma_calkowita += (struktury[i]).suma;
  }
  printf("Suma calkowita wyniosla: %lf\n", suma_calkowita);
  return 0;
}
