#ifndef CITOYEN_H
#define CITOYEN_H

typedef struct {
    int jour;
    int mois;
    int annee;
} Date;

typedef struct {
    char id[20];
    char nom[100];
    Date naissance;
    char gouvernorat[50];
    char sexe[10];
} Citoyen;

void ajouter_citoyen(Citoyen c);
void extraire_annee_mois(const char *date, int *annee, int *mois);
float rechercher_prix_service(const char *id_service);
float rechercher_prix_parking(const char *id_parking);
void generer_facture(const char *id_citoyen, int annee, int mois);
int modifier_citoyen(const char *id, Citoyen c_modifie);
int supprimer_citoyen(const char *id);
int rechercher_citoyen_par_id(const char *id);

#endif