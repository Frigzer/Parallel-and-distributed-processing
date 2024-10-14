# kompilator c
CCOMP = gcc

# konsolidator
LOADER = gcc

# opcje optymalizacji:
# wersja do debugowania
OPT = -g -DDEBUG -O0
# wersja zoptymalizowana do mierzenia czasu
#OPT = -O3

# pliki naglowkowe
INC = -I../pomiar_czasu

# biblioteki
LIB = -L../pomiar_czasu -lpomiar_czasu -lm

# zaleznosci i komendy
fork: fork.o 
	$(LOADER) $(OPT) fork.o -o fork $(LIB)

# jak uzyskac plik fork.o ?
fork.o: fork.c ../pomiar_czasu/pomiar_czasu.h
	$(CCOMP) -c $(OPT) fork.c $(INC) 

# zaleznosci i komendy
clone: clone.o 
	$(LOADER) $(OPT) clone.o -o clone $(LIB)

# jak uzyskac plik clone.o ?
clone.o: clone.c ../pomiar_czasu/pomiar_czasu.h
	$(CCOMP) -c $(OPT) clone.c $(INC) 

# zaleznosci i komendy
clone2: clone2.o 
	$(LOADER) $(OPT) clone2.o -o clone2 $(LIB)

# jak uzyskac plik clone2.o ?
clone2.o: clone2.c ../pomiar_czasu/pomiar_czasu.h
	$(CCOMP) -c $(OPT) clone2.c $(INC) 

# zaleznosci i komendy
program: program.o 
	$(LOADER) $(OPT) program.o -o program

# jak uzyskac plik program.o ?
program.o: program.c
	$(CCOMP) -c $(OPT) program.c


clean:
	rm -f *.o fork clone
