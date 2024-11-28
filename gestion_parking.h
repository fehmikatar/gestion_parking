#ifndef GESTION_PARKING_H
#define GESTION_PARKING_H

typedef struct {
    int id;
    char nom[50];
    char adresse[100];
    float prix;
    int capacite;
    char type[20]; //affecter un agent
    int agent_id; 
} parking;

// Déclarations des fonctions
int ajouter_parking(const char *filename, parking p);
int modifier_parking(const char *filename, int id, parking p);
int supprimer_parking(const char *filename, int id);
parking chercher_parking(const char *filename, int id);
void afficher_parkings(const char *filename); // Déclaration de la fonction pour afficher tous les parkings
int affecter_agent_parking(const char *filename, int parking_id, int agent_id);

#endif // GESTION_PARKING_H
