#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "agent.h"

// Fonction pour saisir un agent depuis l'utilisateur
void saisirAgent(Agent *agent) {
    printf("Entrez l'ID de l'agent: ");
    scanf("%d", &agent->id);
    getchar(); // pour consommer le '\n' restant

    printf("Entrez le nom de l'agent: ");
    fgets(agent->nom, sizeof(agent->nom), stdin);
    agent->nom[strcspn(agent->nom, "\n")] = 0; // Suppression du '\n'

    printf("Entrez le prénom de l'agent: ");
    fgets(agent->prenom, sizeof(agent->prenom), stdin);
    agent->prenom[strcspn(agent->prenom, "\n")] = 0;

    printf("Entrez l'email de l'agent: ");
    fgets(agent->email, sizeof(agent->email), stdin);
    agent->email[strcspn(agent->email, "\n")] = 0;

    printf("Entrez le genre de l'agent: ");
    fgets(agent->genre, sizeof(agent->genre), stdin);
    agent->genre[strcspn(agent->genre, "\n")] = 0;

    printf("Entrez l'adresse de l'agent: ");
    fgets(agent->adresse, sizeof(agent->adresse), stdin);
    agent->adresse[strcspn(agent->adresse, "\n")] = 0;

    printf("Entrez le parking de l'agent: ");
    fgets(agent->parking, sizeof(agent->parking), stdin);
    agent->parking[strcspn(agent->parking, "\n")] = 0;

    // Nouvelle section pour l'affectation
    printf("L'agent est-il affecté ? (1 pour Oui, 0 pour Non): ");
    scanf("%d", &agent->affectation);
}

// Fonction pour ajouter un agent dans le fichier
void ajouterAgent(const char *filename, const Agent *agent) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s.\n", filename);
        return;
    }

    fprintf(file, "%d, %s, %s, %s, %s, %s, %s, %d\n", 
        agent->id, agent->nom, agent->prenom, agent->email, 
        agent->genre, agent->adresse, agent->parking, agent->affectation);

    fclose(file);
    printf("L'agent a été ajouté avec succès.\n");
}

// Fonction pour modifier un agent dans le fichier
void modifierAgent(const char *filename, int id, const Agent *agent) {
    FILE *file = fopen(filename, "r+");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s.\n", filename);
        return;
    }

    char line[256];
    long pos;
    int found = 0;

    // Rechercher l'agent dans le fichier
    while (fgets(line, sizeof(line), file)) {
        int current_id;
        sscanf(line, "%d", &current_id);
        if (current_id == agent->id) {
            pos = ftell(file) - strlen(line);
            found = 1;
            break;
        }
    }

    if (found) {
        fseek(file, pos, SEEK_SET);
        fprintf(file, "%d, %s, %s, %s, %s, %s, %s, %d\n", 
            agent->id, agent->nom, agent->prenom, agent->email, 
            agent->genre, agent->adresse, agent->parking, agent->affectation);
        printf("L'agent a été modifié avec succès.\n");
    } else {
        printf("Agent non trouvé.\n");
    }

    fclose(file);
}

// Fonction pour supprimer un agent du fichier
void supprimerAgent(const char *filename, int id) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s.\n", filename);
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Erreur lors de la création du fichier temporaire.\n");
        fclose(file);
        return;
    }

    char line[256];
    int found = 0;

    // Copie les données dans le fichier temporaire sauf pour l'agent à supprimer
    while (fgets(line, sizeof(line), file)) {
        int current_id;
        sscanf(line, "%d", &current_id);
        if (current_id != id) {
            fputs(line, temp);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(temp);

    // Remplacer l'ancien fichier par le fichier temporaire
    if (found) {
        remove(filename);
        rename("temp.txt", filename);
        printf("L'agent a été supprimé avec succès.\n");
    } else {
        remove("temp.txt");
        printf("Agent non trouvé.\n");
    }
}

// Fonction pour afficher tous les agents
void afficherAgents(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s.\n", filename);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        int id, affectation;
        char nom[100], prenom[100], email[100], genre[10], adresse[200], parking[100];

        sscanf(line, "%d, %99[^,], %99[^,], %99[^,], %9[^,], %199[^,], %99[^,], %d", 
               &id, nom, prenom, email, genre, adresse, parking, &affectation);

        // Convertir l'affectation en chaîne lisible
        char affectation_str[10];
        if (affectation == 1) {
            strcpy(affectation_str, "Oui");
        } else {
            strcpy(affectation_str, "Non");
        }

        printf("ID: %d, Nom: %s, Prénom: %s, Email: %s, Genre: %s, Adresse: %s, Parking: %s, Affectation: %s\n", 
               id, nom, prenom, email, genre, adresse, parking, affectation_str);
    }

    fclose(file);
}

// Fonction pour valider une date
void valider_date(int day, int month, int year) {
    // Validation de l'année, du mois et du jour
    if (month < 1 || month > 12) {
        printf("Mois invalide\n");
        return;
    }
    if (day < 1 || day > 31) {
        printf("Jour invalide\n");
        return;
    }
    // Si la date est valide, afficher la date
    printf("Date valide: %d/%d/%d\n", day, month, year);
}

// Fonction pour afficher les réservations à une date spécifique
void afficher_reservations(const char *date, int id) {
    FILE *file = fopen("reservations.txt", "r");
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier reservations.txt.\n");
        return;
    }

    char line[256];
    int found = 0;

    while (fgets(line, sizeof(line), file)) {
        char reservation_date[11], parking_name[50], client_name[100];
        int agent_id;

        // Lecture de la réservation depuis la ligne
        int matched = sscanf(line, "%10s, %d, %49[^,], %99[^\n]", reservation_date, &agent_id, parking_name, client_name);

        if (matched == 4) {
            // Si la date et l'ID de l'agent correspondent, afficher la réservation
            if (strcmp(reservation_date, date) == 0 && agent_id == id) {
                printf("Réservation pour le %s : Parking %s réservé par %s\n", reservation_date, parking_name, client_name);
                found = 1;
            }
        }
    }

    if (!found) {
        printf("Aucune réservation trouvée pour l'agent avec ID %d à la date %s.\n", id, date);
    }

    fclose(file);
}

// Fonction pour créer un fichier de réservations
void creer_fichier_reservations(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erreur lors de la création du fichier %s.\n", filename);
        return;
    }
    fclose(file);
    printf("Fichier %s créé avec succès.\n", filename);
}
