#ifndef RESERVATION_H
#define RESERVATION_H

#define MAX_RESERVATIONS 100
#define MAX_PARKINGS 50

// Structure de réservation
typedef struct {
    int id;
    char marque[20];
    char modele[20];
    char plaque[10];
    int jours;
    int heure_arrivee;
    int heure_depart;
} Reservation;

// Structure de parking
typedef struct {
    int id;
    char location[50];
    int capacity;
} Parking;
// Fonctions liées aux réservations
int charger_reservations(Reservation reservations[], const char* filename);
void ajouter_reservation(const char* filename);
void afficher_reservations(const char* filename);
void supprimer_reservation(const char* filename, int id);
void sauvegarder_reservations(Reservation reservations[], int n_reservations, const char* filename);

// Fonctions liées aux parkings
int charger_parkings(Parking parkings[], const char* filename);
void sauvegarder_parkings(Parking parkings[], int n_parkings, const char* filename);
void choisir_parking(Parking parkings[], int n_parkings);

#endif



