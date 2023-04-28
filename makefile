CC = g++
CFLAGS = -Wall -O3 --std=c++11

main.exe : main.o data_structures.o
	$(CC) main.o data_structures.o -o main.exe

main.o : main.cpp data_structures.h
	$(CC) -c main.cpp -o main.o $(CFLAGS)
data_structures.o : data_structures.cpp data_structures.h
		$(CC) -c data_structures.cpp -o data_structures.o $(CFLAGS)

clean:
	rm *.o main.exe

esegui:
	./main.exe
