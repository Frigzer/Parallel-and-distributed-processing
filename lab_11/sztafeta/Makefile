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

all: MPI_sztafeta run 

run: MPI_sztafeta
	$(MPI_run) -np 10 ./MPI_sztafeta

# zaleznosci i komendy
MPI_sztafeta : MPI_sztafeta.o
	$(LOADER) $(OPT) MPI_sztafeta.o -o MPI_sztafeta $(LIB)

# jak uzyskac plik moj_program.o ?
MPI_sztafeta.o: MPI_sztafeta.c 
	$(CCOMP) -c $(OPT) MPI_sztafeta.c

clean:
	rm -f *.o MPI_sztafeta
