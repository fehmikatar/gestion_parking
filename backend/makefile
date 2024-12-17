CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = prog

$(TARGET): gestion_parking.o agent.o service.o main.o
	$(CC) $(CFLAGS) gestion_parking.o agent.o service.o main.o -o $(TARGET)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

gestion_parking.o: gestion_parking.c agent.c service.c 
	$(CC) $(CFLAGS) -c gestion_parking.c

clean:
	rm -f *.o $(TARGET)