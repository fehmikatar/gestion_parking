#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestion_parking.h"

// Structure pour un agent
typedef struct {
    int id;
    char nom[50];
    char prenom[50];
    char email[100];
    char genre[20];
    char adresse[100];
    char parking[50];
    int agent_id; // L'ID de l'agent
} agent;

// Fonction pour chercher un agent par ID dans le fichier agents.txt
int chercher_agent_par_id(const char *filename, int agent_id) {
    FILE *file = fopen(filename, "r");
    agent a;
    int found = 0;

    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier des agents");
        return 0;
    }

    while (fscanf(file, "%d,%49[^,],%49[^,],%99[^,],%19[^,],%99[^,],%49[^,],%d", 
                  &a.id, a.nom, a.prenom, a.email, a.genre, a.adresse, a.parking, &a.agent_id) != EOF) {
        if (a.id == agent_id) {
            found = 1;
            break;
        }
    }

    fclose(file);
    return found;
}

// Ajouter un parking
int ajouter_parking(const char *filename, parking p) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 0;
    }
    p.agent_id = 0; // Aucun agent affecté par défaut
    fprintf(file, "%d;%s;%s;%.2f;%d;%s;%d\n", p.id, p.nom, p.adresse, p.prix, p.capacite, p.type, p.agent_id);
    fclose(file);
    return 1;
}

// Modifier un parking (prix, capacité, type, etc.)
int modifier_parking(const char *filename, int id, parking p) {
    FILE *file = fopen(filename, "r");
    FILE *tempFile = fopen("temp.txt", "w");
    parking temp;
    int found = 0;

    if (file == NULL || tempFile == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 0;
    }

    while (fscanf(file, "%d;%49[^;];%99[^;];%f;%d;%19[^;];%d", 
                  &temp.id, temp.nom, temp.adresse, &temp.prix, &temp.capacite, temp.type, &temp.agent_id) != EOF) {
        if (temp.id == id) {
            // Si parking trouvé, on le remplace par les nouvelles informations
            fprintf(tempFile, "%d;%s;%s;%.2f;%d;%s;%d\n", 
                    p.id, p.nom, p.adresse, p.prix, p.capacite, p.type, p.agent_id);
            found = 1;
        } else {
            // Si pas trouvé, on garde les anciennes informations
            fprintf(tempFile, "%d;%s;%s;%.2f;%d;%s;%d\n", 
                    temp.id, temp.nom, temp.adresse, temp.prix, temp.capacite, temp.type, temp.agent_id);
        }
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

// Supprimer un parking
int supprimer_parking(const char *filename, int id) {
    FILE *file = fopen(filename, "r");
    FILE *tempFile = fopen("temp.txt", "w");
    parking temp;
    int found = 0;

    if (file == NULL || tempFile == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 0;
    }

    while (fscanf(file, "%d;%49[^;];%99[^;];%f;%d;%19[^;];%d", 
                  &temp.id, temp.nom, temp.adresse, &temp.prix, &temp.capacite, temp.type, &temp.agent_id) != EOF) {
        if (temp.id != id) {
            fprintf(tempFile, "%d;%s;%s;%.2f;%d;%s;%d\n", 
                    temp.id, temp.nom, temp.adresse, temp.prix, temp.capacite, temp.type, temp.agent_id);
        } else {
            found = 1;
        }
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

// Chercher un parking par ID
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
            return p;
        }
    }

    fclose(file);
    return p;
}

// Afficher tous les parkings
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

// Affecter un agent à un parking
int affecter_agent_parking(const char *filename, int parking_id, int agent_id) {
    if (!chercher_agent_par_id("agents.txt", agent_id)) {
        printf("Erreur : Agent non trouvé.\n");
        return 0;  // L'agent n'a pas été trouvé dans le fichier agents.txt
    }

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
            p.agent_id = agent_id;  // Assigner l'agent au parking
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

