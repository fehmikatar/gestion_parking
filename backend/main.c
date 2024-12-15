#include <stdio.h>
#include "reservation.h"

int main() {
    char filename_reservations[] = "reservation.txt";
    char filename_parkings[] = "paking.txt";
    int option, id;
    reservation r;

    printf("Système de gestion des réservations\n");

    do {
        printf("\nMenu :\n");
        printf("1. Ajouter une réservation\n");
        printf("2. Modifier une réservation\n");
        printf("3. Supprimer une réservation\n");
        printf("4. Afficher vos réservations\n");
        printf("5. Afficher les parkings triés par places disponibles\n");
        printf("6. Quitter\n");
        printf("Choisissez une option : ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Entrer les informations de la réservation :\n");
                printf("ID Réservation: ");
                scanf("%d", &r.id_reservation);
                printf("ID Citoyen: ");
                scanf("%d", &r.id_Citoyen);
                printf("ID Parking: ");
                scanf("%d", &r.id_parking);
                printf("ID Service: ");
                scanf("%d", &r.id_service);
                printf("Date Début (Jour Mois Année): ");
                scanf("%d %s %d", &r.date_debut.jour, r.date_debut.month, &r.date_debut.year);
                printf("Date Fin (Jour Mois Année): ");
                scanf("%d %s %d", &r.date_fin.jour, r.date_fin.month, &r.date_fin.year);
                printf("Type de véhicule: ");
                scanf("%s", r.type_vehicule);
                add_reservation(r, filename_reservations);
                break;

            case 2:
                printf("Entrer l'ID de la réservation à modifier: ");
                scanf("%d", &id); 
                modify_reservation(id, filename_reservations); 
                break;

            case 3:
                printf("Entrer l'ID de la réservation à supprimer: ");
                scanf("%d", &id); 
                delete_reservation(id, filename_reservations); 
                break;

            case 4:
                printf("Entrez l'ID de la réservation à afficher: ");
                scanf("%d", &id);
                show_reservation_by_id(id, filename_reservations);
                break;

            case 5:
                show_sorted_parkings(filename_parkings);
                break;

            case 6:
                printf("Au revoir!\n");
                break;

            default:
                printf("Option invalide!\n");
        }
    } while (option != 6);

    return 0;
}
