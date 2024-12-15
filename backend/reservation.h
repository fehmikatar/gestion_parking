#ifndef RESERVATION_H
#define RESERVATION_H

typedef struct {
    int jour;
    char month[60];
    int year;
} date;

typedef struct {
    int id_reservation;
    int id_Citoyen;
    int id_parking;
    int id_service;
    date date_debut;
    date date_fin;
    char type_vehicule[10];
} reservation;

typedef struct {
    int id_parking;
    char nom_parking[100];
    int places_disponibles;
} parking;

void add_reservation(reservation r, const char *filename);
void modify_reservation(int id_to_modify, const char *filename);  
void delete_reservation(int id_reservation, const char *filename);
void show_reservation_by_id(int id_reservation, const char *filename);
void show_sorted_parkings(const char *filename);

#endif
