#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include"pomiar_czasu.h"

int zmienna_globalna=0;

int main(){
  
  int pid, wynik, i;

  inicjuj_czas();
  
  for(i=0;i<1000;i++){
    
    pid = fork(); 			
    
    if(pid==0){ 			
      
      zmienna_globalna++;

      //char arg1[] = " ";
      //char arg2[] = "test";
      //char arg3[] = "Adam";
      //char arg4[] = "Borek";
      //char* arg[] = {arg1,arg2,NULL};
      //char* arg[] = {"/bin/whoami",NULL};
      char* arg[] = {" ","Adam"," ","Borek",NULL};
      //wynik=execv("/bin/whoami",arg); 
      wynik=execv("./program",arg); 
       if(wynik==-1)
           printf("Proces potomny nie wykonal programu\n");

      exit(0);
      
    } else {					
      
      wait(NULL);
      
    }
    
  }

  drukuj_czas();
  
}

  
