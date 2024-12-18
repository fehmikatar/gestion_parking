#include "reservation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Charger les réservations depuis un fichier
int load_parking_reservations(ParkingReservation reservations[], const char* filename) {
    FILE* file = fopen(filename, "r");
    int count = 0;
    if (file) {
        while (fscanf(file, "%d %s %s %s %d %d %d\n", 
            &reservations[count].reservation_id, 
            reservations[count].vehicle_brand, 
            reservations[count].vehicle_model,
            reservations[count].license_plate, 
            &reservations[count].reservation_days, 
            &reservations[count].arrival_hour, 
            &reservations[count].departure_hour) != EOF) {
            count++;
        }
        fclose(file);
    } else {
        printf("Erreur lors de l'ouverture du fichier des réservations.\n");
    }
    return count;
}

// Ajouter une réservation
void create_parking_reservation(const char* filename) {
    FILE* file = fopen(filename, "a");
    if (file) {
        ParkingReservation new_reservation;
        
        printf("Entrez les informations de la réservation:\n");
        printf("Marque du véhicule: ");
        scanf("%19s", new_reservation.vehicle_brand);
        printf("Modèle du véhicule: ");
        scanf("%19s", new_reservation.vehicle_model);
        printf("Plaque d'immatriculation: ");
        scanf("%9s", new_reservation.license_plate);
        printf("Nombre de jours de réservation: ");
        scanf("%d", &new_reservation.reservation_days);
        printf("Heure d'arrivée: ");
        scanf("%d", &new_reservation.arrival_hour);
        printf("Heure de départ: ");
        scanf("%d", &new_reservation.departure_hour);

        // Générer un ID de réservation unique
        new_reservation.reservation_id = rand() % 10000 + 1;

        // Écrire la réservation dans le fichier
        fprintf(file, "%d %s %s %s %d %d %d\n", 
            new_reservation.reservation_id, 
            new_reservation.vehicle_brand, 
            new_reservation.vehicle_model, 
            new_reservation.license_plate,
            new_reservation.reservation_days, 
            new_reservation.arrival_hour, 
            new_reservation.departure_hour);
        
        fclose(file);
        printf("Réservation ajoutée avec succès. ID de réservation: %d\n", new_reservation.reservation_id);
    } else {
        printf("Erreur lors de l'ouverture du fichier de réservation.\n");
    }
}

// Afficher les réservations par nom de fichier
void display_parking_reservations_by_filename(const char* filename) {
    FILE* file = fopen(filename, "r");
    ParkingReservation reservation;
    
    if (file) {
        printf("Liste des réservations de parking:\n");
        printf("ID  | Marque | Modèle | Plaque | Jours | Arrivée | Départ\n");
        printf("------------------------------------------------------------\n");
        
        while (fscanf(file, "%d %s %s %s %d %d %d\n", 
            &reservation.reservation_id, 
            reservation.vehicle_brand, 
            reservation.vehicle_model, 
            reservation.license_plate,
            &reservation.reservation_days, 
            &reservation.arrival_hour, 
            &reservation.departure_hour) != EOF) {
            
            printf("%d | %s | %s | %s | %d | %d | %d\n", 
                reservation.reservation_id, 
                reservation.vehicle_brand, 
                reservation.vehicle_model, 
                reservation.license_plate, 
                reservation.reservation_days,
                reservation.arrival_hour, 
                reservation.departure_hour);
        }
        
        fclose(file);
    } else {
        printf("Erreur lors de l'ouverture du fichier de réservations.\n");
    }
}

// Supprimer une réservation
void delete_parking_reservation(const char* filename, int reservation_id) {
    FILE* file = fopen(filename, "r");
    FILE* temp_file = fopen("temp_reservations.txt", "w");
    ParkingReservation reservation;
    int reservation_found = 0;

    if (file && temp_file) {
        while (fscanf(file, "%d %s %s %s %d %d %d\n", 
            &reservation.reservation_id, 
            reservation.vehicle_brand, 
            reservation.vehicle_model, 
            reservation.license_plate,
            &reservation.reservation_days, 
            &reservation.arrival_hour, 
            &reservation.departure_hour) != EOF) {
            
            if (reservation.reservation_id != reservation_id) {
                fprintf(temp_file, "%d %s %s %s %d %d %d\n", 
                    reservation.reservation_id, 
                    reservation.vehicle_brand, 
                    reservation.vehicle_model, 
                    reservation.license_plate,
                    reservation.reservation_days, 
                    reservation.arrival_hour, 
                    reservation.departure_hour);
            } else {
                reservation_found = 1;
            }
        }
        
        fclose(file);
        fclose(temp_file);
        
        remove(filename);
        rename("temp_reservations.txt", filename);

        if (reservation_found) {
            printf("Réservation avec l'ID %d supprimée avec succès.\n", reservation_id);
        } else {
            printf("Aucune réservation trouvée avec l'ID %d.\n", reservation_id);
        }
    } else {
        printf("Erreur lors de l'ouverture des fichiers.\n");
    }
}

// Sauvegarder les réservations
void save_parking_reservations(ParkingReservation reservations[], int reservation_count, const char* filename) { FILE* file = fopen(filename, "w");
    if (file) {
        for (int i = 0; i < reservation_count; i++) {
            fprintf(file, "%d %s %s %s %d %d %d\n", 
                reservations[i].reservation_id, 
                reservations[i].vehicle_brand, 
                reservations[i].vehicle_model,
                reservations[i].license_plate, 
                reservations[i].reservation_days, 
                reservations[i].arrival_hour, 
                reservations[i].departure_hour);
        }
        fclose(file);
        printf("Réservations sauvegardées avec succès.\n");
    } else {
        printf("Erreur lors de la sauvegarde des réservations.\n");
    }
}

// Charger les emplacements de parking
int load_parking_locations(ParkingLocation parking_locations[], const char* filename) {
    FILE* file = fopen(filename, "r");
    int count = 0;
    if (file) {
        while (fscanf(file, "%d %s %d\n", 
            &parking_locations[count].parking_id, 
            parking_locations[count].parking_location, 
            &parking_locations[count].parking_capacity) != EOF) {
            count++;
        }
        fclose(file);
    } else {
        printf("Erreur lors de l'ouverture du fichier des emplacements de parking.\n");
    }
    return count;
}

// Sauvegarder les emplacements de parking
void save_parking_locations(ParkingLocation parking_locations[], int location_count, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file) {
        for (int i = 0; i < location_count; i++) {
            fprintf(file, "%d %s %d\n", 
                parking_locations[i].parking_id, 
                parking_locations[i].parking_location, 
                parking_locations[i].parking_capacity);
        }
        fclose(file);
        printf("Emplacements de parking sauvegardés avec succès.\n");
    } else {
        printf("Erreur lors de la sauvegarde des emplacements de parking.\n");
    }
}

// Lister les emplacements de parking disponibles
void list_available_parking_locations(ParkingLocation parking_locations[], int location_count) {
    printf("Liste des emplacements de parking disponibles:\n");
    for (int i = 0; i < location_count; i++) {
        printf("ID: %d, Location: %s, Capacité: %d\n", 
            parking_locations[i].parking_id, 
            parking_locations[i].parking_location, 
            parking_locations[i].parking_capacity);
    }
}