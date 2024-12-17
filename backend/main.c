#include "reservation.h"
#include <stdio.h>

#define FILENAME_RESERVATIONS "reservations.txt"
#define FILENAME_PARKINGS "parkings.txt"

int main() {
    Reservation reservations[MAX_RESERVATIONS]; // Tableau pour stocker les réservations
    Parking parkings[MAX_PARKINGS]; // Tableau pour stocker les parkings

    int n_reservations = 0; // Nombre de réservations
    int n_parkings = 0;     // Nombre de parkings
    int choix, id;

    // Charger les réservations et les parkings depuis les fichiers
    n_reservations = charger_reservations(reservations, FILENAME_RESERVATIONS);
    n_parkings = charger_parkings(parkings, FILENAME_PARKINGS);

    do {
        printf("\n=== Menu Principal ===\n");
        printf("1. Ajouter une réservation\n");
        printf("2. Afficher les réservations\n");
        printf("3. Supprimer une réservation\n");
        printf("4. Afficher les parkings triés et choisir\n");
        printf("5. Sauvegarder et quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                // Appel pour ajouter une réservation
                ajouter_reservation(FILENAME_RESERVATIONS);
                break;
            case 2:
                // Appel pour afficher les réservations
                afficher_reservations(FILENAME_RESERVATIONS);
                break;
            case 3:
                printf("Entrez l'ID de la réservation à supprimer : ");
                scanf("%d", &id);
                // Appel pour supprimer une réservation
                supprimer_reservation(FILENAME_RESERVATIONS, id);
                break;
            case 4:
                // Afficher les parkings triés et choisir
                choisir_parking(parkings, n_parkings);
                break;
            case 5:
                // Sauvegarder les réservations et parkings dans les fichiers
                sauvegarder_reservations(reservations, n_reservations, FILENAME_RESERVATIONS);
                sauvegarder_parkings(parkings, n_parkings, FILENAME_PARKINGS);
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide, veuillez réessayer.\n");
        }
    } while (choix != 5);

    return 0;
}


