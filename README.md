#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// Structure pour stocker les performances d'un athlète
typedef struct {
    char date[11];  // Format AAAA-MM-JJ
    char epreuve[20];  // Type d'épreuve (100m, 400m, etc.)
    float temps;  // Temps réalisé
    int position_relais;  // Position dans le relais, -1 si non applicable
} Performance;

// Structure pour un athlète
typedef struct {
    char nom[50];
    Performance performances[100]; // Tableau des performances, taille arbitraire
    int nombrePerformances;
} Athlete;


void enregistrerAthlete(const char *nom_fichier, Athlete athlete);

void enregistrerAthlete(const char *nom_fichier, AthletePerformance performance) {
    FILE *fichier = fopen(nom_fichier, "a"); // Ouvre le fichier en mode append pour ajouter les nouvelles données sans écraser les anciennes
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s\n", nom_fichier);
        return;
    }
    // Écriture de la performance dans le fichier
    fprintf(fichier, "%s %s %.2f %d\n", performance.date, performance.event_type, performance.time, performance.relay_position);
    fclose(fichier);  // Fermeture du fichier
    printf("Performance enregistrée pour %s\n", nom_fichier);
}

void enregistrerPerformance(const char *nom_fichier, PerformanceAthlete performance);
void enregistrerPerformances(const char *nom_fichier, AthletePerformance *performances, int *nbPerformances) {
    FILE *fichier = fopen(nom_fichier, "r");  // Ouvre le fichier en mode lecture
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s\n", nom_fichier);
        *nbPerformances = 0; // aucune performance n'a été chargée en raison de l'échec de l'ouverture du fichier
        return; //  termine l'exécution de la fonction prématurément si une erreur survient
    }

int index = 0; // Initialise un compteur pour suivre le nombre de performances lues
    while (fgets(fichier, "%s %s %f %d", performances[index].date, performances[index].event_type, &performances[index].time, &performances[index].relay_position) == 4) {
        index++;
        if (index >= 100) break;  // Présumant un maximum de 100 performances
    }
    *nbPerformances = index; // on stocke le nombre total de performances lues dans la variable pointée par nbPerformances
    fclose(fichier);  // Fermeture du fichier
    printf("Performances chargées pour %s\n", nom_fichier);
}


void chargerPerformances(const char *nom_fichier, PerformanceAthlete *performances, int *nbPerformances);
void mettreAJourPerformance(const char *nom_fichier, PerformanceAthlete performance);
void afficherHistoriqueAthlete(const char *nom_fichier);

void afficherHistoriqueAthlete(const char *nom_fichier) {
    // Construire le nom complet du fichier basé sur le nom de l'athlète
    char nomCompletFichier[64];
    snprintf(nomCompletFichier, sizeof(nomCompletFichier), "%s.txt", nom_fichier);

    // Ouvrir le fichier en mode lecture
    FILE *fichier = fopen(nomCompletFichier, "r");
    if (!fichier) {
        printf("Impossible d'ouvrir le fichier %s pour lecture.\n", nomCompletFichier);
        return;
    }

    // Lire et afficher les performances de l'athlète
    Performance performance;
    printf("Historique des performances pour %s :\n", nom_fichier);
    while (fscanf(fichier, "%s %s %f %d", 
                  performance.date, performance.epreuve, 
                  &performance.temps, &performance.position_relais) == 4) {
        printf("Date : %s, Épreuve : %s, Temps : %.2f secondes", 
               performance.date, performance.epreuve, performance.temps);
        if (performance.position_relais != -1) {
            printf(", Position dans le relais : %d", performance.position_relais);
        }
        printf("\n");
    }

    // Fermer le fichier
    fclose(fichier);
}


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
