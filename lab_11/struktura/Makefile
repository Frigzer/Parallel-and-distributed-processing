# kompilator c
CCOMP = mpicc

# konsolidator
LOADER = mpicc

# program uruchomieniowy MPI
MPI_run = mpiexec -oversubscribe

# opcje optymalizacji:
# wersja do debugowania
OPT = -g -DDEBUG
# wersja zoptymalizowana do mierzenia czasu
# OPT = -O3

# pliki naglowkowe
#INC = -I../pomiar_czasu

# biblioteki
#LIB = -L../pomiar_czasu -lm
LIB = -lm

all: MPI_struktura run 

run: MPI_struktura
	$(MPI_run) -np 4 ./MPI_struktura

# zaleznosci i komendy
MPI_struktura : MPI_struktura.o
	$(LOADER) $(OPT) MPI_struktura.o -o MPI_struktura $(LIB)

# jak uzyskac plik moj_program.o ?
MPI_struktura.o: MPI_struktura.c 
	$(CCOMP) -c $(OPT) MPI_struktura.c

clean:
	rm -f *.o MPI_struktura
