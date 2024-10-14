#define _GNU_SOURCE
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <linux/sched.h>

#include <../pomiar_czasu/pomiar_czasu.h>

int zmienna_globalna=0;

#define ROZMIAR_STOSU 1024*64

int funkcja_watku( void* argument )
{
  
  int zmienna_lokalna = 0;

  for(int i = 0; i < 100000; i++) 
  {

    zmienna_globalna++;
    zmienna_lokalna++;
  
  }

  printf("Zmienna globalna: %d,\tzmienna lokalna: %d\n",zmienna_globalna, zmienna_lokalna);

  return 0;
}

int main()
{

  void *stos1, *stos2;
  pid_t pid1, pid2;
  int i; 
  
  stos1 = malloc( ROZMIAR_STOSU );
  if (stos1 == 0) {
    printf("Proces nadrzędny - blad alokacji stosu 1\n");
    exit( 1 );
  }
  stos2 = malloc( ROZMIAR_STOSU );
  if (stos2 == 0) {
    printf("Proces nadrzędny - blad alokacji stosu 2\n");
    exit( 1 );
  }

  inicjuj_czas();

  pid1 = clone( &funkcja_watku, (void *) stos1+ROZMIAR_STOSU, 
	 CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, 0 );
  pid2 = clone( &funkcja_watku, (void *) stos2+ROZMIAR_STOSU, 
	 CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, 0 );

  waitpid(pid1, NULL, __WCLONE);
  waitpid(pid2, NULL, __WCLONE);

  
  printf("Zmienna globalna: %d\n",zmienna_globalna);

  drukuj_czas();

  free( stos1 );
  free( stos2 );

}
