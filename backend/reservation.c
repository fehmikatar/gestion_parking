#include <stdio.h>
#include <string.h>
#include "reservation.h"

void add_reservation(reservation r, const char *filename) {  
    FILE *f = fopen(filename, "a+");
    if (f == NULL) {
        printf("Error opening file\n");
        return;
    }
    fprintf(f, "%d;%d;%d;%d;%d;%s;%d;%d;%s;%d;%s\n",
            r.id_reservation, r.id_Citoyen, r.id_parking, r.id_service,
            r.date_debut.jour, r.date_debut.month, r.date_debut.year,
            r.date_fin.jour, r.date_fin.month, r.date_fin.year,
            r.type_vehicule);
    fclose(f);
    printf("Reservation added successfully.\n");
}

void modify_reservation(int id_to_modify, const char *filename) {
    FILE *f = fopen(filename, "r");
    FILE *f_temp = fopen("reservation_temp.txt", "w");

    if (f == NULL || f_temp == NULL) {
        printf("Error handling file\n");
        return;
    }

    reservation temp;
    int found = 0;

   
    while (fscanf(f, "%d;%d;%d;%d;%d;%59[^;];%d;%d;%59[^;];%d;%9[^\n]\n",
                  &temp.id_reservation, &temp.id_Citoyen, &temp.id_parking, &temp.id_service,
                  &temp.date_debut.jour, temp.date_debut.month, &temp.date_debut.year,
                  &temp.date_fin.jour, temp.date_fin.month, &temp.date_fin.year,
                  temp.type_vehicule) != EOF) {

        
        if (temp.id_reservation == id_to_modify) {
            printf("Reservation found! Please enter the updated details:\n");
            printf("ID Réservation: ");
            scanf("%d", &temp.id_reservation);  
            printf("ID Citoyen: ");
            scanf("%d", &temp.id_Citoyen);  
            printf("ID Parking: ");
            scanf("%d", &temp.id_parking);
            printf("ID Service: ");
            scanf("%d", &temp.id_service);
            printf("Date Début (Jour Mois Année): ");
            scanf("%d %s %d", &temp.date_debut.jour, temp.date_debut.month, &temp.date_debut.year);
            printf("Date Fin (Jour Mois Année): ");
            scanf("%d %s %d", &temp.date_fin.jour, temp.date_fin.month, &temp.date_fin.year);
            printf("Type de véhicule: ");
            scanf("%s", temp.type_vehicule);

            found = 1; 
        }


        fprintf(f_temp, "%d;%d;%d;%d;%d;%s;%d;%d;%s;%d;%s\n",
                temp.id_reservation, temp.id_Citoyen, temp.id_parking, temp.id_service,
                temp.date_debut.jour, temp.date_debut.month, temp.date_debut.year,
                temp.date_fin.jour, temp.date_fin.month, temp.date_fin.year,
                temp.type_vehicule);
    }

    fclose(f);
    fclose(f_temp);

    
    remove(filename);
    rename("reservation_temp.txt", filename);  
    if (found) {
        printf("Reservation modified successfully.\n");
    } else {
        printf("Reservation with ID %d not found.\n", id_to_modify);
    }
}


void delete_reservation(int id_reservation, const char *filename) {  
    FILE *f = fopen(filename, "r");
    FILE *f_temp = fopen("reservation_temp.txt", "w");
    if (f == NULL || f_temp == NULL) {
        printf("Error handling file\n");
        return;
    }

    reservation temp;
    int found = 0;

    while (fscanf(f, "%d;%d;%d;%d;%d;%59[^;];%d;%d;%59[^;];%d;%9[^\n]\n",
                  &temp.id_reservation, &temp.id_Citoyen, &temp.id_parking, &temp.id_service,
                  &temp.date_debut.jour, temp.date_debut.month, &temp.date_debut.year,
                  &temp.date_fin.jour, temp.date_fin.month, &temp.date_fin.year,
                  temp.type_vehicule) != EOF) {

        if (temp.id_reservation == id_reservation) {
            found = 1;
        } else {
            fprintf(f_temp, "%d;%d;%d;%d;%d;%s;%d;%d;%s;%d;%s\n",
                    temp.id_reservation, temp.id_Citoyen, temp.id_parking, temp.id_service,
                    temp.date_debut.jour, temp.date_debut.month, temp.date_debut.year,
                    temp.date_fin.jour, temp.date_fin.month, temp.date_fin.year,
                    temp.type_vehicule);
        }
    }

    fclose(f);
    fclose(f_temp);

    remove(filename);
    rename("reservation_temp.txt", filename);

    printf(found ? "Reservation deleted successfully.\n" : "Reservation not found.\n");
}

void show_reservation_by_id(int id_reservation, const char *filename) {  
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Error opening file\n");
        return;
    }

    reservation temp;
    int found = 0;

    while (fscanf(f, "%d;%d;%d;%d;%d;%59[^;];%d;%d;%59[^;];%d;%9[^\n]\n",
                  &temp.id_reservation, &temp.id_Citoyen, &temp.id_parking, &temp.id_service,
                  &temp.date_debut.jour, temp.date_debut.month, &temp.date_debut.year,
                  &temp.date_fin.jour, temp.date_fin.month, &temp.date_fin.year,
                  temp.type_vehicule) != EOF) {

        if (temp.id_reservation == id_reservation) {
            printf("Reservation Details:\n");
            printf("Reservation ID: %d\n", temp.id_reservation);
            printf("Citizen ID: %d\n", temp.id_Citoyen);
            printf("Parking ID: %d\n", temp.id_parking);
            printf("Service ID: %d\n", temp.id_service);
            printf("Start Date: %d %s %d\n", temp.date_debut.jour, temp.date_debut.month, temp.date_debut.year);
            printf("End Date: %d %s %d\n", temp.date_fin.jour, temp.date_fin.month, temp.date_fin.year);
            printf("Vehicle Type: %s\n", temp.type_vehicule);
            found = 1;
            break;
        }
    }

    fclose(f);
    if (!found) {
        printf("Reservation with ID %d not found.\n", id_reservation);
    }
}

void show_sorted_parkings(const char *filename) {  
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Error opening file: %s\n", filename);
        return;
    }

    parking parkings[100];
    int count = 0;

    while (fscanf(f, "%d %59s %d\n", &parkings[count].id_parking, parkings[count].nom_parking, &parkings[count].places_disponibles) != EOF) {
        count++;
    }

    fclose(f);

    
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (parkings[i].places_disponibles > parkings[j].places_disponibles) {
                parking temp = parkings[i];
                parkings[i] = parkings[j];
                parkings[j] = temp;
            }
        }
    }

    
    printf("Sorted Parkings by Available Spots:\n");
    for (int i = 0; i < count; i++) {
        printf("Parking ID: %d, %s, Available Spots: %d\n", parkings[i].id_parking, parkings[i].nom_parking, parkings[i].places_disponibles);
    }
}
