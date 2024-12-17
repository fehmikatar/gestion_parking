#ifndef GESTION_PARKING_H
#define GESTION_PARKING_H

typedef struct {
    int id;
    char nom[50];
    char adresse[100];
    float prix;
    int capacite;
    char type[20]; // Type du parking (ex: couvert, ouvert)
    int agent_id;  // ID de l'agent affecté
} parking;

// Déclarations des fonctions
int ajouter_parking(const char *filename, parking p);
int modifier_parking(const char *filename, int id, parking p);
int supprimer_parking(const char *filename, int id);
parking chercher_parking(const char *filename, int id);
void afficher_parkings(const char *filename);
int affecter_agent_parking(const char *filename, int parking_id, int agent_id);

#endif // GESTION_PARKING_H

