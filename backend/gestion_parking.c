#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestion_parking.h"

// Modified function to add parking to include agent_id
int ajouter_parking(const char *filename, parking p) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 0;
    }
    p.agent_id=0;
    fprintf(file, "%d;%s;%s;%.2f;%d;%s;%d\n", p.id, p.nom, p.adresse, p.prix, p.capacite, p.type, p.agent_id);
    fclose(file);
    return 1;
}

// Modified function to modify parking to include agent_id
int modifier_parking(const char *filename, int id, parking p) {
    FILE *file = fopen(filename, "r");
    FILE *tempFile = fopen("temp.txt", "w");
    parking p2;
    int found = 0;
    if (file == NULL || tempFile == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 0;
    }
    while (fscanf(file, "%d;%49[^;];%99[^;];%f;%d;%19[^;];%d", 
                  &p2.id, p2.nom, p2.adresse, &p2.prix, &p2.capacite, p2.type, &p2.agent_id) != EOF) {
        if (p2.id == id) {
            fprintf(tempFile, "%d;%s;%s;%.2f;%d;%s;%d\n", 
                    p.id, p.nom, p.adresse, p.prix, p.capacite, p.type, p.agent_id);
            found = 1;
        } else {
            fprintf(tempFile, "%d;%s;%s;%.2f;%d;%s;%d\n", 
                    p2.id, p2.nom, p2.adresse, p2.prix, p2.capacite, p2.type, p2.agent_id);
        }
    }
    fclose(file);
    fclose(tempFile);
    remove(filename);
    rename("temp.txt", filename);
    return found;
}

// Modified function to delete parking to match new structure
int supprimer_parking(const char *filename, int id) {
    FILE *file = fopen(filename, "r");
    FILE *tempFile = fopen("temp.txt", "w");
    int found = 0;
    parking p;
    if (file == NULL || tempFile == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 0;
    }
    while (fscanf(file, "%d;%49[^;];%99[^;];%f;%d;%19[^;];%d", 
                  &p.id, p.nom, p.adresse, &p.prix, &p.capacite, p.type, &p.agent_id) != EOF) {
        if (p.id != id) {
            fprintf(tempFile, "%d;%s;%s;%.2f;%d;%s;%d\n", 
                    p.id, p.nom, p.adresse, p.prix, p.capacite, p.type, p.agent_id);
        } else {
            found = 1;
        }
    }
    fclose(file);
    fclose(tempFile);
    remove(filename);
    rename("temp.txt", filename);
    return found;
}

// Modified function to search for parking to match new structure
parking chercher_parking(const char *filename, int id) {
    FILE *file = fopen(filename, "r");
    parking p = {-1}; // Valeur par défaut pour indiquer que le parking n'a pas été trouvé
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return p;
    }
    while (fscanf(file, "%d;%49[^;];%99[^;];%f;%d;%19[^;];%d", 
                  &p.id, p.nom, p.adresse, &p.prix, &p.capacite, p.type, &p.agent_id) != EOF) {
        if (p.id == id) {
            fclose(file);
            return p; // Retourne le parking trouvé
        }
    }
    fclose(file);
    return p; // Retourne un parking avec id -1 si non trouvé
}

// Modified function to display parkings to match new structure
void afficher_parkings(const char *filename) {
    FILE *file = fopen(filename, "r");
    parking p;
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }
    printf("Liste des parkings:\n");
    while (fscanf(file, "%d;%49[^;];%99[^;];%f;%d;%19[^;];%d", 
                  &p.id, p.nom, p.adresse, &p.prix, &p.capacite, p.type, &p.agent_id) != EOF) {
        printf("ID: %d, Nom: %s, Adresse: %s, Prix: %.2f, Capacité: %d, Type: %s, Agent ID: %d\n", 
               p.id, p.nom, p.adresse, p.prix, p.capacite, p.type, p.agent_id);
    }
    fclose(file);
}

// New function to assign an agent to a parking
int affecter_agent_parking(const char *filename, int parking_id, int agent_id) {
    FILE *file = fopen(filename, "r");
    FILE *tempFile = fopen("temp.txt", "w");
    parking p;
    int found = 0;

    if (file == NULL || tempFile == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 0;
    }

    while (fscanf(file, "%d;%49[^;];%99[^;];%f;%d;%19[^;];%d", 
                  &p.id, p.nom, p.adresse, &p.prix, &p.capacite, p.type, &p.agent_id) != EOF) {
        if (p.id == parking_id) {
            p.agent_id = agent_id;
            found = 1;
        }
        fprintf(tempFile, "%d;%s;%s;%.2f;%d;%s;%d\n", 
                p.id, p.nom, p.adresse, p.prix, p.capacite, p.type, p.agent_id);
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove(filename);
        rename("temp.txt", filename);
        return 1;
    }

    remove("temp.txt");
    return 0;
}
