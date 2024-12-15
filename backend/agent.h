#ifndef AGENT_H
#define AGENT_H

#define MAX_NOM 100
#define MAX_PRENOM 100
#define MAX_EMAIL 100
#define MAX_GENRE 10
#define MAX_ADRESSE 200
#define MAX_PARKING 100

// Structure Agent mise à jour
typedef struct {
    int id;
    char nom[MAX_NOM];
    char prenom[MAX_PRENOM];
    char email[MAX_EMAIL];
    char genre[MAX_GENRE];
    char adresse[MAX_ADRESSE];
    char parking[MAX_PARKING];
    int affectation;  // Nouveau champ pour l'affectation (1 pour Oui, 0 pour Non)
} Agent;

// Prototypes de fonctions (inchangés)
void saisirAgent(Agent *agent);
void ajouterAgent(const char *filename, const Agent *agent);
void modifierAgent(const char *filename, int id, const Agent *agent);
void supprimerAgent(const char *filename, int id);
void afficherAgents(const char *filename);
void valider_date(int day, int month, int year);
void afficher_reservations(const char *date, int id);
void creer_fichier_reservations(const char *filename);

#endif // AGENT_H

