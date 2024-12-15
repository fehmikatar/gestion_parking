prog: gestion_parking.o main.o
	gcc gestion_parking.o main.o -o prog

main.o: main.c gestion_parking.h
	gcc -c main.c -g

gestion_parking.o: gestion_parking.c gestion_parking.h
	gcc -c gestion_parking.c -g
