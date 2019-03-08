CC = g++ -fopenmp
.LDFLAGS=-fopenmp
prog: main.o knn.o sorts.o utils.o
	$(CC) main.o knn.o sorts.o utils.o -o prog
main.o: main.cpp knn.h
	$(CC) -c main.cpp
knn.o: knn.cpp knn.h sorts.h utils.h
	$(CC) -c knn.cpp
sorts.o: sorts.cpp sorts.h
	$(CC) -c sorts.cpp
utils.o: utils.cpp
	$(CC) -c utils.cpp
clean:
	rm main.o knn.o sorts.o utils.o prog
sclean:
	rm main.o knn.o sorts.o utils.o parallel_sol.txt serial_sol.txt prog
