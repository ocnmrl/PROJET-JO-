#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Structure pour stocker une performance d'un athlète
typedef struct {
    char date[11];  // Format YYYY-MM-DD
    char epreuve[20];
    double temps;   // Temps réalisé en secondes
    int positionRelais; // Position dans le relais, 0 pour les épreuves individuelles
} Performance;

// Structure pour un athlète
typedef struct {
    char nom[50];
    Performance performances[100]; // Tableau des performances, taille arbitraire
    int nombrePerformances;
} Athlete;

// Fonction pour sauvegarder les performances d'un athlète dans un fichier
void sauvegarderPerformances(Athlete *athlete) {
    char nomFichier[60];
    sprintf(nomFichier, "%s.txt", athlete->nom);
    FILE *fichier = fopen(nomFichier, "w");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier %s\n", nomFichier);
        return;
    }
    for (int i = 0; i < athlete->nombrePerformances; i++) {
        fprintf(fichier, "%s %s %lf %d\n", athlete->performances[i].date,
                athlete->performances[i].epreuve, athlete->performances[i].temps,
                athlete->performances[i].positionRelais);
    }
    fclose(fichier);
}

// Fonction pour charger les performances d'un athlète depuis un fichier
void chargerPerformances(Athlete *athlete) {
    char nomFichier[60];
    sprintf(nomFichier, "%s.txt", athlete->nom);
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        // Si le fichier n'existe pas, on assume que c'est le premier usage et on continue sans erreur
        return;
    }
    Performance p;
    while (fscanf(fichier, "%s %s %lf %d", p.date, p.epreuve, &p.temps, &p.positionRelais) == 4) {
        athlete->performances[athlete->nombrePerformances++] = p;
    }
    fclose(fichier);
}

// Fonction pour afficher les statistiques d'un athlète pour une épreuve donnée
void statistiquesAthlete(Athlete *athlete, const char *epreuve) {
    double min = 1e9, max = 0, total = 0;
    int count = 0;
    for (int i = 0; i < athlete->nombrePerformances; i++) {
        if (strcmp(athlete->performances[i].epreuve, epreuve) == 0) {
            double temps = athlete->performances[i].temps;
            if (temps < min) min = temps;
            if (temps > max) max = temps;
            total += temps;
            count++;
        }
    }
    if (count == 0) {
        printf("Aucune performance trouvée pour %s dans l'épreuve %s\n", athlete->nom, epreuve);
        return;
    }
    printf("Athlète: %s, Épreuve: %s\n", athlete->nom, epreuve);
    printf("Meilleur temps: %lf, Pire temps: %lf, Moyenne: %lf\n", min, max, total / count);
}

// Fonction pour ajouter une nouvelle performance
void ajouterPerformance(Athlete *athlete) {
    if (athlete->nombrePerformances >= 100) {
        printf("Nombre maximum de performances atteint pour %s.\n", athlete->nom);
        return;
    }
    Performance p;
    printf("Entrer la date de l'entrainement (YYYY-MM-DD): ");
    scanf("%s", p.date);
    printf("Entrer le type d'épreuve: ");
    scanf("%s", p.epreuve);
    printf("Entrer le temps réalisé: ");
    scanf("%lf", &p.temps);
    p.positionRelais = 0;  // Mettre à jour si nécessaire pour les épreuves de relais
    athlete->performances[athlete->nombrePerformances++] = p;
    sauvegarderPerformances(athlete);
}

// Fonction pour afficher l'historique des performances
void afficherHistorique(Athlete *athlete) {
    printf("Historique des performances pour %s:\n", athlete->nom);
    for (int i = 0; i < athlete->nombrePerformances; i++) {
        printf("%s - %s - %lf s - Position Relais: %d\n", athlete->performances[i].date,
               athlete->performances[i].epreuve, athlete->performances[i].temps,
               athlete->performances[i].positionRelais);
    }
}

// Menu principal pour interagir avec l'utilisateur
void menu() {
    Athlete athlete;
    strcpy(athlete.nom, "John Doe");  // Modifier selon les besoins
    athlete.nombrePerformances = 0;
    chargerPerformances(&athlete);

    int choix;
    bool continuer = true;

    while (continuer) {
        printf("1. Entrer une nouvelle performance\n");
        printf("2. Afficher l'historique des performances\n");
        printf("3. Afficher les statistiques d'un athlète pour une épreuve\n");
        printf("4. Quitter\n");
        printf("Choisir une option: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajouterPerformance(&athlete);
                break;
            case 2:
                afficherHistorique(&athlete);
                break;
            case 3:
                {
                    char epreuve[20];
                    printf("Entrer le nom de l'épreuve pour les statistiques: ");
                    scanf("%s", epreuve);
                    statistiquesAthlete(&athlete, epreuve);
                }
                break;
            case 4:
                continuer = false;
                break;
            default:
                printf("Option invalide. Veuillez réessayer.\n");
        }
    }
}

int main() {
    menu();
    return 0;
}
