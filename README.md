#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure pour stocker les informations générales d'un athlète
typedef struct {
    char nom[50];  // Nom de l'athlète
    char genre[10];  // Genre de l'athlète, "Homme" ou "Femme"
} Athlete;

// Structure pour stocker les performances d'un athlète
typedef struct {
    char date[11];  // Format AAAA-MM-JJ
    char type_epreuve[20];  // Type d'épreuve (100m, 400m, etc.)
    float temps;  // Temps réalisé
    int position_relay;  // Position dans le relais, -1 si non applicable
} PerformanceAthlete;

// Prototypes des fonctions à développer
void enregistrerAthlete(const char *nom_fichier, Athlete athlete);
void enregistrerPerformance(const char *nom_fichier, PerformanceAthlete performance);
void chargerPerformances(const char *nom_fichier, PerformanceAthlete *performances, int *nbPerformances);
void mettreAJourPerformance(const char *nom_fichier, PerformanceAthlete performance);
void afficherHistoriqueAthlete(const char *nom_fichier);
void afficherStatistiques(const char *nom_fichier);
void trierPerformancesParDate(PerformanceAthlete *performances, int nbPerformances);
void trierPerformancesParEpreuve(PerformanceAthlete *performances, int nbPerformances);

// Programme principal
int main() {
    // Initialisation des variables nécessaires
    Athlete athlete;
    PerformanceAthlete performance;
    int choix;
    
    // Menu principal pour interagir avec l'utilisateur
    while (1) {
        printf("\nMenu Principal:\n");
        printf("1. Entrer un nouvel athlète\n");
        printf("2. Entrer une nouvelle performance\n");
        printf("3. Afficher l'historique d'un athlète\n");
        printf("4. Afficher les statistiques d'un athlète\n");
        printf("5. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        
        switch (choix) {
            case 1:
                printf("Nom de l'athlète : ");
                scanf("%s", athlete.nom);
                printf("Genre de l'athlète (Homme/Femme) : ");
                scanf("%s", athlete.genre);
                enregistrerAthlete("athletes.dat", athlete);
                break;
            case 2:
                printf("Nom de l'athlète : ");
                scanf("%s", athlete.nom);
                printf("Date (AAAA-MM-JJ) : ");
                scanf("%s", performance.date);
                printf("Type d'épreuve : ");
                scanf("%s", performance.type_epreuve);
                printf("Temps réalisé : ");
                scanf("%f", &performance.temps);
                performance.position_relay = -1;  // Modifier si relais
                enregistrerPerformance(athlete.nom, performance);
                break;
            case 3:
                printf("Nom de l'athlète pour l'historique : ");
                scanf("%s", athlete.nom);
                afficherHistoriqueAthlete(athlete.nom);
                break;
            case 4:
                printf("Nom de l'athlète pour les statistiques : ");
                scanf("%s", athlete.nom);
                afficherStatistiques(athlete.nom);
                break;
            case 5:
                return 0;
            default:
                printf("Choix invalide, veuillez réessayer.\n");
        }
    }
    
    return 0;
}
