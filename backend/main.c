#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // Pour access()
#include "agent.h"   // Pour utiliser la structure Agent et les fonctions associées

int main() {
    int choix;
    int id;
    Agent agent;
    char parking[100];
    char date[11];  // Pour saisir la date à rechercher
    int affectation = 0;  // Initialisation du nombre d'affectations à 0
    
   
    // Vérifier si le fichier reservations.txt existe, et le créer si nécessaire
    if (access("reservations.txt", F_OK) == -1) {
        printf("Le fichier reservations.txt n'existe pas, création...\n");
        creer_fichier_reservations("reservations.txt");
    }

    do {
        printf("\nMenu de gestion des agents de parking:\n");
        printf("1. Ajouter un agent\n");
        printf("2. Modifier un agent\n");
        printf("3. Supprimer un agent\n");
        printf("4. Afficher tous les agents\n");
        printf("5. Afficher les réservations à une date\n");
        printf("0. Quitter\n");
        printf("Choisissez une option: ");

        if (scanf("%d", &choix) != 1) {
            printf("Entrée invalide. Veuillez entrer un nombre.\n");
            while (getchar() != '\n');  // Consommer l'entrée incorrecte
            continue;
        }

        getchar();  // pour consommer le '\n' laissé par scanf

        switch (choix) {
            case 1:
                // Ajouter un agent
                saisirAgent(&agent);
                ajouterAgent("agents.txt", &agent);
                break;
            case 2:
                // Modifier un agent
                printf("Entrez l'ID de l'agent à modifier: ");
                scanf("%d", &agent.id);
                saisirAgent(&agent);
                modifierAgent("agents.txt", agent.id, &agent);
                break;
            case 3:
                // Supprimer un agent
                printf("Entrez l'ID de l'agent à supprimer: ");
                scanf("%d", &agent.id);
                supprimerAgent("agents.txt", agent.id);
                break;
            case 4:
                // Afficher tous les agents
                afficherAgents("agents.txt");
                break;
           
           case 5:  // Afficher les réservations à une date spécifique
                printf("Entrez l'ID de l'agent : ");
                if (scanf("%d", &id) != 1 || id <= 0) {
                printf("Entrée invalide. L'ID doit être un entier positif.\n");
                while (getchar() != '\n'); // Vider le buffer
                break; // Revenir au menu principal
                }

                printf("Entrez la date (format YYYY-MM-DD) : ");
                scanf("%10s", date);
		printf("La date saisie est : %s\n", date);

                afficher_reservations(date, id);
                break;

            case 0:
                // Quitter
                printf("Au revoir!\n");
                break;
            default:
                printf("Choix invalide!\n");
        }

    } while (choix != 0);

    return 0;
}

