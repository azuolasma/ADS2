# Makefile for compiling the max_queens program

# Link the max_queens program
max_queens.exe: max_queens.o
	gcc -o max_queens.exe max_queens.o

# Compile the max_queens source file
max_queens.o: max_queens.c
	gcc -c max_queens.c

# Clean the build
clean:
	del *.o *.exe
