#include <stdio.h>
#include <stdlib.h>
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
                printf("Entrez l'ID du parking: ");
                scanf("%d", &p.id);
                printf("Entrez l'ID de l'agent à affecter: ");
                scanf("%d", &agent_id);
                if (affecter_agent_parking(FILENAME, p.id, agent_id)) {
                    printf("Agent affecté au parking avec succès.\n");
                } else {
                    printf("Erreur lors de l'affectation de l'agent au parking.\n");
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
