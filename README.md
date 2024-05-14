#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Définition de la structure pour stocker les performances d'un athlète
typedef struct {
    char date[11];  // Format YYYY-MM-DD
    char event_type[20];  // Type d'épreuve (100m, 400m, etc.)
    float time;  // Temps réalisé
    int relay_position;  // Position dans le relais, -1 si non applicable
} AthletePerformance;

// Prototypes des fonctions à développer
void savePerformance(const char *filename, AthletePerformance performance);
void loadPerformances(const char *filename, AthletePerformance *performances, int *count);
void updatePerformance(const char *filename, AthletePerformance performance);
void displayAthleteHistory(const char *filename);
void displayStatistics(const char *filename);
void sortPerformancesByDate(AthletePerformance *performances, int count);
void sortPerformancesByEvent(AthletePerformance *performances, int count);

// Programme principal
int main() {
    // Initialisation des variables nécessaires
    char athleteName[50];
    AthletePerformance performance;
    int choice;
    
    // Menu principal pour interagir avec l'utilisateur
    while (1) {
        printf("\nMenu Principal:\n");
        printf("1. Entrer une nouvelle performance\n");
        printf("2. Afficher l'historique d'un athlète\n");
        printf("3. Afficher les statistiques d'un athlète\n");
        printf("4. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Nom de l'athlète : ");
                scanf("%s", athleteName);
                printf("Date (YYYY-MM-DD) : ");
                scanf("%s", performance.date);
                printf("Type d'épreuve : ");
                scanf("%s", performance.event_type);
                printf("Temps réalisé : ");
                scanf("%f", &performance.time);
                performance.relay_position = -1;  // Modifier si relais
                savePerformance(athleteName, performance);
                break;
            case 2:
                printf("Nom de l'athlète pour l'historique : ");
                scanf("%s", athleteName);
                displayAthleteHistory(athleteName);
                break;
            case 3:
                printf("Nom de l'athlète pour les statistiques : ");
                scanf("%s", athleteName);
                displayStatistics(athleteName);
                break;
            case 4:
                return 0;
            default:
                printf("Choix invalide, veuillez réessayer.\n");
        }
    }
    
    return 0;
}
