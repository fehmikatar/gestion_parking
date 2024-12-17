#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "service.h"

// Ajouter un service
void ajouterService(const char *filename, Service *service) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier\n");
        return;
    }
    fprintf(file, "%d;%s;%s;%.2f;%d\n", service->id, service->type, service->disponibilite, service->prix, service->maxClients);
    fclose(file);
}

// Modifier un service
void modifierService(const char *filename, int id, Service *newService) {
    FILE *file = fopen(filename, "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (file == NULL || tempFile == NULL) {
        printf("Erreur d'ouverture des fichiers\n");
        return;
    }

    Service temp;
    int found = 0;
    while (fscanf(file, "%d;%99[^;];%49[^;];%f;%d\n", &temp.id, temp.type, temp.disponibilite, &temp.prix, &temp.maxClients) == 5) {
        if (temp.id == id) {
            fprintf(tempFile, "%d;%s;%s;%.2f;%d\n", newService->id, newService->type, newService->disponibilite, newService->prix, newService->maxClients);
            found = 1;
        } else {
            fprintf(tempFile, "%d;%s;%s;%.2f;%d\n", temp.id, temp.type, temp.disponibilite, temp.prix, temp.maxClients);
        }
    }

    fclose(file);
    fclose(tempFile);
    remove(filename);
    rename("temp.txt", filename);

    if (!found) {
        printf("Service non trouvé\n");
    }
}

// Supprimer un service
void supprimerService(const char *filename, int id) {
    FILE *file = fopen(filename, "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (file == NULL || tempFile == NULL) {
        printf("Erreur d'ouverture des fichiers\n");
        return;
    }

    Service temp;
    int found = 0;
    while (fscanf(file, "%d;%99[^;];%49[^;];%f;%d\n", &temp.id, temp.type, temp.disponibilite, &temp.prix, &temp.maxClients) == 5) {
        if (temp.id != id) {
            fprintf(tempFile, "%d;%s;%s;%.2f;%d\n", temp.id, temp.type, temp.disponibilite, temp.prix, temp.maxClients);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);
    remove(filename);
    rename("temp.txt", filename);

    if (found) {
        printf("Service supprimé\n");
    } else {
        printf("Service non trouvé\n");
    }
}

// Afficher tous les services
void afficherServices(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier\n");
        return;
    }

    Service temp;
    printf("ID\tType\t\tDisponibilité\tPrix\tMax Clients\n");
    printf("------------------------------------------------------------\n");
    while (fscanf(file, "%d;%99[^;];%49[^;];%f;%d\n", &temp.id, temp.type, temp.disponibilite, &temp.prix, &temp.maxClients) == 5) {
        printf("%d\t%s\t\t%s\t%.2f\t%d\n", temp.id, temp.type, temp.disponibilite, temp.prix, temp.maxClients);
    }

    fclose(file);
}

// Affecter un service à une réservation
void affecterServiceReservation(const char *filenameServices, const char *filenameReservations, int idReservation, int idService, const char *nom, const char *prenom, const char *date) {
    FILE *reservationsFile = fopen(filenameReservations, "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (reservationsFile == NULL || tempFile == NULL) {
        printf("Erreur d'ouverture des fichiers\n");
        return;
    }

    Reservation temp;
    int found = 0;
    while (fscanf(reservationsFile, "%d;%d;%99[^;];%99[^;];%19[^\n]\n", &temp.idReservation, &temp.idService, temp.nom, temp.prenom, temp.date) == 5) {
        if (temp.idReservation == idReservation) {
            fprintf(tempFile, "%d;%d;%s;%s;%s\n", idReservation, idService, nom, prenom, date);
            found = 1;
        } else {
            fprintf(tempFile, "%d;%d;%s;%s;%s\n", temp.idReservation, temp.idService, temp.nom, temp.prenom, temp.date);
        }
    }

    if (!found) {
        fprintf(tempFile, "%d;%d;%s;%s;%s\n", idReservation, idService, nom, prenom, date);
    }

    fclose(reservationsFile);
    fclose(tempFile);
    remove(filenameReservations);
    rename("temp.txt", filenameReservations);

    printf("Service affecté ou mis à jour avec succès\n");
}

