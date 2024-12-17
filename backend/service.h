#ifndef SERVICE_H
#define SERVICE_H

typedef struct {
    int id;                 // ID du service
    char type[100];         // Type de service
    char disponibilite[50]; // Disponibilité (ex: 24/7)
    float prix;             // Prix du service
    int maxClients;         // Nombre maximum de clients
} Service;

typedef struct {
    int idReservation;      // ID de la réservation
    int idService;          // ID du service réservé
    char nom[100];          // Nom du client
    char prenom[100];       // Prénom du client
    char date[20];          // Date d'affectation
} Reservation;

// Prototypes des fonctions
void ajouterService(const char *filename, Service *service);
void modifierService(const char *filename, int id, Service *newService);
void supprimerService(const char *filename, int id);
void afficherServices(const char *filename);
void affecterServiceReservation(const char *filenameServices, const char *filenameReservations, int idReservation, int idService, const char *nom, const char *prenom, const char *date);

#endif

