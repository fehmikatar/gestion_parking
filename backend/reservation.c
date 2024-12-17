#include "reservation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fonction pour charger les réservations depuis un fichier
int charger_reservations(Reservation reservations[], const char* filename) {
    FILE* file = fopen(filename, "r");
    int n = 0;
    if (file) {
        while (fscanf(file, "%d %s %s %s %d %d %d\n", &reservations[n].id, reservations[n].marque, reservations[n].modele,
                       reservations[n].plaque, &reservations[n].jours, &reservations[n].heure_arrivee, &reservations[n].heure_depart) != EOF) {
            n++;
        }
        fclose(file);
    } else {
        printf("Erreur lors de l'ouverture du fichier des réservations.\n");
    }
    return n;
}

// Fonction pour ajouter une réservation
void ajouter_reservation(const char* filename) {
    FILE* file = fopen(filename, "a");
    if (file) {
        Reservation new_reservation;
        printf("Entrez les informations de la réservation:\n");
        printf("Marque: ");
        scanf("%s", new_reservation.marque);
        printf("Modèle: ");
        scanf("%s", new_reservation.modele);
        printf("Plaque: ");
        scanf("%s", new_reservation.plaque);
        printf("Nombre de jours: ");
        scanf("%d", &new_reservation.jours);
        printf("Heure d'arrivée: ");
        scanf("%d", &new_reservation.heure_arrivee);
        printf("Heure de départ: ");
        scanf("%d", &new_reservation.heure_depart);

        new_reservation.id = rand() % 1000;  // ID aléatoire

        fprintf(file, "%d %s %s %s %d %d %d\n", new_reservation.id, new_reservation.marque, new_reservation.modele, new_reservation.plaque,
                new_reservation.jours, new_reservation.heure_arrivee, new_reservation.heure_depart);
        fclose(file);
        printf("Réservation ajoutée avec succès.\n");
    } else {
        printf("Erreur lors de l'ouverture du fichier.\n");
    }
}

// Fonction pour afficher les réservations
void afficher_reservations(const char* filename) {
    FILE* file = fopen(filename, "r");
    Reservation reservation;
    if (file) {
        printf("Liste des réservations:\n");
        while (fscanf(file, "%d %s %s %s %d %d %d\n", &reservation.id, reservation.marque, reservation.modele, reservation.plaque,
                       &reservation.jours, &reservation.heure_arrivee, &reservation.heure_depart) != EOF) {
            printf("ID: %d, Marque: %s, Modèle: %s, Plaque: %s, Jours: %d, Heure arrivée: %d, Heure départ: %d\n", 
                   reservation.id, reservation.marque, reservation.modele, reservation.plaque, reservation.jours,
                   reservation.heure_arrivee, reservation.heure_depart);
        }
        fclose(file);
    } else {
        printf("Erreur lors de l'ouverture du fichier des réservations.\n");
    }
}

// Fonction pour supprimer une réservation
void supprimer_reservation(const char* filename, int id) {
    FILE* file = fopen(filename, "r");
    FILE* temp_file = fopen("temp.txt", "w");
    Reservation reservation;
    int found = 0;

    if (file && temp_file) {
        while (fscanf(file, "%d %s %s %s %d %d %d\n", &reservation.id, reservation.marque, reservation.modele, reservation.plaque,
                       &reservation.jours, &reservation.heure_arrivee, &reservation.heure_depart) != EOF) {
            if (reservation.id != id) {
                fprintf(temp_file, "%d %s %s %s %d %d %d\n", reservation.id, reservation.marque, reservation.modele, reservation.plaque,
                        reservation.jours, reservation.heure_arrivee, reservation.heure_depart);
            } else {
                found = 1;
            }
        }
        fclose(file);
        fclose(temp_file);
        remove(filename);
        rename("temp.txt", filename);

        if (found) {
            printf("Réservation avec ID %d supprimée.\n", id);
        } else {
            printf("Réservation non trouvée.\n");
        }
    } else {
        printf("Erreur lors de l'ouverture du fichier.\n");
    }
}

// Fonction pour sauvegarder les réservations dans un fichier
void sauvegarder_reservations(Reservation reservations[], int n_reservations, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file) {
        for (int i = 0; i < n_reservations; i++) {
            fprintf(file, "%d %s %s %s %d %d %d\n", reservations[i].id, reservations[i].marque, reservations[i].modele,
                    reservations[i].plaque, reservations[i].jours, reservations[i].heure_arrivee, reservations[i].heure_depart);
        }
        fclose(file);
        printf("Réservations sauvegardées avec succès.\n");
    } else {
        printf("Erreur lors de la sauvegarde des réservations.\n");
    }
}

int charger_parkings(Parking parkings[], const char* filename) {
    FILE* file = fopen(filename, "r");
    int n = 0;
    if (file) {
        while (fscanf(file, "%d %s %d\n", &parkings[n].id, parkings[n].location, &parkings[n].capacity) != EOF) {
            n++;
        }
        fclose(file);
    } else {
        printf("Erreur lors de l'ouverture du fichier des parkings.\n");
    }
    return n;
}

// Fonction pour sauvegarder les parkings dans un fichier
void sauvegarder_parkings(Parking parkings[], int n_parkings, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file) {
        for (int i = 0; i < n_parkings; i++) {
            fprintf(file, "%d %s %d\n", parkings[i].id, parkings[i].location, parkings[i].capacity);
        }
        fclose(file);
        printf("Parkings sauvegardés avec succès.\n");
    } else {
        printf("Erreur lors de la sauvegarde des parkings.\n");
    }
}

// Fonction pour afficher les parkings et choisir
void choisir_parking(Parking parkings[], int n_parkings) {
    printf("Liste des parkings disponibles:\n");
    for (int i = 0; i < n_parkings; i++) {
        printf("ID: %d, Location: %s, Capacité: %d\n", parkings[i].id, parkings[i].location, parkings[i].capacity);
    }
}
