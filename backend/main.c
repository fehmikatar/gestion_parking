#include <stdio.h>
#include "service.h"

int main() {
    int choix;
    Service service;
    int idReservation, idService;
    char nom[100], prenom[100], date[20];

    do {
        printf("\nMenu Gestion des Services:\n");
        printf("1. Ajouter un service\n");
        printf("2. Modifier un service\n");
        printf("3. Supprimer un service\n");
        printf("4. Afficher tous les services\n");
        printf("5. Affecter un service à une réservation\n");
        printf("0. Quitter\n");
        printf("Choisissez une option: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("Entrez l'ID du service: ");
                scanf("%d", &service.id);
                printf("Entrez le type de service: ");
                scanf(" %[^\n]", service.type);
                printf("Entrez la disponibilité: ");
                scanf(" %[^\n]", service.disponibilite);
                printf("Entrez le prix: ");
                scanf("%f", &service.prix);
                printf("Entrez le nombre maximum de clients: ");
                scanf("%d", &service.maxClients);
                ajouterService("services.txt", &service);
                break;

            case 2:
                printf("Entrez l'ID du service à modifier: ");
                scanf("%d", &idService);
                printf("Entrez les nouvelles informations:\n");
                printf("Type: ");
                scanf(" %[^\n]", service.type);
                printf("Disponibilité: ");
                scanf(" %[^\n]", service.disponibilite);
                printf("Prix: ");
                scanf("%f", &service.prix);
                printf("Nombre maximum de clients: ");
                scanf("%d", &service.maxClients);
                service.id = idService;
                modifierService("services.txt", idService, &service);
                break;

            case 3:
                printf("Entrez l'ID du service à supprimer: ");
                scanf("%d", &idService);
                supprimerService("services.txt", idService);
                break;

            case 4:
                afficherServices("services.txt");
                break;

            case 5:
                printf("Entrez l'ID de la réservation: ");
                scanf("%d", &idReservation);
                printf("Entrez l'ID du service: ");
                scanf("%d", &idService);
                printf("Entrez le nom du client: ");
                scanf(" %[^\n]", nom);
                printf("Entrez le prénom du client: ");
                scanf(" %[^\n]", prenom);
                printf("Entrez la date d'affectation (jj/mm/aaaa): ");
                scanf(" %[^\n]", date);
                affecterServiceReservation("services.txt", "reservations.txt", idReservation, idService, nom, prenom, date);
                break;

            case 0:
                printf("Au revoir!\n");
                break;

            default:
                printf("Option invalide.\n");
        }
    } while (choix != 0);

    return 0;
}
