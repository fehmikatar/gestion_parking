#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestion_parking.h"
#define FILENAME "parkings.txt"

void afficher_menu() {
    printf("Menu:\n");
    printf("1. Ajouter un parking\n");
    printf("2. Modifier un parking\n");
    printf("3. Supprimer un parking\n");
    printf("4. Afficher tous les parkings\n");
    printf("5. Affecter un agent à un parking\n");
    printf("6. Quitter\n");
    printf("Choisissez une option: ");
}
void afficher_agents(const char *filename) {
    FILE *file = fopen(filename, "r");
    char ligne[256];

    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier agents.txt");
        return;
    }

    printf("Liste des agents:\n");
    printf("---------------------------------------------\n");
    printf("ID | Nom | Prénom | Contact | Genre | Adresse | Parking\n");
    printf("---------------------------------------------\n");

    while (fgets(ligne, sizeof(ligne), file)) {
        // Supprimer le caractère de nouvelle ligne
        ligne[strcspn(ligne, "\n")] = 0;

        int id;
        char nom[50] = "", prenom[50] = "", contact[50] = "", genre[20] = "", adresse[50] = "", park[50] = "";

        // Compter le nombre de champs
        int champs_lus = sscanf(ligne, "%d;%49[^;];%49[^;];%49[^;];%19[^;];%49[^;];%49[^\n]", 
                   &id, nom, prenom, contact, genre, adresse, park);

        // Gérer les différents cas de parsing
        switch(champs_lus) {
            case 7: // Tous les champs
                printf("%d | %s | %s | %s | %s | %s | %s\n", 
                       id, nom, prenom, contact, genre, adresse, park);
                break;
            case 6: // Manque un champ (probablement genre)
                printf("%d | %s | %s | %s | M/F | %s | %s\n", 
                       id, nom, prenom, contact, adresse, park);
                break;
            case 5: // Manque adresse et genre
                printf("%d | %s | %s | %s | M/F | Add | %s\n", 
                       id, nom, prenom, contact, park);
                break;
            default:
                printf("Ligne invalide : %s\n", ligne);
        }
    }

    printf("---------------------------------------------\n");
    fclose(file);
}
int verifier_correspondance_parking(const char *agents_file, const char *parkings_file, int agent_id, int parking_id) {
    FILE *agents = fopen(agents_file, "r");
    FILE *parkings = fopen(parkings_file, "r");
    
    char ligne_agent[256];
    char ligne_parking[256];
    
    int id_agent;
    char nom_agent[50];
    char prenom_agent[50];
    char contact_agent[50];
    char genre_agent[20];
    char adresse_agent[50];
    char park_agent[50];
    
    int id_parking;
    char nom_parking[50];
    char adresse_parking[100];
    float prix_parking;
    int capacite_parking;
    char type_parking[20];
    int agent_id_parking;

    if (agents == NULL || parkings == NULL) {
        perror("Erreur lors de l'ouverture des fichiers");
        if (agents) fclose(agents);
        if (parkings) fclose(parkings);
        return 0;
    }

    // Trouver l'agent
    while (fgets(ligne_agent, sizeof(ligne_agent), agents)) {
        if (sscanf(ligne_agent, "%d;%49[^;];%49[^;];%49[^;];%19[^;];%49[^;];%49[^\n]", 
                   &id_agent, nom_agent, prenom_agent, contact_agent, genre_agent, adresse_agent, park_agent) == 7) {
            if (id_agent == agent_id) {
                // Trouver le parking
                while (fscanf(parkings, "%d;%49[^;];%99[^;];%f;%d;%19[^;];%d", 
                              &id_parking, nom_parking, adresse_parking, &prix_parking, 
                              &capacite_parking, type_parking, &agent_id_parking) != EOF) {
                    if (id_parking == parking_id) {
                        // Vérifier la correspondance du nom de parking
                        if (strcmp(park_agent, nom_parking) == 0) {
                            fclose(agents);
                            fclose(parkings);
                            return 1;  // Correspondance trouvée
                        }
                    }
                }
                break;  // Agent trouvé mais parking ne correspond pas
            }
        }
    }

    fclose(agents);
    fclose(parkings);
    return 0;  // Pas de correspondance
}

int main() {
    int choix;
    parking p;
    int agent_id;

    do {
        afficher_menu();
        scanf("%d", &choix);
        switch (choix) {
            case 1: // Ajouter un parking
                printf("Entrez l'ID du parking: ");
                scanf("%d", &p.id);
                printf("Entrez le nom du parking: ");
                scanf(" %[^\n]", p.nom);
                printf("Entrez l'adresse du parking: ");
                scanf(" %[^\n]", p.adresse);
                printf("Entrez le prix: ");
                scanf("%f", &p.prix);
                printf("Entrez la capacité: ");
                scanf("%d", &p.capacite);
                printf("Entrez le type: ");
                scanf(" %[^\n]", p.type);
                // Initialize agent_id to 0 by default
                p.agent_id = 0;
                if (ajouter_parking(FILENAME, p)) {
                    printf("Parking ajouté avec succès.\n");
                } else {
                    printf("Erreur lors de l'ajout du parking.\n");
                }
                break;
            case 2: // Modifier un parking
                printf("Entrez l'ID du parking à modifier: ");
                scanf("%d", &p.id);
                printf("Entrez le nouveau nom du parking: ");
                scanf(" %[^\n]", p.nom);
                printf("Entrez la nouvelle adresse du parking: ");
                scanf(" %[^\n]", p.adresse);
                printf("Entrez le nouveau prix: ");
                scanf("%f", &p.prix);
                printf("Entrez la nouvelle capacité: ");
                scanf("%d", &p.capacite);
                printf("Entrez le nouveau type: ");
                scanf(" %[^\n]", p.type);
                // Preserve existing agent_id when modifying
                p.agent_id = chercher_parking(FILENAME, p.id).agent_id;
                if (modifier_parking(FILENAME, p.id, p)) {
                    printf("Parking modifié avec succès.\n");
                } else {
                    printf("Erreur lors de la modification du parking.\n");
                }
                break;
            case 3: // Supprimer un parking
                printf("Entrez l'ID du parking à supprimer: ");
                scanf("%d", &p.id);
                if (supprimer_parking(FILENAME, p.id)) {
                    printf("Parking supprimé avec succès.\n");
                } else {
                    printf("Erreur lors de la suppression du parking.\n");
                }
                break;
            case 4: // Afficher tous les parkings
                afficher_parkings(FILENAME);
                break;
            case 5: // Affecter un agent à un parking
   		 // Afficher les parkings disponibles
 		   printf("Parkings disponibles :\n");
   		 afficher_parkings(FILENAME);

   		 // Afficher les agents disponibles
   		 printf("\n");
		    afficher_agents("agents.txt");

   		 // Reste de la logique d'affectation d'agent
   		 printf("Entrez l'ID du parking: ");
   		 scanf("%d", &p.id);
   		 printf("Entrez l'ID de l'agent à affecter: ");
    		scanf("%d", &agent_id);
    
    		// Vérification de correspondance
   		 if (verifier_correspondance_parking("agents.txt", FILENAME, agent_id, p.id)) {
    		    if (affecter_agent_parking(FILENAME, p.id, agent_id)) {
     	       printf("Agent affecté au parking avec succès.\n");
    	    } else {
    	        printf("Erreur lors de l'affectation de l'agent au parking.\n");
    	    }
 	   } else {
 	       printf("Erreur : L'agent ne peut pas être affecté à ce parking.\n");
  	  }
  		  break;
            case 6: // Quitter
                printf("Au revoir!\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choix != 6);
    return 0;
}
