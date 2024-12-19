#include <stdio.h>
#include <string.h>
#include "citoyen.h"

// Fonction pour ajouter un citoyen
void ajouter_citoyen(Citoyen c) {
    FILE *f = fopen("citoyen.txt", "a");
    if (f != NULL) {
        fprintf(f, "ID:%s\nNom:%s\nJour:%d\nMois:%d\nAnnee:%d\nGouvernorat:%s\nSexe:%s\n",
                c.id, c.nom, c.naissance.jour, c.naissance.mois, c.naissance.annee, 
                c.gouvernorat, c.sexe);
        fclose(f);
    } else {
        printf("Erreur d'ouverture du fichier citoyen.txt\n");
    }
}

// Fonction pour extraire l'année et le mois d'une date sous format "YYYY-MM-DD"
void extraire_annee_mois(const char *date, int *annee, int *mois) {
    sscanf(date, "%d-%d", annee, mois);  // Assure-toi que le format de la date est "YYYY-MM-DD"
}

// Fonction pour rechercher le prix d'un service par son ID dans service.txt
float rechercher_prix_service(const char *id_service) {
    FILE *f_service = fopen("service.txt", "r");
    if (f_service == NULL) {
        printf("Erreur lors de l'ouverture de service.txt\n");
        return 0;
    }

    char id[20], type_service[30], dispo[10];
    float prix_service;

    while (fscanf(f_service, "%s %s %s %f", id, type_service, dispo, &prix_service) != EOF) {
        if (strcmp(id, id_service) == 0) {
            fclose(f_service);
            return prix_service;
        }
    }

    fclose(f_service);
    return 0;  // Si non trouvé
}

// Fonction pour rechercher le prix d'un parking par son ID dans parking.txt
float rechercher_prix_parking(const char *id_parking) {
    FILE *f_parking = fopen("parking.txt", "r");
    if (f_parking == NULL) {
        printf("Erreur lors de l'ouverture de parking.txt\n");
        return 0;
    }

    char id[20], type_parking[30];
    float prix_parking;

    while (fscanf(f_parking, "%s %s %f", id, type_parking, &prix_parking) != EOF) {
        if (strcmp(id, id_parking) == 0) {
            fclose(f_parking);
            return prix_parking;
        }
    }

    fclose(f_parking);
    return 0;  // Si non trouvé
}

// Fonction pour générer la facture à partir de l'ID citoyen et de la date donnée (année, mois)
void generer_facture(const char *id_citoyen, int annee, int mois) {
    FILE *f_reservation = fopen("reservation.txt", "r");
    if (f_reservation == NULL) {
        printf("Erreur lors de l'ouverture de reservation.txt\n");
        return;
    }

    char id_reservation[20], date[20], id_citoyen_res[20], id_service[20], id_parking[20];
    float total = 0;
    int annee_res, mois_res;

    // Parcourir les réservations
    while (fscanf(f_reservation, "%s %s %s %s %s", id_reservation, date, id_citoyen_res, id_service, id_parking) != EOF) {
        // Vérifier si l'ID citoyen correspond
        if (strcmp(id_citoyen_res, id_citoyen) == 0) {
            // Extraire l'année et le mois de la réservation
            extraire_annee_mois(date, &annee_res, &mois_res);

            // Vérifier si la réservation est dans le mois et l'année donnés
            if (annee_res == annee && mois_res == mois) {
                // Ajouter le prix du service
                total += rechercher_prix_service(id_service);
                // Ajouter le prix du parking
                total += rechercher_prix_parking(id_parking);
            }
        }
    }

    fclose(f_reservation);

    // Afficher la facture
    printf("Facture totale pour le citoyen %s en %04d-%02d : %.2f\n", id_citoyen, annee, mois, total);
}

// Fonction pour modifier un citoyen par ID
int modifier_citoyen(const char *id, Citoyen c_modifie) {
    FILE *f = fopen("citoyen.txt", "r");
    FILE *f_temp = fopen("temp.txt", "w");
    if (!f || !f_temp) {
        return 0;
    }

    char buffer[1024];
    int id_found = 0;

    while (fgets(buffer, sizeof(buffer), f)) {
        if (strstr(buffer, id)) {
            fprintf(f_temp, "ID:%s\nNom:%s\nJour:%d\nMois:%d\nAnnee:%d\nGouvernorat:%s\nSexe:%s\n",
                    c_modifie.id, c_modifie.nom, c_modifie.naissance.jour, c_modifie.naissance.mois, 
                    c_modifie.naissance.annee, c_modifie.gouvernorat, c_modifie.sexe);
            id_found = 1;
            while (fgets(buffer, sizeof(buffer), f) && !strstr(buffer, "Sexe:"));
        } else {
            fputs(buffer, f_temp);
        }
    }

    fclose(f);
    fclose(f_temp);

    if (id_found) {
        remove("citoyen.txt");
        rename("temp.txt", "citoyen.txt");
    } else {
        remove("temp.txt");
    }
    return id_found;
}

// Fonction pour supprimer un citoyen par ID
int supprimer_citoyen(const char *id) {
    FILE *f = fopen("citoyen.txt", "r");
    FILE *f_temp = fopen("temp.txt", "w");
    if (!f || !f_temp) {
        return 0;
    }

    char buffer[1024];
    int id_found = 0;
    while (fgets(buffer, sizeof(buffer), f)) {
        if (strstr(buffer, id)) {
            id_found = 1;
            while (fgets(buffer, sizeof(buffer), f) && !strstr(buffer, "Sexe:"));
        } else {
            fputs(buffer, f_temp);
        }
    }

    fclose(f);
    fclose(f_temp);

    if (id_found) {
        remove("citoyen.txt");
        rename("temp.txt", "citoyen.txt");
    } else {
        remove("temp.txt");
    }
    return id_found;
}

// Fonction pour rechercher un citoyen par ID
int rechercher_citoyen_par_id(const char *id) {
    FILE *f = fopen("citoyen.txt", "r");
    if (f == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier citoyen.txt\n");
        return 0;
    }

    char buffer[1024];
    int id_found = 0;

    while (fgets(buffer, sizeof(buffer), f)) {
        if (strstr(buffer, "ID:") != NULL && strstr(buffer, id) != NULL) {
            id_found = 1;
            break;
        }
    }

    fclose(f);
    return id_found;
}

