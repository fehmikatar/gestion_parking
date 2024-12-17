CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = prog

$(TARGET): reservation.o main.o
	$(CC) $(CFLAGS) reservation.o main.o -o $(TARGET)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

reservation.o: reservation.c
	$(CC) $(CFLAGS) -c reservation.c

clean:
	rm -f *.o $(TARGET)
