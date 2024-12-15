reservation: reservation.o main.o
	gcc reservation.o main.o -o reservation -g
main.o: main.c reservation.h
	gcc -c main.c -g
reservation.o: reservation.c reservation.h
	gcc -c reservation.c -g
