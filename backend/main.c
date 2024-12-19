#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "agent.h"
#include "gestion_parking.h"
#include "service.h"
#include "reservation.h"
#include "citoyen.h" 

int main() {
    int choix;
    int id, agent_id, idReservation, idService;
    Agent agent;
    parking p;
    Service service;
    char date[20];
    char nom[100], prenom[100];
    Citoyen citoyen; 

    // Variables pour les réservations de parking
    ParkingReservation reservations[MAX_PARKING_RESERVATIONS];
    ParkingLocation parking_locations[MAX_PARKING_LOCATIONS];
    int n_reservations = 0;
    int n_parking_locations = 0;

    // Charger les réservations et les emplacements de parking
    n_reservations = load_parking_reservations(reservations, "parking_reservations.txt");
    n_parking_locations = load_parking_locations(parking_locations, "parking_locations.txt");

    // Vérifier et créer les fichiers nécessaires s'ils n'existent pas
    if (access("reservations.txt", F_OK) == -1) {
        printf("Le fichier reservations.txt n'existe pas, création...\n");
        creer_fichier_reservations("reservations.txt");
    }

    if (access("parkings.txt", F_OK) == -1) {
        printf("Le fichier parkings.txt n'existe pas, création...\n");
        FILE *file = fopen("parkings.txt", "w");
        if (file) fclose(file);
    }

    if (access("agents.txt", F_OK) == -1) {
        printf("Le fichier agents.txt n'existe pas, création...\n");
        FILE *file = fopen("agents.txt", "w");
        if (file) fclose(file);
    }

    if (access("services.txt", F_OK) == -1) {
        printf("Le fichier services.txt n'existe pas, création...\n");
        FILE *file = fopen("services.txt", "w");
        if (file) fclose(file);
    }

    // Fichiers pour les nouvelles réservations de parking
    if (access("parking_reservations.txt", F_OK) == -1) {
        printf("Le fichier parking_reservations.txt n'existe pas, création...\n");
        FILE *file = fopen("parking_reservations.txt", "w");
        if (file) fclose(file);
    }

    if (access("parking_locations.txt", F_OK) == -1) {
        printf("Le fichier parking_locations.txt n'existe pas, création...\n");
        FILE *file = fopen("parking_locations.txt", "w");
        if (file) fclose(file);
    }

    do {
        printf("\n--- Menu Principal de Gestion des Parkings, Agents et Services ---\n");
        printf("Gestion des Agents:\n");
        printf("1. Ajouter un agent\n");
        printf("2. Modifier un agent\n");
        printf("3. Supprimer un agent\n");
        printf("4. Afficher tous les agents\n");
        printf("5. Afficher les réservations à une date\n");
        
        printf("\nGestion des Parkings:\n");
        printf("6. Ajouter un parking\n");
        printf("7. Modifier un parking\n");
        printf("8. Supprimer un parking\n");
        printf("9. Afficher tous les parkings\n");
        printf("10. Affecter un agent à un parking\n");
        
        printf("\nGestion des Services:\n");
        printf("11. Ajouter un service\n");
        printf("12. Modifier un service\n");
        printf("13. Supprimer un service\n");
        printf("14. Afficher tous les services\n");
        printf("15. Affecter un service à une réservation\n");

        printf("\nGestion des Réservations:\n");
        printf("16. Ajouter une réservation de parking\n");
        printf("17. Afficher les réservations de parking\n");
        printf("18. Supprimer une réservation de parking\n");
        printf("19. Afficher les emplacements de parking\n");

        printf("\nGestion des Citoyens:\n");
        printf("20. Ajouter un citoyen\n");
        printf("21. Modifier un citoyen\n");
        printf("22. Supprimer un citoyen\n");
        printf("23. Rechercher un citoyen\n");
        printf("24. Générer une facture pour un citoyen\n");

        printf("\n0. Quitter\n");
        printf("Choisissez une option: ");

        if (scanf("%d", &choix) != 1) {
            printf("Entrée invalide. Veuillez entrer un nombre.\n");
            while (getchar() != '\n');  // Consommer l'entrée incorrecte
            continue;
        }
        getchar();    // pour consommer le '\n' laissé par scanf

        switch (choix) {
            // Gestion des Agents
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
            case 5:
                // Afficher les réservations à une date spécifique
                printf("Entrez l'ID de l'agent : ");
                if (scanf("%d", &id) != 1 || id <= 0) {
                    printf("Entrée invalide. L'ID doit être un entier positif.\n");
                    while (getchar() != '\n'); // Vider le buffer
                    break; // Revenir au menu principal
                }
                printf("Entrez la date (format YYYY-MM-DD) : ");
                scanf("%19s", date);
                afficher_reservations(date, id);
                break;

            // Gestion des Parkings
            case 6:
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
            case 7:
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
            case 8:
                // Supprimer un parking
                printf("Entrez l'ID du parking à supprimer: ");
                scanf("%d", &id);
                if (supprimer_parking("parkings.txt", id)) {
                    printf("Parking supprimé avec succès.\n");
                } else {
                    printf("Erreur lors de la suppression du parking.\n");
                }
                break;
            case 9:
                // Afficher tous les parkings
                afficher_parkings("parkings.txt");
                break;
            case 10:
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

            // Gestion des Services
            case 11:
                // Ajouter un service
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
            case 12:
                // Modifier un service
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
            case 13:
                // Supprimer un service
                printf("Entrez l'ID du service à supprimer: ");
                scanf("%d", &idService);
                supprimerService("services.txt", idService);
                break;
            case 14:
                // Afficher tous les services
                afficherServices("services.txt");
                break;
            case 15:
                // Affecter un service à une réservation
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
                        // Nouvelles options pour les réservations de parking
            case 16:
                create_parking_reservation("parking_reservations.txt");
                break;
            case 17:
                display_parking_reservations_by_filename("parking_reservations.txt");
                break;
            case 18:
                printf("Entrez l'ID de la réservation à supprimer: ");
                scanf("%d", &id);
                delete_parking_reservation("parking_reservations.txt", id);
                break;
            case 19:
                list_available_parking_locations(parking_locations, n_parking_locations);
                break;

                // Gestion des Citoyens
            case 20:
                // Ajouter un citoyen
                printf("Entrez l'ID du citoyen: ");
                scanf("%s", citoyen.id);
                printf("Entrez le nom du citoyen: ");
                scanf("%s", citoyen.nom);
                printf("Entrez le jour de naissance: ");
                scanf("%d", &citoyen.naissance.jour);
                printf("Entrez le mois de naissance: ");
                scanf("%d", &citoyen.naissance.mois);
                printf("Entrez l'année de naissance: ");
                scanf("%d", &citoyen.naissance.annee);
                printf("Entrez le gouvernorat: ");
                scanf("%s", citoyen.gouvernorat);
                printf("Entrez le sexe: ");
                scanf("%s", citoyen.sexe);
                
                ajouter_citoyen(citoyen);
                break;

            case 21:
                // Modifier un citoyen
                printf("Entrez l'ID du citoyen à modifier: ");
                scanf("%s", citoyen.id);
                
                printf("Entrez les nouvelles informations:\n");
                printf("Nom: ");
                scanf("%s", citoyen.nom);
                printf("Jour de naissance: ");
                scanf("%d", &citoyen.naissance.jour);
                printf("Mois de naissance: ");
                scanf("%d", &citoyen.naissance.mois);
                printf("Année de naissance: ");
                scanf("%d", &citoyen.naissance.annee);
                printf("Gouvernorat: ");
                scanf("%s", citoyen.gouvernorat);
                printf("Sexe: ");
                scanf("%s", citoyen.sexe);
                
                if (modifier_citoyen(citoyen.id, citoyen)) {
                    printf("Citoyen modifié avec succès.\n");
                } else {
                    printf("Erreur de modification du citoyen.\n");
                }
                break;

            case 22:
                // Supprimer un citoyen
                printf("Entrez l'ID du citoyen à supprimer: ");
                scanf("%s", citoyen.id);
                
                if (supprimer_citoyen(citoyen.id)) {
                    printf("Citoyen supprimé avec succès.\n");
                } else {
                    printf("Erreur de suppression du citoyen.\n");
                }
                break;

            case 23:
                // Rechercher un citoyen
                printf("Entrez l'ID du citoyen à rechercher: ");
                scanf("%s", citoyen.id);
                
                if (rechercher_citoyen_par_id(citoyen.id)) {
                    printf("Citoyen trouvé.\n");
                } else {
                    printf("Citoyen non trouvé.\n");
                }
                break;

            case 24:
                // Générer une facture
                printf("Entrez l'ID du citoyen: ");
                scanf("%s", citoyen.id);
                printf("Entrez l'année: ");
                int annee;
                scanf("%d", &annee);
                printf("Entrez le mois: ");
                int mois;
                scanf("%d", &mois);
                
                generer_facture(citoyen.id, annee, mois);
                break;

            case 0:
                // Sauvegarde et quitter
                printf("Au revoir!\n");
                break;
            default:
                printf("Choix invalide!\n");
        }
    } while (choix != 0);

    return 0;
}