#include <stdio.h>
#include <stdlib.h>
#include "gestion_parking.h"

int main() {
    parking p;
    int id, choix, agent_id;

    while (1) {
        printf("Menu:\n");
        printf("1. Ajouter un parking\n");
        printf("2. Modifier un parking\n");
        printf("3. Supprimer un parking\n");
        printf("4. Afficher tous les parkings\n");
        printf("5. Affecter un agent à un parking\n");
        printf("6. Quitter\n");
        printf("Entrez votre choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                // Ajouter un parking
                printf("Entrez l'ID du parking: ");
                scanf("%d", &p.id);
                printf("Entrez le nom du parking: ");
                scanf("%s", p.nom);
                printf("Entrez l'adresse du parking: ");
                scanf("%s", p.adresse);
                printf("Entrez le prix: ");
                scanf("%f", &p.prix);
                printf("Entrez la capacité: ");
                scanf("%d", &p.capacite);
                printf("Entrez le type (ex: couvert, ouvert): ");
                scanf("%s", p.type);
                ajouter_parking("parkings.txt", p);
                break;

            case 2:
                // Modifier un parking
                printf("Entrez l'ID du parking à modifier: ");
                scanf("%d", &id);
                printf("Entrez le nouveau prix: ");
                scanf("%f", &p.prix);
                printf("Entrez la nouvelle capacité: ");
                scanf("%d", &p.capacite);
                printf("Entrez le nouveau type (ex: couvert, ouvert): ");
                scanf("%s", p.type);
                if (modifier_parking("parkings.txt", id, p)) {
                    printf("Parking modifié avec succès.\n");
                } else {
                    printf("Erreur lors de la modification du parking.\n");
                }
                break;

            case 3:
                // Supprimer un parking
                printf("Entrez l'ID du parking à supprimer: ");
                scanf("%d", &id);
                if (supprimer_parking("parkings.txt", id)) {
                    printf("Parking supprimé avec succès.\n");
                } else {
                    printf("Erreur lors de la suppression du parking.\n");
                }
                break;

            case 4:
                // Afficher tous les parkings
                afficher_parkings("parkings.txt");
                break;

            case 5:
                // Affecter un agent à un parking
                printf("Entrez l'ID du parking: ");
                scanf("%d", &id);
                printf("Entrez l'ID de l'agent: ");
                scanf("%d", &agent_id);
                if (affecter_agent_parking("parkings.txt", id, agent_id)) {
                    printf("Agent affecté au parking avec succès.\n");
                } else {
                    printf("Erreur lors de l'affectation de l'agent.\n");
                }
                break;

            case 6:
                printf("Au revoir!\n");
                return 0;

            default:
                printf("Choix invalide. Essayez à nouveau.\n");
        }
    }
}

